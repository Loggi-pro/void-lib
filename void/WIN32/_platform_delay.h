#pragma once
//Win32
//#include <platform_specific.h> for types
#ifndef COMPATIBILITY_H
	#error Do not include '<Arch>/_delay.h' files directly, use 'delay.h' instead.
#endif
#undef _MSC_EXTENSIONS
#undef LOWORD
#undef HIWORD
#undef LOBYTE
#undef HIBYTE
#include "windows.h"
namespace vd {
namespace Private {

enum {
	PlatformCyclesPerDelayLoop32 = 1,
	PlatformCyclesPerDelayLoop16 = 1,
	PlatformCyclesPerDelayLoop8 = 1
};
enum {
	PlatformCyclesPerCall32 = 0,
	PlatformCyclesPerCall16 = 0,
	PlatformCyclesPerCall8 = 0
};
inline void delaySeconds( double seconds ) {
	int64_t timeEllapsed;
	int64_t timeStart;
	int64_t timeDelta;
	QueryPerformanceFrequency( (LARGE_INTEGER*)(&timeDelta ) );
	QueryPerformanceCounter ( (LARGE_INTEGER*)(&timeStart ) );
	int64_t timeToWait = (int64_t) ((double)timeDelta * (double)seconds);
	timeEllapsed = timeStart;

	while ( ( timeEllapsed - timeStart ) < timeToWait ) {
		QueryPerformanceCounter( (LARGE_INTEGER*)(&timeEllapsed ) );
	};
}
inline void delayMiliSeconds( double miliseconds ) {
	int64_t timeEllapsed;
	int64_t timeStart;
	int64_t timeDelta;
	QueryPerformanceFrequency( (LARGE_INTEGER*)(&timeDelta ) );
	int64_t timeToWait = (int64_t) ((double)timeDelta * (double)miliseconds /1000.0);
	QueryPerformanceCounter ( (LARGE_INTEGER*)(&timeStart ) );
	timeEllapsed = timeStart;

	while ( ( timeEllapsed - timeStart ) < timeToWait ) {
		QueryPerformanceCounter( (LARGE_INTEGER*)(&timeEllapsed ) );
	};
}
inline void delayMicroSeconds( double microseconds ) {
	int64_t timeEllapsed;
	int64_t timeStart;
	int64_t timeDelta;
	QueryPerformanceFrequency( (LARGE_INTEGER*)(&timeDelta ) );
	int64_t timeToWait = (int64_t ) ((double)timeDelta * (double)microseconds /1000000.0);
	QueryPerformanceCounter ( (LARGE_INTEGER*)(&timeStart ) );
	timeEllapsed = timeStart;

	while ( ( timeEllapsed - timeStart ) < timeToWait ) {
		QueryPerformanceCounter( (LARGE_INTEGER*)(&timeEllapsed ) );
	};
}

template <uint32_t CpuFreq>
void DelayLoop(uint32_t delayLoops) {
	double time = (double)delayLoops / (double)CpuFreq;

	if (time >= 1) {
		delaySeconds(time);
	} else if (time >= 0.001) {
		delayMiliSeconds(time * 1000);
	} else {
		delayMicroSeconds(time * 1000000);
	}
}

template <uint32_t CpuFreq>
inline void PlatformDelayCycle32(uint32_t delayLoops) {
	DelayLoop<CpuFreq>(delayLoops);
}

template <uint32_t CpuFreq>
inline void PlatformDelayCycle16(uint16_t delayLoops) {
	DelayLoop<CpuFreq>(delayLoops);
}
template <uint32_t CpuFreq>
inline void PlatformDelayCycle8(uint8_t delayLoops) {
	DelayLoop<CpuFreq>(delayLoops);
}


}
}