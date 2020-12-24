#pragma once
//Win32
//#include <platform_specific.h> for types
#ifndef COMPATIBILITY_H
	#error Do not include '<Arch>/_platform_assert.h' files directly, use 'assert.h' instead.
#endif

#include <stdio.h>
#include <process.h>

	#ifdef VOID_ASSERT_TRAP
	 extern void assert_failed(const char* filename, int line);
	 #else
	inline void assert_failed(const char* filename, int line){
		printf("Assertion failed, file '%s' line '%d'.",filename,line);abort();
	}
	#endif