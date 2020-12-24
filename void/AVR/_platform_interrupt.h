#pragma once
//#include <platform_specific.h> for types
#ifndef COMPATIBILITY_H
	#error Do not include '<Arch>/_platform_interrupt.h' files directly, use 'interrupt.h' instead.
#endif
#include <avr/interrupt.h>

#ifdef __INTELLISENSE__
	#define VOID_ISR(x) void _isr_function_##x(void) //for workaround INTELLISENSE check
#else
	#define VOID_ISR(x) ISR(x)
#endif


namespace vd {

	namespace Private {

		typedef uint32_t TControlRegType;
		inline void DisableInterrupts() {
			cli();
		}

		inline void EnableInterrupts() {
			sei();
		}

		inline TControlRegType getControlReg() {
			return SREG;
		}

		inline void restoreControlReg(const TControlRegType* s) {
			SREG = (uint8_t) * s;
		}


	}
}
