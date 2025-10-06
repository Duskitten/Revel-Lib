#ifndef INCLUDE_REVEL_LIB_REDEFINE
#define INCLUDE_REVEL_LIB_REDEFINE

#if __cplusplus__
extern "C"{
#endif

#include <psptypes.h>

#define Vector3 ScePspFVector3
#define Vector2 ScePspFVector2

#define Quaternion ScePspFQuaternion
#define EulerAngle ScePspFVector3

#define TEXTURE_BASE_NEAR (Vector2){0.0f,0.0f}
#define TEXTURE_BASE_FAR (Vector2){1.0f,1.0f}

typedef struct Vector2i{
	int 	x;
	int 	y;
} Vector2i;

typedef struct Vector3i{
	unsigned int 	x;
	unsigned int 	y;
    unsigned int 	z;
} Vector3i;

#if __cplusplus__
};
#endif
#endif
