#include "names.h"
typedef int TI128 __attribute__((mode(TI)));
typedef unsigned char u8;
/* Copies the position and orientation (three direction vectors) from one object to another. */
void moby_copy_transform(u8 *source, u8 *dest) {
    TI128 *src_vec;
    TI128 *dst_vec;
    int i;
    *(TI128 *)(dest + 0x10) = *(TI128 *)(source + 0x10);
    src_vec = (TI128 *)(source + 0xC0);
    dst_vec = (TI128 *)(dest + 0xC0);
    for (i = 0; i < 3; i++)
        *dst_vec++ = *src_vec++;
}
