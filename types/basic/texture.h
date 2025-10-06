#ifndef INCLUDE_REVEL_LIB_TEXTURE
#define INCLUDE_REVEL_LIB_TEXTURE


#if __cplusplus__
extern "C"{
#endif

//Include Revel Libs
#include "../../revel-define.h"

//Include 3rd Party Libs
#include "../../3rdparty/stb/stb_image.h"

//Include PSP Libs
#include <pspgu.h>
#include <pspgum.h>
#include <pspge.h>
#include <pspdisplay.h>
#include <pspkernel.h>


//Begin!
typedef struct {
    Vector2i size;
    Vector2i psize;
    void* data;
} Texture;


// This function is taken from : 
// https://github.com/IridescentRose/PSP-GPU-Tutorials/tree/master/common
// Under MIT License
unsigned int getMemorySize(unsigned int width, unsigned int height, unsigned int psm)
{
	switch (psm)
	{
		case GU_PSM_T4:
			return (width * height) >> 1;

		case GU_PSM_T8:
			return width * height;

		case GU_PSM_5650:
		case GU_PSM_5551:
		case GU_PSM_4444:
		case GU_PSM_T16:
			return 2 * width * height;

		case GU_PSM_8888:
		case GU_PSM_T32:
			return 4 * width * height;

		default:
			return 0;
	}
}

// This function is taken from : 
// https://github.com/IridescentRose/PSP-GPU-Tutorials/tree/master/common
// Under MIT License
void* getStaticVramBuffer(unsigned int width, unsigned int height, unsigned int psm)
{
	static unsigned int staticOffset = 0;
	unsigned int memSize = getMemorySize(width,height,psm);
	void* result = (void*)staticOffset;
	staticOffset += memSize;

	return result;
}

// This function is taken from : 
// https://github.com/IridescentRose/PSP-GPU-Tutorials/tree/master/common
// Under MIT License
void* getStaticVramTexture(unsigned int width, unsigned int height, unsigned int psm)
{
	void* result = getStaticVramBuffer(width,height,psm);
	return (void*)(((unsigned int)result) + ((unsigned int)sceGeEdramGetAddr()));
}


// This function is taken from : 
// https://github.com/IridescentRose/PSP-GPU-Tutorials/tree/master/common
// Under MIT License
void swizzle_fast(u8 *out, const u8 *in, const unsigned int width, const unsigned int height) {
    unsigned int blockx, blocky;
    unsigned int j;

    unsigned int width_blocks = (width / 16);
    unsigned int height_blocks = (height / 8);

    unsigned int src_pitch = (width - 16) / 4;
    unsigned int src_row = width * 8;

    const u8 *ysrc = in;
    u32 *dst = (u32 *)out;

    for (blocky = 0; blocky < height_blocks; ++blocky) {
        const u8 *xsrc = ysrc;
        for (blockx = 0; blockx < width_blocks; ++blockx) {
            const u32 *src = (u32 *)xsrc;
            for (j = 0; j < 8; ++j) {
                *(dst++) = *(src++);
                *(dst++) = *(src++);
                *(dst++) = *(src++);
                *(dst++) = *(src++);
                src += src_pitch;
            }
            xsrc += 16;
        }
        ysrc += src_row;
    }
}

// This function is taken from : 
// https://github.com/IridescentRose/PSP-GPU-Tutorials/tree/master/common
// Under MIT License
unsigned int pow2(const unsigned int value) {
    unsigned int poweroftwo = 1;
    while (poweroftwo < value) {
        poweroftwo <<= 1;
    }
    return poweroftwo;
}

// This function is taken from : 
// https://github.com/IridescentRose/PSP-GPU-Tutorials/tree/master/common
// Under MIT License
void copy_texture_data(void* dest, const void* src, const int pW, const int width, const int height){
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            ((unsigned int*)dest)[x + y * pW] = ((unsigned int *)src)[x + y * width];
        }
    }
}



// This function is taken from : 
// https://github.com/IridescentRose/PSP-GPU-Tutorials/tree/master/common
// Under MIT License and has modifications for Revel Lib.
Texture* create_texture(const char* filename, const int vram){
    int width, height, nrChannels;    
    stbi_set_flip_vertically_on_load(GU_TRUE);
    unsigned char *data = stbi_load(filename, &width, &height,
                                    &nrChannels, STBI_rgb_alpha);

    if(!data){
        return NULL;
    }

    Texture* texture = (Texture*)malloc(sizeof(Texture));
    texture->size = (Vector2i){width, height};
    texture->psize = (Vector2i){pow2(width), pow2(height)};

    unsigned int *dataBuffer =
        (unsigned int *)memalign(16, texture->psize.y * texture->psize.x * 4);

    // Copy to Data Buffer
    copy_texture_data(dataBuffer, data, texture->psize.x, texture->size.x, texture->size.y);

    // Free STB Data
    stbi_image_free(data);

    unsigned int* swizzled_pixels = NULL;
    size_t size = texture->psize.y * texture->psize.x * 4;
    if(vram){
        swizzled_pixels = getStaticVramTexture(texture->psize.x, texture->psize.y, GU_PSM_8888);
    } else {
        swizzled_pixels = (unsigned int *)memalign(16, size);
    }
    
    swizzle_fast((u8*)swizzled_pixels, (const u8*)dataBuffer, texture->psize.x * 4, texture->psize.y);

    free(dataBuffer);
    texture->data = swizzled_pixels;

    sceKernelDcacheWritebackInvalidateAll();

    return texture;
}

// This function is taken from : 
// https://github.com/IridescentRose/PSP-GPU-Tutorials/tree/master/common
// Under MIT License
void bind_texture(Texture* texture) {
    if(texture == NULL)
        return;

    sceGuTexMode(GU_PSM_8888, 0, 0, 1);
    sceGuTexFunc(GU_TFX_MODULATE, GU_TCC_RGBA);
    sceGuTexFilter(GU_NEAREST, GU_NEAREST);
    sceGuTexWrap(GU_REPEAT, GU_REPEAT);
    sceGuTexImage(0, texture->size.x, texture->size.y, texture->size.x, texture->data);
}



#if __cplusplus__
};
#endif


#endif