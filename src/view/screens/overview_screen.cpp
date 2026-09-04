/*
 * SPDX-FileCopyrightText: 2026 James Murphy
 *
 * SPDX-License-Identifier: LicenseRef-Tavden-Proprietary
 */

#include "overview_screen.h"

#include "asset_manager.h"
#include "bindings.h"
#include "field_widgets.h"
#include "theme.h"

namespace screen {
namespace {

void configure_module_panel(lv_obj_t* panel) {
    lv_obj_set_flex_flow(panel, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(panel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_style_pad_row(panel, 1, 0);
}

} // namespace

OverviewScreen::OverviewScreen(viewmodel::BaseViewModel& view_model, app::AssetManager& assets)
    : BaseScreen(view_model, assets) {
    init();
}

void OverviewScreen::build_content(lv_obj_t* content) {
    auto* accent = lv_obj_create(content);
    lv_obj_remove_style_all(accent);
    lv_obj_set_size(accent, 3, 88);
    lv_obj_align(accent, LV_ALIGN_LEFT_MID, 8, 0);
    lv_obj_set_style_bg_opa(accent, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(accent, view::palette(view_model().is_dark_mode()).primary, 0);
    reactive::observe_obj(accent,
                          view_model().dark_mode_subject(),
                          [](lv_observer_t* observer, lv_subject_t* subject) {
                              auto* object = lv_observer_get_target_obj(observer);
                              if (object) {
                                  lv_obj_set_style_bg_color(
                                      object,
                                      view::palette(lv_subject_get_int(subject) != 0).primary,
                                      0);
                              }
                          });

    auto* identity = lv_obj_create(content);
    lv_obj_remove_style_all(identity);
    lv_obj_set_size(identity, 114, 96);
    lv_obj_align(identity, LV_ALIGN_LEFT_MID, 18, 0);
    lv_obj_set_flex_flow(identity, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(identity, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_style_pad_row(identity, 0, 0);
    lv_obj_clear_flag(identity, LV_OBJ_FLAG_SCROLLABLE);

    auto* kicker = view::widgets::create_label(
        identity, view_model(), assets(), "FIELD SYSTEM", 8, true, true);
    lv_obj_set_style_text_letter_space(kicker, 1, 0);
    view::widgets::create_label(identity, view_model(), assets(), "TAVDEN", 22, true);
    view::widgets::create_label(identity, view_model(), assets(), "ZERO", 22, false);
    auto* proof = view::widgets::create_label(
        identity, view_model(), assets(), "LINUX / V0.1", 8, false, false, true);
    lv_obj_set_style_pad_top(proof, 5, 0);

    auto* modules = lv_obj_create(content);
    lv_obj_remove_style_all(modules);
    lv_obj_set_size(modules, 180, 94);
    lv_obj_align(modules, LV_ALIGN_RIGHT_MID, -6, 0);
    lv_obj_clear_flag(modules, LV_OBJ_FLAG_SCROLLABLE);

    auto* system_panel = view::widgets::create_panel(modules, view_model(), 180, 44);
    lv_obj_align(system_panel, LV_ALIGN_TOP_MID, 0, 0);
    configure_module_panel(system_panel);
    auto* system_heading = view::widgets::create_label(
        system_panel, view_model(), assets(), "01 / SYSTEM", 9, true, true);
    lv_obj_set_style_text_letter_space(system_heading, 1, 0);
    view::widgets::create_bound_label(
        system_panel, view_model(), assets(), view_model().hostname_subject(), 12, true, 164);

    auto* network_panel = view::widgets::create_panel(modules, view_model(), 180, 44);
    lv_obj_align(network_panel, LV_ALIGN_BOTTOM_MID, 0, 0);
    configure_module_panel(network_panel);
    auto* network_heading = view::widgets::create_label(
        network_panel, view_model(), assets(), "02 / NETWORK", 9, true, true);
    lv_obj_set_style_text_letter_space(network_heading, 1, 0);
    view::widgets::create_bound_label(
        network_panel, view_model(), assets(), view_model().link_subject(), 12, true, 164);
}

} // namespace screen
