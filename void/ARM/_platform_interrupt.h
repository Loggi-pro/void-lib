#pragma once
#include <void/platform_specific.h> //for types
#ifndef COMPATIBILITY_H
	#error Do not include '<Arch>/_platform_interrupt.h' files directly, use 'interrupt.h' instead.
#endif

namespace vd {

namespace Private {
typedef uint32_t TControlRegType;

	inline void DisableInterrupts() {
		__disable_irq();
	}
	inline void EnableInterrupts() {
	__enable_irq();
	}



inline TControlRegType getControlReg() {
	return __get_PRIMASK();
}

inline void restoreControlReg(const TControlRegType* s) {
	__set_PRIMASK(*s);
}


}


}