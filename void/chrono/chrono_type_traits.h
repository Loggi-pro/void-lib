

//minimum trait
template <class Period1, class Period2> struct MinTrait;

template <> struct MinTrait<vd::chrono::micro_t, vd::chrono::micro_t> {
	typedef vd::chrono::micro_t min;
	typedef vd::chrono::micro_t max;
};
template <> struct MinTrait <vd::chrono::micro_t, vd::chrono::milli_t > {
	typedef vd::chrono::micro_t min;
	typedef vd::chrono::milli_t max;
};
template <> struct MinTrait <vd::chrono::micro_t, vd::chrono::seconds_t > {
	typedef vd::chrono::micro_t min;
	typedef vd::chrono::seconds_t max;
};
template <> struct MinTrait <vd::chrono::micro_t, vd::chrono::minutes_t > {
	typedef vd::chrono::micro_t min;
	typedef vd::chrono::minutes_t max;
};
template <> struct MinTrait <vd::chrono::micro_t, vd::chrono::hours_t > {
	typedef  vd::chrono::micro_t min;
	typedef vd::chrono::hours_t max;
};
//
template <> struct MinTrait <vd::chrono::milli_t, vd::chrono::micro_t > {
	typedef vd::chrono::micro_t min;
	typedef vd::chrono::milli_t max;
};
template <> struct MinTrait <vd::chrono::milli_t, vd::chrono::milli_t > {
	typedef vd::chrono::milli_t min;
	typedef vd::chrono::milli_t max;
};
template <> struct MinTrait <vd::chrono::milli_t, vd::chrono::seconds_t > {
	typedef vd::chrono::milli_t min;
	typedef vd::chrono::seconds_t max;
};
template <> struct MinTrait <vd::chrono::milli_t, vd::chrono::minutes_t > {
	typedef vd::chrono::milli_t min;
	typedef vd::chrono::minutes_t max;
};
template <> struct MinTrait <vd::chrono::milli_t, vd::chrono::hours_t > {
	typedef vd::chrono::milli_t min;
	typedef vd::chrono::hours_t max;
};
//
template <> struct MinTrait <vd::chrono::seconds_t, vd::chrono::micro_t > {
	typedef vd::chrono::micro_t min;
	typedef vd::chrono::seconds_t max;
};
template <> struct MinTrait <vd::chrono::seconds_t, vd::chrono::milli_t > {
	typedef vd::chrono::milli_t min;
	typedef vd::chrono::seconds_t max;
};
template <> struct MinTrait <vd::chrono::seconds_t, vd::chrono::seconds_t > {
	typedef vd::chrono::seconds_t min;
	typedef vd::chrono::seconds_t max;
};
template <> struct MinTrait <vd::chrono::seconds_t, vd::chrono::minutes_t > {
	typedef vd::chrono::seconds_t min;
	typedef vd::chrono::minutes_t max;
};
template <> struct MinTrait <vd::chrono::seconds_t, vd::chrono::hours_t > {
	typedef vd::chrono::seconds_t min;
	typedef vd::chrono::hours_t max;
};
//
template <> struct MinTrait <vd::chrono::hours_t, vd::chrono::micro_t > {
	typedef vd::chrono::micro_t min;
	typedef vd::chrono::hours_t max;
};
template <> struct MinTrait <vd::chrono::hours_t, vd::chrono::milli_t > {
	typedef vd::chrono::milli_t min;
	typedef vd::chrono::hours_t max;
};
template <> struct MinTrait <vd::chrono::hours_t, vd::chrono::seconds_t > {
	typedef vd::chrono::seconds_t min;
	typedef vd::chrono::hours_t max;
};
template <> struct MinTrait <vd::chrono::hours_t, vd::chrono::minutes_t > {
	typedef vd::chrono::minutes_t min;
	typedef vd::chrono::hours_t max;
};
template <> struct MinTrait <vd::chrono::hours_t, vd::chrono::hours_t > {
	typedef vd::chrono::hours_t min;
	typedef vd::chrono::hours_t max;
};