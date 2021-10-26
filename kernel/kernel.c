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

//kernel init
void kernelInit(struct stivale2_struct *stivale2_struct) {
    struct stivale2_struct_tag_framebuffer* frameBuffer = stivale2_get_tag(stivale2_struct,STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);
    struct stivale2module m;
    stivale2_get_module(stivale2_struct,&m,"font");
    framebufferInit(frameBuffer,&m);
}

//entry point
void _start(struct stivale2_struct *stivale2_struct) {
    kernelInit(stivale2_struct);
    framebufferClear(0xFF0000);
    char tmp[10];
    framebufferPlotString(itoa(1054,tmp,10));

    while(1) asm volatile ("hlt");
}