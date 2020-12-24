#pragma once
namespace vd {
	namespace Private {
#if defined(__GNUC__)	// gcc compiler
inline void DelayLoop(uint32_t delayLoops)
{
	__asm__ __volatile__
	(
		"1: \n"
		" CBZ %[delayLoops], 2f \n"
		" SUB %[delayLoops], %[delayLoops], #1 \n"
		" B 1b \n"
		"2: \n"
		: [delayLoops] "+l"(delayLoops)
	);
}

enum
{	
	PlatformCyclesPerDelayLoop32 = 4,
	PlatformCyclesPerDelayLoop16 = 4,
	PlatformCyclesPerDelayLoop8 = 4
};
enum {
	PlatformCyclesPerCall32 = 0,
	PlatformCyclesPerCall16 = 0,
	PlatformCyclesPerCall8 = 0
};
#elif defined(__ICCARM__)	// IAR compiler
#include <intrinsics.h>

inline void DelayLoop(uint32_t delayLoops)
{
	do
	{
	// TODO: rewrite in assembly
	 // __no_operation();
	}while(delayLoops--);
}	
enum
{	
	PlatformCyclesPerDelayLoop32 = 4,
	PlatformCyclesPerDelayLoop16 = 4,
	PlatformCyclesPerDelayLoop8 = 4
};
enum {
	PlatformCyclesPerCall32 = 0,
	PlatformCyclesPerCall16 = 0,
	PlatformCyclesPerCall8 = 0
};
#elif defined ( __CC_ARM   ) // ARM (RealView) compiler
inline void DelayLoop(uint32_t delayLoops)
{
	__asm{
		start:
		SUBS     delayLoops,delayLoops,#1	// 1
		BCS      start						// 1+2
	}
}
enum
{	
	PlatformCyclesPerDelayLoop32 = 4,
	PlatformCyclesPerDelayLoop16 = 4,
	PlatformCyclesPerDelayLoop8 = 4
};
enum {
	PlatformCyclesPerCall32 = 0,
	PlatformCyclesPerCall16 = 0,
	PlatformCyclesPerCall8 = 0
};
#else
#error Not supported compiler
#endif

template <uint32_t CpuFreq>
inline void PlatformDelayCycle16(uint16_t delayLoops) 
{
	DelayLoop(delayLoops);
}
template <uint32_t CpuFreq>
inline void PlatformDelayCycle8(uint8_t delayLoops)
{
	DelayLoop(delayLoops);
}
template <uint32_t CpuFreq>
inline void PlatformDelayCycle32(uint32_t delayLoops)
{
	DelayLoop(delayLoops);
}

}
}