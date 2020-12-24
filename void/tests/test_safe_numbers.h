#include "unity/unity_fixture.h"
#include <void/assert.h>
#include <void/limits.h>
#ifdef _VOID_SAFE_INTEGERS

class VoidTest_SafeNumbers : UnityTestClass<VoidTest_SafeNumbers> {

	public:
		static void setup() {}
		static void tearDown() {}


		#ifdef min
#undef min
		#endif

		#ifdef max
#undef max
		#endif

		template <typename T, typename R>
		static constexpr bool IsInBounds(const R& low, const R& high) {
			return (vd::numeric_limits<T>::min() <= low) && (vd::numeric_limits<T>::max() >= high);
		}



		template <class T, T Min, T Max,
		          class P = boost::safe_numerics::native,
		          class E = boost::safe_numerics::strict_exception_policy,
		          typename vd::enable_if< IsInBounds<T>(Min, Max), int>::type = 0
		          >
		using range_t = boost::safe_numerics::safe_base <T, static_cast<T>(Min), static_cast<T>(Max), P, E>;
		static void TestSignedOverflow() {
			safe_t<s08> a = 127;
			EXPECT_EXCEPTION(safe_t<s08> b = a + 10);
		}
		static void TestMiddleOperationOverflow_OnPCShouldPass() {
			safe_t<u16> a = 65535;
			safe_t<u16> b = 10;
			safe_t<u16> c = 20;
			safe_t<u16> d = 0;
			EXPECT_NO_EXCEPTION( d = a + b - c); //it cast to u32
			TEST_ASSERT_EQUAL(65535 - 10, d);
		}
		static void TestMiddleOperationOverflow_OnAvrShouldBeException() {
			vd::safe_avr_t<u16> a = 65535;
			vd::safe_avr_t<u16> b = 10;
			vd::safe_avr_t<u16> c = 20;
			vd::safe_avr_t<u16> d = 0;
			EXPECT_EXCEPTION(d = a + b - c);
		}
		static void TestMiddleOperationOverflow_OnSTM8ShouldBeException() {
			vd::safe_stm8_t<u16> a = 65535;
			vd::safe_stm8_t<u16> b = 10;
			vd::safe_stm8_t<u16> c = 20;
			vd::safe_stm8_t<u16> d = 0;
			EXPECT_EXCEPTION(d = a + b - c);
		}

		static void SignedRange() {
			range_t < int16_t,-1, 127 > t = 0;
			EXPECT_EXCEPTION(
			    t = 128;
			);
		}
		static void UnsignedRange() {
			range_t<uint16_t, 0, 127> t = 0;
			EXPECT_EXCEPTION(
			    t = 128;
			);
		}
		static void RangeOperations() {
			range_t<uint8_t, 0, 1> t = 1;
			EXPECT_EXCEPTION(
					t+=1;
			);
			EXPECT_NO_EXCEPTION(
				t = 1;
				t = 0;
			)
		}

		static void run() {
			RUN_TEST_CASE_CLASS(VoidTest_SafeNumbers, TestSignedOverflow);
			RUN_TEST_CASE_CLASS(VoidTest_SafeNumbers, TestMiddleOperationOverflow_OnPCShouldPass);
			RUN_TEST_CASE_CLASS(VoidTest_SafeNumbers, TestMiddleOperationOverflow_OnAvrShouldBeException);
			RUN_TEST_CASE_CLASS(VoidTest_SafeNumbers, TestMiddleOperationOverflow_OnSTM8ShouldBeException);
			RUN_TEST_CASE_CLASS(VoidTest_SafeNumbers, SignedRange);
			RUN_TEST_CASE_CLASS(VoidTest_SafeNumbers, UnsignedRange);
			RUN_TEST_CASE_CLASS(VoidTest_SafeNumbers, RangeOperations);
		}
};
#else
class VoidTest_SafeNumbers : UnityTestClass<VoidTest_SafeNumbers> {
public:
	static void run() {}
};
#endif