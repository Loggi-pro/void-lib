#pragma once
#include <unity/unity_fixture_classes.h>
#include <loggi/interp.h>
//#include <iostream>
class VoidTest_Bezier : UnityTestClass<VoidTest_Bezier> {
	public:
		static void setup() {}
		static void tearDown() {}

		static void calcBezier() {
			using namespace loggi;
			using namespace vd;
			using Type = double;
			Point2D<Type> testValues[] = {
				{0, 0   },
				{20, 0  },
				{45, -47},
				{53, 335},
				{57, 26 },
				{62, 387},
				{74, 104},
				{89, 0  },
				{95, 100},
				{100, 0 },
			};
			//result values for Between Points = 2
			Point2D<Type> resultValues[] = {
				{0, 0},
				{10, 0},
				{20, 0},
				{32.5, -27.4332},
				{45, -47},
				{49, 144.363},
				{53, 335},
				{55, 180.497},
				{57, 26},
				{59.5, 206.486},
				{62, 387},
				{68, 269.705},
				{74, 104},
				{84.3125, 21.7833},
				{89, 0},
				{92, 50.0525},
				{95, 100},
				{98.4383, 49.9953},
				{100, 0}
			};
			Segment<Type> spline[COUNT_OF(testValues) - 1];
			gsl::span<Segment<Type>> result(spline);
			calculateSpline<Type>(gsl::span<Point2D<Type>>(testValues), result);
			const int BETWEEN_POINTS = 2;
			int index = 0;

			for (auto s : spline) {
				for (int i = 0; i < BETWEEN_POINTS; ++i) {
					float x = (float)i / BETWEEN_POINTS;
					Point2D<Type> p = s.calc(x);
					//std::cout << p.x << " " << p.y << std::endl;
					TEST_ASSERT_EQUAL_FLOAT(resultValues[index].x, p.x);
					TEST_ASSERT_EQUAL_FLOAT(resultValues[index].y, p.y);
					index++;
				}
			}

			//last point
			Point2D<Type> p = spline[COUNT_OF(spline) - 1].calc(1);
			//std::cout << p.x << " " << p.y << std::endl;
			TEST_ASSERT_EQUAL_FLOAT(resultValues[index].x, p.x);
			TEST_ASSERT_EQUAL_FLOAT(resultValues[index].y, p.y);
		}

		static void run() {
			RUN_TEST_CASE_CLASS(VoidTest_Bezier, calcBezier);
		}
};