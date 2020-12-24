#pragma once
#include <void/index_sequence.h>
#include <void/type_traits.h>
#include <void/pair.h>
namespace vd {
	// Contains the actual value for one item in the tuple. The
	// template parameter `i` allows the
	// `Get` function to find the value in O(1) time
	/*
	template<size_t i, typename Item>
	struct TupleLeaf {
		Item value;
	};



	// TupleImpl is a proxy for the final class that has an extra
	// template parameter `i`.
	template<size_t i, typename... Items>
	struct TupleImpl;

	// Base case: empty tuple
	template<size_t i>
	struct TupleImpl<i> {
		constexpr static size_t len = 0;

		struct times_struct {
			template<class F>
			void with_item(F func) {
			}

			template<class F>
			void with_index(F func) {
			}
		};
		times_struct times;
	};


	template<size_t i, typename HeadItem, typename... TailItems>
	HeadItem& get(TupleImpl<i, HeadItem, TailItems...>& tuple);

	// Recursive specialization
	template<size_t i, typename HeadItem, typename... TailItems>
	struct TupleImpl<i, HeadItem, TailItems...> :
		public TupleLeaf<i, HeadItem>, // This adds a `value` member of type HeadItem
		public TupleImpl < i + 1, TailItems... > { // This recurses
			constexpr static size_t len = 1 + sizeof...(TailItems);
			struct times_struct {
				private:
					template<class F, class Tuple, size_t...Is>
					void for_each_in_tuple(Tuple& tuple, F func, vd::index_sequence<Is...>) {
						using expander = int[];
						(void)expander {
							0, ((void)func(get<Is>(tuple)), 0)...
						};
					}

					template<class F, class Tuple, size_t...Is>
					void for_each_in_tuple_byindex(Tuple& tuple, F func, vd::index_sequence<Is...>) {
						using expander = int[];
						(void)expander {
							//vd::integral_constant<size_t, Is>{}::value
							0, ((void)func(vd::integral_constant<size_t, Is>{}), 0)...
						};
					}


				public:
					//	template<class F, class...Ts>
					//	void with_item(Tuple<Ts...>& tuple, F func) {
					//		for_each_in_tuple(tuple, func, make_index_sequence<sizeof...(Ts)>());
					//	}

					//	template<class F, class...Ts>
					//	void with_index(Tuple<Ts...>& tuple, F func) {
					//		for_each_in_tuple_byindex(tuple, func, make_index_sequence<sizeof...(Ts)>());
					//	}
					//

					template<class F>
					void with_item(F func) {
						for_each_in_tuple(*this, func, vd::make_index_sequence<len>());
					}

					template<class F>
					void with_index(F func) {
						for_each_in_tuple_byindex(*this, func, vd::make_index_sequence<len>());
					}



			};


			times_struct times;
	};



	// Templated alias to avoid having to specify `i = 0`
	template<typename... Items>


		// Obtain a reference to i-th item in a tuple
	template<size_t i, typename HeadItem, typename... TailItems>
	HeadItem& get(TupleImpl<i, HeadItem, TailItems...>& tuple) {
	// Fully qualified name for the member, to find the right one
	// (they are all called `value`).
	return tuple.TupleLeaf<i, HeadItem>::value;
	}















	using tuple = TupleImpl<0, Items...>;

	*/
	template <typename L, typename... types>
	class tuple;

	// Actual implementation for a type
	template <size_t _index, typename T>
	class _tuple_impl {
		public:
			constexpr _tuple_impl(T const& v): val(v) {
			}

			constexpr _tuple_impl(T&& v): val(vd::move(v)) {
			}

			constexpr T& get() {
				return val;
			}

			constexpr const T& get()const {
				return val;
			}
		private:
			T val;
	};



	// extract_type_at is a class that, given a list of types and an index, defines a type member
	// with the type of the index given from the list (zero based index).
	// E.g. extract<1, int, double, float>::type == double
	// For this we define ::type recursively, until we hit index zero, at that point there is a specialization
	// that defines the member ::type, and stops the recursion
	template <size_t index, typename L, typename... Args>
	struct extract_type_at {
		using type = typename extract_type_at < index - 1, Args... >::type;
	};

	// This is the stop type. If the index is zero, we define the member type to be the correspondent type
	template <typename L, typename... Args>
	struct extract_type_at<0, L, Args...> {
		using type = L;
	};

	// Method to get the value of a tuple, given an index
	// We cast the tuple to the base class that corresponds to the index
	// and type for that index
	template <size_t index, typename... Args>
	constexpr auto& get(tuple<Args...>& t) {
		return (static_cast<_tuple_impl<index, typename extract_type_at<index, Args...>::type>&>(t)).get();
	}

	template <size_t index, typename... Args>
	constexpr auto& get(const tuple<Args...>& t) {
		return (static_cast<const _tuple_impl<index, typename extract_type_at<index, Args...>::type>&>
		        (t)).get();
	}

	// general template, will be used only when there is no arguments
	template <size_t _index, typename... types>
	class _tuple_recurr_base {
	};

	// This is a partial specialization, so as long as there is at least one argument
	// this specialization is preferred to the _tuple_recurr_base<std::size_t, typename ...types>
	template <size_t _index, typename L, typename... types>
	class _tuple_recurr_base<_index, L, types...> : public _tuple_impl<_index, L>,
		public _tuple_recurr_base < _index + 1, types... > {
		public:
			template <typename CL, typename... CArgs>
			constexpr _tuple_recurr_base(CL&& arg,
			                             CArgs&& ... args) : _tuple_impl<_index, CL>(vd::forward<CL>(arg)),
				_tuple_recurr_base < _index + 1, types... > (vd::forward<CArgs>(args)...) {
			}

	};

	template<typename T>
	struct times_struct;
	template <typename L, typename... types>
	class tuple : public _tuple_recurr_base<0, L, types...>,
		private times_struct<tuple<L, types... >> {
			friend struct times_struct<tuple<L, types... >>; //for static_cast self CRTP
		public:
			// The constructor uses the same recursion as the inheritance
			constexpr static size_t len() {
				return 1 + sizeof...(types);
			}
			template <typename... CArgs>
			constexpr tuple(CArgs&& ... args) : _tuple_recurr_base<0, L, types...>(vd::forward<CArgs>
				        (args)...) {
			}

			template <typename... Args>
			friend bool operator==(tuple<Args...>& t1, tuple<Args...>& t2);

			constexpr const auto& times()const  {
				return *static_cast <const times_struct<tuple<L, types... >>*>(this);
			};
			constexpr auto& times() {
				return *static_cast <times_struct<tuple<L, types... >>*>(this);
			};
	};


	// template deduction guideline
	template <typename... CArgs>
	tuple(CArgs... args)->tuple<CArgs...>;
	//template<class T1, class T2>
	//vd::tuple(vd::pair<T1, T2>)->vd::tuple<T1, T2>;



	template <size_t index, typename... Args>
	bool compare_tuple(tuple<Args...>& t1, tuple<Args...>& t2) {
		if constexpr (index == 0) {
			return get<0>(t1) == get<0>(t2);
		} else {
			return get<index>(t1) == get<index>(t2) && compare_tuple < index - 1 > (t1, t2);
		}
	}

	template <typename... Args>
	bool operator==(tuple<Args...>& t1, tuple<Args...>& t2) {
		return compare_tuple < sizeof...(Args) - 1 > (t1, t2);
	}


	template<typename T>
	struct times_struct {
		private:
			template<class F, size_t...Is>
			constexpr void for_each_in_tuple(const T* tuple, F func, vd::index_sequence<Is...>)const {
				using expander = int[];
				(void)expander {
					0, ((void)func(get<Is>(*tuple)), 0)...
				};
			}
			template<class F, size_t...Is>
			constexpr void for_each_in_tuple(T* tuple, F func, vd::index_sequence<Is...>) {
				using expander = int[];
				(void)expander {
					0, ((void)func(get<Is>(*tuple)), 0)...
				};
			}

			template<class F, size_t...Is>
			constexpr void for_each_in_tuple_byindex(F func, vd::index_sequence<Is...>)const {
				using expander = int[];
				(void)expander {
					//vd::integral_constant<size_t, Is>{}::value
					0, ((void)func(vd::integral_constant<size_t, Is>{}), 0)...
				};
			}
			template<class F, size_t...Is>
			constexpr void for_each_in_tuple_byindex(F func, vd::index_sequence<Is...>) {
				using expander = int[];
				(void)expander {
					//vd::integral_constant<size_t, Is>{}::value
					0, ((void)func(vd::integral_constant<size_t, Is>{}), 0)...
				};
			}
			constexpr T* self() {
				return static_cast<T*>(this);
			}
			constexpr const T* self()const {
				return static_cast<const T*>(this);
			}

		public:
			template<class F>
			constexpr void with_item(F func)const  {
				for_each_in_tuple(self(), func,
				                  vd::make_index_sequence < T::len() >());
			}

			template<class F>
			constexpr void with_index(F func)const {
				for_each_in_tuple_byindex(func,
				                          vd::make_index_sequence < T::len() >());
			}
			template<class F>
			constexpr void with_item(F func) {
				for_each_in_tuple(self(), func,
				                  vd::make_index_sequence < T::len() >());
			}

			template<class F>
			constexpr void with_index(F func) {
				for_each_in_tuple_byindex(func,
				                          vd::make_index_sequence < T::len() >());
			}
	};











	//tuple size




	template< class T >
	class tuple_size;

	template< class... Types >
	class tuple_size<tuple<Types...> >
		: public vd::integral_constant<size_t, sizeof...(Types)> {
	};

	template< class T >
	class tuple_size<const T>
		: public vd::integral_constant<size_t, tuple_size<T>::value> {
	};



	template< class T >
	inline constexpr size_t tuple_size_v = tuple_size<T>::value;


	/*
	namespace detail {
		template <class F, class Tuple, size_t... I>
		constexpr decltype(auto) apply_impl(F&& f, Tuple&& t, vd::index_sequence<I...>) {
			// This implementation is valid since C++20 (via P1065R2)
			// In C++17, a constexpr counterpart of std::invoke is actually needed here
			return vd::invoke(vd::forward<F>(f), vd::get<I>(vd::forward<Tuple>(t))...);
		}
	}  // namespace detail

	template <class F, class Tuple>
	constexpr decltype(auto) apply(F&& f, Tuple&& t) {
		using Indices = vd::make_index_sequence<vd::tuple_size_v<vd::remove_reference_t<Tuple>>>;
		return detail::apply_impl(vd::forward<F>(f), vd::forward<Tuple>(t),
		                          Indices{});
	}
	*/

	template<typename F, typename Tuple, size_t ...S >
	constexpr decltype(auto) apply_tuple_impl(F&& fn, Tuple&& t, vd::index_sequence<S...>) {
		return vd::forward<F>(fn)(vd::get<S>(vd::forward<Tuple>(t))...);
	}
	template<typename F, typename Tuple>
	constexpr decltype(auto) apply(F&& fn, Tuple&& t) {
		size_t constexpr tSize
		    = vd::tuple_size<typename vd::remove_reference<Tuple>::type>::value;
		return apply_tuple_impl(vd::forward<F>(fn),
		                        vd::forward<Tuple>(t),
		                        vd::make_index_sequence<tSize>());
	}

	//make tuple
	template<class T> struct unwrap { using type = T; };
	template<class T> struct unwrap<vd::reference_wrapper<T>> { using type = T&; };

	//template<class... Ts>
	//tuple(Ts...)->tuple<typename unwrap<Ts>::type...>;

	template <class T>
	struct unwrap_refwrapper {
		using type = T;
	};

	template <class T>
	struct unwrap_refwrapper<vd::reference_wrapper<T>> {
		using type = T&;
	};

	template <class T>
	using special_decay_t = typename unwrap_refwrapper<typename vd::decay<T>::type>::type;

	template <class... Types>
	auto make_tuple(Types&& ... args) {
		return vd::tuple<special_decay_t<Types>...>(vd::forward<Types>(args)...);
	}

	namespace experimental {
		//for_each_in_tuple 
		template<class Tuple, class F>
		F for_each(Tuple&& t, F&& f) {
			return vd::apply(
				//<class...Ts> 
				[&] (auto&&...ts) {(f(vd::forward<decltype(ts)>(ts)), ...); },
				vd::forward<Tuple>(t)), f;
		}
	}	

} //namespace vd


/*
tuple_obj.times.with_index([&](const auto val) {
			const size_t index = decltype(val)::value;

		});
tuple_obj.times.with_item([&](const auto& item) {
			item...
		});

...
auto item = get<0>(tuple_obj);
size_t count= tuple_obj.len;

*/

