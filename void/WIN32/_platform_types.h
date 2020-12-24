#pragma once
#ifndef COMPATIBILITY_H
	#error Do not include '<Arch>/_types.h' files directly, use 'platform_specific.h' instead.
#endif
#include <stdint.h>
//#include <stddef.h>
#ifdef _VOID_SAFE_INTEGERS
#ifndef _VOID_NATIVE_CPP17_SUPPORT
	#error Compiler must support C++17 standart for _VOID_SAFE_INTEGERS directive.
#endif
#include <boost/safe_numerics/cpp.hpp>
#include <boost/safe_numerics/safe_integer.hpp>
#include <boost/safe_numerics/exception.hpp>
#include <boost/safe_numerics/exception_policies.hpp>
#include <boost/safe_numerics/safe_integer_range.hpp>
#include <boost/safe_numerics/safe_integer_literal.hpp>
namespace vd {

	using promotion_avr = boost::safe_numerics::cpp <
	                      8,  // char      8 bits
	                      16, // short     16 bits
	                      16, // int       16 bits
	                      32, // long      32 bits
	                      64  // long long 32 bits
	                      >;
	using promotion_stm8 = boost::safe_numerics::cpp <
	                       8,  // char      8 bits //????
	                       16, // short     16 bits
	                       16, // int       16 bits
	                       32, // long      32 bits
	                       64  // long long 32 bits
	                       >;
//chose target promotion rules
#if defined(_TARGET_AVR)
	using promotion = promotion_avr;
#elif defined(_TARGET_STM8)
	using promotion = promotion_stm8;
#else
	using promotion = boost::safe_numerics::native;
#endif

	template <typename T> // T is char, int, etc data type
	using safe_avr_t = boost::safe_numerics::safe<T, vd::promotion_avr>;
	template <typename T> // T is char, int, etc data type
	using safe_stm8_t = boost::safe_numerics::safe<T, vd::promotion_stm8>;
}
template <typename T> // T is char, int, etc data type
using safe_t =
    boost::safe_numerics::safe<T, vd::promotion, boost::safe_numerics::default_exception_policy>;

/*
using u08 = safe_t<uint8_t>;
using u16 = safe_t<uint16_t>;
using u32 = safe_t<uint32_t>;
using u64 = safe_t<uint64_t>;
using s08 = safe_t<int8_t>;
using s16 = safe_t<int16_t>;
using s32 = safe_t<int32_t>;
using s64 = safe_t<int64_t>;
*/
#define safe_literal_avr(x) make_safe_literal(x, vd::promotion_avr, boost::safe_numerics::default_exception_policy)
#define safe_literal_stm8(x) make_safe_literal(x, vd::promotion_stm8, boost::safe_numerics::default_exception_policy)
#define safe_literal(x) make_safe_literal(x, vd::promotion, boost::safe_numerics::default_exception_policy)

#endif
typedef uint8_t		u08;
typedef uint16_t	u16;
typedef uint32_t	u32;
typedef uint64_t	u64;
typedef int8_t		s08;
typedef int16_t		s16;
typedef int32_t		s32;
typedef int64_t		s64;
#define literal(x) x
/*
#ifndef _VOID_NULLPTR_SUPPORT
#define nullptr (0) //no support for nullptr
#endif*/
