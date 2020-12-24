#include "unity/unity_fixture.h"
#include <void/gsl.h>

class VoidTest_Gsl : UnityTestClass<VoidTest_Chrono> {
		static int* use_not_null(vd::gsl::not_null<int*> p) {
			// use p knowing it's not nullptr, NULL or 0.
			return p;
		}
		static void foo(const vd::gsl::span<int> a) {
			TEST_ASSERT_EQUAL(3, a.size());
			TEST_ASSERT_EQUAL(1, a.data()[0]);
			TEST_ASSERT_EQUAL(2, a.data()[1]);
			TEST_ASSERT_EQUAL(3, a.data()[2]);
		}
	public:
		static void setup() {}
		static void tearDown() {}

		static void Test_Span() {
			int a[] = { 1, 2, 3 };
			foo(a);
		}
		static void Test_NotNull() {
			int* b = 0;
			EXPECT_ASSERT(
			    use_not_null(b)
			);
			EXPECT_ASSERT(
			    use_not_null(nullptr);
			);
			int a = 5;
			int* c = &a;
			EXPECT_NO_ASSERT(
			    use_not_null(c);
			)
		}


		static void run() {
			RUN_TEST_CASE_CLASS(VoidTest_Gsl, Test_Span);
			RUN_TEST_CASE_CLASS(VoidTest_Gsl, Test_NotNull);
		}
};