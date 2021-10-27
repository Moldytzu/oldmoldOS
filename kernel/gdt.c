#include <gdt.h>

struct GDT BasicGDT = {
    //kernel
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //null
    {0,0,0,0,0,0,1,1,0,1,0,1,1,1,1,0}, //read only, executable in ring 0, system segment, ring 0, present
    {0,0,0,0,1,0,0,1,0,1,0,1,0,1,1,0}, //read & write, not executable, system segment, ring 0, present

    //code
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //null
    {0,0,0,0,0,0,1,1,3,1,0,1,1,1,1,0}, //read only, executable in ring 3, system segment, ring 3, present
    {0,0,0,0,1,0,0,1,3,1,0,1,0,1,1,0}, //read & write, not executable, system segment, ring 3, present
}; 