#pragma once

namespace vd {
// Return hi order part of 32x32=>64 multiplication
	static inline uint32_t mul32hu(uint32_t u, uint32_t v) {
		#if defined(AVR) || defined (__AVR__)
// implementation for 8-bit MCUs with 8x8=>16 hardware multiplication
		uint8_t a0 = (uint8_t)(u >> 0);
		uint8_t a1 = (uint8_t)(u >> 8);
		uint8_t a2 = (uint8_t)(u >> 16);
		uint8_t a3 = (uint8_t)(u >> 24);
		uint8_t b0 = (uint8_t)(v >> 0);
		uint8_t b1 = (uint8_t)(v >> 8);
		uint8_t b2 = (uint8_t)(v >> 16);
		uint8_t b3 = (uint8_t)(v >> 24);
		union {
			struct {
				uint8_t w0, w1, w2, w3, w4, w5, w6, w7;
			} u8;
			uint32_t u32[2];
		};
		u8.w0 = u8.w1 = u8.w2 = u8.w3 = 0;
		uint8_t k = 0;
		uint16_t t;
		t = a0 * b0 + u8.w0 + k;	u8.w0 = t;	k = t >> 8;
		t = a1 * b0 + u8.w1 + k;	u8.w1 = t;	k = t >> 8;
		t = a2 * b0 + u8.w2 + k;	u8.w2 = t;	k = t >> 8;
		t = a3 * b0 + u8.w3 + k;	u8.w3 = t;	k = t >> 8;
		u8.w4 = k;	k = 0;
		t = a0 * b1 + u8.w1 + k;	u8.w1 = t;	k = t >> 8;
		t = a1 * b1 + u8.w2 + k;	u8.w2 = t;	k = t >> 8;
		t = a2 * b1 + u8.w3 + k;	u8.w3 = t;	k = t >> 8;
		t = a3 * b1 + u8.w4 + k;	u8.w4 = t;	k = t >> 8;
		u8.w5 = k;	k = 0;
		t = a0 * b2 + u8.w2 + k;	u8.w2 = t;	k = t >> 8;
		t = a1 * b2 + u8.w3 + k;	u8.w3 = t;	k = t >> 8;
		t = a2 * b2 + u8.w4 + k;	u8.w4 = t;	k = t >> 8;
		t = a3 * b2 + u8.w5 + k;	u8.w5 = t;	k = t >> 8;
		u8.w6 = k;	k = 0;
		t = a0 * b3 + u8.w3 + k;	u8.w3 = t;	k = t >> 8;
		t = a1 * b3 + u8.w4 + k;	u8.w4 = t;	k = t >> 8;
		t = a2 * b3 + u8.w5 + k;	u8.w5 = t;	k = t >> 8;
		t = a3 * b3 + u8.w6 + k;	u8.w6 = t;	k = t >> 8;
		u8.w7 = k;
		return u32[1];
		#else
		return uint32_t((uint64_t(u) * v) >> 32);
		#endif
	}

}