#pragma once
#include <void/math.h>
#include <void/type_traits.h>
#include <void/limits.h>
namespace vd {

	template<typename _Float>
	constexpr vd::enable_if_t<vd::is_floating_point_v<_Float>, _Float>
	lerp(_Float __a, _Float __b, _Float __t) {
		if (vd::isnan(__a) || vd::isnan(__b) || vd::isnan(__t))
		{ return vd::numeric_limits<_Float>::quiet_NaN(); }
		else if ((__a <= _Float{0} && __b >= _Float{0})
		         || (__a >= _Float{0} && __b <= _Float{0}))
			// ab <= 0 but product could overflow.
		#ifndef FMA
			return __t * __b + (_Float {1} - __t) * __a;
		#else
			return vd::fma(__t, __b, (_Float {1} - __t) * __a);
		#endif
		else if (__t == _Float {1})
			return __b;
		else {
			// monotonic near t == 1.
			#ifndef FMA
			const auto __x = __a + __t * (__b - __a);
			#else
			const auto __x = vd::fma(__t, __b - __a, __a);
			#endif
			return (__t > _Float {1}) == (__b > __a)
			       ? vd::max(__b, __x)
			       : vd::min(__b, __x);
		}
	}

} // namespace vd