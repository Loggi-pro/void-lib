#pragma once

/*!
	@addtogroup utilities
	@{
	@file
*/

//! \ingroup utilities
//! \brief Macros to make structure packed
//! \code
//! PACKED(
//!	struct S {
//!		int a;
//!	});
//! \endcode
#ifdef _PACKED
	#define PACKED(x) _PACKED(x)
#else
	#error "PACKED macros is not supported for this platform. Platform specific files must provie _PACKED macros."
#endif

//! @}