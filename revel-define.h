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

#if __cplusplus__
};
#endif
#endif

