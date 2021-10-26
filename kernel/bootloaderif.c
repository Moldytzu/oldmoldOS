#include <bootloaderif.h>
#include <utils.h>

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

void stivale2_get_module(struct stivale2_struct* stivale2_struct, struct stivale2module* mod, const char* sig) {
	struct stivale2_struct_tag_modules* stivale2_modules = (struct stivale2_struct_tag_modules*)stivale2_get_tag(stivale2_struct, STIVALE2_STRUCT_TAG_MODULES_ID);
	for(size_t i = 0; i < stivale2_modules->module_count; i++) {
		struct stivale2_module* stivale2_module_ = &stivale2_modules->modules[i];
        if(strcmp(stivale2_module_->string,sig)!=0) continue; 
	    mod->base = (void*)stivale2_module_->begin;
        mod->size = stivale2_module_->end - stivale2_module_->begin;
        return;
	}
}