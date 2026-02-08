#include "bstk/global.hpp"
#include "bstk/config.hpp"
#include <algorithm>

namespace bstk {

	Global::Global(Config& config) : config_(&config) {
		load_from_config();
	}

	void Global::load_from_config() {
		auto& p = props_;

		// Identity
		load_value("bst.bluestacks_account_id", p.identity.account_id);
		load_value("bst.guid", p.identity.guid);
		load_value("bst.machine_id", p.identity.machine_id);
		load_value("bst.launcher_guid", p.identity.launcher_guid);
		load_value("bst.install_id", p.identity.install_id);
		load_value("bst.version_machine_id", p.identity.version_machine_id);
		load_value("bst.country", p.identity.country);
		load_value("bst.locale", p.identity.locale);
		load_value("bst.install_date", p.identity.install_date);

		// System
		load_value("bst.system_ram", p.system.system_ram);
		load_value("bst.fresh_cpu_core", p.system.fresh_cpu_core);
		load_value("bst.fresh_cpu_ram", p.system.fresh_cpu_ram);
		load_value("bst.mem_opt_mode", p.system.mem_opt_mode);
		load_value("bst.mem_pcd_enabled", p.system.mem_pcd_enabled);
		load_value("bst.mem_pcd_pclimit", p.system.mem_pcd_pclimit);
		load_value("bst.mem_pcr_enabled", p.system.mem_pcr_enabled);
		load_value("bst.mem_pcr_pclimit", p.system.mem_pcr_pclimit);
		load_value("bst.mem_swap_enabled", p.system.mem_swap_enabled);
		load_value("bst.enable_mem_dedup", p.system.enable_mem_dedup);

		// Display
		load_value("bst.qt_renderer", p.display.qt_renderer);
		load_value("bst.ui_scale_factor", p.display.ui_scale_factor);
		load_value("bst.fullscreen_blurb_shown", p.display.fullscreen_blurb_shown);
		load_value("bst.custom_cursor_enabled", p.display.custom_cursor_enabled);
		load_value("bst.enable_esc_fullscreen", p.display.enable_esc_fullscreen);
		load_value("bst.enable_esc_mousecursor", p.display.enable_esc_mousecursor);
		load_value("bst.enable_statusbar", p.display.enable_statusbar);
		load_value("bst.enable_navigationbar", p.display.enable_navigationbar);
		load_value("bst.fixed_window_size", p.display.fixed_window_size);
		load_value("bst.key_controls_overlay_enabled", p.display.key_controls_overlay_enabled);
		load_value("bst.key_controls_overlay_opacity", p.display.key_controls_overlay_opacity);

		// Graphics
		load_value("bst.prefer_dedicated_gpu", p.graphics.prefer_dedicated_gpu);
		load_value("bst.force_raw_mode", p.graphics.force_raw_mode);
		load_value("bst.raw_incompatible_cpu", p.graphics.raw_incompatible_cpu);
		load_value("bst.status.hypervisor", p.graphics.hypervisor);
		load_value("bst.hyperv_elevate_required", p.graphics.hyperv_elevate_required);
		load_value("bst.force_hyperv_elevation", p.graphics.force_hyperv_elevation);

		// Input
		load_value("bst.enable_gamepad_detection", p.input.enable_gamepad_detection);
		load_value("bst.enable_gamepad_vibration", p.input.enable_gamepad_vibration);
		load_value("bst.enable_native_gamepad", p.input.enable_native_gamepad);
		load_value("bst.show_gamepad_detection_message", p.input.show_gamepad_detection_message);
		load_value("bst.show_camera_detection_message", p.input.show_camera_detection_message);
		load_value("bst.microphone_device", p.input.microphone_device);
		load_value("bst.speaker_device", p.input.speaker_device);

		// Network
		load_value("bst.enable_adb_access", p.network.enable_adb_access);
		load_value("bst.enable_adb_remote_access", p.network.enable_adb_remote_access);
		load_value("bst.dns_server", p.network.dns_server);
		load_value("bst.dns_server2", p.network.dns_server2);

		// Cloud
		load_value("bst.bluestacks_cdn_url", p.cloud.cdn_url);
		load_value("bst.bluestacks_cloud_url", p.cloud.cloud_url);
		load_value("bst.bluestacks_cloud_url2", p.cloud.cloud_url2);
		load_value("bst.bluestacks_eb_url", p.cloud.eb_url);
		load_value("bst.sso_host_env", p.cloud.sso_host_env);

		// Features
		load_value("bst.enable_discord_integration", p.features.enable_discord_integration);
		load_value("bst.enable_image_detection", p.features.enable_image_detection);
		load_value("bst.enable_programmatic_ads", p.features.enable_programmatic_ads);
		load_value("bst.launch_store_on_boot", p.features.launch_store_on_boot);
		load_value("bst.create_desktop_shortcuts", p.features.create_desktop_shortcuts);
		load_value("bst.enable_bsx_app_shortcuts", p.features.enable_bsx_app_shortcuts);
		load_value("bst.enable_sigin_gamelaunch", p.features.enable_sigin_gamelaunch);
		load_value("bst.show_charger_warning", p.features.show_charger_warning);
		load_value("bst.mute_all_instances", p.features.mute_all_instances);

		// Warnings
		load_value("bst.show_raw_mode_warning", p.warnings.show_raw_mode_warning);
		load_value("bst.show_macro_delete_warning", p.warnings.show_macro_delete_warning);
		load_value("bst.show_macro_folder_delete_warning", p.warnings.show_macro_folder_delete_warning);
		load_value("bst.show_schedule_macro_delete_warning", p.warnings.show_schedule_macro_delete_warning);
		load_value("bst.show_scheme_delete_warning", p.warnings.show_scheme_delete_warning);
		load_value("bst.do_not_show_link_account_popup", p.warnings.do_not_show_link_account_popup);
		load_value("bst.hyperv_api_error_popup_shown", p.warnings.hyperv_api_error_popup_shown);
		load_value("bst.crosshair_onboarding_popup_shown", p.warnings.crosshair_onboarding_popup_shown);
		load_value("bst.gamepad_editing_onboarding_done", p.warnings.gamepad_editing_onboarding_done);
		load_value("bst.stop_macro_on_home_blurb_shown", p.warnings.stop_macro_on_home_blurb_shown);

		// Media
		load_value("bst.media_folder", p.media.media_folder);
		load_value("bst.shared_folders", p.media.shared_folders);

		// Logging
		load_value("bst.log_levels", p.logging.log_levels);
		load_value("bst.enable_webengine_console_log", p.logging.enable_webengine_console_log);

		// Feature Flags
		load_value("bst.feature.ai_chat", p.feature_flags.ai_chat);
		load_value("bst.feature.app_install_stats", p.feature_flags.app_install_stats);
		load_value("bst.feature.auto_upload_nowgg_moments", p.feature_flags.auto_upload_nowgg_moments);
		load_value("bst.feature.bluestacksX", p.feature_flags.bluestacksX);
		load_value("bst.feature.creator_studio", p.feature_flags.creator_studio);
		load_value("bst.feature.macros", p.feature_flags.macros);
		load_value("bst.feature.nowbux", p.feature_flags.nowbux);
		load_value("bst.feature.nowgg_login_popup", p.feature_flags.nowgg_login_popup);
		load_value("bst.feature.popout_ai_chat", p.feature_flags.popout_ai_chat);
		load_value("bst.feature.programmatic_ads", p.feature_flags.programmatic_ads);
		load_value("bst.feature.quicklaunch", p.feature_flags.quicklaunch);
		load_value("bst.feature.rooting", p.feature_flags.rooting);
		load_value("bst.feature.show_cloud_instance", p.feature_flags.show_cloud_instance);
		load_value("bst.feature.show_moments", p.feature_flags.show_moments);
		load_value("bst.feature.show_programmatic_ads_preference", p.feature_flags.show_programmatic_ads_preference);
		load_value("bst.feature.show_quest_icon", p.feature_flags.show_quest_icon);
		load_value("bst.feature.skipNowggLogin", p.feature_flags.skipNowggLogin);
		load_value("bst.feature.usage_stats", p.feature_flags.usage_stats);
		load_value("bst.feature.live_stream", p.feature_flags.live_stream);
		load_value("bst.feature.ntp_server", p.feature_flags.ntp_server);
		load_value("bst.feature.discord_url", p.feature_flags.discord_url);

		// MIM
		load_value("bst.mim_win_height", p.mim.win_height);
		load_value("bst.mim_win_x", p.mim.win_x);
		load_value("bst.mim_win_y", p.mim.win_y);
		load_value("bst.mim_win_screen", p.mim.win_screen);
		load_value("bst.mim.max_fps", p.mim.max_fps);
		load_value("bst.mim.instances_per_row", p.mim.instances_per_row);
		load_value("bst.mim.instance_sort_option", p.mim.instance_sort_option);
		load_value("bst.mim.instance_arrangement_layout", p.mim.instance_arrangement_layout);
		load_value("bst.mim.batch_operation_interval", p.mim.batch_operation_interval);
		load_value("bst.mim.delete_folder_warning", p.mim.delete_folder_warning);
		load_value("bst.mim.delete_instance_in_folder_warning", p.mim.delete_instance_in_folder_warning);

		// Analytics
		load_value("bst.campaign_hash", p.analytics.campaign_hash);
		load_value("bst.campaign_name", p.analytics.campaign_name);
		load_value("bst.channel_handle", p.analytics.channel_handle);
		load_value("bst.exit_utm_campaign", p.analytics.exit_utm_campaign);

		// Launcher
		load_value("bst.launcher_version", p.launcher.launcher_version);
		load_value("bst.host_user_agent", p.launcher.host_user_agent);
	}

	void Global::save_to_config() {
		auto& p = props_;

		// Identity
		save_value("bst.bluestacks_account_id", p.identity.account_id);
		save_value("bst.country", p.identity.country);
		save_value("bst.locale", p.identity.locale);
		// Note: guid, machine_id, etc. are usually read-only

		// System
		save_value("bst.fresh_cpu_core", p.system.fresh_cpu_core);
		save_value("bst.fresh_cpu_ram", p.system.fresh_cpu_ram);
		save_value("bst.mem_opt_mode", p.system.mem_opt_mode);
		save_value("bst.mem_pcd_enabled", p.system.mem_pcd_enabled);
		save_value("bst.mem_pcd_pclimit", p.system.mem_pcd_pclimit);
		save_value("bst.mem_pcr_enabled", p.system.mem_pcr_enabled);
		save_value("bst.mem_pcr_pclimit", p.system.mem_pcr_pclimit);
		save_value("bst.mem_swap_enabled", p.system.mem_swap_enabled);
		save_value("bst.enable_mem_dedup", p.system.enable_mem_dedup);

		// Display
		save_value("bst.qt_renderer", p.display.qt_renderer);
		save_value("bst.ui_scale_factor", p.display.ui_scale_factor);
		save_value("bst.custom_cursor_enabled", p.display.custom_cursor_enabled);
		save_value("bst.enable_esc_fullscreen", p.display.enable_esc_fullscreen);
		save_value("bst.enable_esc_mousecursor", p.display.enable_esc_mousecursor);
		save_value("bst.enable_statusbar", p.display.enable_statusbar);
		save_value("bst.enable_navigationbar", p.display.enable_navigationbar);
		save_value("bst.fixed_window_size", p.display.fixed_window_size);
		save_value("bst.key_controls_overlay_enabled", p.display.key_controls_overlay_enabled);
		save_value("bst.key_controls_overlay_opacity", p.display.key_controls_overlay_opacity);

		// Graphics
		save_value("bst.prefer_dedicated_gpu", p.graphics.prefer_dedicated_gpu);
		save_value("bst.force_raw_mode", p.graphics.force_raw_mode);
		save_value("bst.status.hypervisor", p.graphics.hypervisor);
		save_value("bst.hyperv_elevate_required", p.graphics.hyperv_elevate_required);
		save_value("bst.force_hyperv_elevation", p.graphics.force_hyperv_elevation);

		// Input
		save_value("bst.enable_gamepad_detection", p.input.enable_gamepad_detection);
		save_value("bst.enable_gamepad_vibration", p.input.enable_gamepad_vibration);
		save_value("bst.enable_native_gamepad", p.input.enable_native_gamepad);
		save_value("bst.show_gamepad_detection_message", p.input.show_gamepad_detection_message);
		save_value("bst.show_camera_detection_message", p.input.show_camera_detection_message);
		save_value("bst.microphone_device", p.input.microphone_device);
		save_value("bst.speaker_device", p.input.speaker_device);

		// Network
		save_value("bst.enable_adb_access", p.network.enable_adb_access);
		save_value("bst.enable_adb_remote_access", p.network.enable_adb_remote_access);
		save_value("bst.dns_server", p.network.dns_server);
		save_value("bst.dns_server2", p.network.dns_server2);

		// Cloud
		save_value("bst.sso_host_env", p.cloud.sso_host_env);

		// Features
		save_value("bst.enable_discord_integration", p.features.enable_discord_integration);
		save_value("bst.enable_image_detection", p.features.enable_image_detection);
		save_value("bst.enable_programmatic_ads", p.features.enable_programmatic_ads);
		save_value("bst.launch_store_on_boot", p.features.launch_store_on_boot);
		save_value("bst.create_desktop_shortcuts", p.features.create_desktop_shortcuts);
		save_value("bst.enable_bsx_app_shortcuts", p.features.enable_bsx_app_shortcuts);
		save_value("bst.enable_sigin_gamelaunch", p.features.enable_sigin_gamelaunch);
		save_value("bst.show_charger_warning", p.features.show_charger_warning);
		save_value("bst.mute_all_instances", p.features.mute_all_instances);

		// Warnings
		save_value("bst.show_raw_mode_warning", p.warnings.show_raw_mode_warning);
		save_value("bst.show_macro_delete_warning", p.warnings.show_macro_delete_warning);
		save_value("bst.show_macro_folder_delete_warning", p.warnings.show_macro_folder_delete_warning);
		save_value("bst.show_schedule_macro_delete_warning", p.warnings.show_schedule_macro_delete_warning);
		save_value("bst.show_scheme_delete_warning", p.warnings.show_scheme_delete_warning);
		save_value("bst.do_not_show_link_account_popup", p.warnings.do_not_show_link_account_popup);

		// Media
		save_value("bst.media_folder", p.media.media_folder);
		save_value("bst.shared_folders", p.media.shared_folders);

		// Logging
		save_value("bst.log_levels", p.logging.log_levels);
		save_value("bst.enable_webengine_console_log", p.logging.enable_webengine_console_log);

		// Feature Flags
		save_value("bst.feature.ai_chat", p.feature_flags.ai_chat);
		save_value("bst.feature.app_install_stats", p.feature_flags.app_install_stats);
		save_value("bst.feature.auto_upload_nowgg_moments", p.feature_flags.auto_upload_nowgg_moments);
		save_value("bst.feature.bluestacksX", p.feature_flags.bluestacksX);
		save_value("bst.feature.creator_studio", p.feature_flags.creator_studio);
		save_value("bst.feature.macros", p.feature_flags.macros);
		save_value("bst.feature.nowbux", p.feature_flags.nowbux);
		save_value("bst.feature.nowgg_login_popup", p.feature_flags.nowgg_login_popup);
		save_value("bst.feature.popout_ai_chat", p.feature_flags.popout_ai_chat);
		save_value("bst.feature.programmatic_ads", p.feature_flags.programmatic_ads);
		save_value("bst.feature.quicklaunch", p.feature_flags.quicklaunch);
		save_value("bst.feature.rooting", p.feature_flags.rooting);
		save_value("bst.feature.show_cloud_instance", p.feature_flags.show_cloud_instance);
		save_value("bst.feature.show_moments", p.feature_flags.show_moments);
		save_value("bst.feature.show_programmatic_ads_preference", p.feature_flags.show_programmatic_ads_preference);
		save_value("bst.feature.show_quest_icon", p.feature_flags.show_quest_icon);
		save_value("bst.feature.skipNowggLogin", p.feature_flags.skipNowggLogin);
		save_value("bst.feature.usage_stats", p.feature_flags.usage_stats);
		save_value("bst.feature.live_stream", p.feature_flags.live_stream);
		save_value("bst.feature.ntp_server", p.feature_flags.ntp_server);

		// MIM
		save_value("bst.mim_win_height", p.mim.win_height);
		save_value("bst.mim_win_x", p.mim.win_x);
		save_value("bst.mim_win_y", p.mim.win_y);
		save_value("bst.mim_win_screen", p.mim.win_screen);
		save_value("bst.mim.max_fps", p.mim.max_fps);
		save_value("bst.mim.instances_per_row", p.mim.instances_per_row);
		save_value("bst.mim.instance_sort_option", p.mim.instance_sort_option);
		save_value("bst.mim.instance_arrangement_layout", p.mim.instance_arrangement_layout);
		save_value("bst.mim.batch_operation_interval", p.mim.batch_operation_interval);
		save_value("bst.mim.delete_folder_warning", p.mim.delete_folder_warning);
		save_value("bst.mim.delete_instance_in_folder_warning", p.mim.delete_instance_in_folder_warning);
	}

	Value Global::get(std::string_view key) const {
		std::string full = full_key(key);
		if (auto val = config_->get(full)) {
			return *val;
		}
		return Value{};
	}

	void Global::set(std::string_view key, const Value& value) {
		config_->set(full_key(key), value);
	}

	void Global::set(std::string_view key, Value&& value) {
		config_->set(full_key(key), std::move(value));
	}

	bool Global::has(std::string_view key) const {
		return config_->has(full_key(key));
	}

	bool Global::remove(std::string_view key) {
		return config_->remove(full_key(key));
	}

	std::vector<std::string> Global::keys() const {
		std::vector<std::string> result;
		for (const auto& [k, v] : *config_) {
			if (!is_instance_key(k)) {
				result.push_back(k);
			}
		}
		return result;
	}

	std::vector<std::string> Global::keys_with_prefix(std::string_view prefix) const {
		auto all = config_->get_keys_with_prefix(prefix);
		std::vector<std::string> result;
		for (const auto& k : all) {
			if (!is_instance_key(k)) {
				result.push_back(k);
			}
		}
		return result;
	}

	bool Global::is_instance_key(std::string_view key) {
		return key.size() > 14 && key.substr(0, 14) == "bst.instance.";
	}

	std::string Global::full_key(std::string_view key) const {
		// If key already starts with bst., use as-is, otherwise prepend bst.
		if (key.size() > 4 && key.substr(0, 4) == "bst.") {
			return std::string(key);
		}
		return "bst." + std::string(key);
	}

	template<typename T>
	void Global::load_value(std::string_view key, T& target, std::string_view category) {
		if (auto val = config_->get(std::string(key))) {
			if constexpr (std::is_same_v<T, std::string>) {
				target = val->as_string();
			}
			else if constexpr (std::is_same_v<T, bool>) {
				target = val->as_bool();
			}
			else if constexpr (std::is_integral_v<T>) {
				target = static_cast<T>(val->as_int());
			}
			else if constexpr (std::is_floating_point_v<T>) {
				target = static_cast<T>(val->as_double());
			}
		}
	}

	template<typename T>
	void Global::save_value(std::string_view key, const T& source) {
		if constexpr (std::is_same_v<T, std::string>) {
			config_->set_string(std::string(key), source);
		}
		else if constexpr (std::is_same_v<T, bool>) {
			config_->set_bool(std::string(key), source);
		}
		else if constexpr (std::is_integral_v<T>) {
			config_->set_int(std::string(key), static_cast<int64_t>(source));
		}
		else if constexpr (std::is_floating_point_v<T>) {
			config_->set_double(std::string(key), static_cast<double>(source));
		}
	}

	// Explicit instantiations
	template void Global::load_value<std::string>(std::string_view, std::string&, std::string_view);
	template void Global::load_value<bool>(std::string_view, bool&, std::string_view);
	template void Global::load_value<int>(std::string_view, int&, std::string_view);
	template void Global::load_value<int64_t>(std::string_view, int64_t&, std::string_view);
	template void Global::load_value<double>(std::string_view, double&, std::string_view);

	template void Global::save_value<std::string>(std::string_view, const std::string&);
	template void Global::save_value<bool>(std::string_view, const bool&);
	template void Global::save_value<int>(std::string_view, const int&);
	template void Global::save_value<int64_t>(std::string_view, const int64_t&);
	template void Global::save_value<double>(std::string_view, const double&);

} // namespace bstk