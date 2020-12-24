#define UNITY_EXCLUDE_STDINT_H
#define UNITY_EXCLUDE_STDLIB_MALLOC
#define UNITY_EXCLUDE_FLOAT
#include <unity\unity_fixture.h>
#include <_cph_todo\time\dateutils.h>

//_GROUP_NAME

TEST_GROUP(DATEUTILS_TEST);

TEST_SETUP(DATEUTILS_TEST) {
}


TEST_TEAR_DOWN(DATEUTILS_TEST) {
}
TEST(DATEUTILS_TEST, DateTimeUtils) {
	TEST_ASSERT_EQUAL(12, TDateTimeUtils::Month_Previous(1));
	TEST_ASSERT_EQUAL(1, TDateTimeUtils::Month_Next(12));
	TEST_ASSERT_EQUAL(2, TDateTimeUtils::Month_Next(1));
	TEST_ASSERT_EQUAL(true, TDateTimeUtils::IsLeap(2000));
	TEST_ASSERT_EQUAL(false, TDateTimeUtils::IsLeap(2001));
	TEST_ASSERT_EQUAL(29, TDateTimeUtils::DaysInMonth(02, true));
	TEST_ASSERT_EQUAL(28, TDateTimeUtils::DaysInMonth(02, false));
	TEST_ASSERT_EQUAL(31, TDateTimeUtils::DaysInMonth(01, false));
}
TEST(DATEUTILS_TEST, Date_DefaultConstructor) {
	TDate date;
	TEST_ASSERT_EQUAL(0, date.Year);
	TEST_ASSERT_EQUAL(0, date.Month);
	TEST_ASSERT_EQUAL(0, date.Day);
}
TEST(DATEUTILS_TEST, Date_Constructor) {
	TDate date(2014, 12, 31);
	TEST_ASSERT_EQUAL(2014, date.Year);
	TEST_ASSERT_EQUAL(12, date.Month);
	TEST_ASSERT_EQUAL(31, date.Day);
}
TEST(DATEUTILS_TEST, Date_ConstructorFromDate) {
	TDate date(2014, 12, 31);
	TDate date2(date);
	TEST_ASSERT_EQUAL(2014, date2.Year);
	TEST_ASSERT_EQUAL(12, date2.Month);
	TEST_ASSERT_EQUAL(31, date2.Day);
}

TEST(DATEUTILS_TEST, Date_Set) {
	TDate date;
	date.Set(2014, 12, 31);
	TEST_ASSERT_EQUAL(2014, date.Year);
	TEST_ASSERT_EQUAL(12, date.Month);
	TEST_ASSERT_EQUAL(31, date.Day);
}


TEST(DATEUTILS_TEST, Date_Clear) {
	TDate date(2014, 12, 31);
	date.Clear();
	TEST_ASSERT_EQUAL(0, date.Year);
	TEST_ASSERT_EQUAL(0, date.Month);
	TEST_ASSERT_EQUAL(0, date.Day);
}
TEST(DATEUTILS_TEST, Date_CopyFrom) {
	TDate date(2014, 12, 31);
	TDate date2;
	date2.CopyFrom(date);
	TEST_ASSERT_EQUAL(2014, date2.Year);
	TEST_ASSERT_EQUAL(12, date2.Month);
	TEST_ASSERT_EQUAL(31, date2.Day);
}
TEST(DATEUTILS_TEST, Date_CopyTo) {
	TDate date(2014, 12, 31);
	TDate date2;
	date.CopyTo(&date2);
	TEST_ASSERT_EQUAL(2014, date2.Year);
	TEST_ASSERT_EQUAL(12, date2.Month);
	TEST_ASSERT_EQUAL(31, date2.Day);
}
IGNORE_TEST(DATEUTILS_TEST, Date_ToString) {
	TDate date(2014, 12, 31);
	char string[10];
	date.ToString(string);
	TEST_ASSERT_EQUAL('\0', string[date.StringLen()]);

	for (u08 i = 0; i < date.StringLen(); i++) {
		TEST_ASSERT_INT8_WITHIN(64, 64, string[i]);
	}
}
TEST(DATEUTILS_TEST, Date_Comparison) {
	TDate date(2014, 12, 30);
	TDate date_same(2014, 12, 30);
	TDate date_lowyear(2013, 12, 30);
	TDate date_lowmonth(2014, 11, 30);
	TDate date_lowday(2014, 11, 29);
	TEST_ASSERT_EQUAL(DATETIME_EQUAL, TDate::Compare(date, date_same));
	TEST_ASSERT_EQUAL(DATETIME_FIRST_GREATER, TDate::Compare(date, date_lowyear));
	TEST_ASSERT_EQUAL(DATETIME_SECOND_GREATER, TDate::Compare(date_lowyear, date));
	TEST_ASSERT_EQUAL(DATETIME_FIRST_GREATER, TDate::Compare(date, date_lowmonth));
	TEST_ASSERT_EQUAL(DATETIME_FIRST_GREATER, TDate::Compare(date, date_lowday));
}

TEST(DATEUTILS_TEST, Date_ComparisonIsEqual) {
	TDate date(2014, 12, 30);
	TDate date_same(2014, 12, 30);
	TDate date_notsame(2014, 11, 30);
	TEST_ASSERT_EQUAL(true, date.IsEqual(date_same));
	TEST_ASSERT_EQUAL(false, date.IsEqual(date_notsame));
}
TEST(DATEUTILS_TEST, Date_ComparisonIsSameMonth) {
	TDate date(2014, 12, 30);
	TDate date_same_other_year(2015, 12, 30);
	TDate date_same_other_day(2014, 12, 5);
	TDate date_same(date);
	TDate date_notsame(2015, 1, 5);
	TEST_ASSERT_EQUAL(false, date.IsSameMonth(date_same_other_year));
	TEST_ASSERT_EQUAL(true, date.IsSameMonth(date_same_other_day));
	TEST_ASSERT_EQUAL(true, date.IsSameMonth(date_same));
	TEST_ASSERT_EQUAL(false, date.IsSameMonth(date_notsame));
}
TEST(DATEUTILS_TEST, Date_ComparisonIsSameDay) {
	TDate date(2014, 12, 30);
	TDate date_same_other_year(2015, 12, 30);
	TDate date_same_other_month(2014, 11, 30);
	TDate date_same(2014, 12, 30);
	TDate date_notsame(2000, 1, 5);
	TEST_ASSERT_EQUAL(false, date.IsSameDay(date_same_other_year));
	TEST_ASSERT_EQUAL(false, date.IsSameDay(date_same_other_month));
	TEST_ASSERT_EQUAL(true, date.IsSameDay(date_same));
	TEST_ASSERT_EQUAL(false, date.IsSameDay(date_notsame));
}
TEST(DATEUTILS_TEST, Date_ComparisonIsNextMonthThan) {
	TDate date(2014, 12, 30);
	TDate date_same(2015, 1, 31);
	TDate date_same2(2015, 2, 1);
	TDate date_notsame(2000, 1, 5);
	TDate date_other(2015, 12, 30);
	TDate date28(2015, 02, 28);
	TDate date29(2015, 03, 1);
	TEST_ASSERT_EQUAL(true, date_same.IsNextMonthThan(date));
	TEST_ASSERT_EQUAL(true, date_same2.IsNextMonthThan(date_same));
	TEST_ASSERT_EQUAL(false, date_same.IsNextMonthThan(date_other));
	TEST_ASSERT_EQUAL(false, date.IsNextMonthThan(date_notsame));
	TEST_ASSERT_EQUAL(true, date29.IsNextMonthThan(date28));
}
TEST(DATEUTILS_TEST, Date_ComparisonIsPrevMonthThan) {
	TDate date(2014, 12, 30);
	TDate date_same(2015, 1, 31);
	TDate date_same2(2015, 2, 1);
	TDate date_notsame(2000, 1, 5);
	TDate date_other(2015, 12, 30);
	TDate date28(2015, 02, 28);
	TDate date29(2015, 03, 1);
	TEST_ASSERT_EQUAL(true, date.IsPrevMonthThan(date_same));
	TEST_ASSERT_EQUAL(true, date_same.IsPrevMonthThan(date_same2));
	TEST_ASSERT_EQUAL(false, date_other.IsPrevMonthThan(date_same));
	TEST_ASSERT_EQUAL(false, date_notsame.IsPrevMonthThan(date));
	TEST_ASSERT_EQUAL(true, date28.IsPrevMonthThan(date29));
}
TEST(DATEUTILS_TEST, Date_ComparisonIsPrevDayThan) {
	TDate date(2015, 12, 31);
	TDate date_same(2015, 12, 30);
	TDate date_same2(2016, 1, 1);
	TDate date_notsame(2000, 1, 5);
	TDate date28(2015, 02, 28);
	TDate date28_2(2015, 03, 1);
	TDate date29(2016, 02, 28);
	TDate date29_2(2016, 02, 29);
	TDate date29_3(2016, 03, 1);
	TEST_ASSERT_EQUAL(true, date_same.IsPrevDayThan(date));//BEFORE NY
	TEST_ASSERT_EQUAL(true, date.IsPrevDayThan(date_same2)); //NY
	TEST_ASSERT_EQUAL(false, date_same2.IsPrevDayThan(date_same)); //wrong
	TEST_ASSERT_EQUAL(true, date28.IsPrevDayThan(date28_2));//28.02 not leap
	TEST_ASSERT_EQUAL(true, date29.IsPrevDayThan(date29_2));//28.02 leap
	TEST_ASSERT_EQUAL(true, date29_2.IsPrevDayThan(date29_3));//29.02 leap
	TEST_ASSERT_EQUAL(false, date29.IsPrevDayThan(date29_3));//28.02->01.03 leap
}
TEST(DATEUTILS_TEST, Date_ComparisonIsNextDayThan) {
	TDate date(2015, 12, 31);
	TDate date_same(2015, 12, 30);
	TDate date_same2(2016, 1, 1);
	TDate date_notsame(2000, 1, 5);
	TDate date28(2015, 02, 28);
	TDate date28_2(2015, 03, 1);
	TDate date29(2016, 02, 28);
	TDate date29_2(2016, 02, 29);
	TDate date29_3(2016, 03, 1);
	TEST_ASSERT_EQUAL(true, date.IsNextDayThan(date_same));//BEFORE NY
	TEST_ASSERT_EQUAL(true, date_same2.IsNextDayThan(date)); //NY
	TEST_ASSERT_EQUAL(false, date_same.IsNextDayThan(date_same2)); //wrong
	TEST_ASSERT_EQUAL(true, date28_2.IsNextDayThan(date28));//28.02 not leap
	TEST_ASSERT_EQUAL(true, date29_2.IsNextDayThan(date29));//28.02 leap
	TEST_ASSERT_EQUAL(true, date29_3.IsNextDayThan(date29_2));//29.02 leap
	TEST_ASSERT_EQUAL(false, date29_3.IsNextDayThan(date29));//28.02->01.03 leap
}
TEST(DATEUTILS_TEST, Date_ComparisonIsSameYear) {
	TDate date(2015, 12, 31);
	TDate date_same(2015, 12, 30);
	TDate date_notsame(2016, 1, 1);
	TDate date_other(2000, 1, 5);
	TEST_ASSERT_EQUAL(true, date.IsSameYear(date_same));
	TEST_ASSERT_EQUAL(false, date.IsSameYear(date_notsame));
	TEST_ASSERT_EQUAL(false, date.IsSameYear(date_other));
}

TEST(DATEUTILS_TEST, Date_ComparisonEquations) {
	TDate date(2015, 12, 30);
	TDate date2(2015, 12, 31);
	TDate date3(2016, 1, 1);
	TDate date4(2015, 12, 30);
	TEST_ASSERT_EQUAL(true, date3 > date2);
	TEST_ASSERT_EQUAL(true, date2 > date);
	TEST_ASSERT_EQUAL(false, date > date3);
	TEST_ASSERT_EQUAL(true, date4 >= date);
	TEST_ASSERT_EQUAL(true, date3 >= date2);
	TEST_ASSERT_EQUAL(false, date >= date3);
	TEST_ASSERT_EQUAL(true, date2 < date3);
	TEST_ASSERT_EQUAL(true, date < date2);
	TEST_ASSERT_EQUAL(false, date3 < date);
	TEST_ASSERT_EQUAL(true, date <= date4);
	TEST_ASSERT_EQUAL(true, date2 <= date3);
	TEST_ASSERT_EQUAL(false, date3 <= date);
}
TEST(DATEUTILS_TEST, Date_IncDec) {
	TDate date(2015, 12, 30);
	date.IncDay();
	TEST_ASSERT_EQUAL(2015, date.Year); TEST_ASSERT_EQUAL(12, date.Month);
	TEST_ASSERT_EQUAL(31, date.Day);
	date.IncDay();
	TEST_ASSERT_EQUAL(2016, date.Year); TEST_ASSERT_EQUAL(01, date.Month);
	TEST_ASSERT_EQUAL(1, date.Day);
	date.DecDay();
	TEST_ASSERT_EQUAL(2015, date.Year); TEST_ASSERT_EQUAL(12, date.Month);
	TEST_ASSERT_EQUAL(31, date.Day);
	date.DecDay();
	TEST_ASSERT_EQUAL(2015, date.Year); TEST_ASSERT_EQUAL(12, date.Month);
	TEST_ASSERT_EQUAL(30, date.Day);
	date.Year = 2015;
	date.Month = 12;
	date.Day = 30;
	date.IncMonth();
	TEST_ASSERT_EQUAL(2016, date.Year); TEST_ASSERT_EQUAL(1, date.Month);
	TEST_ASSERT_EQUAL(30, date.Day);
	date.IncMonth();
	TEST_ASSERT_EQUAL(2016, date.Year); TEST_ASSERT_EQUAL(2, date.Month);
	TEST_ASSERT_EQUAL(29, date.Day);//day reduction
	date.DecMonth();
	TEST_ASSERT_EQUAL(2016, date.Year); TEST_ASSERT_EQUAL(1, date.Month);
	TEST_ASSERT_EQUAL(29, date.Day);
	date.DecMonth();
	TEST_ASSERT_EQUAL(2015, date.Year); TEST_ASSERT_EQUAL(12, date.Month);
	TEST_ASSERT_EQUAL(29, date.Day);
	date.Year = 2015; date.Month = 12; date.Day = 30;
	date.IncYear();
	TEST_ASSERT_EQUAL(2016, date.Year); TEST_ASSERT_EQUAL(12, date.Month);
	TEST_ASSERT_EQUAL(30, date.Day);
	date.Year = 2016; date.Month = 02; date.Day = 29;
	date.IncYear();
	TEST_ASSERT_EQUAL(2017, date.Year); TEST_ASSERT_EQUAL(02, date.Month);
	TEST_ASSERT_EQUAL(28, date.Day); //day reduction
	date.DecYear();
	TEST_ASSERT_EQUAL(2016, date.Year); TEST_ASSERT_EQUAL(02, date.Month);
	TEST_ASSERT_EQUAL(28, date.Day);
}

TEST(DATEUTILS_TEST, Date_DecDay_BetweenMonthWithDiffMaxDays) {
	TDate date(2016, 06, 1);
	date.DecDay();
	TEST_ASSERT_EQUAL(2016, date.Year); TEST_ASSERT_EQUAL(05, date.Month);
	TEST_ASSERT_EQUAL(31, date.Day);
}


TEST(DATEUTILS_TEST, Date_DecYear_BetweenYearWithLeapDay) {
	TDate date(2016, 02, 29);
	date.DecYear();
	TEST_ASSERT_EQUAL(2015, date.Year);
	TEST_ASSERT_EQUAL(02, date.Month);
	TEST_ASSERT_EQUAL(28, date.Day);
}
TEST(DATEUTILS_TEST, Date_IncYear_BetweenYearWithLeapDay) {
	TDate date(2016, 02, 29);
	date.DecYear();
	TEST_ASSERT_EQUAL(2017, date.Year);
	TEST_ASSERT_EQUAL(02, date.Month);
	TEST_ASSERT_EQUAL(28, date.Day);
}


TEST(DATEUTILS_TEST, Date_MonthBetween) {
	TDate time1(2000, 2, 28);
	TDate time2(2000, 3, 1);
	TDate time5(2000, 4, 10);
	TDate time6(2000, 5, 1);
	TDate time7(2000, 3, 1);
	TDate time8(2001, 3, 1);
	TDate time9(1999, 3, 1);
	TEST_ASSERT_EQUAL(1, time1.MonthBetween(time2)); //, 1, "Febriary in leap_year");
	TEST_ASSERT_EQUAL(0, time1.MonthBetween(time1));//, 0, "same month\n");
	TEST_ASSERT_EQUAL(1, time5.MonthBetween(time6));//, 1, "month");
	TEST_ASSERT_EQUAL(2, time6.MonthBetween(time7));//, -2, "month back");
	TEST_ASSERT_EQUAL(12, time7.MonthBetween(time8)); //, 12, "not leap year");
	TEST_ASSERT_EQUAL(12, time8.MonthBetween(time7)); //, -12, "not leap year back");
	TDate time01 (2001, 3, 1);
	TDate time02 (2003, 3, 1);
	TEST_ASSERT_EQUAL(24, time01.MonthBetween(time02));// , 24, "two years(not leap),same_month");
	TEST_ASSERT_EQUAL(24, time02.MonthBetween(time01));// , -24, "two years(not leap),same_month back");
	TDate time000001(1999, 3, 1);
	TDate time000002(2001, 2, 1);
	TEST_ASSERT_EQUAL(12 + 11, time000001.MonthBetween(time000002));// , 12 + 11, "two years -1 month");
	TDate time03(2000, 3, 1);
	TDate time04(2002, 4, 1);
	TEST_ASSERT_EQUAL(12 + 12 + 1,
	                  time03.MonthBetween(time04)); // , 12 + 12 + 1, "two years,+1 month");
}

TEST(DATEUTILS_TEST, Date_DaysBetween) {
	TDate time1(2000, 2, 28);
	TDate time2(2000, 3, 1);
	TDate time3(2001, 2, 28);
	TDate time4(2001, 3, 1);
	TDate time5(2000, 4, 10);
	TDate time6(2000, 5, 1);
	TDate time7(2000, 3, 1);
	TDate time8(2001, 3, 1);
	TDate time9(1999, 3, 1);
	TEST_ASSERT_EQUAL(2, time1.DaysBetween(time2)); //, 2, "Febriary in leap_year");
	TEST_ASSERT_EQUAL(1, time3.DaysBetween(time4)); //, 1, "Febriary in not leap year");
	TEST_ASSERT_EQUAL(21, time5.DaysBetween(time6)); //, 21, "month");
	TEST_ASSERT_EQUAL(61, time6.DaysBetween(time7)); //, -61, "month back");
	TEST_ASSERT_EQUAL(365, time7.DaysBetween(time8)); //, 365, "not leap year");
	TEST_ASSERT_EQUAL(365, time8.DaysBetween(time7)); //, -365, "not leap year back");
	TEST_ASSERT_EQUAL(366, time9.DaysBetween(time7)); //, 366, "leap year");
	TDate time01(2001, 3, 1);
	TDate time02(2003, 3, 1);
	TEST_ASSERT_EQUAL(365 + 365, time01.DaysBetween(
	                      time02)); // , 365 + 365, "two years(not leap),same_month");
	TDate time001(2000, 3, 1);
	TDate time002(2002, 3, 1);
	TEST_ASSERT_EQUAL(365 + 365, time001.DaysBetween(
	                      time002)); // , 365 + 365, "two years(first leap),same_month");
	TDate time0001(1998, 3, 1);
	TDate time0002(2000, 3, 1);
	TEST_ASSERT_EQUAL(365 + 366, time0001.DaysBetween(
	                      time0002)); // , 365 + 366, "two years(last leap),same_month");
	TDate time00001(1999, 3, 1);
	TDate time00002(2001, 3, 1);
	TEST_ASSERT_EQUAL(366 + 365, time00001.DaysBetween(
	                      time00002)); // , 366 + 365, "two years(middle leap),same_month");
	TDate time000001(1999, 3, 1);
	TDate time000002(2001, 2, 1);
	TEST_ASSERT_EQUAL(366 + 365 - 28,
	                  time000001.DaysBetween(
	                      time000002)); // , 366 + 365 - 28, "two years(middle leap but without FEBRIARY),same_month");
	TDate time03(2000, 3, 1);
	TDate time04(2002, 4, 1);
	TEST_ASSERT_EQUAL(365 + 365 + 31,
	                  time03.DaysBetween(time04)); // , 365 + 365 + 31, "two years,+1 month");
	TDate time05(2000, 3, 1);
	TDate time06(2002, 2, 27);
	TEST_ASSERT_EQUAL(365 + 365 - 2,
	                  time05.DaysBetween(time06)); // , 365 + 365 - 2, "two years,-1month(-2 days)");
	TDate time07(2000, 3, 1);
	TDate time08(2002, 2, 27);
	TEST_ASSERT_EQUAL(365 + 365 - 2,
	                  time07.DaysBetween(time08)); // , 365 + 365 - 2, "1 year,other_month,-2 days");
	TDate time09(2015, 5,  4);
	TDate time010(2015, 5, 5);
	TEST_ASSERT_EQUAL(1, time09.DaysBetween(time010));// , 1, "1 day middle month");
	TDate time011(2015, 5, 31);
	TDate time012(2015, 6,  1);
	TEST_ASSERT_EQUAL(1, time011.DaysBetween(time012)); // , 1, "1 day on edge months");
}


TEST(DATEUTILS_TEST, Date_CalendarYearsBetweenn) {
	TDate date(2015, 12, 30);
	TDate date2(2016, 1, 1);
	TDate date3(2018, 12, 30);
	TEST_ASSERT_EQUAL(1, date.CalendarYearsBetween(date2));
	TEST_ASSERT_EQUAL(2, date2.CalendarYearsBetween(date3));
}
TEST(DATEUTILS_TEST, Date_CheckIsValid) {
	TDate date(2015, 12, 30);
	TDate date2(0, 0, 0);
	TDate date3(2000, 13, 1);
	TDate date4(2000, 12, 32);
	TDate date5(2000, 11, 31);
	TDate date6(2000, 2, 30);
	TDate date7(2001, 2, 29);
	TDate date8(2001, 0, 5);
	TEST_ASSERT_EQUAL(true, date.IsDateValid());
	TEST_ASSERT_EQUAL(false, date2.IsDateValid());
	TEST_ASSERT_EQUAL(false, date2.IsDateValid());
	TEST_ASSERT_EQUAL(false, date3.IsDateValid());
	TEST_ASSERT_EQUAL(false, date4.IsDateValid());
	TEST_ASSERT_EQUAL(false, date5.IsDateValid());
	TEST_ASSERT_EQUAL(false, date6.IsDateValid());
	TEST_ASSERT_EQUAL(false, date7.IsDateValid());
	TEST_ASSERT_EQUAL(false, date8.IsDateValid());
}
TEST(DATEUTILS_TEST, Date_ChangeDigits) {
	TDate date(2015, 12, 31);
	date.ChangeYearDigit(-1);
	TEST_ASSERT_EQUAL(2014, date.Year); TEST_ASSERT_EQUAL(12, date.Month);
	TEST_ASSERT_EQUAL(31, date.Day);
	date.ChangeYearDigit(-10);
	TEST_ASSERT_EQUAL(2004, date.Year); TEST_ASSERT_EQUAL(12, date.Month);
	TEST_ASSERT_EQUAL(31, date.Day);
	date.ChangeYearDigit(+50);
	TEST_ASSERT_EQUAL(2054, date.Year); TEST_ASSERT_EQUAL(12, date.Month);
	TEST_ASSERT_EQUAL(31, date.Day);
	date.ChangeYearDigit(0);
	TEST_ASSERT_EQUAL(2054, date.Year); TEST_ASSERT_EQUAL(12, date.Month);
	TEST_ASSERT_EQUAL(31, date.Day);
	date.ChangeMonthDigit(-1);
	TEST_ASSERT_EQUAL(2054, date.Year); TEST_ASSERT_EQUAL(11, date.Month);
	TEST_ASSERT_EQUAL(30, date.Day);//day reduction
	date.ChangeMonthDigit(-10);
	TEST_ASSERT_EQUAL(2054, date.Year); TEST_ASSERT_EQUAL(1, date.Month);
	TEST_ASSERT_EQUAL(30, date.Day);
	date.ChangeMonthDigit(10);
	TEST_ASSERT_EQUAL(2054, date.Year); TEST_ASSERT_EQUAL(11, date.Month);
	TEST_ASSERT_EQUAL(30, date.Day);
	date.ChangeMonthDigit(1);
	TEST_ASSERT_EQUAL(2054, date.Year); TEST_ASSERT_EQUAL(12, date.Month);
	TEST_ASSERT_EQUAL(30, date.Day);
	date.ChangeMonthDigit(30);
	TEST_ASSERT_EQUAL(2054, date.Year); TEST_ASSERT_EQUAL(1, date.Month);
	TEST_ASSERT_EQUAL(30, date.Day);
	date.ChangeDayDigit(-1);
	TEST_ASSERT_EQUAL(2054, date.Year); TEST_ASSERT_EQUAL(1, date.Month);
	TEST_ASSERT_EQUAL(29, date.Day);
	date.ChangeDayDigit(-30);
	TEST_ASSERT_EQUAL(2054, date.Year); TEST_ASSERT_EQUAL(1, date.Month);
	TEST_ASSERT_EQUAL(31, date.Day);//overflow
	date.ChangeDayDigit(10);
	TEST_ASSERT_EQUAL(2054, date.Year); TEST_ASSERT_EQUAL(1, date.Month);
	TEST_ASSERT_EQUAL(1, date.Day);//overflow
	date.ChangeDayDigit(30);
	TEST_ASSERT_EQUAL(2054, date.Year); TEST_ASSERT_EQUAL(1, date.Month);
	TEST_ASSERT_EQUAL(31, date.Day);
}


TEST(DATEUTILS_TEST, Time_DefaultConstructor) {
	TTime time;
	TEST_ASSERT_EQUAL(0, time.Hour);
	TEST_ASSERT_EQUAL(0, time.Minute);
	TEST_ASSERT_EQUAL(0, time.Second);
}
TEST(DATEUTILS_TEST, Time_Constructor) {
	TTime time(20, 59, 59);
	TEST_ASSERT_EQUAL(20, time.Hour);
	TEST_ASSERT_EQUAL(59, time.Minute);
	TEST_ASSERT_EQUAL(59, time.Second);
}
TEST(DATEUTILS_TEST, Time_ConstructorFromtime) {
	TTime time(20, 59, 59);
	TTime time2(time);
	TEST_ASSERT_EQUAL(20, time2.Hour);
	TEST_ASSERT_EQUAL(59, time2.Minute);
	TEST_ASSERT_EQUAL(59, time2.Second);
}
TEST(DATEUTILS_TEST, Time_Clear) {
	TTime time(20, 59, 59);
	time.Clear();
	TEST_ASSERT_EQUAL(0, time.Hour);
	TEST_ASSERT_EQUAL(0, time.Minute);
	TEST_ASSERT_EQUAL(0, time.Second);
}
TEST(DATEUTILS_TEST, Time_Set) {
	TTime time;
	time.Set(20, 59, 59);
	TEST_ASSERT_EQUAL(20, time.Hour);
	TEST_ASSERT_EQUAL(59, time.Minute);
	TEST_ASSERT_EQUAL(59, time.Second);
	time.Set();
	TEST_ASSERT_EQUAL(0, time.Hour);
	TEST_ASSERT_EQUAL(0, time.Minute);
	TEST_ASSERT_EQUAL(0, time.Second);
}
TEST(DATEUTILS_TEST, Time_CopyFrom) {
	TTime time(20, 59, 59);
	TTime time2;
	time2.CopyFrom(time);
	TEST_ASSERT_EQUAL(20, time2.Hour);
	TEST_ASSERT_EQUAL(59, time2.Minute);
	TEST_ASSERT_EQUAL(59, time2.Second);
}
TEST(DATEUTILS_TEST, Time_CopyTo) {
	TTime time(20, 59, 59);
	TTime time2;
	time.CopyTo(&time2);
	TEST_ASSERT_EQUAL(20, time2.Hour);
	TEST_ASSERT_EQUAL(59, time2.Minute);
	TEST_ASSERT_EQUAL(59, time2.Second);
}
IGNORE_TEST(DATEUTILS_TEST, Time_ToString) {
	TTime time(20, 59, 59);
	char string[10];
	time.ToString(string);
	TEST_ASSERT_EQUAL('\0', string[time.StringLen()]);

	for (u08 i = 0; i < time.StringLen(); i++) {
		TEST_ASSERT_INT8_WITHIN(64, 64, string[i]);
	}
}
TEST(DATEUTILS_TEST, Time_Comparison) {
	TTime time(20, 59, 59);
	TTime time_same(20, 59, 59);
	TTime time_lowHour(1, 59, 59);
	TTime time_lowMinute(20, 1, 59);
	TTime time_lowSecond(20, 59, 1);
	TEST_ASSERT_EQUAL(DATETIME_EQUAL, TTime::Compare(time, time_same));
	TEST_ASSERT_EQUAL(DATETIME_FIRST_GREATER, TTime::Compare(time, time_lowHour));
	TEST_ASSERT_EQUAL(DATETIME_SECOND_GREATER, TTime::Compare(time_lowHour, time));
	TEST_ASSERT_EQUAL(DATETIME_FIRST_GREATER, TTime::Compare(time, time_lowMinute));
	TEST_ASSERT_EQUAL(DATETIME_FIRST_GREATER, TTime::Compare(time, time_lowSecond));
}

TEST(DATEUTILS_TEST, Time_ComparisonIsEqual) {
	TTime time(20, 59, 59);
	TTime time_same(20, 59, 59);
	TTime time_notsame(20, 1, 59);
	TEST_ASSERT_EQUAL(true, time == time_same);
	TEST_ASSERT_EQUAL(false, time == time_notsame);
}



TEST(DATEUTILS_TEST, Time_SecondsMoreThan) {
	TTime time(13, 50, 1);
	TTime time_litle(13, 50, 30);
	TTime time_more(13, 50, 59);
	TTime time_overflow(13, 51, 1);
	TEST_ASSERT_EQUAL(-29, time.SecondsMoreThan(time_litle));
	TEST_ASSERT_EQUAL(0, time.SecondsMoreThan(time));
	TEST_ASSERT_EQUAL(29, time_more.SecondsMoreThan(time_litle));
	TEST_ASSERT_EQUAL(-58, time_overflow.SecondsMoreThan(time_more));//overflow
}

TEST(DATEUTILS_TEST, Time_ComparisonEquations) {
	TTime time(13, 50, 1);
	TTime time2(13, 50, 2);
	TTime time3(13, 51, 1);
	TTime time4(14, 51, 1);
	TEST_ASSERT_EQUAL(true, time2 > time);
	TEST_ASSERT_EQUAL(true, time3 > time2);
	TEST_ASSERT_EQUAL(false, time > time4);
	TEST_ASSERT_EQUAL(true, time >= time);
	TEST_ASSERT_EQUAL(true, time4 >= time);
	TEST_ASSERT_EQUAL(false, time2 >= time3);
	TEST_ASSERT_EQUAL(true, time < time2);
	TEST_ASSERT_EQUAL(true, time2 < time3);
	TEST_ASSERT_EQUAL(false, time4 < time);
	TEST_ASSERT_EQUAL(true, time <= time);
	TEST_ASSERT_EQUAL(true, time2 <= time3);
	TEST_ASSERT_EQUAL(true, time3 <= time4);
}
TEST(DATEUTILS_TEST, Time_ChangeDigits) {
	TTime time(13, 59, 1);
	time.ChangeHourDigit(-1);
	TEST_ASSERT_EQUAL(12, time.Hour); TEST_ASSERT_EQUAL(59, time.Minute);
	TEST_ASSERT_EQUAL(1, time.Second);
	time.ChangeHourDigit(-12);
	TEST_ASSERT_EQUAL(23, time.Hour); TEST_ASSERT_EQUAL(59, time.Minute);
	TEST_ASSERT_EQUAL(1, time.Second);
	time.ChangeHourDigit(+50);
	TEST_ASSERT_EQUAL(1, time.Hour); TEST_ASSERT_EQUAL(59, time.Minute);
	TEST_ASSERT_EQUAL(1, time.Second);
	time.ChangeMinuteDigit(-1);
	TEST_ASSERT_EQUAL(1, time.Hour); TEST_ASSERT_EQUAL(58, time.Minute);
	TEST_ASSERT_EQUAL(1, time.Second);
	time.ChangeMinuteDigit(+10);
	TEST_ASSERT_EQUAL(1, time.Hour); TEST_ASSERT_EQUAL(1, time.Minute);
	TEST_ASSERT_EQUAL(1, time.Second);
	time.ChangeMinuteDigit(-60);
	TEST_ASSERT_EQUAL(1, time.Hour); TEST_ASSERT_EQUAL(59, time.Minute);
	TEST_ASSERT_EQUAL(1, time.Second);
	time.ChangeSecondDigit(-1);
	TEST_ASSERT_EQUAL(1, time.Hour); TEST_ASSERT_EQUAL(59, time.Minute);
	TEST_ASSERT_EQUAL(59, time.Second);
	time.ChangeSecondDigit(1);
	TEST_ASSERT_EQUAL(1, time.Hour); TEST_ASSERT_EQUAL(59, time.Minute);
	TEST_ASSERT_EQUAL(1, time.Second);
}
TEST(DATEUTILS_TEST, Time_IsValid) {
	TTime time(13, 59, 1);
	TEST_ASSERT_EQUAL(true, time.IsTimeValid());
	TEST_ASSERT_EQUAL(false, time.Set(25, 59, 1).IsTimeValid());
	TEST_ASSERT_EQUAL(false, time.Set(24, 59, 1).IsTimeValid());
	TEST_ASSERT_EQUAL(false, time.Set(23, 60, 1).IsTimeValid());
	TEST_ASSERT_EQUAL(false, time.Set(23, 59, 60).IsTimeValid());
}

TEST(DATEUTILS_TEST, DateTime_DefaultConstructor) {
	TDateTime dt;
	TEST_ASSERT_EQUAL(0, dt.date.Year);
	TEST_ASSERT_EQUAL(0, dt.date.Month);
	TEST_ASSERT_EQUAL(0, dt.date.Day);
	TEST_ASSERT_EQUAL(0, dt.time.Hour);
	TEST_ASSERT_EQUAL(0, dt.time.Minute);
	TEST_ASSERT_EQUAL(0, dt.time.Second);
	TEST_ASSERT_EQUAL(0, dt.time.Millis);
}
TEST(DATEUTILS_TEST, DateTme_Constructor) {
	TDateTime dt(2014, 12, 30, 20, 10, 1, 999);
	TEST_ASSERT_EQUAL(2014, dt.date.Year);
	TEST_ASSERT_EQUAL(12, dt.date.Month);
	TEST_ASSERT_EQUAL(30, dt.date.Day);
	TEST_ASSERT_EQUAL(20, dt.time.Hour);
	TEST_ASSERT_EQUAL(10, dt.time.Minute);
	TEST_ASSERT_EQUAL(1, dt.time.Second);
	TEST_ASSERT_EQUAL(999, dt.time.Millis);
}
TEST(DATEUTILS_TEST, DateTme_ConstructorFromDateTime) {
	TDateTime dt(2014, 12, 30, 20, 10, 0, 0);
	TDateTime dt2(dt);
	TEST_ASSERT_EQUAL(2014, dt2.date.Year);
	TEST_ASSERT_EQUAL(12, dt2.date.Month);
	TEST_ASSERT_EQUAL(30, dt2.date.Day);
	TEST_ASSERT_EQUAL(20, dt2.time.Hour);
	TEST_ASSERT_EQUAL(10, dt2.time.Minute);
	TEST_ASSERT_EQUAL(0, dt2.time.Second);
	TEST_ASSERT_EQUAL(0, dt2.time.Millis);
}
TEST(DATEUTILS_TEST, DateTme_ConstructorFromDate) {
	TDate date(2014, 12, 30);
	TDateTime dt(date);
	TEST_ASSERT_EQUAL(2014, dt.date.Year);
	TEST_ASSERT_EQUAL(12, dt.date.Month);
	TEST_ASSERT_EQUAL(30, dt.date.Day);
	TEST_ASSERT_EQUAL(0, dt.time.Hour);
	TEST_ASSERT_EQUAL(0, dt.time.Minute);
	TEST_ASSERT_EQUAL(0, dt.time.Second);
	TEST_ASSERT_EQUAL(0, dt.time.Millis);
}

TEST(DATEUTILS_TEST, DateTme_DecrementDay) {
	TDateTime dt;
	dt.date.Day = 13;
	dt.date.Month = 3;
	dt.date.Year = 2019;
	dt.time.Hour = 1;
	dt.time.Minute = 20;
	dt.time.Second = 0;
	dt.time.Millis = 0;
	dt.time.ChangeHourDigit(-1);
	TEST_ASSERT_EQUAL(0, dt.time.Hour);
}

TEST(DATEUTILS_TEST, DateTme_Set) {
	TDateTime dt;
	dt.Set(2014, 12, 30, 20, 10, 1, 500);
	TEST_ASSERT_EQUAL(2014, dt.date.Year);
	TEST_ASSERT_EQUAL(12, dt.date.Month);
	TEST_ASSERT_EQUAL(30, dt.date.Day);
	TEST_ASSERT_EQUAL(20, dt.time.Hour);
	TEST_ASSERT_EQUAL(10, dt.time.Minute);
	TEST_ASSERT_EQUAL(1, dt.time.Second);
	TEST_ASSERT_EQUAL(500, dt.time.Millis);
	dt.Set(200, 10, 5);
	TEST_ASSERT_EQUAL(200, dt.date.Year);
	TEST_ASSERT_EQUAL(10, dt.date.Month);
	TEST_ASSERT_EQUAL(5, dt.date.Day);
	TEST_ASSERT_EQUAL(0, dt.time.Hour);
	TEST_ASSERT_EQUAL(0, dt.time.Minute);
	TEST_ASSERT_EQUAL(0, dt.time.Second);
	TEST_ASSERT_EQUAL(0, dt.time.Millis);
}

IGNORE_TEST(DATEUTILS_TEST, DateTme_FROM_NTP_TIME_NYI) {
	TEST_ASSERT_TRUE_MESSAGE(false, "TEST NYI");
}

TEST(DATEUTILS_TEST, DateTme_Clear) {
	TDateTime dt(2014, 12, 30, 20, 10, 1, 500);
	dt.date.Clear();
	TEST_ASSERT_EQUAL(0, dt.date.Year);
	TEST_ASSERT_EQUAL(0, dt.date.Month);
	TEST_ASSERT_EQUAL(0, dt.date.Day);
	TEST_ASSERT_EQUAL(20, dt.time.Hour);
	TEST_ASSERT_EQUAL(10, dt.time.Minute);
	TEST_ASSERT_EQUAL(1, dt.time.Second);
	TEST_ASSERT_EQUAL(500, dt.time.Millis);
	dt.Set(2014, 12, 30, 20, 10, 1, 400);
	dt.time.Clear();
	TEST_ASSERT_EQUAL(2014, dt.date.Year);
	TEST_ASSERT_EQUAL(12, dt.date.Month);
	TEST_ASSERT_EQUAL(30, dt.date.Day);
	TEST_ASSERT_EQUAL(0, dt.time.Hour);
	TEST_ASSERT_EQUAL(0, dt.time.Minute);
	TEST_ASSERT_EQUAL(0, dt.time.Second);
	TEST_ASSERT_EQUAL(0, dt.time.Millis);
	dt.Set(2014, 12, 30, 20, 10, 1, 300);
	dt.ClearDateTime();
	TEST_ASSERT_EQUAL(0, dt.date.Year);
	TEST_ASSERT_EQUAL(0, dt.date.Month);
	TEST_ASSERT_EQUAL(0, dt.date.Day);
	TEST_ASSERT_EQUAL(0, dt.time.Hour);
	TEST_ASSERT_EQUAL(0, dt.time.Minute);
	TEST_ASSERT_EQUAL(0, dt.time.Second);
	TEST_ASSERT_EQUAL(0, dt.time.Millis);
}

IGNORE_TEST(DATEUTILS_TEST, DateTme_ToString) {
	TDateTime dt(2014, 12, 30, 20, 10, 1, 12);
	char string[20];
	dt.DateTimeToString(string); //TODO
	TEST_ASSERT_EQUAL('\0', string[dt.StringLen()]);

	for (u08 i = 0; i < dt.StringLen(); i++) {
		TEST_ASSERT_INT8_WITHIN(64, 64, string[i]);
	}
}

TEST(DATEUTILS_TEST, DateTme_ToDate) {
	TDateTime dt(2014, 12, 30, 20, 10, 1, 12);
	TDate date;
	dt.ToDate(&date);
	TEST_ASSERT_EQUAL(2014, date.Year);
	TEST_ASSERT_EQUAL(12, date.Month);
	TEST_ASSERT_EQUAL(30, date.Day);
}
TEST(DATEUTILS_TEST, DateTme_CopyFrom) {
	TDateTime dt(2014, 12, 30, 20, 10, 1, 500);
	TDateTime dt2;
	dt2.CopyFrom(dt);
	TEST_ASSERT_EQUAL(2014, dt2.date.Year);
	TEST_ASSERT_EQUAL(12, dt2.date.Month);
	TEST_ASSERT_EQUAL(30, dt2.date.Day);
	TEST_ASSERT_EQUAL(20, dt2.time.Hour);
	TEST_ASSERT_EQUAL(10, dt2.time.Minute);
	TEST_ASSERT_EQUAL(1, dt2.time.Second);
	TEST_ASSERT_EQUAL(500, dt2.time.Millis);
}
TEST(DATEUTILS_TEST, DateTme_CopyTo) {
	TDateTime dt(2014, 12, 30, 20, 10, 1, 500);
	TDateTime dt2;
	dt.CopyTo(&dt2);
	TEST_ASSERT_EQUAL(2014, dt2.date.Year);
	TEST_ASSERT_EQUAL(12, dt2.date.Month);
	TEST_ASSERT_EQUAL(30, dt2.date.Day);
	TEST_ASSERT_EQUAL(20, dt2.time.Hour);
	TEST_ASSERT_EQUAL(10, dt2.time.Minute);
	TEST_ASSERT_EQUAL(1, dt2.time.Second);
	TEST_ASSERT_EQUAL(500, dt2.time.Millis);
}
TEST(DATEUTILS_TEST, DateTme_IsValid) {
	TDateTime date(2015, 12, 30);
	TDateTime date2(0, 0, 0);
	TDateTime date3(2000, 13, 1);
	TDateTime date4(2000, 12, 32);
	TDateTime date5(2000, 11, 31);
	TDateTime date6(2000, 2, 30);
	TDateTime date7(2001, 2, 29);
	TDateTime date8(2001, 0, 5);
	TEST_ASSERT_EQUAL(true,  date.Set(2015, 12, 30).IsValid());
	TEST_ASSERT_EQUAL(false, date2.Set(0, 0, 0).IsValid());
	TEST_ASSERT_EQUAL(false, date2.Set(2000, 13, 1).IsValid());
	TEST_ASSERT_EQUAL(false, date3.Set(2000, 12, 32).IsValid());
	TEST_ASSERT_EQUAL(false, date4.Set(2000, 11, 31).IsValid());
	TEST_ASSERT_EQUAL(false, date5.Set(2000, 2, 30).IsValid());
	TEST_ASSERT_EQUAL(false, date6.Set(2001, 2, 29).IsValid());
	TEST_ASSERT_EQUAL(false, date7.Set(2001, 0, 5).IsValid());
	TEST_ASSERT_EQUAL(true, date.Set(2015, 12, 30, 23, 12, 59).IsValid());
	TEST_ASSERT_EQUAL(false, date.Set(2015, 12, 30, 25, 59, 1).IsValid());
	TEST_ASSERT_EQUAL(false, date.Set(2015, 12, 30, 24, 59, 1).IsValid());
	TEST_ASSERT_EQUAL(false, date.Set(2015, 12, 30, 23, 60, 1).IsValid());
	TEST_ASSERT_EQUAL(false, date.Set(2015, 12, 30, 23, 59, 60).IsValid());
}

TEST(DATEUTILS_TEST, DateTime_Comparison) {
	TDateTime date(2014, 12, 30, 23, 30, 50);
	TDateTime date_same(2014, 12, 30, 23, 30, 50);
	TDateTime date_lowyear(2013, 12, 30, 23, 30, 50);
	TDateTime date_lowmonth(2014, 11, 30, 23, 30, 50);
	TDateTime date_lowday(2014, 11, 29, 23, 30, 50);
	TEST_ASSERT_EQUAL(DATETIME_EQUAL, TDateTime::Compare(date, date_same));
	TEST_ASSERT_EQUAL(DATETIME_FIRST_GREATER, TDateTime::Compare(date, date_lowyear));
	TEST_ASSERT_EQUAL(DATETIME_SECOND_GREATER, TDateTime::Compare(date_lowyear, date));
	TEST_ASSERT_EQUAL(DATETIME_FIRST_GREATER, TDateTime::Compare(date, date_lowmonth));
	TEST_ASSERT_EQUAL(DATETIME_FIRST_GREATER, TDateTime::Compare(date, date_lowday));
	TDateTime time(2014, 12, 30, 20, 59, 59);
	TDateTime time_same(2014, 12, 30, 20, 59, 59);
	TDateTime time_lowHour(2014, 12, 30, 1, 59, 59);
	TDateTime time_lowMinute(2014, 12, 30, 20, 1, 59);
	TDateTime time_lowSecond(2014, 12, 30, 20, 59, 1);
	TEST_ASSERT_EQUAL(DATETIME_EQUAL, TDateTime::Compare(time, time_same));
	TEST_ASSERT_EQUAL(DATETIME_FIRST_GREATER, TDateTime::Compare(time, time_lowHour));
	TEST_ASSERT_EQUAL(DATETIME_SECOND_GREATER, TDateTime::Compare(time_lowHour, time));
	TEST_ASSERT_EQUAL(DATETIME_FIRST_GREATER, TDateTime::Compare(time, time_lowMinute));
	TEST_ASSERT_EQUAL(DATETIME_FIRST_GREATER, TDateTime::Compare(time, time_lowSecond));
}

TEST(DATEUTILS_TEST, DateTime_ComparisonEquations) {
	TDateTime date(2015, 12, 30, 23, 30, 50);
	TDateTime date2(2015, 12, 31, 30, 23, 30, 50);
	TDateTime date3(2016, 1, 1, 30, 23, 30, 50);
	TDateTime date4(2015, 12, 30, 30, 23, 30, 50);
	TEST_ASSERT_EQUAL(true, date3 > date2);
	TEST_ASSERT_EQUAL(true, date2 > date);
	TEST_ASSERT_EQUAL(false, date > date3);
	TEST_ASSERT_EQUAL(true, date4 >= date);
	TEST_ASSERT_EQUAL(true, date3 >= date2);
	TEST_ASSERT_EQUAL(false, date >= date3);
	TEST_ASSERT_EQUAL(true, date2 < date3);
	TEST_ASSERT_EQUAL(true, date < date2);
	TEST_ASSERT_EQUAL(false, date3 < date);
	TEST_ASSERT_EQUAL(true, date <= date4);
	TEST_ASSERT_EQUAL(true, date2 <= date3);
	TEST_ASSERT_EQUAL(false, date3 <= date);
	TDateTime time(2015, 12, 30, 13, 50, 1);
	TDateTime time2(2015, 12, 30, 13, 50, 2);
	TDateTime time3(2015, 12, 30, 13, 51, 1);
	TDateTime time4(2015, 12, 30, 14, 51, 1);
	TEST_ASSERT_EQUAL(true, time2 > time);
	TEST_ASSERT_EQUAL(true, time3 > time2);
	TEST_ASSERT_EQUAL(false, time > time4);
	TEST_ASSERT_EQUAL(true, time >= time);
	TEST_ASSERT_EQUAL(true, time4 >= time);
	TEST_ASSERT_EQUAL(false, time2 >= time3);
	TEST_ASSERT_EQUAL(true, time < time2);
	TEST_ASSERT_EQUAL(true, time2 < time3);
	TEST_ASSERT_EQUAL(false, time4 < time);
	TEST_ASSERT_EQUAL(true, time <= time);
	TEST_ASSERT_EQUAL(true, time2 <= time3);
	TEST_ASSERT_EQUAL(true, time3 <= time4);
}

TEST(DATEUTILS_TEST, DateTime_ComparisonIsEqual) {
	TDateTime date(2014, 12, 30, 20, 59, 59);
	TDateTime date_same(2014, 12, 30, 20, 59, 59);
	TDateTime date_notsame(2014, 11, 30, 20, 59, 59);
	TEST_ASSERT_EQUAL(true, date == date_same);
	TEST_ASSERT_EQUAL(false, date == date_notsame);
	TDateTime time(2014, 12, 30, 20, 59, 59);
	TDateTime time_same(2014, 12, 30, 20, 59, 59);
	TDateTime time_notsame(2014, 12, 30, 20, 1, 59);
	TEST_ASSERT_EQUAL(true, time == time_same);
	TEST_ASSERT_EQUAL(false, time == time_notsame);
}

TEST(DATEUTILS_TEST, DateTime_HoursBetween) {
	TDateTime time1 (2000, 2, 28, 03, 15, 20, 10 );
	TDateTime time2 (2000, 2, 28, 04, 15, 20, 10 );
	TDateTime time5 (2000, 4, 10, 03, 59, 20, 10 );
	TDateTime time6 (2000, 4, 10, 04, 0, 20, 10 );
	TDateTime time7 (2000, 3, 1, 03, 15, 20, 10 );
	TDateTime time8 (2000, 3, 1, 06, 15, 20, 10 );
	TDateTime time9 (1999, 3, 1, 03, 15, 20, 10 );
	TDateTime time10( 1999, 3, 2, 02, 15, 20, 10 );
	TDateTime time11( 1999, 3, 3, 02, 15, 20, 10 );
	TDateTime time0 (2015, 05, 02, 15, 33, 20, 10 );
	TDateTime time01( 2015, 05, 02, 15, 44, 20, 10 );
	TDateTime time12(2000, 4, 28, 03, 15, 20, 10);
	TDateTime time13(2000, 4, 28, 23, 0);
	TDateTime time14(2000, 4, 29, 2, 1);
	TDateTime time15(2000, 5, 1, 0, 0);
	TEST_ASSERT_EQUAL(0, time0.HoursBetween_MaxDay(time01)); // 0, "no1");
	TEST_ASSERT_EQUAL(0, time1.HoursBetween_MaxDay(time1));// 0, "no");
	TEST_ASSERT_EQUAL(1, time1.HoursBetween_MaxDay(time2));// 1, "1 hour");
	TEST_ASSERT_EQUAL(-1, time2.HoursBetween_MaxDay(time1));// -1, "hour back");
	TEST_ASSERT_EQUAL(1, time5.HoursBetween_MaxDay(time6));// 1, "1 minute");
	TEST_ASSERT_EQUAL(3, time7.HoursBetween_MaxDay(time8));// 3, "3 hours");
	TEST_ASSERT_EQUAL(23, time9.HoursBetween_MaxDay(time10)); // 23, "1 day,23");
	TEST_ASSERT_EQUAL(-23, time10.HoursBetween_MaxDay(time9)); // -23, "1 day back,23");
	TEST_ASSERT_EQUAL(24, time10.HoursBetween_MaxDay(time11)); // 24, "1 day full");
	TEST_ASSERT_EQUAL(24, time10.HoursBetween_MaxDay(time11)); // 24, "1 day full");
	TEST_ASSERT_EQUAL(24, time1.HoursBetween_MaxDay(time12)); // overflow, 2 days forward
	TEST_ASSERT_EQUAL(24, time1.HoursBetween_MaxDay(time12)); // overflow, 2 days forward
	TEST_ASSERT_EQUAL(3, time13.HoursBetween_MaxDay(time14)); // на стыке дней
	TEST_ASSERT_EQUAL(24, time13.HoursBetween_MaxDay(time15)); // на стыке дней overflow
}
TEST(DATEUTILS_TEST, DateTime_MinutesBetween) {
	TDateTime time1(2000, 2, 18, 15, 15);
	TDateTime time2(2000, 2, 18, 15, 59);
	TDateTime time3(2000, 2, 18, 16, 10);
	TDateTime time4(2000, 2, 18, 16, 25);
	TDateTime time5(2000, 2, 19, 15, 15);
	//
	TDateTime time6(2000, 2, 18, 23, 15);
	TDateTime time7(2000, 2, 19, 0, 10);
	TDateTime time8(2000, 2, 19, 0, 25);
	TDateTime time9(2000, 2, 19, 1, 10);
	TEST_ASSERT_EQUAL(0, time1.MinutesBetween_MaxHour(time1)); // same day
	TEST_ASSERT_EQUAL(45 - 1, time1.MinutesBetween_MaxHour(time2)); // same hour
	TEST_ASSERT_EQUAL(-(45 - 1), time2.MinutesBetween_MaxHour(time1)); // same hour.inverse
	TEST_ASSERT_EQUAL(55, time1.MinutesBetween_MaxHour(time3)); // hour changed
	TEST_ASSERT_EQUAL(60, time1.MinutesBetween_MaxHour(time4)); // hour changed,overflow
	TEST_ASSERT_EQUAL(60, time1.MinutesBetween_MaxHour(time5)); // other day
	TEST_ASSERT_EQUAL(55, time6.MinutesBetween_MaxHour(time7)); // hour changed, other day
	TEST_ASSERT_EQUAL(60, time6.MinutesBetween_MaxHour(time8)); // other day, overflow in same hour
	TEST_ASSERT_EQUAL(60, time6.MinutesBetween_MaxHour(time9)); // other day, overflow2 in other hour
}






TEST(DATEUTILS_TEST, DateTime_IncrMillis) {
	TDateTime dt(2015, 12, 31, 23, 59, 59, 999);
	dt.IncDateTimeMillis();
	TEST_ASSERT_EQUAL(2016, dt.date.Year); // next day
	TEST_ASSERT_EQUAL(01, dt.date.Month);
	TEST_ASSERT_EQUAL(01, dt.date.Day);
	TEST_ASSERT_EQUAL(0, dt.time.Hour);
	TEST_ASSERT_EQUAL(0, dt.time.Minute);
	TEST_ASSERT_EQUAL(0, dt.time.Second);
	TEST_ASSERT_EQUAL(0, dt.time.Millis);
}
TEST(DATEUTILS_TEST, DateTime_DecMillis) {
	TDateTime dt(2016, 01, 1, 0, 0, 0, 0);
	dt.DecDateTimeMillis();
	TEST_ASSERT_EQUAL(2015, dt.date.Year); // prev day
	TEST_ASSERT_EQUAL(12, dt.date.Month);
	TEST_ASSERT_EQUAL(31, dt.date.Day);
	TEST_ASSERT_EQUAL(23, dt.time.Hour);
	TEST_ASSERT_EQUAL(59, dt.time.Minute);
	TEST_ASSERT_EQUAL(59, dt.time.Second);
	TEST_ASSERT_EQUAL(999, dt.time.Millis);
}

TEST_GROUP_RUNNER(DATEUTILS_TEST) {
	RUN_TEST_CASE(DATEUTILS_TEST, DateTimeUtils);
	RUN_TEST_CASE(DATEUTILS_TEST, Date_DefaultConstructor);
	RUN_TEST_CASE(DATEUTILS_TEST, Date_Constructor);
	RUN_TEST_CASE(DATEUTILS_TEST, Date_ConstructorFromDate);
	RUN_TEST_CASE(DATEUTILS_TEST, Date_Set);
	RUN_TEST_CASE(DATEUTILS_TEST, Date_Clear);
	RUN_TEST_CASE(DATEUTILS_TEST, Date_CopyFrom);
	RUN_TEST_CASE(DATEUTILS_TEST, Date_CopyTo);
	RUN_TEST_CASE(DATEUTILS_TEST, Date_ToString);
	RUN_TEST_CASE(DATEUTILS_TEST, Date_Comparison);
	RUN_TEST_CASE(DATEUTILS_TEST, Date_ComparisonIsEqual);
	RUN_TEST_CASE(DATEUTILS_TEST, Date_ComparisonIsSameMonth);
	RUN_TEST_CASE(DATEUTILS_TEST, Date_ComparisonIsSameDay);
	RUN_TEST_CASE(DATEUTILS_TEST, Date_ComparisonIsNextMonthThan);
	RUN_TEST_CASE(DATEUTILS_TEST, Date_ComparisonIsPrevMonthThan);
	RUN_TEST_CASE(DATEUTILS_TEST, Date_ComparisonIsPrevDayThan);
	RUN_TEST_CASE(DATEUTILS_TEST, Date_ComparisonIsNextDayThan);
	RUN_TEST_CASE(DATEUTILS_TEST, Date_ComparisonIsSameYear);
	RUN_TEST_CASE(DATEUTILS_TEST, Date_ComparisonEquations);
	RUN_TEST_CASE(DATEUTILS_TEST, Date_IncDec);
	RUN_TEST_CASE(DATEUTILS_TEST, Date_DecDay_BetweenMonthWithDiffMaxDays);
	RUN_TEST_CASE(DATEUTILS_TEST, Date_DecYear_BetweenYearWithLeapDay);
	RUN_TEST_CASE(DATEUTILS_TEST, Date_DecYear_BetweenYearWithLeapDay);
	RUN_TEST_CASE(DATEUTILS_TEST, Date_MonthBetween);
	RUN_TEST_CASE(DATEUTILS_TEST, Date_DaysBetween);
	RUN_TEST_CASE(DATEUTILS_TEST, Date_CalendarYearsBetweenn);
	RUN_TEST_CASE(DATEUTILS_TEST, Date_CheckIsValid);
	RUN_TEST_CASE(DATEUTILS_TEST, Date_ChangeDigits);
	RUN_TEST_CASE(DATEUTILS_TEST, Time_DefaultConstructor);
	RUN_TEST_CASE(DATEUTILS_TEST, Time_Constructor);
	RUN_TEST_CASE(DATEUTILS_TEST, Time_ConstructorFromtime);
	RUN_TEST_CASE(DATEUTILS_TEST, Time_Clear);
	RUN_TEST_CASE(DATEUTILS_TEST, Time_IsValid);
	RUN_TEST_CASE(DATEUTILS_TEST, Time_Set);
	RUN_TEST_CASE(DATEUTILS_TEST, Time_CopyFrom);
	RUN_TEST_CASE(DATEUTILS_TEST, Time_CopyTo);
	RUN_TEST_CASE(DATEUTILS_TEST, Time_ToString);
	RUN_TEST_CASE(DATEUTILS_TEST, Time_Comparison);
	RUN_TEST_CASE(DATEUTILS_TEST, Time_ComparisonIsEqual);
	RUN_TEST_CASE(DATEUTILS_TEST, Time_SecondsMoreThan);
	RUN_TEST_CASE(DATEUTILS_TEST, Time_ComparisonEquations);
	RUN_TEST_CASE(DATEUTILS_TEST, DateTime_DefaultConstructor);
	RUN_TEST_CASE(DATEUTILS_TEST, DateTme_Constructor);
	RUN_TEST_CASE(DATEUTILS_TEST, DateTme_ConstructorFromDateTime);
	RUN_TEST_CASE(DATEUTILS_TEST, DateTme_ConstructorFromDate);
	RUN_TEST_CASE(DATEUTILS_TEST, DateTme_Set);
	RUN_TEST_CASE(DATEUTILS_TEST, DateTme_DecrementDay);
	RUN_TEST_CASE(DATEUTILS_TEST, DateTme_FROM_NTP_TIME_NYI);
	RUN_TEST_CASE(DATEUTILS_TEST, DateTme_Clear);
	RUN_TEST_CASE(DATEUTILS_TEST, DateTme_ToString);
	RUN_TEST_CASE(DATEUTILS_TEST, DateTme_ToDate);
	RUN_TEST_CASE(DATEUTILS_TEST, DateTme_CopyFrom);
	RUN_TEST_CASE(DATEUTILS_TEST, DateTme_CopyTo);
	RUN_TEST_CASE(DATEUTILS_TEST, DateTme_IsValid);
	RUN_TEST_CASE(DATEUTILS_TEST, DateTime_Comparison);
	RUN_TEST_CASE(DATEUTILS_TEST, DateTime_ComparisonEquations);
	RUN_TEST_CASE(DATEUTILS_TEST, DateTime_ComparisonIsEqual);
	RUN_TEST_CASE(DATEUTILS_TEST, DateTime_HoursBetween);
	RUN_TEST_CASE(DATEUTILS_TEST, DateTime_MinutesBetween);
	RUN_TEST_CASE(DATEUTILS_TEST, DateTime_IncrMillis);
	RUN_TEST_CASE(DATEUTILS_TEST, DateTime_DecMillis);
}










/*

void _DateTime_Test_DaysBetween()
{


	TDate time1 = {2000,2,28,03,15,20,10};
	TDate time2 = {2000,3,1,03,15,20,10};
	TDate time3 = {2001,2,28,03,15,20,10};
	TDate time4 = {2001,3,1,03,15,20,10};
	TDate time5 = {2000,4,10,03,15,20,10};
	TDate time6 = {2000,5,1,03,15,20,10};
	TDate time7 = {2000,3,1,03,15,20,10};
	TDate time8 = {2001,3,1,03,15,20,10};
	TDate time9 = {1999,3,1,03,15,20,10};
	TEST_ASSERT_EQUAL(DateTime_DaysBetween(&time1,&time2),2,"Febriary in leap_year");
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time3,&time4),1,"Febriary in not leap year");
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time5,&time6),21,"month");
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time6,&time7),-61,"month back");
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time7,&time8),365,"not leap year");
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time8,&time7),-365,"not leap year back");
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time9,&time7),366,"leap year");

	TDate time01 = {2001,3,1,03,15,20,10};
	TDate time02 = {2003,3,1,03,15,20,10};
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time01,&time02),365+365,"two years(not leap),same_month");

	TDate time001 = {2000,3,1,03,15,20,10};
	TDate time002 = {2002,3,1,03,15,20,10};
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time001,&time002),365+365,"two years(first leap),same_month");



	TDate time0001 = {1998,3,1,03,15,20,10};
	TDate time0002 = {2000,3,1,03,15,20,10};
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time0001,&time0002),365+366,"two years(last leap),same_month");

	TDate time00001 = {1999,3,1,03,15,20,10};
	TDate time00002 = {2001,3,1,03,15,20,10};
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time00001,&time00002),366+365,"two years(middle leap),same_month");

	TDate time000001 = {1999,3,1,03,15,20,10};
	TDate time000002 = {2001,2,1,03,15,20,10};
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time000001,&time000002),366+365-28,"two years(middle leap but without FEBRIARY),same_month");


	TDate time03 = {2000,3,1,03,15,20,10};
	TDate time04 = {2002,4,1,03,15,20,10};
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time03,&time04),365+365+31,"two years,+1 month");

	TDate time05 = {2000,3,1,03,15,20,10};
	TDate time06 = {2002,2,27,03,15,20,10};
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time05,&time06),365+365-2,"two years,-1month(-2 days)");

	TDate time07 = {2000,3,1,03,15,20,10};
	TDate time08 = {2002,2,27,03,15,20,10};
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time07,&time08),365+365-2,"1 year,other_month,-2 days");



	TDate time09 = { 2015, 5, 4, 15, 14, 44, 44 };
	TDate time010 = { 2015, 5, 5, 15, 14, 45, 45 };
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time09, &time010), 1, "1 day middle month");
	TDate time011 = { 2015, 5, 31, 15, 14, 44, 44 };
	TDate time012 = { 2015, 6, 1, 15, 14, 45, 45 };
	TEST_ASSERT_EQUAL_16(DateTime_DaysBetween(&time011, &time012), 1, "1 day on edge months");

}

void _DateTime_Test_MonthsBetween()
{


	TDate time1 = { 2000, 2, 28, 03, 15, 20, 10 };
	TDate time2 = { 2000, 3, 1, 03, 15, 20, 10 };
	TDate time5 = { 2000, 4, 10, 03, 15, 20, 10 };
	TDate time6 = { 2000, 5, 1, 03, 15, 20, 10 };
	TDate time7 = { 2000, 3, 1, 03, 15, 20, 10 };
	TDate time8 = { 2001, 3, 1, 03, 15, 20, 10 };
	TDate time9 = { 1999, 3, 1, 03, 15, 20, 10 };
	TEST_ASSERT_EQUAL_16(DateTime_MonthsBetween(&time1, &time2), 1, "Febriary in leap_year");
	TEST_ASSERT_EQUAL_16(DateTime_MonthsBetween(&time1, &time1), 0, "same month\n");
	TEST_ASSERT_EQUAL_16(DateTime_MonthsBetween(&time5, &time6), 1, "month");
	TEST_ASSERT_EQUAL_16(DateTime_MonthsBetween(&time6, &time7), -2, "month back");
	TEST_ASSERT_EQUAL_16(DateTime_MonthsBetween(&time7, &time8), 12, "not leap year");
	TEST_ASSERT_EQUAL_16(DateTime_MonthsBetween(&time8, &time7), -12, "not leap year back");

	TDate time01 = { 2001, 3, 1, 03, 15, 20, 10 };
	TDate time02 = { 2003, 3, 1, 03, 15, 20, 10 };
	TEST_ASSERT_EQUAL_16(DateTime_MonthsBetween(&time01, &time02), 24, "two years(not leap),same_month");
	TEST_ASSERT_EQUAL_16(DateTime_MonthsBetween(&time02, &time01), -24, "two years(not leap),same_month back");


	TDate time000001 = { 1999, 3, 1, 03, 15, 20, 10 };
	TDate time000002 = { 2001, 2, 1, 03, 15, 20, 10 };
	TEST_ASSERT_EQUAL_16(DateTime_MonthsBetween(&time000001, &time000002), 12+11, "two years -1 month");


	TDate time03 = { 2000, 3, 1, 03, 15, 20, 10 };
	TDate time04 = { 2002, 4, 1, 03, 15, 20, 10 };
	TEST_ASSERT_EQUAL_16(DateTime_MonthsBetween(&time03, &time04), 12 + 12 + 1, "two years,+1 month");


}




*/