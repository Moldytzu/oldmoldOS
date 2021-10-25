#include <stdint.h>
#include <stddef.h>
#include <stivale2.h>

//Kernel stack (4 mb should be enough for now)
static uint8_t stack[4096*1024*1024];

//terminal tag
static struct stivale2_header_tag_terminal terminal_hdr_tag = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_TERMINAL_ID,
        .next = 0
    },
    .flags = 0
};

//framebuffer tag
static struct stivale2_header_tag_framebuffer framebuffer_hdr_tag = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
        .next = (uint64_t)&terminal_hdr_tag
    },
    .framebuffer_width  = 0,
    .framebuffer_height = 0,
    .framebuffer_bpp    = 0
};

//header
__attribute__((section(".stivale2hdr"), used))
static struct stivale2_header stivale_hdr = {
    .entry_point = 0, //to be filled by limine
    .stack = (uintptr_t)stack + sizeof(stack), //stack growing downwards
    .flags = (1 << 1) | (1 << 2),
    .tags = (uintptr_t)&framebuffer_hdr_tag //start of the linked list
};

//get tag
void *stivale2_get_tag(struct stivale2_struct *stivale2_struct, uint64_t id) {
    struct stivale2_tag *current_tag = (void *)stivale2_struct->tags;
    while(1) {
        if (current_tag == NULL) //if we are done with the list we return nothing
            return NULL;
        if (current_tag->identifier == id) //if we found the tag we want, we return it
            return current_tag;
        current_tag = (void *)current_tag->next; //get next tag
    }
}

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
