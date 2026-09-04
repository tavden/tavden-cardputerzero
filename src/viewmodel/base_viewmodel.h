/*
 * SPDX-FileCopyrightText: 2026 M5Stack Technology CO LTD
 * SPDX-FileCopyrightText: 2026 James Murphy
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "base_model.h"
#include "subjects.h"

#include "lvgl.h"

namespace viewmodel {

class BaseViewModel {
public:
    BaseViewModel();
    ~BaseViewModel();

    BaseViewModel(const BaseViewModel&) = delete;
    BaseViewModel& operator=(const BaseViewModel&) = delete;

    lv_subject_t* title_subject();
    lv_subject_t* dark_mode_subject();
    lv_subject_t* current_page_subject();
    lv_subject_t* hostname_subject();
    lv_subject_t* os_subject();
    lv_subject_t* kernel_subject();
    lv_subject_t* architecture_subject();
    lv_subject_t* uptime_subject();
    lv_subject_t* load_subject();
    lv_subject_t* memory_subject();
    lv_subject_t* storage_subject();
    lv_subject_t* interface_subject();
    lv_subject_t* interface_type_subject();
    lv_subject_t* link_subject();
    lv_subject_t* address_subject();
    lv_subject_t* received_subject();
    lv_subject_t* transmitted_subject();
    lv_subject_t* captured_at_subject();
    lv_subject_t* refresh_count_subject();
    lv_subject_t* quit_requested_subject();

    bool is_dark_mode() const;
    void set_dark_mode(bool enabled);
    void toggle_dark_mode();

    model::AppPage current_page() const;
    void show_overview_page();
    void show_system_page();
    void show_network_page();
    void refresh_data();
    void request_quit();

private:
    void publish_navigation();

    model::BaseModel model_;
    reactive::StringSubject<32> title_subject_;
    reactive::BoolSubject dark_mode_subject_;
    reactive::IntSubject current_page_subject_;
    reactive::StringSubject<96> hostname_subject_;
    reactive::StringSubject<128> os_subject_;
    reactive::StringSubject<128> kernel_subject_;
    reactive::StringSubject<48> architecture_subject_;
    reactive::StringSubject<48> uptime_subject_;
    reactive::StringSubject<48> load_subject_;
    reactive::StringSubject<64> memory_subject_;
    reactive::StringSubject<64> storage_subject_;
    reactive::StringSubject<48> interface_subject_;
    reactive::StringSubject<48> interface_type_subject_;
    reactive::StringSubject<48> link_subject_;
    reactive::StringSubject<48> address_subject_;
    reactive::StringSubject<48> received_subject_;
    reactive::StringSubject<48> transmitted_subject_;
    reactive::StringSubject<48> captured_at_subject_;
    reactive::IntSubject refresh_count_subject_;
    reactive::BoolSubject quit_requested_subject_;
};

} // namespace viewmodel
