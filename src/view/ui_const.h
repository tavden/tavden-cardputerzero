/*
 * SPDX-FileCopyrightText: 2026 M5Stack Technology CO LTD
 * SPDX-FileCopyrightText: 2026 James Murphy
 *
 * SPDX-License-Identifier: MIT
 */



#pragma once

#include <cstdint>

namespace view {

// some font constants
constexpr const char* ICON_SIGN_OUT           = "\uE42A";
constexpr const char* ICON_TEXT_BOLD          = "\uE5BE";
constexpr const char* ICON_MOON               = "\uE330";
constexpr const char* ICON_SUN                = "\uE474";
constexpr const char* ICON_SQUARE_ARROW_LEFT  = "\uE074";
constexpr const char* ICON_SQUARE_ARROW_RIGHT = "\uE076";
constexpr const char* ICON_MINUS              = "\uE32A";
constexpr const char* ICON_PLUS               = "\uE3D4";
constexpr const char* ICON_INFO               = "\uE2CE";
constexpr const char* ICON_WIFI_NONE          = "\uE4F0";
constexpr const char* ICON_WIFI_LOW           = "\uE4EC";
constexpr const char* ICON_WIFI_MEDIUM        = "\uE4EE";
constexpr const char* ICON_WIFI_HIGH          = "\uE4EA";
constexpr const char* ICON_ETHERNET           = "\uEDDE";
constexpr const char* ICON_BAT_FULL           = "\uE7C4";
constexpr const char* ICON_BAT_HIGH           = "\uE7C2";
constexpr const char* ICON_BAT_MEDIUM         = "\uE7C0";
constexpr const char* ICON_BAT_LOW            = "\uE7BE";
constexpr const char* ICON_BAT_EMPTY          = "\uE7C6";
constexpr const char* ICON_BAT_CHARGING       = "\uE0BC";

namespace color {

// Tavden field-system palette: mist, steel, blueprint, obsidian and brass.
namespace light {
constexpr uint32_t kPrimary      = 0x9A6D25;
constexpr uint32_t kInfo         = 0x35577C;
constexpr uint32_t kSuccess      = 0x3E7255;
constexpr uint32_t kWarning      = 0x9A6D25;
constexpr uint32_t kError        = 0x9D4651;
constexpr uint32_t kBody         = 0xE8EBEF;
constexpr uint32_t kCard         = 0xF2F4F7;
constexpr uint32_t kAction       = 0xDDE2E8;
constexpr uint32_t kButton       = 0xF2F4F7;
constexpr uint32_t kBorder       = 0xAAB2BD;
constexpr uint32_t kTextPrimary  = 0x0E1421;
constexpr uint32_t kTextDisabled = 0x5F6875;
} // namespace light

namespace dark {
constexpr uint32_t kPrimary      = 0xCDA15A;
constexpr uint32_t kInfo         = 0x6F91B8;
constexpr uint32_t kSuccess      = 0x78AD8D;
constexpr uint32_t kWarning      = 0xCDA15A;
constexpr uint32_t kError        = 0xD97883;
constexpr uint32_t kBody         = 0x090C12;
constexpr uint32_t kCard         = 0x0E1421;
constexpr uint32_t kAction       = 0x101B2D;
constexpr uint32_t kButton       = 0x132440;
constexpr uint32_t kBorder       = 0x263346;
constexpr uint32_t kTextPrimary  = 0xF2F4F7;
constexpr uint32_t kTextDisabled = 0x8E96A3;
} // namespace dark

} // namespace color

} // namespace view
