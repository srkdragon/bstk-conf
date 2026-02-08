#ifndef BSTK_CONFIG_HPP
#define BSTK_CONFIG_HPP

#include "value.hpp"
#include <unordered_map>
#include <vector>
#include <string>
#include <string_view>
#include <fstream>
#include <functional>

namespace bstk {

	class Config {
	public:
		using Iterator = std::unordered_map<std::string, Value>::iterator;
		using ConstIterator = std::unordered_map<std::string, Value>::const_iterator;

		Config() = default;

		// Load from file
		[[nodiscard]] bool load_from_file(const std::string& filepath);
		[[nodiscard]] bool load_from_string(std::string_view content);

		// Save to file
		[[nodiscard]] bool save_to_file(const std::string& filepath) const;
		[[nodiscard]] std::string to_string() const;

		// Value access
		[[nodiscard]] bool has(std::string_view key) const;
		[[nodiscard]] const Value* get(std::string_view key) const;
		[[nodiscard]] Value* get(std::string_view key);

		// Template getters with defaults
		template<typename T>
		[[nodiscard]] T get_or(std::string_view key, T default_val) const;

		// Setters
		void set(std::string_view key, const Value& value);
		void set(std::string_view key, Value&& value);
		void set_string(std::string_view key, std::string_view value);
		void set_int(std::string_view key, int64_t value);
		void set_double(std::string_view key, double value);
		void set_bool(std::string_view key, bool value);

		// Remove
		bool remove(std::string_view key);

		// Iteration
		[[nodiscard]] ConstIterator begin() const noexcept { return data_.begin(); }
		[[nodiscard]] ConstIterator end() const noexcept { return data_.end(); }
		[[nodiscard]] Iterator begin() noexcept { return data_.begin(); }
		[[nodiscard]] Iterator end() noexcept { return data_.end(); }

		// Queries
		[[nodiscard]] size_t size() const noexcept { return data_.size(); }
		[[nodiscard]] bool empty() const noexcept { return data_.empty(); }
		void clear() noexcept { data_.clear(); modified_keys_.clear(); }

		// Hierarchical access (e.g., "bst.instance.Pie64.ram")
		[[nodiscard]] std::vector<std::string> get_keys_with_prefix(std::string_view prefix) const;
		[[nodiscard]] Config get_namespace(std::string_view prefix) const;

		// Instance management helpers (BlueStacks specific)
		[[nodiscard]] std::vector<std::string> get_instance_names() const;
		[[nodiscard]] Config get_instance_config(std::string_view instance_name) const;

	private:
		std::unordered_map<std::string, Value> data_;
		std::vector<std::string> modified_keys_; // Track order for serialization

		void parse_content(std::string_view content);
	};

	// Template implementations
	template<typename T>
	T Config::get_or(std::string_view key, T default_val) const {
		auto it = data_.find(std::string(key));
		if (it == data_.end()) return default_val;

		if constexpr (std::is_same_v<T, std::string>) {
			return it->second.as_string();
		}
		else if constexpr (std::is_same_v<T, int64_t>) {
			return it->second.as_int();
		}
		else if constexpr (std::is_same_v<T, int>) {
			return static_cast<int>(it->second.as_int());
		}
		else if constexpr (std::is_same_v<T, double>) {
			return it->second.as_double();
		}
		else if constexpr (std::is_same_v<T, float>) {
			return static_cast<float>(it->second.as_double());
		}
		else if constexpr (std::is_same_v<T, bool>) {
			return it->second.as_bool();
		}
		else {
			static_assert(std::is_same_v<T, T>, "Unsupported type for get_or");
			return default_val;
		}
	}

} // namespace bstk

#endif // BSTK_CONFIG_HPP