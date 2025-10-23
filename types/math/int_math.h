#ifndef INCLUDE_REVEL_LIB_INTMATH
#define INCLUDE_REVEL_LIB_INTMATH

#if __cplusplus__
extern "C"{
#endif

//Include Revel Libs
#include "../../revel-define.h"

// Found here: https://stackoverflow.com/questions/427477/fastest-way-to-clamp-a-real-fixed-floating-point-value
// And modified for Revel Lib
int clamp_int(int value, int min_val, int max_val) {
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