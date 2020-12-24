#pragma once
#include <unity/unity_fixture.h>
#include <void/tests/test_bits.h>
#include <void/tests/test_bezier.h>
#include <void/tests/test_comparators.h>
#include <void/tests/test_numeric.h>
#include <void/tests/test_auto_size.h>
#include <void/tests/test_chrono.h>
#include <void/tests/test_gsl.h>
#include <void/tests/test_safe_numbers.h>
#include <void/tests/test_dateutils.h>
#include <void/tests/test_fixed_point.h>
#include <void/tests/test_result.h>
inline void RunVoidTests() {
	RUN_TEST_GROUP_CLASS(VoidTest_Bezier);
	RUN_TEST_GROUP_CLASS(VoidTest_Bits);
	RUN_TEST_GROUP_CLASS(VoidTest_Numeric);
	RUN_TEST_GROUP_CLASS(VoidTest_Math);
	RUN_TEST_GROUP_CLASS(VoidTest_Chrono);
	RUN_TEST_GROUP_CLASS(VoidTest_Gsl);
	RUN_TEST_GROUP_CLASS(VoidTest_SafeNumbers);
	RUN_TEST_GROUP_CLASS(VoidTest_Dateutils);
	RUN_TEST_GROUP_CLASS(VoidTest_FixedPoint);
	RUN_TEST_GROUP_CLASS(VoidTest_Result);
}