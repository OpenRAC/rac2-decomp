#include "include_asm.h"
#include "common.h"

/* Own unit: -G8 for the small-data scale factors, -fno-sched-spec for the loop. */

extern char D_00237700[];
extern char D_001B2830[] __attribute__((section(".sdata")));
extern float D_001B0970 __attribute__((sda));
extern float D_001B096C __attribute__((sda));
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);

/* Fills the eight-vector table D_00237700 from the object's two axis rows
   (+0xC0, +0xD0): entries 4-7 are row0, -row0, -row1, row1, entries 0-3 the
   four sums of a signed row0 and a signed row1. Every entry is then scaled,
   moved to the object's position (+0x10) and offset by D_001B2830. Writing
   the table through `base` before the loop and through `out` in it keeps the
   two pointers apart, as retail's allocation needs. */
void BuildObjectBasisVectors(char *object)
{
    char vectors[4][16] __attribute__((aligned(16)));
    char temp[16] __attribute__((aligned(16)));
    char sum[16] __attribute__((aligned(16)));
    char *base = D_00237700;
    char *out;
    char *pos;
    int i;

    qcopy(vectors[0], object + 0xC0);
    qcopy(vectors[3], object + 0xD0);
    FastVecScale(vectors[1], vectors[0], -1.0f);
    FastVecScale(vectors[2], vectors[3], -1.0f);
    qcopy(base + 0x40, vectors[0]);
    qcopy(base + 0x50, vectors[1]);
    qcopy(base + 0x60, vectors[2]);
    qcopy(base + 0x70, vectors[3]);
    pos = object + 0x10;
    out = base;
    for (i = 0; i < 8; i++) {
        if (i < 4)
            FastVecAdd(out, vectors[i >> 1], vectors[2 + (i & 1)]);
        vec_scale_to_length(out, out, D_001B0970);
        FastVecAdd(out, out, pos);
        vec_scale_to_length(temp, D_001B2830, -D_001B096C);
        FastVecAdd(out, out, temp);
        out += 16;
        FastVecAdd(sum, temp, pos);
    }
}
