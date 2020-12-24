#include "dateutils_test.h"
#include "test_harness/test_harness.h"


void _DateTime_Test_DaysBetween()
{


	TTimeStruct time1 = {2000,2,28,03,15,20,10};
	TTimeStruct time2 = {2000,3,1,03,15,20,10};
	TTimeStruct time3 = {2001,2,28,03,15,20,10};
	TTimeStruct time4 = {2001,3,1,03,15,20,10};
	TTimeStruct time5 = {2000,4,10,03,15,20,10};
	TTimeStruct time6 = {2000,5,1,03,15,20,10};
	TTimeStruct time7 = {2000,3,1,03,15,20,10};
	TTimeStruct time8 = {2001,3,1,03,15,20,10};
	TTimeStruct time9 = {1999,3,1,03,15,20,10};
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time1,&time2),2,"Febriary in leap_year");
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time3,&time4),1,"Febriary in not leap year");
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time5,&time6),21,"month");
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time6,&time7),-61,"month back");
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time7,&time8),365,"not leap year");
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time8,&time7),-365,"not leap year back");
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time9,&time7),366,"leap year");

	TTimeStruct time01 = {2001,3,1,03,15,20,10};
	TTimeStruct time02 = {2003,3,1,03,15,20,10};
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time01,&time02),365+365,"two years(not leap),same_month");

	TTimeStruct time001 = {2000,3,1,03,15,20,10};
	TTimeStruct time002 = {2002,3,1,03,15,20,10};
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time001,&time002),365+365,"two years(first leap),same_month");



	TTimeStruct time0001 = {1998,3,1,03,15,20,10};
	TTimeStruct time0002 = {2000,3,1,03,15,20,10};
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time0001,&time0002),365+366,"two years(last leap),same_month");

	TTimeStruct time00001 = {1999,3,1,03,15,20,10};
	TTimeStruct time00002 = {2001,3,1,03,15,20,10};
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time00001,&time00002),366+365,"two years(middle leap),same_month");

	TTimeStruct time000001 = {1999,3,1,03,15,20,10};
	TTimeStruct time000002 = {2001,2,1,03,15,20,10};
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time000001,&time000002),366+365-28,"two years(middle leap but without FEBRIARY),same_month");


	TTimeStruct time03 = {2000,3,1,03,15,20,10};
	TTimeStruct time04 = {2002,4,1,03,15,20,10};
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time03,&time04),365+365+31,"two years,+1 month");

	TTimeStruct time05 = {2000,3,1,03,15,20,10};
	TTimeStruct time06 = {2002,2,27,03,15,20,10};
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time05,&time06),365+365-2,"two years,-1month(-2 days)");

	TTimeStruct time07 = {2000,3,1,03,15,20,10};
	TTimeStruct time08 = {2002,2,27,03,15,20,10};
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time07,&time08),365+365-2,"1 year,other_month,-2 days");



	TTimeStruct time09 = { 2015, 5, 4, 15, 14, 44, 44 };
	TTimeStruct time010 = { 2015, 5, 5, 15, 14, 45, 45 };
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time09, &time010), 1, "1 day middle month");
	TTimeStruct time011 = { 2015, 5, 31, 15, 14, 44, 44 };
	TTimeStruct time012 = { 2015, 6, 1, 15, 14, 45, 45 };
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time011, &time012), 1, "1 day on edge months");

}

void _DateTime_Test_MonthsBetween()
{


	TTimeStruct time1 = { 2000, 2, 28, 03, 15, 20, 10 };
	TTimeStruct time2 = { 2000, 3, 1, 03, 15, 20, 10 };
	TTimeStruct time5 = { 2000, 4, 10, 03, 15, 20, 10 };
	TTimeStruct time6 = { 2000, 5, 1, 03, 15, 20, 10 };
	TTimeStruct time7 = { 2000, 3, 1, 03, 15, 20, 10 };
	TTimeStruct time8 = { 2001, 3, 1, 03, 15, 20, 10 };
	TTimeStruct time9 = { 1999, 3, 1, 03, 15, 20, 10 };
	TEST_ASSERT_EQUAL_16(DateTime_MonthsBetween(&time1, &time2), 1, "Febriary in leap_year");
	TEST_ASSERT_EQUAL_16(DateTime_MonthsBetween(&time1, &time1), 0, "same month\n");
	TEST_ASSERT_EQUAL_16(DateTime_MonthsBetween(&time5, &time6), 1, "month");
	TEST_ASSERT_EQUAL_16(DateTime_MonthsBetween(&time6, &time7), -2, "month back");
	TEST_ASSERT_EQUAL_16(DateTime_MonthsBetween(&time7, &time8), 12, "not leap year");
	TEST_ASSERT_EQUAL_16(DateTime_MonthsBetween(&time8, &time7), -12, "not leap year back");

	TTimeStruct time01 = { 2001, 3, 1, 03, 15, 20, 10 };
	TTimeStruct time02 = { 2003, 3, 1, 03, 15, 20, 10 };
	TEST_ASSERT_EQUAL_16(DateTime_MonthsBetween(&time01, &time02), 24, "two years(not leap),same_month");
	TEST_ASSERT_EQUAL_16(DateTime_MonthsBetween(&time02, &time01), -24, "two years(not leap),same_month back");


	TTimeStruct time000001 = { 1999, 3, 1, 03, 15, 20, 10 };
	TTimeStruct time000002 = { 2001, 2, 1, 03, 15, 20, 10 };
	TEST_ASSERT_EQUAL_16(DateTime_MonthsBetween(&time000001, &time000002), 12+11, "two years -1 month");


	TTimeStruct time03 = { 2000, 3, 1, 03, 15, 20, 10 };
	TTimeStruct time04 = { 2002, 4, 1, 03, 15, 20, 10 };
	TEST_ASSERT_EQUAL_16(DateTime_MonthsBetween(&time03, &time04), 12 + 12 + 1, "two years,+1 month");


}


void _DateTime_Test_Hours()
{


	TTimeStruct time1 = { 2000, 2, 28, 03, 15, 20, 10 };
	TTimeStruct time2 = { 2000, 2, 28, 04, 15, 20, 10 };
	TTimeStruct time5 = { 2000, 4, 10, 03, 59, 20, 10 };
	TTimeStruct time6 = { 2000, 4, 10, 04, 0, 20, 10 };
	TTimeStruct time7 = { 2000, 3, 1, 03, 15, 20, 10 };
	TTimeStruct time8 = { 2000, 3, 1, 06, 15, 20, 10 };
	TTimeStruct time9 = { 1999, 3, 1, 03, 15, 20, 10 };
	TTimeStruct time10 = { 1999, 3, 2, 02, 15, 20, 10 };
	TTimeStruct time11 = { 1999, 3, 3, 02, 15, 20, 10 };
	TTimeStruct time0 = { 2015, 05, 02, 15, 33, 20, 10 };
	TTimeStruct time01 = { 2015, 05, 02, 15, 44, 20, 10 };

	TEST_ASSERT_EQUAL_16(DateTime_HoursBetween(&time0, &time01), 0, "no1");

	TEST_ASSERT_EQUAL_16(DateTime_HoursBetween(&time1, &time1), 0, "no");
	TEST_ASSERT_EQUAL_16(DateTime_HoursBetween(&time1, &time2), 1, "1 hour");
	TEST_ASSERT_EQUAL_16(DateTime_HoursBetween(&time2, &time1), -1, "hour back");
	TEST_ASSERT_EQUAL_16(DateTime_HoursBetween(&time5, &time6), 1, "1 minute");
	TEST_ASSERT_EQUAL_16(DateTime_HoursBetween(&time7, &time8), 3, "3 hours");
	TEST_ASSERT_EQUAL_16(DateTime_HoursBetween(&time9, &time10), 23, "1 day,23");
	TEST_ASSERT_EQUAL_16(DateTime_HoursBetween(&time10, &time9), -23, "1 day back,23");
	TEST_ASSERT_EQUAL_16(DateTime_HoursBetween(&time10, &time11), 24, "1 day full");


}

