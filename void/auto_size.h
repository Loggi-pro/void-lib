#pragma once
#include "static_if.h"
namespace vd {

	namespace details {
		template<uint32_t size>
		struct UnsignedAutoSize {
			static const bool LessOrEq8 = size <= 0xffUL;
			static const bool LessOrEq16 = size <= 0xffffUL;
			using value = static_if_v <
			              LessOrEq8,
			              uint8_t,
			              static_if_v<LessOrEq16, uint16_t, uint32_t >>;
		};

		template<uint32_t size>
		struct SignedAutoSize {
			static const bool LessOrEq8 = size <= 0x7fUL;
			static const bool LessOrEq16 = size <= 0x7fffUL;
			using value = static_if_v <
			              LessOrEq8,
			              int8_t,
			              static_if_v<LessOrEq16, int16_t, int32_t >>;
		};
	}


	//return unsigned type which can hold value=size
	template<uint32_t size>
	using uintx_t = typename details::UnsignedAutoSize<size>::value;
	//return signed type which can hold value=size
	template<uint32_t size>
	using intx_t = typename details::SignedAutoSize<size>::value;



}