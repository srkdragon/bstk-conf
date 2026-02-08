#include "bstk/parser.hpp"
#include "bstk/value.hpp"
#include <charconv>
#include <cctype>

namespace bstk {

	std::optional<ParsedLine> Parser::parse_line(std::string_view line) {
		line = trim(line);

		// Skip empty lines and comments
		if (line.empty() || line[0] == '#') {
			return std::nullopt;
		}

		// Find equals sign
		size_t eq_pos = line.find('=');
		if (eq_pos == std::string_view::npos) {
			return std::nullopt;
		}

		std::string key = std::string(trim(line.substr(0, eq_pos)));
		std::string_view value_view = trim(line.substr(eq_pos + 1));

		// Remove quotes if present
		std::string value;
		if (value_view.size() >= 2 && value_view.front() == '"' && value_view.back() == '"') {
			value = unescape(value_view.substr(1, value_view.size() - 2));
		}
		else {
			value = std::string(value_view);
		}

		return ParsedLine{ std::move(key), std::move(value), true };
	}

	std::string Parser::unescape(std::string_view value) {
		std::string result;
		result.reserve(value.size());

		for (size_t i = 0; i < value.size(); ++i) {
			if (value[i] == '\\' && i + 1 < value.size()) {
				char next = value[i + 1];
				switch (next) {
				case '"': result += '"'; ++i; break;
				case '\\': result += '\\'; ++i; break;
				case 'n': result += '\n'; ++i; break;
				case 'r': result += '\r'; ++i; break;
				case 't': result += '\t'; ++i; break;
				default: result += value[i]; break;
				}
			}
			else {
				result += value[i];
			}
		}

		return result;
	}

	std::string Parser::escape(std::string_view value) {
		std::string result;
		result.reserve(value.size());

		for (char c : value) {
			switch (c) {
			case '"': result += "\\\""; break;
			case '\\': result += "\\\\"; break;
			case '\n': result += "\\n"; break;
			case '\r': result += "\\r"; break;
			case '\t': result += "\\t"; break;
			default: result += c; break;
			}
		}

		return result;
	}

	Value Parser::infer_value(std::string_view raw_value) {
		if (looks_like_bool(raw_value)) {
			return Value(raw_value == "1" || raw_value == "true" || raw_value == "True");
		}
		if (looks_like_int(raw_value)) {
			int64_t val = 0;
			std::from_chars(raw_value.data(), raw_value.data() + raw_value.size(), val);
			return Value(val);
		}
		if (looks_like_double(raw_value)) {
			return Value(std::stod(std::string(raw_value)));
		}
		return Value(std::string(raw_value));
	}

	std::string_view Parser::trim(std::string_view sv) {
		size_t start = 0;
		while (start < sv.size() && std::isspace(static_cast<unsigned char>(sv[start]))) {
			++start;
		}
		size_t end = sv.size();
		while (end > start && std::isspace(static_cast<unsigned char>(sv[end - 1]))) {
			--end;
		}
		return sv.substr(start, end - start);
	}

	bool Parser::looks_like_int(std::string_view sv) {
		if (sv.empty()) return false;
		size_t i = (sv[0] == '-' || sv[0] == '+') ? 1 : 0;
		if (i >= sv.size()) return false;
		for (; i < sv.size(); ++i) {
			if (!std::isdigit(static_cast<unsigned char>(sv[i]))) return false;
		}
		return true;
	}

	bool Parser::looks_like_double(std::string_view sv) {
		if (sv.empty()) return false;
		bool has_dot = false;
		size_t i = (sv[0] == '-' || sv[0] == '+') ? 1 : 0;
		if (i >= sv.size()) return false;
		for (; i < sv.size(); ++i) {
			if (sv[i] == '.') {
				if (has_dot) return false;
				has_dot = true;
			}
			else if (!std::isdigit(static_cast<unsigned char>(sv[i]))) {
				return false;
			}
		}
		return has_dot;
	}

	bool Parser::looks_like_bool(std::string_view sv) {
		return sv == "0" || sv == "1" || sv == "true" || sv == "false" ||
			sv == "True" || sv == "False";
	}

} // namespace bstk