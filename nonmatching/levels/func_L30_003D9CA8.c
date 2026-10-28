/* func_L30_003D9CA8 - 436 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Block-move copy of the 0x90 struct (Block local = *src) compiles to ld/sd
   loop, retail is lq/sq loop (same as nonmatching func_00288870: compiler
   lacks TImode block moves). Rest of the body decoded (see draft). Needs
   flags -O2 -G8 -frac2-qcopy -frac2-qcopy-barrier. */

#include "include_asm.h"

/* Needs the small-data profile (-G8) together with the quadword copy and its scheduling
   barrier (config/cflags.txt). */

typedef int TQ __attribute__((mode(TI)));
typedef float Vec4[4] __attribute__((aligned(16)));

typedef union {
    Vec4 m[4];
    TQ q[9];
} Block;

extern Vec4 D_001B09B0[4] __attribute__((sda));
extern char D_001B9DC0[];

extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(void *, int, int);

void func_L30_003D9CA8(float *origin, Block *src, float scale_a, float scale_b) {
    Block block = *src;
    Vec4 axis = {0.0f, 0.0f, 1.0f, 1.0f};
    Vec4 a, b, c, d;
    Vec4 pos;
    int i;

    *(TQ *)pos = *(TQ *)origin;
    func_00282CF0(a, D_001B9DC0, pos);
    func_00282F20(a, a, 1.0f);
    func_00282DD8(b, a, axis);
    func_00282F20(b, b, 1.0f);
    func_00282DD8(c, b, a);
    func_00282D30(d, a, scale_b);
    func_00282CC0(pos, pos, d);
    for (i = 0; i < 4; i++) {
        func_00282D30(block.m[i], D_001B09B0[i], scale_a);
        func_002830C0(block.m[i], block.m[i], a);
    }
    func_00280B90(&block, 0, 0);
}
