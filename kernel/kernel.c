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
    frameBuffer = stivale2_get_tag(stivale2_struct,STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);
    for(int i = 0;i<=0x10000;i++)
        *(uint8_t*)(frameBuffer->framebuffer_addr + i) = 0xFF;

    while(1) asm volatile ("hlt");
}
