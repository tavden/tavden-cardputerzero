/*
 * SPDX-FileCopyrightText: 2026 James Murphy
 *
 * SPDX-License-Identifier: LicenseRef-Tavden-Proprietary
 */

#include "system_info.h"

#include <algorithm>
#include <array>
#include <chrono>
#include <cctype>
#include <cstdint>
#include <cstdio>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#if defined(__linux__)
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <sys/statvfs.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <unistd.h>
#endif

namespace system_info {
namespace {

std::string trim(std::string value) {
    const auto visible = [](unsigned char ch) { return std::isspace(ch) == 0; };
    value.erase(value.begin(), std::find_if(value.begin(), value.end(), visible));
    value.erase(std::find_if(value.rbegin(), value.rend(), visible).base(), value.end());
    return value;
}

std::string unquote(std::string value) {
    value = trim(std::move(value));
    if (value.size() >= 2 && value.front() == '"' && value.back() == '"') {
        return value.substr(1, value.size() - 2);
    }
    return value;
}

uint64_t read_counter(const std::filesystem::path& path) {
    std::ifstream input(path);
    uint64_t value = 0;
    return input >> value ? value : 0;
}

std::string human_bytes(uint64_t bytes) {
    static constexpr std::array<const char*, 4> units = {"B", "KB", "MB", "GB"};
    double value = static_cast<double>(bytes);
    std::size_t unit = 0;
    while (value >= 1024.0 && unit + 1 < units.size()) {
        value /= 1024.0;
        ++unit;
    }

    std::ostringstream output;
    output << std::fixed << std::setprecision(unit < 2 ? 0 : 1) << value << ' ' << units[unit];
    return output.str();
}

std::string format_pair(uint64_t used, uint64_t total) {
    if (total == 0) {
        return "Unavailable";
    }
    const bool use_gibibytes = total >= 1024ULL * 1024ULL * 1024ULL;
    const double divisor = use_gibibytes ? 1024.0 * 1024.0 * 1024.0 : 1024.0 * 1024.0;
    std::ostringstream output;
    output << std::fixed << std::setprecision(use_gibibytes ? 1 : 0)
           << static_cast<double>(used) / divisor << " / "
           << static_cast<double>(total) / divisor << (use_gibibytes ? " GB" : " MB");
    return output.str();
}

std::string format_uptime(long seconds) {
    if (seconds < 0) {
        return "Unavailable";
    }
    const long days = seconds / 86400;
    const long hours = (seconds % 86400) / 3600;
    const long minutes = (seconds % 3600) / 60;
    std::ostringstream output;
    if (days > 0) {
        output << days << "d ";
    }
    output << hours << "h " << minutes << "m";
    return output.str();
}

std::string capture_time() {
    const std::time_t now = std::time(nullptr);
    std::tm local{};
#if defined(_WIN32)
    localtime_s(&local, &now);
#else
    localtime_r(&now, &local);
#endif
    std::array<char, 20> text{};
    std::strftime(text.data(), text.size(), "%H:%M:%S", &local);
    return text.data();
}

std::string read_os_name() {
    std::ifstream input("/etc/os-release");
    std::string line;
    while (std::getline(input, line)) {
        const auto separator = line.find('=');
        if (separator == std::string::npos || line.substr(0, separator) != "PRETTY_NAME") {
            continue;
        }
        return unquote(line.substr(separator + 1));
    }
    return "Linux";
}

#if defined(__linux__)
struct NetworkCandidate {
    std::string name;
    std::string address;
    bool running{false};
    int priority{0};
};

int interface_priority(const std::string& name) {
    if (name.rfind("wl", 0) == 0) return 30;
    if (name.rfind("en", 0) == 0 || name.rfind("eth", 0) == 0) return 20;
    return 10;
}

void read_network(Snapshot& snapshot) {
    ifaddrs* addresses = nullptr;
    if (getifaddrs(&addresses) != 0 || !addresses) {
        return;
    }

    std::vector<NetworkCandidate> candidates;
    for (auto* item = addresses; item; item = item->ifa_next) {
        if (!item->ifa_addr || item->ifa_addr->sa_family != AF_INET || !item->ifa_name) {
            continue;
        }
        if ((item->ifa_flags & IFF_LOOPBACK) != 0) {
            continue;
        }

        std::array<char, INET_ADDRSTRLEN> address{};
        const auto* socket_address = reinterpret_cast<sockaddr_in*>(item->ifa_addr);
        if (!inet_ntop(AF_INET, &socket_address->sin_addr, address.data(), address.size())) {
            continue;
        }

        const bool up = (item->ifa_flags & IFF_UP) != 0;
        const bool running = (item->ifa_flags & IFF_RUNNING) != 0;
        candidates.push_back({item->ifa_name,
                              address.data(),
                              up && running,
                              interface_priority(item->ifa_name) + (up && running ? 100 : 0)});
    }
    freeifaddrs(addresses);

    if (candidates.empty()) {
        return;
    }
    const auto selected = std::max_element(candidates.begin(), candidates.end(),
                                           [](const auto& left, const auto& right) {
                                               return left.priority < right.priority;
                                           });
    snapshot.interface_name = selected->name;
    snapshot.ipv4_address = selected->address;
    snapshot.link_state = selected->running ? "UP / CONNECTED" : "DOWN";
    snapshot.interface_type = selected->name.rfind("wl", 0) == 0 ? "WIRELESS" : "WIRED / OTHER";

    const std::filesystem::path statistics =
        std::filesystem::path("/sys/class/net") / selected->name / "statistics";
    snapshot.received = human_bytes(read_counter(statistics / "rx_bytes"));
    snapshot.transmitted = human_bytes(read_counter(statistics / "tx_bytes"));
}
#endif

} // namespace

Snapshot capture() {
    Snapshot snapshot{
        "Unavailable", "Linux", "Unavailable", "Unavailable",
        "Unavailable", "Unavailable", "Unavailable", "Unavailable",
        "No active interface", "NONE", "OFFLINE", "Not assigned", "0 B", "0 B", capture_time()
    };

#if defined(__linux__)
    std::array<char, 256> hostname{};
    if (gethostname(hostname.data(), hostname.size() - 1) == 0) {
        snapshot.hostname = hostname.data();
    }

    utsname kernel{};
    if (uname(&kernel) == 0) {
        snapshot.kernel = std::string(kernel.sysname) + " " + kernel.release;
        snapshot.architecture = kernel.machine;
    }
    snapshot.os_name = read_os_name();

    struct sysinfo info {};
    if (sysinfo(&info) == 0) {
        snapshot.uptime = format_uptime(info.uptime);
        const uint64_t total = static_cast<uint64_t>(info.totalram) * info.mem_unit;
        uint64_t available = static_cast<uint64_t>(info.freeram) * info.mem_unit;

        std::ifstream memory_info("/proc/meminfo");
        std::string key;
        uint64_t value_kib = 0;
        std::string unit;
        while (memory_info >> key >> value_kib >> unit) {
            if (key == "MemAvailable:") {
                available = value_kib * 1024U;
                break;
            }
        }
        snapshot.memory = format_pair(total > available ? total - available : 0, total);

        std::ostringstream load;
        load << std::fixed << std::setprecision(2)
             << static_cast<double>(info.loads[0]) / static_cast<double>(1U << SI_LOAD_SHIFT);
        snapshot.load = load.str() + " (1 min)";
    }

    struct statvfs filesystem {};
    if (statvfs("/", &filesystem) == 0) {
        const uint64_t total = static_cast<uint64_t>(filesystem.f_blocks) * filesystem.f_frsize;
        const uint64_t available = static_cast<uint64_t>(filesystem.f_bavail) * filesystem.f_frsize;
        snapshot.storage = format_pair(total > available ? total - available : 0, total);
    }

    read_network(snapshot);
#else
    snapshot.os_name = "Desktop preview";
#endif
    return snapshot;
}

Snapshot demo() {
    return Snapshot{
        "cardputerzero",
        "Debian GNU/Linux",
        "Linux 6.x",
        "aarch64",
        "0h 42m",
        "0.18 (1 min)",
        "196 / 512 MB",
        "1.8 / 7.3 GB",
        "wlan0",
        "WIRELESS",
        "UP / CONNECTED",
        "192.0.2.42",
        "12.4 MB",
        "1.8 MB",
        "12:34:56",
    };
}

} // namespace system_info
