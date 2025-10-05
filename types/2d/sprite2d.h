#ifndef INCLUDE_REVEL_LIB_SPRITE2D
#define INCLUDE_REVEL_LIB_SPRITE2D

#if __cplusplus__
extern "C"{
#endif

//Include Revel Libs
#include "../../revel-define.h"
#include "../basic/coreobject.h"
#include "../basic/texture.h"

//Include System Libs
#include <malloc.h>

//Include PSP Libs
#include <pspgu.h>

//Begin!
typedef struct {
    CoreObject* object;
    Vector2 uv_a;
    Vector2 uv_b;
    Texture* texture;
    uint32_t modulate;
    void* data;
} Sprite2D;

typedef struct
{
    float u, v;
    uint32_t modulate;
    float x, y, z;
} TextureVertex;
/*
*Creates a new Sprite2D object.
*- This functions within 2D space only
*
*/
Sprite2D* create_sprite2d(Vector2 uv_a, Vector2 uv_b,Texture* tex){
    Sprite2D* sprite = malloc(sizeof(Sprite2D));
    if(sprite != NULL){
        sprite->object = create_coreobject();
        sprite->uv_a = uv_a;
        sprite->uv_b = uv_b;
        sprite->texture = tex;
        return sprite;
    }else{
        return NULL;
    }
};

void draw_sprite2d(Sprite2D* sprite){
    static TextureVertex vertices[2];

    vertices[0].u = sprite->uv_a.x;
    vertices[0].v = sprite->uv_a.y;
    vertices[0].modulate = sprite->modulate;
    vertices[0].x = sprite->object->local_position.x;
    vertices[0].y = sprite->object->local_position.y;
    vertices[0].z = 0.0f;

    vertices[1].u = sprite->uv_b.x;;
    vertices[1].v = sprite->uv_b.y;
    vertices[1].modulate = sprite->modulate;
    vertices[1].x = (sprite->object->local_position.x + sprite->texture->size.x);
    vertices[1].y = (sprite->object->local_position.y + sprite->texture->size.y);
    vertices[1].z = 0.0f;

	bind_texture(sprite);
    sceGuDrawArray(GU_SPRITES, GU_COLOR_8888 | GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_2D, 2, 0, vertices);
};

#if __cplusplus__
};
#endif
#endif
