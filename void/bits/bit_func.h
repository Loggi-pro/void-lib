#pragma once
#include "../assert.h"
#include "../static_assert.h"
#include "../type_traits.h"
#include <void/type_traits.h>
#include <void/limits.h>
#include <void/auto_size.h>
namespace vd {
	template<class T, T arg>
	struct ReverseBits;

	template<uint32_t arg>
	struct ReverseBits<uint32_t, arg> {
		private:
			static const uint32_t t1 = ((arg >> 1) & 0x55555555) | ((arg & 0x55555555) << 1);
			static const uint32_t t2 = ((t1 >> 2) & 0x33333333) | ((t1 & 0x33333333) << 2);
			static const uint32_t t3 = ((t2 >> 4) & 0x0F0F0F0F) | ((t2 & 0x0F0F0F0F) << 4);
			static const uint32_t t4 = ((t3 >> 8) & 0x00FF00FF) | ((t3 & 0x00FF00FF) << 8);
		public:
			static const uint32_t value = (t4 >> 16) | ( t4 << 16);
	};

	template<uint16_t arg>
	struct ReverseBits<uint16_t, arg> {
		private:
			static const uint16_t t1 = ((arg >> 1) & 0x5555) | ((arg & 0x5555) << 1);
			static const uint16_t t2 = ((t1 >> 2) & 0x3333) | ((t1 & 0x3333) << 2);
			static const uint16_t t3 = ((t2 >> 4) & 0x0F0F) | ((t2 & 0x0F0F) << 4);
		public:
			static const uint16_t value = uint16_t(t3 >> 8) | uint16_t((t3 << 8) & 0xff00);
	};

	template<uint8_t arg>
	struct ReverseBits<uint8_t, arg> {
		private:
			static const uint8_t t1 = ((arg >> 1) & 0x55) | ((arg & 0x55) << 1);
			static const uint8_t t2 = ((t1 >> 2) & 0x33) | ((t1 & 0x33) << 2);
		public:
			static const uint8_t value = uint8_t(t2 >> 4) | uint8_t(t2 << 4);
	};


	template<unsigned long x>
	class PopulatedBits {
			static const unsigned long x1 = (x & 0x55555555) + ((x >> 1) & 0x55555555);
			static const unsigned long x2 = (x1 & 0x33333333) + ((x1 >> 2) & 0x33333333);
			static const unsigned long x3 = (x2 & 0x0f0f0f0f) + ((x2 >> 4) & 0x0f0f0f0f);
			static const unsigned long x4 = (x3 & 0x00ff00ff) + ((x3 >> 8) & 0x00ff00ff);
		public:
			static const unsigned long value = (x4 & 0x0000ffff) + ((x4 >> 16) & 0x0000ffff);
	};

	namespace details {
		template<typename... T>
		using areInts = vd::conjunction<vd::is_integral<T>...>;

		template<typename... T>
		using IsInteger = vd::enable_if_t < areInts<T...>::value >;

	}


	template <typename T>
	constexpr T bvalue(uint8_t b) {
		using Tr = typename vd::remove_cv<T>::type;
		assert(vd::numeric_limits<Tr>::digits > b);
		//assert((sizeof(T) * 8U) > (b); //TODO numeric_limits::digits
		return static_cast<T>(static_cast<T>(1) << static_cast<T>(b));
	}

	template <typename T,uint8_t b>
	constexpr T bvalue() {
		using Tr = typename vd::remove_cv<T>::type;
		VOID_STATIC_ASSERT(vd::numeric_limits<Tr>::digits > b);
		return static_cast<T>(static_cast<T>(1) << static_cast<T>(b));
	}

	inline constexpr uint32_t bitsToMaxValue(uint8_t bits) {
		const uint32_t mask = static_cast<uint32_t>(1) << (bits-1);
		return static_cast<uint32_t>((mask-1)|mask);
	}




	//create mask from bits
	template <typename T, typename ... T1>
	constexpr T masked(T1 ...bit) {
		return (bvalue<T>(static_cast<uint8_t>(bit)) | ...);
	}

	//create mask struct
	template<typename T>
	struct Mask {
		const T value;
		explicit constexpr Mask(T m) : value(m) {}
	};


	/*
	static_assert(areInts<int, int, vd::Mask<u08>>::value == false);
	static_assert(areInts<int, int, int>::value);
	static_assert(vd::is_same<IsInteger<int,int,float>,void>::value==true);
	*/


	template<typename T, typename ...T1, typename = details::IsInteger<T1...>>
	constexpr inline void setBit(T& value, T1 ...bits) {
		value = (value | ... | bvalue<T>(static_cast<uint8_t>(bits)) );
	}

	template<typename T, typename T1>
	constexpr inline void setBit(T& value, Mask<T1>&& m) {
		value = (value | m.value);
	}

	template<typename T, typename T1>
	constexpr inline void clearBit(T& value, Mask<T1>&& m) {
		value &= ~(m.value);
	}


	template<typename T, typename ...T1, typename = details::IsInteger<T1...>>
	constexpr inline void clearBit(T& value, T1 ...bits) {
		value = (T)(value & ... & ~bvalue<T>(static_cast<uint8_t>(bits)));
	}

	template<uint8_t... bits, typename T>
	constexpr inline void clearBit(T& value) {
		value = (T)(value & ... & ~bvalue<T>(bits));
	}

	template<typename T, typename ...T1, typename = details::IsInteger<T1...>>
	constexpr inline void toggleBit(T& value, T1 ...bits) {
		value = (T)(value ^ ... ^ bvalue<T>(static_cast<uint8_t>(bits)));
	}

	template<uint8_t... bits, typename T>
	constexpr inline void toggleBit(T& value) {
		value = (T)(value ^ ... ^ bvalue<T>(bits));
	}



	template<typename T, typename ...T1, typename = details::IsInteger<T1...>>
	constexpr inline bool isBitSet(T& value, T1 ...bit) {
		return value & masked<T, T1...>(bit...);
	}

	template<uint8_t... bits, typename T>
	constexpr inline void isBitSet(T& value) {
		return value & masked<T, uint8_t>(bits...);
	}


	template<typename T, typename T1>
	constexpr inline bool isBitSet(T& value, const Mask<T1>& m) {
		return value & m.value;
	}

#//define BIT_SET(x,bit) (x |= (1<<bit))
	//#define BIT_CLEAR(x,bit) (x &= ~(1<<bit))
	/*
	#define BIT_CHANGED(x1,x2,BIT) ((x1 & (1<<BIT))^(x2 & (1<<BIT)))
	#define BIT_CHANGED_SET(Dest,Val,BIT) ((Dest & (1<<BIT))^(Val & (1<<BIT)))//returns 1 if BIT Changed 0->1;

	#define BIT_CLEAR_MASK(x,MASK) (x &= ~(MASK))
	#define BIT_SET_VAL(x,MASK) (x |=(MASK))

	#define BIT_SET_MASK(x,Val,Mask) (x = (Val&(Mask))|(x&~(Mask)))
	#define BIT_SET_EXCEPT(Dest,Val,Mask) (Dest = (Val &~(Mask))|(Dest &(Mask)))//Set Value, except position in mask(1<<x);
	*/

}//vd

