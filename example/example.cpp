#include <bstk/bstk.hpp>
#include <iostream>

int main() {
	// Load configuration
	bstk::Config config;
	if (!config.load_from_file("bluestacks.conf")) {
		std::cerr << "Failed to load config\n";
		return 1;
	}

	std::cout << "=== BlueStacks Configuration Manager ===\n\n";

	// ============================================
	// GLOBAL CONFIGURATION
	// ============================================

	std::cout << "--- Global Settings ---\n";

	// Create global config handler
	bstk::Global global(config);

	// Print current state
	std::cout << global << "\n\n";

	// ============================================
	// METHOD 1: Direct Property Access
	// ============================================

	std::cout << "Current Settings:\n";
	std::cout << "  Country: " << global.props().identity.country << "\n";
	std::cout << "  Locale: " << global.props().identity.locale << "\n";
	std::cout << "  ADB Access: " << (global.props().network.enable_adb_access ? "Yes" : "No") << "\n";
	std::cout << "  UI Scale: " << global.props().display.ui_scale_factor << "\n";
	std::cout << "  System RAM: " << global.props().system.system_ram << " MB\n";
	std::cout << "  Hypervisor: " << global.props().graphics.hypervisor << "\n";
	std::cout << "  Macros Enabled: " << (global.props().feature_flags.macros ? "Yes" : "No") << "\n";

	// ============================================
	// METHOD 2: Fluent Interface - Chain Configuration
	// ============================================

	std::cout << "\n--- Configuring via Fluent Interface ---\n";

	global
		.country("US")
		.locale("en-US")
		.adb_access(true)
		.adb_remote_access(false)
		.ui_scale(1.25)
		.prefer_dedicated_gpu(true)
		.hypervisor("vbox")
		.gamepad_detection(true)
		.gamepad_vibration(true)
		.discord_integration(true)
		.enable_macros(true)
		.enable_rooting(false)
		.show_statusbar(true)
		.show_navigationbar(false)
		.overlay_opacity(75)
		.fresh_cpu(8, 8192)  // 8 cores, 8GB default RAM
		.memory_optimization(1)
		.enable_swap(false)
		.mim_framerate(60)
		.mim_grid(3)
		.desktop_shortcuts(true)
		.launch_store_on_boot(false);

	std::cout << "Configuration updated fluently!\n";

	// ============================================
	// METHOD 3: Batch Category Updates
	// ============================================

	std::cout << "\n--- Batch Category Updates ---\n";

	// Update all display settings at once
	{
		auto& d = global.props().display;
		d.enable_esc_fullscreen = true;
		d.enable_esc_mousecursor = true;
		d.custom_cursor_enabled = true;
		d.fixed_window_size = false;
		d.key_controls_overlay_enabled = true;
		d.key_controls_overlay_opacity = 60;
	}

	// Update all network settings
	{
		auto& n = global.props().network;
		n.enable_adb_access = true;
		n.dns_server = "1.1.1.1";
		n.dns_server2 = "1.0.0.1";
	}

	// Update feature flags
	{
		auto& f = global.props().feature_flags;
		f.ai_chat = false;
		f.live_stream = true;
		f.nowbux = true;
		f.skipNowggLogin = true;
		f.usage_stats = false;
	}

	// ============================================
	// METHOD 4: Conditional Logic
	// ============================================

	std::cout << "\n--- Conditional Configuration ---\n";

	// Auto-configure based on system RAM
	int64_t sys_ram = global.props().system.system_ram;
	if (sys_ram > 32000) {  // 32GB+
		global.props().system.fresh_cpu_core = 8;
		global.props().system.fresh_cpu_ram = 8192;
		global.props().system.mem_opt_mode = 2;  // Aggressive optimization
		std::cout << "High-end system detected: Optimized for performance\n";
	}
	else if (sys_ram > 16000) {  // 16GB+
		global.props().system.fresh_cpu_core = 4;
		global.props().system.fresh_cpu_ram = 4096;
		global.props().system.mem_opt_mode = 1;
		std::cout << "Mid-range system detected: Balanced settings\n";
	}
	else {
		global.props().system.fresh_cpu_core = 2;
		global.props().system.fresh_cpu_ram = 2048;
		global.props().system.mem_opt_mode = 0;
		std::cout << "Low-end system detected: Conservative settings\n";
	}

	// ============================================
	// METHOD 5: Generic Key Access (for unknown/custom keys)
	// ============================================

	std::cout << "\n--- Generic Key Access ---\n";

	// Read any global key
	auto custom_value = global.get("bst.custom.setting");
	std::cout << "Custom setting: " << custom_value.as_string() << "\n";

	// Set any global key
	global.set("bst.custom.timestamp", bstk::Value("2024-01-01"));
	global.set("bst.experimental.feature", bstk::Value(true));

	// Check existence
	if (global.has("bst.feature.macros")) {
		std::cout << "Macros feature key exists\n";
	}

	// List all global keys
	auto all_keys = global.keys();
	std::cout << "Total global keys: " << all_keys.size() << "\n";

	// Get keys by category
	auto feature_keys = global.keys_with_prefix("bst.feature.");
	std::cout << "Feature flag keys: " << feature_keys.size() << "\n";

	// ============================================
	// METHOD 6: Instance Management (Combined)
	// ============================================

	std::cout << "\n--- Instance Management ---\n";

	bstk::InstanceManager instances(config);

	std::cout << "Managing " << instances.count() << " instances\n";

	// Configure all instances based on global settings
	bool global_root = global.props().feature_flags.rooting;

	for (auto& inst : instances) {
		// Sync with global settings
		if (global_root) {
			inst.root_access(true);
		}

		// Apply global performance settings
		inst.props().graphics_engine = global.props().graphics.hypervisor == "hyperv" ? "hyperv" : "aga";

		inst.save_to_config();
	}

	// ============================================
	// METHOD 7: Save Everything
	// ============================================

	std::cout << "\n--- Saving Configuration ---\n";

	// Save global settings
	global.save_to_config();

	// Save all instances
	instances.save_all();

	// Save to file
	if (config.save_to_file("bluestacks_optimized.conf")) {
		std::cout << "Saved optimized configuration!\n";
	}

	// ============================================
	// METHOD 8: Print Final Summary
	// ============================================

	std::cout << "\n=== Final Configuration Summary ===\n";
	std::cout << "Global:\n";
	std::cout << "  Account: " << global.props().identity.account_id << "\n";
	std::cout << "  Country: " << global.props().identity.country << "\n";
	std::cout << "  ADB: " << (global.props().network.enable_adb_access ? "Enabled" : "Disabled") << "\n";
	std::cout << "  Rooting Feature: " << (global.props().feature_flags.rooting ? "Enabled" : "Disabled") << "\n";
	std::cout << "  UI Scale: " << global.props().display.ui_scale_factor << "x\n";
	std::cout << "  Default CPU/RAM: " << global.props().system.fresh_cpu_core << " cores / "
		<< global.props().system.fresh_cpu_ram << "MB\n";

	std::cout << "\nInstances:\n";
	for (const auto& inst : instances) {
		std::cout << "  - " << inst.name() << ": " << inst.props().display_name
			<< " (" << inst.props().cpus << " CPU, " << inst.props().ram << "MB RAM"
			<< ", Root: " << (inst.props().enable_root_access ? "Yes" : "No") << ")\n";
	}

	return 0;
}