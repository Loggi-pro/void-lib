#pragma once
#include <void/static_assert.h>
#include <void/type_traits.h>
#include <void/limits.h>
#include <stdint.h>
#include <math.h>
#ifdef _WIN32
	
	#include <cmath>
#endif

#ifdef abs
	#undef abs
#endif

#ifdef min
	#undef min
#endif

#ifdef max
	#undef max
#endif
#ifndef M_PI
#define M_PI   3.141592653589793238462643
#endif

namespace vd {

#ifdef VOID_COMPILER_GCC

	#undef fma
	#undef fmaf
	#undef fmal
	#undef fmax
	#undef fmaxf
	#undef fmaxl
	#undef isnan

	#ifdef isnormal
		#undef isnormal
	#endif
	constexpr bool isnormal(float __x) {
		return __builtin_isnormal(__x);
	}
	constexpr bool isnormal(long double __x) {
		return __builtin_isnormal(__x);
	}


	constexpr bool isnormal(double __x) {
		return __builtin_isnormal(__x);
	}

	constexpr float fma(float __x, float __y, float __z) {
		return __builtin_fmaf(__x, __y, __z);
	}

	constexpr long double fma(long double __x, long double __y, long double __z)
	{ return __builtin_fmal(__x, __y, __z); }

	constexpr bool isnan(float __x)
	{ return __builtin_isnan(__x); }

	constexpr bool
	isnan(double __x)
	{ return __builtin_isnan(__x); }

	constexpr bool
	isnan(long double __x)
	{ return __builtin_isnan(__x); }
#elif defined(VOID_COMPILER_MSVC)

	#undef fma
	#undef fmaf
	#undef fmal
	#undef fmax
	#undef fmaxf
	#undef fmaxl
	#undef isnan

	#ifdef isnormal
		#undef isnormal
	#endif
	#define MAKE_ALIAS_TO(X)\
		template <typename... Args>\
		constexpr auto X(Args&& ... args) -> decltype(std::X(std::forward<Args>(args)...)) {\
			return std::X(std::forward<Args>(args)...);\
		}
		MAKE_ALIAS_TO(isnan);
		MAKE_ALIAS_TO(isnormal);
	#undef MAKE_ALIAS_TO
#endif



	template <uint64_t Arg, unsigned Base>
	struct Log {
		static const int  value = Log < Arg / Base, Base >::value + 1;
	};

	template <unsigned Base>
	struct Log<1, Base> {
		static const int value = 0;
	};

	template <unsigned Base>
	struct Log<0, Base> {
		static const int value = -1;
	};

	template<uint64_t num, unsigned pow>
	struct Pow {
		static const uint64_t value = num * Pow < num, pow - 1 >::value;
	};

	template<uint64_t num>
	struct Pow<num, 0> {
		static const uint64_t value = 1u;
	};

	template<class T>
	struct MinValue {
		static const T value = vd::numeric_limits<T>::is_signed ? ( T(1) << (sizeof(T) * 8 - 1)) : 0;
	};

	template<class T>
	struct MaxValue {
		static const T value = ~MinValue<T>::value;
	};

	template<class T, unsigned Base>
	struct MaxPowerOf {
		static const T value = Pow<Base, Log<MaxValue<T>::value, Base>::value>::value;
	};

	template<class T>
	struct Unsigned {
		typedef T Result;
	};

	template<class T>
	struct Signed {
		typedef T Result;
	};

	template<> struct Unsigned<int> {typedef unsigned int Result;};
	template<> struct Unsigned<char> {typedef unsigned char Result;};
	template<> struct Unsigned<signed char> {typedef unsigned char Result;};
	template<> struct Unsigned<long> {typedef unsigned long Result;};
	template<> struct Unsigned<short> {typedef unsigned short Result;};
	template<> struct Unsigned<long long> {typedef unsigned long long Result;};

	template<> struct Signed<unsigned int> {typedef int Result;};
	template<> struct Signed<unsigned char> {typedef char Result;};
	template<> struct Signed<unsigned long> {typedef long Result;};
	template<> struct Signed<unsigned short> {typedef short Result;};
	template<> struct Signed<unsigned long long> {typedef long long Result;};

	template<class T>
	constexpr const T& max(const T& a, const T& b) {
		return (a < b) ? b : a;
	}

	template<class T, class Compare>
	constexpr const T& max(const T& a, const T& b, Compare comp) {
		return (comp(a, b)) ? b : a;
	}

	template<class T>
	constexpr const T& min(const T& a, const T& b) {
		return (b < a) ? b : a;
	}
	template<class T, class Compare>
	constexpr const T& min(const T& a, const T& b, Compare comp) {
		return (comp(b, a)) ? b : a;
	}

	//template<class T> T (max)(T a, T b) {return a > b ? a : b;}
	//template<class T> T (min)(T a, T b) {return a > b ? b : a;}
	template<class T> T (sqr)(T a) {return a * a;}

	template<bool isSigned> struct NegativeHelper {
		template<class T> static bool IsNegative(T v) {return v < 0;}
	};

	template<> struct NegativeHelper<false> {
		template<class T> static bool IsNegative(T) {return false;}
	};

	template<class T> static inline bool (IsNegative)(T v) {
		return NegativeHelper<vd::numeric_limits<T>::is_signed>::IsNegative(v);
	}

	template<bool Signed> struct AbsHelper {
		template<class T> static T Abs(T value) {return value >= T(0) ? value : -value;}
	};
	template<> struct AbsHelper<false> {
		template<class T> static T Abs(T value) {return value;}
	};

	namespace Private {
		template<typename T>
		using notIsFloating = vd::enable_if_t<vd::is_integral_v<T>>;
	}
	template<class T, typename = Private::notIsFloating<T>>
	T Abs(T a) {
		return AbsHelper< vd::numeric_limits<T>::is_signed>::Abs(a);
	}
	#ifndef _WIN32
	inline float Abs(float a) {
		union FloatToInt {
			float f;
			uint32_t i;
		} fi;
		fi.f = a;
		fi.i &= 0x7fffffff;
		return fi.f;
	}
	#else
	template<typename T>
	inline T Abs(T a) {
		return ::abs(a);
	}

	#endif



	template<class T>
	constexpr inline uint8_t ilog2 (T x) {
		int8_t res = -1;

		do {
			res++;
		} while (x >>= 1);

		return res;
	}
	#ifndef _WIN32
	inline uint32_t sqrt(uint32_t value) {
		uint32_t result = 0;
		uint32_t add = 0x8000;

		for (int i = 0; i < 16; i++) {
			uint32_t rootGuess = result | add;
			uint32_t guess = rootGuess * rootGuess;

			if (value >= guess) {
				result = rootGuess;
			}

			add >>= 1;
		}

		return result;
	}

	inline int32_t sqrt(int32_t value) {
		return sqrt((uint32_t)value);
	}


	inline float sqrt(float value) {
		VOID_STATIC_ASSERT(sizeof(float) == 4);
		const uint32_t InitialGuessConstant = (1ul << 29) - (1ul << 22);
		union FloatToInt {
			float f;
			uint32_t i;
		} fToInt;
		fToInt.f = value;
		fToInt.i &= 0x7ffffffful;
		fToInt.i = InitialGuessConstant + (fToInt.i >> 1);
		float guess = fToInt.f;
		guess = 0.5f * (guess + value / guess);
		guess = 0.5f * (guess + value / guess);
		return guess;
	}
	#else
	inline float sqrt(float x) noexcept {
		return ::sqrtf(x);
	}
	inline  double sqrt(double x) noexcept {
		return ::sqrt(x);
	}
	inline long double sqrt(long double x) noexcept {
		return ::sqrt(x);
	}
	template<typename T>
	double sqrt(T x) noexcept {
		return ::sqrt(x);
	}

	#endif
	namespace Private {
		template <typename T>
		using IsSigned = vd::enable_if_t < !vd::numeric_limits<T>::is_signed >;
	}
	template <typename T, typename = Private::IsSigned<T>>
	T sat_add(T x, T y) {
		T res = static_cast<T>(x + y);
		res |= static_cast<T>(-(res < x));
		return res;
	}
	template <typename T, typename = Private::IsSigned<T>>
	T sat_sub(T x, T y) {
		T res = static_cast<T>(x - y);
		res &= static_cast<T>(-(res <= x));
		return res;
	}


}
