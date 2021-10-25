#pragma once
#include <stdint.h>
#include <stddef.h>
#include <bootloaderif.h>

struct frameBuffer {
    void* base;
    uint16_t width;
    uint16_t height;
};

void framebufferInit(struct stivale2_struct_tag_framebuffer* fr);
void framebufferPutPixel(uint16_t x, uint16_t y, uint32_t color);
struct frameBuffer* framebufferGet();