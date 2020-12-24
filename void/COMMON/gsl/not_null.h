#pragma once
#include <void/assert.h>
//
// not_null<> - Wrap any indirection and enforce non-null.
//
namespace vd {
	namespace gsl {

		template< class T >
		class not_null {
				typedef T get_result_t;
			public:
				template< class U >
				not_null(const U& u) : ptr_(u) {
					assert( ptr_ != nullptr );
				}
				template< class U >
				not_null(U& u) : ptr_(u) {
					assert(ptr_ != nullptr);
				}
				~not_null() {};
				not_null(const not_null& other) : ptr_(other.ptr_) {
				}
				not_null& operator=(not_null const& other) {
					ptr_ = other.ptr_; return *this;
				}

				template< class U >
				not_null(const not_null<U>& other) : ptr_(other.get()) {
				}

				get_result_t get() const {
					// Without cheating and changing ptr_ from the outside, this check is superfluous:
					assert( ptr_ != nullptr );
					return ptr_;
				}

				operator get_result_t  () const {
					return get();
				}
				get_result_t operator->() const {
					return get();
				}

			private:
				// prevent compilation when initialized with a nullptr or literal 0:
				//#if gsl_HAVE( NULLPTR )
				//not_null(             std::nullptr_t ) ;
				//not_null& operator=( std::nullptr_t ) ;
				//else
				not_null(int);
				not_null& operator=(int);
				//endif
				// unwanted operators...pointers only point to single objects!
				not_null& operator++();
				not_null& operator--();
				not_null   operator++(int);
				not_null   operator--(int);
				not_null& operator+ (size_t);
				not_null& operator+=(size_t);
				not_null& operator- (size_t);
				not_null& operator-=(size_t);
				not_null& operator+=(ptrdiff_t);
				not_null& operator-=(ptrdiff_t);
				void       operator[](ptrdiff_t) const;
			private:
				T ptr_;
		};
	}
}