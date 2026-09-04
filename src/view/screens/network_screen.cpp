/*
 * SPDX-FileCopyrightText: 2026 James Murphy
 *
 * SPDX-License-Identifier: LicenseRef-Tavden-Proprietary
 */

#include "network_screen.h"

#include "asset_manager.h"
#include "field_widgets.h"

namespace screen {

NetworkScreen::NetworkScreen(viewmodel::BaseViewModel& view_model, app::AssetManager& assets)
    : BaseScreen(view_model, assets) {
    init();
}

void NetworkScreen::build_content(lv_obj_t* content) {
    auto* heading = view::widgets::create_label(
        content, view_model(), assets(), "NETWORK / PASSIVE", 9, true, true);
    lv_obj_set_style_text_letter_space(heading, 1, 0);
    lv_obj_align(heading, LV_ALIGN_TOP_LEFT, 8, 5);

    auto* local_only = view::widgets::create_label(
        content, view_model(), assets(), "NO PACKETS SENT", 8, true, false, true);
    lv_obj_align(local_only, LV_ALIGN_TOP_RIGHT, -8, 6);

    auto* identity = view::widgets::create_panel(content, view_model(), 116, 76);
    lv_obj_align(identity, LV_ALIGN_BOTTOM_LEFT, 8, -7);
    lv_obj_set_flex_flow(identity, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(identity, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_style_pad_row(identity, 1, 0);

    view::widgets::create_label(identity, view_model(), assets(), "INTERFACE", 9, true, true);
    view::widgets::create_bound_label(
        identity, view_model(), assets(), view_model().interface_subject(), 16, true, 100);
    view::widgets::create_bound_label(
        identity, view_model(), assets(), view_model().interface_type_subject(), 9, false, 100);
    auto* state = view::widgets::create_bound_label(
        identity, view_model(), assets(), view_model().link_subject(), 10, true, 100);
    lv_obj_set_style_pad_top(state, 3, 0);

    auto* address = view::widgets::create_metric(
        content, view_model(), assets(), "IPV4 ADDRESS", view_model().address_subject(), 178);
    lv_obj_align(address, LV_ALIGN_TOP_RIGHT, -8, 25);

    auto* traffic = lv_obj_create(content);
    lv_obj_remove_style_all(traffic);
    lv_obj_set_size(traffic, 178, 38);
    lv_obj_align(traffic, LV_ALIGN_BOTTOM_RIGHT, -8, -7);
    lv_obj_set_flex_flow(traffic, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(traffic, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(traffic, LV_OBJ_FLAG_SCROLLABLE);
    view::widgets::create_metric(
        traffic, view_model(), assets(), "RX BYTES", view_model().received_subject(), 84);
    view::widgets::create_metric(
        traffic, view_model(), assets(), "TX BYTES", view_model().transmitted_subject(), 84);
}

} // namespace screen
