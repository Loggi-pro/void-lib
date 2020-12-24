#pragma once

#ifndef COMPATIBILITY_H
	#error Do not include '<Arch>/_types.h' files directly, use 'platform_specific.h' instead.
#endif
#if ((__cplusplus >= 201103L) || (_MSC_VER >= 1900)) // C++ 11 implementation
	#define _VOID_NATIVE_CPP11_SUPPORT
	#define _VOID_NATIVE_CPP11_TYPES_SUPPORT
	#define _MB_CONSTEXPR constexpr
#endif
#if ((__cplusplus >= 201402L) || (_MSC_VER >= 1916)) // C++ 17 implementation
	#define _VOID_NATIVE_CPP17_SUPPORT
	#define _VOID_NATIVE_CPP17_CONSTEXPR_SUPPORT
	#define _VOID_NATIVE_CPP17_TYPES_SUPPORT

#endif

#ifdef __GNUC__
	#define VOID_COMPILER_GCC
#elif defined (_MSC_VER)
	#define VOID_COMPILER_MSVC
#endif


#ifndef _MB_CONSTEXPR
	#define _MB_CONSTEXPR
#endif
/*
#if ((defined(__ICCSTM8__) && (VER >= 800))||(_MSC_VER >= 1600) ||(__cplusplus >=201103L))
#define _VOID_NULLPTR_SUPPORT
#endif*/

