#pragma once
//#include <platform_specific.h> for types
#ifndef COMPATIBILITY_H
	#error Do not include '<Arch>/_device.h' files directly, use 'platform_specific.h' instead.
#endif

#ifdef __STM32F303xC__
	#ifndef __CORTEX_M4__
	#define __CORTEX_M4__
	#endif
	#ifndef __CORTEXFAMILY_F3__
	#define __CORTEXFAMILY_F3__
	#endif
//#elif defined()

#endif