
#pragma once
#ifdef (_AVR)
#include <avr/pgmspace.h>
#else
	#ifndef PROGMEM
		#define PROGMEM //Emulate for non AVR mcu
	#endif
#endif
namespace vd {


#define ARGS01(P, S) P##00 S
#define ARGS02(P, S) ARGS01(P, S),P##01 S
#define ARGS03(P, S) ARGS02(P, S),P##02 S
#define ARGS04(P, S) ARGS03(P, S),P##03 S
#define ARGS05(P, S) ARGS04(P, S),P##04 S
#define ARGS06(P, S) ARGS05(P, S),P##05 S
#define ARGS07(P, S) ARGS06(P, S),P##06 S
#define ARGS08(P, S) ARGS07(P, S),P##07 S
#define ARGS09(P, S) ARGS08(P, S),P##08 S
#define ARGS0A(P, S) ARGS09(P, S),P##09 S
	namespace Private {
		// Базовый шаблон строки
		template<size_t S, char... L>struct _PStr;
		template<size_t S, char... L>struct _Str;
		// Вспомогательные макросы, раскрывающие последовательность пронумерованных элементов. В примере я ограничился 10 элементами

		// Специализации класса для определенной длины строки (от 0 до 10 символов). Строка гарантированно будет завершена 0.

		template<char... L>struct _Str<0x00, L...> {
			inline static const char v[] = { 0 };
		};

		template<ARGS01(char _, ), char... L>
		struct _Str<0x01, ARGS01(_, ), L...> {
			inline static const char v[] = { ARGS01(_,), 0 };
		};

		template<ARGS02(char _, ), char... L>struct _Str<0x02, ARGS02(_, ), L...> {
			inline static const char v[] = { ARGS02(_,), 0 };
		};

		template<ARGS03(char _, ), char... L>struct _Str<0x03, ARGS03(_, ), L...> {
			inline static const char v[] = { ARGS03(_,), 0 };
		};

		template<ARGS04(char _, ), char... L>struct _Str<0x04, ARGS04(_, ), L...> {
			inline static const char v[] = { ARGS04(_,), 0 };
		};

		template<ARGS05(char _, ), char... L>struct _Str<0x05, ARGS05(_, ), L...> {
			inline static const char v[] = { ARGS05(_,), 0 };
		};

		template<ARGS06(char _, ), char... L>struct _Str<0x06, ARGS06(_, ), L...> {
			inline static const char v[] = { ARGS06(_,), 0 };
		};

		template<ARGS07(char _, ), char... L>struct _Str<0x07, ARGS07(_, ), L...> {
			inline static const char v[] = { ARGS07(_,), 0 };
		};

		template<ARGS08(char _, ), char... L>struct _Str<0x08, ARGS08(_, ), L...> {
			inline static const char v[] = { ARGS08(_,), 0 };
		};

		template<ARGS09(char _, ), char... L>struct _Str<0x09, ARGS09(_, ), L...> {
			inline static const char v[] = { ARGS09(_,), 0 };
		};

		template<ARGS0A(char _, ), char... L>struct _Str<0x0A, ARGS0A(_, ), L...> {
			inline static const char v[] = { ARGS0A(_,), 0 };
		};

		template<char... L>struct _PStr<0x00, L...> {
			inline static const char PROGMEM v[] = { 0 };
		};

		template<ARGS01(char _, ), char... L>
		struct _PStr<0x01, ARGS01(_, ), L...> {
			inline static const char PROGMEM v[] = { ARGS01(_,), 0 };
		};

		template<ARGS02(char _, ), char... L>struct _PStr<0x02, ARGS02(_, ), L...> {
			inline static const char PROGMEM v[] = { ARGS02(_,), 0 };
		};

		template<ARGS03(char _, ), char... L>struct _PStr<0x03, ARGS03(_, ), L...> {
			inline static const char PROGMEM v[] = { ARGS03(_,), 0 };
		};

		template<ARGS04(char _, ), char... L>struct _PStr<0x04, ARGS04(_, ), L...> {
			inline static const char PROGMEM v[] = { ARGS04(_,), 0 };
		};

		template<ARGS05(char _, ), char... L>struct _PStr<0x05, ARGS05(_, ), L...> {
			inline static const char PROGMEM v[] = { ARGS05(_,), 0 };
		};

		template<ARGS06(char _, ), char... L>struct _PStr<0x06, ARGS06(_, ), L...> {
			inline static const char PROGMEM v[] = { ARGS06(_,), 0 };
		};

		template<ARGS07(char _, ), char... L>struct _PStr<0x07, ARGS07(_, ), L...> {
			inline static const char PROGMEM v[] = { ARGS07(_,), 0 };
		};

		template<ARGS08(char _, ), char... L>struct _PStr<0x08, ARGS08(_, ), L...> {
			inline static const char PROGMEM v[] = { ARGS08(_,), 0 };
		};

		template<ARGS09(char _, ), char... L>struct _PStr<0x09, ARGS09(_, ), L...> {
			inline static const char PROGMEM v[] = { ARGS09(_,), 0 };
		};

		template<ARGS0A(char _, ), char... L>struct _PStr<0x0A, ARGS0A(_, ), L...> {
			inline static const char PROGMEM v[] = { ARGS0A(_,), 0 };
		};

	}
	// Селектор символа

	struct CharSelector {
		typedef char(*F)(char);
		template<size_t n>
		constexpr CharSelector(const char(&s)[n], F f) : s(s), l(n), f(f) {}
		template<size_t n>
		constexpr CharSelector(const char(&s)[n]) : s(s), l(n) {}
		constexpr char operator [](size_t i) { return i < l ? f(s[i]) : 0; }
		const char* s = 0;
		const size_t l = 0;
		const F f = [](char c) {return c; };
	};
	// Вспомогательный макрос для экранирования запятых

}
#define STR_UNION(...) __VA_ARGS__
#define MAKE_FUNC_STRING(T,f) STR_UNION(vd::Private::_Str<vd::CharSelector(T).l - 1, ARGS0A(vd::CharSelector(T,f)[0x, ])>::v)
#define MAKE_STRING(T) STR_UNION(vd::Private::_Str<vd::CharSelector(T).l - 1, ARGS0A(vd::CharSelector(T)[0x, ])>::v)

#define MAKE_FUNC_PROGMEM_STRING(T,f) STR_UNION(vd::Private::_PStr<vd::CharSelector(T).l - 1, ARGS0A(vd::CharSelector(T,f)[0x, ])>::v)
#define MAKE_PROGMEM_STRING(T) STR_UNION(vd::Private::_PStr<vd::CharSelector(T).l - 1, ARGS0A(vd::CharSelector(T)[0x, ])>::v)

#define STATIC_STRING(T) MAKE_STRING(T) //STRING IN RAM MEMORY(static, singleton, const)
#define FLASH_STRING(T) MAKE_PROGMEM_STRING(T) //STRING IN PROGMEM MEMORY
//Usage const char* s = FLASH_STRING("Hello");

NOT YET TESTED!


