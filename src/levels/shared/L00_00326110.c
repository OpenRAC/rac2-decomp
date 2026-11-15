#include "common.h"

extern u8 D_00189EA0[];
extern u32 D_001A79F0 MACRO_ADDR;
extern s32 D_002A0D50[];
extern f32 func_00282E48(u8 *, u8 *);
extern void func_L00_00321878(u8 *, s32, s32, s32, s32, s32, f32);

void func_L00_00326110(u8 *a0, s32 a1, f32 f12) {
    s32 mode = 1;
    u32 i;
    s32 v;

    if (fast_vec_dist(a0 + 0x10, D_00189EA0) < 7.0f)
        mode = 3;
    i = D_001A79F0;
    if (i > 25)
        i = 25;
    v = D_002A0D50[i] * a1 - 1;
    func_L00_00321878(a0, v, v, mode, -1, 0, f12);
}
