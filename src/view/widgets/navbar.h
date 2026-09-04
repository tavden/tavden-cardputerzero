/*
 * SPDX-FileCopyrightText: 2026 M5Stack Technology CO LTD
 * SPDX-FileCopyrightText: 2026 James Murphy
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "base_widget.h"
#include "base_viewmodel.h"

#include <array>

namespace app {
class AssetManager;
}

namespace view::widgets {

class NavBar final : public BaseWidgets {
public:
    NavBar(lv_obj_t* parent, viewmodel::BaseViewModel& view_model, app::AssetManager& assets);
    ~NavBar() override;

    void build() override;

    static void primary_cb(lv_event_t* event);
    static void system_cb(lv_event_t* event);
    static void refresh_cb(lv_event_t* event);
    static void network_cb(lv_event_t* event);
    static void theme_cb(lv_event_t* event);

private:
    void update();
    void style();

    static void state_observer_cb(lv_observer_t* observer, lv_subject_t* subject);

    viewmodel::BaseViewModel& view_model_;
    app::AssetManager& assets_;
    std::array<lv_obj_t*, 5> buttons_{};
    std::array<lv_obj_t*, 5> labels_{};
    std::array<lv_obj_t*, 5> indicators_{};
    lv_observer_t* page_observer_{nullptr};
    lv_observer_t* theme_observer_{nullptr};
};

} // namespace view::widgets
