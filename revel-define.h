#ifndef INCLUDE_REVEL_LIB_REDEFINE
#define INCLUDE_REVEL_LIB_REDEFINE

#if __cplusplus__
extern "C"{
#endif

//Add STB Lib
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

//Add PSP libs
#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspgu.h>
#include <pspgum.h>
#include <pspdebug.h>

//Add Other libs
#include <string.h>
#include <malloc.h>

// Found here: https://stackoverflow.com/questions/4353525/floating-point-linear-interpolation
float lerp(float a, float b, float f)
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

