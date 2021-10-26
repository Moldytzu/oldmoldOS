#include <framebuffer.h>
struct frameBuffer fb;
struct PSFFont* fnt;

uint16_t cursorX;
uint16_t cursorY;
uint32_t cursorColor;

void framebufferInit(struct stivale2_struct_tag_framebuffer* fr, struct stivale2module* module) {
    fb.base = (void*)fr->framebuffer_addr;
    fb.height = fr->framebuffer_height;
    fb.width = fr->framebuffer_width;
    fnt = module->base;

    cursorX = 0;
    cursorY = 0;
    cursorColor = 0xFFFFFF;
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

void framebufferPlotString(const char* chr) {
    for(int i = 0;chr[i] != 0;i++) {
        framebufferPlotCharacter(cursorX,cursorY,cursorColor,chr[i]);
        cursorX+=10;
        if(cursorX+10 >= fb.width) {
            cursorX = 0;
            cursorY += 18;
        }
    }
}

struct Cursor framebufferGetCursor() {
    struct Cursor p;
    p.x = cursorX;
    p.y = cursorY;
    p.color = cursorColor;
    return p;
}

void framebufferSetCursor(uint16_t x, uint16_t y, uint32_t color) {
    cursorX = x;
    cursorY = y;
    cursorColor = color;
}

void framebufferClear(uint32_t color) {
    for(int y = 0;y<fb.height;y++)
        for(int x = 0;x<fb.width;x++)
            framebufferPutPixel(x,y,color);
}