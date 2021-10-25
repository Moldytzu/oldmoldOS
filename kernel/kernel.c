#include <bootloaderif.h> //bootloader interface

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
    struct stivale2_struct_tag_terminal *term_str_tag;
    term_str_tag = stivale2_get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_TERMINAL_ID);
    if (term_str_tag == NULL) while(1) asm volatile ("hlt"); //if we don't find the tag, we hang

    //terminal write
    void *term_write_ptr = (void *)term_str_tag->term_write;
    void (*term_write)(const char *string, size_t length) = term_write_ptr;
    term_write("moldOS", 6);

    while(1) asm volatile ("hlt");
}
