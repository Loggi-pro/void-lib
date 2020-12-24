#pragma once
//#include <platform_specific.h> for types
#ifndef COMPATIBILITY_H
	#error Do not include '<Arch>/_platform_packed.h' files directly, use 'platform_specific.h' instead.
#endif


#ifdef _MSC_VER
	#define _PACKED(__Declaration__ ) __pragma( pack(push, 1) ) __Declaration__; __pragma( pack(pop) )
#elif defined(__GNUC__)
	#define _PACKED( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#endif
