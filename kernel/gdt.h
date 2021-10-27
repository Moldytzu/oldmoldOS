#include <stdint.h>

struct GDTDescriptor {
    uint16_t size;
    uint64_t offset;
};

struct GDTSegment {
    uint16_t limit0;
    uint16_t base0;
    uint16_t base1;
    unsigned accessAC:1;
    unsigned accessRW:1;
    unsigned accessDC:1;
    unsigned accessEX:1;
    unsigned accessS:1;
    unsigned accessPrivl:2;
    unsigned accessPr:1;
    unsigned limit1:4;
    unsigned flagAvailable:1;
    unsigned flag64bitCode:1;
    unsigned flagSegmentSize:1;
    unsigned flagGranularity:1;
    uint8_t base2;
};

struct GDT {
    struct GDTSegment kNull; 
    struct GDTSegment kCode; 
    struct GDTSegment kData; 
    struct GDTSegment uNull; 
    struct GDTSegment uCode; 
    struct GDTSegment uData; 
};

extern struct GDT BasicGDT;