#pragma once
#include <void/platform_specific.h>
#include <void/chrono.h>
#ifndef F_CPU
	#error F_CPU not defined for void/delay.h
#endif




namespace vd {

	/*!
		\defgroup delay Delay
		\brief Delay functions
		\{
		@file
	*/
	//! \brief Delay for specified compile-known time
	template <class literalTime, uint32_t CpuFreq = F_CPU>
	void delay() {
		//	uint8_t us = _val = (d.count() * Period2::Num * Period::Denom) / (Period2::Denom * Period::Num);
		//const Duration < Private::Period_micro> dur(Duration<typename literalTime::PeriodInfo>
		//        (literalTime::static_value));
		const uint32_t delayLoops32 = (uint32_t)(CpuFreq / (1.0e6 *
		                              ::vd::Private::PlatformCyclesPerDelayLoop32) * literalTime::to_micro::static_value -
		                              ::vd::Private::PlatformCyclesPerCall32 / ::vd::Private::PlatformCyclesPerDelayLoop32);
		const uint32_t delayLoops16 = (uint32_t)(CpuFreq / (1.0e6 *
		                              ::vd::Private::PlatformCyclesPerDelayLoop16) * literalTime::to_micro::static_value -
		                              ::vd::Private::PlatformCyclesPerCall16 / ::vd::Private::PlatformCyclesPerDelayLoop16);
		const uint32_t delayLoops8 = (uint32_t)(CpuFreq / (1.0e6 *
		                                        ::vd::Private::PlatformCyclesPerDelayLoop8) * literalTime::to_micro::static_value -
		                                        ::vd::Private::PlatformCyclesPerCall8 / ::vd::Private::PlatformCyclesPerDelayLoop8);

		if (delayLoops16 > 0xFFFFul) {
			::vd::Private::PlatformDelayCycle32<CpuFreq>(delayLoops32);
		} else if (delayLoops8 > 0xFFul) {
			::vd::Private::PlatformDelayCycle16<CpuFreq>((uint16_t)delayLoops16);
		} else {
			if (delayLoops8 == 0) { return; } //TODO StaticAssert Here

			::vd::Private::PlatformDelayCycle8<CpuFreq>((uint8_t)delayLoops8);
		}
	}
	#ifdef _VOID_NATIVE_CPP17_CONSTEXPR_SUPPORT
	//! \brief Delay for specified compile-known time  (c++17)
	//! \code
	//! delay(1_sec);
	//! \endcode
	template <typename T>
	constexpr void delay(const T literal, uint32_t CpuFreq = F_CPU) {
		delay<T, F_CPU>();
	}
	#endif

	#ifdef _VOID_NATIVE_CPP11_SUPPORT
	//! \brief Delay for specified time (c++11)
	//! \code
	//! delay(vd::chrono::seconds(1));
	//! \endcode
	template <class Period, uint32_t CpuFreq = F_CPU>
	void delay(const ::vd::chrono::any_t<Period>& adur) {
		//	uint8_t us = _val = (d.count() * Period2::Num * Period::Denom) / (Period2::Denom * Period::Num);
		const ::vd::chrono::Duration<::vd::chrono::Private::Period_micro> dur(adur);
		const uint32_t delayLoops32 = (uint32_t)(CpuFreq / (1.0e6 *
		                              ::vd::Private::PlatformCyclesPerDelayLoop32) * dur.count() -
		                              ::vd::Private::PlatformCyclesPerCall32 / ::vd::Private::PlatformCyclesPerDelayLoop32);
		const uint32_t delayLoops16 = (uint32_t)(CpuFreq / (1.0e6 *
		                              ::vd::Private::PlatformCyclesPerDelayLoop16) * dur.count() -
		                              ::vd::Private::PlatformCyclesPerCall16 / ::vd::Private::PlatformCyclesPerDelayLoop16);
		const uint32_t delayLoops8 = (uint32_t)(CpuFreq / (1.0e6 *
		                                        ::vd::Private::PlatformCyclesPerDelayLoop8) * dur.count() -
		                                        ::vd::Private::PlatformCyclesPerCall8 / ::vd::Private::PlatformCyclesPerDelayLoop8);

		if (delayLoops16 > 0xFFFFul) {
			::vd::Private::PlatformDelayCycle32<CpuFreq>(delayLoops32);
		} else if (delayLoops8 > 0xFFul) {
			::vd::Private::PlatformDelayCycle16<CpuFreq>((uint16_t)delayLoops16);
		} else {
			if (delayLoops8 == 0) { return; } //TODO StaticAssert Here

			::vd::Private::PlatformDelayCycle8<CpuFreq>((uint8_t)delayLoops8);
		}
	}
	#endif
	//! \brief Delay for specified compile-known nanoseconds
	//! \code
	//! delay_ns<1000>();
	//! \endcode
	template<uint32_t ns, uint32_t CpuFreq = F_CPU>
	void delay_ns() {
		const uint32_t delayLoops32 = (uint32_t)(CpuFreq / (1.0e9 *
		                              ::vd::Private::PlatformCyclesPerDelayLoop32) * ns -
		                              ::vd::Private::PlatformCyclesPerCall32 / ::vd::Private::PlatformCyclesPerDelayLoop32);
		const uint32_t delayLoops16 = (uint32_t)(CpuFreq / (1.0e9 *
		                              ::vd::Private::PlatformCyclesPerDelayLoop16) * ns -
		                              ::vd::Private::PlatformCyclesPerCall16 / ::vd::Private::PlatformCyclesPerDelayLoop16);
		const uint32_t delayLoops8  = (uint32_t)(CpuFreq / (1.0e9 *
		                              ::vd::Private::PlatformCyclesPerDelayLoop8) * ns -
		                              ::vd::Private::PlatformCyclesPerCall8 / ::vd::Private::PlatformCyclesPerDelayLoop8);

		if (delayLoops16 > 0xFFFFul) {
			::vd::Private::PlatformDelayCycle32<CpuFreq>(delayLoops32);
		} else if (delayLoops8 > 0xFFul) {
			::vd::Private::PlatformDelayCycle16<CpuFreq>((uint16_t)delayLoops16);
		} else {
			if (delayLoops8 == 0) { return; }//TODO StaticAssert Here

			::vd::Private::PlatformDelayCycle8<CpuFreq>((uint8_t)delayLoops8);
		}
	}

	//! \brief Delay for specified compile-known micorseconds
	//! \code
	//! delay_us<1000>();
	//! \endcode
	template<uint32_t us, uint32_t CpuFreq = F_CPU>
	void delay_us() {
		const uint32_t delayLoops32 = (uint32_t)(CpuFreq / (1.0e6 *
		                              (uint32_t)::vd::Private::PlatformCyclesPerDelayLoop32) * us -
		                              (uint32_t)::vd::Private::PlatformCyclesPerCall32 / (uint32_t)
		                              ::vd::Private::PlatformCyclesPerDelayLoop32);
		const uint32_t delayLoops16 = (uint32_t)(CpuFreq / (1.0e6 *
		                              (uint32_t)::vd::Private::PlatformCyclesPerDelayLoop16) * us -
		                              (uint32_t)::vd::Private::PlatformCyclesPerCall16 / (uint32_t)
		                              ::vd::Private::PlatformCyclesPerDelayLoop16);
		const uint32_t delayLoops8  = (uint32_t)(CpuFreq / (1.0e6 *
		                              (uint32_t)::vd::Private::PlatformCyclesPerDelayLoop8) * us -
		                              (uint32_t)::vd::Private::PlatformCyclesPerCall8 / (uint32_t)
		                              ::vd::Private::PlatformCyclesPerDelayLoop8);

		if (delayLoops16 > 0xFFFFul) {
			::vd::Private::PlatformDelayCycle32<CpuFreq>(delayLoops32);
		} else if (delayLoops8 > 0xFFul) {
			::vd::Private::PlatformDelayCycle16<CpuFreq>((uint16_t)delayLoops16);
		} else {
			if (delayLoops8 == 0) { return; } //TODO StaticAssert Here

			::vd::Private::PlatformDelayCycle8<CpuFreq>((uint8_t)delayLoops8);
		}
	}
	//! \brief Delay for specified compile-known milliseconds
	//!  \code
	//!  delay_us<1000>();
	//!  \endcode
	template<uint32_t ms, uint32_t CpuFreq = F_CPU>
	void delay_ms() {
		delay_us<ms * 1000, CpuFreq>();
	}

//! \}
}


