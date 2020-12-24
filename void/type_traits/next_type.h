#pragma once
namespace vd {
	template <typename T>
	struct next_type;

	template <>
	struct next_type<uint8_t> {
		using type = uint16_t;
	};
	template <>
	struct next_type<uint16_t> {
		using type = uint32_t;
	};
	template <>
	struct next_type<int8_t> {
		using type = int16_t;
	};
	template <>
	struct next_type<int16_t> {
		using type = int32_t;
	};

	template <typename T>
	using next_type_t = typename next_type<T>::type;


}