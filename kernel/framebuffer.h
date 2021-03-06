#pragma once
#include <stdint.h>
#include <stddef.h>
#include <bootloaderif.h>

struct frameBuffer {
    void* base;
    uint16_t width;
    uint16_t height;
    uint16_t pps; //pixels per scanline or pitch
};

struct PSFHeader {
    uint16_t magic;
    uint8_t mode;
    uint8_t numglyph;
};

struct PSFFont {
    struct PSFHeader header;
    char glyphs; 
};

struct Cursor {
    uint16_t x;
    uint16_t y;
    uint32_t color;
};

void framebufferInit(struct stivale2_struct_tag_framebuffer* fr, struct stivale2module* module);
void framebufferPutPixel(uint16_t x, uint16_t y, uint32_t color);
void framebufferPlotCharacter(uint16_t xOff, uint16_t yOff, uint32_t color, char chr);
void framebufferPlotString(const char* chr);
struct Cursor framebufferGetCursor();
void framebufferSetCursor(uint16_t x, uint16_t y, uint32_t color);
void framebufferClear(uint32_t color);

struct frameBuffer* framebufferGet();