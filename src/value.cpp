#include "bstk/value.hpp"
#include <charconv>
#include <sstream>

namespace bstk {

	std::string Value::as_string() const {
		return std::visit([](auto&& arg) -> std::string {
			using T = std::decay_t<decltype(arg)>;
			if constexpr (std::is_same_v<T, std::string>) {
				return arg;
			}
			else if constexpr (std::is_same_v<T, bool>) {
				return arg ? "1" : "0";
			}
			else {
				return std::to_string(arg);
			}
			}, data_);
	}

	int64_t Value::as_int() const {
		if (std::holds_alternative<int64_t>(data_)) {
			return std::get<int64_t>(data_);
		}
		if (std::holds_alternative<double>(data_)) {
			return static_cast<int64_t>(std::get<double>(data_));
		}
		if (std::holds_alternative<std::string>(data_)) {
			const auto& s = std::get<std::string>(data_);
			int64_t result = 0;
			std::from_chars(s.data(), s.data() + s.size(), result);
			return result;
		}
		return std::get<bool>(data_) ? 1 : 0;
	}

	double Value::as_double() const {
		if (std::holds_alternative<double>(data_)) {
			return std::get<double>(data_);
		}
		if (std::holds_alternative<int64_t>(data_)) {
			return static_cast<double>(std::get<int64_t>(data_));
		}
		if (std::holds_alternative<std::string>(data_)) {
			return std::stod(std::get<std::string>(data_));
		}
		return std::get<bool>(data_) ? 1.0 : 0.0;
	}

	bool Value::as_bool() const {
		if (std::holds_alternative<bool>(data_)) {
			return std::get<bool>(data_);
		}
		if (std::holds_alternative<int64_t>(data_)) {
			return std::get<int64_t>(data_) != 0;
		}
		if (std::holds_alternative<double>(data_)) {
			return std::get<double>(data_) != 0.0;
		}
		const auto& s = std::get<std::string>(data_);
		return !s.empty() && s != "0" && s != "false" && s != "False";
	}

	std::string Value::to_string() const {
		return std::visit([](auto&& arg) -> std::string {
			using T = std::decay_t<decltype(arg)>;
			if constexpr (std::is_same_v<T, std::string>) {
				// Escape quotes and backslashes
				std::string result = "\"";
				for (char c : arg) {
					if (c == '\\' || c == '"') result += '\\';
					result += c;
				}
				result += '"';
				return result;
			}
			else if constexpr (std::is_same_v<T, bool>) {
				return arg ? "\"1\"" : "\"0\"";
			}
			else {
				return "\"" + std::to_string(arg) + "\"";
			}
			}, data_);
	}

} // namespace bstk