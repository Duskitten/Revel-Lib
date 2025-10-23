#ifndef INCLUDE_REVEL_LIB_PATCH2D
#define INCLUDE_REVEL_LIB_PATCH2D

#if __cplusplus__
extern "C"{
#endif

#include "../../revel-define.h"

//Add Revel Libs
#include "../basic/coreobject.h"
#include "../basic/texture.h"

typedef struct Patch2D
{
    CoreObject* core;
    ScePspFVector2 uv_a;
    ScePspFVector2 uv_b;
    ScePspFVector2 slice_a_size;
    ScePspFVector2 slice_b_size;
    ScePspFVector2 size;
	unsigned int modulate;
    Texture* texture;
} Patch2D;

//Taken from here: https://pspdev.github.io/basic_programs.html
typedef struct TextureVertex
{
    float u, v;
    uint32_t colour;
    float x, y, z;
} TextureVertex;


Patch2D* create_patch2d(Texture* texture, unsigned int modulate, 
    ScePspFVector2 uv_a,ScePspFVector2 uv_b, ScePspFVector2 size, ScePspFVector2 slice_a_size, ScePspFVector2 slice_b_size){

    Patch2D* patch  = (Patch2D*)malloc(sizeof(Patch2D));
    if(patch != NULL){
        
        patch->texture = texture;
        patch->uv_a = uv_a;
        patch->uv_b = uv_b;
        patch->modulate = modulate;
        patch->size = size;
        patch->slice_a_size = slice_a_size;
        patch->slice_b_size = slice_b_size;
        CoreObject* core = (CoreObject*)malloc(sizeof(CoreObject));
        patch->core = core;
    }
    sceKernelDcacheWritebackInvalidateAll();
    return patch;
    

}

//Taken from here: https://pspdev.github.io/basic_programs.html
//And modified for Revel Engine.
void draw_patch2d(Patch2D* patch) {
    TextureVertex* vertices = (TextureVertex*)malloc(18 * sizeof(TextureVertex));

    //Upper Left Corner
    vertices[0].u = patch->uv_a.x;
    vertices[0].v = patch->uv_a.y;
    vertices[0].colour = patch->modulate;
    vertices[0].x = patch->core->position.x;
    vertices[0].y = patch->core->position.y;
    vertices[0].z = 0.0f;
    vertices[1].u = patch->slice_a_size.x;
    vertices[1].v = patch->slice_a_size.y;
    vertices[1].colour = patch->modulate;
    vertices[1].x = patch->core->position.x + patch->slice_a_size.x;
    vertices[1].y = patch->core->position.y + patch->slice_a_size.y;
    vertices[1].z = 0.0f;

    //Upper Right Corner
    vertices[2].u = patch->uv_b.x - patch->slice_b_size.x;
    vertices[2].v = patch->uv_a.y;
    vertices[2].colour = patch->modulate;
    vertices[2].x = patch->core->position.x + (patch->size.x - patch->slice_b_size.x);
    vertices[2].y = patch->core->position.y;
    vertices[2].z = 0.0f;
    vertices[3].u = patch->uv_b.x;
    vertices[3].v = patch->slice_a_size.y;
    vertices[3].colour = patch->modulate;
    vertices[3].x = patch->core->position.x + patch->size.x;
    vertices[3].y = patch->core->position.y + patch->slice_a_size.y;
    vertices[3].z = 0.0f;

    //Lower Left Corner
    vertices[4].u = patch->uv_a.x;
    vertices[4].v = patch->uv_b.y - patch->slice_b_size.y;
    vertices[4].colour = patch->modulate;
    vertices[4].x = patch->core->position.x;
    vertices[4].y = patch->core->position.y + (patch->size.y - patch->slice_b_size.y);
    vertices[4].z = 0.0f;
    vertices[5].u = patch->slice_a_size.x;
    vertices[5].v = patch->uv_b.y;
    vertices[5].colour = patch->modulate;
    vertices[5].x = patch->core->position.x + patch->slice_a_size.x;
    vertices[5].y = patch->core->position.y + patch->size.y;
    vertices[5].z = 0.0f;

    //Lower Right Corner
    vertices[6].u = patch->uv_b.x - patch->slice_b_size.x;
    vertices[6].v = patch->uv_b.y - patch->slice_b_size.y;
    vertices[6].colour = patch->modulate;
    vertices[6].x = patch->core->position.x + (patch->size.x - patch->slice_b_size.x);
    vertices[6].y = patch->core->position.y + (patch->size.y - patch->slice_b_size.y);
    vertices[6].z = 0.0f;
    vertices[7].u = patch->uv_b.x;
    vertices[7].v = patch->uv_b.y;
    vertices[7].colour = patch->modulate;
    vertices[7].x = patch->core->position.x + patch->size.x;
    vertices[7].y = patch->core->position.y + patch->size.y;
    vertices[7].z = 0.0f;

    //Top Bar
    vertices[8].u = patch->slice_a_size.x;
    vertices[8].v = patch->uv_a.y;
    vertices[8].colour = patch->modulate;
    vertices[8].x = patch->core->position.x + patch->slice_a_size.x;
    vertices[8].y = patch->core->position.y;
    vertices[8].z = 0.0f;
    vertices[9].u = patch->uv_b.x - patch->slice_b_size.x;
    vertices[9].v = patch->slice_a_size.y;
    vertices[9].colour = patch->modulate;
    vertices[9].x = patch->core->position.x + (patch->size.x - patch->slice_b_size.x);
    vertices[9].y = patch->core->position.y + patch->slice_a_size.y;
    vertices[9].z = 0.0f;

    //Left Bar
    vertices[10].u = patch->uv_a.x;
    vertices[10].v = patch->slice_a_size.y;
    vertices[10].colour = patch->modulate;
    vertices[10].x = patch->core->position.x;
    vertices[10].y = patch->core->position.y + patch->slice_a_size.y;
    vertices[10].z = 0.0f;

    vertices[11].u = patch->slice_a_size.x;
    vertices[11].v = patch->uv_b.y - patch->slice_b_size.y;
    vertices[11].colour = patch->modulate;
    vertices[11].x = patch->core->position.x + patch->slice_a_size.x;
    vertices[11].y = patch->core->position.y + (patch->size.y - patch->slice_b_size.y);
    vertices[11].z = 0.0f;

    //Center
    vertices[12].u = patch->slice_a_size.x;
    vertices[12].v = patch->slice_a_size.y;
    vertices[12].colour = patch->modulate;
    vertices[12].x = patch->core->position.x + patch->slice_a_size.x;
    vertices[12].y = patch->core->position.y + patch->slice_a_size.y;
    vertices[12].z = 0.0f;

    vertices[13].u = patch->uv_b.x - patch->slice_b_size.x;
    vertices[13].v = patch->uv_b.y - patch->slice_b_size.y;
    vertices[13].colour = patch->modulate;
    vertices[13].x = patch->core->position.x + (patch->size.x - patch->slice_b_size.x);
    vertices[13].y = patch->core->position.y + (patch->size.y - patch->slice_b_size.y);
    vertices[13].z = 0.0f;

    //Right Bar
    vertices[14].u = patch->uv_b.x - patch->slice_b_size.x;
    vertices[14].v = patch->slice_a_size.y;
    vertices[14].colour = patch->modulate;
    vertices[14].x = patch->core->position.x + (patch->size.x - patch->slice_b_size.x);
    vertices[14].y = patch->core->position.y + patch->slice_a_size.y;
    vertices[14].z = 0.0f;

    vertices[15].u = patch->uv_b.x;
    vertices[15].v = patch->uv_b.y - patch->slice_b_size.y;
    vertices[15].colour = patch->modulate;
    vertices[15].x = patch->core->position.x + patch->size.x;
    vertices[15].y = patch->core->position.y + (patch->size.y - patch->slice_b_size.y);
    vertices[15].z = 0.0f;

    //Bottom Bar
    vertices[16].u = patch->slice_a_size.x;
    vertices[16].v = patch->uv_b.y - patch->slice_b_size.y;
    vertices[16].colour = patch->modulate;
    vertices[16].x = patch->core->position.x + patch->slice_a_size.x;
    vertices[16].y = patch->core->position.y + (patch->size.y - patch->slice_b_size.y);
    vertices[16].z = 0.0f;

    vertices[17].u = patch->uv_b.x - patch->slice_b_size.x;
    vertices[17].v = patch->uv_b.y;
    vertices[17].colour = patch->modulate;
    vertices[17].x = patch->core->position.x + (patch->size.x - patch->slice_b_size.x);
    vertices[17].y = patch->core->position.y + patch->size.y;
    vertices[17].z = 0.0f;


    sceKernelDcacheWritebackInvalidateAll();
    bind_texture(patch->texture);
    sceGuDrawArray(GU_SPRITES, GU_COLOR_8888 | GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_2D, 18, 0, vertices);
    free(vertices);
}

#if __cplusplus__
};
#endif
#endif
