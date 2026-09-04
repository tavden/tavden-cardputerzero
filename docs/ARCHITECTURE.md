# Architecture

## Intent

Tavden Zero is a Linux application designed for CardputerZero, not an ESP32
firmware compatibility layer. The proof of concept preserves Tavden's
keyboard-first interaction, restrained visual language and module boundaries
while using normal Linux facilities and the official LVGL platform baseline.

The first milestone is deliberately narrow: prove that the application shell,
device-sized UI, AArch64 build and a useful read-only module are credible
before making claims that require physical hardware.

## Data flow

    /proc, /sys and Linux APIs
               |
               v
       system_info::capture()
               |
               v
      immutable Snapshot value
               |
               v
      BaseViewModel::refresh_data()
               |
               v
        LVGL reactive subjects
               |
               v
     Overview / System / Network

Capture is synchronous, bounded and initiated at startup or by the user with
key 6. The UI never presents background polling as live telemetry. Each refresh
publishes a coherent snapshot and capture time.

## Layers

### System service

src/system owns Linux-native information collection. It has no dependency on
LVGL, making it independently testable. Its Snapshot value is the boundary
between operating-system data and presentation.

The service currently uses:

- uname and gethostname for host identity;
- sysinfo and /proc/meminfo for uptime, load and memory;
- statvfs for root filesystem capacity;
- getifaddrs for local IPv4/interface discovery; and
- /sys/class/net statistics for RX/TX byte counters.

### Model and view model

The model stores current page and theme. BaseViewModel translates an immutable
system snapshot into LVGL subjects and exposes the small action surface used by
the keyboard and views: navigate, refresh, toggle theme and exit.

### View

The view is built from LVGL objects at a fixed logical resolution of 320 × 170.
It contains three screens and reusable field-style metric/panel widgets.
Tavden's obsidian, midnight, blueprint, mist, steel and brass palette is
centralized in the theme constants.

### Platform

On CardputerZero, LVGL uses the Linux framebuffer backend and an evdev keypad.
On desktop, SDL2 renders exactly the same 320 × 170 LVGL surface in a simulator
frame. Device-status and screenshot services also live behind this boundary.

## Navigation

Keys 4–8 are treated as fixed soft keys matching the labels in the bottom bar:

- 4: exit from overview or return home from a module;
- 5: System;
- 6: refresh;
- 7: Network;
- 8: light/dark mode.

Escape mirrors key 4. Help and Print Screen are global actions when those Linux
key events are available.

## Safety properties

The proof of concept intentionally has no active network behavior:

- no sockets are opened;
- no DNS or HTTP requests are made at runtime;
- no hosts or ports are scanned;
- no interface or routing state is changed;
- no privileged command is executed;
- no background service is installed; and
- no root execution is required or expected.

Accordingly, app-builder.json declares every optional device permission false.
Build-time dependency downloads are separate from application runtime behavior.

## Extension boundaries

Future modules should depend on small service interfaces that return value
objects, then publish those values through the view model. Good next modules
include session notes, removable-storage status and a serial-terminal
foundation. Device-specific logic should stay in src/platform rather than leak
into screens.

Any future capability that transmits data, changes system state or requires
additional hardware must be visibly separated, permission-gated and documented
before it is enabled.
