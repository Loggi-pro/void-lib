#pragma once
#include <unity/unity_fixture_classes.h>
#include <void/numeric.h>
#include <void/math.h>
class VoidTest_Numeric : UnityTestClass<VoidTest_Numeric> {

		template<typename Int>
		static bool test_midpoint_twos_comp() {
			const vd::make_unsigned_t<Int> a = 10, b = 5;

			const auto mab = vd::midpoint(a, b);
			return (mab == 7) || (mab == 8);
		}

		template<typename Real>
		static  bool test_midpoint_huge() {
			const auto huge = vd::numeric_limits<Real>::max();
			const auto a = -huge;
			const auto b = +huge;
			const auto c = vd::midpoint(a, b);
			//std::cout << "c = " << c << '\n';
			//std::cout << "c == 0: " << std::boolalpha << (c == Real{ 0 }) << '\n';
			return c == Real{ 0 };
		}
		template<typename Tp>
		static  bool test_midpoint_ptr() {
			const unsigned int num = 21;
			const Tp arr[num] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
			const auto a = arr;
			const auto b = arr + num;
			const auto ab = vd::midpoint(a, b);
			//std::cout << "a = " << a << "; b = " << b << "; ab = " << ab << '\n';
			//std::cout << "ab - a = " << ab - a << "; ab - b = " << ab - b << '\n';
			//std::cout << "ab = " << ab << "; *ab = " << *ab << '\n';
			const auto ba = vd::midpoint(b - 1, a - 1); // rbegin, rend
			//std::cout << "ba - (b-1) = " << ba - (b - 1) << "; ba - (a-1) = " << ba - (a - 1) << '\n';
			//std::cout << "ba = " << ba << "; *ba = " << *ba << '\n';
			return (*ab == *ba) && (*ab == 10);
		}

	public:

		static void setup() {}
		static void tearDown() {}
		static void Numeric_Midpoint() {
			TEST_ASSERT(test_midpoint_twos_comp<unsigned char>());
			TEST_ASSERT(test_midpoint_twos_comp<short>());
			TEST_ASSERT(test_midpoint_twos_comp<int>());
			TEST_ASSERT(test_midpoint_twos_comp<long>());
			TEST_ASSERT(test_midpoint_twos_comp<long long>());
			TEST_ASSERT(test_midpoint_huge<float>());
			TEST_ASSERT(test_midpoint_huge<double>());
			TEST_ASSERT(test_midpoint_huge<long double>());
			TEST_ASSERT(test_midpoint_ptr<int>());
		}

		static void run() {
			RUN_TEST_CASE_CLASS(VoidTest_Numeric, Numeric_Midpoint);
		}
};


class VoidTest_Math : UnityTestClass<VoidTest_Math> {

		template<typename Real>
		static bool test() {
			const auto a = Real{ 5 };
			const auto b = Real{ 10 };
			const auto t = Real{ Real(0.75) };
			const Real res = vd::lerp(a, b, t);
			//std::cout << "x = " << x << '\n';
			return res == (Real)8.75;
		}

		template<typename Real>
		static bool test_ends() {
			const auto a = Real{ -3 };
			const auto b = Real{ +5 };
			const auto ca = vd::lerp(a, b, Real{ 0 });
			//std::cout << "ca = " << ca << '\n';
			//std::cout << "ca == a: " << std::boolalpha << (ca == a) << '\n';
			const auto cb = vd::lerp(a, b, Real{ 1 });
			//std::cout << "cb = " << cb << '\n';
			//std::cout << "cb == b: " << std::boolalpha << (cb == b) << '\n';
			return ca == a && cb == b;
		}

		template<typename Real>
		bool static test_nan() {
			const auto a = Real{ 5 };
			const auto b = Real{ 10 };
			const auto t = Real{ 0.75L };
			const auto anan = vd::numeric_limits<Real>::quiet_NaN();
			const auto bnan = vd::numeric_limits<Real>::quiet_NaN();
			const auto tnan = vd::numeric_limits<Real>::quiet_NaN();
			const auto nan = vd::isnan(vd::lerp(anan, b, t))
			                 && vd::isnan(vd::lerp(a, bnan, t))
			                 && vd::isnan(vd::lerp(a, b, tnan));
			//std::cout << "nan: " << std::boolalpha << nan << '\n';
			return nan;
		}
		/*
		template<typename Real>
		static bool test_subnorm() {
			const auto denorm = vd::numeric_limits<Real>::denorm_min();
			const auto a = Real{ 5 } *denorm;
			const auto b = Real{ 10 } *denorm;
			const auto t = Real{ 0.75L };
			const auto x = vd::lerp(a, b, t);
			//std::cout << "x: " << x / denorm << '\n';
			const auto a00 = Real{ 500 } *denorm;
			const auto b00 = Real{ 1000 } *denorm;
			const auto x00 = vd::lerp(a00, b00, t);
			std::cout << "x00: " << x00 / denorm << '\n';
			return x00 / denorm == 875.f && x / denorm == 8.75f;
		}
		*/
		template<typename Real>
		static bool test_inf() {
			const auto a = Real{ 5 };
			const auto b = a;
			const auto t = vd::numeric_limits<Real>::infinity();
			const auto c = vd::lerp(a, b, t);
			//std::cout << "c = " << c << '\n';
			//std::cout << "c == a: " << std::boolalpha << (c == a) << '\n';
			return c == a;
		}

		template<typename Real>
		static bool test_huge() {
			const auto max = vd::numeric_limits<Real>::max() / 16;
			const auto a = Real{ 5 } *max;
			const auto b = Real{ 10 } *max;
			const auto t = Real{ 3 } / Real{ 4 };
			const auto c = vd::lerp(a, b, t);
			//std::cout << "c = " << c / max << '\n';
			//std::cout << "c == b/2: " << std::boolalpha << (c == Real{ 8.75 } *max) << '\n';
			return c == Real{ 8.75 } *max;
		}
		template<typename Int>
		static bool test_saturation_add() {
			Int max = vd::numeric_limits<Int>::max();
			Int a = static_cast<Int>(max - 1);
			Int b = 2;
			Int res = vd::sat_add(a, b);
			Int res2 = vd::sat_add(a, a);
			return  res == max &&  res2 == max;
		}
		template<typename Int>
		static bool test_saturation_sub() {
			Int min = 0;
			Int max = vd::numeric_limits<Int>::max();
			Int a =  static_cast<Int>(max - 1);
			Int b = 2;
			Int res = vd::sat_sub(a, max);
			Int res2 = vd::sat_sub(b, max);
			return  res == min && res2 == min;
		}

	public:

		static void setup() {}
		static void tearDown() {}
		static void Math_Lerp() {
			TEST_ASSERT(test<float>());
			TEST_ASSERT(test<double>());
			TEST_ASSERT(test<long double>());
			TEST_ASSERT(test_nan<float>());
			TEST_ASSERT(test_nan<double>());
			TEST_ASSERT(test_nan<long double>());
			TEST_ASSERT(test_ends<float>());
			TEST_ASSERT(test_ends<double>());
			TEST_ASSERT(test_ends<long double>());
			TEST_ASSERT(test_inf<float>());
			TEST_ASSERT(test_inf<double>());
			TEST_ASSERT(test_inf<long double>());
			//TEST_ASSERT(test_subnorm<float>());
			TEST_ASSERT(test_huge<float>());
			TEST_ASSERT(test_huge<double>());
			TEST_ASSERT(test_huge<long double>());
		}
		static void saturation_add() {
			TEST_ASSERT(test_saturation_add<uint8_t>());
			TEST_ASSERT(test_saturation_add<uint16_t>());
			TEST_ASSERT(test_saturation_add<uint32_t>());
		}
		static void saturation_sub() {
			TEST_ASSERT(test_saturation_sub<uint8_t>());
			TEST_ASSERT(test_saturation_sub<uint16_t>());
			TEST_ASSERT(test_saturation_sub<uint32_t>());
		}

		static void run() {
			RUN_TEST_CASE_CLASS(VoidTest_Math, Math_Lerp);
			RUN_TEST_CASE_CLASS(VoidTest_Math, saturation_add);
			RUN_TEST_CASE_CLASS(VoidTest_Math, saturation_sub);
		}
};