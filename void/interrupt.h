#pragma once
#include "platform_specific.h"

namespace vd {

	/*!
		\addtogroup atomic Atomic
		\brief Atomic functions
		\{
		@file
	*/

	//! \brief Disable all interrupts
	inline void DisableInterrupts() {
		vd::Private::DisableInterrupts();
	}

	//! \brief Enable all interrupts
	inline void EnableInterrupts() {
		vd::Private::EnableInterrupts();
	}


//! @}





}

