#ifndef INCLUDE_REVEL_LIB_FLOATMATH
#define INCLUDE_REVEL_LIB_FLOATMATH

#if __cplusplus__
extern "C"{
#endif

//Include Revel Libs
#include "../../revel-define.h"

// Found here: https://stackoverflow.com/questions/4353525/floating-point-linear-interpolation
float lerp_float(float a, float b, float f)
{
    return a * (1.0 - f) + (b * f);
}

// Found here: https://stackoverflow.com/questions/427477/fastest-way-to-clamp-a-real-fixed-floating-point-value
float clamp_float(float value, float min_val, float max_val) {
    if (value < min_val) {
        return min_val;
    } else if (value > max_val) {
        return max_val;
    } else {
        return value;
    }
}

#if __cplusplus__
};
#endif


#endif