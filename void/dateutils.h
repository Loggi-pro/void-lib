#pragma once
//�� �������� � ������>+-1 � ����� �� ����� ���������� ������������ � �������� �������(���� ���� �����)
#include <void/platform_specific.h>
#include <void/static_assert.h>
#define TO_SECONDS(x)	(x*1UL*24*60*60)
#define SECONDS_2014 TO_SECONDS(41638UL)
#define SECONDS_IN_LPYEAR TO_SECONDS(366UL)
#define SECONDS_IN_YEAR TO_SECONDS(365UL)

#define DAYS_IN_LPYEAR (366UL)
#define DAYS_IN_YEAR (365UL)
#define MONTH_IN_YEAR (12UL)
#define HOURS_IN_DAY (24UL)
#define YEARS_MAX (9999UL)
#define YEARS_MIN (1900UL)
#define MINUTES_IN_HOUR (60UL)
#define SECONDS_IN_MINUTE (60UL)
#define MILLIS_IN_SECOND (1000UL)
#define DAYS_IN_MONTH_MAX (31UL)

typedef enum {DATETIME_EQUAL = 0, DATETIME_FIRST_GREATER = -1, DATETIME_SECOND_GREATER = 1} TDateTimeCompare;
class TDateTime;

class TDateTimeUtils {
	private:
		static inline const u08 days_in_monthArr[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	public:
		template <typename T>
		static T Prev(T t);
		template <typename T>
		static T Next(T t);
		template <typename T>
		static bool DecValue(T& val, T Min, T delta);

		template <typename T>
		static bool IncValue(T& val, T Max, T delta);

		u08 static Month_Previous(u08 month);
		u08 static Month_Next(u08 month);

		bool static IsLeap(u16  year);

		static u08  DaysInMonth(u08 month, u16 year);
		static u08  DaysInMonth(u08 month, bool isLeap);
		static u32 SecondsInMonth(u08 month, u16 year);
		static u32 SecondsInMonth( u08 month, bool isLeap);
		static u32  SecondsInYear(u16 year);


		template <typename T>
		bool GetMinMax(T& time1, T& time2, T** MaxTime, T** MinTime);
};
//const u08 TDateTimeUtils::days_in_monthArr[] PROGMEM = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };




class TDate {
private:
	//<0 if date1>date2; >0 if date1<date2

	void _checkDayForOverflow();
	//inc by 1, if >Max then set=max
	bool _incDayDigitWithCarry(u08 delta = 1);
	bool _decDayDigitWithCarry(u08 delta = 1, bool IS_in_range_of_this_month = false);
	bool _incMonthDigitWithCarry(u08 delta = 1);
	bool _decMonthDigitWithCarry(u08 delta = 1);
	bool _incYearDigitWithCarry(u16 delta = 1);
	bool _decYearDigitWithCarry(u16 delta = 1);

	bool _IsLater_Than(const TDate & other_date)const;
	bool _IsLaterOrE_Than(const TDate & other_date)const;
	bool _IsEarly_Than(const TDate & other_date)const;
	bool _IsEarlyOrE_Than(const TDate & other_date)const;

public:
	u16 Year = 0;
	u08 Month = 0;
	u08 Day = 0;
	TDate() = default;
	TDate(u16 AYear, u08 AMonth, u08 ADay);
	TDate & Set(u16 AYear, u08 AMonth, u08 ADay);
	void Clear();
	TDate(const TDate & other_date) = default;


	static u08 StringLen();
	char* ToString(char* string)const;

	static TDateTimeCompare Compare(const TDate & date1, const TDate & date2);


	bool IsEqual(const TDate & other_date)const;

	bool IsSameMonth(const TDate & other_date)const;
	bool IsNextMonthThan(const TDate & other_date) const;
	bool IsPrevMonthThan(const TDate & other_date) const;

	bool IsSameDay(const TDate & other_date) const;
	bool IsPrevDayThan(const TDate & other_date) const;
	bool IsNextDayThan(const TDate & other_date) const;
	bool IsSameYear(const TDate & other_date) const;
	static u16 MonthBetween(const TDate & lhs, const TDate & rhs);
	//length=9



	TDate & IncDay(u08 delta = 1);
	TDate & DecDay(u08 delta = 1);
	TDate & IncMonth(u08 delta = 1);
	TDate & DecMonth(u08 delta = 1);
	TDate & IncYear(u16 delta = 1);
	TDate & DecYear(u16 delta = 1);

	TDate GetPrevDay();
	TDate GetNextDay();
	TDate GetNextMonth();
	TDate GetPrevMonth();
	TDate GetNextYear();
	TDate GetPrevYear();


	u16 MonthBetween(const TDate & other_date) const;
	u16 DaysBetween(const TDate & time2) const;

	u16 CalendarYearsBetween(const TDate & other_date) const;
	bool IsDateValid()const;

	bool ChangeYearDigit(s16 delta);
	bool ChangeMonthDigit(s08 delta);
	bool ChangeDayDigit(s08 delta);

	bool operator==(const TDate & time1)const;
	bool operator!=(const TDate & time1)const;
	bool operator<(const TDate & time1)const;
	bool operator<=(const TDate & time1)const;
	bool operator>(const TDate & time1)const;
	bool operator>=(const TDate & time1)const;

};
//VOID_STATIC_ASSERT(sizeof(TDate) == 4);


class TTime {
private:
	friend class TDateTime;
	bool _incHourWithCarry(u08 delta = 1);

	bool _decHourWithCarry(u08 delta = 1);


	bool _incMinuteWithCarry(u08 delta = 1);
	bool _decMinuteWithCarry(u08 delta = 1);
	bool _incSecondWithCarry(u08 delta = 1);
	bool _decSecondWithCarry(u08 delta = 1);
	bool _incMillisWithCarry(u16 delta = 1);
	bool _decMillisWithCarry(u16 delta = 1);


	bool _IsEqual(const TTime & time)const;
	bool _IsLater_Than(const TTime & other_time) const;
	bool _IsLaterOrE_Than(const TTime & other_time) const;
	bool _IsEarly_Than(const TTime & other_time) const;
	bool _IsEarlyOrE_Than(const TTime & other_time) const;

public:
	u16 Millis;
	u08 Second;
	u08 Minute;
	u08 Hour;
	TTime(u08 AHour, u08 AMinute, u08 ASecond, u16 AMillis = 0);
	TTime(const TTime & other) = default;
	TTime() = default;
	TTime & Set(u08 AHour = 0, u08 AMinute = 0, u08 ASecond = 0,
	            const u16 AMillis = 0);
	void Clear();


	TTime & IncSeconds();
	TTime & DecSeconds();
	TTime & IncMinutes();
	TTime & DecMinutes();
	TTime & IncHours();
	TTime & DecHours();


	//char len = 6;
	char* ToString(char* string)const;

	static u08 StringLen();

	static TDateTimeCompare Compare(const TTime & time1, const TTime & time2);


	//if>0 = this greater than arg ������ �������, �� ��������� ������!
	s08 SecondsMoreThan(TTime & other_time)const;
	bool IsTimeValid() const;

	bool ChangeHourDigit(s08 delta);
	bool ChangeMinuteDigit(s08 delta);
	bool ChangeSecondDigit(s08 delta);
	bool ChangeMillisDigit(s16 delta);

	bool operator==(const TTime & time1)const;
	bool operator!=(const TTime & time1)const;
	bool operator<(const TTime & time1)const;
	bool operator<=(const TTime & time1)const;
	bool operator>(const TTime & time1)const;
	bool operator>=(const TTime & time1)const;

};
//VOID_STATIC_ASSERT(sizeof(TTime) == 5);

class TDateTime {
private:
	bool _IsLater_Than(const TDateTime & other_datetime) const;
	bool _IsLaterOrE_Than(const TDateTime & other_datetime) const;
	bool _IsEarly_Than(const TDateTime & other_datetime) const;
	bool _IsEarlyOrE_Than(const TDateTime & other_datetime) const;
	bool _IsEqual(const TDateTime & Adt) const;
public:
	TDate date;
	TTime time;
	TDateTime(const u16 AYear, const u08 AMonth, const u08 ADay, const u08 AHours = 0,
	          const u08 AMinutes = 0, const u08 ASeconds = 0, const u16 AMillis = 0);
	TDateTime() = default;
	TDateTime(const TDate & dt);
	TDateTime(const TDateTime & dt) = default;
	TDateTime & Set(const u16 AYear, const u08 AMonth, const u08 ADay, const u08 AHours = 0,
	                const u08 AMinutes = 0, const u08 ASeconds = 0, const u16 AMillis = 0);
	//FROM 1900.01.01 //work with ntp if year>2014, not calc milliseconds
	void FromNTPTime(u32 timestamp, s08 timezone);

	void ClearDateTime();

	static u08 StringLen();
	//��/��/��,��:��string length = 15;
	char* DateTimeToString(char string[15]) const;

	bool IsValid()const;



	static TDateTimeCompare Compare(const TDateTime & time1, const TDateTime & time2);


	TDateTime & IncDateTimeMillis(u16 delta = 1);
	TDateTime & DecDateTimeMillis(u16 delta = 1);
	TDateTime & IncDateTimeSeconds(u08 delta = 1);
	TDateTime & DecDateTimeSeconds(u08 delta = 1);
	TDateTime & IncDateTimeMinutes(u08 delta = 1);
	TDateTime & DecDateTimeMinutes(u08 delta = 1);
	TDateTime & IncDateTimeHours(u08 delta = 1);
	TDateTime & DecDateTimeHours(u08 delta = 1);



	//� ������ 1 ���
	//���������
	bool operator==(const TDateTime & time1)const;
	bool operator!=(const TDateTime & time1)const;
	bool operator<(const TDateTime & time1)const;
	bool operator<=(const TDateTime & time1)const;
	bool operator>(const TDateTime & time1)const;
	bool operator>=(const TDateTime & time1)const;




	//>0 if Arg.Hour>Self.Hour
	s08 HoursBetween_MaxDay(const TDateTime & time) const;
	//>0 if Arg.Minutes>Self.Minutes
	s08 MinutesBetween_MaxHour(const TDateTime & other_time)const;
};
//VOID_STATIC_ASSERT(sizeof(TDateTime) == 9);
