# Void library

Micro library for abstraction of type system from platform for MCU like `AVR`, `STM8`, `STM32`.

# Quick Start

1. Add **<void/platform_specific.h>** to every file in project. (You can use force include of c\c++ compiler)
2. Select platform by defining one of the macros (global define to all project): `_AVR`,`_STM8`,`_ARM`, `WIN32`.
3. (Optional) Predefine `_UNITY` for TEST project based on Unity framework.
4. (Optional) Enable _Safe numeric_ feature for PC project.

# Features

- **Safe Numerics**: integer range checking. Detection of integer overflows, outranges and invalid math evaluations (on different CPU architectures) (<boost/safe_numerics> integration).

---

# Types

- _Header_: **void/platform_specific.h**
- _Description_:
  1. Alias to standart types,
     unsigned: `u08, u16, u32, u64`, signed: `s08, s16, s32, s64`.
  2. Null pointer type `nullptr`.
  3. Byte and word getters from variable:
     `vd::lowByte(byte)`, `vd::hiByte(byte)`, `vd::lowWord(word)`, `vd::hiWord(word)`.
  4. `PACK()` macro for platform-independent packed structs:
     `PACK(struct foo {char a; });`
  5. Types with different order of bytes (and auto conversion between them and common types).
     4.1. Little endian types guaranteed,
     unsigned: `u08le, u16le, u32le, u64le`, signed: `s08le, s16le, s32le, s64le`.
     4.2. Big endian types guaranteed,
     unsigned: `u08be, u16be, u32be, u64be`, signed: `s08be, s16be, s32be, s64ble`.
     4.3. Converter template functions:
     `T vd::toLittleEndian<T>(T val)`, `T vd::toBigEndian<T>(T val) `, `T vd::fromLittleEndian<T>(T val)`, `T vd::fromBigEndian<T>(T val)`.
  6. Size of array function: `countOf(arr)` (c++11) or `COUNT_OF(arr)` (macro).

# GSL Types

- _Header_: **void/gsl.h**
- _Description_:
  1. `vd::gsl::span<T>` A view of contiguous T's, replace for (\*,length) in function argument.
  2. `vd::gsl::not_null<>` wrap any pointer, auto assert for nullptr.
- _Example_:
<details> 
<summary> (Click to expand):</summary>

```c++
    int summ(const vd::gsl::span<int> a) { //same as (int* a, int a_length)
        int res = 0;
        for (int i = 0; i<a.size();++i){
            res+=a.data()[i];
        }
        return res;
    }
    //using
    int a[] = { 1, 2, 3 };
	int res = summ(a);
```

```c++
    int* use_not_null(vd::gsl::not_null<int*> p) { //assert here if p==nullptr
    	// use p knowing it's not nullptr, NULL or 0.
    	return p;
    }
    //using
    int a = 5;
	int* b = &a;
    use_not_null(b);
```

</details>

# Time types

- _Header_: **void/chrono.h**
- _Description_:
  1. Time types for different durations:
     `vd::hours(x)`, `vd::minutes(x)`, `vd::seconds(x)`, `vd::milli(x)`, `vd::micro(x) `.
  2. Auto convert any time type to other type in math operations:
     `vd::hours(1)+vd::minutes(10) == vd::minutes(70)`.
  3. Literal time types for using in compile time expressions:  
     `vd::hours_l<x> vd::minutes_l<x>`, `vd::seconds_l<x>`, `vd::milli_l<x>`, `vd::micro_l<x> `.
- _Warning_: On use math operations with different time types, bigger time type will be trunked and call _ASSERTION_ (in debug mode):

```c++
    //WARNING Never do like this
	vd::seconds s(5);
	vd::milli m(500);
	s += m; //assert here
	s += m; //assert here
    //s == 5
```

- _Example_:
<details> 
<summary> (Click to expand):</summary>

```c++
    //Run-time example
	vd::seconds s(5);
	vd::milli m(1000);
	vd::micro us(1000000);
	s += m;
	s += us;
    if (s.count() == 7) {
        ...
    }
```

```c++
    //Compile-time example
    enum {
        TIME = vd::seconds_l<5>::static_value+vd::milli_l<1000>::static_value; // Equals to 6
    }
```

</details>

- _Comment_:
  1. Run-time types have `.count()` method which returns time value (in corresponding units).
  2. Compile-time types have `::static_value` field which returns compile-time raw time value (in corresponding units).

# Delay

- _Header_: **void/delay.h**
- _Description_:
  1. Dumb blocking delay:
     `vd::delay_ns<x>()`, `vd::delay_us<x>()`, `vd::delay_ms<x>()`.
  2. Time type support:
     `vd::delay<time_type_literal>()`, `vd::delay(time_type);`.
- _Example_:
<details> 
<summary> (Click to expand)</summary>

```c++
    //Templated functions
	vd::delay_ms<1000>();
	vd::delay<vd::seconds_l<1>>();
```

```c++
    //Pass time as argument
   	vd::delay(vd::milli(1000));
```

</details>

- _Comment_:
  1. Better to use templated functions in case of good compiler optimization.
  1. Pass time as argument only if you have compile-time unknown delay duration.

# Interrupts

- _Header_: **void\interrupt.h**
- _Description_:
  1. Interrupt routine macro for architecture-independent interrupt handlers: `VOID_ISR(x){}`.
  1. Interrupt control: `vd::DisableInterrupts()` and `vd::EnableInterrupts()`
  1. Blocks with disabled interrupts:
     `ATOMIC_BLOCK(RESTORE_STATE) {<code>}` - disable interrupts in block and restore interrupt state (RESTORE_STATE is arg by default, you can omit it)
     `ATOMIC_BLOCK(FORCE_ON) {<code>}` - disable interrupts in block and force enable interrupts on exit

# Assertion

- _Header_: **void/assert.h**
- _Description_:
  1. Assert implementation `assert(bool);`. Call `printf` and `abort()` on fail.
  2. Assert checking is persist only in **Debug** mode (macro `_DEBUG` defined).
  3. Define macro `VOID_RELEASE_ASSERT` to keep assert checking in **Release** mode.
  4. Define macro `VOID_ASSERT_TRAP` to trap assert by user-defined function `_void_assert_trap(char* filename, int line)`. (Setup custom action on failed condition)
  5. (Unity Support): define macro `_UNITY` globally for all project. If macro defined, `assert` will register assert in Unity system on fail.
     Requirements:
     5.1. Unity header with path <unity/unity_fixture.h> must exist.
     5.2. `void UnitySetAssertStatus(char status, const char* inFile, UNITY_LINE_TYPE atLine)` function must exist;
- _Example_:
<details> 
<summary> (Click to expand):</summary>

```c++
    int a = 1;
    assert(a==1); //pass
    assert(a==0); //fail
```

</details>

- _Comment_:
  1. When no define `_DEBUG` exist all assert checking is removed (except for `VOID_RELEASE_ASSERT` define).

# Static Assertion

- _Header_: **void/static_assert.h**
- _Description_: Assert checking in compile-time. Can be used outside of functions, and inside struct\class definitions:
  `VOID_STATIC_ASSERT(bool)` or `VOID_STATIC_ASSERT_MSG(bool,msg)`.
- _Example_:
<details> 
<summary> (Click to expand):</summary>

```c++
    int a = 1;
    enum { TIME = 1};
    VOID_STATIC_ASSERT(a==1); // Inappropriate use, not compile-time variable
    VOID_STATIC_ASSERT(TIME==1); // pass
    VOID_STATIC_ASSERT(TIME==0); // static assert fail, compile-time error
```

</details>

---

# Feature: Safe numerics

- _Description_: redefine built-in library types: unsigned: `u08, u16, u32, u64`, signed: `s08, s16, s32, s64` as special safe types. In math operations this safe types uses:
  1. CPU-architecture specific middle types (for example: 16-bit integers for stm8 instead of 32-bit of x86).
  2. Range and overflow checkin.
- _Usage_:
  1. Compile code (tests) for x86 architecture, which will be executed like TARGET-architecture code.
  2. Test will fail on invalid equation evaluations.
  3. Exception will be throws on integer overflows and range check faults.
- _How to use_:
  1. Globaly define macro: `_VOID_SAFE_INTEGERS`
  1. Globaly define macro for target CPU (to choose size of integer types): `_TARGET_AVR` or `_TARGET_STM8` (if no target CPU defined then uses native architecture types).
  1. Write common code with `u08, u16, u32, u64, s08, s16, s32, s64` types.
  1. Use `literal(x)` macro for literal integer constants.
- _Requirements_:
  1. C++14 Support (Visual studio 2017+)
  2. Valid path to `boost` library in c/c++ compiler includes path's. (feature uses <boost/safe_numerics/...> headers in source code).
- _Example_:
<details> 
<summary> (Click to expand):</summary>:

```c++
	//integer overflow
	s08 x = 127;
	s08 y = 2;
    s08 z = x+y; // rather than producing an invalid result an exception is thrown
```

```c++
	//invalid eq. evaluation on target CPU. This code evaluate wrong only on STM8 (correct on x86 test)
    u16 averageAmplitude = 12000;
	u16 res = (averageAmplitude*(literal(100) - literal(5))) / literal(100); //With _TARGET_STM8 exception is thrown
	//x86 Result: res == 11400 (correct)
	//stm8 Result: res == 258 (wrong)
```

</details>

---

# Troubleshooting

1. `Error : #error NO_ARCHITECTURE_DEFINED: _AVR/_ARM/WIN32/_STM8`
   Define architecture-specific macro: `_AVR`/`_ARM`/`WIN32`/`_STM8`.
2. `Fatal error C1189: #error: Compiler must support C++17 standart for _VOID_SAFE_INTEGERS directive.`
   Compiler don`t support C++17 for _Safe numeric_ feature.
3. `...boost\safe_base_operations.hpp(549): error C2131: expression did not evaluate to a constant`
   `...\boost\safe_numerics\checked_result.hpp(36): note: failure was caused by a read of a variable outside its lifetime`
   `...\boost\safe_numerics\checked_result.hpp(36): note: see usage of '$S1'`
   In Project options set **C/C++ Language->Conformance mode** to **Yes(/permissive)**.
