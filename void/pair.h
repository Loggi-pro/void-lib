#pragma once

/*!
	\defgroup Pair Pair
	\ingroup Types
	\brief Simple pair type
	@{
	@file
*/

namespace vd {
	template <class T1,class T2>
	struct pair {
		T1 first;
		T2 second;
	};
	
}

//!@}