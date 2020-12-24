
template <uint32_t _Num, uint32_t _Denom = 1> struct Ratio {
	static const uint32_t Num = _Num;
	static const uint32_t Denom = _Denom;
};

template <class Period1, class Period2>
struct MinTrait {}; //period comparator


template<typename T, typename U>
struct is_same {
	static const bool value = false;
};

template<typename T>
struct is_same<T, T> { //specialization
	static const bool value = true;
};

template <class Period = Ratio<1, 1>>
class Duration {
		uint32_t _val;
	public:
		typedef Period PeriodInfo;
		_MB_CONSTEXPR uint32_t  count()const {
			return _val;
		}

		_MB_CONSTEXPR Duration(): _val(0) {}

		//For literal operator time support (like _ms,_h etc.)
		_MB_CONSTEXPR Duration(uint32_t val): _val(val) {
		}

		template<class Period2 >
		_MB_CONSTEXPR Duration(const Duration<Period2>& d): _val((d.count() * Period2::Num *
			        Period::Denom) / (Period2::Denom * Period::Num)) {
			/*typedef MinTrait <Duration<Period>, Duration<Period2>>::min minDuration;
			const bool isStricted = is_same<minDuration, Duration<Period2>>::value
			                        && !is_same<Period, Period2>::value;
			VOID_STATIC_ASSERT(isStricted == true);*/
			if (d.count() != 0) {
				assert(_val !=
				       0); //????????? ???????? ??-?? ????????? ?????. ?.?. ? ???????? ???? ???? ????????? ???????? ? ???????? ??????? ?????
			}
		}
		Duration operator+(const Duration& d) const {
			Duration res(_val);
			res += d._val;
			return res;
		}
		Duration operator+(const uint32_t& rhs)const {
			Duration res(_val);
			res._val += rhs;
			return res;
		}
		Duration operator-(const Duration& d) const {
			Duration res(_val);
			res._val -= d._val;
			return res;
		}

		Duration operator-(const uint32_t& rhs) const {
			Duration res(_val);
			res._val -= rhs;
			return res;
		}

		Duration operator*(const uint32_t& rhs) const {
			Duration res(_val);
			res._val *= rhs;
			return res;
		}
		Duration operator/(const uint32_t& rhs) const {
			Duration res(_val);
			res._val /= rhs;
			return res;
		}
		Duration operator%(const uint32_t& rhs) const {
			Duration res(_val);
			res._val %= rhs;
			return res;
		}
		Duration& operator+=(const Duration& d) {
			_val += d._val;
			return *this;
		}
		Duration& operator+=(const uint32_t& rhs) {
			_val += rhs;
			return *this;
		}
		Duration& operator-=(const Duration& d) {
			assert(_val >= d._val);
			_val -= d._val;
			return *this;
		}
		Duration& operator-=(const uint32_t& rhs) {
			assert(_val >= rhs);
			_val -= rhs;
			return *this;
		}

		Duration& operator*=(const uint32_t& rhs) {
			_val *= rhs;
			return *this;
		}

		Duration& operator/=(const uint32_t& rhs) {
			_val /= rhs;
			return *this;
		}
		Duration& operator%=(const uint32_t& rhs) {
			_val %= rhs;
			return *this;
		}
		Duration& operator++() {
			_val++;
			return *this;
		}
		Duration operator++(int) {
			Duration<Period> result(*this);
			_val++;
			return result;
		}
		Duration& operator--() {
			_val--;
			return *this;
		}
		Duration operator--(int) {
			Duration<Period> result(*this);
			_val--;
			return result;
		}


};


namespace Private {
	typedef Ratio<1000UL * 60UL * 60UL, 1> Period_hours;
	typedef Ratio<1000UL * 60UL, 1> Period_minutes;
	typedef Ratio<1000UL, 1> Period_seconds;
	typedef Ratio<1, 1> Period_milli;
	typedef Ratio<1, 1000UL> Period_micro;

	template <uint32_t value, class FromPeriod, class ToPeriod>
	struct PeriodConverter {
		enum {
			result = (value * FromPeriod::Num * ToPeriod::Denom) / (FromPeriod::Denom * ToPeriod::Num)
		};
	};

}




template < class Period1, class Period2>
bool operator==(const Duration< Period1>& lhs, const Duration<Period2>& rhs) {
	typedef typename MinTrait<Duration< Period1>, Duration<Period2>>::min minDuration;
	return minDuration(lhs).count() == minDuration(rhs).count();
}
template < class Period1, class Period2>
bool operator!=(const Duration< Period1>& lhs, const Duration< Period2>& rhs) {
	typedef typename MinTrait<Duration< Period1>, Duration<Period2>>::min minDuration;
	return minDuration(lhs).count() != minDuration(rhs).count();
}
template < class Period1, class Period2>
bool operator<(const Duration< Period1>& lhs, const Duration< Period2>& rhs) {
	typedef typename MinTrait<Duration< Period1>, Duration<Period2>>::min minDuration;
	return minDuration(lhs).count() < minDuration(rhs).count();
}
template < class Period1, class Period2>
bool operator<=(const Duration< Period1>& lhs, const Duration< Period2>& rhs) {
	typedef typename MinTrait<Duration< Period1>, Duration<Period2>>::min minDuration;
	return minDuration(lhs).count() <= minDuration(rhs).count();
}
template < class Period1, class Period2>
bool operator>(const Duration< Period1>& lhs, const Duration< Period2>& rhs) {
	typedef typename MinTrait<Duration< Period1>, Duration<Period2>>::min minDuration;
	return minDuration(lhs).count() > minDuration(rhs).count();
}
template < class Period1, class Period2>
bool operator>=(const Duration< Period1>& lhs, const Duration< Period2>& rhs) {
	typedef typename MinTrait<Duration< Period1>, Duration<Period2>>::min minDuration;
	return minDuration(lhs).count() >= minDuration(rhs).count();
}