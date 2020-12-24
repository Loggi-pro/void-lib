#pragma once

namespace vd {

	enum float_round_style {
		round_indeterminate       = -1,
		round_toward_zero         = 0,
		round_to_nearest          = 1,
		round_toward_infinity     = 2,
		round_toward_neg_infinity = 3
	};
	enum float_denorm_style {
		denorm_indeterminate = -1,
		denorm_absent        = 0,
		denorm_present       = 1
	};

#ifdef VOID_COMPILER_GCC
	#define FLOATING_DENORM_LOSS false
#elif defined (VOID_COMPILER_MSVC)
	#define FLOATING_DENORM_LOSS true
#endif
#ifdef min
	#undef min
#endif
#ifdef max
	#undef max
#endif

	template< class T > class numeric_limits {
			static constexpr bool is_specialized = false;
			static constexpr bool is_signed = false;
			static constexpr bool is_integer = false;
			static constexpr bool is_exact = false;
			static constexpr bool has_infinity = false;
			static constexpr bool has_quiet_NaN = false;
			static constexpr bool has_signaling_NaN = false;
			static constexpr vd::float_denorm_style has_denorm = vd::denorm_absent;
			static constexpr bool has_denorm_loss = false;
			static constexpr vd::float_round_style round_style = vd::round_toward_zero;
			static constexpr bool is_iec559 = false;
			static constexpr bool is_bounded = false;
			static constexpr bool is_modulo = false;
			static constexpr int digits = 0;
			static constexpr int digits10 = 0;
			static constexpr int max_digits10 = 0;
			static constexpr int radix = 0;
			static constexpr int min_exponent = 0;
			static constexpr int min_exponent10 = 0;
			static constexpr int max_exponent = 0;
			static constexpr int max_exponent10 = 0;
			static constexpr bool traps = false;
			static constexpr bool tinyness_before = false;

			static constexpr T signaling_NaN() noexcept {
				return T();
			}
	};

	template<> struct numeric_limits<bool> {
		using T = bool;
		static constexpr bool is_specialized = true;
		static constexpr bool is_signed = false;
		static constexpr bool is_integer = true;
		static constexpr bool is_exact = true;
		static constexpr bool has_infinity = false;
		static constexpr bool has_quiet_NaN = false;
		static constexpr bool has_signaling_NaN = false;
		static constexpr vd::float_denorm_style has_denorm = vd::denorm_absent;
		static constexpr bool has_denorm_loss = false;
		static constexpr vd::float_round_style round_style = vd::round_toward_zero;
		static constexpr bool is_iec559 = false;
		static constexpr bool is_bounded = true;
		static constexpr bool is_modulo = false;
		static constexpr int digits = 1;
		static constexpr int digits10 = 0;
		static constexpr int max_digits10 = 0;
		static constexpr int radix = 2;
		static constexpr int min_exponent = 0;
		static constexpr int min_exponent10 = 0;
		static constexpr int max_exponent = 0;
		static constexpr int max_exponent10 = 0;
		static constexpr bool traps = false;
		static constexpr bool tinyness_before = false;
		static constexpr T min() noexcept {
			return false;
		}
		static constexpr T lowest() noexcept {
			return false;
		}
		static constexpr T max() noexcept {
			return true;
		}
		static T epsilon() {
			return false;
		}
		static constexpr T round_error() noexcept {
			return false;
		}
		static constexpr T infinity() noexcept {
			return false;
		}
		static constexpr T quiet_NaN() noexcept {
			return false;
		}
		static constexpr T signaling_NaN() noexcept {
			return false;
		}
		static constexpr T denorm_min() noexcept {
			return false;
		}
	};
	template<> struct numeric_limits<char> {
		using T = char;
		static constexpr bool is_specialized = true;
		static constexpr bool is_signed = CHAR_MIN != 0;
		static constexpr bool is_integer = true;
		static constexpr bool is_exact = true;
		static constexpr bool has_infinity = false;
		static constexpr bool has_quiet_NaN = false;
		static constexpr bool has_signaling_NaN = false;
		static constexpr vd::float_denorm_style has_denorm = vd::denorm_absent;
		static constexpr bool has_denorm_loss = false;
		static constexpr vd::float_round_style round_style = vd::round_toward_zero;
		static constexpr bool is_iec559 = false;
		static constexpr bool is_bounded = true;
		static constexpr bool is_modulo = CHAR_MIN == 0;
		static constexpr int digits = 8 - (CHAR_MIN != 0);
		static constexpr int digits10 = 2;
		static constexpr int max_digits10 = 0;
		static constexpr int radix = 2;
		static constexpr int min_exponent = 0;
		static constexpr int min_exponent10 = 0;
		static constexpr int max_exponent = 0;
		static constexpr int max_exponent10 = 0;
		static constexpr bool traps = true;
		static constexpr bool tinyness_before = false;
		static constexpr T min() noexcept {
			return CHAR_MIN;
		}
		static constexpr T lowest() noexcept {
			return CHAR_MIN;
		}
		static constexpr T max() noexcept {
			return CHAR_MAX;
		}
		static T epsilon() {
			return 0;
		}
		static constexpr T round_error() noexcept {
			return 0;
		}
		static constexpr T infinity() noexcept {
			return 0;
		}
		static constexpr T quiet_NaN() noexcept {
			return 0;
		}
		static constexpr T signaling_NaN() noexcept {
			return 0;
		}
		static constexpr T denorm_min() noexcept {
			return 0;
		}
	};
	template<> struct numeric_limits<signed char> {
		using T = signed char;
		static constexpr bool is_specialized = true;
		static constexpr bool is_signed = true;
		static constexpr bool is_integer = true;
		static constexpr bool is_exact = true;
		static constexpr bool has_infinity = false;
		static constexpr bool has_quiet_NaN = false;
		static constexpr bool has_signaling_NaN = false;
		static constexpr vd::float_denorm_style has_denorm = vd::denorm_absent;
		static constexpr bool has_denorm_loss = false;
		static constexpr vd::float_round_style round_style = vd::round_toward_zero;
		static constexpr bool is_iec559 = false;
		static constexpr bool is_bounded = true;
		static constexpr bool is_modulo = false;
		static constexpr int digits = CHAR_BIT - 1;
		static constexpr int digits10 = 2;
		static constexpr int max_digits10 = 0;
		static constexpr int radix = 2;
		static constexpr int min_exponent = 0;
		static constexpr int min_exponent10 = 0;
		static constexpr int max_exponent = 0;
		static constexpr int max_exponent10 = 0;
		static constexpr bool traps = true;
		static constexpr bool tinyness_before = false;
		static constexpr T min() noexcept {
			return SCHAR_MIN;
		}
		static constexpr T lowest() noexcept {
			return SCHAR_MIN;
		}
		static constexpr T max() noexcept {
			return SCHAR_MAX;
		}
		static T epsilon() {
			return 0;
		}
		static constexpr T round_error() noexcept {
			return 0;
		}
		static constexpr T infinity() noexcept {
			return 0;
		}
		static constexpr T quiet_NaN() noexcept {
			return 0;
		}
		static constexpr T signaling_NaN() noexcept {
			return 0;
		}
		static constexpr T denorm_min() noexcept {
			return 0;
		}
	};
	template<> struct numeric_limits<unsigned char> {
		using T = unsigned char;
		static constexpr bool is_specialized = true;
		static constexpr bool is_signed = false;
		static constexpr bool is_integer = true;
		static constexpr bool is_exact = true;
		static constexpr bool has_infinity = false;
		static constexpr bool has_quiet_NaN = false;
		static constexpr bool has_signaling_NaN = false;
		static constexpr vd::float_denorm_style has_denorm = vd::denorm_absent;
		static constexpr bool has_denorm_loss = false;
		static constexpr vd::float_round_style round_style = vd::round_toward_zero;
		static constexpr bool is_iec559 = false;
		static constexpr bool is_bounded = true;
		static constexpr bool is_modulo = true;
		static constexpr int digits = CHAR_BIT;
		static constexpr int digits10 = 2;
		static constexpr int max_digits10 = 0;
		static constexpr int radix = 2;
		static constexpr int min_exponent = 0;
		static constexpr int min_exponent10 = 0;
		static constexpr int max_exponent = 0;
		static constexpr int max_exponent10 = 0;
		static constexpr bool traps = true;
		static constexpr bool tinyness_before = false;
		static constexpr T min() noexcept {
			return 0;
		}
		static constexpr T lowest() noexcept {
			return 0;
		}
		static constexpr T max() noexcept {
			return UCHAR_MAX;
		}
		static T epsilon() {
			return 0;
		}
		static constexpr T round_error() noexcept {
			return 0;
		}
		static constexpr T infinity() noexcept {
			return 0;
		}
		static constexpr T quiet_NaN() noexcept {
			return 0;
		}
		static constexpr T signaling_NaN() noexcept {
			return 0;
		}
		static constexpr T denorm_min() noexcept {
			return 0;
		}
	};
	template<> struct numeric_limits<wchar_t> {
		using T = wchar_t;
		static constexpr bool is_specialized = true;
		static constexpr bool is_signed = false;
		static constexpr bool is_integer = true;
		static constexpr bool is_exact = true;
		static constexpr bool has_infinity = false;
		static constexpr bool has_quiet_NaN = false;
		static constexpr bool has_signaling_NaN = false;
		static constexpr vd::float_denorm_style has_denorm = vd::denorm_absent;
		static constexpr bool has_denorm_loss = false;
		static constexpr vd::float_round_style round_style = vd::round_toward_zero;
		static constexpr bool is_iec559 = false;
		static constexpr bool is_bounded = true;
		static constexpr bool is_modulo = true;
		static constexpr int digits = CHAR_BIT * sizeof(wchar_t);
		static constexpr int digits10 = 4;
		static constexpr int max_digits10 = 0;
		static constexpr int radix = 2;
		static constexpr int min_exponent = 0;
		static constexpr int min_exponent10 = 0;
		static constexpr int max_exponent = 0;
		static constexpr int max_exponent10 = 0;
		static constexpr bool traps = true;
		static constexpr bool tinyness_before = false;
		static constexpr T min() noexcept {
			return WCHAR_MIN;
		}
		static constexpr T lowest() noexcept {
			return WCHAR_MIN;
		}
		static constexpr T max() noexcept {
			return WCHAR_MAX;
		}
		static T epsilon() {
			return 0;
		}
		static constexpr T round_error() noexcept {
			return 0;
		}
		static constexpr T infinity() noexcept {
			return 0;
		}
		static constexpr T quiet_NaN() noexcept {
			return 0;
		}
		static constexpr T signaling_NaN() noexcept {
			return 0;
		}
		static constexpr T denorm_min() noexcept {
			return 0;
		}
	};
	template<> struct numeric_limits<char16_t> {
		using T = char16_t;
		static constexpr bool is_specialized = true;
		static constexpr bool is_signed = false;
		static constexpr bool is_integer = true;
		static constexpr bool is_exact = true;
		static constexpr bool has_infinity = false;
		static constexpr bool has_quiet_NaN = false;
		static constexpr bool has_signaling_NaN = false;
		static constexpr vd::float_denorm_style has_denorm = vd::denorm_absent;
		static constexpr bool has_denorm_loss = false;
		static constexpr vd::float_round_style round_style = vd::round_toward_zero;
		static constexpr bool is_iec559 = false;
		static constexpr bool is_bounded = true;
		static constexpr bool is_modulo = true;
		static constexpr int digits = CHAR_BIT * sizeof(char16_t);
		static constexpr int digits10 = 4;
		static constexpr int max_digits10 = 0;
		static constexpr int radix = 2;
		static constexpr int min_exponent = 0;
		static constexpr int min_exponent10 = 0;
		static constexpr int max_exponent = 0;
		static constexpr int max_exponent10 = 0;
		static constexpr bool traps = true;
		static constexpr bool tinyness_before = false;
		static constexpr T min() noexcept {
			return 0;
		}
		static constexpr T lowest() noexcept {
			return 0;
		}
		static constexpr T max() noexcept {
			return UINT_LEAST16_MAX;
		}
		static T epsilon() {
			return 0;
		}
		static constexpr T round_error() noexcept {
			return 0;
		}
		static constexpr T infinity() noexcept {
			return 0;
		}
		static constexpr T quiet_NaN() noexcept {
			return 0;
		}
		static constexpr T signaling_NaN() noexcept {
			return 0;
		}
		static constexpr T denorm_min() noexcept {
			return 0;
		}
	};
	template<> struct numeric_limits<char32_t> {
		using T = char32_t;
		static constexpr bool is_specialized = true;
		static constexpr bool is_signed = false;
		static constexpr bool is_integer = true;
		static constexpr bool is_exact = true;
		static constexpr bool has_infinity = false;
		static constexpr bool has_quiet_NaN = false;
		static constexpr bool has_signaling_NaN = false;
		static constexpr vd::float_denorm_style has_denorm = vd::denorm_absent;
		static constexpr bool has_denorm_loss = false;
		static constexpr vd::float_round_style round_style = vd::round_toward_zero;
		static constexpr bool is_iec559 = false;
		static constexpr bool is_bounded = true;
		static constexpr bool is_modulo = true;
		static constexpr int digits = CHAR_BIT * sizeof(char32_t);
		static constexpr int digits10 = 9;
		static constexpr int max_digits10 = 0;
		static constexpr int radix = 2;
		static constexpr int min_exponent = 0;
		static constexpr int min_exponent10 = 0;
		static constexpr int max_exponent = 0;
		static constexpr int max_exponent10 = 0;
		static constexpr bool traps = true;
		static constexpr bool tinyness_before = false;
		static constexpr T min() noexcept {
			return 0;
		}
		static constexpr T lowest() noexcept {
			return 0;
		}
		static constexpr T max() noexcept {
			return UINT_LEAST32_MAX;
		}
		static T epsilon() {
			return 0;
		}
		static constexpr T round_error() noexcept {
			return 0;
		}
		static constexpr T infinity() noexcept {
			return 0;
		}
		static constexpr T quiet_NaN() noexcept {
			return 0;
		}
		static constexpr T signaling_NaN() noexcept {
			return 0;
		}
		static constexpr T denorm_min() noexcept {
			return 0;
		}
	};
	template<> struct numeric_limits<short> {
		using T = short;
		static constexpr bool is_specialized = true;
		static constexpr bool is_signed = true;
		static constexpr bool is_integer = true;
		static constexpr bool is_exact = true;
		static constexpr bool has_infinity = false;
		static constexpr bool has_quiet_NaN = false;
		static constexpr bool has_signaling_NaN = false;
		static constexpr vd::float_denorm_style has_denorm = vd::denorm_absent;
		static constexpr bool has_denorm_loss = false;
		static constexpr vd::float_round_style round_style = vd::round_toward_zero;
		static constexpr bool is_iec559 = false;
		static constexpr bool is_bounded = true;
		static constexpr bool is_modulo = false;
		static constexpr int digits = CHAR_BIT * sizeof(short) -1;
		static constexpr int digits10 = 4;
		static constexpr int max_digits10 = 0;
		static constexpr int radix = 2;
		static constexpr int min_exponent = 0;
		static constexpr int min_exponent10 = 0;
		static constexpr int max_exponent = 0;
		static constexpr int max_exponent10 = 0;
		static constexpr bool traps = true;
		static constexpr bool tinyness_before = false;
		static constexpr T min() noexcept {
			return SHRT_MIN;
		}
		static constexpr T lowest() noexcept {
			return SHRT_MIN;
		}
		static constexpr T max() noexcept {
			return SHRT_MAX;
		}
		static T epsilon() {
			return 0;
		}
		static constexpr T round_error() noexcept {
			return 0;
		}
		static constexpr T infinity() noexcept {
			return 0;
		}
		static constexpr T quiet_NaN() noexcept {
			return 0;
		}
		static constexpr T signaling_NaN() noexcept {
			return 0;
		}
		static constexpr T denorm_min() noexcept {
			return 0;
		}
	};
	template<> struct numeric_limits<unsigned short> {
		using T = unsigned short;
		static constexpr bool is_specialized = true;
		static constexpr bool is_signed = false;
		static constexpr bool is_integer = true;
		static constexpr bool is_exact = true;
		static constexpr bool has_infinity = false;
		static constexpr bool has_quiet_NaN = false;
		static constexpr bool has_signaling_NaN = false;
		static constexpr vd::float_denorm_style has_denorm = vd::denorm_absent;
		static constexpr bool has_denorm_loss = false;
		static constexpr vd::float_round_style round_style = vd::round_toward_zero;
		static constexpr bool is_iec559 = false;
		static constexpr bool is_bounded = true;
		static constexpr bool is_modulo = true;
		static constexpr int digits = CHAR_BIT * sizeof(short);
		static constexpr int digits10 = 4;
		static constexpr int max_digits10 = 0;
		static constexpr int radix = 2;
		static constexpr int min_exponent = 0;
		static constexpr int min_exponent10 = 0;
		static constexpr int max_exponent = 0;
		static constexpr int max_exponent10 = 0;
		static constexpr bool traps = true;
		static constexpr bool tinyness_before = false;
		static constexpr T min() noexcept {
			return 0;
		}
		static constexpr T lowest() noexcept {
			return 0;
		}
		static constexpr T max() noexcept {
			return USHRT_MAX;
		}
		static T epsilon() {
			return 0;
		}
		static constexpr T round_error() noexcept {
			return 0;
		}
		static constexpr T infinity() noexcept {
			return 0;
		}
		static constexpr T quiet_NaN() noexcept {
			return 0;
		}
		static constexpr T signaling_NaN() noexcept {
			return 0;
		}
		static constexpr T denorm_min() noexcept {
			return 0;
		}
	};
	template<> struct numeric_limits<int> {
		using T = int;
		static constexpr bool is_specialized = true;
		static constexpr bool is_signed = true;
		static constexpr bool is_integer = true;
		static constexpr bool is_exact = true;
		static constexpr bool has_infinity = false;
		static constexpr bool has_quiet_NaN = false;
		static constexpr bool has_signaling_NaN = false;
		static constexpr vd::float_denorm_style has_denorm = vd::denorm_absent;
		static constexpr bool has_denorm_loss = false;
		static constexpr vd::float_round_style round_style = vd::round_toward_zero;
		static constexpr bool is_iec559 = false;
		static constexpr bool is_bounded = true;
		static constexpr bool is_modulo = false;
		static constexpr int digits = CHAR_BIT * sizeof(int) -1;
		static constexpr int digits10 = 9;
		static constexpr int max_digits10 = 0;
		static constexpr int radix = 2;
		static constexpr int min_exponent = 0;
		static constexpr int min_exponent10 = 0;
		static constexpr int max_exponent = 0;
		static constexpr int max_exponent10 = 0;
		static constexpr bool traps = true;
		static constexpr bool tinyness_before = false;
		static constexpr T min() noexcept {
			return INT_MIN;
		}
		static constexpr T lowest() noexcept {
			return INT_MIN;
		}
		static constexpr T max() noexcept {
			return INT_MAX;
		}
		static T epsilon() {
			return 0;
		}
		static constexpr T round_error() noexcept {
			return 0;
		}
		static constexpr T infinity() noexcept {
			return 0;
		}
		static constexpr T quiet_NaN() noexcept {
			return 0;
		}
		static constexpr T signaling_NaN() noexcept {
			return 0;
		}
		static constexpr T denorm_min() noexcept {
			return 0;
		}
	};
	template<> struct numeric_limits<unsigned int> {
		using T = unsigned int;
		static constexpr bool is_specialized = true;
		static constexpr bool is_signed = false;
		static constexpr bool is_integer = true;
		static constexpr bool is_exact = true;
		static constexpr bool has_infinity = false;
		static constexpr bool has_quiet_NaN = false;
		static constexpr bool has_signaling_NaN = false;
		static constexpr vd::float_denorm_style has_denorm = vd::denorm_absent;
		static constexpr bool has_denorm_loss = false;
		static constexpr vd::float_round_style round_style = vd::round_toward_zero;
		static constexpr bool is_iec559 = false;
		static constexpr bool is_bounded = true;
		static constexpr bool is_modulo = true;
		static constexpr int digits = CHAR_BIT * sizeof(int);
		static constexpr int digits10 = 9;
		static constexpr int max_digits10 = 0;
		static constexpr int radix = 2;
		static constexpr int min_exponent = 0;
		static constexpr int min_exponent10 = 0;
		static constexpr int max_exponent = 0;
		static constexpr int max_exponent10 = 0;
		static constexpr bool traps = true;
		static constexpr bool tinyness_before = false;
		static constexpr T min() noexcept {
			return 0;
		}
		static constexpr T lowest() noexcept {
			return 0;
		}
		static constexpr T max() noexcept {
			return 	UINT_MAX;
		}
		static T epsilon() {
			return 0;
		}
		static constexpr T round_error() noexcept {
			return 0;
		}
		static constexpr T infinity() noexcept {
			return 0;
		}
		static constexpr T quiet_NaN() noexcept {
			return 0;
		}
		static constexpr T signaling_NaN() noexcept {
			return 0;
		}
		static constexpr T denorm_min() noexcept {
			return 0;
		}
	};
	template<> struct numeric_limits<long> {
		using T = long;
		static constexpr bool is_specialized = true;
		static constexpr bool is_signed = true;
		static constexpr bool is_integer = true;
		static constexpr bool is_exact = true;
		static constexpr bool has_infinity = false;
		static constexpr bool has_quiet_NaN = false;
		static constexpr bool has_signaling_NaN = false;
		static constexpr vd::float_denorm_style has_denorm = vd::denorm_absent;
		static constexpr bool has_denorm_loss = false;
		static constexpr vd::float_round_style round_style = vd::round_toward_zero;
		static constexpr bool is_iec559 = false;
		static constexpr bool is_bounded = true;
		static constexpr bool is_modulo = false;
		static constexpr int digits = CHAR_BIT * sizeof(long) -1;
		static constexpr int digits10 = 9;
		static constexpr int max_digits10 = 0;
		static constexpr int radix = 2;
		static constexpr int min_exponent = 0;
		static constexpr int min_exponent10 = 0;
		static constexpr int max_exponent = 0;
		static constexpr int max_exponent10 = 0;
		static constexpr bool traps = true;
		static constexpr bool tinyness_before = false;
		static constexpr T min() noexcept {
			return LONG_MIN;
		}
		static constexpr T lowest() noexcept {
			return LONG_MIN;
		}
		static constexpr T max() noexcept {
			return 	LONG_MAX;
		}
		static T epsilon() {
			return 0;
		}
		static constexpr T round_error() noexcept {
			return 0;
		}
		static constexpr T infinity() noexcept {
			return 0;
		}
		static constexpr T quiet_NaN() noexcept {
			return 0;
		}
		static constexpr T signaling_NaN() noexcept {
			return 0;
		}
		static constexpr T denorm_min() noexcept {
			return 0;
		}
	};
	template<> struct numeric_limits<unsigned long> {
		using T = unsigned long;
		static constexpr bool is_specialized = true;
		static constexpr bool is_signed = false;
		static constexpr bool is_integer = true;
		static constexpr bool is_exact = true;
		static constexpr bool has_infinity = false;
		static constexpr bool has_quiet_NaN = false;
		static constexpr bool has_signaling_NaN = false;
		static constexpr vd::float_denorm_style has_denorm = vd::denorm_absent;
		static constexpr bool has_denorm_loss = false;
		static constexpr vd::float_round_style round_style = vd::round_toward_zero;
		static constexpr bool is_iec559 = false;
		static constexpr bool is_bounded = true;
		static constexpr bool is_modulo = true;
		static constexpr int digits = CHAR_BIT * sizeof(long);
		static constexpr int digits10 = 9;
		static constexpr int max_digits10 = 0;
		static constexpr int radix = 2;
		static constexpr int min_exponent = 0;
		static constexpr int min_exponent10 = 0;
		static constexpr int max_exponent = 0;
		static constexpr int max_exponent10 = 0;
		static constexpr bool traps = true;
		static constexpr bool tinyness_before = false;
		static constexpr T min() noexcept {
			return 0;
		}
		static constexpr T lowest() noexcept {
			return 0;
		}
		static constexpr T max() noexcept {
			return ULONG_MAX;
		}
		static T epsilon() {
			return 0;
		}
		static constexpr T round_error() noexcept {
			return 0;
		}
		static constexpr T infinity() noexcept {
			return 0;
		}
		static constexpr T quiet_NaN() noexcept {
			return 0;
		}
		static constexpr T signaling_NaN() noexcept {
			return 0;
		}
		static constexpr T denorm_min() noexcept {
			return 0;
		}
	};
	template<> struct numeric_limits<long long> {
		using T = long long;
		static constexpr bool is_specialized = true;
		static constexpr bool is_signed = true;
		static constexpr bool is_integer = true;
		static constexpr bool is_exact = true;
		static constexpr bool has_infinity = false;
		static constexpr bool has_quiet_NaN = false;
		static constexpr bool has_signaling_NaN = false;
		static constexpr vd::float_denorm_style has_denorm = vd::denorm_absent;
		static constexpr bool has_denorm_loss = false;
		static constexpr vd::float_round_style round_style = vd::round_toward_zero;
		static constexpr bool is_iec559 = false;
		static constexpr bool is_bounded = true;
		static constexpr bool is_modulo = false;
		static constexpr int digits = CHAR_BIT * sizeof(long long) -1;
		static constexpr int digits10 = 18;
		static constexpr int max_digits10 = 0;
		static constexpr int radix = 2;
		static constexpr int min_exponent = 0;
		static constexpr int min_exponent10 = 0;
		static constexpr int max_exponent = 0;
		static constexpr int max_exponent10 = 0;
		static constexpr bool traps = true;
		static constexpr bool tinyness_before = false;
		static constexpr T min() noexcept {
			return LLONG_MIN;
		}
		static constexpr T lowest() noexcept {
			return LLONG_MIN;
		}
		static constexpr T max() noexcept {
			return LLONG_MAX;
		}
		static T epsilon() {
			return 0;
		}
		static constexpr T round_error() noexcept {
			return 0;
		}
		static constexpr T infinity() noexcept {
			return 0;
		}
		static constexpr T quiet_NaN() noexcept {
			return 0;
		}
		static constexpr T signaling_NaN() noexcept {
			return 0;
		}
		static constexpr T denorm_min() noexcept {
			return 0;
		}
	};
	template<> struct numeric_limits<unsigned long long> {
		using T = unsigned long long;
		static constexpr bool is_specialized = true;
		static constexpr bool is_signed = false;
		static constexpr bool is_integer = true;
		static constexpr bool is_exact = true;
		static constexpr bool has_infinity = false;
		static constexpr bool has_quiet_NaN = false;
		static constexpr bool has_signaling_NaN = false;
		static constexpr vd::float_denorm_style has_denorm = vd::denorm_absent;
		static constexpr bool has_denorm_loss = false;
		static constexpr vd::float_round_style round_style = vd::round_toward_zero;
		static constexpr bool is_iec559 = false;
		static constexpr bool is_bounded = true;
		static constexpr bool is_modulo = true;
		static constexpr int digits = CHAR_BIT * sizeof(long long);
		static constexpr int digits10 = 19;
		static constexpr int max_digits10 = 0;
		static constexpr int radix = 2;
		static constexpr int min_exponent = 0;
		static constexpr int min_exponent10 = 0;
		static constexpr int max_exponent = 0;
		static constexpr int max_exponent10 = 0;
		static constexpr bool traps = true;
		static constexpr bool tinyness_before = false;
		static constexpr T  min() noexcept {
			return 0;
		}
		static constexpr T lowest() noexcept {
			return 0;
		}
		static constexpr T max() noexcept {
			return 	ULLONG_MAX;
		}
		static T epsilon() {
			return 0;
		}
		static constexpr T round_error() noexcept {
			return 0;
		}
		static constexpr T infinity() noexcept {
			return 0;
		}
		static constexpr T quiet_NaN() noexcept {
			return 0;
		}
		static constexpr T signaling_NaN() noexcept {
			return 0;
		}
		static constexpr T denorm_min() noexcept {
			return 0;
		}
	};
	template<> struct numeric_limits<float> {
		using T = float;
		static constexpr bool is_specialized = true;
		static constexpr bool is_signed = true;
		static constexpr bool is_integer = false;
		static constexpr bool is_exact = false;
		static constexpr bool has_infinity = true;
		static constexpr bool has_quiet_NaN = true;
		static constexpr bool has_signaling_NaN = true;
		static constexpr vd::float_denorm_style has_denorm = vd::denorm_present;
		static constexpr bool has_denorm_loss = FLOATING_DENORM_LOSS;
		static constexpr vd::float_round_style round_style = vd::round_to_nearest;
		static constexpr bool is_iec559 = true;
		static constexpr bool is_bounded = true;
		static constexpr bool is_modulo = false;
		static constexpr int digits = FLT_MANT_DIG;
		static constexpr int digits10 =	FLT_DIG /* 6 for IEEE float */;
		static constexpr int max_digits10 = FLT_DECIMAL_DIG;
		static constexpr int radix =	FLT_RADIX;
		static constexpr int min_exponent = FLT_MIN_EXP;
		static constexpr int min_exponent10 =	FLT_MIN_10_EXP;
		static constexpr int max_exponent = FLT_MAX_EXP;
		static constexpr int max_exponent10 =	FLT_MAX_10_EXP;
		static constexpr bool traps = false;
		static constexpr bool tinyness_before = false;
		static constexpr T min() noexcept {
			return FLT_MIN;
		}
		static constexpr T lowest() noexcept {
			return -FLT_MAX;
		}
		static constexpr T max() noexcept {
			return FLT_MAX;
		}
		static T epsilon() {
			return FLT_EPSILON;
		}
		static constexpr T round_error() noexcept {
			return 0.5f;
		}
		static constexpr T infinity() noexcept {
			return HUGE_VALF;
		}
		static constexpr T quiet_NaN() noexcept {
			return NANF;
		}
		static constexpr T signaling_NaN() noexcept {
			return NANSF;
		}
		static constexpr T denorm_min() noexcept {
			return FLT_TRUE_MIN;
		}
	};
	template<> struct numeric_limits<double> {
		using T = double;
		static constexpr bool is_specialized = true;
		static constexpr bool is_signed = true;
		static constexpr bool is_integer = false;
		static constexpr bool is_exact = false;
		static constexpr bool has_infinity = true;
		static constexpr bool has_quiet_NaN = true;
		static constexpr bool has_signaling_NaN = true;
		static constexpr vd::float_denorm_style has_denorm = vd::denorm_present;
		static constexpr bool has_denorm_loss = FLOATING_DENORM_LOSS;
		static constexpr vd::float_round_style round_style = vd::round_to_nearest;
		static constexpr bool is_iec559 = true;
		static constexpr bool is_bounded = true;
		static constexpr bool is_modulo = false;
		static constexpr int digits =	DBL_MANT_DIG;
		static constexpr int digits10 = DBL_DIG /* 15 for IEEE double */;
		static constexpr int max_digits10 = DBL_DECIMAL_DIG ;
		static constexpr int radix =	FLT_RADIX;
		static constexpr int min_exponent = DBL_MIN_EXP;
		static constexpr int min_exponent10 = DBL_MIN_10_EXP;
		static constexpr int max_exponent = DBL_MAX_EXP;
		static constexpr int max_exponent10 =	DBL_MAX_10_EXP;
		static constexpr bool traps = false;
		static constexpr bool tinyness_before = false;
		static constexpr T min() noexcept {
			return DBL_MIN;
		}
		static constexpr T lowest() noexcept {
			return -DBL_MAX;
		}
		static constexpr T max() noexcept {
			return DBL_MAX;
		}
		static T epsilon() {
			return 	DBL_EPSILON;
		}
		static constexpr T round_error() noexcept {
			return 0.5;
		}
		static constexpr T infinity() noexcept {
			return HUGE_VAL;
		}
		static constexpr T quiet_NaN() noexcept {
			return NAN;
		}
		static constexpr T signaling_NaN() noexcept {
			return NANS;
		}
		static constexpr T denorm_min() noexcept {
			return DBL_TRUE_MIN;
		}
	};
	template<> struct numeric_limits<long double> {
		using T = long double;
		static constexpr bool is_specialized = true;
		static constexpr bool is_signed = true;
		static constexpr bool is_integer = false;
		static constexpr bool is_exact = false;
		static constexpr bool has_infinity = true;
		static constexpr bool has_quiet_NaN = true;
		static constexpr bool has_signaling_NaN = true;
		static constexpr vd::float_denorm_style has_denorm = vd::denorm_present;
		static constexpr bool has_denorm_loss = FLOATING_DENORM_LOSS;
		static constexpr vd::float_round_style round_style = vd::round_to_nearest;
		static constexpr bool is_iec559 = true;
		static constexpr bool is_bounded = true;
		static constexpr bool is_modulo = false;
		static constexpr int digits =	LDBL_MANT_DIG;
		static constexpr int digits10 = LDBL_DIG /* 18 for 80-bit Intel long double */;
		static constexpr int max_digits10 = DBL_DECIMAL_DIG;
		static constexpr int radix =	FLT_RADIX;
		static constexpr int min_exponent =	LDBL_MIN_EXP;
		static constexpr int min_exponent10 = LDBL_MIN_10_EXP;
		static constexpr int max_exponent =	LDBL_MAX_EXP;
		static constexpr int max_exponent10 = LDBL_MAX_10_EXP;
		static constexpr bool traps = false;
		static constexpr bool tinyness_before = false;
		static constexpr T min() noexcept {
			return LDBL_MIN;
		}
		static constexpr T lowest() noexcept {
			return -LDBL_MAX;
		}
		static constexpr T max() noexcept {
			return LDBL_MAX;
		}
		static T epsilon() {
			return LDBL_EPSILON;
		}
		static constexpr T round_error() noexcept {
			return 0.5l;
		}
		static constexpr T infinity() noexcept {
			return 	HUGE_VALL;
		}
		static constexpr T quiet_NaN() noexcept {
			return NANL;
		}
		static constexpr T signaling_NaN() noexcept {
			return NANSL;
		}
		static constexpr T denorm_min() noexcept {
			return LDBL_TRUE_MIN;
		}
	};
}