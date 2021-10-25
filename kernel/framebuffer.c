#include <framebuffer.h>
struct frameBuffer fb;

void framebufferInit(struct stivale2_struct_tag_framebuffer* fr) {
    fb.base = (void*)fr->framebuffer_addr;
    fb.height = fr->framebuffer_height;
    fb.width = fr->framebuffer_width;
}

void framebufferPutPixel(uint16_t x, uint16_t y, uint32_t color) {
    ((uint32_t*)fb.base)[y * fb.width + x] = color;
}

struct frameBuffer* framebufferGet() {
    return &fb;
}