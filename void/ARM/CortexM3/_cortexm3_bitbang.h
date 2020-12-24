#pragma once
namespace vd {
	constexpr uint32_t bit_num_from_value(uint32_t val, uint32_t comp_val, uint32_t bit_num) {
		return bit_num = (val == comp_val) ? bit_num : bit_num_from_value(val, 2 * comp_val,
						 bit_num + 1);
	}	
}
#define	BIT_BAND_PER(reg, reg_val)	*(reinterpret_cast<volatile uint32_t *>(PERIPH_BB_BASE + 32 * (reinterpret_cast<uint32_t>(&(reg)) - PERIPH_BASE) + 4 * (bit_num_from_value(static_cast<uint32_t>(reg_val), static_cast<uint32_t>(0x01), static_cast<uint32_t>(0)))))

//usage 	BIT_BAND_PER(GPIOB->MODER, GPIO_MODER_MODER0_0) = false; //Сброс
//			BIT_BAND_PER(GPIOB->MODER, GPIO_MODER_MODER0_0) = true; //Установка