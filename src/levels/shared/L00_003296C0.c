#include "common.h"

extern u8 **ref_L00_003296C0_00;

/* Adds an object with a value to the end of the numbered list. */
void func_L00_003296C0(void *object, int index, int value) {
    u8 **first, **second;
    int offset;

    if (!object)
        return;
    first = (u8 **)(index * 4 + (unsigned int)ref_L00_003296C0_00);
    offset = (*first)[4] * 8;
    *(void **)(offset + (unsigned int)*first) = object;
    *(u8 *)(offset + (unsigned int)*first + 5) = value;
    second = (u8 **)(index * 4 + (unsigned int)ref_L00_003296C0_00);
    *(unsigned short *)(offset + (unsigned int)(*second) + 6) = 0;
    ++(*second)[4];
}
