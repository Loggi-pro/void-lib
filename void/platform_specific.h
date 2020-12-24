#pragma once
#ifndef COMPATIBILITY_H
	#define COMPATIBILITY_H
#endif



#ifdef __cplusplus
	#include "COMMON/_compiler.h"
	#ifdef _AVR
		#define IS_LITTLE_ENDIAN
		#include "COMMON/_common_types.h"
		#include "AVR/_platform_abi.h"
		#include "AVR/_platform_compiler.h"
		#include "AVR/_platform_limits.h"
		#include "AVR/_platform_interrupt.h"
		#include "COMMON/_common_atomic.h"
		#include "AVR/_platform_atomic.h"
		#include "AVR/_platform_packed.h"
		#include "AVR/_platform_delay.h"
		#include "AVR/_platform_assert.h"
	#elif (defined (WIN32) || defined(WIN64) )
		#define IS_LITTLE_ENDIAN
		#ifndef F_CPU
			#define F_CPU 1
		#endif
		#include "WIN32/_platform_types.h"
		#include "WIN32/_platform_interrupt.h"
		#include "COMMON/_common_atomic.h"
		#include "WIN32/_platform_atomic.h"
		#include "WIN32/_platform_delay.h"
		#include "WIN32/_platform_packed.h"
		#include "WIN32/_platform_assert.h"
		#include "WIN32/_platform_limits.h"
	#elif defined(_ARM)
		#define IS_LITTLE_ENDIAN
		#include "COMMON/_common_types.h"
		#include "ARM/_device.h"
		#include "ARM/_platform_interrupt.h"
		#include "COMMON/_common_atomic.h"
		#include "ARM/_platform_atomic.h"
		#include "ARM/_platform_packed.h"
		#include "ARM/_platform_delay.h"
		#include "ARM/_platform_assert.h"
		#include "ARM/_platform_limits.h"
	#elif defined(_STM8)
		#define IS_BIG_ENDIAN
		#include "COMMON/_common_types.h"
		#include "STM8/_platform_limits.h" //NYI
		#include "STM8/_platform_interrupt.h"
		#include "STM8/_platform_packed.h"
		#include "STM8/_platform_delay.h"
	#else
		#error NO_ARCHITECTURE_DEFINED: _AVR/_ARM/WIN32/_STM8
	#endif
	#include "COMMON/_concat.h"
	#include "COMMON/_types_support.h"
	#include "COMMON/_littlebigendian_types.h" //after packed
	#include "COMMON/_comparators.h" //any_of, all_of,none_of
#endif

