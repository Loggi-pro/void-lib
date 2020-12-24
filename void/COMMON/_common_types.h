#pragma once
#ifndef COMPATIBILITY_H
	#error Do not include '<Arch>/_common_types.h' files directly, use 'platform_specific.h' instead.
#endif
#include <stddef.h> //for size_t
#include <stdint.h>

#ifndef _VOID_NULLPTR_SUPPORT
	#define nullptr (0) //no support for nullptr
#endif


#if defined (__ICCARM__) || defined(__ICCSTM8__)  //IAR SUPPORT
	typedef unsigned long long uint64_t;
	typedef signed long long int64_t;
	#define   _UINT64_T_DECLARED
#endif




/*!
	\defgroup basic_types Basic types
	\ingroup types
	\brief Basic types for platform declaration
	@{
	@file
*/
typedef signed int ptrdiff_t; //!< @brief pointer diff type
//Types
typedef uint8_t		u08;//!< unsigned byte
typedef uint16_t	u16;//!< unsigned word
typedef uint32_t	u32;//!< unsigned dword
typedef uint64_t	u64;//!< unsigned qword
typedef int8_t		s08;//!< signed byte
typedef int16_t		s16;//!< signed word
typedef int32_t		s32;//!< signed dword
typedef int64_t		s64;//!< signed qword
#define literal(x) x
//! @}
