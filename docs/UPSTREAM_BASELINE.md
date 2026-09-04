# Upstream baseline

Reviewed on 4 September 2026.

## Selected official baseline

The project was scaffolded from the current
[CardputerZero application template](https://github.com/CardputerZero/Template)
at:

    80ca83ebb6e8e54da302a0a7fe6dfc1d893242de
    2026-09-01 — fix: popup hint

That repository is the application template linked from the Quick Start area
of the official [CardputerZero documentation](https://docs.m5stack.com/en/CardputerZero).
At the reviewed revision it provides:

- CMake 3.31 presets;
- LVGL v9.5.0;
- an SDL2 desktop simulator;
- Linux framebuffer and evdev device paths;
- an aarch64-linux-gnu cross toolchain;
- CM0 BSP sysroot release v0.0.4; and
- CPack generation of an arm64 Debian package.

This is the supported shape used by Tavden Zero.

## Packaging and store metadata

The [CardputerZero AppBuilder](https://github.com/CardputerZero/AppBuilder) was
reviewed at:

    64edc2292628b436d3e624b150faeed2d60c31af
    2026-08-26 — feat(czdev): pass deb Maintainer to the store policy pre-check

Its current czdev scaffold/publish metadata informed app-builder.json, the
320 × 170 screenshots, icon sizing, four-character share code, explicit
permission declarations and non-root packaging.

The official [CardputerZero launcher](https://github.com/CardputerZero/launcher)
was also checked for its LVGL/APPLaunch conventions.

## Resources not selected as the application base

The older
[M5Stack Linux libraries](https://github.com/m5stack/M5Stack_Linux_Libs) were
reviewed at commit:

    8c412407623badbc24ed710b55f7a80b6a8d2fb3
    2026-04-07 — [add] lvgl 9_5

Those resources use the earlier SCons-oriented project shape. They remain
useful historical context, but the official documentation now links the newer
CMake CardputerZero template, so Tavden Zero does not force the older build
layout into the project.

## Tavden references

The public [Tavden Field Suite](https://github.com/tavden/tavden-field-suite)
release was reviewed at:

    bbb09c94bbc5c7d84a022eb0edc45e3c7c6d44e7
    2026-08-14 — Launch Tavden Field Suite v1.0.0

The public [Tavden website](https://tavden.com/) was reviewed at:

    c77fdd0d99559dd0421489f7f69c014e80c6c1d1
    2026-08-16 — Publish Tavden Field Suite v1.0.0 release status

The existing Field Suite repository contains release binaries and
documentation rather than reusable application source. Tavden Zero therefore
reuses brand principles, palette and product discipline, not ESP32
implementation code.

## Current documentation caveat

The official CardputerZero product page still describes parts of the platform
documentation as work in progress, with SDK/kernel sections pending. The
application template and AppBuilder are active but evolving. Exact upstream
revisions are recorded here so future changes can be evaluated intentionally
instead of silently changing the build.
