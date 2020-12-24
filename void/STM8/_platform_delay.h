#pragma once
//#include <platform_specific.h> for types
#ifndef COMPATIBILITY_H
	#error Do not include '<Arch>/_platform_delay.h' files directly, use 'delay.h' instead.
#endif

namespace vd {
namespace Private {
enum {
  PlatformCyclesPerDelayLoop32 = 6,
  PlatformCyclesPerDelayLoop16 = 4,
  PlatformCyclesPerDelayLoop8 = 3,
  PlatformCyclesPerCall32 = 0,	
PlatformCyclesPerCall16 = 0,	
PlatformCyclesPerCall8 = 0
};

template <uint32_t CpuFreq>
inline void PlatformDelayCycle32(uint32_t delayLoops)
{		
//?l10 - 32bit registers
  //?l1 -32bit registers
  
}
//LWRD(var) HWRD(var)
template <uint32_t CpuFreq>
inline void PlatformDelayCycle16(uint16_t delayLoops)
{	
  //X-16 bit register
	asm("PUSH CC\n" 				//1 ---
            "PUSHW X\n" 				//2 ---
              "LDW X,a\n" 	        //2 ---
            "Lable:\n" "NOP\n" 			//1
		"DECW X\n"  				//1
		"JRNE Lable\n" 				//2(1 on last)
		"POPW X\n" 					//2 ---
                  "POP CC\n"); 				//1 ---
		//8 on call
		//
}



template <uint32_t CpuFreq>
inline void PlatformDelayCycle8(uint8_t delayLoops)
{
  //A -8 bit register
	asm("PUSH CC\n" 				//1 ---
		"PUSH X\n" 					//1 ---
		"LD X,  delayLoops \n" 	//1 ---
		"Lable:\n" "DEC X\n"  		//1
		"JRNE Lable\n" 				//2(1 on last)
		"POP X\n" 					//1 ---
		"POP CC\n"); 				//1 ---
		//5-1 on call
		//
}


}
}

