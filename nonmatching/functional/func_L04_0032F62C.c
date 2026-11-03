/* functional: medium. Gated SAME in level 04, and in levels 06 and 08 with those levels' D_L06_/D_L08_ names substituted in a test copy (level 08's copy uses 0x1AD8D8/0x1AD8DC/0x1AD900); with the D_L04_ names the gate's alignment mispairs them in 06/08 because retail reuses $at for constants. Retail is hand-written asm (COP1 accumulator, $at as a pointer, lq/sq copies); here plain C with the same reads and writes in the same order. The eight-neighbour sum is accumulated product by product like mula/madda, but the FPU accumulator's rounding is not reproduced. The quadword copies are done as word copies of the same bytes in the same chunk order. The threshold is read as word 7 of D_L04_001AD840, the address retail forms. Retail quirk kept: while D_L04_001AD81C is non-zero the next cell's "old" value is the previous cell's damping amount instead of a reload. */

#include "include_asm.h"

typedef int s32;
typedef unsigned int u32;
typedef unsigned char u8;
typedef float f32;

extern f32 D_L04_001AD818;   /* damping factor */
extern u32 D_L04_001AD81C;   /* non-zero: always store the damped value */
extern s32 D_L04_001AD840[]; /* word 7 (0x1AD85C): float-bits threshold below which the undamped value is stored */

/* Ripple step for patch `index`: from the 24-float-wide work grid at a0 + 0x70
   (16x16 cells with a border), each cell of the patch's row-`row` 16x16 grid is set to
   a quarter of its eight neighbours minus its old value, damped; then the grid's edges
   are copied into the neighbouring patches named by the bytes at patch +0xC..+0x13
   (0xFF = none). Patches are 0x1190 bytes, a row grid 0x5C0 bytes at patch +0x50. */
void func_L04_0032F62C(u32 a0, s32 index, s32 row, void *a3)
{
    u8 *base = (u8 *)a3;
    u8 *patch = base + index * 4496;
    u32 rowoff = row * 1472;
    f32 *src = (f32 *)(a0 + 112);
    f32 *dst = (f32 *)(patch + rowoff + 80);
    f32 k = D_L04_001AD818;
    s32 thr = D_L04_001AD840[7];
    u32 *grid;
    u8 *nbase;
    s32 y, x, i;
    u8 n;

    for (y = 0; y < 16; y++) {
        f32 old = dst[0];
        for (x = 0; x < 16; x++) {
            f32 acc, raw, damp;
            u32 bits;

            acc = src[-25] * 0.25f;
            acc = acc + src[-24] * 0.25f;
            acc = acc + src[-23] * 0.25f;
            acc = acc + src[-1] * 0.25f;
            acc = acc + src[1] * 0.25f;
            acc = acc + src[23] * 0.25f;
            acc = acc + src[24] * 0.25f;
            acc = acc + src[25] * 0.25f;
            raw = acc - old * 1.0f;
            src++;
            dst++;
            bits = *(u32 *)&raw;
            damp = raw * k;
            if (D_L04_001AD81C != 0) {
                /* retail: lwu + bgtz, i.e. any non-zero word */
                old = damp;
                dst[-1] = raw - damp;
            } else {
                s32 d = (s32)(bits & 0x7FFFFFFF) - thr;
                old = dst[0];
                if (d < 0) {
                    *(u32 *)&dst[-1] = bits;
                } else {
                    dst[-1] = raw - damp;
                }
            }
        }
        src += 8;
    }

    grid = (u32 *)(patch + rowoff + 80);
    nbase = base + rowoff + 80;

    n = patch[12];
    if (n != 255) {
        u32 *d = (u32 *)(nbase + n * 4496);
        for (i = 0; i < 4; i++) {
            u32 a0w = grid[i * 4 + 0], a1w = grid[i * 4 + 1], a2w = grid[i * 4 + 2], a3w = grid[i * 4 + 3];
            u32 b0w = grid[16 + i * 4 + 0], b1w = grid[16 + i * 4 + 1], b2w = grid[16 + i * 4 + 2], b3w = grid[16 + i * 4 + 3];
            d[288 + i * 4 + 0] = a0w; d[288 + i * 4 + 1] = a1w; d[288 + i * 4 + 2] = a2w; d[288 + i * 4 + 3] = a3w;
            d[320 + i * 4 + 0] = b0w; d[320 + i * 4 + 1] = b1w; d[320 + i * 4 + 2] = b2w; d[320 + i * 4 + 3] = b3w;
        }
    }
    n = patch[13];
    if (n != 255) {
        u32 *d = (u32 *)(nbase + n * 4496);
        for (i = 0; i < 16; i++) {
            u32 c0 = grid[i * 16 + 0];
            u32 c1 = grid[i * 16 + 1];
            d[304 + i] = c0;
            d[336 + i] = c1;
        }
    }
    n = patch[14];
    if (n != 255) {
        u32 *d = (u32 *)(nbase + n * 4496);
        for (i = 0; i < 16; i++) {
            d[256 + i] = grid[240 + i];
        }
    }
    n = patch[15];
    if (n != 255) {
        u32 *d = (u32 *)(nbase + n * 4496);
        for (i = 0; i < 16; i++) {
            d[272 + i] = grid[i * 16 + 15];
        }
    }
    n = patch[16];
    if (n != 255) {
        u32 *d = (u32 *)(nbase + n * 4496);
        u32 c0 = grid[0], c1 = grid[1], c16 = grid[16];
        d[355] = c0;
        d[356] = c1;
        d[357] = c16;
    }
    n = patch[17];
    if (n != 255) {
        u32 *d = (u32 *)(nbase + n * 4496);
        d[354] = grid[15];
    }
    n = patch[18];
    if (n != 255) {
        u32 *d = (u32 *)(nbase + n * 4496);
        d[353] = grid[240];
    }
    n = patch[19];
    if (n != 255) {
        u32 *d = (u32 *)(nbase + n * 4496);
        d[352] = grid[255];
    }
}
