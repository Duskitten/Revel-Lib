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
    FontCharacter** sprites;
    unsigned int modulate;
    Texture* texture;
} Font2D;



Font2D* create_font2d(Texture* texture, ScePspIVector2 character_slices, ScePspFVector2 character_size, 
    ScePspFVector2 character_spacing, unsigned int modulate, char* charactersA){
    Font2D* font = (Font2D*)malloc(sizeof(Font2D));

    if(font != NULL){
        CoreObject* core = (CoreObject*)malloc(sizeof(CoreObject));
        font->core = core;
        font->texture = texture;
        font->character_size = character_size;
        font->character_spacing = character_spacing;
        font->modulate = modulate;
        font->characters = charactersA;
        font->character_slices = character_slices;
        unsigned int charlength = strlen(charactersA);
        
        FontCharacter* char_compiler[charlength];
        ScePspIVector2 pos = {0,0};
        int realvalue = 0;
        for(int i = 0; i < charlength; i++){
            if(realvalue == font->character_slices.x){
                realvalue = 0;
            }
            
            if(i != 0 && realvalue == 0){
                pos.y += 1;
            }

            ScePspIVector2 newposA = {realvalue*font->character_size.x,pos.y*font->character_size.y};
            ScePspIVector2 newposB = {(realvalue*font->character_size.x)+font->character_size.x,(pos.y*font->character_size.y)+font->character_size.y};
            FontCharacter* character = (FontCharacter*)malloc(sizeof(FontCharacter));

            character->uv_a = newposA;
            character->uv_b = newposB;
            character->character = charactersA[i];

            char_compiler[i] = character;
            realvalue += 1;
        }
        font->sprites = char_compiler;
    }
    sceKernelDcacheWritebackInvalidateAll();
    return font;
    
}

void draw_font2d(Font2D* font, char* text, ScePspFVector2 position){
    int real_size = strlen(text);
    int doubled_real_size = real_size * 2;
    //Apparently we need to add buffer space? not totally sure why. But it works.
    ScePspIVector2 RelayPos = (ScePspIVector2){0,0};

    TextureVertex* vertices = (TextureVertex*)malloc(doubled_real_size * sizeof(TextureVertex));
    
    for(int x = 0; x < real_size; x++){
        int realX = x*2;
        int realXP1 = realX+1;
        char* found;
        found = strchr(font->characters, text[x]);
        if(text[x] == '\n'){
            RelayPos.x = -1;
            RelayPos.y += 1;
        } else 
        if(found){
            //pspDebugScreenSetXY(32, x+1);
            FontCharacter sprite = *font->sprites[(found - font->characters)];
            pspDebugScreenSetXY(32, x);
            pspDebugScreenPrintf("%c, with %d", sprite.character, (found - font->characters));
            vertices[realX].u = (float)sprite.uv_a.x;
            vertices[realX].v = (float)sprite.uv_a.y;
            vertices[realX].colour = font->modulate;
            vertices[realX].x = position.x + (RelayPos.x * font->character_size.x);
            vertices[realX].y = position.y+ (RelayPos.y * font->character_size.y);
            vertices[realX].z = 0.0f;
            
            vertices[realXP1].u = (float)sprite.uv_b.x;
            vertices[realXP1].v = (float)sprite.uv_b.y;
            vertices[realXP1].colour = font->modulate;
            vertices[realXP1].x = position.x + (RelayPos.x * font->character_size.x) + font->character_size.x;
            vertices[realXP1].y = position.y + font->character_size.y + (RelayPos.y * font->character_size.y);
            vertices[realXP1].z = 0.0f; 
        }
        RelayPos.x += 1;
    }
    sceKernelDcacheWritebackInvalidateAll();
    bind_texture(font->texture);
    sceGuDrawArray(GU_SPRITES, GU_COLOR_8888 | GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_2D, doubled_real_size, 0, vertices);
    free(vertices);
}

#if __cplusplus__
};
#endif
#endif
