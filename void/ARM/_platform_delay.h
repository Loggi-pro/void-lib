#pragma once
//#include <platform_specific.h> for types
#ifndef COMPATIBILITY_H
	#error Do not include '<Arch>/_platform_delay.h' files directly, use 'delay.h' instead.
#endif


#if defined(__CORTEX_M3__)
	#include "CortexM4/_cortexm3_delay.h"
#elif defined(__CORTEX_M4__)
	#include "CortexM4/_cortexm4_delay.h"
#endif