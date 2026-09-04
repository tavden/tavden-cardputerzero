/*
 * SPDX-FileCopyrightText: 2026 James Murphy
 *
 * SPDX-License-Identifier: LicenseRef-Tavden-Proprietary
 */

#include "system_info.h"

#include <cassert>
#include <iostream>

int main() {
    const auto snapshot = system_info::capture();
    const bool valid = !snapshot.hostname.empty() &&
                       !snapshot.kernel.empty() &&
                       !snapshot.architecture.empty() &&
                       !snapshot.memory.empty() &&
                       !snapshot.storage.empty() &&
                       !snapshot.captured_at.empty();
    if (!valid) {
        std::cerr << "system snapshot contains an empty required field\n";
        return 1;
    }
    std::cout << "snapshot: " << snapshot.hostname << " | " << snapshot.architecture
              << " | " << snapshot.memory << " | " << snapshot.interface_name << '\n';

    const auto demo = system_info::demo();
    assert(demo.hostname == "cardputerzero");
    assert(demo.architecture == "aarch64");
    assert(demo.ipv4_address == "192.0.2.42");
    return 0;
}
