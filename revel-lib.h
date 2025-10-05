#ifndef INCLUDE_REVEL_LIB
#define INCLUDE_REVEL_LIB

#if __cplusplus__
extern "C"{
#endif

#include <pspdisplay.h>
#include <pspgu.h>
#include <pspgum.h>
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <psptypes.h>

#define Vector3 ScePspFVector3
#define Vector2 ScePspFVector2
#define Quaternion ScePspFQuaternion

typedef struct {
    Vector3 Local_Position;
    Quaternion Local_Rotation;
    Vector3 Local_Scale;

    Vector3 Global_Position;
    Quaternion Global_Rotation;
    Vector3 Global_Scale;
} CoreObject;

void RevelInit(ScePspFVector3 test) {
}

#if __cplusplus__
};
#endif


#endif