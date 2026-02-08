#include "bstk/config.hpp"
#include "bstk/parser.hpp"
#include <sstream>
#include <algorithm>

namespace bstk {

	bool Config::load_from_file(const std::string& filepath) {
		std::ifstream file(filepath);
		if (!file.is_open()) return false;

		std::stringstream buffer;
		buffer << file.rdbuf();
		return load_from_string(buffer.str());
	}

	bool Config::load_from_string(std::string_view content) {
		clear();
		parse_content(content);
		return true;
	}

	bool Config::save_to_file(const std::string& filepath) const {
		std::ofstream file(filepath);
		if (!file.is_open()) return false;
		file << to_string();
		return file.good();
	}

	std::string Config::to_string() const {
		std::ostringstream oss;

		// Group by prefix for better organization
		std::vector<std::string> keys;
		keys.reserve(data_.size());
		for (const auto& [k, v] : data_) {
			keys.push_back(k);
		}
		std::sort(keys.begin(), keys.end());

		std::string last_prefix;
		for (const auto& key : keys) {
			auto it = data_.find(key);
			if (it == data_.end()) continue;

			// Add blank line between different top-level sections
			size_t first_dot = key.find('.');
			if (first_dot != std::string::npos) {
				std::string prefix = key.substr(0, first_dot);
				if (!last_prefix.empty() && prefix != last_prefix) {
					oss << "\n";
				}
				last_prefix = prefix;
			}

			oss << key << "=" << it->second.to_string() << "\n";
		}

		return oss.str();
	}

	bool Config::has(std::string_view key) const {
		return data_.find(std::string(key)) != data_.end();
	}

	const Value* Config::get(std::string_view key) const {
		auto it = data_.find(std::string(key));
		if (it != data_.end()) return &it->second;
		return nullptr;
	}

	Value* Config::get(std::string_view key) {
		auto it = data_.find(std::string(key));
		if (it != data_.end()) return &it->second;
		return nullptr;
	}

	void Config::set(std::string_view key, const Value& value) {
		std::string k(key);
		if (!data_.contains(k)) {
			modified_keys_.push_back(k);
		}
		data_[k] = value;
	}

	void Config::set(std::string_view key, Value&& value) {
		std::string k(key);
		if (!data_.contains(k)) {
			modified_keys_.push_back(k);
		}
		data_[k] = std::move(value);
	}

	void Config::set_string(std::string_view key, std::string_view value) {
		set(key, Value(std::string(value)));
	}

	void Config::set_int(std::string_view key, int64_t value) {
		set(key, Value(value));
	}

	void Config::set_double(std::string_view key, double value) {
		set(key, Value(value));
	}

	void Config::set_bool(std::string_view key, bool value) {
		set(key, Value(value));
	}

	bool Config::remove(std::string_view key) {
		auto it = data_.find(std::string(key));
		if (it != data_.end()) {
			data_.erase(it);
			modified_keys_.erase(
				std::remove(modified_keys_.begin(), modified_keys_.end(), std::string(key)),
				modified_keys_.end()
			);
			return true;
		}
		return false;
	}

	std::vector<std::string> Config::get_keys_with_prefix(std::string_view prefix) const {
		std::vector<std::string> result;
		for (const auto& [k, v] : data_) {
			if (k.size() >= prefix.size() &&
				std::string_view(k).substr(0, prefix.size()) == prefix) {
				result.push_back(k);
			}
		}
		return result;
	}

	Config Config::get_namespace(std::string_view prefix) const {
		Config result;
		std::string p(prefix);
		if (!p.empty() && p.back() != '.') p += '.';

		for (const auto& [k, v] : data_) {
			if (k.size() > p.size() && k.substr(0, p.size()) == p) {
				result.set(k.substr(p.size()), v);
			}
		}
		return result;
	}

	std::vector<std::string> Config::get_instance_names() const {
		std::vector<std::string> names;
		std::string prefix = "bst.instance.";

		for (const auto& [k, v] : data_) {
			if (k.size() > prefix.size() && k.substr(0, prefix.size()) == prefix) {
				size_t dot_pos = k.find('.', prefix.size());
				if (dot_pos != std::string::npos) {
					std::string name = k.substr(prefix.size(), dot_pos - prefix.size());
					if (std::find(names.begin(), names.end(), name) == names.end()) {
						names.push_back(name);
					}
				}
			}
		}
		return names;
	}

	Config Config::get_instance_config(std::string_view instance_name) const {
		return get_namespace(std::string("bst.instance.") + std::string(instance_name));
	}

	void Config::parse_content(std::string_view content) {
		size_t line_start = 0;
		while (line_start < content.size()) {
			size_t line_end = content.find('\n', line_start);
			if (line_end == std::string_view::npos) line_end = content.size();

			std::string_view line = content.substr(line_start, line_end - line_start);
			if (auto parsed = Parser::parse_line(line)) {
				data_[parsed->key] = Parser::infer_value(parsed->value);
				modified_keys_.push_back(parsed->key);
			}

			line_start = line_end + 1;
		}
	}

} // namespace bstk