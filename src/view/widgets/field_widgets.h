/*
 * SPDX-FileCopyrightText: 2026 James Murphy
 *
 * SPDX-License-Identifier: LicenseRef-Tavden-Proprietary
 */

#pragma once

#include "lvgl.h"

namespace app {
class AssetManager;
}

namespace viewmodel {
class BaseViewModel;
}

namespace view::widgets {

lv_obj_t* create_panel(lv_obj_t* parent,
                       viewmodel::BaseViewModel& view_model,
                       int32_t width,
                       int32_t height);

lv_obj_t* create_label(lv_obj_t* parent,
                       viewmodel::BaseViewModel& view_model,
                       app::AssetManager& assets,
                       const char* text,
                       int32_t size,
                       bool bold,
                       bool accent = false,
                       bool muted = false);

lv_obj_t* create_bound_label(lv_obj_t* parent,
                             viewmodel::BaseViewModel& view_model,
                             app::AssetManager& assets,
                             lv_subject_t* subject,
                             int32_t size,
                             bool bold,
                             int32_t width);

lv_obj_t* create_metric(lv_obj_t* parent,
                        viewmodel::BaseViewModel& view_model,
                        app::AssetManager& assets,
                        const char* caption,
                        lv_subject_t* value,
                        int32_t width);

} // namespace view::widgets
