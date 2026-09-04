/*
 * SPDX-FileCopyrightText: 2026 James Murphy
 *
 * SPDX-License-Identifier: LicenseRef-Tavden-Proprietary
 */

#include "system_screen.h"

#include "asset_manager.h"
#include "field_widgets.h"

#include <array>

namespace screen {

SystemScreen::SystemScreen(viewmodel::BaseViewModel& view_model, app::AssetManager& assets)
    : BaseScreen(view_model, assets) {
    init();
}

void SystemScreen::build_content(lv_obj_t* content) {
    auto* heading = view::widgets::create_label(
        content, view_model(), assets(), "SYSTEM / LOCAL STATE", 9, true, true);
    lv_obj_set_style_text_letter_space(heading, 1, 0);
    lv_obj_align(heading, LV_ALIGN_TOP_LEFT, 8, 5);

    auto* timestamp = view::widgets::create_bound_label(
        content, view_model(), assets(), view_model().captured_at_subject(), 8, false, 120);
    lv_obj_set_style_text_align(timestamp, LV_TEXT_ALIGN_RIGHT, 0);
    lv_obj_align(timestamp, LV_ALIGN_TOP_RIGHT, -8, 6);

    struct Metric {
        const char* caption;
        lv_subject_t* subject;
    };
    const std::array<Metric, 6> metrics = {{
        {"HOST", view_model().hostname_subject()},
        {"ARCH", view_model().architecture_subject()},
        {"UPTIME", view_model().uptime_subject()},
        {"MEMORY", view_model().memory_subject()},
        {"STORAGE", view_model().storage_subject()},
        {"LOAD", view_model().load_subject()},
    }};

    for (std::size_t index = 0; index < metrics.size(); ++index) {
        auto* item = view::widgets::create_metric(
            content, view_model(), assets(), metrics[index].caption, metrics[index].subject, 98);
        const int32_t column = static_cast<int32_t>(index % 3);
        const int32_t row = static_cast<int32_t>(index / 3);
        lv_obj_align(item, LV_ALIGN_TOP_LEFT, 8 + column * 103, 24 + row * 40);
    }
}

} // namespace screen
