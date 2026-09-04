/*
 * SPDX-FileCopyrightText: 2026 James Murphy
 *
 * SPDX-License-Identifier: LicenseRef-Tavden-Proprietary
 */

#pragma once

#include "base_screen.h"

namespace screen {

class OverviewScreen final : public BaseScreen {
public:
    OverviewScreen(viewmodel::BaseViewModel& view_model, app::AssetManager& assets);

protected:
    void build_content(lv_obj_t* content) override;
};

} // namespace screen
