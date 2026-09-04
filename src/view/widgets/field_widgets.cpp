/*
 * SPDX-FileCopyrightText: 2026 James Murphy
 *
 * SPDX-License-Identifier: LicenseRef-Tavden-Proprietary
 */

#include "field_widgets.h"

#include "asset_manager.h"
#include "base_viewmodel.h"
#include "bindings.h"

namespace view::widgets {

lv_obj_t* create_panel(lv_obj_t* parent,
                       viewmodel::BaseViewModel& view_model,
                       int32_t width,
                       int32_t height) {
    auto* panel = lv_obj_create(parent);
    lv_obj_remove_style_all(panel);
    lv_obj_set_size(panel, width, height);
    lv_obj_set_style_border_width(panel, 1, 0);
    lv_obj_set_style_pad_all(panel, 7, 0);
    lv_obj_clear_flag(panel, LV_OBJ_FLAG_SCROLLABLE);
    reactive::bind_theme(panel, view_model.dark_mode_subject(), reactive::ThemeRole::Button);
    return panel;
}

lv_obj_t* create_label(lv_obj_t* parent,
                       viewmodel::BaseViewModel& view_model,
                       app::AssetManager& assets,
                       const char* text,
                       int32_t size,
                       bool bold,
                       bool accent,
                       bool muted) {
    auto* label = lv_label_create(parent);
    lv_label_set_text(label, text ? text : "");
    auto* font = assets.load_standard_font(
        size,
        bold ? app::StandardFontWeight::Bold : app::StandardFontWeight::Regular);
    lv_obj_set_style_text_font(label, font ? font : &lv_font_montserrat_14, 0);
    reactive::bind_theme(label,
                         view_model.dark_mode_subject(),
                         accent ? reactive::ThemeRole::AccentText
                                : (muted ? reactive::ThemeRole::MutedText : reactive::ThemeRole::Text));
    return label;
}

lv_obj_t* create_bound_label(lv_obj_t* parent,
                             viewmodel::BaseViewModel& view_model,
                             app::AssetManager& assets,
                             lv_subject_t* subject,
                             int32_t size,
                             bool bold,
                             int32_t width) {
    auto* label = create_label(parent, view_model, assets, "", size, bold);
    lv_obj_set_width(label, width);
    lv_obj_set_height(label, size + 4);
    lv_label_set_long_mode(label, LV_LABEL_LONG_DOT);
    lv_label_bind_text(label, subject, nullptr);
    return label;
}

lv_obj_t* create_metric(lv_obj_t* parent,
                        viewmodel::BaseViewModel& view_model,
                        app::AssetManager& assets,
                        const char* caption,
                        lv_subject_t* value,
                        int32_t width) {
    auto* item = lv_obj_create(parent);
    lv_obj_remove_style_all(item);
    lv_obj_set_size(item, width, 38);
    lv_obj_set_flex_flow(item, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(item, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_style_pad_row(item, 1, 0);
    lv_obj_clear_flag(item, LV_OBJ_FLAG_SCROLLABLE);

    auto* caption_label = create_label(item, view_model, assets, caption, 9, true, true);
    lv_obj_set_style_text_letter_space(caption_label, 1, 0);
    create_bound_label(item, view_model, assets, value, 12, false, width);
    return item;
}

} // namespace view::widgets
