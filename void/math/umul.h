#pragma once


//Multiply integer value by float number (division by power of 2) with resolution of 1/256
	
#define UMUL256(CHISLO_INT,CONST_FLOAT) (((CHISLO_INT) * (int)((CONST_FLOAT) * 256 + 0.5)) >> 8)
namespace vd {
	
template <typename T>
constexpr T umul256(T a, float b){
    return (((a)*(T)((b)*256.0f+0.5f))>>8);
}

}