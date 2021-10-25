#pragma once
#include <stivale2.h>
#include <stdint.h>
#include <stddef.h>

//Kernel stack (4 mb should be enough for now)
static uint8_t kernelStack[4096*1024*1024];

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

//get tag
void *stivale2_get_tag(struct stivale2_struct *stivale2_struct, uint64_t id);