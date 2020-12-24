#pragma once
#include <void/type_traits.h>
#include <void/static_assert.h>
namespace vd {
	namespace fn {

		template <typename T>
		struct just_type {
			using type = T;

			template <class U>
			constexpr bool operator==(just_type<U>) { return false; }

			constexpr bool operator==(just_type<T>) { return true; }

			template <class U>
			constexpr bool operator!=(just_type<U>) { return true; }
			constexpr bool operator!=(just_type<T>) { return false; }
		};

		template <typename ...Ts> struct list {

			template <class... Us>
			constexpr bool operator==(list<Us...>) { return false; }
			constexpr bool operator==(list<Ts...>) { return true; }
			template <class... Us>
			constexpr bool operator!=(list<Us...>) { return true; }
			constexpr bool operator!=(list<Ts...>) { return false; }

			template <class... Us>
			constexpr auto operator+(list<Us...>) {
				return list<Ts..., Us...> {};
			}
		};
		using empty_list = list<>;


		template <class... Ts, class...Us>
		constexpr bool equal(list<Ts...>, list<Us...>) {return false;}
		template <class... Ts>
		constexpr bool equal(list<Ts...>, list<Ts...>) {return true;}

		template <class... Ts, class...Us>
		constexpr bool nequal(list<Ts...>, list<Us...>) {return false;}
		template <class... Ts>
		constexpr bool nequal(list<Ts...>, list<Ts...>) {return true;}



		template <typename... Ts, typename... As>
		constexpr auto push_front (list<Ts...>, just_type<As>...) { return list<As..., Ts...> {};}
		template <typename ...Us, typename... Ts>
		constexpr list<Us..., Ts...> push_front (list<Ts...>) { return {}; }
		template <typename... Ts, typename... As>
		constexpr auto push_back (list<Ts...>, just_type<As>...) { return list<Ts..., As...> {};}
		template <typename...Us, typename... Ts>
		constexpr  list<Ts..., Us...> push_back (list<Ts...>) { return {}; }
		template <typename...Ts, typename T>
		constexpr  list<Ts...> pop_back(list<Ts..., T>) { return {}; }


		constexpr  empty_list pop_back(empty_list) { return {}; }

		VOID_STATIC_ASSERT(push_back<int>(	list<double, char> {}) ==
		                   list<double, char, int> {});
		static_assert(push_back(	list<double, char> {}, just_type<int> {}, just_type<float> {}) ==
		              list<double, char, int, float> {});
		static_assert(push_front<int>(list<double, char> {}) ==
		              list<int, double, char> {});
		static_assert(push_front(	list<double, char> {}, just_type<int> {}, just_type<float> {}) ==
		              list<int, float, double, char> {});


		template <typename T, typename ... As>
		constexpr list<As...> tail (list<T, As...>) {return {};}
		template <typename T, typename... Ts>
		constexpr just_type<T> head(list<T, Ts...>) { return {}; }

		constexpr empty_list head(empty_list) { return {};}

		template <class T, class...Ts>
		constexpr bool contains(list<Ts...>) {
			return (... || vd::is_same_v<T, Ts>);
		}

		template <class... Ts>
		constexpr size_t size(list<Ts...>) {
			return sizeof...(Ts);
		}

		template <typename... Ts>
		constexpr bool empty(list<Ts...> l) {
			return sizeof(l) == 0;
		}

		//======================================get by index===================


		template <size_t N, typename ...Ts>
		struct get_impl;

		template <class T, class...Ts> //found case
		struct get_impl<0, T, Ts...> {using type = T;};

		template <size_t N, class T, class...Ts> //continue case
		struct get_impl<N, T, Ts...> {
			using type = typename get_impl < N - 1, Ts... >::type;
		};

		template <size_t N> //not FOUND case, SFINAE friendly
		struct get_impl<N> {
			static_assert(N >= 0);
			using type = void;
		};

		template <size_t N, class...Ts>
		constexpr auto get(list<Ts...>) {return just_type<typename get_impl<N, Ts...>::type> {};}
		static_assert(get<1>(list<double, int, char> {}) == just_type<int> {});
		//static_assert(get<5>(list<double,int,char>{})==just_type<int>{}); //compilation error


		template <class T, class...Ts>
		constexpr size_t find(vd::fn::list<Ts...> tp) {
			bool bs[] = {vd::is_same_v<T, Ts>...};

			for (size_t i = 0; i < size(tp); i++) {
				if (bs[i]) {
					return i;
				}
			}

			return size(tp);
		}

		template <class T, class...Ts>
		constexpr size_t find(vd::fn::list<Ts...> tp, just_type<T>) {
			bool bs[] = {vd::is_same_v<T, Ts>...};

			for (size_t i = 0; i < size(tp); i++) {
				if (bs[i]) {
					return i;
				}
			}

			return size(tp);
		}

		static_assert(find<int>(vd::fn::list<double, int, char> {}) == 1);
		static_assert(find(vd::fn::list<double, int, char> {}, just_type<int> {}) == 1);
		//haskell partial call analogye
		template <template <class...> class F, class...Ts>
		struct part_caller {
			template <class...Us>
			using type = typename F<Ts..., Us...>::type;
		};

		template <template <class...> class F, class...Ts>
		constexpr size_t find_if(vd::fn::list<Ts...> tp) {
			bool bs[] = {F<Ts>::value...};

			for (size_t i = 0; i < size(tp); i++) {
				if (bs[i]) {
					return i;
				}
			}

			return size(tp);
		}

		//metafunction wrapper for value-returning metafunction
		template <template <class...> class F>
		struct value_fn {
			template <class...Ts>
			constexpr auto operator()(just_type<Ts>...) {
				return F<Ts...>::value;
			}
		};


		/*
		template <template <class...> class F>
		constexpr value_fn<F> value_fn_v;
		*/

		template <class F, class...Ts>
		constexpr size_t find_if(list<Ts...> tp, F f) {
			bool bs[] = {f(just_type<Ts>{})...};

			for (size_t i = 0; i < size(tp); i++) {
				if (bs[i]) {
					return i;
				}
			}

			return size(tp);
		}



		static_assert(vd::fn::find_if(
		                  vd::fn::list<double, int, char> {}
		, [](auto t) {
			typedef decltype(t) type;
			return vd::is_same_v<type, float>;
		}) == 3);

		/*
		static_assert(vd::fn::find_if(vd::fn::list<double, int*, char> {},
		                              vd::fn::value_fn_v<vd::is_pointer>)
		              == 1);
					  */
		static_assert(vd::fn::find_if<vd::is_pointer>(vd::fn::list<double, int*, char> {}) == 1);


		template <class F, class...Ts>
		constexpr bool all_of(list<Ts...>, F f) {return (... && f(just_type<Ts> {}));}

		template <template <class...> class F, class...Ts>
		constexpr bool all_of(list<Ts...>) {return (... && F<Ts>::value);}

		template <class F, class...Ts>
		constexpr bool any_of(list<Ts...>, F f) { return (... || f(just_type<Ts> {}));}

		template <template <class...> class F, class...Ts>
		constexpr bool any_of(list<Ts...>) { return (... || F<Ts>::value); }

		template <class F, class...Ts>
		constexpr bool none_of(list<Ts...> tp, F f) { return !any_of(tp, f);}

		template <template <class...> class F, class...Ts>
		constexpr bool none_of(list<Ts...> tp) { return !any_of<F>(tp);}


		static_assert(vd::fn::all_of<vd::is_pointer>(vd::fn::list<int*, double*, char*> {}));
		static_assert(vd::fn::all_of<vd::is_pointer>(vd::fn::empty_list{}));


		static_assert(vd::fn::any_of<vd::is_reference>(vd::fn::list<int&, double, char**> {}));
		static_assert(!vd::fn::any_of<vd::is_reference>(vd::fn::empty_list{}));

		static_assert(vd::fn::none_of<vd::is_void>(vd::fn::list<int, double, char> {}));
		static_assert(vd::fn::none_of<vd::is_void>(vd::fn::empty_list{}));


		template <template <class...> class F, class...Ts>
		constexpr auto transform(list<Ts...>) {
			return list<typename F<Ts>::type...> {};
		}





		template<class T, class F>
		constexpr auto transform_one(F f) {
			return list < decltype(f(just_type<T> {})) > {};
		}

		template <class F, class...Ts>
		constexpr auto transform(list<Ts...>, F f) {
			return (empty_list{} +... + transform_one<Ts>(f));
		}


		static_assert(transform<vd::add_pointer>(	list<int, double, char> {}) ==
		              list<int*, double*, char*> {});



		//=====================reverse=================================================
		template <class... Ts> //finish case
		constexpr auto reverse_impl(empty_list, list<Ts...> res) { return res;}

		template <class T, class... Ts, class...Us> //continue
		constexpr auto reverse_impl(list<T, Ts...>, list<Us...>) {
			return reverse_impl(list<Ts...> {}, list<T, Us...> {});
		}
		template <class... Ts>
		constexpr auto reverse(list<Ts...> tp) { return reverse_impl(tp, {});}


		static_assert(reverse(list<int, double, char> {}) ==
		              list<char, double, int> {});

		//===================genereate=================================================
		template <int I, class T, class...Ts> //continue case
		struct generate_impl {
			using type = typename generate_impl < I - 1, T, Ts..., T >::type;
		};

		template <class T, class...Ts> //finish case
		struct generate_impl<0, T, Ts...> {
			using type = list<Ts...>;
		};

		template <int I, class T>
		constexpr auto generate() { return typename generate_impl<I, T>::type{};}

		template <int CURRENT, int STEP, int END, class...Ts> //finish case
		struct generate_impl_2 {
			using type = typename generate_impl_2 < CURRENT + STEP, STEP, END, Ts...,
			      vd::integral_constant<int, CURRENT >>::type;
		};

		template <int STEP, int END, class...Ts> //finish case
		struct generate_impl_2<END, STEP, END, Ts...> {
			using type = list<Ts..., vd::integral_constant<int, END>>;
		};


		template <int INIT, int STEP, int END>
		constexpr auto generate() { return typename generate_impl_2<INIT, STEP, END>::type{};}

		static_assert(generate<3, int>() == list<int, int, int> {});
		static_assert(generate<0, 1, 3>() ==
		              list<vd::integral_constant<int, 0>, vd::integral_constant<int, 1>, vd::integral_constant<int, 2>, vd::integral_constant<int, 3>> {});
		static_assert(generate<0, -1, -3>() ==
		              list<vd::integral_constant<int, 0>, vd::integral_constant<int, -1>, vd::integral_constant<int, -2>, vd::integral_constant<int, -3>> {});
		//====================foreach===================================================

		template <class F, class...Ts, class ...Args>

		constexpr void foreach (list<Ts...> tp, F f, Args...args) {
			(..., f(just_type<Ts> {}, args...));
		}

		template <class T, class...Ts>
		constexpr size_t count(list<Ts...>) {
			return (0 + ... + vd::is_same<T, Ts>::value);
		}

		template <class T, class...Ts>
		constexpr size_t count(list<Ts...>, just_type<T>) {
			return (0 + ... + vd::is_same<T, Ts>::value);
		}

		template <class F, class...Ts, class ...Args>
		constexpr size_t count_if(list<Ts...>, F f, Args...args) {
			return (0 + ... + f(just_type<Ts> {}, args...));
		}

		static_assert(count<vd::integral_constant<int, 10>>
		              (list<vd::integral_constant<int, 10>, vd::integral_constant<int, 11>, vd::integral_constant<int, 10>> {})
		              == 2);
		static_assert(count_if(
		                  list<vd::integral_constant<int, 10>, vd::integral_constant<int, 11>, vd::integral_constant<int, 10>> {}, [](
		auto b) {
			return vd::is_same<decltype(b), just_type<vd::integral_constant<int, 10>>>::value;
		}) == 2);


		/*template <typename...Ts>
		constexpr  auto pop_back(list<Ts...> l) { return reverse(tail(reverse(l))); }
		*/

		template <typename T, typename...Us>
		constexpr  auto pop_back_impl(list<T> tp, list<Us...> newlist) {
			return newlist;
		}

		template <typename...Ts, typename...Us>
		constexpr  auto pop_back_impl(list<Ts...> tp, list<Us...> newlist) {
			return pop_back_impl(tail(tp), push_back(newlist, head(tp)));
		}

		template <typename...Ts>
		constexpr  auto pop_back(list<Ts...> tp) {
			empty_list res;
			return pop_back_impl(tp, res);
		}

		/*static_assert(pop_back(list<int, double, char>{}) ==list<int, double>{});

		static_assert(pop_back(empty_list{}) ==empty_list{});*/

		//====================filter===================================================

		template<template <class...> class F, class T>
		constexpr auto filter_one() {
			if constexpr (F<T>::value) {
				return list<T> {};
			} else {
				return empty_list{};
			}
		}

		template<template <class...> class F, class... Ts>
		constexpr auto filter(list<Ts...>) {
			return (empty_list{} +... + filter_one<F, Ts>());
		}

		static_assert(filter<vd::is_pointer>(list<char, double*, int*> {}) ==
		              list<double*, int*> {});

		template<class T, class F>
		constexpr auto filter_one(F f) {
			if constexpr (f(just_type<T> {})) {
				return list<T> {};
			} else {
				return empty_list{};
			}
		}

		template<class F, class... Ts>
		constexpr auto filter(list<Ts...>, F f) {
			return (empty_list{} +... + filter_one<Ts, F>(f));
		}

		static_assert(filter<vd::is_pointer>(list<char, double*, int*> {}) ==
		              list<double*, int*> {});


		static_assert(filter(list<char, double*, int> {}, [](auto t) {
			typedef typename decltype(t)::type type;
			return vd::is_same<type, int>::value;
		}) ==
		list<int> {});


		//=================reduce===================================

		template <class U, class F, class... Ts> //finish case
		constexpr U reduce_impl(empty_list, U res, F) { return res;}

		template <class U, class F, class T, class... Ts> //continue
		constexpr U reduce_impl(list<T, Ts...>, U accumulator, F f) {
			U newVal = f(just_type<T> {}, accumulator);
			return reduce_impl(list<Ts...> {}, newVal, f);
		}

		template <class F, class U, typename...Ts>
		constexpr U reduce(list<Ts...> l, F f, U init = U()) {
			return reduce_impl(l, init, f);
		}

		static_assert(reduce(list<vd::integral_constant<int, 10>, vd::integral_constant<int, 20>> {}, [](
		auto b, int accumulator) {
			typedef typename decltype(b)::type type;
			int v = type::value;
			return accumulator + v;
		}, 0) == 30);
		//=========================unique===================================
		template<typename ...Ts>
		constexpr auto is_unique(list<Ts...> tp) {
			auto newList = filter(tp, [tp](auto t) {
				typedef typename decltype(t)::type type;
				return count<type>(tp) == 1;
			});
			return size(tp) == size(newList);
		}

		static_assert(is_unique(list<int, char, float> {}) == true);
		static_assert(is_unique(list<int, char, float, int> {}) == false);

		template <class... Ts> //finish case
		constexpr auto make_unique_impl(empty_list, list<Ts...> res) { return res;}

		template <class T, class... Ts, class...Us> //continue
		constexpr auto make_unique_impl(list<T, Ts...>, list<Us...>) {
			if constexpr (contains<T>(list<Us...> {})) {
				return make_unique_impl(list<Ts...> {}, list<Us...> {});
			} else {
				return make_unique_impl(list<Ts...> {}, list<Us..., T> {});
			}
		}

		template<class... Ts>
		constexpr auto make_unique(list<Ts...> tp) {
			return make_unique_impl(tp, empty_list{});
		}

		static_assert(make_unique(list<int, char, float> {}) == list<int, char, float> {});
		static_assert(make_unique(list<int, char, int, float> {}) == list<int, char, float> {});



		template <typename F, typename ... Args>
		constexpr bool apply_till(list<>, F f, Args...args) {
			return false;
		}

		template <typename F, typename T, typename...Ts, typename ... Args>
		constexpr bool apply_till(list<T, Ts...>, F f, Args...args) {
			if (f(just_type<T> {}, args...)) {
				return true;
			} else {
				return apply_till(list<Ts...> {}, f, args...);
			}
		}


		/*example WITH template function ((auto t))
			auto l = [](auto t, bool& finded){
				typedef typename decltype(t)::type; //type
				finded = button_type::init(); //call any function
				return finded;//true=>not continue
			};
			vd::foreach_func<button1,buttons...>::call(l);
			if (finded)....
		*/

	}
}