/* func_L07_0040F8F8: retained near miss, 30 October 2026.
   Profile: -O2 -G8 -ffunction-sections.
   Local checks: 424/408 bytes, 0/1 in each of USA v1.01, v2.00 and PAL.
   No strict linked match is claimed.

   Standalone canonical-symbol variant of func_L07_0040F8F8.c. The old draft
   remains unchanged. A one-dimensional vector array and a real 16-byte
   TIMode clear still do not produce the two retail bases and offsets.
   qzero_nc, -fno-force-mem, -fno-rerun-loop-opt and -fno-gcse did not match.
*/

#include "common.h"
typedef struct { f32 lane[4]; } Vector;
extern Vector D_L07_002A0100[];
extern void func_00282CC0(void *a, void *b, u8 *c);
extern f32 func_00282E48(void *, void *);
extern void func_00282D30(u8 *a, u8 *b, f32 c);

#define REC(i) ((u8 *)&D_L07_002A0100[(i) * 18])
#define REC2(i) (b + (i) * 0x120)
#define W(p) (*(f32 *)((p) + 0xC))

void func_L07_0040F8F8(void)
{
    union { s32 q __attribute__((mode(TI))); f32 f[4]; } sum;
    s32 i, n, k;
    u8 *b = (u8 *)D_L07_002A0100;

    for (i = 0; i < 3; i++) {
        n = 0;
        sum.q = 0;
        if (W(REC(i)) == 1.0f) {
            do {
                func_00282CC0(&sum, &sum, REC2(i) + n * 0x10);
                n++;
            } while (W(REC(i) + n * 0x10) == 1.0f);
        }
        func_00282D30(REC(i) + n * 0x10, REC(i) + n * 0x10, 1.0f / n);
        W(REC(i) + n * 0x10) = 0.0f;
        for (k = 0; k < n; k++) {
            f32 d = func_00282E48(REC2(i) + k * 0x10, REC2(i) + n * 0x10) + 4.0f;
            if (W(REC2(i) + n * 0x10) < d)
                W(REC2(i) + n * 0x10) = d;
        }
    }
}
