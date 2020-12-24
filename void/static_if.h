#pragma once

namespace vd {

	namespace details {
		template<bool condition, class TypeIfTrue, class TypeIfFale>
		struct _static_if {
			using value = TypeIfTrue;
		};

		template<class TypeIfTrue, class TypeIfFalse>
		struct _static_if <false, TypeIfTrue, TypeIfFalse> {
			using value = TypeIfFalse;
		};
	}

	template<bool condition, class TypeIfTrue, class TypeIfFalse>
	using static_if = typename details::_static_if<condition, TypeIfTrue, TypeIfFalse>;
	template<bool condition, class TypeIfTrue, class TypeIfFalse>
	using static_if_v = typename details::_static_if<condition, TypeIfTrue, TypeIfFalse>::value;
}
