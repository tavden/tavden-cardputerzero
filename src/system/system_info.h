/*
 * SPDX-FileCopyrightText: 2026 James Murphy
 *
 * SPDX-License-Identifier: LicenseRef-Tavden-Proprietary
 */

#pragma once

#include <string>

namespace system_info {

struct Snapshot {
    std::string hostname;
    std::string os_name;
    std::string kernel;
    std::string architecture;
    std::string uptime;
    std::string load;
    std::string memory;
    std::string storage;
    std::string interface_name;
    std::string interface_type;
    std::string link_state;
    std::string ipv4_address;
    std::string received;
    std::string transmitted;
    std::string captured_at;
};

// Reads local, non-privileged Linux system state. No packets are sent and no
// configuration is changed.
Snapshot capture();

// Deterministic fictional data for public screenshots and UI demonstrations.
// The IPv4 value is from TEST-NET-1 (RFC 5737), not a reachable private host.
Snapshot demo();

} // namespace system_info
