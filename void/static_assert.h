#pragma once
#include "platform_specific.h"
#ifdef __cplusplus

#define __hereCONCAT2(First, Second) (First ## Second)
#define __hereCONCAT(First, Second) __hereCONCAT2(First, Second)

//copied from Boost library
namespace vd {
	template <bool x> struct STATIC_ASSERTION_FAILURE;
	template <> struct STATIC_ASSERTION_FAILURE<true> { enum { value = 1 }; };
	template <> struct STATIC_ASSERTION_FAILURE<false> { enum { value = -1 }; };
//template<int x> struct static_assert_test {};

	/*
	#define VOID_STATIC_ASSERT( B ) \
		typedef ::vd::static_assert_test\
		<sizeof(::vd::STATIC_ASSERTION_FAILURE< bool( B ) >)>\
		(__hereCONCAT(vd_static_assert_typedef_, __LINE__))

	*/


}



#endif

#ifdef _VOID_NATIVE_CPP17_SUPPORT //c++17
	#define VOID_STATIC_ASSERT(...) static_assert(__VA_ARGS__)
	//#define VOID_STATIC_ASSERT(...) typedef char __hereCONCAT(static_assert_failed_at_line_, __LINE__) [(__VA_ARGS__) ? 1 : -1]
#else //before c++17
	#ifdef _VOID_NATIVE_CPP11_SUPPORT //variadic macros (comma in expression support->like template arguments)
		#define VOID_STATIC_ASSERT(...) typedef char __hereCONCAT(static_assert_failed_at_line_, __LINE__) [(__VA_ARGS__) ? 1 : -1]
	#else  //before c++11
		#define VOID_STATIC_ASSERT(expr) typedef char __hereCONCAT(static_assert_failed_at_line_, __LINE__) [(expr) ? 1 : -1]
	#endif

	#ifdef __GNUC__
		#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
	#endif

#endif



#ifdef _VOID_NATIVE_CPP11_SUPPORT //c++11
	//Dont work in struct/unions
	//#define VOID_STATIC_ASSERT_MSG(expression, message) typedef char STATIC_ASSERTION_ ## message[(expression) ? 1 : -1]
	#define VOID_STATIC_ASSERT_MSG(expr,message) static_assert(expr,message)
#else //before c++11
	#define VOID_STATIC_ASSERT_MSG(expression, message) VOID_STATIC_ASSERT(expression)
#endif

#if defined(__GNUC__)
	#define DEPRECATE(foo, msg) foo __attribute__((deprecated(msg)))
#elif defined(_MSC_VER)
	#define DEPRECATE(foo, msg) __declspec(deprecated(msg)) foo
#else
	#error This compiler is not supported
#endif

#define PP_CAT(x,y) PP_CAT1(x,y)
#define PP_CAT1(x,y) x##y
namespace vd {
	namespace detail {
		struct true_type {};
		struct false_type {};
		template <int test> struct converter : public true_type {};
		template <> struct converter<0> : public false_type {};
	}
}
#define VOID_STATIC_WARNING(cond, msg) \
	struct PP_CAT(static_warning,__LINE__) { \
		DEPRECATE(void _(vd::detail::false_type const& ),msg) {}; \
		void _(vd::detail::true_type const& ) {}; \
		PP_CAT(static_warning,__LINE__)() {_(vd::detail::converter<(cond)>());} \
	}

// Note: using STATIC_WARNING_TEMPLATE changes the meaning of a program in a small way.
// It introduces a member/variable declaration.  This means at least one byte of space
// in each structure/class instantiation.  STATIC_WARNING should be preferred in any
// non-template situation.
//  'token' must be a program-wide unique identifier.
#define VOID_STATIC_WARNING_TEMPLATE(token, cond, msg) \
	VOID_STATIC_WARNING(cond, msg) PP_CAT(PP_CAT(_localvar_, token),__LINE__)
