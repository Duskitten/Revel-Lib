#ifndef INCLUDE_REVEL_LIB_FONT2D
#define INCLUDE_REVEL_LIB_FONT2D

#if __cplusplus__
extern "C"{
#endif

#include "../../revel-define.h"

//include Revel libs
#include "../basic/coreobject.h"
#include "../basic/texture.h"

typedef struct {
    CoreObject* core;
    char characters;
    ScePspFVector2 character_size;
    ScePspFVector2 character_spacing;
    ScePspFVector2 character_size;
    void* character_uv_map;
} Font2D;


#if __cplusplus__
};
#endif
#endif
