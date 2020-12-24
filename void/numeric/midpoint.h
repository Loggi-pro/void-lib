#include <stdint.h>
#include <void/math.h>
#include <void/type_traits.h>
#include <void/limits.h>



namespace vd {


	template<typename _Int>
	constexpr vd::enable_if_t < vd::is_integral_v<_Int>
	&& !vd::is_same_v<_Int, bool>, _Int > midpoint(_Int a, _Int b) noexcept {
		using _UInt = vd::make_unsigned_t<_Int>;
		const auto ua = _UInt(a);
		const auto ub = _UInt(b);

		if (ub > ua) {
			return _Int(_UInt(a) + (_UInt(b) - _UInt(a)) / 2);
		} else {
			return _Int(_UInt(b) + (_UInt(a) - _UInt(b)) / 2);
		}
	}

	// What about infinity?
	template<typename _Float>
	constexpr vd::enable_if_t<vd::is_floating_point_v<_Float>, _Float> midpoint(_Float a,
	        _Float b) noexcept {
		if (vd::isnan(a) || vd::isnan(b)) {
			return vd::numeric_limits<_Float>::quiet_NaN();
		} else {
			return vd::isnormal(a) && vd::isnormal(b)
			       ? a / 2 + b / 2
			       : (a + b) / 2;
		}
	}

	template<typename _Tp>
	constexpr _Tp* midpoint(_Tp* a, _Tp* b) {
		//using _Iptr = std::intptr_t;
		//return static_cast<_Tp*>(a + std::midpoint(_Iptr(a), _Iptr(b)));
		const auto diff = (b - a) / 2;
		return a + diff;
	}

} // namespace std
