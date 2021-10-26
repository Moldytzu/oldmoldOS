#include <framebuffer.h>
struct frameBuffer fb;
struct PSFFont* fnt;

void framebufferInit(struct stivale2_struct_tag_framebuffer* fr, struct stivale2module* module) {
    fb.base = (void*)fr->framebuffer_addr;
    fb.height = fr->framebuffer_height;
    fb.width = fr->framebuffer_width;
    fnt = module->base;
}

void framebufferPutPixel(uint16_t x, uint16_t y, uint32_t color) {
    ((uint32_t*)fb.base)[y * fb.width + x] = color;
}

void framebufferPlotCharacter(uint16_t xOff, uint16_t yOff, uint32_t color, char chr) {
    char* fontPtr = &fnt->glyphs + (chr * fnt->header.numglyph);
    for (unsigned long y = yOff; y < yOff + 16; y++){
        for (unsigned long x = xOff; x < xOff + 8; x++){
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0){
                    framebufferPutPixel(x,y,color);
                }

        }
        fontPtr++;
    }
}

struct frameBuffer* framebufferGet() {
    return &fb;
}

/*
    char* fontPtr = m.base+sizeof(struct PSFHeader) + ('A' * fontHeader->numglyph);
    for (unsigned long y = 0; y < 0 + 16; y++){
        for (unsigned long x = 0; x < 0+8; x++){
            if ((*fontPtr & (0b10000000 >> (x - 0))) > 0){
                    framebufferPutPixel(x,y,0xFFFFFF);
                }

        }
        fontPtr++;
    }
*/