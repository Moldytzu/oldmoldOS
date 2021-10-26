#pragma once

#include <stivale2.h>
#include <stdint.h>
#include <stddef.h>

//sample tag
static struct stivale2_header_tag_framebuffer sampleTag = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
        .next = 0
    },
};

struct stivale2module {
    void* base;
	size_t size;
};


//get tag
void* stivale2_get_tag(struct stivale2_struct* stivale2_struct, uint64_t id);

//get module

void stivale2_get_module(struct stivale2_struct* stivale2_struct, struct stivale2module* mod, const char* sig);