#pragma once
//#include <platform_specific.h> for types
#ifndef COMPATIBILITY_H
	#error Do not include '<Arch>/_platform_packed.h' files directly, use 'platform_specific.h' instead.
#endif
//USING
//typedef PACKED_STRUCT() { short a; int b } my_struct_t;
//PACKED_SRUCT(my_other_struct) { short a; int b };

#define _PACKED(__declaration__)  __declaration__ __attribute__((packed))

