/* Header to define cxx abi parts missing from avrlibc */
#pragma once
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
__extension__ typedef int __guard __attribute__((mode (__DI__)));

inline char& flag_part(__guard *g) {
    return *(reinterpret_cast<char*>(g));
}

inline uint8_t& sreg_part(__guard *g) {
    return *(reinterpret_cast<uint8_t*>(g) + sizeof(char));
}

extern "C" {
	



inline int __cxa_guard_acquire(__guard *g) {
    uint8_t oldSREG = SREG;
    cli();
    // Initialization of static variable has to be done with blocked interrupts
    // because if this function is called from interrupt and sees that somebody
    // else is already doing initialization it MUST wait until initializations
    // is complete. That's impossible.
    // If you don't want this overhead compile with -fno-threadsafe-statics
    if (flag_part(g)) { //inited
        SREG = oldSREG; //return interrupt state
        return false;
    } else {
        sreg_part(g) = oldSREG;
        return true;
    }
}

inline void __cxa_guard_release (__guard *g) {
    flag_part(g) = 1;
    SREG = sreg_part(g);
}

inline void __cxa_guard_abort (__guard *g) {
    SREG = sreg_part(g);
}

inline void __cxa_pure_virtual(void) {
    // We might want to write some diagnostics to uart in this case
    //std::terminate();
}

inline void __cxa_deleted_virtual(void) {
    // We might want to write some diagnostics to uart in this case
    //std::terminate();
}

}