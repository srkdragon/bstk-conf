#ifndef BSTK_GLOBAL_HPP
#define BSTK_GLOBAL_HPP

#include "value.hpp"
#include <string>
#include <string_view>
#include <vector>
#include <functional>
#include <iostream>

namespace bstk {

	// Forward declaration
	class Config;

	class Global {
	public:
		// Structured properties for easy access and IDE autocomplete
		struct Properties {
			// Application Identity
			struct {
				std::string account_id;                    // bst.bluestacks_account_id
				std::string guid;                          // bst.guid
				std::string machine_id;                    // bst.machine_id
				std::string launcher_guid;                 // bst.launcher_guid
				std::string install_id;                    // bst.install_id
				std::string version_machine_id;            // bst.version_machine_id
				std::string country;                       // bst.country
				std::string locale;                        // bst.locale
				std::string install_date;                  // bst.install_date
			} identity;

			// System Resources
			struct {
				int64_t system_ram = 0;                    // bst.system_ram (MB)
				int fresh_cpu_core = 4;                    // bst.fresh_cpu_core
				int fresh_cpu_ram = 4096;                  // bst.fresh_cpu_ram (MB)
				int mem_opt_mode = 0;                      // bst.mem_opt_mode
				bool mem_pcd_enabled = false;              // bst.mem_pcd_enabled
				int mem_pcd_pclimit = 40;                  // bst.mem_pcd_pclimit
				bool mem_pcr_enabled = true;               // bst.mem_pcr_enabled
				int mem_pcr_pclimit = 48;                  // bst.mem_pcr_pclimit
				bool mem_swap_enabled = false;             // bst.mem_swap_enabled
				bool enable_mem_dedup = true;              // bst.enable_mem_dedup
			} system;

			// Display & UI
			struct {
				std::string qt_renderer = "Auto";          // bst.qt_renderer
				double ui_scale_factor = 1.0;              // bst.ui_scale_factor
				bool fullscreen_blurb_shown = false;       // bst.fullscreen_blurb_shown
				bool custom_cursor_enabled = true;         // bst.custom_cursor_enabled
				bool enable_esc_fullscreen = true;         // bst.enable_esc_fullscreen
				bool enable_esc_mousecursor = true;        // bst.enable_esc_mousecursor
				bool enable_statusbar = true;              // bst.enable_statusbar
				bool enable_navigationbar = false;         // bst.enable_navigationbar
				bool fixed_window_size = false;            // bst.fixed_window_size
				bool key_controls_overlay_enabled = true;  // bst.key_controls_overlay_enabled
				int key_controls_overlay_opacity = 50;     // bst.key_controls_overlay_opacity
			} display;

			// Graphics & Performance
			struct {
				bool prefer_dedicated_gpu = true;          // bst.prefer_dedicated_gpu
				bool force_raw_mode = false;               // bst.force_raw_mode
				bool raw_incompatible_cpu = false;         // bst.raw_incompatible_cpu
				std::string hypervisor = "vbox";           // bst.status.hypervisor
				bool hyperv_elevate_required = false;      // bst.hyperv_elevate_required
				bool force_hyperv_elevation = false;       // bst.force_hyperv_elevation
			} graphics;

			// Input Devices
			struct {
				bool enable_gamepad_detection = true;      // bst.enable_gamepad_detection
				bool enable_gamepad_vibration = true;      // bst.enable_gamepad_vibration
				bool enable_native_gamepad = true;         // bst.enable_native_gamepad (2=true)
				bool show_gamepad_detection_message = true;// bst.show_gamepad_detection_message
				bool show_camera_detection_message = true; // bst.show_camera_detection_message
				std::string microphone_device;             // bst.microphone_device
				std::string speaker_device;                // bst.speaker_device
			} input;

			// Network & ADB
			struct {
				bool enable_adb_access = true;             // bst.enable_adb_access
				bool enable_adb_remote_access = false;     // bst.enable_adb_remote_access
				std::string dns_server = "8.8.8.8";        // bst.dns_server
				std::string dns_server2 = "10.0.2.3";      // bst.dns_server2
			} network;

			// Cloud & Services
			struct {
				std::string cdn_url;                       // bst.bluestacks_cdn_url
				std::string cloud_url;                     // bst.bluestacks_cloud_url
				std::string cloud_url2;                    // bst.bluestacks_cloud_url2
				std::string eb_url;                        // bst.bluestacks_eb_url
				std::string sso_host_env = "prod";         // bst.sso_host_env
			} cloud;

			// Features & Integrations
			struct {
				bool enable_discord_integration = true;    // bst.enable_discord_integration
				bool enable_image_detection = true;        // bst.enable_image_detection
				bool enable_programmatic_ads = true;       // bst.enable_programmatic_ads
				bool launch_store_on_boot = true;          // bst.launch_store_on_boot
				bool create_desktop_shortcuts = true;      // bst.create_desktop_shortcuts
				bool enable_bsx_app_shortcuts = false;     // bst.enable_bsx_app_shortcuts
				bool enable_sigin_gamelaunch = true;       // bst.enable_sigin_gamelaunch
				bool show_charger_warning = true;          // bst.show_charger_warning
				bool mute_all_instances = false;           // bst.mute_all_instances
			} features;

			// Warnings & Popups
			struct {
				bool show_raw_mode_warning = true;         // bst.show_raw_mode_warning
				bool show_macro_delete_warning = true;     // bst.show_macro_delete_warning
				bool show_macro_folder_delete_warning = true;// bst.show_macro_folder_delete_warning
				bool show_schedule_macro_delete_warning = true;// bst.show_schedule_macro_delete_warning
				bool show_scheme_delete_warning = true;    // bst.show_scheme_delete_warning
				bool do_not_show_link_account_popup = false;// bst.do_not_show_link_account_popup
				bool hyperv_api_error_popup_shown = false; // bst.hyperv_api_error_popup_shown
				bool crosshair_onboarding_popup_shown = false;// bst.crosshair_onboarding_popup_shown
				bool gamepad_editing_onboarding_done = false;// bst.gamepad_editing_onboarding_done
				bool stop_macro_on_home_blurb_shown = false;// bst.stop_macro_on_home_blurb_shown
			} warnings;

			// Media & Shared Folders
			struct {
				std::string media_folder;                  // bst.media_folder
				std::string shared_folders;                // bst.shared_folders
			} media;

			// Logging & Debug
			struct {
				std::string log_levels = "*:I";            // bst.log_levels
				bool enable_webengine_console_log = false; // bst.enable_webengine_console_log
				bool enable_logcat_redirection = false;    // bst.enable_logcat_redirection (instance)
			} logging;

			// Feature Flags
			struct {
				bool ai_chat = false;                      // bst.feature.ai_chat
				bool app_install_stats = true;             // bst.feature.app_install_stats
				bool auto_upload_nowgg_moments = true;     // bst.feature.auto_upload_nowgg_moments
				bool bluestacksX = true;                   // bst.feature.bluestacksX
				bool creator_studio = false;               // bst.feature.creator_studio
				bool macros = true;                        // bst.feature.macros
				bool nowbux = true;                        // bst.feature.nowbux
				bool nowgg_login_popup = true;             // bst.feature.nowgg_login_popup
				bool popout_ai_chat = false;               // bst.feature.popout_ai_chat
				bool programmatic_ads = true;              // bst.feature.programmatic_ads
				bool quicklaunch = false;                  // bst.feature.quicklaunch
				bool rooting = false;                      // bst.feature.rooting
				bool show_cloud_instance = true;           // bst.feature.show_cloud_instance
				bool show_moments = true;                  // bst.feature.show_moments
				bool show_programmatic_ads_preference = true;// bst.feature.show_programmatic_ads_preference
				bool show_quest_icon = false;              // bst.feature.show_quest_icon
				bool skipNowggLogin = true;                // bst.feature.skipNowggLogin
				bool usage_stats = true;                   // bst.feature.usage_stats
				bool live_stream = false;                  // bst.feature.live_stream
				std::string ntp_server = "time.nist.gov";  // bst.feature.ntp_server
				std::string discord_url;                   // bst.feature.discord_url
			} feature_flags;

			// Multi-Instance Manager (MIM)
			struct {
				int win_height = 512;                      // bst.mim_win_height
				int win_x = 0;                             // bst.mim_win_x
				int win_y = 0;                             // bst.mim_win_y
				std::string win_screen;                    // bst.mim_win_screen
				int max_fps = 60;                          // bst.mim.max_fps
				int instances_per_row = 2;                 // bst.mim.instances_per_row
				std::string instance_sort_option = "name"; // bst.mim.instance_sort_option
				std::string instance_arrangement_layout = "grid";// bst.mim.instance_arrangement_layout
				int batch_operation_interval = 2000;       // bst.mim.batch_operation_interval
				bool delete_folder_warning = true;         // bst.mim.delete_folder_warning
				bool delete_instance_in_folder_warning = true;// bst.mim.delete_instance_in_folder_warning
			} mim;

			// Campaign & Analytics (read-only mostly)
			struct {
				std::string campaign_hash;                 // bst.campaign_hash
				std::string campaign_name;                 // bst.campaign_name
				std::string channel_handle;                // bst.channel_handle
				std::string exit_utm_campaign;             // bst.exit_utm_campaign
			} analytics;

			// Launcher Info
			struct {
				std::string launcher_version;              // bst.launcher_version
				std::string host_user_agent;               // bst.host_user_agent
			} launcher;
		};

		// Constructor
		explicit Global(Config& config);

		// Load/Save
		void load_from_config();
		void save_to_config();

		// Property access
		[[nodiscard]] Properties& props() noexcept { return props_; }
		[[nodiscard]] const Properties& props() const noexcept { return props_; }

		// ============================================
		// FLUENT INTERFACE - Identity
		// ============================================
		Global& account_id(std::string val) { props_.identity.account_id = std::move(val); return *this; }
		Global& country(std::string val) { props_.identity.country = std::move(val); return *this; }
		Global& locale(std::string val) { props_.identity.locale = std::move(val); return *this; }

		// ============================================
		// FLUENT INTERFACE - System Resources
		// ============================================
		Global& fresh_cpu(int cores, int ram_mb) {
			props_.system.fresh_cpu_core = cores;
			props_.system.fresh_cpu_ram = ram_mb;
			return *this;
		}
		Global& memory_optimization(int mode) { props_.system.mem_opt_mode = mode; return *this; }
		Global& enable_swap(bool enable) { props_.system.mem_swap_enabled = enable; return *this; }
		Global& enable_mem_dedup(bool enable) { props_.system.enable_mem_dedup = enable; return *this; }

		// ============================================
		// FLUENT INTERFACE - Display
		// ============================================
		Global& ui_scale(double factor) { props_.display.ui_scale_factor = factor; return *this; }
		Global& qt_renderer(std::string renderer) { props_.display.qt_renderer = std::move(renderer); return *this; }
		Global& show_statusbar(bool show) { props_.display.enable_statusbar = show; return *this; }
		Global& show_navigationbar(bool show) { props_.display.enable_navigationbar = show; return *this; }
		Global& overlay_opacity(int percent) { props_.display.key_controls_overlay_opacity = percent; return *this; }

		// ============================================
		// FLUENT INTERFACE - Graphics
		// ============================================
		Global& prefer_dedicated_gpu(bool prefer) { props_.graphics.prefer_dedicated_gpu = prefer; return *this; }
		Global& hypervisor(std::string type) { props_.graphics.hypervisor = std::move(type); return *this; }
		Global& force_raw_mode(bool force) { props_.graphics.force_raw_mode = force; return *this; }

		// ============================================
		// FLUENT INTERFACE - Input
		// ============================================
		Global& gamepad_detection(bool enable) { props_.input.enable_gamepad_detection = enable; return *this; }
		Global& gamepad_vibration(bool enable) { props_.input.enable_gamepad_vibration = enable; return *this; }
		Global& native_gamepad(bool enable) { props_.input.enable_native_gamepad = enable; return *this; }

		// ============================================
		// FLUENT INTERFACE - Network
		// ============================================
		Global& adb_access(bool enable) { props_.network.enable_adb_access = enable; return *this; }
		Global& adb_remote_access(bool enable) { props_.network.enable_adb_remote_access = enable; return *this; }
		Global& dns_primary(std::string dns) { props_.network.dns_server = std::move(dns); return *this; }
		Global& dns_secondary(std::string dns) { props_.network.dns_server2 = std::move(dns); return *this; }

		// ============================================
		// FLUENT INTERFACE - Features
		// ============================================
		Global& discord_integration(bool enable) { props_.features.enable_discord_integration = enable; return *this; }
		Global& image_detection(bool enable) { props_.features.enable_image_detection = enable; return *this; }
		Global& programmatic_ads(bool enable) { props_.features.enable_programmatic_ads = enable; return *this; }
		Global& launch_store_on_boot(bool enable) { props_.features.launch_store_on_boot = enable; return *this; }
		Global& desktop_shortcuts(bool enable) { props_.features.create_desktop_shortcuts = enable; return *this; }

		// ============================================
		// FLUENT INTERFACE - MIM
		// ============================================
		Global& mim_framerate(int fps) { props_.mim.max_fps = fps; return *this; }
		Global& mim_grid(int instances_per_row) { props_.mim.instances_per_row = instances_per_row; return *this; }
		Global& mim_layout(std::string layout) { props_.mim.instance_arrangement_layout = std::move(layout); return *this; }

		// ============================================
		// FLUENT INTERFACE - Feature Flags
		// ============================================
		Global& enable_macros(bool enable) { props_.feature_flags.macros = enable; return *this; }
		Global& enable_rooting(bool enable) { props_.feature_flags.rooting = enable; return *this; }
		Global& enable_ai_chat(bool enable) { props_.feature_flags.ai_chat = enable; return *this; }
		Global& enable_live_stream(bool enable) { props_.feature_flags.live_stream = enable; return *this; }
		Global& enable_nowbux(bool enable) { props_.feature_flags.nowbux = enable; return *this; }
		Global& skip_nowgg_login(bool skip) { props_.feature_flags.skipNowggLogin = skip; return *this; }

		// Generic access for any global key
		[[nodiscard]] Value get(std::string_view key) const;
		void set(std::string_view key, const Value& value);
		void set(std::string_view key, Value&& value);
		[[nodiscard]] bool has(std::string_view key) const;
		bool remove(std::string_view key);

		// Get all global keys (non-instance keys)
		[[nodiscard]] std::vector<std::string> keys() const;
		[[nodiscard]] std::vector<std::string> keys_with_prefix(std::string_view prefix) const;

		// Commit changes immediately
		void commit() { save_to_config(); }

		// Check if key is an instance key (helper)
		[[nodiscard]] static bool is_instance_key(std::string_view key);

	private:
		Config* config_;
		Properties props_;

		[[nodiscard]] std::string full_key(std::string_view key) const;
		void load_value(std::string_view key, auto& target, std::string_view category = "");
		void save_value(std::string_view key, const auto& source);

		// Mapping helpers
		void load_all();
		void save_all();
	};

	// Stream output
	inline std::ostream& operator<<(std::ostream& os, const Global& global) {
		const auto& p = global.props();
		os << "GlobalConfig("
			<< "Country: " << p.identity.country
			<< ", Locale: " << p.identity.locale
			<< ", Hypervisor: " << p.graphics.hypervisor
			<< ", ADB: " << (p.network.enable_adb_access ? "Enabled" : "Disabled")
			<< ")";
		return os;
	}

} // namespace bstk

#endif // BSTK_GLOBAL_HPP