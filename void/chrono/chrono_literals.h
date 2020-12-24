#pragma once

template <uint32_t TIME>
struct hours_l { /*: public Duration<Private::Period_hours>*/
		typedef Private::Period_hours SelfPeriod;
		typedef SelfPeriod PeriodInfo;
	private:
		//	hours_l() {}
	public:
		_MB_CONSTEXPR hours_l() {}
		enum {
			static_value = TIME
		};
		typedef hours_l <
		Private::PeriodConverter<TIME, SelfPeriod, Private::Period_hours>::result > to_hours;
		typedef minutes_l <
		Private::PeriodConverter<TIME, SelfPeriod, Private::Period_minutes>::result > to_minutes;
		typedef seconds_l <
		Private::PeriodConverter < TIME, SelfPeriod, Private::Period_seconds>::result > to_seconds;
		typedef milli_l <
		Private::PeriodConverter < TIME, SelfPeriod, Private::Period_milli>::result > to_milli;
		typedef micro_l <
		Private::PeriodConverter < TIME, SelfPeriod, Private::Period_micro>::result > to_micro;

};
template <uint32_t TIME>
struct minutes_l { /*: public Duration<Private::Period_minutes>*/
		typedef Private::Period_minutes SelfPeriod;
		typedef SelfPeriod PeriodInfo;
	private:
		//minutes_l() {}
	public:
		_MB_CONSTEXPR minutes_l() {}
		enum {
			static_value = TIME
		};
		typedef hours_l <
		Private::PeriodConverter<TIME, SelfPeriod, Private::Period_hours>::result > to_hours;
		typedef minutes_l <
		Private::PeriodConverter<TIME, SelfPeriod, Private::Period_minutes>::result > to_minutes;
		typedef seconds_l <
		Private::PeriodConverter < TIME, SelfPeriod, Private::Period_seconds>::result > to_seconds;
		typedef milli_l <
		Private::PeriodConverter < TIME, SelfPeriod, Private::Period_milli>::result > to_milli;
		typedef micro_l <
		Private::PeriodConverter < TIME, SelfPeriod, Private::Period_micro>::result > to_micro;
};
template <uint32_t TIME>
struct seconds_l { /*: public Duration<Private::Period_seconds>*/
		typedef Private::Period_seconds SelfPeriod;
		typedef SelfPeriod PeriodInfo;

	private:
		//seconds_l() {}
	public:
		_MB_CONSTEXPR seconds_l() {}
		enum {
			static_value = TIME
		};
		typedef hours_l <
		Private::PeriodConverter<TIME, SelfPeriod, Private::Period_hours>::result > to_hours;
		typedef minutes_l <
		Private::PeriodConverter<TIME, SelfPeriod, Private::Period_minutes>::result > to_minutes;
		typedef seconds_l <
		Private::PeriodConverter < TIME, SelfPeriod, Private::Period_seconds>::result > to_seconds;
		typedef milli_l <
		Private::PeriodConverter < TIME, SelfPeriod, Private::Period_milli>::result > to_milli;
		typedef micro_l <
		Private::PeriodConverter < TIME, SelfPeriod, Private::Period_micro>::result > to_micro;

};
template <uint32_t TIME>
struct milli_l { /*: public Duration<Private::Period_milli> */
		typedef Private::Period_milli SelfPeriod;
		typedef SelfPeriod PeriodInfo;
	private:
		//milli_l() {}
	public:
		_MB_CONSTEXPR milli_l() {}
		enum {
			static_value = TIME
		};
		typedef hours_l <
		Private::PeriodConverter<TIME, SelfPeriod, Private::Period_hours>::result > to_hours;
		typedef minutes_l <
		Private::PeriodConverter<TIME, SelfPeriod, Private::Period_minutes>::result > to_minutes;
		typedef seconds_l <
		Private::PeriodConverter < TIME, SelfPeriod, Private::Period_seconds>::result > to_seconds;
		typedef milli_l <
		Private::PeriodConverter < TIME, SelfPeriod, Private::Period_milli>::result > to_milli;
		typedef micro_l <
		Private::PeriodConverter < TIME, SelfPeriod, Private::Period_micro>::result > to_micro;
};
template <uint32_t TIME>
struct micro_l { /* : public Duration<Private::Period_micro>*/
		typedef Private::Period_micro SelfPeriod;
		typedef SelfPeriod PeriodInfo;
	private:
		//micro_l() {}
	public:
		_MB_CONSTEXPR micro_l() {}
		enum {
			static_value = TIME
		};
		typedef hours_l <
		Private::PeriodConverter<TIME, SelfPeriod, Private::Period_hours>::result > to_hours;
		typedef minutes_l <
		Private::PeriodConverter<TIME, SelfPeriod, Private::Period_minutes>::result > to_minutes;
		typedef seconds_l <
		Private::PeriodConverter < TIME, SelfPeriod, Private::Period_seconds>::result > to_seconds;
		typedef milli_l <
		Private::PeriodConverter < TIME, SelfPeriod, Private::Period_milli>::result > to_milli;
		typedef micro_l <
		Private::PeriodConverter < TIME, SelfPeriod, Private::Period_micro>::result > to_micro;

};

namespace literals {}

#ifdef _VOID_NATIVE_CPP17_CONSTEXPR_SUPPORT
namespace Private {
	template <uint32_t V>
	constexpr uint32_t make_uint32_t() {
		return V;
	}

	template <uint32_t V, char C, char... Cs>
	constexpr uint32_t make_uint32_t() {
		return make_uint32_t < 10 * V + C - '0', Cs... > ();
	}
}
namespace literals {
	template <char...Cs>
	constexpr auto operator "" _h() {
		const uint32_t time = Private::make_uint32_t<0, Cs...>();
		return hours_t(time);
		//return hours_l<time> {};
	}

	template <char...Cs>
	constexpr auto operator "" _m() {
		const uint32_t time = Private::make_uint32_t<0, Cs...>();
		return minutes_t(time);
		//return minutes_l<time> {};
	}

	template <char...Cs>
	constexpr auto operator "" _s() {
		const uint32_t time = Private::make_uint32_t<0, Cs...>();
		return seconds_t(time);
		//return seconds_l<time> {};
	}
	template <char...Cs>
	constexpr auto operator "" _ms() {
		const uint32_t time = Private::make_uint32_t<0, Cs...>();
		return milli_t(time);
		//	return milli_l<time> {};
	}

	template <char...Cs>
	constexpr auto operator "" _us() {
		const uint32_t time = Private::make_uint32_t<0, Cs...>();
		return micro_t(time);
		//	return micro_l<time> {};
	}
}
#endif
