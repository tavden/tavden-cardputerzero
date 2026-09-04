/*
 * SPDX-FileCopyrightText: 2026 James Murphy
 *
 * SPDX-License-Identifier: LicenseRef-Tavden-Proprietary
 */

#pragma once

#include "base_screen.h"

namespace screen {

class SystemScreen final : public BaseScreen {
public:
    SystemScreen(viewmodel::BaseViewModel& view_model, app::AssetManager& assets);

protected:
    void build_content(lv_obj_t* content) override;
};

} // namespace screen
