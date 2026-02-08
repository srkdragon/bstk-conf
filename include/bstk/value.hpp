#ifndef BSTK_VALUE_HPP
#define BSTK_VALUE_HPP

#include <string>
#include <variant>
#include <stdexcept>

namespace bstk {

	class Value {
	public:
		using Variant = std::variant<std::string, int64_t, double, bool>;

		Value() = default;
		explicit Value(std::string val) : data_(std::move(val)) {}
		explicit Value(int64_t val) : data_(val) {}
		explicit Value(double val) : data_(val) {}
		explicit Value(bool val) : data_(val) {}

		// Type checks
		[[nodiscard]] bool is_string() const noexcept { return std::holds_alternative<std::string>(data_); }
		[[nodiscard]] bool is_int() const noexcept { return std::holds_alternative<int64_t>(data_); }
		[[nodiscard]] bool is_double() const noexcept { return std::holds_alternative<double>(data_); }
		[[nodiscard]] bool is_bool() const noexcept { return std::holds_alternative<bool>(data_); }
		[[nodiscard]] bool is_number() const noexcept { return is_int() || is_double(); }

		// Getters with automatic conversion attempts
		[[nodiscard]] std::string as_string() const;
		[[nodiscard]] int64_t as_int() const;
		[[nodiscard]] double as_double() const;
		[[nodiscard]] bool as_bool() const;

		// Raw access
		[[nodiscard]] const Variant& raw() const noexcept { return data_; }
		[[nodiscard]] Variant& raw() noexcept { return data_; }

		// Comparison
		bool operator==(const Value& other) const { return data_ == other.data_; }
		bool operator!=(const Value& other) const { return !(*this == other); }

		// String representation for serialization
		[[nodiscard]] std::string to_string() const;

	private:
		Variant data_;
	};

} // namespace bstk

#endif // BSTK_VALUE_HPP