#ifndef INCLUDE_REVEL_LIB_FONT2D
#define INCLUDE_REVEL_LIB_FONT2D

#if __cplusplus__
extern "C"{
#endif

//Include Revel Libs
#include "../../revel-define.h"
#include "../basic/coreobject.h"
#include "../basic/texture.h"
#include "../2d/sprite2d.h"

//Include System Libs
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

//Include PSP Libs
#include <pspgu.h>


//Begin!
typedef struct {
    CoreObject* object;
    const char* character_order;
    Vector2i slice_count;
    Vector2i character_size;
    Texture* texture;
    uint32_t modulate;
    int spacing_x;
    int spacing_y;
    //void* data;
    Vector2i* character_uv[];
} Font2D;

Font2D* create_font2d(int spacing_x, int spacing_y,const char* character_order, Vector2i slice_count, Vector2i character_size, uint32_t modulate, Texture* tex){
    Font2D* font = (Font2D*)malloc(sizeof(Font2D));
    if(font != NULL){
        font->object = create_coreobject();
        font->slice_count = slice_count;
        font->character_size = character_size;
        font->character_order = character_order;
        font->spacing_x = spacing_x;
        font->spacing_y = spacing_y;
        font->texture = tex;
        font->modulate = modulate;
        return font;
    }else{
        return NULL;
    }
};

void draw_font2d(Font2D* font, Vector2i Position, char* text){
    int length = 0;
    
    
    //put text parser here.
    int skipnext = 0;
    int nextY = 0;

    for(int current_charpos = 0; current_charpos < strlen(text); current_charpos++){
        
        if(text[current_charpos] == '\\' && current_charpos+1 <= strlen(text) && text[current_charpos+1] == 'n'){
            //char nextchar = (char)text[current_charpos+1];
            skipnext = 1;
        }
        else if (skipnext == 1)
        {
            skipnext = 0;
        } else {
            length += 1;
        }
    }

    length = length * 2;
    TextureVertex vertices[length * 2];
    skipnext = 0;
    int real_pos = 0;
    int vert_pos = 0;
    int line_pos = 0;
    for(int current_charpos = 0; current_charpos < strlen(text); current_charpos++){
        
        if(text[current_charpos] == '\\' && 
        current_charpos+1 <= strlen(text) && 
        text[current_charpos+1] == 'n'){
            //char nextchar = (char)text[current_charpos+1];
            skipnext = 1;
            nextY += 1;
            line_pos = 0;
        }
        else if (skipnext == 1)
        {
            skipnext = 0;
        } else {
            Vector2i pos = (Vector2i){0,0};

            int pos_y = 0;
            for(int pos1 = 0; pos1 < strlen(font->character_order); pos1++){
                int total_pos = pos1 % font->slice_count.x;

                if(pos1 != 0 && total_pos == 0){
                    pos_y += 1;
                }

                if(font->character_order[pos1] == text[current_charpos]){
                    pos = (Vector2i){total_pos,pos_y};
                }
                
            }
            
            pos.x *= font->character_size.x;
            pos.y *= font->character_size.y;
            vertices[vert_pos].u = pos.x;
            vertices[vert_pos].v = -pos.y;
            vertices[vert_pos].modulate = font->modulate;
            vertices[vert_pos].x = Position.x + (font->spacing_x * line_pos) + (font->character_size.x* line_pos);
            vertices[vert_pos].y = Position.y + (font->spacing_y * nextY) + (font->character_size.y * nextY);
            vertices[vert_pos].z = 0.0f;

            vertices[vert_pos+1].u = pos.x + font->character_size.x;
            vertices[vert_pos+1].v = -(pos.y + font->character_size.y);
            vertices[vert_pos+1].modulate = font->modulate;
            vertices[vert_pos+1].x = (Position.x + font->character_size.x) + (font->spacing_x * line_pos) + (font->character_size.x * line_pos);
            vertices[vert_pos+1].y = (Position.y + font->character_size.y) + (font->spacing_y * nextY) + (font->character_size.y * nextY);
            vertices[vert_pos+1].z = 0.0f;
            real_pos += 1;
            line_pos += 1;
            vert_pos += 2;
        }
    }

    //End text parser.

    bind_texture(font->texture);
    sceGuTexImage(0, font->texture->size.x, font->texture->size.y, font->texture->size.x, font->texture->data);

    sceGuDrawArray(GU_SPRITES, GU_COLOR_8888 | GU_TEXTURE_32BITF | GU_VERTEX_32BITF | GU_TRANSFORM_2D, length, 0, vertices);


};

#if __cplusplus__
};
#endif
#endif
