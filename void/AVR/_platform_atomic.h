#pragma once

#define DECLARE_OP(OPERATION, OP_NAME) \
	template<class T, class T2>\
	static inline T FetchAnd ## OP_NAME (T * ptr, T2 value)\
	{\
		T tmp = *ptr;\
		*ptr = tmp OPERATION value;\
		return tmp;\
	}\
	template<class T, class T2>\
	static inline T OP_NAME ## AndFetch(T * ptr, T2 value)\
	{\
		*ptr = *ptr OPERATION value;\
		return *ptr;\
	}
namespace vd {
	namespace Private {
		class VoidAtomicPolicy {
				VoidAtomicPolicy();
			public:
				DECLARE_OP(+, Add)
				DECLARE_OP(-, Sub)
				DECLARE_OP( |, Or)
				DECLARE_OP(&, And)
				DECLARE_OP(^, Xor)

				template<class T>
				static inline T Fetch(const T* const ptr) {
					return *ptr;
				}

				template<class T, class T2>
				static inline bool CompareExchange(T* ptr, T2 oldValue, T2 newValue) {
					if (*ptr != oldValue) {
						return false;
					}

					*ptr = newValue;
					return true;
				}
				template <class T, class T2>
				static void Set(T* ptr, T2 newValue) {
					*ptr = newValue;
				}
		};
#undef DECLARE_OP

#define ATOMIC_BLOCK(...) if(vd::Private::atomic_guard_t<__VA_ARGS__> _atomic = vd::Private::atomic_guard_t<__VA_ARGS__>()){}else

#define DECLARE_OP(OPERATION, OP_NAME) \
	template<class T, class T2>\
	static T FetchAnd ## OP_NAME (volatile T * ptr, T2 value)\
	{\
		ATOMIC_BLOCK(vd::Private::RESTORE_STATE) \
		{\
			T tmp = *ptr;\
			*ptr = tmp OPERATION value;\
			return tmp;\
		}\
		return T(0); \
	}\
	template<class T, class T2>\
	static T OP_NAME ## AndFetch(volatile T * ptr, T2 value)\
	{\
		ATOMIC_BLOCK(vd::Private::RESTORE_STATE) \
		{\
			*ptr = *ptr OPERATION value;\
			return *ptr;\
		}\
		return T(0); \
	}


		class AtomicPolicy {
				AtomicPolicy();
			public:
				DECLARE_OP(+, Add)
				DECLARE_OP(-, Sub)
				DECLARE_OP( |, Or)
				DECLARE_OP(&, And)
				DECLARE_OP(^, Xor)

				template<class T>
				static T Fetch(volatile T* ptr) {
					ATOMIC_BLOCK(vd::Private::RESTORE_STATE) {
						return *ptr;
					}
					return T(0); // shutup compiler
				}

				template<class T, class T2>
				static bool CompareExchange(T* ptr, T2 oldValue, T2 newValue) {
					ATOMIC_BLOCK(vd::Private::RESTORE_STATE) {
						if (*ptr != oldValue) { return false; }

						*ptr = newValue;
					}
					return true;
				}
				template <class T, class T2>
				static void Set(T* ptr, T2 newValue) {
					ATOMIC_BLOCK(vd:: Private::RESTORE_STATE) {
						*ptr = newValue;
					}
				}
		};
	}
#undef DECLARE_OP
#undef ATOMIC_BLOCK
}