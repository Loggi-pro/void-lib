#include "unity\unity_fixture.h"
#include <void/assert.h>
#include <void/fixed_point.h>
class VoidTest_FixedPoint : UnityTestClass<VoidTest_FixedPoint> {

	public:
		static void setup() {}
		static void tearDown() {}


		static void Constructor() {
			vd::fixed_point<int32_t, 16> fp0(0);
			TEST_ASSERT((int32_t)fp0 == 0);
			vd::fixed_point<int32_t, 16> fp1((int8_t) - 128);
			TEST_ASSERT((int8_t)fp1 == -128);
			vd::fixed_point<int32_t, 16> fp2((uint8_t)127);
			TEST_ASSERT((uint8_t)fp2 == 127);
			vd::fixed_point<int32_t, 16> fp3((int16_t) - 32768);
			TEST_ASSERT((int16_t)fp3 == -32768);
			vd::fixed_point<int32_t, 16> fp4((uint16_t)32767);
			TEST_ASSERT((uint16_t)fp4 == 32767);
			vd::fixed_point<int32_t, 16> fp5((int32_t) - 32768);
			TEST_ASSERT((int32_t)fp5 == -32768);
			vd::fixed_point<int32_t, 16> fp6((uint32_t)32767);
			TEST_ASSERT((int32_t)fp6 == 32767);
			vd::fixed_point<int32_t, 16> fp7((float) - 1.5);
			TEST_ASSERT((float)fp7 == -1.5f);
			vd::fixed_point<int32_t, 16> fp8((float)1.5);
			TEST_ASSERT((float)fp8 == 1.5f);
			vd::fixed_point<int32_t, 16> fp9((double) - 1.5);
			TEST_ASSERT((double)fp9 == -1.5);
			vd::fixed_point<int32_t, 16> fp10((double)1.5);
			TEST_ASSERT((double)fp10 == 1.5);
			vd::fixed_point<int32_t, 16> fp11((long double) - 1.5);
			TEST_ASSERT((long double)fp11 == -1.5L);
			vd::fixed_point<int32_t, 16> fp12((long double)1.5);
			TEST_ASSERT((long double)fp12 == 1.5L);
		}

		static void Copy_construction() {
			vd::fixed_point<int32_t, 16> fp0(0);
			vd::fixed_point<int32_t, 16> fp0c(fp0);
			TEST_ASSERT((int32_t)fp0c == 0);
			vd::fixed_point<int32_t, 16> fp1((int8_t) - 128);
			vd::fixed_point<int32_t, 16> fp1c(fp1);
			TEST_ASSERT((int8_t)fp1c == -128);
			vd::fixed_point<int32_t, 16> fp2((uint8_t)127);
			vd::fixed_point<int32_t, 16> fp2c(fp2);
			TEST_ASSERT((uint8_t)fp2c == 127);
			vd::fixed_point<int32_t, 16> fp3((int16_t) - 32768);
			vd::fixed_point<int32_t, 16> fp3c(fp3);
			TEST_ASSERT((int16_t)fp3c == -32768);
			vd::fixed_point<int32_t, 16> fp4((uint16_t)32767);
			vd::fixed_point<int32_t, 16> fp4c(fp4);
			TEST_ASSERT((uint16_t)fp4c == 32767);
			vd::fixed_point<int32_t, 16> fp5((int32_t) - 32768);
			vd::fixed_point<int32_t, 16> fp5c(fp5);
			TEST_ASSERT((int32_t)fp5c == -32768);
			vd::fixed_point<int32_t, 16> fp6((uint32_t)32767);
			vd::fixed_point<int32_t, 16> fp6c(fp6);
			TEST_ASSERT((int32_t)fp6c == 32767);
			vd::fixed_point<int32_t, 16> fp7((float) - 1.5);
			vd::fixed_point<int32_t, 16> fp7c(fp7);
			TEST_ASSERT((float)fp7c == -1.5f);
			vd::fixed_point<int32_t, 16> fp8((float)1.5);
			vd::fixed_point<int32_t, 16> fp8c(fp8);
			TEST_ASSERT((float)fp8c == 1.5f);
			vd::fixed_point<int32_t, 16> fp9((double) - 1.5);
			vd::fixed_point<int32_t, 16> fp9c(fp9);
			TEST_ASSERT((double)fp9c == -1.5);
			vd::fixed_point<int32_t, 16> fp10((double)1.5);
			vd::fixed_point<int32_t, 16> fp10c(fp10);
			TEST_ASSERT((double)fp10c == 1.5);
			vd::fixed_point<int32_t, 16> fp11((long double) - 1.5);
			vd::fixed_point<int32_t, 16> fp11c(fp11);
			TEST_ASSERT((long double)fp11c == -1.5L);
			vd::fixed_point<int32_t, 16> fp12((long double)1.5);
			vd::fixed_point<int32_t, 16> fp12c(fp12);
			TEST_ASSERT((long double)fp12c == 1.5L);
		}


		static void Copy_assignment() {
			vd::fixed_point<int32_t, 16> fp0(0);
			vd::fixed_point<int32_t, 16> fp0c;
			fp0c = fp0;
			TEST_ASSERT((int32_t)fp0c == 0);
			vd::fixed_point<int32_t, 16> fp1((int8_t) - 128);
			vd::fixed_point<int32_t, 16> fp1c;
			fp1c = fp1;
			TEST_ASSERT((int8_t)fp1c == -128);
			vd::fixed_point<int32_t, 16> fp2((uint8_t)127);
			vd::fixed_point<int32_t, 16> fp2c;
			fp2c = fp2;
			TEST_ASSERT((uint8_t)fp2c == 127);
			vd::fixed_point<int32_t, 16> fp3((int16_t) - 32768);
			vd::fixed_point<int32_t, 16> fp3c;
			fp3c = fp3;
			TEST_ASSERT((int16_t)fp3c == -32768);
			vd::fixed_point<int32_t, 16> fp4((uint16_t)32767);
			vd::fixed_point<int32_t, 16> fp4c;
			fp4c = fp4;
			TEST_ASSERT((uint16_t)fp4c == 32767);
			vd::fixed_point<int32_t, 16> fp5((int32_t) - 32768);
			vd::fixed_point<int32_t, 16> fp5c;
			fp5c = fp5;
			TEST_ASSERT((int32_t)fp5c == -32768);
			vd::fixed_point<int32_t, 16> fp6((uint32_t)32767);
			vd::fixed_point<int32_t, 16> fp6c;
			fp6c = fp6;
			TEST_ASSERT((uint32_t)fp6c == 32767);
			vd::fixed_point<int32_t, 16> fp7((float) - 1.5);
			vd::fixed_point<int32_t, 16> fp7c;
			fp7c = fp7;
			TEST_ASSERT((float)fp7c == -1.5f);
			vd::fixed_point<int32_t, 16> fp8((float)1.5);
			vd::fixed_point<int32_t, 16> fp8c;
			fp8c = fp8;
			TEST_ASSERT((float)fp8c == 1.5f);
			vd::fixed_point<int32_t, 16> fp9((double) - 1.5);
			vd::fixed_point<int32_t, 16> fp9c;
			fp9c = fp9;
			TEST_ASSERT((double)fp9c == -1.5);
			vd::fixed_point<int32_t, 16> fp10((double)1.5);
			vd::fixed_point<int32_t, 16> fp10c;
			fp10c = fp10;
			TEST_ASSERT((double)fp10c == 1.5);
			vd::fixed_point<int32_t, 16> fp11((long double) - 1.5);
			vd::fixed_point<int32_t, 16> fp11c;
			fp11c = fp11;
			TEST_ASSERT((long double)fp11c == -1.5L);
			vd::fixed_point<int32_t, 16> fp12((long double)1.5);
			vd::fixed_point<int32_t, 16> fp12c;
			fp12c = fp12;
			TEST_ASSERT((long double)fp12c == 1.5L);
		}

		static void Comparison() {
			vd::fixed_point<int32_t, 16> fp0(0);
			vd::fixed_point<int32_t, 16> fp1((int8_t) - 128);
			vd::fixed_point<int32_t, 16> fp2((uint8_t)127);
			vd::fixed_point<int32_t, 16> fp3((int16_t) - 32768);
			vd::fixed_point<int32_t, 16> fp4((uint16_t)32767);
			vd::fixed_point<int32_t, 16> fp5((int32_t) - 32768);
			vd::fixed_point<int32_t, 16> fp6((uint32_t)32767);
			vd::fixed_point<int32_t, 16> fp7((float) - 1.5);
			vd::fixed_point<int32_t, 16> fp8((float)1.5);
			vd::fixed_point<int32_t, 16> fp9((double) - 1.5);
			vd::fixed_point<int32_t, 16> fp10((double)1.5);
			vd::fixed_point<int32_t, 16> fp11((long double) - 1.5);
			vd::fixed_point<int32_t, 16> fp12((long double)1.5);
			bool smaller = fp1 < fp2;
			bool bigger = fp2 > fp1;
			bool notsmaller = !(fp4 < fp3);
			bool notbigger = !(fp3 > fp4);
			TEST_ASSERT(smaller);
			TEST_ASSERT(bigger);
			TEST_ASSERT(notsmaller);
			TEST_ASSERT(notbigger);
		}

		static void Equality() {
			vd::fixed_point<int32_t, 16> fp0(0);
			vd::fixed_point<int32_t, 16> fp1((int8_t) - 128);
			vd::fixed_point<int32_t, 16> fp2((uint8_t)127);
			vd::fixed_point<int32_t, 16> fp3((int16_t) - 32768);
			vd::fixed_point<int32_t, 16> fp4((uint16_t)32767);
			vd::fixed_point<int32_t, 16> fp5((int32_t) - 32768);
			vd::fixed_point<int32_t, 16> fp6((uint32_t)32767);
			vd::fixed_point<int32_t, 16> fp7((float) - 1.5);
			vd::fixed_point<int32_t, 16> fp8((float)1.5);
			vd::fixed_point<int32_t, 16> fp9((double) - 1.5);
			vd::fixed_point<int32_t, 16> fp10((double)1.5);
			vd::fixed_point<int32_t, 16> fp11((long double) - 1.5);
			vd::fixed_point<int32_t, 16> fp12((long double)1.5);
			bool same = fp3 == fp5 && fp4 == fp6 && fp7 == fp9 && fp9 == fp11 &&
			            fp8 == fp10 && fp10 == fp12;
			bool notsame = fp1 != fp2 && fp3 != fp4 && fp5 != fp6 && fp7 != fp8 &&
			               fp9 != fp10 && fp11 != fp12;
			TEST_ASSERT(same);
			TEST_ASSERT(notsame);
		}

		static void Unary_minus() {
			vd::fixed_point<int32_t, 16> fp1((int8_t) - 127);
			vd::fixed_point<int32_t, 16> fp2((uint8_t)127);
			vd::fixed_point<int32_t, 16> fp3((int16_t) - 32767);
			vd::fixed_point<int32_t, 16> fp4((uint16_t)32767);
			vd::fixed_point<int32_t, 16> fp5((int32_t) - 32767);
			vd::fixed_point<int32_t, 16> fp6((uint32_t)32767);
			vd::fixed_point<int32_t, 16> fp7((float) - 1.5);
			vd::fixed_point<int32_t, 16> fp8((float)1.5);
			vd::fixed_point<int32_t, 16> fp9((double) - 1.5);
			vd::fixed_point<int32_t, 16> fp10((double)1.5);
			vd::fixed_point<int32_t, 16> fp11((long double) - 1.5);
			vd::fixed_point<int32_t, 16> fp12((long double)1.5);
			TEST_ASSERT(fp1 == -fp2);
			TEST_ASSERT(-fp1 == fp2);
			TEST_ASSERT(fp3 == -fp4);
			TEST_ASSERT(-fp3 == fp4);
			TEST_ASSERT(fp5 == -fp6);
			TEST_ASSERT(-fp5 == fp6);
			TEST_ASSERT(fp7 == -fp8);
			TEST_ASSERT(-fp7 == fp8);
			TEST_ASSERT(fp9 == -fp10);
			TEST_ASSERT(-fp9 == fp10);
			TEST_ASSERT(fp11 == -fp12);
			TEST_ASSERT(-fp11 == fp12);
		}

		static void Prefix_increment() {
			double a = vd::numeric_limits<vd::fixed_point<int32_t, 16> >::min();
			vd::fixed_point<int32_t, 16> b = a;

			while (a < (double)
			        vd::numeric_limits<vd::fixed_point<int32_t, 16> >::max()) {
				++a;
				TEST_ASSERT(++b == (vd::fixed_point<int32_t, 16>)(a));
			}
		}

		static void Prefix_decrement() {
			double a = vd::numeric_limits<vd::fixed_point<int32_t, 16> >::max();
			vd::fixed_point<int32_t, 16> b = a;

			while (a > (double)
			        vd::numeric_limits<vd::fixed_point<int32_t, 16> >::min() +
			        1) {
				--a;
				TEST_ASSERT(--b == (vd::fixed_point<int32_t, 16>)(a));
			}
		}

		static void Postfix_decrement() {
			double a = vd::numeric_limits<vd::fixed_point<int32_t, 16> >::max();
			vd::fixed_point<int32_t, 16> b = a;

			while (a > (double)
			        vd::numeric_limits<vd::fixed_point<int32_t, 16> >::min() +
			        1) {
				TEST_ASSERT(b-- == (vd::fixed_point<int32_t, 16>)(a));
				a--;
			}
		}

		static void Add() {
			double a = vd::numeric_limits<vd::fixed_point<int16_t, 8> >::min();
			double b = vd::numeric_limits<vd::fixed_point<int16_t, 8> >::max();

			for (double x = a; x < b; ++x) {
				for (double y = a; y < b; ++y) {
					vd::fixed_point<int32_t, 16> xx = x;
					vd::fixed_point<int32_t, 16> yy = y;
					TEST_ASSERT((vd::fixed_point<int32_t, 16>)(x + y) == xx + yy);
				}
			}
		}

		static void Subtract() {
			double a = vd::numeric_limits<vd::fixed_point<int16_t, 8> >::min();
			double b = vd::numeric_limits<vd::fixed_point<int16_t, 8> >::max();

			for (double x = a; x < b; ++x) {
				for (double y = a; y < b; ++y) {
					vd::fixed_point<int32_t, 16> xx = x;
					vd::fixed_point<int32_t, 16> yy = y;
					TEST_ASSERT((vd::fixed_point<int32_t, 16>)(x - y) == xx - yy);
				}
			}
		}
		static void Add_assign() {
			double a = vd::numeric_limits<vd::fixed_point<int16_t, 8> >::min();
			double b = vd::numeric_limits<vd::fixed_point<int16_t, 8> >::max();

			for (double x = a; x < b; ++x) {
				for (double y = a; y < b; ++y) {
					vd::fixed_point<int32_t, 16> xx(x);
					xx += vd::fixed_point<int32_t, 16>(y);
					TEST_ASSERT((vd::fixed_point<int32_t, 16>)(x + y) == xx);
				}
			}
		}

		static void Subtract_assign() {
			double a = vd::numeric_limits<vd::fixed_point<int16_t, 8> >::min();
			double b = vd::numeric_limits<vd::fixed_point<int16_t, 8> >::max();

			for (double x = a; x < b; ++x) {
				for (double y = a; y < b; ++y) {
					vd::fixed_point<int32_t, 16> xx(x);
					xx -= vd::fixed_point<int32_t, 16>(y);
					TEST_ASSERT((vd::fixed_point<int32_t, 16>)(x - y) == xx);
				}
			}
		}
		static void Multiply() {
			double a = vd::numeric_limits<vd::fixed_point<int16_t, 8> >::min();
			double b = vd::numeric_limits<vd::fixed_point<int16_t, 8> >::max();

			for (double x = a; x < b; ++x) {
				for (double y = a; y < b; ++y) {
					vd::fixed_point<int32_t, 16> xx = x;
					vd::fixed_point<int32_t, 16> yy = y;
					TEST_ASSERT((vd::fixed_point<int32_t, 16>)(x * y) == xx * yy);
				}
			}
		}
		/*
		static void Divide() {
			double a = vd::numeric_limits<vd::fixed_point<int16_t, 8> >::min();
			double b = vd::numeric_limits<vd::fixed_point<int16_t, 8> >::max();

			for (double x = a; x < b; ++x) {
				for (double y = a; y < b; ++y) {
					vd::fixed_point<int16_t, 8> xx = x;
					vd::fixed_point<int16_t, 8> yy = y;
					vd::fixed_point<int16_t, 8> left(x / y);
					vd::fixed_point<int16_t, 8> right = xx / yy;
					//TEST_ASSERT(left == right); //cant test, because epsilon problem. +-1
				}
			}
		}*/
		static void Multiply_assign() {
			double a = vd::numeric_limits<vd::fixed_point<int16_t, 8> >::min();
			double b = vd::numeric_limits<vd::fixed_point<int16_t, 8> >::max();

			for (double x = a; x < b; ++x) {
				for (double y = a; y < b; ++y) {
					vd::fixed_point<int32_t, 16> xx(x);
					xx *= vd::fixed_point<int32_t, 16>(y);
					TEST_ASSERT((vd::fixed_point<int32_t, 16>)(x * y) == xx);
				}
			}
		}
		static void Divide_assign() {
			double a = vd::numeric_limits<vd::fixed_point<int16_t, 8> >::min();
			double b = vd::numeric_limits<vd::fixed_point<int16_t, 8> >::max();

			for (double x = a; x < b; ++x) {
				for (double y = a; y < b; ++y) {
					vd::fixed_point<int32_t, 16> xx(x);

					if (y != 0) {
						xx /= vd::fixed_point<int32_t, 16>(y);
						//TEST_ASSERT((vd::fixed_point<int32_t, 16>)(x / y) == xx);
					}
				}
			}
		}
		static void Absolute() {
			double a = vd::numeric_limits<vd::fixed_point<int32_t, 16> >::min();
			a += 1;

			while (a <= (double)
			        vd::numeric_limits<vd::fixed_point<int32_t, 16> >::max()) {
				vd::fixed_point<int32_t, 16> b = fabs((vd::fixed_point<int32_t, 16>)a);
				TEST_ASSERT((double)b == fabs(a));
				a += .5;
			}
		}
		static void square_root() {
			using fp32_t = vd::fixed_point<int32_t, 16>;

			for (double a = 0;
			        a <= (double)vd::numeric_limits<fp32_t>::max();
			        a += .5) {
				fp32_t b = sqrt((fp32_t)a);
				fp32_t bb = (double)b;
				fp32_t sqrta = sqrt(a);
				TEST_ASSERT(bb== sqrta);
			}
		}

		static void run() {
			RUN_TEST_CASE_CLASS(VoidTest_FixedPoint, Constructor);
			RUN_TEST_CASE_CLASS(VoidTest_FixedPoint, Copy_construction);
			RUN_TEST_CASE_CLASS(VoidTest_FixedPoint, Copy_assignment);
			RUN_TEST_CASE_CLASS(VoidTest_FixedPoint, Equality);
			RUN_TEST_CASE_CLASS(VoidTest_FixedPoint, Unary_minus);
			RUN_TEST_CASE_CLASS(VoidTest_FixedPoint, Prefix_increment);
			RUN_TEST_CASE_CLASS(VoidTest_FixedPoint, Prefix_decrement);
			RUN_TEST_CASE_CLASS(VoidTest_FixedPoint, Postfix_decrement);
			RUN_TEST_CASE_CLASS(VoidTest_FixedPoint, Add);
			RUN_TEST_CASE_CLASS(VoidTest_FixedPoint, Subtract);
			RUN_TEST_CASE_CLASS(VoidTest_FixedPoint, Add_assign);
			RUN_TEST_CASE_CLASS(VoidTest_FixedPoint, Subtract_assign);
			RUN_TEST_CASE_CLASS(VoidTest_FixedPoint, Multiply);
			//RUN_TEST_CASE_CLASS(VoidTest_FixedPoint, Divide);
			RUN_TEST_CASE_CLASS(VoidTest_FixedPoint, Multiply_assign);
			RUN_TEST_CASE_CLASS(VoidTest_FixedPoint, Divide_assign);
			RUN_TEST_CASE_CLASS(VoidTest_FixedPoint, Absolute);
			//RUN_TEST_CASE_CLASS(VoidTest_FixedPoint, square_root);
		}
};


