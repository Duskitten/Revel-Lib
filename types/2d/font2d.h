#ifndef INCLUDE_REVEL_LIB_FONT2D
#define INCLUDE_REVEL_LIB_FONT2D

#if __cplusplus__
extern "C"{
#endif

#include "../../revel-define.h"

//include Revel libs
#include "../basic/coreobject.h"
#include "../basic/texture.h"
#include "../2d/sprite2d.h"

typedef struct FontCharacter{
    ScePspIVector2 uv_a;
    ScePspIVector2 uv_b;
    char character;
} FontCharacter;

typedef struct Font2D{
    CoreObject* core;
    char* characters;
    ScePspFVector2 character_size;
    ScePspIVector2 character_slices;
    ScePspFVector2 character_spacing;
    FontCharacter* sprites;
    unsigned int modulate;
    Texture* texture;
} Font2D;



Font2D* create_font2d(Texture* texture, ScePspIVector2 character_slices, ScePspFVector2 character_size, 
    ScePspFVector2 character_spacing, unsigned int modulate, char* charactersA){
    Font2D* font = (Font2D*)malloc(sizeof(Font2D));

    if(font != NULL){
        font->texture = texture;
        font->character_size = character_size;
        font->character_spacing = character_spacing;
        font->modulate = modulate;
        font->characters = charactersA;
        font->character_slices = character_slices;
        unsigned int charlength = strlen(charactersA);
        
        FontCharacter char_compiler[charlength];
        ScePspIVector2 pos = {0,0};
        for(int i = 0; i < charlength; i++){
            unsigned int looper = i % character_slices.x;
            pos.x = looper;
            //unsigned int sizeA = i;
            //unsigned int sizeB = i*2;
            
            if(i != 0 && looper == 0){
                pos.y += 1;
            }
            ScePspIVector2 newposA = {pos.x*font->character_size.x,pos.y*font->character_size.y};
            ScePspIVector2 newposB = {(pos.x*font->character_size.x)+font->character_size.x,(pos.y*font->character_size.y)+font->character_size.y};
            FontCharacter character = *(FontCharacter*)malloc(sizeof(FontCharacter));

            character.uv_a = newposA;
            character.uv_b = newposB;
            character.character = charactersA[i];

            char_compiler[i] = character;
        }
        font->sprites = char_compiler;
    }
    sceKernelDcacheWritebackInvalidateAll();
    return font;
    
}

//This is important for accessing our data.
//FontCharacter obj = *(font->character_uv_map+charpos);

void draw_font2d(Font2D* font, char* text, ScePspFVector2 position){
    int real_size = strlen(text);
    int doubled_real_size = real_size * 2;
    TextureVertex vertices[doubled_real_size];
    int indices[doubled_real_size];
    for(int x = 0; x < real_size; x++){
        int realX = x*2;
        int realXP1 = realX+1;
        char* found;
        found = strchr(font->characters, text[x]);
        if(found){
            FontCharacter sprite = *(font->sprites+(found - font->characters));
            vertices[realX].u = (float)sprite.uv_a.x;
            vertices[realX].v = (float)sprite.uv_a.y;
            vertices[realX].colour = font->modulate;
            vertices[realX].x = position.x + (x * font->character_size.x);
            vertices[realX].y = position.y;
            vertices[realX].z = 0.0f;
            indices[realX] = realX;
            
            vertices[realXP1].u = (float)sprite.uv_b.x;
            vertices[realXP1].v = (float)sprite.uv_b.y;
            vertices[realXP1].colour = font->modulate;
            vertices[realXP1].x = position.x+(x * font->character_size.x) + font->character_size.x;
            vertices[realXP1].y = position.y + font->character_size.y;
            vertices[realXP1].z = 0.0f;
            indices[realXP1] = realXP1;
        }
    }
    sceKernelDcacheWritebackInvalidateAll();
    bind_texture(font->texture);
    sceGuDrawArray(GU_SPRITES, GU_COLOR_8888 | GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_2D, doubled_real_size, &indices, vertices);
    
}

#if __cplusplus__
};
#endif
#endif
