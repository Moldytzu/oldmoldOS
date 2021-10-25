#pragma once

#include <stivale2.h>
#include <stdint.h>
#include <stddef.h>

//sample tag
static struct stivale2_header_tag_framebuffer s_tag0 = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
        .next = 0
    },
};

//get tag
void *stivale2_get_tag(struct stivale2_struct *stivale2_struct, uint64_t id);

