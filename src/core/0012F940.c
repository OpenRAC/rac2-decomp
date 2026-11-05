#include "include_asm.h"

struct IndirectWord
{
    unsigned char reserved[64];
    unsigned int *value;
};

/* Returns the constant integer 1. Matches func_0012F940 disassembly and decompilation. */
int func_0012F940(void) {
    return 1;
}

extern int r1_func_0012BDD0(void *);


/* rac1-decomp src/core/0012AC80.c: func_0012F948 */
int func_0012F948(char *p, unsigned int addr, int size) {
    char *t = *(char **)(p + 0x40);

    *(int *)(t + 0xB0) = 1;
    *(int *)(t + 0xD8) = (addr & 0x0FFFFFFF) | 0x20000000;
    *(int *)(t + 0xE4) = size;
    *(int *)(t + 0xE0) = 0;
    *(int *)(t + 0xDC) = 0;
    return r1_func_0012BDD0(p);
}

unsigned int func_0012F9A8(struct IndirectWord *resource)
{
    return *resource->value;
}
