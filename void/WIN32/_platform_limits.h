#pragma once
	#include <cfloat>

	#ifndef NANF
		#define NANF (__builtin_nanf("0"))
	#endif
	#ifndef NAN
		#define NAN (__builtin_nan("0"))
	#endif
	#ifndef NANL
		#define NANL (__builtin_nan("0"))
	#endif

	#ifndef NANSF
		#define NANSF (__builtin_nansf("1"))
	#endif
	#ifndef NANS
		#define NANS (__builtin_nans("1"))
	#endif
	#ifndef NANSL
		#define NANSL (__builtin_nans("1"))
	#endif

	#ifdef VOID_COMPILER_GCC

		#define FLT_DECIMAL_DIG __FLT_DECIMAL_DIG__
		#define DBL_DECIMAL_DIG		__DBL_DECIMAL_DIG__
		#define LDBL_DECIMAL_DIG	__LDBL_DECIMAL_DIG__
		#define FLT_TRUE_MIN	__FLT_DENORM_MIN__
		#define DBL_TRUE_MIN	__DBL_DENORM_MIN__
		#define LDBL_TRUE_MIN	__LDBL_DENORM_MIN__

	#endif