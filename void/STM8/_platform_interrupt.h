#pragma once
//STM8
#ifndef COMPATIBILITY_H
	#error Do not include '<Arch>/_platform_interrupt.h' files directly, use 'interrupt.h' instead.
#endif

#ifdef __INTELLISENSE__
	#define VOID_ISR(x) void _isr_function_##x(void) //for workaround INTELLISENSE check
#else
        #define _VOID_STRINGVECTOR(x) #x
#define VOID_ISR(b)_Pragma( STRINGVECTOR( vector = (b+2) ) ) extern "C" __interrupt void _isr_function__##b( void )
#endif





namespace vd {

namespace Private {
#ifdef __ICCSTM8__ //IAR for STM8
#include <intrinsics.h>
typedef __istate_t TControlRegType;
inline void DisableInterrupts() {
	__disable_interrupt();
}

inline void EnableInterrupts() {
	__enable_interrupt();
}

inline TControlRegType getControlReg() {
	return __get_interrupt_state();
}

inline void restoreControlReg(const TControlRegType* s) {
	__set_interrupt_state(*s);
}
#endif

}
}
