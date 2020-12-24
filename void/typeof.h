#pragma once
//look here http://www.drdobbs.com/a-portable-typeof-operator/184401310?pgno=2
// no definition, only specializations
namespace vd {

	namespace details {
		template<int N> struct select_type;

		template<class T> struct WrapType { typedef T WT; };
	}


#define REGISTER_TYPEOF(N,T)                          \
	template<> struct details::select_type<N> {                \
		typedef details::WrapType<T>::WT Type; };               \
	char (*select_array(const details::WrapType<T>::WT &))[N];

#define typeof(x) details::select_type<sizeof(*select_array(x))>::Type


//====== Registration of types to be used with "typeof" ======

	REGISTER_TYPEOF( 1,  char               )
	REGISTER_TYPEOF( 2,  signed char        )
	REGISTER_TYPEOF( 3,  unsigned char      )
	REGISTER_TYPEOF( 4,  short              )
	REGISTER_TYPEOF( 5,  unsigned short     )
	REGISTER_TYPEOF( 6,  int                )
	REGISTER_TYPEOF( 7,  unsigned int       )
	REGISTER_TYPEOF( 8,  long               )
	REGISTER_TYPEOF( 9,  unsigned long      )
	REGISTER_TYPEOF( 10, long long          )
	REGISTER_TYPEOF( 11, unsigned long long )
	REGISTER_TYPEOF( 12, float              )
	REGISTER_TYPEOF( 13, double             )
	REGISTER_TYPEOF( 14, wchar_t            )
	REGISTER_TYPEOF( 15, int (*)()          )



	/* short a;
	long b;
	typeof(a) c;
	typeof(b) d;
	typeof(1.0) e;
	typeof(main) f;

	  cout << "c is " << typeid(c).name() << '\n';
	cout << "d is " << typeid(d).name() << '\n';
	cout << "e is " << typeid(e).name() << '\n';
	cout << "f is " << typeid(f).name() << '\n';
	*/

}