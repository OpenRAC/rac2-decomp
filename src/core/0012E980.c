#include "common.h"
#include "structs.h"

extern long r1_func_0012AAC8();

extern long r1_func_0012AAC8(void *, int);

extern int r1_func_0012AAA8(void *, int);

/* rac1-decomp src/core/0012A2F0.c: func_0012AB60 */
/* Get n bits: peek them (r1_func_0012AAA8), then consume them
   (r1_func_0012AAC8). */
int mpeg_get_bits_from_stream(void *stream, int bitCount) {
    int bits = r1_func_0012AAA8(stream, bitCount);
    r1_func_0012AAC8(stream, bitCount);
    return bits;
}
