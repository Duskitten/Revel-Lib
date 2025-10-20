#ifndef INCLUDE_REVEL_LIB_SPRITE2D
#define INCLUDE_REVEL_LIB_SPRITE2D

#if __cplusplus__
extern "C"{
#endif

#include "../../revel-define.h"

//Add Revel Libs
#include "../basic/coreobject.h"
#include "../basic/texture.h"

typedef struct
{
    CoreObject* core;
    ScePspFVector2 uv_a;
    ScePspFVector2 uv_b;
    ScePspFVector2 size;
	unsigned int modulate;
    Texture* texture;
} Sprite2D;

//Taken from here: https://pspdev.github.io/basic_programs.html
typedef struct
{
    float u, v;
    uint32_t colour;
    float x, y, z;
} TextureVertex;


Sprite2D* create_sprite2d(Texture* texture, unsigned int modulate, 
    ScePspFVector2 uv_a,ScePspFVector2 uv_b, ScePspFVector2 size){

    Sprite2D* sprite = (Sprite2D*)malloc(sizeof(Sprite2D));
    
    if(sprite != NULL){
        sprite->texture = texture;
        sprite->uv_a = uv_a;
        sprite->uv_b = uv_b;
        sprite->modulate = modulate;
        sprite->size = size;
    }
    sceKernelDcacheWritebackInvalidateAll();
    return sprite;
    

}

//Taken from here: https://pspdev.github.io/basic_programs.html
//And modified for Revel Engine.
void draw_sprite2d(Sprite2D* sprite) {
    static TextureVertex vertices[2];

    vertices[0].u = sprite->uv_a.x;
    vertices[0].v = sprite->uv_a.y;
    vertices[0].colour = sprite->modulate;
    vertices[0].x = sprite->core->position.x;
    vertices[0].y = sprite->core->position.y;
    vertices[0].z = 0.0f;

    vertices[1].u = sprite->uv_b.x;
    vertices[1].v = sprite->uv_b.y;
    vertices[1].colour = sprite->modulate;
    vertices[1].x = sprite->core->position.x + sprite->size.x;
    vertices[1].y = sprite->core->position.y + sprite->size.y;
    vertices[1].z = 0.0f;

    bind_texture(sprite->texture);
    sceGuDrawArray(GU_SPRITES, GU_COLOR_8888 | GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_2D, 2, 0, vertices);
    sceKernelDcacheWritebackInvalidateAll();
}

void draw_sprite2d_no_tex(Sprite2D* sprite) {
    static TextureVertex vertices[2];

    vertices[0].u = sprite->uv_a.x;
    vertices[0].v = sprite->uv_a.y;
    vertices[0].colour = sprite->modulate;
    vertices[0].x = sprite->core->position.x;
    vertices[0].y = sprite->core->position.y;
    vertices[0].z = 0.0f;

    vertices[1].u = sprite->uv_b.x;
    vertices[1].v = sprite->uv_b.y;
    vertices[1].colour = sprite->modulate;
    vertices[1].x = sprite->core->position.x + sprite->size.x;
    vertices[1].y = sprite->core->position.y + sprite->size.y;
    vertices[1].z = 0.0f;

    sceGuDrawArray(GU_SPRITES, GU_INDEX_16BIT | GU_COLOR_8888 | GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_2D, 2, 0, vertices);
}

#if __cplusplus__
};
#endif
#endif
