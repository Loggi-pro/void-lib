#pragma once
#include "static_strings.h"
namespace vd {
	
template <class T, const char* name>
struct NamedType {
	T value;
	static const char* getName() {
		return name;
	}
};

//Usage NamedType<int, FLASH_STRING("Param")> var1 = { 3 };
//var1.getName()

	
	
}