#pragma once
#include <void\assert.h>
#include <void/static_assert.h>

namespace vd {
	namespace chrono {
#include "chrono/chrono_durations.h"
//Periods



//==================================================Durations===========================================
		typedef Duration<Private::Period_hours> hours_t;
		typedef Duration<Private::Period_minutes> minutes_t;
		typedef Duration<Private::Period_seconds> seconds_t;
		typedef Duration<Private::Period_milli> milli_t;
		typedef Duration<Private::Period_micro> micro_t;
#ifdef _VOID_NATIVE_CPP11_SUPPORT
	template <class T>
	using any_t = Duration<T>;
#endif
//========================================Literal Durations extension (constexpr)========================
//can be implemented with using alias in c++11
		template <uint32_t TIME>
		struct hours_l;
		template <uint32_t TIME>
		struct minutes_l;
		template <uint32_t TIME>
		struct seconds_l;
		template <uint32_t TIME>
		struct milli_l;
		template <uint32_t TIME>
		struct micro_l;

#include "chrono/chrono_literals.h"
#include "chrono/chrono_type_traits.h"

	}
}
using namespace vd::chrono::literals;
