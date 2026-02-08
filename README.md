# bstk-conf

[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/std/the-standard)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)

> **Lightweight, fast, and intuitive C++ library for BlueStacks configuration management**

`bstk-conf` provides a modern, type-safe C++ API for parsing, modifying, and generating BlueStacks emulator configuration files.

---

## Features

- **High Performance** - O(1) lookups, efficient parsing, minimal memory footprint
- **Type-Safe** - Strongly typed values with automatic type inference
- **Structured API** - Object-oriented interface with `Global` and `Instance` classes
- **Fluent Interface** - Chain configuration calls for readable code

---

## Usage Examples

### Basic Configuration Loading

```cpp
#include <bstk/bstk.hpp>
#include <iostream>

int main() {
    // Load configuration file
    bstk::Config config;
    if (!config.load_from_file("bluestacks.conf")) {
        std::cerr << "Failed to load configuration\n";
        return 1;
    }

    // Access any value with type inference
    auto ram = config.get_or<int64_t>("bst.instance.Pie64.ram", 4096);
    auto name = config.get_or<std::string>("bst.instance.Pie64.display_name", "BlueStacks");
    
    std::cout << "Instance: " << name << " with " << ram << "MB RAM\n";
    
    return 0;
}
```

### Global Configuration Management

```cpp
#include <bstk/bstk.hpp>

void configure_global_settings(bstk::Config& config) {
    bstk::Global global(config);
    
    // Fluent interface for common settings
    global
        .country("US")
        .locale("en-US")
        .adb_access(true)
        .prefer_dedicated_gpu(true)
        .ui_scale(1.25)
        .enable_macros(true)
        .enable_rooting(false)
        .fresh_cpu(8, 8192)  // 8 cores, 8GB RAM default
        .mim_grid(3);
    
    // Direct property access for batch updates
    auto& p = global.props();
    p.network.dns_server = "1.1.1.1";
    p.network.dns_server2 = "1.0.0.1";
    p.display.enable_statusbar = true;
    p.feature_flags.live_stream = true;
    
    // Save changes
    global.save_to_config();
}
```

### Instance Management

```cpp
#include <bstk/bstk.hpp>
#include <iostream>

void manage_instances(bstk::Config& config) {
    bstk::InstanceManager instances(config);
    
    // Iterate all instances
    for (auto& inst : instances) {
        std::cout << "Instance: " << inst.name() 
                  << " (" << inst.props().display_name << ")\n";
    }
    
    // Find specific instance
    if (auto* pie64 = instances.get("Pie64")) {
        // Fluent configuration
        pie64->display_name("Gaming Mode")
              .resolution(1920, 1080)
              .performance(8, 8192)
              .fps(144, true)
              .root_access(true)
              .vulkan(true);
        
        pie64->save_to_config();
    }
    
    // Bulk operations
    instances.apply_to_all([](bstk::Instance& inst) {
        inst.props().enable_notifications = true;
        inst.props().game_controls_enabled = true;
    });
    
    // Filter instances
    auto rooted = instances.with_root_access();
    auto high_fps = instances.with_high_fps();
    
    // Create new instance
    auto& new_inst = instances.create("Pie64_2")
        .display_name("Secondary Instance")
        .resolution(1280, 720)
        .performance(4, 4096);
    
    new_inst.save_to_config();
    instances.save_all();
}
```
