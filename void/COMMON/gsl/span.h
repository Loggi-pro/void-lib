//
// span for C++98 and later.
// Based on http://wg21.link/p0122r7
// For more information see https://github.com/martinmoene/span-lite
//
// Copyright 2018-2019 Martin Moene
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)




#ifndef NONSTD_SPAN_HPP_INCLUDED
#define NONSTD_SPAN_HPP_INCLUDED

#include <void/type_traits.h>
#define span_lite_MAJOR  0
#define span_lite_MINOR  4
#define span_lite_PATCH  0

#define span_lite_VERSION  span_STRINGIFY(span_lite_MAJOR) "." span_STRINGIFY(span_lite_MINOR) "." span_STRINGIFY(span_lite_PATCH)

#define span_STRINGIFY(  x )  span_STRINGIFY_( x )
#define span_STRINGIFY_( x )  #x

// span configuration:

#define span_SPAN_DEFAULT  0
#define span_SPAN_NONSTD   1
#define span_SPAN_STD      2

#ifndef  span_CONFIG_SELECT_SPAN
	#define span_CONFIG_SELECT_SPAN  ( span_HAVE_STD_SPAN ? span_SPAN_STD : span_SPAN_NONSTD )
#endif

#ifndef  span_CONFIG_INDEX_TYPE
	#define span_CONFIG_INDEX_TYPE  unsigned int
#endif

// span configuration (features):

#ifndef  span_FEATURE_WITH_CONTAINER
	#ifdef   span_FEATURE_WITH_CONTAINER_TO_STD
		#define span_FEATURE_WITH_CONTAINER  span_IN_STD( span_FEATURE_WITH_CONTAINER_TO_STD )
	#else
		#define span_FEATURE_WITH_CONTAINER  0
	#endif
#endif

#ifndef  span_FEATURE_CONSTRUCTION_FROM_STDARRAY_ELEMENT_TYPE
	#define span_FEATURE_CONSTRUCTION_FROM_STDARRAY_ELEMENT_TYPE  0
#endif

#ifndef  span_FEATURE_MEMBER_AT
	#define span_FEATURE_MEMBER_AT  0
#endif

#ifndef  span_FEATURE_MEMBER_BACK_FRONT
	#define span_FEATURE_MEMBER_BACK_FRONT  0
#endif

#ifndef  span_FEATURE_MEMBER_CALL_OPERATOR
	#define span_FEATURE_MEMBER_CALL_OPERATOR  0
#endif

#ifndef  span_FEATURE_MEMBER_SWAP
	#define span_FEATURE_MEMBER_SWAP  0
#endif

#ifndef  span_FEATURE_NON_MEMBER_FIRST_LAST_SUB
	#define span_FEATURE_NON_MEMBER_FIRST_LAST_SUB  0
#endif

#ifndef  span_FEATURE_SAME
	#define span_FEATURE_SAME  0
#endif

#ifndef  span_FEATURE_MAKE_SPAN
	#ifdef   span_FEATURE_MAKE_SPAN_TO_STD
		#define span_FEATURE_MAKE_SPAN  span_IN_STD( span_FEATURE_MAKE_SPAN_TO_STD )
	#else
		#define span_FEATURE_MAKE_SPAN  0
	#endif
#endif

#ifndef  span_FEATURE_BYTE_SPAN
	#define span_FEATURE_BYTE_SPAN  0
#endif

// Control presence of exception handling (try and auto discover):

#ifndef span_CONFIG_NO_EXCEPTIONS
	#define span_CONFIG_NO_EXCEPTIONS  1
	#undef  span_CONFIG_CONTRACT_VIOLATION_THROWS
	#undef  span_CONFIG_CONTRACT_VIOLATION_TERMINATES
	#define span_CONFIG_CONTRACT_VIOLATION_THROWS  0
	#define span_CONFIG_CONTRACT_VIOLATION_TERMINATES  1
#endif

// Control pre- and postcondition violation behaviour:

#if    defined( span_CONFIG_CONTRACT_LEVEL_ON )
	#define        span_CONFIG_CONTRACT_LEVEL_MASK  0x11
#elif  defined( span_CONFIG_CONTRACT_LEVEL_OFF )
	#define        span_CONFIG_CONTRACT_LEVEL_MASK  0x00
#elif  defined( span_CONFIG_CONTRACT_LEVEL_EXPECTS_ONLY )
	#define        span_CONFIG_CONTRACT_LEVEL_MASK  0x01
#elif  defined( span_CONFIG_CONTRACT_LEVEL_ENSURES_ONLY )
	#define        span_CONFIG_CONTRACT_LEVEL_MASK  0x10
#else
	#define        span_CONFIG_CONTRACT_LEVEL_MASK  0x11
#endif

#if    defined( span_CONFIG_CONTRACT_VIOLATION_THROWS )
	#define        span_CONFIG_CONTRACT_VIOLATION_THROWS_V  span_CONFIG_CONTRACT_VIOLATION_THROWS
#else
	#define        span_CONFIG_CONTRACT_VIOLATION_THROWS_V  0
#endif

#if    defined( span_CONFIG_CONTRACT_VIOLATION_THROWS     ) && span_CONFIG_CONTRACT_VIOLATION_THROWS && \
	defined( span_CONFIG_CONTRACT_VIOLATION_TERMINATES ) && span_CONFIG_CONTRACT_VIOLATION_TERMINATES
	# error Please define none or one of span_CONFIG_CONTRACT_VIOLATION_THROWS and span_CONFIG_CONTRACT_VIOLATION_TERMINATES to 1, but not both.
#endif

// C++ language version detection (C++20 is speculative):
// Note: VC14.0/1900 (VS2015) lacks too much from C++14.

#ifndef   span_CPLUSPLUS
	#if defined(_MSVC_LANG ) && !defined(__clang__)
		#define span_CPLUSPLUS  (_MSC_VER == 1900 ? 201103L : _MSVC_LANG )
	#else
		#define span_CPLUSPLUS  __cplusplus
	#endif
#endif

#define span_CPP98_OR_GREATER  ( span_CPLUSPLUS >= 199711L )
#define span_CPP11_OR_GREATER  ( span_CPLUSPLUS >= 201103L )
#define span_CPP14_OR_GREATER  ( span_CPLUSPLUS >= 201402L )
#define span_CPP17_OR_GREATER  ( span_CPLUSPLUS >= 201703L )
#define span_CPP20_OR_GREATER  ( span_CPLUSPLUS >= 202000L )

// C++ language version (represent 98 as 3):

#define span_CPLUSPLUS_V  ( span_CPLUSPLUS / 100 - (span_CPLUSPLUS > 200000 ? 2000 : 1994) )

#define span_IN_STD( v )  ( ((v) == 98 ? 3 : (v)) >= span_CPLUSPLUS_V )

#define span_CONFIG(         feature )  ( span_CONFIG_##feature )
#define span_FEATURE(        feature )  ( span_FEATURE_##feature )
#define span_FEATURE_TO_STD( feature )  ( span_IN_STD( span_FEATURE( feature##_TO_STD ) ) )

// Use C++20 std::span if available and requested:

#define  span_HAVE_STD_SPAN  0

#define  span_USES_STD_SPAN  ( (span_CONFIG_SELECT_SPAN == span_SPAN_STD) || ((span_CONFIG_SELECT_SPAN == span_SPAN_DEFAULT) && span_HAVE_STD_SPAN) )

//
// Use C++20 std::span:
//

#if span_USES_STD_SPAN
#else  // span_USES_STD_SPAN

// Compiler versions:
//
// MSVC++ 6.0  _MSC_VER == 1200 (Visual Studio 6.0)
// MSVC++ 7.0  _MSC_VER == 1300 (Visual Studio .NET 2002)
// MSVC++ 7.1  _MSC_VER == 1310 (Visual Studio .NET 2003)
// MSVC++ 8.0  _MSC_VER == 1400 (Visual Studio 2005)
// MSVC++ 9.0  _MSC_VER == 1500 (Visual Studio 2008)
// MSVC++ 10.0 _MSC_VER == 1600 (Visual Studio 2010)
// MSVC++ 11.0 _MSC_VER == 1700 (Visual Studio 2012)
// MSVC++ 12.0 _MSC_VER == 1800 (Visual Studio 2013)
// MSVC++ 14.0 _MSC_VER == 1900 (Visual Studio 2015)
// MSVC++ 14.1 _MSC_VER >= 1910 (Visual Studio 2017)

#if defined(_MSC_VER ) && !defined(__clang__)
	#define span_COMPILER_MSVC_VER      (_MSC_VER )
	#define span_COMPILER_MSVC_VERSION  (_MSC_VER / 10 - 10 * ( 5 + (_MSC_VER < 1900 ) ) )
#else
	#define span_COMPILER_MSVC_VER      0
	#define span_COMPILER_MSVC_VERSION  0
#endif

#define span_COMPILER_VERSION( major, minor, patch )  ( 10 * ( 10 * (major) + (minor) ) + (patch) )

#if defined(__clang__)
	#define span_COMPILER_CLANG_VERSION  span_COMPILER_VERSION(__clang_major__, __clang_minor__, __clang_patchlevel__)
#else
	#define span_COMPILER_CLANG_VERSION  0
#endif

#if defined(__GNUC__) && !defined(__clang__)
	#define span_COMPILER_GNUC_VERSION  span_COMPILER_VERSION(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#else
	#define span_COMPILER_GNUC_VERSION  0
#endif

// half-open range [lo..hi):
#define span_BETWEEN( v, lo, hi )  ( (lo) <= (v) && (v) < (hi) )

// Compiler warning suppression:

// Presence of language and library features:

#define span_HAVE( feature )  ( span_HAVE_##feature )

#ifdef _HAS_CPP0X
	#define span_HAS_CPP0X  _HAS_CPP0X
#else
	#define span_HAS_CPP0X  0
#endif

#define span_CPP11_80   (span_CPP11_OR_GREATER || span_COMPILER_MSVC_VER >= 1400)
#define span_CPP11_90   (span_CPP11_OR_GREATER || span_COMPILER_MSVC_VER >= 1500)
#define span_CPP11_100  (span_CPP11_OR_GREATER || span_COMPILER_MSVC_VER >= 1600)
#define span_CPP11_110  (span_CPP11_OR_GREATER || span_COMPILER_MSVC_VER >= 1700)
#define span_CPP11_120  (span_CPP11_OR_GREATER || span_COMPILER_MSVC_VER >= 1800)
#define span_CPP11_140  (span_CPP11_OR_GREATER || span_COMPILER_MSVC_VER >= 1900)

#define span_CPP14_000  (span_CPP14_OR_GREATER)
#define span_CPP14_120  (span_CPP14_OR_GREATER || span_COMPILER_MSVC_VER >= 1800)
#define span_CPP14_140  (span_CPP14_OR_GREATER || span_COMPILER_MSVC_VER >= 1900)

#define span_CPP17_000  (span_CPP17_OR_GREATER)

// Presence of C++11 language features:

#define span_HAVE_ALIAS_TEMPLATE             false
#define span_HAVE_AUTO                       false
#define span_HAVE_CONSTEXPR_11               true
#define span_HAVE_DEFAULT_FUNCTION_TEMPLATE_ false
#define span_HAVE_EXPLICIT_CONVERSION        false
#define span_HAVE_INITIALIZER_LIST           true
#define span_HAVE_IS_DEFAULT                 false
#define span_HAVE_IS_DELETE                  false
#define span_HAVE_NOEXCEPT                   false
#define span_HAVE_NULLPTR                    false
#define span_HAVE_STATIC_ASSERT              false

// Presence of C++14 language features:

#define span_HAVE_CONSTEXPR_14              true

// Presence of C++17 language features:

#define span_HAVE_DEPRECATED                false
#define span_HAVE_NODISCARD                 false
#define span_HAVE_NORETURN                  false

// MSVC: template parameter deduction guides since Visual Studio 2017 v15.7

#define span_HAVE_DEDUCTION_GUIDES         false

// Presence of C++ library features:

#define span_HAVE_ADDRESSOF                false
#define span_HAVE_ARRAY                    false
#define span_HAVE_BYTE                     false
#define span_HAVE_CONDITIONAL              false
#define span_HAVE_CONTAINER_DATA_METHOD    false
#define span_HAVE_DATA                     false
#define span_HAVE_LONGLONG                 false
#define span_HAVE_REMOVE_CONST             false
#define span_HAVE_SNPRINTF                 false
#define span_HAVE_TYPE_TRAITS              false

// Presence of byte-lite:

#ifdef NONSTD_BYTE_LITE_HPP
	#define span_HAVE_NONSTD_BYTE  1
#else
	#define span_HAVE_NONSTD_BYTE  0
#endif

// C++ feature usage:

#if span_HAVE_ADDRESSOF
	#define span_ADDRESSOF(x)  std::addressof(x)
#else
	#define span_ADDRESSOF(x)  (&x)
#endif

#if span_HAVE_CONSTEXPR_11
	#define span_constexpr constexpr
#else
	#define span_constexpr /*span_constexpr*/
#endif

#if span_HAVE_CONSTEXPR_14
	#define span_constexpr14 constexpr
#else
	#define span_constexpr14 /*span_constexpr*/
#endif

#if span_HAVE_EXPLICIT_CONVERSION
	#define span_explicit explicit
#else
	#define span_explicit /*explicit*/
#endif

#if span_HAVE_IS_DELETE
	#define span_is_delete = delete
#else
	#define span_is_delete
#endif

#if span_HAVE_IS_DELETE
	#define span_is_delete_access public
#else
	#define span_is_delete_access private
#endif

#if span_HAVE_NOEXCEPT && ! span_CONFIG_CONTRACT_VIOLATION_THROWS_V
	#define span_noexcept noexcept
#else
	#define span_noexcept /*noexcept*/
#endif

#if span_HAVE_NULLPTR
	#define span_nullptr nullptr
#else
	#define span_nullptr NULL
#endif

#if span_HAVE_DEPRECATED
	#define span_deprecated(msg) [[deprecated(msg)]]
#else
	#define span_deprecated(msg) /*[[deprecated]]*/
#endif

#if span_HAVE_NODISCARD
	#define span_nodiscard [[nodiscard]]
#else
	#define span_nodiscard /*[[nodiscard]]*/
#endif

#if span_HAVE_NORETURN
	#define span_noreturn [[noreturn]]
#else
	#define span_noreturn /*[[noreturn]]*/
#endif

// Other features:

#define span_HAVE_CONSTRAINED_SPAN_CONTAINER_CTOR  false


// Contract violation

#define span_ELIDE_CONTRACT_EXPECTS  ( 0 == ( span_CONFIG_CONTRACT_LEVEL_MASK & 0x01 ) )
#define span_ELIDE_CONTRACT_ENSURES  ( 0 == ( span_CONFIG_CONTRACT_LEVEL_MASK & 0x10 ) )

#if span_ELIDE_CONTRACT_EXPECTS
	#define span_constexpr_exp    span_constexpr
	#define span_EXPECTS( cond )  /* Expect elided */
#else
	#define span_constexpr_exp    span_constexpr14
	#define span_EXPECTS( cond )  span_CONTRACT_CHECK( "Precondition", cond )
#endif

#if span_ELIDE_CONTRACT_ENSURES
	#define span_constexpr_ens    span_constexpr
	#define span_ENSURES( cond )  /* Ensures elided */
#else
	#define span_constexpr_ens    span_constexpr14
	#define span_ENSURES( cond )  span_CONTRACT_CHECK( "Postcondition", cond )
#endif

#define span_CONTRACT_CHECK( type, cond ) \
	cond ? static_cast< void >( 0 ) \
	: vd::gsl::detail::report_contract_violation( span_LOCATION( __FILE__, __LINE__ ) ": " type " violation." )

#ifdef __GNUG__
	#define span_LOCATION( file, line )  file ":" span_STRINGIFY( line )
#else
	#define span_LOCATION( file, line )  file "(" span_STRINGIFY( line ) ")"
#endif

namespace vd {
	namespace gsl {

// [views.constants], constants

		typedef span_CONFIG_INDEX_TYPE index_t;

		typedef ptrdiff_t extent_t;

		span_constexpr const extent_t dynamic_extent = -1;

		template< class T, extent_t Extent = dynamic_extent >
		class span;

// Tag to select span constructor taking a container (prevent ms-gsl warning C26426):

		struct with_container_t { span_constexpr with_container_t() span_noexcept {} };
		const  span_constexpr   with_container_t with_container;

// Implementation details:

		namespace detail {


			template< class T > struct remove_const { typedef T type; };
			template< class T > struct remove_const< T const > { typedef T type; };

			template< class T > struct remove_volatile { typedef T type; };
			template< class T > struct remove_volatile< T volatile > { typedef T type; };

			template< class T >
			struct remove_cv {
				typedef typename detail::remove_volatile< typename detail::remove_const< T >::type >::type type;
			};



			#if ! span_HAVE( TYPE_TRAITS )

			struct true_type { enum { value = true }; };
			struct false_type { enum { value = false }; };

			template< class T, class U > struct is_same : false_type {};
			template< class T          > struct is_same<T, T> : true_type {};

			#endif



			span_noreturn inline void report_contract_violation(char const* /*msg*/) span_noexcept {
				//std::terminate();
			}



		}  // namespace detail

// Prevent signed-unsigned mismatch:

#define span_sizeof(T)  static_cast<extent_t>( sizeof(T) )

		template< class T >
		inline span_constexpr index_t to_size(T size) {
			return static_cast<index_t>(size);
		}







//
// [views.span] - A view over a contiguous, single-dimension sequence of objects
//
		template< class T = uint8_t, extent_t Extent /*= dynamic_extent*/ >
		class span {
			public:
				// constants and types

				typedef T element_type;
				typedef typename detail::remove_cv< T >::type value_type;

				typedef T&        reference;
				typedef T*        pointer;
				typedef T const* const_pointer;
				typedef T const& const_reference;

				typedef index_t   index_type;
				typedef extent_t  extent_type;

				//typedef pointer        iterator;
				//typedef const_pointer  const_iterator;

				typedef ptrdiff_t difference_type;

				//typedef std::reverse_iterator< iterator >       reverse_iterator;
				//typedef std::reverse_iterator< const_iterator > const_reverse_iterator;

				//    static constexpr extent_type extent = Extent;
				enum { extent = Extent };

				// 26.7.3.2 Constructors, copy, and assignment [span.cons]

			span_constexpr span() span_noexcept: data_(span_nullptr), size_(0) {
					// span_EXPECTS( data() == span_nullptr );
					// span_EXPECTS( size() == 0 );
				}

				span_constexpr_exp span(pointer ptr, index_type count): data_(ptr), size_(count) {
					span_EXPECTS(
					    (ptr == span_nullptr && count == 0) ||
					    (ptr != span_nullptr && count >= 0)
					);
				}
				template <typename T2>
				span_constexpr_exp span(const T2& ptr) : data_((pointer) & ptr), size_(sizeof(T2)) {
					VOID_STATIC_ASSERT(sizeof(T) == 1);
				}
				/*
								template <typename T2>
								span_constexpr_exp span(const T2* ptr) : data_((const_pointer)ptr), size_(sizeof(T2)) {
									VOID_STATIC_ASSERT(sizeof(T) == 1);
								}

									template <typename T2>
								span_constexpr_exp span(T2& ptr) : data_((pointer) & ptr), size_(sizeof(T2)) {
									VOID_STATIC_ASSERT(sizeof(T) == 1);
								}

								template <typename T2>
								span_constexpr_exp span(T2* ptr) : data_((pointer)ptr), size_(sizeof(T2)) {
									VOID_STATIC_ASSERT(sizeof(T) == 1);
								}
				*/

				span_constexpr_exp span(pointer firstElem, pointer lastElem)
					: data_(firstElem), size_(lastElem - firstElem) {
					// size_(to_size(std::distance(firstElem, lastElem))) {
					span_EXPECTS(lastElem > firstElem);
					//std::distance(firstElem, lastElem) >= 0
					//);
				}
				template < size_t N>
			span_constexpr span(element_type(&arr)[N]) span_noexcept : data_(span_ADDRESSOF(arr[0])), size_(N)
				{}

				/*
				span(initializer_list<element_type> list) span_noexcept : data_(list.begin()), size_(list.size())
				{}
				*/



				span_constexpr span(span const& other) span_noexcept
			: data_(other.data_)
				, size_(other.size_)
				{}

				~span() span_noexcept
				{}

				span_constexpr14 span& operator=(span const& other) span_noexcept {
					data_ = other.data_;
					size_ = other.size_;

					return *this;
				}

				template < class OtherElementType, extent_type OtherExtent
				           #if span_HAVE( DEFAULT_FUNCTION_TEMPLATE_ARG )
				           , class = typename std::enable_if <
				               (Extent == dynamic_extent || Extent == OtherExtent) &&
				               std::is_convertible<OtherElementType(*)[], element_type(*)[]>::value
				               >::type
				           #endif
				           >
				span_constexpr_exp span(span<OtherElementType, OtherExtent> const& other) span_noexcept
			: data_(reinterpret_cast<pointer>(other.data()))
				, size_(other.size()) {
					span_EXPECTS(OtherExtent == dynamic_extent || other.size() == to_size(OtherExtent));
				}

				// 26.7.3.3 Subviews [span.sub]

				template< extent_type Count >
				span_constexpr_exp span< element_type, Count >
				first() const {
					span_EXPECTS(0 <= Count && Count <= size());
					return span< element_type, Count >(data(), Count);
				}

				template< extent_type Count >
				span_constexpr_exp span< element_type, Count >
				last() const {
					span_EXPECTS(0 <= Count && Count <= size());
					return span< element_type, Count >(data() + (size() - Count), Count);
				}


				template< index_type Offset, extent_type Count /*= dynamic_extent*/ >

				span_constexpr_exp span< element_type, Count >
				subspan() const {
					span_EXPECTS(
					    (0 <= Offset && Offset <= size()) &&
					    (Count == dynamic_extent || (0 <= Count && Count + Offset <= size()))
					);
					return span< element_type, Count >(
					           data() + Offset, Count != dynamic_extent ? Count : (Extent != dynamic_extent ? Extent - Offset :
					                   size() - Offset));
				}

				span_constexpr_exp span< element_type, dynamic_extent >
				first(index_type count) const {
					span_EXPECTS(0 <= count && count <= size());
					return span< element_type, dynamic_extent >(data(), count);
				}

				span_constexpr_exp span< element_type, dynamic_extent >
				last(index_type count) const {
					span_EXPECTS(0 <= count && count <= size());
					return span< element_type, dynamic_extent >(data() + (size() - count), count);
				}

				span_constexpr_exp span< element_type, dynamic_extent >
				subspan(index_type offset, index_type count = static_cast<index_type>(dynamic_extent)) const {
					span_EXPECTS(
					    ((0 <= offset && offset <= size())) &&
					    (count == static_cast<index_type>(dynamic_extent) || (0 <= count && offset + count <= size()))
					);
					return span< element_type, dynamic_extent >(
					           data() + offset, count == static_cast<index_type>(dynamic_extent) ? size() - offset : count);
				}

				// 26.7.3.4 Observers [span.obs]

				span_constexpr index_type size() const span_noexcept {
					return size_;
				}

				span_constexpr index_type size_bytes() const span_noexcept {
					return size() * to_size(sizeof(element_type));
				}

				span_nodiscard span_constexpr bool empty() const span_noexcept {
					return size() == 0;
				}

				// 26.7.3.5 Element access [span.elem]

				span_constexpr_exp reference operator[](index_type idx) const {
					span_EXPECTS(0 <= idx && idx < size());
					return *(data() + idx);
				}



				span_constexpr pointer data() const span_noexcept {
					return data_;
				}



				// 26.7.3.6 Iterator support [span.iterators]
				/*
						span_constexpr iterator begin() const span_noexcept {
				#if span_CPP11_OR_GREATER
							return { data() };
				#else
							return iterator(data());
				#endif
						}

						span_constexpr iterator end() const span_noexcept {
				#if span_CPP11_OR_GREATER
							return { data() + size() };
				#else
							return iterator(data() + size());
				#endif
						}

						span_constexpr const_iterator cbegin() const span_noexcept {
				#if span_CPP11_OR_GREATER
							return { data() };
				#else
							return const_iterator(data());
				#endif
						}

						span_constexpr const_iterator cend() const span_noexcept {
				#if span_CPP11_OR_GREATER
							return { data() + size() };
				#else
							return const_iterator(data() + size());
				#endif
						}

						span_constexpr reverse_iterator rbegin() const span_noexcept {
							return reverse_iterator(end());
						}

						span_constexpr reverse_iterator rend() const span_noexcept {
							return reverse_iterator(begin());
						}

						span_constexpr const_reverse_iterator crbegin() const span_noexcept {
							return const_reverse_iterator(cend());
						}

						span_constexpr const_reverse_iterator crend() const span_noexcept {
							return const_reverse_iterator(cbegin());
						}
				*/
			private:
				pointer    data_;
				index_type size_;
		};


		template<typename U>
		vd::gsl::span<uint8_t>
		make_span(const U& type) {
			return span<uint8_t>((uint8_t*)&type, sizeof(U));
		}

		template<typename U>
		void  make_span(U* type) {//cant make span from pointer
		}



// class template argument deduction guides:



// 26.7.3.7 Comparison operators [span.comparison]



		template< class T1, extent_t E1, class T2, extent_t E2  >
		inline span_constexpr bool operator==(span<T1, E1> const& l, span<T2, E2> const& r) {
			// (l.size() == r.size() && std::equal(l.begin(), l.end(), r.begin()));
			if (l.size() != r.size()) {
				return false;
			}

			for (size_t i = 0; i < l.size(); i++) {
				if (l.data()[i] != r.data()[i]) { return false; }
			}

			return true;
		}
		/*
		template< class T1, extent_t E1, class T2, extent_t E2  >
		inline span_constexpr bool operator<(span<T1, E1> const& l, span<T2, E2> const& r) {
			return std::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end());
		}
		*/
		template< class T1, extent_t E1, class T2, extent_t E2  >
		inline span_constexpr bool operator!=(span<T1, E1> const& l, span<T2, E2> const& r) {
			return !(l == r);
		}
		/*
		template< class T1, extent_t E1, class T2, extent_t E2  >
		inline span_constexpr bool operator<=(span<T1, E1> const& l, span<T2, E2> const& r) {
			return !(r < l);
		}

		template< class T1, extent_t E1, class T2, extent_t E2  >
		inline span_constexpr bool operator>(span<T1, E1> const& l, span<T2, E2> const& r) {
			return (r < l);
		}

		template< class T1, extent_t E1, class T2, extent_t E2  >
		inline span_constexpr bool operator>=(span<T1, E1> const& l, span<T2, E2> const& r) {
			return !(l < r);
		}
		*/
// 26.7.2.6 views of object representation [span.objectrep]




	}  // namespace span_lite
}  // namespace vd

// make available in nonstd:

namespace vd {

//using span_lite::operator<;
//using span_lite::operator<=;
//using span_lite::operator>;
//using span_lite::operator>=;



}  // namespace nonstd

#endif  // span_USES_STD_SPAN



#endif  // NONSTD_SPAN_HPP_INCLUDED