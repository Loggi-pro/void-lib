#pragma once
#include <void/platform_specific.h>
#ifndef COMPATIBILITY_H
	#error Do not include '<Arch>/_types.h' files directly, use 'platform_specific.h' instead.
#endif
#include <void/static_assert.h>


/*!
	\defgroup types Types
	\brief Different types
	@file
*/

/*!
	\defgroup type_traits Type traits
	\brief Different type traits utilities
*/

/*!
	\defgroup utilities Utilities
	\brief Some types utilities
	\ingroup types
	@{
	@file
*/
#define SIZEOF(s,m) ((size_t) sizeof(((s *)0)->m)) //!< @brief Get size of array
#define OFFSETOF(s,m) (size_t)&(((s *)0)->m) //!< @brief Get offset of member of struct/class
#define COUNT_OF(a) ( sizeof(a)/sizeof(*(a)) ) //!< @brief Count element count in array

#ifdef _VOID_NATIVE_CPP11_SUPPORT
//! @brief Count element count of static array in run-time (if passed variable is not array-> compile error) (c++11 only)
template < class T, size_t N >
constexpr size_t countOf(const T(&array)[N]) { return N; }
#endif

#ifdef _VOID_NATIVE_CPP17_CONSTEXPR_SUPPORT
//support for binary literals
namespace vd {
	namespace Private {
		template <uint64_t V>
		constexpr uint64_t make_binary() {
			return V;
		}

		template <uint64_t V, char C, char... Cs>
		constexpr uint64_t make_binary() {
			VOID_STATIC_ASSERT_MSG(C == '0' || C == '1', "invalid_binary");
			return make_binary < 2 * V + C - '0', Cs... > ();
		}
	}

	//! \ingroup Utilities
	//! @brief Allow to create byte literals, like 0101_b;
	template <char... Cs>
	uint64_t operator "" _b() {
		VOID_STATIC_ASSERT_MSG(sizeof...(Cs) <= 64, "overflow");
		return Private::make_binary<0, Cs...>();
	}
}
#endif


#define SINGLE_ARG(...) __VA_ARGS__ //!< @brief Allow to pass elements with comma(templates, function calls) in macros

#define HI(x) ((x)>>8)	//!< @brief Get hi byte of word (macro)
#define LO(x) ((x)& 0xFF)//!< @brief Get low byte of variable (macro)
#ifndef HIWORD
	#define HIWORD(a) (*((u16*)&(a) + 1))	//!< @brief Get hightest two bytes (word) of dword (macro)
#endif
#ifndef LOWORD
	#define LOWORD(a) (*((u16*)&(a)))	//!< @brief Get lowest two bytes (word) of dword (macro)
#endif
namespace vd {
	//! \ingroup utilities
	//! @brief Create word from low and hi byte
	inline _MB_CONSTEXPR uint16_t makeWord(uint8_t low, uint8_t hi) {
		uint16_t res = (uint16_t)(((uint16_t)hi) << 8);
		return (uint16_t)(res | low);
	}

	//! \ingroup utilities
	//! @brief Get hi byte of word
	_MB_CONSTEXPR uint8_t hiByte(uint16_t x) {
		return (uint8_t)(x >> 8);
	}
	//! \ingroup utilities
	//! @brief Get low byte of variable
	template <typename T>
	_MB_CONSTEXPR uint8_t lowByte(T x) {
		return (uint8_t)(x & 0xFF);
	}
	//! \ingroup utilities
	//! @brief Get hightest two bytes (word) of dword
	_MB_CONSTEXPR uint16_t hiWord(uint32_t x) {
		return (uint16_t)(x >> 16);
	}
	//! \ingroup utilities
	//! @brief Get lowest two bytes (word) of dword
	_MB_CONSTEXPR uint16_t lowWord(uint32_t x) {
		return (uint16_t)(x & 0xFFFF);
	}
	//! \ingroup utilities
	//! @brief Swap two bytes of word (change endianness)
	inline _MB_CONSTEXPR uint16_t swapBytes(uint16_t w) {
		uint16_t res = (uint16_t)((uint16_t)(lowByte(w) << 8) | hiByte(w));
		return res;
	}

}



#define BYTE0(a) (*((u8*)(&(a)) + 0))	//!< @brief Get 1-st byte of variable (macro)
#define BYTE1(a) (*((u8*)&(a) + 1))	//!< @brief Get 2-nd byte of variable (macro)
#define BYTE2(a) (*((u8*)&(a) + 2))	//!< @brief Get 3-rd byte of variable (macro)
#define BYTE3(a) (*((u8*)&(a) + 3)) //!< @brief Get 4-th byte of variable (macro)


#define BIT0                (1<<0)		//!< @brief Get 1 bit of variable (macro)
#define BIT1                (1<<1)		//!< @brief Get 2 bit of variable (macro)
#define BIT2                (1<<2)		//!< @brief Get 3 bit of variable (macro)
#define BIT3                (1<<3)		//!< @brief Get 4 bit of variable (macro)
#define BIT4                (1<<4)		//!< @brief Get 5 bit of variable (macro)
#define BIT5                (1<<5)		//!< @brief Get 6 bit of variable (macro)
#define BIT6                (1<<6)		//!< @brief Get 7 bit of variable (macro)
#define BIT7                (1<<7)		//!< @brief Get 8 bit of variable (macro)
#define BIT8                (1<<8)		//!< @brief Get 9 bit of variable (macro)
#define BIT9                (1<<9)		//!< @brief Get 10 bit of variable (macro)
#define BIT10               (1<<10)		//!< @brief Get 11 bit of variable (macro)
#define BIT11               (1<<11)		//!< @brief Get 12 bit of variable (macro)
#define BIT12               (1<<12)		//!< @brief Get 13 bit of variable (macro)
#define BIT13               (1<<13)		//!< @brief Get 14 bit of variable (macro)
#define BIT14               (1<<14)		//!< @brief Get 15 bit of variable (macro)
#define BIT15               (1<<15)		//!< @brief Get 16 bit of variable (macro)
#define BIT16               (1UL<<16)	//!< @brief Get 17 bit of variable (macro)
#define BIT17               (1UL<<17)	//!< @brief Get 18 bit of variable (macro)
#define BIT18               (1UL<<18)	//!< @brief Get 19 bit of variable (macro)
#define BIT19               (1UL<<19)	//!< @brief Get 20 bit of variable (macro)
#define BIT20               (1UL<<20)	//!< @brief Get 21 bit of variable (macro)
#define BIT21               (1UL<<21)	//!< @brief Get 22 bit of variable (macro)
#define BIT22               (1UL<<22)	//!< @brief Get 23 bit of variable (macro)
#define BIT23               (1UL<<23)	//!< @brief Get 24 bit of variable (macro)
#define BIT24               (1UL<<24)	//!< @brief Get 25 bit of variable (macro)
#define BIT25               (1UL<<25)	//!< @brief Get 26 bit of variable (macro)
#define BIT26               (1UL<<26)	//!< @brief Get 27 bit of variable (macro)
#define BIT27               (1UL<<27)	//!< @brief Get 28 bit of variable (macro)
#define BIT28               (1UL<<28)	//!< @brief Get 29 bit of variable (macro)
#define BIT29               (1UL<<29)	//!< @brief Get 30 bit of variable (macro)
#define BIT30               (1UL<<30)	//!< @brief Get 31 bit of variable (macro)
#define BIT31               (1UL<<31)	//!< @brief Get 32 bit of variable (macro)
//!@}



