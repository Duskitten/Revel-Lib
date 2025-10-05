#ifndef INCLUDE_REVEL_LIB_SPRITE2D
#define INCLUDE_REVEL_LIB_SPRITE2D

#if __cplusplus__
extern "C"{
#endif

#include "../../revel-lib.h"
#include "../resource/texture.h"
typedef struct {
    CoreObject* object;
    Vector2 uv;
    Texture* tex;
} Sprite2D;

#if __cplusplus__
};
#endif
#endif
