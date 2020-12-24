#pragma once
//#include "core_cm4.h"

namespace
{
	class DwtInitializer
	{
	public:
		DwtInitializer()
		{
			if (!(CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk)) 
			{
				CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
				DWT->CYCCNT = 0;
				DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
			}
		}
	};
	
	DwtInitializer dwtInitializer;
}

namespace vd {
	namespace Private {
		inline void DelayLoop(uint32_t delayLoops)
		{
			uint32_t start = DWT->CYCCNT;
			while(DWT->CYCCNT - start < delayLoops);
		}
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
	}
}

