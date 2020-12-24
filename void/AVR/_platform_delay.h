#pragma once
//#include <platform_specific.h> for types
#ifndef COMPATIBILITY_H
	#error Do not include '<Arch>/_platform_delay.h' files directly, use 'delay.h' instead.
#endif
namespace vd {
	namespace Private {
#ifdef __AVR__ //GCC
enum
{	
	PlatformCyclesPerDelayLoop32 = 6,	
	PlatformCyclesPerDelayLoop16 = 4,	
	PlatformCyclesPerDelayLoop8 = 3
};
enum {
	PlatformCyclesPerCall32 = 0,
	PlatformCyclesPerCall16 = 0,
	PlatformCyclesPerCall8 = 0
};
template <uint32_t CpuFreq>
inline void PlatformDelayCycle32(uint32_t delayLoops)
{		
	__asm volatile (
		"1: subi %A0, 1" "\n\t"
		"sbci %B0, 0"  "\n\t"
		"sbci %C0, 0"  "\n\t"
		"sbci %D0, 0"  "\n\t"
		"brne 1b"
		: "+d" (delayLoops)
	);
}
template <uint32_t CpuFreq>
inline void PlatformDelayCycle16(uint16_t delayLoops)
{	
	__asm volatile (
		"1: sbiw %0,1" "\n\t"
		"brne 1b"
		: "=w" (delayLoops)
		: "0" (delayLoops)
	);
}
template <uint32_t CpuFreq>
inline void PlatformDelayCycle8(uint8_t delayLoops)
{
	__asm volatile (
		"1: dec %0" "\n\t"
		"brne 1b"
		: "=r" (delayLoops)
		: "0" (delayLoops)	
	);
}
#elif defined(__ICCAVR__)

#include <intrinsics.h>
enum
{	
	PlatformCyclesPerDelayLoop32 = 1,	
	PlatformCyclesPerDelayLoop16 = 1,	
	PlatformCyclesPerDelayLoop8 = 1
};
enum {
	PlatformCyclesPerCall32 = 0,
	PlatformCyclesPerCall16 = 0,
	PlatformCyclesPerCall8 = 0
};
template <uint32_t CpuFreq>
inline void PlatformDelayCycle32(uint32_t delayLoops)
{	
	__delay_cycles(delayLoops); 
}
template <uint32_t CpuFreq>
inline void PlatformDelayCycle16(uint16_t delayLoops)
{	
	__delay_cycles(delayLoops); 
}
template <uint32_t CpuFreq>
inline void PlatformDelayCycle8(uint8_t delayLoops)
{
	__delay_cycles(delayLoops); 
}
#endif

	}
}