# Validation record

Validation date: 4 September 2026

This record covers the pre-hardware Tavden Zero 0.1.0 proof of concept. It
documents what was actually exercised and keeps physical-device claims
separate.

## Build and test

| Check | Result |
| --- | --- |
| Linux x86-64 Release simulator build | Pass |
| system_info_snapshot automated test | Pass |
| AArch64 Release cross-build | Pass |
| Executable format | ELF 64-bit LSB PIE, ARM aarch64, GNU/Linux |
| Debian package generation | Pass |
| Debian package identity | tavden-cardputerzero 0.1.0-m5stack1, arm64 |

The AArch64 build used the official-template toolchain shape, CM0 BSP sysroot
v0.0.4, LVGL v9.5.0 and the aarch64-linux-gnu GCC/G++ toolchain.

## Package inspection

The generated package was unpacked and inspected:

- binary installed at /usr/bin/tavden-cardputerzero;
- APPLaunch desktop entry and 256/100/80 px Tavden icons present;
- /etc/tavden-zero.conf registered as a conffile;
- project, third-party and split licence notices present;
- architecture is arm64;
- no systemd service is installed;
- no setuid file is present; and
- declared runtime libraries match the ELF dynamic dependencies.

The downloadable package's cryptographic hash is published with the
[v0.1.0 proof-of-concept pre-release](https://github.com/tavden/tavden-cardputerzero/releases/tag/v0.1.0-poc.1).

## UI and screenshot inspection

Overview, System and Network screenshots were generated from the desktop LVGL
surface and checked as 320 × 170 RGBA PNG files. All three use
TAVDEN_DEMO_MODE=1:

- fictional host: cardputerzero;
- fictional interface: wlan0;
- reserved documentation IPv4: 192.0.2.42; and
- fixed sample system values.

The screenshots were visually inspected for clipping and overlap. They are
simulator evidence, not photographs or claims of physical hardware operation.

## Privacy inspection

The release binary, unpacked Debian package and publishable source were scanned
for:

- the development computer's hostname;
- its network-interface name;
- its absolute home-directory path;
- observed local address values; and
- generic RFC 1918 private IPv4 patterns.

No match was found. Compiler prefix mapping removes build-host source paths
from release log strings and binaries. Generated build/dependency directories
are excluded from the clean source deliverable.

The public screenshots were regenerated after this check using only demo data.

## CardputerZero store metadata

The generated store layout was checked with the official
CardputerZero/packages metadata policy at registry revision:

    cbe62f309158ff6b928bb9cd0388e3d412dd2b94

Results:

- blocking errors: 0;
- advisory warnings: 0;
- title Tavden Zero was not already present; and
- share code TVDN was not already present at the reviewed registry revision.

Store metadata is prepared but has not been submitted. The `source_repo` URL
points to the published
[Tavden CardputerZero repository](https://github.com/tavden/tavden-cardputerzero).

## Not validated

No physical CardputerZero was available. The following remain pending:

- framebuffer orientation, colour and refresh;
- keyboard evdev discovery and final key mapping;
- APPLaunch behaviour on the shipping image;
- battery/status sysfs compatibility;
- temperature, power, performance and stability; and
- the real-device video required for first store submission.

Use [HARDWARE_TEST_PLAN.md](HARDWARE_TEST_PLAN.md) before changing any of those
items to passed.
