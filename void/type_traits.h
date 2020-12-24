#pragma once
#ifdef WIN32
	#include <type_traits>
#endif
#if _MSC_VER // Visual C++ fallback
	#define _STDEX_CDECL __cdecl
#endif
#include "type_traits/next_type.h"

namespace vd {

	namespace intern {
		// since we have no static_assert in pre-C++11 we just compile-time assert this way:
		struct type_traits_asserts {
			template<bool>
			struct make_signed_template_require_that_type_shall_be_a_possibly_cv_qualified_but_integral_type_assert;

			template<bool>
			struct make_unsigned_template_require_that_type_shall_be_a_possibly_cv_qualified_but_integral_type_assert;

			template<bool>
			struct not_allowed_arithmetic_type_assert;

			template<bool>
			struct alignment_of_type_can_not_be_zero_assert;
		};

		template<>
		struct type_traits_asserts::make_signed_template_require_that_type_shall_be_a_possibly_cv_qualified_but_integral_type_assert<true> {
			typedef bool
			make_signed_template_require_that_type_shall_be_a_possibly_cv_qualified_but_integral_type_assert_failed;
		};

		template<>
		struct type_traits_asserts::make_unsigned_template_require_that_type_shall_be_a_possibly_cv_qualified_but_integral_type_assert<true> {
			typedef bool
			make_unsigned_template_require_that_type_shall_be_a_possibly_cv_qualified_but_integral_type_assert_failed;
		};

		template<>
		struct type_traits_asserts::not_allowed_arithmetic_type_assert<true> {
			typedef bool not_allowed_arithmetic_type_assert_failed;
		};

		template<>
		struct type_traits_asserts::alignment_of_type_can_not_be_zero_assert<true> {
			typedef bool alignment_of_type_can_not_be_zero_assert_failed;
		};
	}




	//#ifndef WIN32
	template <bool condition, typename Type>
	struct enable_if;

	template <typename Type>
	struct enable_if<true, Type> {
		using type = Type;
	};

	template<bool C, class T = void>
	using enable_if_t = typename vd::enable_if<C, T>::type;

	template<class _Tp, _Tp Val>
	struct integral_constant {
		// convenient template for integral constant types
		static const _Tp value = Val;

		typedef const _Tp value_type;
		typedef integral_constant<_Tp, Val> type;

		operator value_type() const {
			// return stored value
			return (value);
		}

		value_type operator()() const {
			// return stored value
			return (value);
		}
	};

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;




	template <int VAL>
	using constInt = integral_constant<int, VAL>;

	template<bool Val>
	struct bool_constant : public integral_constant<bool, Val> {};

	// Primary template.
	// Define a member typedef @c type to one of two argument types.
	template<bool _Cond, class _Iftrue, class _Iffalse>
	struct conditional {
		typedef _Iftrue type;
	};

	// Partial specialization for false.
	template<class _Iftrue, class _Iffalse>
	struct conditional<false, _Iftrue, _Iffalse> {
		typedef _Iffalse type;
	};

	//���������� �������� {��, ����, ���} ��� ������
	namespace detail {
		struct void_type {};
		typedef char _yes_type;
		struct _no_type {
			char padding[8];
		};
		//typedef void void_type;

		template<class _B1 = void_type, class _B2 = void_type, class _B3 = void_type, class _B4 = void_type>
		struct _or_ :
			public conditional<_B1::value, _B1, _or_<_B2, _or_<_B3, _B4> > >::type
		{ };


		template<>
		struct _or_<void_type, void_type, void_type, void_type>;

		template<class _B1>
		struct _or_<_B1, void_type, void_type, void_type> :
			public _B1
		{ };

		template<class _B1, class _B2>
		struct _or_<_B1, _B2, void_type, void_type> :
			public conditional<_B1::value, _B1, _B2>::type
		{ };

		template<class _B1, class _B2, class _B3>
		struct _or_<_B1, _B2, _B3, void_type> :
			public conditional<_B1::value, _B1, _or_<_B2, _B3> >::type
		{ };

		template<class _B1 = void_type, class _B2 = void_type, class _B3 = void_type, class _B4 = void_type>
		struct _and_;


		template<>
		struct _and_<void_type, void_type, void_type, void_type>;

		template<class _B1>
		struct _and_<_B1, void_type, void_type, void_type> :
			public _B1
		{ };

		template<class _B1, class _B2>
		struct _and_<_B1, _B2, void_type, void_type> :
			public conditional<_B1::value, _B2, _B1>::type
		{ };

		template<class _B1, class _B2, class _B3>
		struct _and_<_B1, _B2, _B3, void_type> :
			public conditional<_B1::value, _and_<_B2, _B3>, _B1>::type
		{ };

		template<class _Pp>
		struct _not_ {
			static const bool value = !bool(_Pp::value);

			typedef const bool value_type;
			typedef integral_constant<bool, _not_::value == bool(true)> type;

			operator bool() const {
				// return stored value
				return (value);
			}

			bool operator()() const {
				// return stored value
				return (value);
			}
		};
	}





	template<class T, class U>
	struct is_same : vd::false_type {};

	template<class T>
	struct is_same<T, T> : true_type {};




	//c++17
	template< class T, class U >
	constexpr bool is_same_v = is_same<T, U>::value;
	//end c++17

	// is_reference
	template<class _Tp>
	struct is_reference :
	//public detail::_or_<is_lvalue_reference<_Tp>, is_rvalue_reference<_Tp> >::type
		public vd::false_type
	{};

	template<class _Tp>
	struct is_reference<_Tp&> :
		public true_type
	{};


	template <class _Tp>
	struct is_const : public vd::false_type { };

	template <class _Tp>
	struct is_const<const _Tp> : public true_type { };

	template <class _Tp>
	struct is_const<const volatile _Tp> : public true_type { };

	namespace detail {

		template <class _R>
		struct _is_function_ptr_helper : public vd::false_type {};



		template <class _R >
struct _is_function_ptr_helper<_R(*)()> : public vd::true_type {};
		template <class _R >
struct _is_function_ptr_helper<_R(*)(...)> : public vd::true_type {};
		template <class _R, class _T0>
struct _is_function_ptr_helper<_R(*)(_T0)> : public vd::true_type {};
		template <class _R, class _T0>
struct _is_function_ptr_helper<_R(*)(_T0 ...)> : public vd::true_type {};
		template <class _R, class _T0, class _T1>
struct _is_function_ptr_helper<_R(*)(_T0, _T1)> : public vd::true_type {};
		template <class _R, class _T0, class _T1>
struct _is_function_ptr_helper<_R(*)(_T0, _T1 ...)> : public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2)> : public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2 ...)> : public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3)> : public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3 ...)> : public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4)> : public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4 ...)> : public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5)> : public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5 ...)> : public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6)> : public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6 ...)> : public
		vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7)> : public
		vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7 ...)> : public
		vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8)> : public
		vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8 ...)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9 ...)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10 ...)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11 ...)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12 ...)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13 ...)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14 ...)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15 ...)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15, class _T16>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15, class _T16>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16 ...)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15, class _T16, class _T17>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15, class _T16, class _T17>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17 ...)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15, class _T16, class _T17, class _T18>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17, _T18)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15, class _T16, class _T17, class _T18>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17, _T18 ...)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15, class _T16, class _T17, class _T18, class _T19>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17, _T18, _T19)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15, class _T16, class _T17, class _T18, class _T19>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17, _T18, _T19 ...)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15, class _T16, class _T17, class _T18, class _T19, class _T20>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17, _T18, _T19, _T20)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15, class _T16, class _T17, class _T18, class _T19, class _T20>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17, _T18, _T19, _T20 ...)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15, class _T16, class _T17, class _T18, class _T19, class _T20, class _T21>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17, _T18, _T19, _T20, _T21)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15, class _T16, class _T17, class _T18, class _T19, class _T20, class _T21>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17, _T18, _T19, _T20, _T21 ...)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15, class _T16, class _T17, class _T18, class _T19, class _T20, class _T21, class _T22>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17, _T18, _T19, _T20, _T21, _T22)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15, class _T16, class _T17, class _T18, class _T19, class _T20, class _T21, class _T22>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17, _T18, _T19, _T20, _T21, _T22 ...)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15, class _T16, class _T17, class _T18, class _T19, class _T20, class _T21, class _T22, class _T23>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17, _T18, _T19, _T20, _T21, _T22, _T23)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15, class _T16, class _T17, class _T18, class _T19, class _T20, class _T21, class _T22, class _T23>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17, _T18, _T19, _T20, _T21, _T22, _T23 ...)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15, class _T16, class _T17, class _T18, class _T19, class _T20, class _T21, class _T22, class _T23, class _T24>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17, _T18, _T19, _T20, _T21, _T22, _T23, _T24)> :
		public vd::true_type {};
		template <class _R, class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15, class _T16, class _T17, class _T18, class _T19, class _T20, class _T21, class _T22, class _T23, class _T24>
struct _is_function_ptr_helper<_R(*)(_T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17, _T18, _T19, _T20, _T21, _T22, _T23, _T24 ...)> :
		public vd::true_type {};


#undef _STDEX_TYPES
#undef _STDEX_ARGS
#undef _STDEX_IS_MEM_FUN_PTR
#undef _STDEX_IS_MEM_FUN_PTR_CLR
#undef _STDEX_IS_MEM_FUN_CDECL_PTR
#undef _STDEX_IS_MEM_FUN_STDCALL_PTR
#undef _STDEX_IS_MEM_FUN_FASTCALL_PTR

#define _STDEX_IS_MEM_FUN_PTR_CLR \
	template <class _R, class _Tp _STDEX_TYPES > \
	_yes_type _is_mem_function_ptr( _R ( _Tp::*const volatile*)(_STDEX_ARGS)); \
	template <class _R, class _Tp _STDEX_TYPES > \
	_yes_type _is_mem_function_ptr( _R ( _Tp::*const volatile*)(_STDEX_ARGS...)); \
	template <class _R, class _Tp _STDEX_TYPES > \
	_yes_type _is_mem_function_ptr( _R ( _Tp::*const volatile*)(_STDEX_ARGS) const); \
	template <class _R, class _Tp _STDEX_TYPES > \
	_yes_type _is_mem_function_ptr( _R ( _Tp::*const volatile*)(_STDEX_ARGS) volatile); \
	template <class _R, class _Tp _STDEX_TYPES > \
	_yes_type _is_mem_function_ptr( _R ( _Tp::*const volatile*)(_STDEX_ARGS) const volatile); \
	template <class _R, class _Tp _STDEX_TYPES > \
	_yes_type _is_mem_function_ptr( _R ( _Tp::*const volatile*)(_STDEX_ARGS...) const); \
	template <class _R, class _Tp _STDEX_TYPES > \
	_yes_type _is_mem_function_ptr( _R ( _Tp::*const volatile*)(_STDEX_ARGS...) volatile); \
	template <class _R, class _Tp _STDEX_TYPES > \
	_yes_type _is_mem_function_ptr( _R ( _Tp::*const volatile*)(_STDEX_ARGS...) const volatile);

		#ifdef _STDEX_CDECL
		_no_type _STDEX_CDECL _is_mem_function_ptr(...);

#define _STDEX_IS_MEM_FUN_CDECL_PTR \
	template <class _R, class _Tp _STDEX_TYPES > \
	_yes_type _is_mem_function_ptr( _R(__cdecl _Tp::*const volatile*)(_STDEX_ARGS)); \
	template <class _R, class _Tp _STDEX_TYPES > \
	_yes_type _is_mem_function_ptr( _R(__cdecl _Tp::*const volatile*)(_STDEX_ARGS) const); \
	template <class _R, class _Tp _STDEX_TYPES > \
	_yes_type _is_mem_function_ptr( _R(__cdecl _Tp::*const volatile*)(_STDEX_ARGS) volatile); \
	template <class _R, class _Tp _STDEX_TYPES > \
	_yes_type _is_mem_function_ptr( _R(__cdecl _Tp::*const volatile*)(_STDEX_ARGS) const volatile);

#define _STDEX_IS_MEM_FUN_STDCALL_PTR \
	template <class _R, class _Tp _STDEX_TYPES > \
	_yes_type _is_mem_function_ptr( _R(__stdcall _Tp::*const volatile*)(_STDEX_ARGS)); \
	template <class _R, class _Tp _STDEX_TYPES > \
	_yes_type _is_mem_function_ptr( _R(__stdcall _Tp::*const volatile*)(_STDEX_ARGS) const); \
	template <class _R, class _Tp _STDEX_TYPES > \
	_yes_type _is_mem_function_ptr( _R(__stdcall _Tp::*const volatile*)(_STDEX_ARGS) volatile); \
	template <class _R, class _Tp _STDEX_TYPES > \
	_yes_type _is_mem_function_ptr( _R(__stdcall _Tp::*const volatile*)(_STDEX_ARGS) const volatile);

#define _STDEX_IS_MEM_FUN_FASTCALL_PTR \
	template <class _R, class _Tp _STDEX_TYPES > \
	_yes_type _is_mem_function_ptr( _R(__fastcall _Tp::*const volatile*)(_STDEX_ARGS)); \
	template <class _R, class _Tp _STDEX_TYPES > \
	_yes_type _is_mem_function_ptr( _R(__fastcall _Tp::*const volatile*)(_STDEX_ARGS) const); \
	template <class _R, class _Tp _STDEX_TYPES > \
	_yes_type _is_mem_function_ptr( _R(__fastcall _Tp::*const volatile*)(_STDEX_ARGS) volatile); \
	template <class _R, class _Tp _STDEX_TYPES > \
	_yes_type _is_mem_function_ptr( _R(__fastcall _Tp::*const volatile*)(_STDEX_ARGS) const volatile);
		#else
		_no_type _is_mem_function_ptr(...);
#define _STDEX_IS_MEM_FUN_CDECL_PTR
#define _STDEX_IS_MEM_FUN_STDCALL_PTR
#define _STDEX_IS_MEM_FUN_FASTCALL_PTR
		#endif

#define _STDEX_IS_MEM_FUN_PTR \
	_STDEX_IS_MEM_FUN_PTR_CLR \
	_STDEX_IS_MEM_FUN_CDECL_PTR \
	_STDEX_IS_MEM_FUN_STDCALL_PTR \
	_STDEX_IS_MEM_FUN_FASTCALL_PTR

#define _STDEX_TYPES
#define _STDEX_ARGS
		_STDEX_IS_MEM_FUN_PTR
#undef _STDEX_TYPES
#undef _STDEX_ARGS

#define _STDEX_TYPES , class _T0
#define _STDEX_ARGS _T0
		_STDEX_IS_MEM_FUN_PTR
#undef _STDEX_TYPES
#undef _STDEX_ARGS

#define _STDEX_TYPES , class _T0, class _T1
#define _STDEX_ARGS _T0, _T1
		_STDEX_IS_MEM_FUN_PTR
#undef _STDEX_TYPES
#undef _STDEX_ARGS

#define _STDEX_TYPES , class _T0, class _T1, class _T2
#define _STDEX_ARGS _T0, _T1, _T2
		_STDEX_IS_MEM_FUN_PTR
#undef _STDEX_TYPES
#undef _STDEX_ARGS

#define _STDEX_TYPES , class _T0, class _T1, class _T2, class _T3
#define _STDEX_ARGS _T0, _T1, _T2, _T3
		_STDEX_IS_MEM_FUN_PTR
#undef _STDEX_TYPES
#undef _STDEX_ARGS

#define _STDEX_TYPES , class _T0, class _T1, class _T2, class _T3, class _T4
#define _STDEX_ARGS _T0, _T1, _T2, _T3, _T4
		_STDEX_IS_MEM_FUN_PTR
#undef _STDEX_TYPES
#undef _STDEX_ARGS

#define _STDEX_TYPES , class _T0, class _T1, class _T2, class _T3, class _T4, class _T5
#define _STDEX_ARGS _T0, _T1, _T2, _T3, _T4, _T5
		_STDEX_IS_MEM_FUN_PTR
#undef _STDEX_TYPES
#undef _STDEX_ARGS

#define _STDEX_TYPES , class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6
#define _STDEX_ARGS _T0, _T1, _T2, _T3, _T4, _T5, _T6
		_STDEX_IS_MEM_FUN_PTR
#undef _STDEX_TYPES
#undef _STDEX_ARGS

#define _STDEX_TYPES , class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7
#define _STDEX_ARGS _T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7
		_STDEX_IS_MEM_FUN_PTR
#undef _STDEX_TYPES
#undef _STDEX_ARGS

#define _STDEX_TYPES , class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8
#define _STDEX_ARGS _T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8
		_STDEX_IS_MEM_FUN_PTR
#undef _STDEX_TYPES
#undef _STDEX_ARGS

#define _STDEX_TYPES , class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9
#define _STDEX_ARGS _T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9
		_STDEX_IS_MEM_FUN_PTR
#undef _STDEX_TYPES
#undef _STDEX_ARGS

#define _STDEX_TYPES , class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10
#define _STDEX_ARGS _T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10
		_STDEX_IS_MEM_FUN_PTR
#undef _STDEX_TYPES
#undef _STDEX_ARGS

#define _STDEX_TYPES , class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11
#define _STDEX_ARGS _T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11
		_STDEX_IS_MEM_FUN_PTR
#undef _STDEX_TYPES
#undef _STDEX_ARGS

#define _STDEX_TYPES , class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12
#define _STDEX_ARGS _T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12
		_STDEX_IS_MEM_FUN_PTR
#undef _STDEX_TYPES
#undef _STDEX_ARGS

#define _STDEX_TYPES , class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13
#define _STDEX_ARGS _T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13
		_STDEX_IS_MEM_FUN_PTR
#undef _STDEX_TYPES
#undef _STDEX_ARGS

#define _STDEX_TYPES , class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14
#define _STDEX_ARGS _T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14
		_STDEX_IS_MEM_FUN_PTR
#undef _STDEX_TYPES
#undef _STDEX_ARGS

#define _STDEX_TYPES , class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15
#define _STDEX_ARGS _T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15
		_STDEX_IS_MEM_FUN_PTR
#undef _STDEX_TYPES
#undef _STDEX_ARGS

#define _STDEX_TYPES , class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15, class _T16
#define _STDEX_ARGS _T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16
		_STDEX_IS_MEM_FUN_PTR
#undef _STDEX_TYPES
#undef _STDEX_ARGS

#define _STDEX_TYPES , class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15, class _T16, class _T17
#define _STDEX_ARGS _T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17
		_STDEX_IS_MEM_FUN_PTR
#undef _STDEX_TYPES
#undef _STDEX_ARGS

#define _STDEX_TYPES , class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15, class _T16, class _T17, class _T18
#define _STDEX_ARGS _T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17, _T18
		_STDEX_IS_MEM_FUN_PTR
#undef _STDEX_TYPES
#undef _STDEX_ARGS

#define _STDEX_TYPES , class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15, class _T16, class _T17, class _T18, class _T19
#define _STDEX_ARGS _T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17, _T18, _T19
		_STDEX_IS_MEM_FUN_PTR
#undef _STDEX_TYPES
#undef _STDEX_ARGS

#define _STDEX_TYPES , class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15, class _T16, class _T17, class _T18, class _T19, class _T20
#define _STDEX_ARGS _T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17, _T18, _T19, _T20
		_STDEX_IS_MEM_FUN_PTR
#undef _STDEX_TYPES
#undef _STDEX_ARGS

#define _STDEX_TYPES , class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15, class _T16, class _T17, class _T18, class _T19, class _T20, class _T21
#define _STDEX_ARGS _T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17, _T18, _T19, _T20, _T21
		_STDEX_IS_MEM_FUN_PTR
#undef _STDEX_TYPES
#undef _STDEX_ARGS

#define _STDEX_TYPES , class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15, class _T16, class _T17, class _T18, class _T19, class _T20, class _T21, class _T22
#define _STDEX_ARGS _T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17, _T18, _T19, _T20, _T21, _T22
		_STDEX_IS_MEM_FUN_PTR
#undef _STDEX_TYPES
#undef _STDEX_ARGS

#define _STDEX_TYPES , class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15, class _T16, class _T17, class _T18, class _T19, class _T20, class _T21, class _T22, class _T23
#define _STDEX_ARGS _T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17, _T18, _T19, _T20, _T21, _T22, _T23
		_STDEX_IS_MEM_FUN_PTR
#undef _STDEX_TYPES
#undef _STDEX_ARGS

#define _STDEX_TYPES , class _T0, class _T1, class _T2, class _T3, class _T4, class _T5, class _T6, class _T7, class _T8, class _T9, class _T10, class _T11, class _T12, class _T13, class _T14, class _T15, class _T16, class _T17, class _T18, class _T19, class _T20, class _T21, class _T22, class _T23, class _T24
#define _STDEX_ARGS _T0, _T1, _T2, _T3, _T4, _T5, _T6, _T7, _T8, _T9, _T10, _T11, _T12, _T13, _T14, _T15, _T16, _T17, _T18, _T19, _T20, _T21, _T22, _T23, _T24
		_STDEX_IS_MEM_FUN_PTR
#undef _STDEX_TYPES
#undef _STDEX_ARGS

#undef _STDEX_IS_MEM_FUN_PTR
#undef _STDEX_IS_MEM_FUN_PTR_CLR
#undef _STDEX_IS_MEM_FUN_CDECL_PTR
#undef _STDEX_IS_MEM_FUN_STDCALL_PTR
#undef _STDEX_IS_MEM_FUN_FASTCALL_PTR


		template <class _Tp, bool _IsRef>
		struct _is_mem_function_ptr_impl {
			static _Tp* _ptr;
			static const bool value = (sizeof(_is_mem_function_ptr(_is_mem_function_ptr_impl::_ptr)) == sizeof(
			                               _yes_type));

			typedef typename vd::integral_constant<bool, _is_mem_function_ptr_impl::value == bool(true)>::type
			type;
		};

		template <class _Tp>
		struct _is_mem_function_ptr_impl<_Tp, true> :
			public vd::false_type
		{};

		template <class _Tp>
		struct _is_mem_function_ptr_helper :
			public _is_mem_function_ptr_impl<_Tp, is_reference<_Tp>::value>::type
		{};

		template <class _Tp, bool _IsMemberFunctionPtr>
		struct _is_function_chooser_impl :
			public vd::false_type
		{ };

		template <class _Tp>
		struct _is_function_chooser_impl<_Tp, false> :
			public vd::detail::_is_function_ptr_helper<_Tp*>
		{ };

		template<class _Tp, bool _IsRef = true>
		struct _is_function_chooser :
			public vd::false_type
		{ };

		//template <class _Tp>
		//struct _is_function_chooser<_Tp, false> {
		//	static const bool value =
		//	    vd::detail::_is_function_ptr_helper<int(*)(int)>::value;
		//};

		template <class _Tp>
		struct _is_function_chooser<_Tp, false> {
			static const bool value =
			    _is_function_chooser_impl<_Tp, _is_mem_function_ptr_helper<_Tp>::value>::value;
		};

	}

	// is_function
	template<class _Tp>
	struct is_function {
		static const bool value = detail::_is_function_chooser<_Tp, is_reference<_Tp>::value>::value;

		typedef const bool value_type;
		typedef integral_constant<bool, is_function::value == bool(true)> type;

		operator bool() const {
			// return stored value
			return (value);
		}

		bool operator()() const {
			// return stored value
			return (value);
		}
	};


	namespace detail {
		template<class>
		struct _is_void_helper
			: public vd::false_type { };

		template<>
		struct _is_void_helper<void>
			: public true_type { };

		template<class _Tp>
		_Tp(&_is_incomplete_type_tester_helper(int))[1];
		template<class _Tp>
		void* _is_incomplete_type_tester_helper(...);

		_yes_type _is_incomplete_type_tester(void*);
		template<class _Tp>
		_no_type _is_incomplete_type_tester(_Tp(&)[1]);

		template<class _Tp>
		struct _is_incomplete_type_helper {
			static const bool value = sizeof(_is_incomplete_type_tester(_is_incomplete_type_tester_helper<_Tp>
			                                 (0))) == sizeof(_yes_type);
		};

		template<class _Tp>
		struct _is_incomplete_type {
			static const bool value = _is_incomplete_type_helper<_Tp>::value;
			typedef integral_constant<bool, _is_incomplete_type_helper<_Tp>::value == bool(true)> type;
		};

		template<>
		struct _is_incomplete_type<void> :
			vd::false_type
		{ };

		template<class _Tp, bool ImplCh = _is_incomplete_type<char[]>::value>
		struct _is_array_impl :
			_and_<_is_incomplete_type<_Tp>, _not_<is_function<_Tp> > >::type
		{ };

		template<class _Tp>
		struct _is_array_impl<_Tp, false> :
			vd::false_type
		{ };

		template<class _Tp>
		struct _is_array_impl<_Tp[], false> :
			true_type
		{ };
	}



	template<class _Tp>
	struct remove_cv;

	// is_void
	template<class _Tp>
	struct is_void :
		public detail::_is_void_helper<typename remove_cv<_Tp>::type>::type
	{ };


	// is_object
	template<class _Tp>
	struct is_object :
		public detail::_not_< detail::_or_< is_function<_Tp>, is_reference<_Tp>, is_void<_Tp> > >::type
	{};

	namespace detail {
		template<class _Tp>
		struct _is_referenceable :
			public _or_<is_object<_Tp>, is_reference<_Tp>, is_function<_Tp> >::type
		{ };
	}





	/// is_volatile
	template<class>
	struct is_volatile : public vd::false_type { };

	template<class _Tp>
	struct is_volatile<volatile _Tp> : public true_type { };

	template<class _Tp>
	struct is_volatile<const volatile _Tp> : public true_type { };

	// is_array
	template<class>
	struct is_array : public vd::false_type { };

	template<class _Tp, size_t _Size>
	struct is_array<_Tp[_Size]> : public true_type { };

	//template<class _Tp>
	//struct is_array<_Tp[]>: public true_type { };


	namespace detail {
		template <class T>
		char test(int T::*);

		struct two { char c[2]; };
		template <class T>
		two test(...);
	}

	template <class T>
	struct is_class : integral_constant
	< bool, sizeof(detail::test<T>(0)) == 1 > //&& !std::is_union<T>::value
	{};
	template< class T >
	constexpr bool is_class_v = is_class<T>::value;


	template< class T > struct remove_reference { typedef T type; };
	template< class T > struct remove_reference<T&> { typedef T type; };
	template< class T > struct remove_reference < T&& > { typedef T type; };



	// remove top level const qualifier
	template<class _Tp> struct remove_const { typedef _Tp type; };

	// remove top level const qualifier
	template<class _Tp>
	struct remove_const<const _Tp> {  typedef _Tp type; };
	// remove top level const qualifier
	template<class _Tp>
	struct remove_const<const volatile _Tp> { typedef volatile _Tp type; };

	// remove top level volatile qualifier
	template<class _Tp>
	struct remove_volatile { typedef _Tp type; };
	// remove top level volatile qualifier
	template<class _Tp>
	struct remove_volatile<volatile _Tp> {typedef _Tp type; };

	// remove top level const and volatile qualifiers
	template<class _Tp>
	struct remove_cv { typedef typename remove_const<typename remove_volatile<_Tp>::type>::type type; };




	// remove_extent
	template<class _Tp>
	struct remove_extent {
		typedef _Tp     type;
	};


	template<class _Tp, size_t _Size>
	struct remove_extent<_Tp[_Size]> {
		typedef _Tp     type;
	};

	template<class _Tp, size_t _Size>
	struct remove_extent< const _Tp[_Size]> {
		typedef const _Tp     type;
	};

	template<class _Tp, size_t _Size>
	struct remove_extent< volatile _Tp[_Size]> {
		typedef volatile _Tp     type;
	};

	template<class _Tp, size_t _Size>
	struct remove_extent< const volatile _Tp[_Size]> {
		typedef const volatile _Tp     type;
	};

	//template<class _Tp>
	//struct remove_extent<_Tp []>
	//{
	//	typedef _Tp type;
	//};

	// remove_all_extents
	template<class _Tp>
	struct remove_all_extents {
		typedef _Tp     type;
	};

	template<class _Tp, size_t _Size>
	struct remove_all_extents<_Tp[_Size]> {
		typedef typename remove_all_extents<_Tp>::type     type;
	};

	template<class _Tp, size_t _Size>
	struct remove_all_extents<const _Tp[_Size]> {
		typedef const typename remove_all_extents<const _Tp>::type     type;
	};

	template<class _Tp, size_t _Size>
	struct remove_all_extents<volatile _Tp[_Size]> {
		typedef volatile typename remove_all_extents<volatile _Tp>::type     type;
	};

	template<class _Tp, size_t _Size>
	struct remove_all_extents<const volatile _Tp[_Size]> {
		typedef const volatile typename remove_all_extents<const volatile _Tp>::type     type;
	};


	template< class T > struct is_pointer_helper     : vd::false_type {};
	template< class T > struct is_pointer_helper<T*> : vd::true_type {};
	template< class T > struct is_pointer : is_pointer_helper<typename vd::remove_cv<T>::type> {};



	template<typename> struct is_integral_base : vd::false_type {};

	template<> struct is_integral_base<bool> : vd::true_type {};
	template<> struct is_integral_base<char> : vd::true_type {};
	template<> struct is_integral_base<unsigned char> : vd::true_type {};
	template<> struct is_integral_base<int> : vd::true_type {};
	template<> struct is_integral_base<unsigned int> : vd::true_type {};
	template<> struct is_integral_base<short> : vd::true_type {};
	template<> struct is_integral_base<unsigned short> : vd::true_type {};
	template<> struct is_integral_base<long int> : vd::true_type {};
	template<> struct is_integral_base<unsigned long int> : vd::true_type {};
	template<> struct is_integral_base<long long int> : vd::true_type {};
	template<> struct is_integral_base<unsigned long long int> : vd::true_type {};
	//template<> struct is_integral_base<enable_if_t<!vd::is_same_v<size_t,unsigned long long int>,size_t>> : vd::true_type {};

	template<typename T> struct is_integral :
		is_integral_base<typename vd::remove_all_extents<T>::type> {};

	template< class T >
	constexpr bool is_integral_v = is_integral<T>::value;

	template< class T >
	struct is_floating_point : integral_constant <
		bool,
		is_same<float, typename remove_cv<T>::type>::value ||
		is_same<double, typename remove_cv<T>::type>::value ||
		is_same<long double, typename remove_cv<T>::type>::value
		> {
	};
	template< class T >
	constexpr bool is_floating_point_v = is_floating_point<T>::value;




	namespace detail {

		template <class T>
		struct type_identity { using type = T; }; // or use std::type_identity (since C++20)

		template <class T>
		auto try_add_lvalue_reference(int) -> type_identity<T&>;
		template <class T>
		auto try_add_lvalue_reference(...) -> type_identity<T>;

		template <class T>
		auto try_add_rvalue_reference(int) -> type_identity < T&& >;
		template <class T>
		auto try_add_rvalue_reference(...) -> type_identity<T>;

	} // namespace detail


	template <class T>
	struct add_lvalue_reference : decltype(detail::try_add_lvalue_reference<T>(0)) {};

	template <class T>
	struct add_rvalue_reference : decltype(detail::try_add_rvalue_reference<T>(0)) {};

	template<class T>
	constexpr typename vd::add_rvalue_reference<T>::type declval() noexcept;


	//template<class _Tp>
	//struct remove_all_extents<_Tp []>
	//{
	//	typedef typename remove_all_extents<_Tp>::type type;
	//};

	namespace detail {
		// Utility for constructing identically cv-qualified types.
		template<class _Unqualified, bool _IsConst, bool _IsVol>
		struct _cv_selector;

		template<class _Unqualified>
		struct _cv_selector<_Unqualified, false, false> {
			typedef _Unqualified _type;
		};

		template<class _Unqualified>
		struct _cv_selector<_Unqualified, false, true> {
			typedef volatile _Unqualified _type;
		};

		template<class _Unqualified>
		struct _cv_selector<_Unqualified, true, false> {
			typedef const _Unqualified _type;
		};

		template<class _Unqualified>
		struct _cv_selector<_Unqualified, true, true> {
			typedef const volatile _Unqualified _type;
		};

		template<class _Qualified, class _Unqualified, bool _IsConst = is_const<_Qualified>::value, bool _IsVol = is_volatile<_Qualified>::value>
		class _match_cv_qualifiers {
				typedef _cv_selector<_Unqualified, _IsConst, _IsVol> _match;

			public:
				typedef typename _match::_type _type;
		};

		// Utility for finding the unsigned versions of signed integral types.
		template<class _Tp>
		struct _make_unsigned {
			typedef _Tp _type;
		};

		template<>
		struct _make_unsigned<char> {
			typedef unsigned char _type;
		};

		template<>
		struct _make_unsigned<signed char> {
			typedef unsigned char _type;
		};

		template<>
		struct _make_unsigned<short> {
			typedef unsigned short _type;
		};

		template<>
		struct _make_unsigned<int> {
			typedef unsigned int _type;
		};

		template<>
		struct _make_unsigned<long> {
			typedef unsigned long _type;
		};

		#if defined(LLONG_MIN) && defined(LLONG_MAX)
		template<>
		struct _make_unsigned<long long> {
			typedef unsigned long long _type;
		};
		#endif


		template<class _Tp>
		class _make_unsigned_selector {
			private:
				typedef intern::type_traits_asserts check;

				//typedef typename
				//check::make_unsigned_template_require_that_type_shall_be_a_possibly_cv_qualified_but_integral_type_assert< is_integral<_Tp>::value >::
				//make_unsigned_template_require_that_type_shall_be_a_possibly_cv_qualified_but_integral_type_assert_failed
				//check1; // if you are there means _Tp is not an integral type

				typedef unsigned char _smallest;
				static const bool _b0 = sizeof(_Tp) <= sizeof(_smallest);
				static const bool _b1 = sizeof(_Tp) <= sizeof(unsigned short);
				static const bool _b2 = sizeof(_Tp) <= sizeof(unsigned int);
				static const bool _b3 = sizeof(_Tp) <= sizeof(unsigned long);
				#if defined(ULLONG_MAX)
				typedef conditional<_make_unsigned_selector<_Tp>::_b3, unsigned long, unsigned long long> _cond3;
				#else
				typedef conditional<_make_unsigned_selector<_Tp>::_b3, unsigned long, unsigned long> _cond3;
				#endif
				typedef typename _cond3::type _cond3_type;
				typedef conditional<_make_unsigned_selector<_Tp>::_b2, unsigned int, _cond3_type> _cond2;
				typedef typename _cond2::type _cond2_type;
				typedef conditional<_make_unsigned_selector<_Tp>::_b1, unsigned short, _cond2_type> _cond1;
				typedef typename _cond1::type _cond1_type;

				typedef typename conditional<_make_unsigned_selector<_Tp>::_b0, _smallest, _cond1_type>::type
				_unsigned_type;
				typedef _match_cv_qualifiers<_Tp, _unsigned_type> _cv_unsigned;

			public:
				typedef typename _cv_unsigned::_type _type;
		};
	}

	// make_unsigned
	template<class _Tp>
	struct make_unsigned {
		typedef typename detail::_make_unsigned_selector<_Tp>::_type type;
	};

	template<class _Tp>
	struct make_unsigned<_Tp const> {
		typedef const typename detail::_make_unsigned_selector<_Tp const>::_type type;
	};

	template<class _Tp>
	struct make_unsigned<_Tp volatile> {
		typedef volatile typename detail::_make_unsigned_selector<_Tp volatile>::_type type;
	};

	template<class _Tp>
	struct make_unsigned<_Tp const volatile> {
		typedef const volatile typename detail::_make_unsigned_selector<_Tp const volatile>::_type type;
	};

	// Integral, but don't define.
	template<>
	struct make_unsigned<bool>;
	template<typename T>
	using make_unsigned_t = typename make_unsigned<T>::type;


	// make_signed

	namespace detail {
		// Utility for finding the signed versions of unsigned integral types.
		template<class _Tp>
		struct _make_signed {
			typedef _Tp _type;
		};

		template<>
		struct _make_signed<char> {
			typedef signed char _type;
		};

		template<>
		struct _make_signed<unsigned char> {
			typedef signed char _type;
		};

		template<>
		struct _make_signed<unsigned short> {
			typedef signed short _type;
		};

		template<>
		struct _make_signed<unsigned int> {
			typedef signed int _type;
		};

		template<>
		struct _make_signed<unsigned long> {
			typedef signed long _type;
		};

		#if defined(ULLONG_MAX)
		template<>
		struct _make_signed<unsigned long long> {
			typedef signed long long _type;
		};
		#endif

		template<class _Tp>
		class _make_signed_selector {
			private:
				typedef intern::type_traits_asserts check;

				//typedef typename
				//check::make_signed_template_require_that_type_shall_be_a_possibly_cv_qualified_but_integral_type_assert< is_integral<_Tp>::value >::
				//make_signed_template_require_that_type_shall_be_a_possibly_cv_qualified_but_integral_type_assert_failed
				//check1; // if you are there means _Tp is not an integral type

				typedef typename _make_unsigned_selector<_Tp>::_type _unsigned_type;

				typedef _make_signed<typename remove_cv<_unsigned_type>::type> _signedt;
				typedef typename _signedt::_type _signed_type;
				typedef _match_cv_qualifiers<_unsigned_type, _signed_type> _cv_signed;

			public:
				typedef typename _cv_signed::_type _type;
		};
	}




	template<class _Tp>
	struct make_signed {
		typedef typename detail::_make_signed_selector<_Tp>::_type type;
	};



	template<class _Tp>
	struct make_signed<_Tp const> {
		typedef const typename detail::_make_signed_selector<_Tp const>::_type type;
	};

	template<class _Tp>
	struct make_signed<_Tp volatile> {
		typedef volatile typename detail::_make_signed_selector<_Tp volatile>::_type type;
	};

	template<class _Tp>
	struct make_signed<_Tp const volatile> {
		typedef const volatile typename detail::_make_signed_selector<_Tp const volatile>::_type type;
	};




	// Integral, but don't define.
	template<>
	struct make_signed<bool>;


	template<typename T>
	using make_signed_t = typename make_signed<T>::type;






	//add_pointer
	namespace detail {
		template<class _Tp, bool>
		struct _add_pointer_helper {
			typedef _Tp     type;
		};

		template<class _Tp>
		struct _add_pointer_helper<_Tp, true> {
			typedef typename remove_reference<_Tp>::type*     type;
		};

		template<class _Tp>
		struct _add_pointer_helper<const _Tp, true> {
			typedef const typename remove_reference<_Tp>::type*     type;
		};

		template<class _Tp>
		struct _add_pointer_helper<volatile _Tp, true> {
			typedef volatile typename remove_reference<_Tp>::type*     type;
		};

		template<class _Tp>
		struct _add_pointer_helper<const volatile _Tp, true> {
			typedef const volatile typename remove_reference<_Tp>::type*     type;
		};
	}

	// add_pointer
	template<class _Tp>
	struct add_pointer
		: public detail::_add_pointer_helper<_Tp, detail::_or_<detail::_is_referenceable<_Tp>, is_void<_Tp> >::value>
	{ };


	namespace detail {
		// Decay trait for arrays and functions, used for perfect forwarding
		// in make_pair, make_tuple, etc.
		template<class _Up,
		         bool _IsArray,
		         bool _IsFunction>
		struct _decay_selector;

		template<class _Up>
		struct _decay_selector<_Up, false, false> {
			typedef typename remove_cv<_Up>::type _type;
		};

		template<class _Up>
		struct _decay_selector<_Up, true, false> {
			typedef typename remove_extent<_Up>::type* _type;
		};

		template<class _Up>
		struct _decay_selector<_Up, false, true> {
			typedef typename add_pointer<_Up>::type _type;
		};
	}

	// decay
	template<class _Tp>
	class decay {
			typedef typename remove_reference<_Tp>::type _remove_type;

		public:
			typedef typename
			detail::_decay_selector<_remove_type, is_array<_remove_type>::value, is_function<_remove_type>::value>::_type
			type;
	};
	template< class T >
	using decay_t = typename decay<T>::type;




	namespace detail {
		template<class _Tp, bool _IsFunction>
		struct _add_const_helper {
			typedef _Tp const type;
		};

		template<class _Tp>
		struct _add_const_helper<_Tp, true> {
			typedef _Tp type;
		};

		template<class _Tp, bool _IsFunction>
		struct _add_volatile_helper {
			typedef _Tp volatile type;
		};

		template<class _Tp>
		struct _add_volatile_helper<_Tp, true> {
			typedef _Tp type;
		};

		template<class _Tp, bool _IsFunction>
		struct _add_cv_helper {
			typedef _Tp const volatile type;
		};

		template<class _Tp>
		struct _add_cv_helper<_Tp, true> {
			typedef _Tp type;
		};
	}

	// add_const
	template<class _Tp>
	struct add_const :
		public detail::_add_const_helper<_Tp, is_function<_Tp>::value> {
	};

	template<class _Tp>
	struct add_const<_Tp&> {
		typedef _Tp& type;
	};

	// add_volatile
	template<class _Tp>
	struct add_volatile :
		public detail::_add_volatile_helper<_Tp, is_function<_Tp>::value> {
	};

	template<class _Tp>
	struct add_volatile<_Tp&> {
		typedef _Tp& type;
	};

	// add_cv
	template<class _Tp>
	struct add_cv :
		public detail::_add_cv_helper<_Tp, is_function<_Tp>::value> {
	};

	template<class _Tp>
	struct add_cv<_Tp&> {
		typedef _Tp& type;
	};




	//NON STANDART

	template <typename UnusedType, typename UnusedType2 = UnusedType>
	struct func_parser {
		using ClassType = void;
	};

	template<typename Res, typename... ArgsTypes>
	struct func_parser<Res(*)(ArgsTypes...)> {
		using ResultType = Res;
		using ClassType = void;
	};

	template<typename Res, typename Class_Name, typename... ArgsTypes>
	struct func_parser<Res(Class_Name::*)(ArgsTypes...)> {
		using ResultType = Res;
		using ClassType = Class_Name;
	};


	namespace detail {
		template <class _Tp>
		struct _alignment_of_trick {
			char c;
			_Tp t;
			_alignment_of_trick();
		};

		template <size_t A, size_t S>
		struct _alignment_logic_helper {
			static const size_t value = A < S ? A : S;
		};

		template <size_t A>
		struct _alignment_logic_helper<A, 0> {
			static const size_t value = A;
		};

		template <size_t S>
		struct _alignment_logic_helper<0, S> {
			static const size_t value = S;
		};

		template< class _Tp >
		struct _alignment_of_impl {
				#if _MSC_VER > 1400
				//
				// With MSVC both the build in __alignof operator
				// and following logic gets things wrong from time to time
				// Using a combination of the two seems to make the most of a bad job:
				//
				static const size_t value =
				    (_alignment_logic_helper <
				     sizeof(_alignment_of_trick<_Tp>) - sizeof(_Tp),
				     __alignof(_Tp)
				     >::value);
				#else
				static const size_t value =
				    (_alignment_logic_helper <
				     sizeof(_alignment_of_trick<_Tp>) - sizeof(_Tp),
				     sizeof(_Tp)
				     >::value);
				#endif
				typedef integral_constant<size_t, size_t(_alignment_of_impl::value)> type;

			private:
				typedef intern::type_traits_asserts check;
				typedef typename check::alignment_of_type_can_not_be_zero_assert < _alignment_of_impl::value != 0
				>::
				alignment_of_type_can_not_be_zero_assert_failed
				check1; // if you are there means aligment of type passed can not be calculated or compiler can not handle this situation (sorry, nothing can be done there)
		};

		// borland compilers seem to be unable to handle long double correctly, so this will do the trick:
		struct _long_double_wrapper { long double value; };
	}

	template <class _Tp>
	struct alignment_of:
		public detail::_alignment_of_impl<_Tp>::type
	{};

	template <class _Tp>
	struct alignment_of<_Tp&>:
		public alignment_of<_Tp*>
	{};

	template<>
	struct alignment_of<long double>:
		public alignment_of<detail::_long_double_wrapper>
	{};

	template<typename T>
	constexpr typename vd::remove_reference<T>::type&& move (T&& t) noexcept {
		return static_cast < typename vd::remove_reference<T>::type && > (t);
	}


	template< class T >
	using remove_cv_t = typename remove_cv<T>::type;


	template< class T >
	using remove_reference_t = typename remove_reference<T>::type;

	template< class T >
	struct remove_cvref {
		typedef vd::remove_cv_t<vd::remove_reference_t<T>> type;
	};
	template< class T >
	using remove_cvref_t = typename remove_cvref<T>::type;



	//template <typename T>
	//T&& forward(vd::remove_reference<T>& t)
	//noexcept { //conditional move: lvalue convert to lvalue, rvalue to rvalue
	//	return static_cast < T && > (t);
	//}


	template<class T> struct is_lvalue_reference : vd::false_type {};
	template<class T> struct is_lvalue_reference<T&> : vd::true_type {};
	template< class T >
	constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;

	template <class _Ty>
	constexpr _Ty&& forward(remove_reference_t<_Ty>& _Arg)
	noexcept { // forward an lvalue as either an lvalue or an rvalue
		return static_cast < _Ty && > (_Arg);
	}

	template <class _Ty>
	constexpr _Ty&& forward(remove_reference_t<_Ty>&& _Arg) noexcept { // forward an rvalue as an rvalue
		static_assert(!is_lvalue_reference_v<_Ty>, "bad forward call");
		return static_cast < _Ty && > (_Arg);
	}

	//common type
	template <typename...>
	using void_t = void;

	// primary template (used for zero types)
	template <class...>
	struct common_type {};

	//////// one type
	template <class T>
	struct common_type<T> : common_type<T, T> {};

	//////// two types
	template <class T1, class T2>
	using cond_t = decltype(false ? vd::declval<T1>() : vd::declval<T2>());

	template <class T1, class T2, class = void>
	struct common_type_2_impl {};

	template <class T1, class T2>
	struct common_type_2_impl<T1, T2, void_t<cond_t<T1, T2>>> {
		using type = typename vd::decay<cond_t<T1, T2>>::type;
	};

	template <class T1, class T2>
	struct common_type<T1, T2>
		: common_type_2_impl<typename vd::decay<T1>::type,
		  typename vd::decay<T2>::type>
	{};

	//////// 3+ types
	template <class AlwaysVoid, class T1, class T2, class...R>
	struct common_type_multi_impl {};

	template <class T1, class T2, class...R>
	struct common_type_multi_impl <
		void_t<typename common_type<T1, T2>::type>, T1, T2, R... >
		: common_type<typename common_type<T1, T2>::type, R...> {};


	template <class T1, class T2, class... R>
	struct common_type<T1, T2, R...>
		: common_type_multi_impl<void, T1, T2, R...> {};

	template< class... T >
	using common_type_t = typename common_type<T...>::type;

	//#else
	//	template< bool B, class T = void >
	//	using enable_if = std::enable_if<B,T>;
	//#endif
	template< bool B, class T, class F >
	using conditional_t = typename conditional<B, T, F>::type;

	template<class...> struct conjunction : vd::true_type {};
	template<class B1> struct conjunction<B1> : B1 {};
	template<class B1, class... Bn>
	struct conjunction<B1, Bn...>
	: conditional_t<bool(B1::value), conjunction<Bn...>, vd::false_type> {
	  };

	template<class... B>
	inline constexpr bool conjunction_v = conjunction<B...>::value;


	//template<class B,class...B1>
	//constexpr bool conjunction_v = conjunction<B,B1...>::value;
	//
	//
	//template<typename... Conds>
	//struct and_ : vd::true_type {};
	//
	//template<typename Cond, typename... Conds>
	//struct and_<Cond, Conds...>
	//	: conditional<Cond::value, and_<Conds...>,vd::false_type>::type {
	//};



	template< class... >
	using void_t = void;


	namespace details {
		template <typename Base> vd::true_type is_base_of_test_func(const volatile Base*);
		template <typename Base> vd::false_type is_base_of_test_func(const volatile void*);
		template <typename Base, typename Derived>
		using pre_is_base_of = decltype(is_base_of_test_func<Base>(vd::declval<Derived*>()));

		// with <experimental/type_traits>:
		// template <typename Base, typename Derived>
		// using pre_is_base_of2 = std::experimental::detected_or_t<std::true_type, pre_is_base_of, Base, Derived>;
		template <typename Base, typename Derived, typename = void>
		struct pre_is_base_of2 : public vd::true_type {};
		// note std::void_t is a C++17 feature
		template <typename Base, typename Derived>
		struct pre_is_base_of2<Base, Derived, vd::void_t<pre_is_base_of<Base, Derived>>> :
			public pre_is_base_of<Base, Derived> {
		};
	}

	template <typename Base, typename Derived>
	struct is_base_of :
		public vd::conditional_t <
		vd::is_class<Base>::value&& vd::is_class<Derived>::value,
		details::pre_is_base_of2<Base, Derived>,
		vd::false_type
		> {
	};

	template< class T >
	T* addressof(T& arg) {
		return reinterpret_cast<T*>(
		           &const_cast<char&>(
		               reinterpret_cast<const volatile char&>(arg)));
	}








	//invoke_result
	template <class T>
	class reference_wrapper;
	namespace detail {
		template <class T>
		struct is_reference_wrapper : vd::false_type {};
		template <class U>
		struct is_reference_wrapper<vd::reference_wrapper<U>> : vd::true_type {};

		template<class T>
		struct invoke_impl {
			template<class F, class... Args>
			constexpr static auto call(F&& f, Args&& ... args)
			-> decltype(vd::forward<F>(f)(vd::forward<Args>(args)...));
		};

		template<class B, class MT>
		struct invoke_impl<MT B::*> {
			template<class T, class Td = typename vd::decay<T>::type,
			         class = typename vd::enable_if<vd::is_base_of<B, Td>::value, void>::type
			         >
			constexpr static auto get(T && t)->T &&;

			template<class T, class Td = typename vd::decay<T>::type,
			         class = typename vd::enable_if<is_reference_wrapper<Td>::value, void>::type
			         >
			constexpr static auto get(T && t) -> decltype(t.get());

			template < class T, class Td = typename vd::decay<T>::type,
			           class = typename vd::enable_if < !vd::is_base_of<B, Td>::value, void >::type,
			           class = typename vd::enable_if < !is_reference_wrapper<Td>::value, void >::type
			           >
			constexpr static auto get(T && t) -> decltype(*vd::forward<T>(t));

			template<class T, class... Args, class MT1,
			         class = typename vd::enable_if<vd::is_function<MT1>::value, void>::type
			         >
			constexpr static auto call(MT1 B::* pmf, T && t, Args && ... args)
			-> decltype((invoke_impl::get(vd::forward<T>(t)).*pmf)(vd::forward<Args>(args)...));

			template<class T>
			constexpr static auto call(MT B::* pmd, T&& t)
			-> decltype(invoke_impl::get(vd::forward<T>(t)).*pmd);
		};

		template<class F, class... Args, class Fd = typename vd::decay<F>::type>
		constexpr auto INVOKE(F && f, Args && ... args)
		-> decltype(invoke_impl<Fd>::call(vd::forward<F>(f), vd::forward<Args>(args)...));

	} // namespace detail





	// Conforming C++14 implementation (is also a valid C++11 implementation):
	namespace detail {
		template <typename AlwaysVoid, typename, typename...>
		struct invoke_result {};
		template <typename F, typename...Args>
		struct invoke_result<decltype(void(detail::INVOKE(vd::declval<F>(), vd::declval<Args>()...))),
		       F, Args...> {
		           using type = decltype(detail::INVOKE(vd::declval<F>(), vd::declval<Args>()...));
		       };
	} // namespace detail

	template <class> struct result_of;
	template <class F, class... ArgTypes>
struct result_of<F(ArgTypes...)> : detail::invoke_result<void, F, ArgTypes...> {};




	template <class F, class... ArgTypes>
	struct invoke_result : detail::invoke_result<void, F, ArgTypes...> {};





	template <typename... Xs>
	using invoke_result_t = typename vd::invoke_result<Xs...>::type;





	template< class F, class... Args>
	constexpr vd::invoke_result_t<F, Args...> invoke(F&& f, Args&& ... args)
	//noexcept(vd::is_nothrow_invocable_v<F, Args...>)
	{
		return detail::INVOKE(vd::forward<F>(f), vd::forward<Args>(args)...);
	}




	//reference wrapper

	namespace detail {
		template <class T> T& FUN(T& t) noexcept { return t; }
		template <class T> void FUN(T&&) = delete;
	}

	template <class T>
	class reference_wrapper {
		public:
			// types
			typedef T type;
			// construct/copy/destroy
			template < class U, class = decltype(
			               detail::FUN<T>(vd::declval<U>()),
			               vd::enable_if_t < !vd::is_same_v<reference_wrapper, remove_cvref_t<U> >> ()
			                                                                                 ) >
			constexpr reference_wrapper(U && u) noexcept(noexcept(detail::FUN<T>(vd::forward<U>(u))))
				: _ptr(vd::addressof(detail::FUN<T>(vd::forward<U>(u)))) {
			}
			constexpr reference_wrapper(const reference_wrapper&) noexcept = default;
			// assignment
			reference_wrapper& operator=(const reference_wrapper& x) noexcept = default;
			// access
			constexpr operator T& () const noexcept { return *_ptr; }
			constexpr T& get() const noexcept { return *_ptr; }
			template< class... ArgTypes >
			typename vd::invoke_result<T&, ArgTypes...>::type
			constexpr operator() (ArgTypes&& ... args) const {
				return vd::invoke(get(), vd::forward<ArgTypes>(args)...);
			}
		private:
			T* _ptr;
	};
	// deduction guides
	template<class T>
	reference_wrapper(T&)->reference_wrapper<T>;

	//is constructible

	template <class, class T, class... Args>
	struct is_constructible_ : vd::false_type {};

	template <class T, class... Args>
	struct is_constructible_ <
	void_t<decltype(T(vd::declval<Args>()...))>,
T, Args... > : vd::true_type {
	};

	template <class T, class... Args>
	using is_constructible = is_constructible_<void_t<>, T, Args...>;


	//is trivially constructible



	//is copy constructible



	template<class T>
	struct is_copy_constructible :
		vd::is_constructible<T, typename vd::add_lvalue_reference<
		typename vd::add_const<T>::type>::type> {
	};

	//template<class T>
	//struct is_trivially_copy_constructible :
	//	vd::is_trivially_constructible<T, typename vd::add_lvalue_reference<
	//	typename vd::add_const<T>::type>::type> {
	//};
	//
	//template<class T>
	//struct is_nothrow_copy_constructible :
	//	vd::is_nothrow_constructible<T, typename vd::add_lvalue_reference<
	//	typename vd::add_const<T>::type>::type> {
	//};
	//
	template< class T >
	inline constexpr bool is_copy_constructible_v = is_copy_constructible<T>::value;
	//template< class T >
	//inline constexpr bool is_trivially_copy_constructible_v = is_trivially_copy_constructible<T>::value;
	//template< class T >
	//inline constexpr bool is_nothrow_copy_constructible_v = is_nothrow_copy_constructible<T>::value;



	//is member pointer

	template< class T >
	struct is_member_pointer_helper : vd::false_type {};

	template< class T, class U >
	struct is_member_pointer_helper<T U::*> : vd::true_type {};

	template< class T >
	struct is_member_pointer :
		is_member_pointer_helper<typename vd::remove_cv<T>::type> {
	};
	template< class T >
	constexpr bool is_member_pointer_v = is_member_pointer<T>::value;



	template< class T >
	struct is_member_function_pointer_helper : vd::false_type {};

	template< class T, class U>
	struct is_member_function_pointer_helper<T U::*> : vd::is_function<T> {};

	template< class T >
	struct is_member_function_pointer : is_member_function_pointer_helper< vd::remove_cv_t<T> > {};
	template< class T >
	constexpr bool is_member_function_pointer_v = is_member_function_pointer<T>::value;

	template<class T>
	struct is_member_object_pointer : vd::integral_constant <
		bool,
		vd::is_member_pointer<T>::value&&
		!vd::is_member_function_pointer<T>::value
		> {
	};
	template< class T >
	constexpr bool is_member_object_pointer_v = is_member_object_pointer<T>::value;
}
