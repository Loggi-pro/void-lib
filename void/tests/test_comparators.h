#pragma once
namespace {
	constexpr int x = 3;
	static_assert(x == vd::any_of(1, 3, 5));
	//static_assert(x == vd::all_of(3, 3, 3));
	static_assert(x == vd::none_of(1, 2, 4));
	static_assert(!(x == vd::none_of(1, 2, 3)));
	//static_assert(x < vd::vd::none_of(1));

	template <int I>
	static constexpr auto add = [](auto v) -> decltype(v + I) { return v + I; };

	static_assert(x == vd::any_of(1, 3, 5));
	static_assert(!(x == vd::any_of(1, 2, 5)));
	static_assert(x != vd::any_of(1, 2, 5));
	static_assert(!(x != vd::any_of(1, 3, 5)));

	static_assert(x < vd::any_of(5, 3, 2, 4));
	static_assert(!(x < vd::any_of(0, 1, 2, 3)));

	static_assert(x <= vd::any_of(6, 5, 3, 4));
	static_assert(!(x <= vd::any_of(0, 1, 2)));

	static_assert(x > vd::any_of(0, 1, 2));
	static_assert(!(x > vd::any_of(4, 3, 5, 6)));

	static_assert(x >= vd::any_of(0, 3, 1, 2));
	static_assert(!(x >= vd::any_of(4, 5, 6)));

	static_assert(x == vd::all_of(3, 3, 3));
	static_assert(!(x == vd::all_of(3, 2, 3)));
	static_assert(x != vd::all_of(3, 2, 3));
	static_assert(!(x != vd::all_of(3, 3, 3)));

	static_assert(x < vd::all_of(4, 5, 6));
	static_assert(!(x < vd::all_of(3, 4, 5, 6)));

	static_assert(x <= vd::all_of(4, 5, 6, 3));
	static_assert(!(x <= vd::all_of(4, 5, 6, 2)));

	static_assert(x > vd::all_of(0, 1, 2));
	static_assert(!(x > vd::all_of(3, 0, 1, 2)));

	static_assert(x >= vd::all_of(0, 3, 1, 2));
	static_assert(!(x >= vd::all_of(0, 4, 1, 2)));




	static_assert(x == vd::none_of(1, 2, 4));
	static_assert(!(x == vd::none_of(1, 3, 4)));
	static_assert(x != vd::none_of(1, 2, 4, 3));
	static_assert(!(x != vd::none_of(1, 2, 4)));

	static_assert(x < vd::none_of(0, 1, 2, 3));
	static_assert(!(x < vd::none_of(4, 0, 1, 2)));

	static_assert(x <= vd::none_of(0, 1, 2));
	static_assert(!(x <= vd::none_of(0, 1, 2, 3)));

	static_assert(x > vd::none_of(3, 4, 5));
	static_assert(!(x > vd::none_of(3, 2, 4, 5)));

	static_assert(x >= vd::none_of(4, 5, 6));
	static_assert(!(x >= vd::none_of(6, 4, 5, 3)));
}
