#include <bootloaderif.h> //bootloader interface
#include <utils.h> //utilities
#include <framebuffer.h> //framebuffer

//Kernel stack (4 mb should be enough for now)
static uint8_t kernelStack[0x1000000];

//header
__attribute__((section(".stivale2hdr"), used))
static struct stivale2_header stivale_hdr = {
    .entry_point = 0, //to be filled by limine
    .stack = (uintptr_t)kernelStack + sizeof(kernelStack), //stack growing downwards
    .flags = 0,
    .tags = (uintptr_t)&sampleTag //start of the linked list
};

void kernelInit(struct stivale2_struct *stivale2_struct) {
    struct stivale2_struct_tag_framebuffer* frameBuffer = stivale2_get_tag(stivale2_struct,STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);
    framebufferInit(frameBuffer);
}

struct PSFHeader {
    uint16_t magic;
    uint8_t mode;
    uint8_t numglyph;
};

//entry point
void _start(struct stivale2_struct *stivale2_struct) {
    kernelInit(stivale2_struct);
    struct module m;
    stivale2_get_module(stivale2_struct,&m,"font");

    struct PSFHeader* fontHeader = m.base;

    char* fontPtr = m.base+sizeof(struct PSFHeader) + ('A' * fontHeader->numglyph);
    for (unsigned long y = 0; y < 0 + 16; y++){
        for (unsigned long x = 0; x < 0+8; x++){
            if ((*fontPtr & (0b10000000 >> (x - 0))) > 0){
                    framebufferPutPixel(x,y,0xFFFFFF);
                }

        }
        fontPtr++;
    }

    while(1) asm volatile ("hlt");
}