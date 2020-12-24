#pragma once
//#include <platform_specific.h> for types
#ifndef COMPATIBILITY_H
	#error Do not include '<Arch>/_platform_interrupt.h' files directly, use 'interrupt.h' instead.
#endif
#define VOID_ISR(x) void _isr_function_##x(void)



namespace vd {

namespace Private {
typedef uint32_t TControlRegType;
inline void DisableInterrupts() {
}

inline void EnableInterrupts() {
}

inline TControlRegType getControlReg() {
	return 0;
}

inline void restoreControlReg(const TControlRegType*) {
}


}
}