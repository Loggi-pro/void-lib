#pragma once
#include <void/tuple.h>
//C++17 Utility classes for comparing multiple values in one simple expression
//based on https://github.com/rollbear/dry-comparisons
//compare library

/*usage
enum { S0, S1, S2, S3 } state;
if (state == any_of(S1, S3)) {...}

int x = 5;
if (x < any_of(1,2,3,4)) {...}
*/


/*!
	\defgroup comparators Comparators
	\brief Some compare utilities
	\ingroup types
	@{
	@file
*/

namespace vd {

	namespace details {
		template <typename ... Ts>
		class logical_tuple : vd::tuple<Ts...> {
				using tuple = vd::tuple<Ts...>;
				constexpr const tuple& self() const { return *this; }
			protected:
				using tuple::tuple;
				template <typename F>
				constexpr bool or_all(const F& f)const {
					return vd::apply([&](const auto & ...ts) { return (f(ts) || ...); }, self());
				}
				template <typename F>
				constexpr bool and_all(const F& f)const {
					return vd::apply([&](const auto & ...ts) { return (f(ts) && ...); }, self());
				}
		};
	}


	//! \ingroup comparators
	//! @brief logical compare if any of items is true
	//! @code
	//! enum { S0, S1, S2, S3 } state;
	//! state = S1;
	//! if (state == vd::any_of(S1, S3)) {...}
	//! @endcode
	template <typename ...Ts>
	class any_of: details::logical_tuple<Ts...> {
			using details::logical_tuple<Ts...>::or_all;
			using details::logical_tuple<Ts...>::and_all;
			using details::logical_tuple<Ts...>::logical_tuple;
			template <typename T>
			constexpr bool operator ==(const T& t) const {
				return or_all([&t](const auto & v) {return v == t; });
			}
			template <typename T>
			constexpr friend bool operator == (const T& l, const any_of& r) {
				return r == l;
			}

			template <typename T>
			constexpr bool operator !=(const T& t) const {
				return and_all([&t](const auto & v) {return v != t; });
			}
			template <typename T>
			constexpr friend bool operator != (const T& l, const any_of& r) {
				return r != l;
			}
			//
			template <typename T>
			constexpr bool operator <(const T& t) const {
				return or_all([&t](const auto & v) {return v < t; });
			}
			template <typename T>
			constexpr friend bool operator < (const T& u, const any_of& a) {
				return a > u;
			}
			//
			template <typename T>
			constexpr bool operator >(const T& t) const {
				return or_all([&t](const auto & v) {return v > t; });
			}
			template <typename T>
			constexpr friend bool operator > (const T& u, const any_of& a) {
				return a < u;
			}
			//
			template <typename T>
			constexpr bool operator <=(const T& t) const {
				return or_all([&t](const auto & v) {return v <= t; });
			}
			template <typename T>
			constexpr friend bool operator <= (const T& u, const any_of& a) {
				return a >= u;
			}
			//
			template <typename T>
			constexpr bool operator >=(const T& t) const {
				return or_all([&t](const auto & v) {return v > t; });
			}
			template <typename T>
			constexpr friend bool operator >= (const T& u, const any_of& a) {
				return a <= u;
			}
			constexpr explicit operator bool() const {
				return or_all([](auto&& v) {return v; });
			}
	};
	//

	//! \ingroup comparators
	//! @brief logical compare if all of items is true
	//! @code
	//! boo flagOne,flagTwo = true;
	//! if (vd::all_of(flagOne, flagTwo)) {...}
	//! @endcode
	template <typename ...Ts>
	class all_of : details::logical_tuple<Ts...> {
			using details::logical_tuple<Ts...>::or_all;
			using details::logical_tuple<Ts...>::and_all;
			using details::logical_tuple<Ts...>::logical_tuple;
		public:
			//==
			template <typename T>
			constexpr bool operator ==(const T& t) const {
				return and_all([&t](const auto & v) {return v == t; });
			}
			template <typename T>
			constexpr friend bool operator == (const T& l, const all_of& r) {
				return r == l;
			}
			template <typename T>
			constexpr bool operator !=(const T& t) const {
				return or_all([&t](const auto & v) {return v != t; });
			}
			template <typename T>
			constexpr friend bool operator != (const T& u, const all_of& a) {
				return a != u;
			}
			//<
			template <typename T>
			constexpr bool operator <(const T& t) const {
				return and_all([&t](const auto & v) {return v < t; });
			}
			template <typename T>
			constexpr friend bool operator < (const T& u, const all_of& a) {
				return a > u;
			}
			//>
			template <typename T>
			constexpr bool operator >(const T& t) const {
				return and_all([&t](const auto & v) {return v > t; });
			}
			template <typename T>
			constexpr friend bool operator > (const T& u, const all_of& a) {
				return a < u;
			}
			//<=
			template <typename T>
			constexpr bool operator <=(const T& t) const {
				return and_all([&t](const auto & v) {return v <= t; });
			}
			template <typename T>
			constexpr friend bool operator <= (const T& u, const all_of& a) {
				return a >= u;
			}
			//>=
			template <typename T>
			constexpr bool operator >=(const T& t) const {
				return and_all([&t](const auto & v) {return v >= t; });
			}
			template <typename T>
			constexpr friend bool operator >= (const T& u, const all_of& a) {
				return a <= u;
			}
			//
			//bool
			constexpr explicit operator bool() const {
				return and_all([](auto&& v) {return v; });
			}
	};



	//! \ingroup comparators
	//! @brief logical compare if none of items is true
	//! @code
	//! enum { S0, S1, S2, S3 } state;
	//! state = S1;
	//! if (state == vd::none_of(S2, S3)) {...}
	//! @endcode
	template <typename ...Ts>
	class none_of : details::logical_tuple<Ts...> {
			using details::logical_tuple<Ts...>::or_all;
			using details::logical_tuple<Ts...>::and_all;
			using details::logical_tuple<Ts...>::logical_tuple;

		public:
			template <typename T>
			constexpr bool operator ==(const T& t) const {
				return !or_all([&t](auto&& v) { return v == t; });
			}
			template < typename T>
			constexpr friend bool operator ==(const T& u, const none_of& a) {
				return a == u;
			}
			//
			template <typename T>
			constexpr bool operator !=(const T& t) const {
				return !and_all([&t](auto&& v) { return v != t; });
			}
			template < typename T>
			constexpr friend bool operator !=(const T& u, const none_of& a) {
				return a != u;
			}
			//<
			template <typename T>
			constexpr bool operator <(const T& t) const {
				return !or_all([&t](auto&& v) { return v < t; });
			}
			template < typename T>
			constexpr friend bool operator<(const T& u, const none_of& a) {
				return a > u;
			}

			//>
			template <typename T>
			constexpr bool operator >(const T& t) const {
				return !or_all([&t](auto&& v) { return v > t; });
			}
			template < typename T>
			constexpr friend bool operator >(const T& u, const none_of& a) {
				return a < u;
			}

			//<=
			template <typename T>
			constexpr bool operator <=(const T& t) const {
				return !or_all([&t](auto&& v) { return v <= t; });
			}
			template < typename T>
			constexpr friend bool operator <=(const T& u, const none_of& a) {
				return a >= u;
			}
			//>=
			template <typename T>
			constexpr bool operator >=(const T& t) const {
				return !or_all([&t](auto&& v) { return v >= t; });
			}
			template < typename T>
			constexpr friend bool operator >=(const T& u, const none_of& a) {
				return a <= u;
			}
			constexpr explicit operator bool() const {
				return !or_all([](auto&& v) {return v; });
			}

	};



	//deduction guides
	template <typename ...Ts>
	any_of(Ts...)->any_of<Ts...>;
	template <typename ... T>
	none_of(T&& ...)->none_of<T...>;
	template <typename ... T>
	all_of(T&& ...)->all_of<T...>;

}
//! @}