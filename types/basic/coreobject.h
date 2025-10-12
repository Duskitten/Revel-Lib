#ifndef INCLUDE_REVEL_LIB_COREOBJECT
#define INCLUDE_REVEL_LIB_COREOBJECT

#if __cplusplus__
extern "C"{
#endif

//Include Revel Libs
#include "../../revel-define.h"

typedef struct
{
    ScePspFVector3 position;
    ScePspFVector3 rotation;
    ScePspFVector3 scale;
} CoreObject;

#if __cplusplus__
};
#endif


#endif