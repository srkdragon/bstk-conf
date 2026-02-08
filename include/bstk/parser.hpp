#ifndef BSTK_PARSER_HPP
#define BSTK_PARSER_HPP

#include <string>
#include <string_view>
#include <optional>
#include <utility>

namespace bstk {

	struct ParsedLine {
		std::string key;
		std::string value;
		bool is_valid = false;
	};

	class Parser {
	public:
		// Parse a single line, returns empty optional if line is empty/comment
		[[nodiscard]] static std::optional<ParsedLine> parse_line(std::string_view line);

		// Unescape a quoted string value
		[[nodiscard]] static std::string unescape(std::string_view value);

		// Escape a string for serialization
		[[nodiscard]] static std::string escape(std::string_view value);

		// Infer type and create appropriate Value
		[[nodiscard]] static class Value infer_value(std::string_view raw_value);

	private:
		[[nodiscard]] static std::string_view trim(std::string_view sv);
		[[nodiscard]] static bool looks_like_int(std::string_view sv);
		[[nodiscard]] static bool looks_like_double(std::string_view sv);
		[[nodiscard]] static bool looks_like_bool(std::string_view sv);
	};

} // namespace bstk

#endif // BSTK_PARSER_HPP