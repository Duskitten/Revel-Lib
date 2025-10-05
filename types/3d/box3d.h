#ifndef INCLUDE_REVEL_LIB_BOX3D
#define INCLUDE_REVEL_LIB_BOX3D

#if __cplusplus__
extern "C"{
#endif

#include "../../revel-define.h"
#include "../basic/coreobject.h"
#include "../basic/texture.h"

typedef struct {
    CoreObject* object;
    Vector2 uv;
    Vector3 size;
    Texture* tex;
    void* data;
} Box3D;

#if __cplusplus__
};
#endif
#endif
