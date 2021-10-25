#include <bootloaderif.h>

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