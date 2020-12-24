#pragma once
#include <unity/unity_fixture_classes.h>
#include <void/chrono.h>
class VoidTest_Chrono : UnityTestClass<VoidTest_Chrono> {
	public:
		static void setup() {}
		static void tearDown() {}
		static void ChronoTest() {
			vd::chrono::seconds_t s(5);
			vd::chrono::milli_t m(1000);
			vd::chrono::micro_t us(1000000);
			s += m;
			s += us;
			TEST_ASSERT_EQUAL(7, s.count());
		}

		static void ChronoTest_FractionAdding_ShouldStrictValueAndAssert() {
			vd::chrono::seconds_t s(5);
			vd::chrono::milli_t m(500);
			EXPECT_ASSERT(
			    s += m;
			    s += m;
			);
			TEST_ASSERT_EQUAL(5, s.count());
		}

		static void ChronoTest_Equal() {
			vd::chrono::seconds_t s(5);
			vd::chrono::milli_t m(5000);
			TEST_ASSERT_EQUAL(true, s == m);
		}


		static void ChronoTest_Diff() {
			vd::chrono::seconds_t s(5);
			vd::chrono::micro_t m(5000001);
			TEST_ASSERT_EQUAL(true, s < m);
		}



		static void run() {
			RUN_TEST_CASE_CLASS(VoidTest_Chrono, ChronoTest);
			RUN_TEST_CASE_CLASS(VoidTest_Chrono, ChronoTest_FractionAdding_ShouldStrictValueAndAssert);
			RUN_TEST_CASE_CLASS(VoidTest_Chrono, ChronoTest_Equal);
			RUN_TEST_CASE_CLASS(VoidTest_Chrono, ChronoTest_Diff);
		}
};