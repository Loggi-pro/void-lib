
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
namespace vd::Private {
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
				if (*ptr != oldValue)
				{ return false; }

				*ptr = newValue;
				return true;
			}
			template <class T, class T2>
			static void Set(T* ptr, T2 newValue) {
				*ptr = newValue;
			}
	};
#undef DECLARE_OP

#define DECLARE_OP(OPERATION, OP_NAME) \
	template<class T2>\
	static uint32_t FetchAnd ## OP_NAME (volatile uint32_t * ptr, T2 value)\
	{\
		uint32_t oldValue, newValue;\
		do\
		{\
			oldValue = __LDREXW(ptr);\
			newValue = oldValue OPERATION value;\
		}while(__STREXW(newValue, ptr));\
		return oldValue;\
	}\
	template<class T2>\
	static uint16_t FetchAnd ## OP_NAME (volatile uint16_t * ptr, T2 value)\
	{\
		uint16_t oldValue, newValue;\
		do\
		{\
			oldValue = __LDREXH(ptr);\
			newValue = oldValue OPERATION value;\
		}while(__STREXH(newValue, ptr));\
		return oldValue;\
	}\
	template<class T2>\
	static uint8_t FetchAnd ## OP_NAME (volatile uint8_t * ptr, T2 value)\
	{\
		uint8_t oldValue, newValue;\
		do\
		{\
			oldValue = __LDREXB(ptr);\
			newValue = oldValue OPERATION value;\
		}while(__STREXB(newValue, ptr));\
		return oldValue;\
	}\
	template<class T2>\
	static uint32_t OP_NAME ## AndFetch(volatile uint32_t * ptr, T2 value)\
	{\
		uint32_t oldValue, newValue;\
		do\
		{\
			oldValue = __LDREXW(ptr);\
			newValue = oldValue OPERATION value;\
		}while(__STREXW(newValue, ptr));\
		return newValue;\
	}\
	template<class T2>\
	static uint16_t OP_NAME ## AndFetch(volatile uint16_t * ptr, T2 value)\
	{\
		uint16_t oldValue, newValue;\
		do\
		{\
			oldValue = __LDREXH(ptr);\
			newValue = oldValue OPERATION value;\
		}while(__STREXH(newValue, ptr));\
		return newValue;\
	}\
	template<class T2>\
	static uint8_t OP_NAME ## AndFetch(volatile uint8_t * ptr, T2 value)\
	{\
		uint8_t oldValue, newValue;\
		do\
		{\
			oldValue = __LDREXB(ptr);\
			newValue = oldValue OPERATION value;\
		}while(__STREXB(newValue, ptr));\
		return newValue;\
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
				__DSB();
				T value = *ptr;
				return value;
			}




			template<class T2>
			static bool CompareExchange(uint32_t* ptr, T2 oldValue, T2 newValue) {
				// эксклюзивно читаем значение переменной и сравниваем со старым значением
				if (__LDREXW(ptr) == oldValue)
// пытаемс¤ эксклюзивно записать в переменную новое значение
				{ return __STREXW(newValue, ptr) == 0; }

// кто-то изменил ¤чейку до нас
				__CLREX();
				return false;
			}
			template<class T2>
			static bool CompareExchange(uint16_t* ptr, T2 oldValue, T2 newValue) {
				// эксклюзивно читаем значение переменной и сравниваем со старым значением
				if (__LDREXH(ptr) == oldValue)
// пытаемс¤ эксклюзивно записать в переменную новое значение
				{ return __STREXH(newValue, ptr) == 0; }

// кто-то изменил ¤чейку до нас
				__CLREX();
				return false;
			}

			template<class T2>
			static bool CompareExchange(uint8_t* ptr, T2 oldValue, T2 newValue) {
				// эксклюзивно читаем значение переменной и сравниваем со старым значением
				if (__LDREXB(ptr) == oldValue)
// пытаемс¤ эксклюзивно записать в переменную новое значение
				{ return __STREXB(newValue, ptr) == 0; }

// кто-то изменил ¤чейку до нас
				__CLREX();
				return false;
			}


			template <class T, class T2>
			static void Set(T* ptr, T2 newValue) {
				*ptr = newValue;
			}
	};
#undef DECLARE_OP




}