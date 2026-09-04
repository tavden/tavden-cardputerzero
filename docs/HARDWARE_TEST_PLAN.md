# CardputerZero hardware test plan

## Purpose

This plan separates build/simulator evidence from claims that require a
physical CardputerZero. No item below should be marked passed without recording
the device, image version, tester, date and evidence.

## Test record

| Field | Value |
| --- | --- |
| Device / serial | Not available |
| CardputerZero image | Not tested |
| Package | tavden-cardputerzero 0.1.0 |
| Tester | Pending |
| Test date | Pending |
| Overall result | **Not run — hardware required** |

## 1. Install and launcher

- Install the arm64 Debian package without unresolved dependencies.
- Confirm the package places no service in systemd and starts no background
  process.
- Confirm APPLaunch displays the Tavden icon, name and description.
- Launch as the standard logged-in user, not root.
- Exit from overview and confirm control returns cleanly to the launcher.
- Remove and reinstall the package; confirm /etc/tavden-zero.conf is handled as
  a conffile.

Evidence: terminal transcript, APPLaunch photo and package version.

## 2. Display

- Confirm native 320 × 170 output fills the panel with correct orientation.
- Compare overview, System and Network views with simulator reference images.
- Check brass, mist, steel, blueprint and obsidian colours by eye.
- Check that no text clips or wraps unexpectedly with the device hostname,
  memory and storage values.
- Toggle light/dark mode repeatedly.
- Confirm no tearing, corruption or stale regions during navigation/refresh.

Evidence: straight-on photographs of all three views in both themes.

## 3. Keyboard and input discovery

- Record the selected /dev/input/event* node and its reported device name.
- Verify keys 4, 5, 6, 7 and 8 match the bottom bar.
- Verify Escape returns home and exits only from overview.
- Verify Help opens/closes the keyboard guide if the image exposes KEY_HELP.
- Verify Print Screen saves a PNG if the image exposes KEY_SYSRQ.
- Hold and rapidly repeat navigation keys; check for duplicate or stuck input.
- Relaunch with APP_KEY_INPUT_DEVICE explicitly set to the recorded node.

Evidence: evdev identification and a key-by-key result table.

## 4. System module accuracy

- Compare hostname and architecture with uname/hostname.
- Compare uptime and one-minute load with /proc/uptime and /proc/loadavg.
- Compare memory values with /proc/meminfo.
- Compare root storage with df.
- Press key 6 and confirm values/capture time refresh as a coherent snapshot.

Evidence: module photo plus matching shell output.

## 5. Network module accuracy and passivity

- Test with Wi-Fi connected, disconnected and reconnecting.
- If available, test another non-loopback interface.
- Compare interface name/address/state with ip addr.
- Compare RX/TX counters with /sys/class/net/INTERFACE/statistics.
- Observe traffic while pressing refresh and confirm Tavden Zero originates no
  packets.
- Confirm no runtime network permission is needed.

Evidence: module photo, matching shell output and passive traffic observation.

## 6. Device-status indicators

- Verify Wi-Fi/ethernet presence and icon changes.
- Compare displayed battery percentage/charging state with the relevant sysfs
  power-supply entries.
- Test with USB power attached and removed.
- Record any image-specific sysfs paths needed by the CardputerZero.

Evidence: photos and sysfs values.

## 7. Resource and stability checks

- Record startup time and peak resident memory.
- Navigate and refresh for ten minutes; check for increasing memory use.
- Run a 30-minute idle/refresh soak.
- Record CPU usage, temperature and battery impact.
- Suspend/resume or display blank/wake if supported by the image.
- Confirm graceful behavior when /proc or /sys values are temporarily
  unavailable.

Evidence: resource log and soak result.

## Acceptance gate for outreach claims

Before changing the README status to hardware-tested:

- all install, display and key-navigation checks must pass;
- system/network values must match independent commands;
- passive behavior must be confirmed;
- at least a 30-minute soak must complete without a crash; and
- real-device photos/video must replace simulator-only evidence where required
  by the M5Stack submission process.

Issues should be recorded with image version and reproduction steps. Hardware
differences must be fixed in src/platform or configuration rather than hidden
in individual screens.
