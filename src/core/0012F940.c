#include "include_asm.h"
#include "names.h"

struct IndirectWord
{
    unsigned char reserved[64];
    unsigned int *value;
};

/* Returns the constant integer 1. Matches func_0012F940 disassembly and decompilation. */
int mpeg_return_one(void) {
    return 1;
}

extern int r1_func_0012BDD0(void *);


/* rac1-decomp src/core/0012AC80.c: func_0012F948 */
/* Gives the movie decoder the address and size of its output buffer. */
int mpeg_set_output_buffer(char *mpeg, unsigned int addr, int size) {
    char *decoder = *(char **)(mpeg + 0x40);

    *(int *)(decoder + 0xB0) = 1;
    *(int *)(decoder + 0xD8) = (addr & 0x0FFFFFFF) | 0x20000000;
    *(int *)(decoder + 0xE4) = size;
    *(int *)(decoder + 0xE0) = 0;
    *(int *)(decoder + 0xDC) = 0;
    return r1_func_0012BDD0(mpeg);
}

/* Reads the value that a resource points to. */
unsigned int mpeg_read_indirect_word(struct IndirectWord *resource)
{
    return *resource->value;
}
