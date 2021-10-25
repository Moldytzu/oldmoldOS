#include <bootloaderif.h> //bootloader interface
#include <utils.h> //utilities
#include <framebuffer.h> //framebuffer

//Kernel stack (4 mb should be enough for now)
static uint8_t kernelStack[4096*1024*1024];

//header
__attribute__((section(".stivale2hdr"), used))
static struct stivale2_header stivale_hdr = {
    .entry_point = 0, //to be filled by limine
    .stack = (uintptr_t)kernelStack + sizeof(kernelStack), //stack growing downwards
    .flags = 0,
    .tags = (uintptr_t)&s_tag0 //start of the linked list
};

//entry point
void _start(struct stivale2_struct *stivale2_struct) {
    struct stivale2_struct_tag_framebuffer* frameBuffer = stivale2_get_tag(stivale2_struct,STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);
    framebufferInit(frameBuffer);
    for(int x = 0;x<framebufferGet()->width;x++)
        for(int y = 0;y<framebufferGet()->height;y++)
            framebufferPutPixel(x,y,0xFF00FF);

    while(1) asm volatile ("hlt");
}
