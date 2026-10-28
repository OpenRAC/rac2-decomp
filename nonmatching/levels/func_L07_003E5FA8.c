/* func_L07_003E5FA8 - 412 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   draft.c = new file L07_003E5FA8-g8.c (-G8). Logic decoded; some floats via
   gp (sda), their neighbours +4 absolute (plain extern) as in retail. 384 vs
   412 bytes.
   Retail uses 7 saved regs: obj in s1, &d(sp+0x30) twice (s4 for qzero and s2
   for calls), pos s5, obj+0xC0 s6, f21=1/60 const, f20=size from
   func_002A7878 (evaluated BEFORE func_002A77E0; fixed via local `size`).
   Mine: 6 regs, obj in s0. Tried a `dp = d` alias pointer (adds 12 bytes,
   still different alloc), st load order. */

#include "common.h"

extern void func_002AD0E0(void *, void *, void *, void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002A7A00(void *, float, float);
extern void func_00283098(void *, void *, void *);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern void func_002C3150(void *, void *, int, int, int, int, float);
extern float D_L07_001B0AD8 __attribute__((sda));
extern float D_L07_001B0AB0 __attribute__((sda));
extern float D_L07_001B0AB4;
extern int D_L07_001B0AD0 __attribute__((sda));
extern int D_L07_001B0AD4;
extern float D_L07_001B0AC0 __attribute__((sda));
extern float D_L07_001B0AC4;
extern int D_L07_001B0AC8 __attribute__((sda));

void func_L07_003E5FA8(u8 *obj) {
    f32 a[4] __attribute__((aligned(16)));
    f32 b[4] __attribute__((aligned(16)));
    f32 c[4] __attribute__((aligned(16)));
    f32 d[4] __attribute__((aligned(16)));
    u8 *st = *(u8 **)(obj + 0x68);
    u8 *target = *(u8 **)(st + 0x260);
    u8 *pos;
    int i;
    int color;
    f32 size;

    qzero(b);
    if (target != 0) {
        pos = obj + 0x10;
        func_002AD0E0(obj, target, pos, b, a, b);
        func_00282CF0(a, a, pos);
    } else {
        qzero(a);
        pos = obj + 0x10;
    }
    for (i = 0; i < 2; i++) {
        qzero(d);
        d[2] = D_L07_001B0AD8;
        if (i == 0) {
            d[2] = -d[2];
        }
        func_002A7A00(c, D_L07_001B0AB0 * 0.016666668f, D_L07_001B0AB4 * 0.016666668f);
        func_00282CC0(c, c, a);
        color = func_002A7820(D_L07_001B0AD0, D_L07_001B0AD4);
        func_00283098(d, d, obj + 0xC0);
        func_00282CC0(d, d, pos);
        size = func_002A7878(D_L07_001B0AC0, D_L07_001B0AC4);
        func_002C3150(d, c, D_L07_001B0AC8, color & 0xFF, func_002A77E0(0xFF) & 0xFF, 0, size);
    }
}
