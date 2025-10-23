#ifndef INCLUDE_REVEL_LIB_RECTMATH
#define INCLUDE_REVEL_LIB_RECTMATH

#if __cplusplus__
extern "C"{
#endif

//Include Revel Libs
#include "../../revel-define.h"

int point_in_rect(ScePspFVector3 Position, ScePspFVector2 Offsets, ScePspFVector3 RectPos, ScePspFVector2 RectSize){
    if(Position.x + Offsets.x >= RectPos.x &&
        Position.x + Offsets.x <= RectPos.x + RectSize.x &&
        Position.y + Offsets.y >= RectPos.y &&
        Position.y + Offsets.y  <= RectPos.y + RectSize.y
    ){
        return GU_TRUE;
    }
    return GU_FALSE;
}

#if __cplusplus__
};
#endif


#endif