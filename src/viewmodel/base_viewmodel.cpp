/*
 * SPDX-FileCopyrightText: 2026 M5Stack Technology CO LTD
 * SPDX-FileCopyrightText: 2026 James Murphy
 *
 * SPDX-License-Identifier: MIT
 */

#include "base_viewmodel.h"

#include "system_info.h"

#include <cstdlib>
#include <string>

namespace viewmodel {
namespace {

int page_to_int(model::AppPage page) {
    return static_cast<int>(page);
}

bool demo_mode_enabled() {
    const char* value = std::getenv("TAVDEN_DEMO_MODE");
    return value && (std::string(value) == "1" || std::string(value) == "true" ||
                     std::string(value) == "yes");
}

} // namespace

BaseViewModel::BaseViewModel()
    : title_subject_(model_.app_title()),
      dark_mode_subject_(model_.dark_mode()),
      current_page_subject_(page_to_int(model_.current_page())),
      hostname_subject_("Loading"),
      os_subject_("Loading"),
      kernel_subject_("Loading"),
      architecture_subject_("Loading"),
      uptime_subject_("Loading"),
      load_subject_("Loading"),
      memory_subject_("Loading"),
      storage_subject_("Loading"),
      interface_subject_("Loading"),
      interface_type_subject_("Loading"),
      link_subject_("Loading"),
      address_subject_("Loading"),
      received_subject_("Loading"),
      transmitted_subject_("Loading"),
      captured_at_subject_("Loading"),
      refresh_count_subject_(0),
      quit_requested_subject_(false) {
    refresh_data();
}

BaseViewModel::~BaseViewModel() = default;

lv_subject_t* BaseViewModel::title_subject() { return title_subject_.native(); }
lv_subject_t* BaseViewModel::dark_mode_subject() { return dark_mode_subject_.native(); }
lv_subject_t* BaseViewModel::current_page_subject() { return current_page_subject_.native(); }
lv_subject_t* BaseViewModel::hostname_subject() { return hostname_subject_.native(); }
lv_subject_t* BaseViewModel::os_subject() { return os_subject_.native(); }
lv_subject_t* BaseViewModel::kernel_subject() { return kernel_subject_.native(); }
lv_subject_t* BaseViewModel::architecture_subject() { return architecture_subject_.native(); }
lv_subject_t* BaseViewModel::uptime_subject() { return uptime_subject_.native(); }
lv_subject_t* BaseViewModel::load_subject() { return load_subject_.native(); }
lv_subject_t* BaseViewModel::memory_subject() { return memory_subject_.native(); }
lv_subject_t* BaseViewModel::storage_subject() { return storage_subject_.native(); }
lv_subject_t* BaseViewModel::interface_subject() { return interface_subject_.native(); }
lv_subject_t* BaseViewModel::interface_type_subject() { return interface_type_subject_.native(); }
lv_subject_t* BaseViewModel::link_subject() { return link_subject_.native(); }
lv_subject_t* BaseViewModel::address_subject() { return address_subject_.native(); }
lv_subject_t* BaseViewModel::received_subject() { return received_subject_.native(); }
lv_subject_t* BaseViewModel::transmitted_subject() { return transmitted_subject_.native(); }
lv_subject_t* BaseViewModel::captured_at_subject() { return captured_at_subject_.native(); }
lv_subject_t* BaseViewModel::refresh_count_subject() { return refresh_count_subject_.native(); }
lv_subject_t* BaseViewModel::quit_requested_subject() { return quit_requested_subject_.native(); }

bool BaseViewModel::is_dark_mode() const { return model_.dark_mode(); }

void BaseViewModel::set_dark_mode(bool enabled) {
    model_.set_dark_mode(enabled);
    publish_navigation();
}

void BaseViewModel::toggle_dark_mode() {
    model_.toggle_dark_mode();
    publish_navigation();
}

model::AppPage BaseViewModel::current_page() const { return model_.current_page(); }

void BaseViewModel::show_overview_page() {
    model_.set_current_page(model::AppPage::Overview);
    publish_navigation();
}

void BaseViewModel::show_system_page() {
    model_.set_current_page(model::AppPage::System);
    publish_navigation();
}

void BaseViewModel::show_network_page() {
    model_.set_current_page(model::AppPage::Network);
    publish_navigation();
}

void BaseViewModel::refresh_data() {
    const auto snapshot = demo_mode_enabled() ? system_info::demo() : system_info::capture();
    hostname_subject_.set(snapshot.hostname.c_str());
    os_subject_.set(snapshot.os_name.c_str());
    kernel_subject_.set(snapshot.kernel.c_str());
    architecture_subject_.set(snapshot.architecture.c_str());
    uptime_subject_.set(snapshot.uptime.c_str());
    load_subject_.set(snapshot.load.c_str());
    memory_subject_.set(snapshot.memory.c_str());
    storage_subject_.set(snapshot.storage.c_str());
    interface_subject_.set(snapshot.interface_name.c_str());
    interface_type_subject_.set(snapshot.interface_type.c_str());
    link_subject_.set(snapshot.link_state.c_str());
    address_subject_.set(snapshot.ipv4_address.c_str());
    received_subject_.set(snapshot.received.c_str());
    transmitted_subject_.set(snapshot.transmitted.c_str());
    captured_at_subject_.set(snapshot.captured_at.c_str());
    refresh_count_subject_.set(refresh_count_subject_.value() + 1);
}

void BaseViewModel::request_quit() {
    quit_requested_subject_.set(true);
}

void BaseViewModel::publish_navigation() {
    title_subject_.set(model_.app_title());
    dark_mode_subject_.set(model_.dark_mode());
    current_page_subject_.set(page_to_int(model_.current_page()));
}

} // namespace viewmodel
