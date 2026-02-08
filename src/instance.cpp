#include "bstk/instance.hpp"
#include "bstk/config.hpp"

namespace bstk {

	Instance::Instance(Config& config, std::string name)
		: config_(&config), name_(std::move(name)) {
		load_from_config();
	}

	void Instance::load_from_config() {
		auto& p = props_;
		std::string prefix = key_prefix();

		// Display
		load_value("display_name", p.display_name);
		load_value("fb_width", p.fb_width);
		load_value("fb_height", p.fb_height);
		load_value("dpi", p.dpi);
		load_value("max_fps", p.max_fps);
		load_value("enable_high_fps", p.enable_high_fps);
		load_value("enable_vsync", p.enable_vsync);
		load_value("enable_fullscreen_all_apps", p.enable_fullscreen_all_apps);

		// Performance
		load_value("cpus", p.cpus);
		load_value("ram", p.ram);
		load_value("graphics_engine", p.graphics_engine);
		load_value("graphics_renderer", p.graphics_renderer);
		load_value("enable_fps_display", p.enable_fps_display);
		load_value("eco_mode_max_fps", p.eco_mode_max_fps);

		// Features
		load_value("enable_root_access", p.enable_root_access);
		load_value("enable_notifications", p.enable_notifications);
		load_value("game_controls_enabled", p.game_controls_enabled);
		load_value("show_sidebar", p.show_sidebar);
		load_value("pin_to_top", p.pin_to_top);

		// Network
		load_value("adb_port", p.adb_port);
		load_value("dns_server", p.dns_server);
		load_value("airplane_mode_active", p.airplane_mode_active);

		// Device
		load_value("device_profile_code", p.device_profile_code);
		load_value("device_carrier_code", p.device_carrier_code);
		load_value("device_country_code", p.device_country_code);

		// Storage/Graphics
		load_value("abi_list", p.abi_list);
		load_value("vulkan_supported", p.vulkan_supported);
		load_value("astc_decoding_mode", p.astc_decoding_mode);

		// Audio
		load_value("android_sound_while_tapping", p.android_sound_while_tapping);

		// Identity
		load_value("android_id", p.android_id);
		load_value("android_google_ad_id", p.android_google_ad_id);
		load_value("google_account_logins", p.google_account_logins);
	}

	void Instance::save_to_config() {
		const auto& p = props_;
		std::string prefix = key_prefix();

		// Display
		save_value("display_name", p.display_name);
		save_value("fb_width", p.fb_width);
		save_value("fb_height", p.fb_height);
		save_value("dpi", p.dpi);
		save_value("max_fps", p.max_fps);
		save_value("enable_high_fps", p.enable_high_fps);
		save_value("enable_vsync", p.enable_vsync);
		save_value("enable_fullscreen_all_apps", p.enable_fullscreen_all_apps);

		// Performance
		save_value("cpus", p.cpus);
		save_value("ram", p.ram);
		save_value("graphics_engine", p.graphics_engine);
		save_value("graphics_renderer", p.graphics_renderer);
		save_value("enable_fps_display", p.enable_fps_display);
		save_value("eco_mode_max_fps", p.eco_mode_max_fps);

		// Features
		save_value("enable_root_access", p.enable_root_access);
		save_value("enable_notifications", p.enable_notifications);
		save_value("game_controls_enabled", p.game_controls_enabled);
		save_value("show_sidebar", p.show_sidebar);
		save_value("pin_to_top", p.pin_to_top);

		// Network
		save_value("adb_port", p.adb_port);
		save_value("dns_server", p.dns_server);
		save_value("airplane_mode_active", p.airplane_mode_active);

		// Device
		save_value("device_profile_code", p.device_profile_code);
		save_value("device_carrier_code", p.device_carrier_code);
		save_value("device_country_code", p.device_country_code);

		// Storage/Graphics
		save_value("abi_list", p.abi_list);
		save_value("vulkan_supported", p.vulkan_supported);
		save_value("astc_decoding_mode", p.astc_decoding_mode);

		// Audio
		save_value("android_sound_while_tapping", p.android_sound_while_tapping);

		// Identity
		save_value("android_id", p.google_account_logins);
		save_value("android_google_ad_id", p.android_google_ad_id);
		save_value("google_account_logins", p.google_account_logins);
	}

	Value Instance::get(std::string_view key) const {
		if (auto val = config_->get(full_key(key))) {
			return *val;
		}
		return Value{};
	}

	void Instance::set(std::string_view key, const Value& value) {
		config_->set(full_key(key), value);
	}

	void Instance::set(std::string_view key, Value&& value) {
		config_->set(full_key(key), std::move(value));
	}

	bool Instance::has(std::string_view key) const {
		return config_->has(full_key(key));
	}

	bool Instance::remove(std::string_view key) {
		return config_->remove(full_key(key));
	}

	std::vector<std::string> Instance::keys() const {
		auto all_keys = config_->get_keys_with_prefix(key_prefix());
		std::string prefix = key_prefix();

		// Strip prefix
		std::vector<std::string> result;
		result.reserve(all_keys.size());
		for (auto& k : all_keys) {
			if (k.size() > prefix.size()) {
				result.push_back(k.substr(prefix.size()));
			}
		}
		return result;
	}

	Value Instance::get_raw(std::string_view key) const {
		return get(key);
	}

	void Instance::commit() {
		save_to_config();
	}

	std::string Instance::full_key(std::string_view key) const {
		return key_prefix() + std::string(key);
	}

	template<typename T>
	void Instance::load_value(std::string_view key, T& target) {
		if (auto val = config_->get(full_key(key))) {
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
	void Instance::save_value(std::string_view key, const T& source) {
		if constexpr (std::is_same_v<T, std::string>) {
			config_->set_string(full_key(key), source);
		}
		else if constexpr (std::is_same_v<T, bool>) {
			config_->set_bool(full_key(key), source);
		}
		else if constexpr (std::is_integral_v<T>) {
			config_->set_int(full_key(key), static_cast<int64_t>(source));
		}
		else if constexpr (std::is_floating_point_v<T>) {
			config_->set_double(full_key(key), static_cast<double>(source));
		}
	}

	// Explicit instantiations
	template void Instance::load_value<std::string>(std::string_view, std::string&);
	template void Instance::load_value<bool>(std::string_view, bool&);
	template void Instance::load_value<int>(std::string_view, int&);
	template void Instance::load_value<int64_t>(std::string_view, int64_t&);

	template void Instance::save_value<std::string>(std::string_view, const std::string&);
	template void Instance::save_value<bool>(std::string_view, const bool&);
	template void Instance::save_value<int>(std::string_view, const int&);
	template void Instance::save_value<int64_t>(std::string_view, const int64_t&);

} // namespace bstk