#pragma once
#include <void/auto_size.h>
#include <void/type_traits.h>
#include <void/static_assert.h>
#include <void/bits.h>
VOID_STATIC_ASSERT(SINGLE_ARG(vd::is_same_v<vd::uintx_t<0>, uint8_t>));
VOID_STATIC_ASSERT(SINGLE_ARG(vd::is_same_v<vd::uintx_t<255>, uint8_t>));
VOID_STATIC_ASSERT(SINGLE_ARG(vd::is_same_v<vd::uintx_t<256>, uint16_t>));
VOID_STATIC_ASSERT(SINGLE_ARG(vd::is_same_v<vd::uintx_t<65535>, uint16_t>));
VOID_STATIC_ASSERT(SINGLE_ARG(vd::is_same_v<vd::uintx_t<65536>, uint32_t>));

VOID_STATIC_ASSERT(SINGLE_ARG(vd::is_same_v<vd::intx_t<0>, int8_t>));
VOID_STATIC_ASSERT(SINGLE_ARG(vd::is_same_v<vd::intx_t<127>, int8_t>));
VOID_STATIC_ASSERT(SINGLE_ARG(vd::is_same_v<vd::intx_t<128>, int16_t>));
VOID_STATIC_ASSERT(SINGLE_ARG(vd::is_same_v<vd::intx_t<32767>, int16_t>));
VOID_STATIC_ASSERT(SINGLE_ARG(vd::is_same_v<vd::intx_t<32768>, int32_t>));

VOID_STATIC_ASSERT(vd::bitsToMaxValue(8) == 255);
VOID_STATIC_ASSERT(vd::bitsToMaxValue(16) == 65535);
VOID_STATIC_ASSERT(vd::bitsToMaxValue(32) == vd::numeric_limits<uint32_t>::max());
VOID_STATIC_ASSERT(vd::bitsToMaxValue(1) == 1);