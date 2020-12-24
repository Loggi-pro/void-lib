// Compiler compatibility header
#pragma once

#if defined(__ICCAVR__) // IAR for AVR
	#define ENABLE_BIT_DEFINITIONS
	#include <ioavr.h>
	#include <intrinsics.h>
	
static inline uint8_t ReadLowFuse()
{
	return _SPM_GET_FUSEBITS();
}

#elif defined(__AVR__) // avr-gcc
	#include <avr/io.h>
	
	#include <avr/interrupt.h>
	#include <avr/builtins.h>
	#include <avr/eeprom.h>

	#if defined(SPMCSR) || defined(SPMCR)
		#include <avr/boot.h>
		static inline uint8_t ReadLowFuse()
		{
			return boot_lock_fuse_bits_get(GET_LOW_FUSE_BITS);
		}
	#else
		
		static inline uint8_t ReadLowFuse()
		{
			return LFUSE_DEFAULT;
		}
	#endif
#else
	#error "Unknown compiler"
#endif