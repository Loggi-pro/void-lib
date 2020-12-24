#pragma once
#include "initializer_list"
#include "type_traits.h"
#include "assert.h"
#include "auto_size.h"
namespace vd {
	template < typename T, size_t SIZE>
	class Array {
			T data[SIZE] = {0};
		public:
			using index_t = vd::uintx_t<SIZE>;
			using data_t  = T;
			constexpr Array() = default;
			constexpr explicit Array(std::initializer_list<T> l) {
				const index_t max = l.size() > SIZE ? SIZE : l.size();
				auto it = l.begin();

				for (index_t i = 0; i < max; ++i) {
					data[i] = *it;
					it++;
				}
			}
			constexpr T& operator[](index_t index) {
				return data[index];
			}
			constexpr const T& operator[](index_t index)const {
				return data[index];
			}

			constexpr T* begin() {
				return data;
			}
			constexpr T* end() {
				return data + SIZE;
			}
			constexpr const T* begin()const  {
				return data;
			}
			constexpr const T* end()const  {
				return data  + SIZE;
			}
			constexpr const T* cbegin() {
				return data;
			}
			constexpr const T* cend() {
				return data  + SIZE;
			}
			constexpr index_t size()const  {
				return SIZE;
			}
	};

	template < typename T, typename... Ts >
	constexpr auto make_array(T&& t, Ts&&  ... ts)-> Array  <  T, sizeof...(Ts) + 1  > {
		return Array  < T, sizeof...(Ts) + 1 >   {std::initializer_list<T>{vd::forward<T>(t), static_cast<T>(vd::forward<Ts>(ts))...}};
	}

}
