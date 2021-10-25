#include <bootloaderif.h> //bootloader interface
#include <utils.h> //utilities

//Kernel stack (4 mb should be enough for now)
static uint8_t kernelStack[4096*1024*1024];

//header
__attribute__((section(".stivale2hdr"), used))
static struct stivale2_header stivale_hdr = {
    .entry_point = 0, //to be filled by limine
    .stack = (uintptr_t)kernelStack + sizeof(kernelStack), //stack growing downwards
    .flags = (1 << 1) | (1 << 2),
    .tags = (uintptr_t)&framebuffer_hdr_tag //start of the linked list
};

//entry point
void _start(struct stivale2_struct *stivale2_struct) {
    term_str_tag = stivale2_get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_TERMINAL_ID);
    if (term_str_tag == NULL) while(1) asm volatile ("hlt"); //if we don't find the tag, we hang

    //terminal write
    void *term_write_ptr = (void *)term_str_tag->term_write;
    void (*term_write)(const char *string, size_t length) = term_write_ptr;
    term_write("moldOS booted!", strlen("moldOS booted!"));

    while(1) asm volatile ("hlt");
}
