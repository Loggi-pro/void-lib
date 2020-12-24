#pragma once
#include <void/platform_specific.h>
#ifdef _UNITY //Trap for unity
	#include "unity/unity_fixture.h"
	#ifdef assert
		#undef assert
	#endif

	#define assert(x) {if (x){} else {\
				UnitySetAssertStatus(1,__FILE__,__LINE__);\
				if (!UnityIsExpectAssert()){\
					EXPECT_NO_ASSERT(false);\
				}\
			}\
		}
#else
#ifndef assert
#define assert(x) {if(x){} else{ assert_failed(__FILE__, __LINE__);}}
#endif
#endif
