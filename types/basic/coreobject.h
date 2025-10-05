#ifndef INCLUDE_REVEL_LIB_COREOBJECT
#define INCLUDE_REVEL_LIB_COREOBJECT

#if __cplusplus__
extern "C"{
#endif

//Include Revel Libs
#include "../../revel-define.h"
#include "../../3rdparty/stb/stb_image.h"

//Include System Stuff
#include <malloc.h>

//Begin!
typedef struct {
    Vector3 local_position;
    Quaternion local_rotation;
    Vector3 local_scale;

    void* children;
    void* parent;
} CoreObject;



CoreObject* create_coreobject(){
    CoreObject* coreobject = malloc(sizeof(CoreObject));

    if(coreobject != NULL){
        coreobject->local_position = (Vector3){0,0,0};
        coreobject->local_rotation = (Quaternion){0,0,0,1};
        coreobject->local_scale = (Vector3){1,1,1};

        coreobject->parent = NULL;

        return coreobject;}
    else{
        return NULL;
    }
}

#if __cplusplus__
};
#endif


#endif