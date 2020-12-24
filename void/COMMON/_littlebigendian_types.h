#pragma once
#include "_littlebigendian.h"
/*!
	\defgroup endian Endian types
	\brief Types with garanted endianness
	\ingroup types
	\{
	\file
*/

namespace vd {
	namespace details {
		template <bool, typename ifTrue, typename ifFalse> struct endian_selector {};
		template <typename ifTrue, typename ifFalse> struct endian_selector<true, ifTrue, ifFalse> { typedef ifTrue type;};
		template <typename ifTrue, typename ifFalse> struct endian_selector<false, ifTrue, ifFalse> { typedef ifFalse type;};
		template <bool b, typename ifTrue, typename ifFalse>
		using endian_selector_t = typename endian_selector<b, ifTrue, ifFalse>::type;
	}

}

namespace vd {
	namespace platform {
		//! @ingroup endian
		//! @brief Compile-time bool to get platform endianness (control by @ref IS_LITTLE_ENDIAN and @ref IS_BIG_ENDIAN macro)
		inline constexpr bool is_little_endian_v = details::platform::IS_LE_NATIVE::value;
		//! @ingroup endian
		//! @brief Compile-time bool to get platform endianness (control by @ref IS_LITTLE_ENDIAN and @ref IS_BIG_ENDIAN macro)
		inline constexpr bool is_big_endian_v = details::platform::IS_BE_NATIVE::value;
	}

}
//! @ingroup endian
//! @{

//Little endian types
//! @brief signed byte little-endian
typedef vd::details::endian_selector_t<	vd::platform::is_little_endian_v, vd::details::TLittleEndian<int8_t>, int8_t>
s08le;
//! @brief signed word little-endian
typedef vd::details::endian_selector_t<vd::platform::is_little_endian_v, vd::details::TLittleEndian<int16_t>, int16_t>
s16le;
//! @brief signed dword little-endian
typedef vd::details::endian_selector_t<vd::platform::is_little_endian_v, vd::details::TLittleEndian<int32_t>, int32_t>
s32le;
//! @brief signed qword little-endian
typedef vd::details::endian_selector_t<vd::platform::is_little_endian_v, vd::details::TLittleEndian<int64_t>, int64_t>
s64le;
//! @brief unsigned byte little-endian
typedef vd::details::endian_selector_t<vd::platform::is_little_endian_v, vd::details::TLittleEndian<uint8_t>,  uint8_t>
u08le;
//! @brief unsigned word little-endian
typedef vd::details::endian_selector_t<vd::platform::is_little_endian_v, vd::details::TLittleEndian<uint16_t>, uint16_t>
u16le;
//! @brief unsigned dword little-endian
typedef vd::details::endian_selector_t<vd::platform::is_little_endian_v, vd::details::TLittleEndian<uint32_t>, uint32_t>
u32le;
//! @brief unsigned qword little-endian
typedef vd::details::endian_selector_t<vd::platform::is_little_endian_v, vd::details::TLittleEndian<uint64_t>, uint64_t>
u64le;
//Big endian types
//! @brief signed byte big-endian
typedef vd::details::endian_selector_t<vd::platform::is_big_endian_v, vd::details::TBigEndian<int8_t>, int8_t>
s08be;
//! @brief signed word big-endian
typedef vd::details::endian_selector_t<vd::platform::is_big_endian_v, vd::details::TBigEndian<int16_t>, int16_t>
s16be;
//! @brief signed dword big-endian
typedef vd::details::endian_selector_t<vd::platform::is_big_endian_v, vd::details::TBigEndian<int32_t>, int32_t>
s32be;
//! @brief signed qword big-endian
typedef vd::details::endian_selector_t<vd::platform::is_big_endian_v, vd::details::TBigEndian<int64_t>, int64_t>
s64be;
//! @brief unsigned byte big-endian
typedef vd::details::endian_selector_t<vd::platform::is_big_endian_v, vd::details::TBigEndian<uint8_t>,  uint8_t>
u08be;
//! @brief unsigned word big-endian
typedef vd::details::endian_selector_t<vd::platform::is_big_endian_v, vd::details::TBigEndian<uint16_t>, uint16_t>
u16be;
//! @brief unsigned dword big-endian
typedef vd::details::endian_selector_t<vd::platform::is_big_endian_v, vd::details::TBigEndian<uint32_t>, uint32_t>
u32be;
//! @brief unsigned qword big-endian
typedef vd::details::endian_selector_t<vd::platform::is_big_endian_v, vd::details::TBigEndian<uint64_t>, uint64_t>
u64be;
//!@}
namespace vd {
	//! @ingroup endian
	//! @{

	//! @brief Convert value to little-endian
	template<typename T>
	T toLittleEndian(T val) {
		#ifdef IS_BIG_ENDIAN
		details::TLittleEndian<T> t(val);
		return t.raw_value;
		#elif defined(IS_LITTLE_ENDIAN)
		return val;
		#endif
	}

	//! @brief Convert value to big-endian
	template<typename T>
	T toBigEndian(T val) {
		#ifdef IS_BIG_ENDIAN
		return val;
		#elif defined(IS_LITTLE_ENDIAN)
		details::TBigEndian<T> t(val);
		return t.raw_value;
		#endif
	}
	//! @brief Convert value from little-endian to native
	template<typename T>
	T fromLittleEndian(T val) {
		#ifdef IS_BIG_ENDIAN
		details::TBigEndian<T> t(val);
		return t.raw_value;
		#elif defined(IS_LITTLE_ENDIAN)
		return val;
		#endif
	}
	//! @brief Convert value from big-endian to native
	template<typename T>
	T fromBigEndian(T val) {
		#ifdef IS_BIG_ENDIAN
		return val;
		#elif defined(IS_LITTLE_ENDIAN)
		details::TLittleEndian<T> t(val);
		return t.raw_value;
		#endif
	}
	//!@}
}
//! \}