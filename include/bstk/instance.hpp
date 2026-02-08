#ifndef BSTK_INSTANCE_HPP
#define BSTK_INSTANCE_HPP

#include "value.hpp"
#include <string>
#include <string_view>
#include <functional>
#include <iostream>

namespace bstk {

    // Forward declaration
    class Config;

    class Instance {
    public:
        // Core properties - direct access to common settings
        struct Properties {
            // Display
            std::string display_name;
            int fb_width = 1280;
            int fb_height = 720;
            int dpi = 240;
            int max_fps = 60;
            bool enable_high_fps = false;
            bool enable_vsync = false;
            bool enable_fullscreen_all_apps = false;

            // Performance
            int cpus = 4;
            int ram = 4096; // MB
            std::string graphics_engine = "aga";
            std::string graphics_renderer = "gl";
            bool enable_fps_display = false;
            int eco_mode_max_fps = 5;

            // Features
            bool enable_root_access = false;
            bool enable_notifications = true;
            bool game_controls_enabled = true;
            bool show_sidebar = true;
            bool pin_to_top = false;

            // Network & ADB
            int adb_port = 5555;
            std::string dns_server = "8.8.8.8";
            bool airplane_mode_active = false;

            // Device Profile
            std::string device_profile_code;
            std::string device_carrier_code;
            std::string device_country_code;

            // Storage
            std::string abi_list;
            bool vulkan_supported = false;
            std::string astc_decoding_mode = "software";

            // Audio
            bool android_sound_while_tapping = true;

            // Identity
            std::string android_id;
            std::string android_google_ad_id;
            std::string google_account_logins;
        };

        // Construct from Config reference and instance name
        Instance(Config& config, std::string name);
        Instance(const Instance&) = default;
        Instance(Instance&&) = default;
        Instance& operator=(const Instance&) = default;
        Instance& operator=(Instance&&) = default;

        // Identity
        [[nodiscard]] const std::string& name() const noexcept { return name_; }
        [[nodiscard]] std::string key_prefix() const { return "bst.instance." + name_ + "."; }

        // Load/Save properties from/to Config
        void load_from_config();
        void save_to_config();

        // Direct property access
        [[nodiscard]] Properties& props() noexcept { return props_; }
        [[nodiscard]] const Properties& props() const noexcept { return props_; }

        // Fluent interface for configuration
        Instance& display_name(std::string val) { props_.display_name = std::move(val); return *this; }
        Instance& resolution(int width, int height) { props_.fb_width = width; props_.fb_height = height; return *this; }
        Instance& dpi(int val) { props_.dpi = val; return *this; }
        Instance& fps(int max, bool high_fps = false) { props_.max_fps = max; props_.enable_high_fps = high_fps; return *this; }
        Instance& performance(int cpus, int ram_mb) { props_.cpus = cpus; props_.ram = ram_mb; return *this; }
        Instance& root_access(bool enable) { props_.enable_root_access = enable; return *this; }
        Instance& graphics_engine(std::string engine) { props_.graphics_engine = std::move(engine); return *this; }
        Instance& vulkan(bool enable) { props_.vulkan_supported = enable; return *this; }
        Instance& notifications(bool enable) { props_.enable_notifications = enable; return *this; }
        Instance& game_controls(bool enable) { props_.game_controls_enabled = enable; return *this; }
        Instance& sidebar(bool show) { props_.show_sidebar = show; return *this; }
        Instance& adb_port(int port) { props_.adb_port = port; return *this; }
        Instance& airplane_mode(bool active) { props_.airplane_mode_active = active; return *this; }
        Instance& profile_code(std::string code) { props_.device_profile_code = std::move(code); return *this; }
        Instance& google_account(std::string email) { props_.google_account_logins = std::move(email); return *this; }

        // Generic value access for any key
        [[nodiscard]] Value get(std::string_view key) const;
        void set(std::string_view key, const Value& value);
        void set(std::string_view key, Value&& value);

        // Check if key exists
        [[nodiscard]] bool has(std::string_view key) const;

        // Remove a key
        bool remove(std::string_view key);

        // Get all keys belonging to this instance
        [[nodiscard]] std::vector<std::string> keys() const;

        // Get raw value from config (bypass cache)
        [[nodiscard]] Value get_raw(std::string_view key) const;

        // Apply to config immediately (if not using save_to_config)
        void commit();

        // Comparison
        bool operator==(const Instance& other) const { return name_ == other.name_; }
        bool operator!=(const Instance& other) const { return !(*this == other); }
        bool operator<(const Instance& other) const { return name_ < other.name_; }

    private:
        Config* config_;
        std::string name_;
        Properties props_;

        [[nodiscard]] std::string full_key(std::string_view key) const;
        void load_value(std::string_view key, auto& target);
        void save_value(std::string_view key, const auto& source);
    };

    // Stream output
    inline std::ostream& operator<< (std::ostream& os, const Instance& inst) {
        os << "Instance(" << inst.name() << ": " << inst.props().display_name
            << ", " << inst.props().fb_width << "x" << inst.props().fb_height
            << ", " << inst.props().cpus << " CPU, " << inst.props().ram << "MB RAM)";
        return os;
    }

} // namespace bstk

#endif // BSTK_INSTANCE_HPP