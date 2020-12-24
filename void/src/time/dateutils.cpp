#include <void/dateutils.h>
#include <void/assert.h>
#ifdef _STM8
	#include <string.h> //for memcpy
#endif
// const u08 TDateTimeUtils::days_in_monthArr[] =
template <typename T>
T TDateTimeUtils::Prev(T t) {
	return (t >= 1) ? (T)(t - 1) : 0;
}

template <typename T>
T TDateTimeUtils::Next(T t) {
	return (T)(t + 1);
}

template <typename T>
bool TDateTimeUtils::DecValue(T& val, T Min, T delta) {
	if (val >= delta + Min) {
		val = (T)(val - delta);
		return false;
	} else {
		val = Min;
		return true;
	}
}

template <typename T>
bool TDateTimeUtils::IncValue(T& val, T Max, T delta) {
	val = (T)(val + delta);

	if (val <= Max) {
		return false;
	} else {
		val = Max;
		return true;
	}
}

u08 TDateTimeUtils::Month_Previous(u08 month) {
	if (month > 1) { return static_cast<u08>(month - 1); }

	return 12;
}

u08 TDateTimeUtils::Month_Next(u08 month) {
	if (month < 12) { return static_cast<u08>(month + 1); }

	return 1;
}

bool TDateTimeUtils::IsLeap(u16 year) {
	if (((year % 4 == 0) && (year % 100 != 0)) || ((year % 400 == 0))) {
		return true;
	}

	return false;
}

u08 TDateTimeUtils::DaysInMonth(u08 month, u16 year) {
	return DaysInMonth(month, IsLeap(year));
}

u08 TDateTimeUtils::DaysInMonth(u08 month, bool isLeap) {
	if (isLeap && month == 2) {
		return 29;
	}

	return days_in_monthArr[month];
}

u32 TDateTimeUtils::SecondsInMonth(u08 month, u16 year) {
	return SecondsInMonth(month, IsLeap(year));
}

u32 TDateTimeUtils::SecondsInMonth(u08 month, bool isLeap) {
	return TO_SECONDS(DaysInMonth(month, isLeap));
}

u32 TDateTimeUtils::SecondsInYear(u16 year) {
	if (IsLeap(year)) {
		return SECONDS_IN_LPYEAR;
	} else {
		return SECONDS_IN_YEAR;
	}
}





template <typename T>
bool TDateTimeUtils::GetMinMax(T& time1, T& time2, T** MaxTime, T** MinTime) {
	TDateTimeCompare sign = Compare(time1, time2);

	if (sign == DATETIME_FIRST_GREATER) {
		*MaxTime = &time1;
		*MinTime = &time2;
		return true;
	} else if (sign == DATETIME_SECOND_GREATER) {
		*MaxTime = &time2;
		*MinTime = time1;
		return true;
	} else { return false; }
}



void TDate::_checkDayForOverflow() {
	u08 max = TDateTimeUtils::DaysInMonth(this->Month, this->Year);

	if (this->Day > max) {
		this->Day = max;
	};
}

bool TDate::_incDayDigitWithCarry(u08 delta ) {
	u08 max = TDateTimeUtils::DaysInMonth(this->Month, this->Year);

	if (!TDateTimeUtils::IncValue(this->Day, max, delta)) { return false; }

	this->Day = 1;
	return true;
}
//���� ����������� true �� ����� ������������ ��� ����� ������, ����� - ����� ����������
bool TDate::_decDayDigitWithCarry(u08 delta, bool IS_in_range_of_this_month ) {
	if (!TDateTimeUtils::DecValue(this->Day, (u08)1, delta)) { return false; }

	u08 lMonth = IS_in_range_of_this_month ? this->Month : TDateTimeUtils::Month_Previous(this->Month);
	this->Day = TDateTimeUtils::DaysInMonth(lMonth, this->Year);
	return true;
}

bool TDate::_incMonthDigitWithCarry(u08 delta ) {
	bool overflow = TDateTimeUtils::IncValue(this->Month, (u08)MONTH_IN_YEAR, delta);

	if (overflow) {
		this->Month = 1;
	};

	_checkDayForOverflow();

	return overflow;
}

bool TDate::_decMonthDigitWithCarry(u08 delta ) {
	bool overflow = TDateTimeUtils::DecValue(this->Month, (u08)1, delta);

	if (overflow) {
		this->Month = MONTH_IN_YEAR;
	};

	_checkDayForOverflow();

	return overflow;
}

bool TDate::_incYearDigitWithCarry(u16 delta ) {
	bool overflow = TDateTimeUtils::IncValue(this->Year, (u16)YEARS_MAX, delta);
	_checkDayForOverflow();

	if (overflow) {
		this->Year = YEARS_MIN;
	}

	return overflow;
}

bool TDate::_decYearDigitWithCarry(u16 delta ) {
	bool overflow = TDateTimeUtils::DecValue(this->Year, (u16)YEARS_MIN, delta);
	_checkDayForOverflow();

	if (overflow) {
		this->Year = YEARS_MAX;
	}

	return overflow;
}


TDate::TDate(u16 AYear, u08 AMonth, u08 ADay) : Year(AYear), Month(AMonth), Day(ADay) {
}

u16 TDate::MonthBetween(const TDate& lhs, const TDate& rhs) {
	return lhs.MonthBetween(rhs);
}

TDate& TDate::Set(u16 AYear, u08 AMonth, u08 ADay) {
	Year = AYear;
	Month = AMonth;
	Day = ADay;
	return *this;
}

void TDate::Clear() {
	Year = 0;
	Month = 0;
	Day = 0;
}

u08 TDate::StringLen() {
	return 9;
}

char* TDate::ToString(char* string) const {
	assert(false); //NYI
	/*
		if (this->Day <= 99) {
			itona<u08>(this->Day, string, 2);
		} else {
			string[0] = 'x';
			string[1] = 'x';
		}

		string[2] = '/';

		if (this->Month <= 12) {
			itona<u08>(this->Month, string + 3, 2);
		} else {
			string[3] = 'x';
			string[4] = 'x';
		}

		string[5] = '/';
		u16 year = this->Year % 100;
		itona<u16>(year, string + 6, 2);
		string[8] = '\0';
		return string;*/
	return string;
}

TDateTimeCompare TDate::Compare(const TDate& date1, const TDate& date2) {
	if (date1.Year > date2.Year) { return DATETIME_FIRST_GREATER; }
	else if (date2.Year > date1.Year) { return DATETIME_SECOND_GREATER; }

	if (date1.Month > date2.Month) { return DATETIME_FIRST_GREATER; }
	else if (date2.Month > date1.Month) { return DATETIME_SECOND_GREATER; }

	if (date1.Day > date2.Day) { return DATETIME_FIRST_GREATER; }
	else if (date2.Day > date1.Day) { return DATETIME_SECOND_GREATER; }

	return DATETIME_EQUAL;
}

bool TDate::IsEqual(const TDate& other_date) const {
	return Day == other_date.Day && Month == other_date.Month && Year == other_date.Year;
}

bool TDate::IsSameMonth(const TDate& other_date) const {
	if (this->Month == other_date.Month) {
		return this->Year == other_date.Year;
	}

	return false;
}

bool TDate::IsNextMonthThan(const TDate& other_date) const {
	u08 prev_month = TDateTimeUtils::Month_Previous(this->Month);

	if (prev_month == other_date.Month) {
		if (prev_month == 12) { //���� ��� ������� ����� ����
			return this->Year - 1 == other_date.Year;
		}

		return this->Year == other_date.Year;
	}

	return false;
}

bool TDate::IsPrevMonthThan(const TDate& other_date) const {
	u08 prev_month = TDateTimeUtils::Month_Previous(other_date.Month);

	if (prev_month == this->Month) {
		if (prev_month == 12) { //���� ��� ������� ����� ����
			return this->Year == other_date.Year - 1;
		}

		return this->Year == other_date.Year;
	}

	return false;
}

bool TDate::IsSameDay(const TDate& other_date) const {
	return IsEqual(other_date);
}

bool TDate::IsPrevDayThan(const TDate& other_date) const {
	TDate prev_day(other_date);
	prev_day.DecDay();
	return *this == prev_day;
}

bool TDate::IsNextDayThan(const TDate& other_date) const {
	TDate prev_day(*this);
	prev_day.DecDay();
	return other_date == prev_day;
}

bool TDate::IsSameYear(const TDate& other_date) const {
	return this->Year == other_date.Year;
}

bool TDate::_IsLater_Than(const TDate& other_date) const {
	return Compare(*this, other_date) == DATETIME_FIRST_GREATER;
}

bool TDate::_IsLaterOrE_Than(const TDate& other_date) const {
	TDateTimeCompare res = Compare(*this, other_date);
	return (res == DATETIME_FIRST_GREATER || res == DATETIME_EQUAL);
}

bool TDate::_IsEarly_Than(const TDate& other_date) const {
	return Compare(*this, other_date) == DATETIME_SECOND_GREATER;
}

bool TDate::_IsEarlyOrE_Than(const TDate& other_date) const {
	TDateTimeCompare res = Compare(*this, other_date);
	return (res == DATETIME_SECOND_GREATER || res == DATETIME_EQUAL);
}

TDate& TDate::IncDay(u08 delta) {
	assert(delta <= TDateTimeUtils::DaysInMonth(this->Month, this->Year));

	if (!_incDayDigitWithCarry(delta)) { return *this; }

	return IncMonth();
}

TDate& TDate::DecDay(u08 delta) {
	assert(delta <= TDateTimeUtils::DaysInMonth(this->Month, this->Year));

	if (!_decDayDigitWithCarry(delta, false)) { return *this; }

	return DecMonth();
}

TDate&  TDate::IncMonth(u08 delta) {
	assert(delta <= MONTH_IN_YEAR);

	if (!_incMonthDigitWithCarry(delta)) { return *this; }

	return IncYear();
}

TDate&  TDate::DecMonth(u08 delta) {
	assert(delta <= MONTH_IN_YEAR);

	if (!_decMonthDigitWithCarry(delta)) { return *this; }

	return DecYear();
}

TDate&  TDate::IncYear(u16 delta) {
	_incYearDigitWithCarry(delta);
	return *this;
}

TDate&  TDate::DecYear(u16 delta) {
	_decYearDigitWithCarry(delta);
	return *this;
}

TDate  TDate::GetPrevDay() {
	TDate res(*this);
	res.DecDay();
	return res;
}

TDate TDate::GetNextDay() {
	TDate res(*this);
	res.IncDay();
	return res;
}

TDate TDate::GetNextMonth() {
	TDate res(*this);
	res.IncMonth();
	return res;
}

TDate TDate::GetPrevMonth() {
	TDate res(*this);
	res.DecMonth();
	return res;
}

TDate TDate::GetNextYear() {
	TDate res(*this);
	res.IncYear();
	return res;
}

TDate TDate::GetPrevYear() {
	TDate res(*this);
	res.DecYear();
	return res;
}


bool TDate::operator!=(const TDate& time1) const {
	return !IsEqual(time1);
}

bool TDate::operator==(const TDate& time1) const {
	return IsEqual(time1);
}

template <typename T>
struct pair {
	const T* max;
	const T* min;
};

u16 TDate::MonthBetween(const TDate& other_date) const {
	TDateTimeCompare sign = TDate::Compare(*this, other_date);

	if (sign == DATETIME_EQUAL) { return 0; }

	const auto [MaxTime, MinTime] = sign == DATETIME_FIRST_GREATER ? pair<TDate>{this, &other_date} :
									pair<TDate>{&other_date, this};
	u16 result = 0;
	u16 year = MinTime->Year;
	const u16 maxtime_prev_year = TDateTimeUtils::Prev(MaxTime->Year);

	while (year < maxtime_prev_year) {
		result += static_cast<u16>(MONTH_IN_YEAR);
		year++;
	}

	if (MaxTime->Year == MinTime->Year) {
		result += static_cast<u16>(MaxTime->Month - MinTime->Month);
	} else { //������� ���� ���
		result += static_cast<u16>(MONTH_IN_YEAR - MinTime->Month + MaxTime->Month);
	}

	return  result;
}

u16 TDate::DaysBetween(const TDate& time2) const {
	TDateTimeCompare sign = TDate::Compare(*this, time2);

	if (sign == DATETIME_EQUAL) { return 0; }

	const auto& [MaxTime, MinTime] = sign == DATETIME_FIRST_GREATER ? pair<TDate> {this, &time2} :
	                                 pair<TDate> {&time2, this};
	u16 result = 0;
	u16 year = MinTime->Year;
	const u16 maxtime_prevyear = TDateTimeUtils::Prev(MaxTime->Year);

	while (year < maxtime_prevyear) {
		bool is_leap = TDateTimeUtils::IsLeap(year);

		if (year == MinTime->Year && MinTime->Month > 2 && is_leap) { result -= 1; } //���� ���������� ������� (������� ��� ������) 2000/03(leap) -> x

		year++;
		result += is_leap ? static_cast<u16>(DAYS_IN_LPYEAR) : static_cast<u16>(DAYS_IN_YEAR);
	}

	if (result > 0 && TDateTimeUtils::IsLeap(maxtime_prevyear)) { result += 1; } //���� ������������� ��� ���� leap

	const u08 maxtime_prevmonth = TDateTimeUtils::Prev(MaxTime->Month);

	if (MaxTime->Year == MinTime->Year) {
		bool is_leap = TDateTimeUtils::IsLeap(MaxTime->Year);
		u08 month = MinTime->Month;

		while (month < maxtime_prevmonth) {
			result += TDateTimeUtils::DaysInMonth(month++, is_leap);
		}
	} else { //������� ���� ���
		bool is_leap = TDateTimeUtils::IsLeap(MaxTime->Year - 1);
		u08 month = MinTime->Month;

		while (month <= 12) {
			result += TDateTimeUtils::DaysInMonth(month++, is_leap);
		}

		//����� ����������� ������ ����
		is_leap = TDateTimeUtils::IsLeap(MaxTime->Year);
		month = 1;

		while (month < maxtime_prevmonth) {
			result += TDateTimeUtils::DaysInMonth(month++, is_leap);
		}
	}

	//������� ���
	if (MaxTime->Month == MinTime->Month) {
		// �� ����� ������� �� ������� 02->03 ������ ����������� ����
		if (result !=
		        0) { // ���� ������ ��� ���,� �� ������� ���������
			result += TDateTimeUtils::DaysInMonth(TDateTimeUtils::Month_Previous(MaxTime->Month),
			                                      MaxTime->Year);
			result -= MinTime->Day;
			result += MaxTime->Day;
		} else { //����� ����� ���� ������� � ��������� ����
			result += static_cast<u16>(MaxTime->Day - MinTime->Day);
		}
	} else { //������� ���� �������
		result += TDateTimeUtils::DaysInMonth(TDateTimeUtils::Month_Previous(MaxTime->Month),
		                                      MaxTime->Year);
		result -= MinTime->Day;
		result += MaxTime->Day;
	}

	return result;
}

u16 TDate::CalendarYearsBetween(const TDate& other_date) const {
	if (this->Year > other_date.Year) {
		return this->Year - other_date.Year;
	};

	return other_date.Year - this->Year;
}

bool TDate::IsDateValid() const {
	if ((u16)this->Year > YEARS_MAX || this->Year == 0) { return false; }

	if ((u08)this->Month > MONTH_IN_YEAR || (u08)this->Month == 0) { return false; }

	if ((u08)this->Day > TDateTimeUtils::DaysInMonth(this->Month, this->Year)) { return false; }

	return true;
}

bool TDate::ChangeYearDigit(s16 delta) {
	if (delta > 0) {
		return _incYearDigitWithCarry((u16)delta);
	} else {
		return _decYearDigitWithCarry((u16)(-delta));
	}
}

bool TDate::ChangeMonthDigit(s08 delta) {
	if (delta > 0) {
		return _incMonthDigitWithCarry((u08)delta);
	} else {
		return _decMonthDigitWithCarry((u08)(-delta));
	}
}

bool TDate::ChangeDayDigit(s08 delta) {
	if (delta > 0) {
		return _incDayDigitWithCarry((u08)delta);
	} else {
		return _decDayDigitWithCarry((u08)(-delta), true);
	}
}

bool TDate::operator<=(const TDate& time1) const {
	return this->_IsEarlyOrE_Than(time1);
}

bool TDate::operator<(const TDate& time1) const {
	return this->_IsEarly_Than(time1);
}

bool TDate::operator>=(const TDate& time1) const {
	return this->_IsLaterOrE_Than(time1);
}

bool TDate::operator>(const TDate& time1) const {
	return this->_IsLater_Than(time1);
}

bool TTime::operator!=(const TTime& time1) const {
	return !_IsEqual(time1);
}

bool TTime::operator==(const TTime& time1) const {
	return _IsEqual(time1);
}

bool TTime::_incHourWithCarry(u08 delta /*= 1*/) {
	if (!TDateTimeUtils::IncValue(this->Hour, (u08)(HOURS_IN_DAY - 1), delta)) { return false; } //NO 24 hour!

	this->Hour = 0;
	return true;
}

bool TTime::_decHourWithCarry(u08 delta /*= 1*/) {
	if (!TDateTimeUtils::DecValue(this->Hour, (u08)0, delta)) { return false; }

	this->Hour = HOURS_IN_DAY - 1;
	return true;
}

bool TTime::_incMinuteWithCarry(u08 delta /*= 1*/) {
	if (!TDateTimeUtils::IncValue(this->Minute, (u08)(MINUTES_IN_HOUR - 1), delta)) { return false; }

	this->Minute = 0;
	return true;
}

bool TTime::_decMinuteWithCarry(u08 delta /*= 1*/) {
	if (!TDateTimeUtils::DecValue(this->Minute, (u08)(0), delta)) { return false; }

	this->Minute = MINUTES_IN_HOUR - 1;
	return true;
}

bool TTime::_incSecondWithCarry(u08 delta /*= 1*/) {
	if (!TDateTimeUtils::IncValue(this->Second, (u08)(SECONDS_IN_MINUTE - 1), delta)) { return false; }

	this->Second = 0;
	return true;
}

bool TTime::_decSecondWithCarry(u08 delta /*= 1*/) {
	if (!TDateTimeUtils::DecValue(this->Second, (u08)(0), delta)) { return false; }

	this->Second = SECONDS_IN_MINUTE - 1;
	return true;
}

bool TTime::_incMillisWithCarry(u16 delta /*= 1*/) {
	if (!TDateTimeUtils::IncValue(this->Millis, (u16)(MILLIS_IN_SECOND - 1), delta)) { return false; }

	this->Millis = 0;
	return true;
}

bool TTime::_decMillisWithCarry(u16 delta /*= 1*/) {
	if (!TDateTimeUtils::DecValue(this->Millis, (u16)(0), delta)) { return false; }
	this->Millis = MILLIS_IN_SECOND - 1;
	return true;
}



TTime& TTime::IncSeconds() {
	if (!_incSecondWithCarry()) {
		return *this;
	}

	if (!_incMinuteWithCarry()) {
		return *this;
	}

	_incHourWithCarry();
	return *this;
}
TTime& TTime::DecSeconds() {
	if (!_decSecondWithCarry()) {
		return *this;
	}

	if (!_decMinuteWithCarry()) {
		return *this;
	}

	_decHourWithCarry();
	return *this;
}
TTime& TTime::IncMinutes() {
	if (!_incMinuteWithCarry()) {
		return *this;
	}

	_incHourWithCarry();
	return *this;
}
TTime& TTime::DecMinutes() {
	if (!_decMinuteWithCarry()) {
		return *this;
	}

	_decHourWithCarry();
	return *this;
}

TTime& TTime::IncHours() {
	_incHourWithCarry();
	return *this;
}
TTime& TTime::DecHours() {
	_decHourWithCarry();
	return *this;
}



TTime::TTime(u08 AHour, u08 AMinute, u08 ASecond, u16 AMillis) :
	 Millis(AMillis),Second(ASecond),Minute(AMinute),Hour(AHour) {}

TTime& TTime::Set(u08 AHour /*= 0*/, u08 AMinute /*= 0*/, u08 ASecond /*= 0*/,
                  u16 AMillis /*= 0*/) {
	Hour = AHour;
	Minute = AMinute;
	Second = ASecond;
	Millis = AMillis;
	return *this;
}

void TTime::Clear() {
	Millis = 0;
	Second = 0;
	Minute = 0;
	Hour = 0;
}

char* TTime::ToString(char* string) const {
	assert(false);//NYI
	return string;
	/*
		if (this->Hour <= 23) {
			itona(this->Hour, string, 2);
		} else {
			string[0] = 'x';
			string[1] = 'x';
		}

		string[2] = ':';

		if (this->Minute <= 59) {
			itona<u08>(this->Minute, (char*)(string + 3), 2);
		} else {
			string[3] = 'x';
			string[4] = 'x';
		}

		string[5] = '\0';
		return string;*/
}

u08 TTime::StringLen() {
	return 6;
}

TDateTimeCompare TTime::Compare(const TTime& time1, const TTime& time2) {
	if (time1.Hour > time2.Hour) { return DATETIME_FIRST_GREATER; }
	else if (time2.Hour > time1.Hour) { return DATETIME_SECOND_GREATER; }

	if (time1.Minute > time2.Minute) { return DATETIME_FIRST_GREATER; }
	else if (time2.Minute > time1.Minute) { return DATETIME_SECOND_GREATER; }

	if (time1.Second > time2.Second) { return DATETIME_FIRST_GREATER; }
	else if (time2.Second > time1.Second) { return DATETIME_SECOND_GREATER; }

	if (time1.Millis > time2.Millis) { return DATETIME_FIRST_GREATER; }
	else if (time2.Millis > time1.Millis) { return DATETIME_SECOND_GREATER; }

	return DATETIME_EQUAL;
}

bool TTime::_IsEqual(const TTime& time) const {
	return Compare(*this, time) == DATETIME_EQUAL;
}

bool TTime::_IsLater_Than(const TTime& other_time) const {
	return Compare(*this, other_time) == DATETIME_FIRST_GREATER;
}

bool TTime::_IsLaterOrE_Than(const TTime& other_time) const {
	TDateTimeCompare res = Compare(*this, other_time);
	return (res == DATETIME_FIRST_GREATER || res == DATETIME_EQUAL);
}

bool TTime::_IsEarly_Than(const TTime& other_time) const {
	return Compare(*this, other_time) == DATETIME_SECOND_GREATER;
}

bool TTime::_IsEarlyOrE_Than(const TTime& other_time) const {
	TDateTimeCompare res = Compare(*this, other_time);
	return (res == DATETIME_SECOND_GREATER || res == DATETIME_EQUAL);
}

s08 TTime::SecondsMoreThan(TTime& other_time) const {
	return (s08)((s08)this->Second - (s08)other_time.Second);
}

bool TTime::IsTimeValid() const {
	if (this->Hour >= HOURS_IN_DAY) { return false; }

	if (this->Minute >= MINUTES_IN_HOUR) { return false; }

	if (this->Second >= SECONDS_IN_MINUTE) { return false; }

	if (this->Millis >= MILLIS_IN_SECOND) { return false; }

	return true;
}

bool TTime::ChangeHourDigit(s08 delta) {
	if (delta > 0) {
		return _incHourWithCarry((u08)delta);
	} else {
		return _decHourWithCarry((u08) - delta);
	}
}

bool TTime::ChangeMinuteDigit(s08 delta) {
	if (delta > 0) {
		return _incMinuteWithCarry((u08)delta);
	} else {
		return _decMinuteWithCarry((u08) - delta);
	}
}

bool TTime::ChangeSecondDigit(s08 delta) {
	if (delta > 0) {
		return _incSecondWithCarry((u08)delta);
	} else {
		return _decSecondWithCarry((u08) - delta);
	}
}
bool TTime::ChangeMillisDigit(s16 delta) {
	if (delta > 0) {
		return _incMillisWithCarry((u08)delta);
	} else {
		return _decMillisWithCarry((u08) - delta);
	}
}

bool TTime::operator<=(const TTime& time1) const {
	return this->_IsEarlyOrE_Than(time1);
}

bool TTime::operator<(const TTime& time1) const {
	return this->_IsEarly_Than(time1);
}

bool TTime::operator>=(const TTime& time1) const {
	return this->_IsLaterOrE_Than(time1);
}

bool TTime::operator>(const TTime& time1) const {
	return this->_IsLater_Than(time1);
}



//====================================================================================




TDateTime::TDateTime(const u16 AYear, const u08 AMonth, const u08 ADay,
                     const u08 AHours /*= 0*/,
                     const u08 AMinutes /*= 0*/, const u08 ASeconds /*= 0*/, const u16 AMillis
                    ) : date(AYear, AMonth, ADay),
	time(AHours, AMinutes, ASeconds, AMillis) {
}
TDateTime::TDateTime(const TDate& dt): date(dt), time() {
}

TDateTime& TDateTime::Set(const u16 AYear, const u08 AMonth, const u08 ADay,
                          const u08 AHours /*= 0*/, const u08 AMinutes /*= 0*/, const u08 ASeconds /*= 0*/, const u16 AMillis
                         ) {
	date.Set(AYear, AMonth, ADay);
	time.Set(AHours, AMinutes, ASeconds, AMillis);
	return *this;
}

void TDateTime::FromNTPTime(u32 timestamp, s08 timezone) {
	//STATIC_ASSERT(1==1); //NOT YET TESTED!
	//��������� ���
	timestamp = static_cast<u32>((s32)(timestamp) + 60L * 60L * timezone);
	timestamp -= SECONDS_2014;
	this->date.Year = 2014;

	while (timestamp > TDateTimeUtils::SecondsInYear(this->date.Year)) {
		timestamp -= TDateTimeUtils::SecondsInYear(this->date.Year);
		this->date.Year++;
	}

	//��� ����. ��������� �����
	this->date.Month = 1;
	bool is_leap = TDateTimeUtils::IsLeap(this->date.Year);

	while (timestamp > TDateTimeUtils::SecondsInMonth(this->date.Month, is_leap)) {
		timestamp -= TDateTimeUtils::SecondsInMonth(this->date.Month, is_leap);
		this->date.Month++;
	}

	//����� ����.��������� ����
	this->date.Day = 1;

	while (timestamp > TO_SECONDS(1)) {
		timestamp -= TO_SECONDS(1);
		this->date.Day++;
	}

	this->time.Hour = static_cast<u08>(timestamp / (MINUTES_IN_HOUR * SECONDS_IN_MINUTE));
	timestamp -= this->time.Hour * (MINUTES_IN_HOUR * SECONDS_IN_MINUTE);
	this->time.Minute = static_cast<u08>(timestamp / MINUTES_IN_HOUR);
	timestamp -= this->time.Minute * SECONDS_IN_MINUTE;
	this->time.Second = static_cast<u08>(timestamp);
}

void TDateTime::ClearDateTime() {
	date.Clear();
	time.Clear();
}

u08 TDateTime::StringLen() {
	return (u08)(TDate::StringLen() - (u08)1/*delete nullterminator*/ + (u08)1 + TTime::StringLen());
}

char* TDateTime::DateTimeToString(char string[15]) const {
	this->date.ToString(string);
	string[TDate::StringLen() - 1] = ',';
	this->time.ToString(string + TDate::StringLen());
	return string;
}


bool TDateTime::IsValid() const {
	return (date.IsDateValid() && time.IsTimeValid());
}

TDateTimeCompare TDateTime::Compare(const TDateTime& time1, const TDateTime& time2) {
	TDateTimeCompare dates = TDate::Compare(time1.date, time2.date);

	if (dates != DATETIME_EQUAL) { return dates; }

	TDateTimeCompare times = TTime::Compare(time1.time, time2.time);
	return times;
}

bool TDateTime::_IsLater_Than(const TDateTime& other_datetime) const {
	return TDateTime::Compare(*this, other_datetime) == DATETIME_FIRST_GREATER;
}

bool TDateTime::operator!=(const TDateTime& time1) const {
	return !_IsEqual(time1);
}

bool TDateTime::operator==(const TDateTime& time1) const {
	return _IsEqual(time1);
}

bool TDateTime::_IsLaterOrE_Than(const TDateTime& other_datetime) const {
	TDateTimeCompare res = TDateTime::Compare(*this, other_datetime);
	return (res == DATETIME_FIRST_GREATER || res == DATETIME_EQUAL);
}

bool TDateTime::_IsEarly_Than(const TDateTime& other_datetime) const {
	return TDateTime::Compare(*this, other_datetime) == DATETIME_SECOND_GREATER;
}

bool TDateTime::_IsEarlyOrE_Than(const TDateTime& other_datetime) const {
	TDateTimeCompare res = TDateTime::Compare(*this, other_datetime);
	return (res == DATETIME_SECOND_GREATER || res == DATETIME_EQUAL);
}

bool TDateTime::operator<=(const TDateTime& time1) const {
	return this->_IsEarlyOrE_Than(time1);
}

bool TDateTime::operator<(const TDateTime& time1) const {
	return this->_IsEarly_Than(time1);
}

bool TDateTime::operator>=(const TDateTime& time1) const {
	return this->_IsLaterOrE_Than(time1);
}

bool TDateTime::operator>(const TDateTime& time1) const {
	return this->_IsLater_Than(time1);
}










bool TDateTime::_IsEqual(const TDateTime& Adt) const {
	return time == Adt.time && date == Adt.date;
}


s08 TDateTime::HoursBetween_MaxDay(const TDateTime& Atime) const {
	u08 result = 0;
	TDateTimeCompare sign = TDateTime::Compare(*this, Atime);

	if (sign == DATETIME_EQUAL) { return 0; }

	const auto [MaxTime, MinTime] = sign == DATETIME_FIRST_GREATER ? pair<TDateTime> {this, &Atime} :
	                                 pair<TDateTime> {&Atime, this};

	if (MaxTime->date == MinTime->date) {
		if (MaxTime->time.Hour == MinTime->time.Hour) {
			return 0;
		} else {
			result = static_cast<u08>(MaxTime->time.Hour - MinTime->time.Hour);
		}
	} else { //������ ����
		if (MaxTime->date.IsNextDayThan(MinTime->date)) {
			result = static_cast<u08>(HOURS_IN_DAY - MinTime->time.Hour + MaxTime->time.Hour);
		} else {
			result = HOURS_IN_DAY;
		}
	}

	if (result > HOURS_IN_DAY) { result = HOURS_IN_DAY; }  //� (*) � (**) ����� ��������� ������

	return static_cast<s08>(sign * result);
}

s08 TDateTime::MinutesBetween_MaxHour(const TDateTime& other_time)const {
	u16 result = 0;
	TDateTimeCompare sign = TDateTime::Compare(*this, other_time);

	if (sign == DATETIME_EQUAL) { return 0; }

	const auto [MaxTime, MinTime] = sign == DATETIME_FIRST_GREATER ? pair<TDateTime> {this, &other_time} :
	                                 pair<TDateTime> {&other_time, this};

	//���� ���������
	if (MaxTime->date == MinTime->date) {
		u08 diff_hour = static_cast<u08>(MaxTime->time.Hour - MinTime->time.Hour);

		if (diff_hour == 0) { //hour equals
			result = static_cast<u16>(MaxTime->time.Minute - MinTime->time.Minute);
		} else if (diff_hour > 1) {
			result = MINUTES_IN_HOUR;
		} else { //==1
			result = static_cast<u16>(MINUTES_IN_HOUR - MinTime->time.Minute + MaxTime->time.Minute); //(*)
		}
	} else {
		//���� ����������
		if (MinTime->time.Hour == HOURS_IN_DAY - 1 && MaxTime->date.IsNextDayThan(MinTime->date)) {
			//������� � ���� ����
			if (MaxTime->time.Hour == 0) { //������ ��� ���
				result = static_cast<u16>(MINUTES_IN_HOUR - MinTime->time.Minute + MaxTime->time.Minute); //(**)
			} else { //�� ������ ���
				result = MINUTES_IN_HOUR;
			}
		} else { //������� � ��������� ����
			result = MINUTES_IN_HOUR;
		}
	}

	if (result > MINUTES_IN_HOUR) { result = MINUTES_IN_HOUR; }  //� (*) � (**) ����� ��������� ������

	s08 signed_result = (s08)result;
	return (s08)((s08)sign * signed_result);
}


TDateTime& TDateTime::IncDateTimeMillis(u16 delta) {
	assert(delta <= MILLIS_IN_SECOND);

	if (!time._incMillisWithCarry(delta)) { return *this; }

	return IncDateTimeSeconds();
}

TDateTime& TDateTime::DecDateTimeMillis(u16 delta) {
	assert(delta <= MILLIS_IN_SECOND);

	if (!time._decMillisWithCarry(delta)) { return *this; }
	return DecDateTimeSeconds();
}
TDateTime& TDateTime::IncDateTimeSeconds(u08 delta ) {
	assert(delta <= SECONDS_IN_MINUTE);

	if (!time._incSecondWithCarry(delta)) { return *this; }

	return IncDateTimeMinutes();
}
TDateTime& TDateTime::DecDateTimeSeconds(u08 delta ) {
	assert(delta <= SECONDS_IN_MINUTE);

	if (!time._decSecondWithCarry(delta)) { return *this; }

	return DecDateTimeMinutes();
}
TDateTime& TDateTime::IncDateTimeMinutes(u08 delta ) {
	assert(delta <= MINUTES_IN_HOUR);

	if (!time._incMinuteWithCarry(delta)) { return *this; }

	return IncDateTimeHours();
}
TDateTime& TDateTime::DecDateTimeMinutes(u08 delta ) {
	assert(delta <= MINUTES_IN_HOUR);

	if (!time._decMinuteWithCarry(delta)) { return *this; }

	return DecDateTimeHours();
}
TDateTime& TDateTime::IncDateTimeHours(u08 delta ) {
	assert(delta <= HOURS_IN_DAY);

	if (!time._incHourWithCarry(delta)) { return *this; }

	date.IncDay();
	return *this;
}
TDateTime& TDateTime::DecDateTimeHours(u08 delta ) {
	assert(delta <= HOURS_IN_DAY);

	if (!time._decHourWithCarry(delta)) { return *this; }

	date.DecDay();
	return *this;
}