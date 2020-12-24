#include "unity/unity_fixture.h"
#include <void/result.h>

class VoidTest_Result : UnityTestClass<VoidTest_Result> {
	public:
		static void setup() {}
		static void tearDown() {}

		static void Test_ReturnNone() {
			auto shouldReturnNone = []()->vd::Result<int> {return {}; };
			TEST_ASSERT_EQUAL(false, shouldReturnNone().isComplete());
			TEST_ASSERT_EQUAL(false, shouldReturnNone().isSuccess());
			TEST_ASSERT_EQUAL(false, shouldReturnNone().isFail());
		}
		static void Test_ReturnError() {
			auto shouldReturnError = []()->vd::Result<int> {return { vd::ResultState::E_ERR }; };
			TEST_ASSERT_EQUAL(true, shouldReturnError().isComplete());
			TEST_ASSERT_EQUAL(false, shouldReturnError().isSuccess());
			TEST_ASSERT_EQUAL(true, shouldReturnError().isFail());
		}

		static void Test_ReturnGood() {
			auto shouldReturnGood = []()->vd::Result<int> {return {10 }; };
			TEST_ASSERT_EQUAL(true, shouldReturnGood().isComplete());
			TEST_ASSERT_EQUAL(true, shouldReturnGood().isSuccess());
			TEST_ASSERT_EQUAL(false, shouldReturnGood().isFail());
			TEST_ASSERT_EQUAL(10, shouldReturnGood().value());
		}

		static void TestVoid_ReturnNone() {
			auto shouldReturnNone = []()->vd::Result<void> {return {}; };
			TEST_ASSERT_EQUAL(false, shouldReturnNone().isComplete());
			TEST_ASSERT_EQUAL(false, shouldReturnNone().isSuccess());
			TEST_ASSERT_EQUAL(false, shouldReturnNone().isFail());
		}
		static void TestVoid_ReturnError() {
			auto shouldReturnError = []()->vd::Result<void> {return { vd::ResultState::E_ERR }; };
			TEST_ASSERT_EQUAL(true, shouldReturnError().isComplete());
			TEST_ASSERT_EQUAL(false, shouldReturnError().isSuccess());
			TEST_ASSERT_EQUAL(true, shouldReturnError().isFail());
		}

		static void TestVoid_ReturnGood() {
			auto shouldReturnGood = []()->vd::Result<void> {return {vd::ResultState::S_DONE }; };
			TEST_ASSERT_EQUAL(true, shouldReturnGood().isComplete());
			TEST_ASSERT_EQUAL(true, shouldReturnGood().isSuccess());
			TEST_ASSERT_EQUAL(false, shouldReturnGood().isFail());
		}


		static void run() {
			RUN_TEST_CASE_CLASS(VoidTest_Result, Test_ReturnNone);
			RUN_TEST_CASE_CLASS(VoidTest_Result, Test_ReturnError);
			RUN_TEST_CASE_CLASS(VoidTest_Result, Test_ReturnGood);
			RUN_TEST_CASE_CLASS(VoidTest_Result, TestVoid_ReturnNone);
			RUN_TEST_CASE_CLASS(VoidTest_Result, TestVoid_ReturnError);
			RUN_TEST_CASE_CLASS(VoidTest_Result, TestVoid_ReturnGood);
		}
};