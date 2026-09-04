/*
 * SPDX-FileCopyrightText: 2026 M5Stack Technology CO LTD
 * SPDX-FileCopyrightText: 2026 James Murphy
 *
 * SPDX-License-Identifier: MIT
 */

#include "navbar.h"

#include "asset_manager.h"
#include "linux_input.h"
#include "theme.h"

namespace view::widgets {
namespace {

constexpr std::array<const char*, 5> kOverviewLabels = {
    "4 EXIT", "5 SYS", "6 SYNC", "7 NET", "8 MODE"
};
constexpr std::array<const char*, 5> kModuleLabels = {
    "4 HOME", "5 SYS", "6 SYNC", "7 NET", "8 MODE"
};
constexpr std::array<lv_event_cb_t, 5> kCallbacks = {
    NavBar::primary_cb,
    NavBar::system_cb,
    NavBar::refresh_cb,
    NavBar::network_cb,
    NavBar::theme_cb,
};

} // namespace

NavBar::NavBar(lv_obj_t* parent, viewmodel::BaseViewModel& view_model, app::AssetManager& assets)
    : BaseWidgets(parent), view_model_(view_model), assets_(assets) {}

NavBar::~NavBar() {
    for (std::size_t index = 0; index < buttons_.size(); ++index) {
        if (buttons_[index]) {
            platform::unregister_nav_button(index, buttons_[index]);
        }
    }
    if (page_observer_) lv_observer_remove(page_observer_);
    if (theme_observer_) lv_observer_remove(theme_observer_);
}

void NavBar::build() {
    if (core_obj_) return;

    core_obj_ = lv_obj_create(parent_);
    lv_obj_remove_style_all(core_obj_);
    lv_obj_set_size(core_obj_, LV_PCT(100), kNavBarHeight);
    lv_obj_align(core_obj_, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_flex_flow(core_obj_, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(core_obj_, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_hor(core_obj_, 3, 0);
    lv_obj_clear_flag(core_obj_, LV_OBJ_FLAG_SCROLLABLE);

    const lv_font_t* font = assets_.load_standard_font(9, app::StandardFontWeight::Bold);
    if (!font) font = &lv_font_montserrat_12;

    for (std::size_t index = 0; index < buttons_.size(); ++index) {
        auto* button = lv_button_create(core_obj_);
        lv_obj_remove_style_all(button);
        lv_obj_set_size(button, 60, 28);
        lv_obj_set_style_bg_opa(button, LV_OPA_TRANSP, 0);
        lv_obj_set_style_pad_all(button, 0, 0);
        lv_obj_clear_flag(button, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_add_event_cb(button, kCallbacks[index], LV_EVENT_CLICKED, &view_model_);

        auto* label = lv_label_create(button);
        lv_obj_set_style_text_font(label, font, 0);
        lv_obj_center(label);

        auto* indicator = lv_obj_create(button);
        lv_obj_remove_style_all(indicator);
        lv_obj_set_size(indicator, 22, 2);
        lv_obj_align(indicator, LV_ALIGN_BOTTOM_MID, 0, 0);
        lv_obj_clear_flag(indicator, LV_OBJ_FLAG_CLICKABLE);

        buttons_[index] = button;
        labels_[index] = label;
        indicators_[index] = indicator;
        platform::register_nav_button(index, button);
    }

    platform::set_nav_shortcut_mode(false);
    page_observer_ = lv_subject_add_observer(view_model_.current_page_subject(), state_observer_cb, this);
    theme_observer_ = lv_subject_add_observer(view_model_.dark_mode_subject(), state_observer_cb, this);
    update();
}

void NavBar::update() {
    const bool overview = view_model_.current_page() == model::AppPage::Overview;
    const auto& labels = overview ? kOverviewLabels : kModuleLabels;
    for (std::size_t index = 0; index < labels_.size(); ++index) {
        lv_label_set_text(labels_[index], labels[index]);
        lv_obj_center(labels_[index]);
    }
    style();
}

void NavBar::style() {
    const auto colors = view::palette(view_model_.is_dark_mode());
    lv_obj_set_style_bg_opa(core_obj_, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(core_obj_, colors.bar, 0);
    lv_obj_set_style_border_width(core_obj_, 1, 0);
    lv_obj_set_style_border_side(core_obj_, LV_BORDER_SIDE_TOP, 0);
    lv_obj_set_style_border_color(core_obj_, colors.border, 0);

    const auto page = view_model_.current_page();
    for (std::size_t index = 0; index < labels_.size(); ++index) {
        const bool active = (index == 1 && page == model::AppPage::System) ||
                            (index == 3 && page == model::AppPage::Network);
        lv_obj_set_style_text_color(labels_[index], active ? colors.primary : colors.text_disabled, 0);
        lv_obj_set_style_bg_color(indicators_[index], colors.primary, 0);
        lv_obj_set_style_bg_opa(indicators_[index], active ? LV_OPA_COVER : LV_OPA_TRANSP, 0);
    }
}

void NavBar::primary_cb(lv_event_t* event) {
    auto* view_model = static_cast<viewmodel::BaseViewModel*>(lv_event_get_user_data(event));
    if (!view_model) return;
    if (view_model->current_page() == model::AppPage::Overview) {
        view_model->request_quit();
    } else {
        view_model->show_overview_page();
    }
}

void NavBar::system_cb(lv_event_t* event) {
    auto* view_model = static_cast<viewmodel::BaseViewModel*>(lv_event_get_user_data(event));
    if (view_model) view_model->show_system_page();
}

void NavBar::refresh_cb(lv_event_t* event) {
    auto* view_model = static_cast<viewmodel::BaseViewModel*>(lv_event_get_user_data(event));
    if (view_model) view_model->refresh_data();
}

void NavBar::network_cb(lv_event_t* event) {
    auto* view_model = static_cast<viewmodel::BaseViewModel*>(lv_event_get_user_data(event));
    if (view_model) view_model->show_network_page();
}

void NavBar::theme_cb(lv_event_t* event) {
    auto* view_model = static_cast<viewmodel::BaseViewModel*>(lv_event_get_user_data(event));
    if (view_model) view_model->toggle_dark_mode();
}

void NavBar::state_observer_cb(lv_observer_t* observer, lv_subject_t*) {
    auto* nav = static_cast<NavBar*>(lv_observer_get_user_data(observer));
    if (nav) nav->update();
}

} // namespace view::widgets
