/* func_PAL_L17_003D0B70, the PAL copy of func_L17_003CC850: the same C, where 1.0f / 60.0f becomes
   0.020000001f; 0.0011111112544313073f becomes 0.0015584417f; 0.0005555556272156537f becomes
   0.0007894737f. */
#include "common.h"

extern f32 func_00283198(f32);

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    u8 pad00[0x80];
    f32 x;
    f32 y;
    f32 z;
    u8 pad8C[0x340 - 0x8C];
    s32 w340;
} L17Player;

extern L17Player D_00189E20;
extern f32 D_L17_001B04BC SDATA(D_L17_001B04BC);
extern f32 func_00283248(f32, f32);
extern f32 func_00283C80(f32, f32);
extern f32 func_00283180(f32);
extern f32 func_002AA2E8(void *, f32, f32);
extern void func_00282CD8(void *, void *, void *);

extern s32 func_L17_003CC798(u8 *a0, TI128 *a1, f32 f1, f32 f2);
void func_PAL_L17_003D0B70(u8 *a0)
{
    f32 *st = *(f32 **)(a0 + 0x68);
    TI128 here __attribute__((aligned(16)));
    f32 dir[4] __attribute__((aligned(16)));

    st[2] = D_L17_001B04BC;
    switch (a0[0x20]) {
    case 0:
        *(f32 *)(a0 + 0x18) = *(f32 *)(a0 + 0x18) - 0.05f;
        a0[0x20] = 1;
        *(u16 *)(a0 + 0x34) |= 0x41;
        break;
    case 1:
        break;
    case 2:
        if (!(D_00189E20.z < *(f32 *)(a0 + 0x18))) {
            break;
        }
        if (!(func_00283C80(*(f32 *)(a0 + 0xF8),
                          func_00283248(D_00189E20.x - *(f32 *)(a0 + 0x10),
                                      D_00189E20.y - *(f32 *)(a0 + 0x14))) < 1.5707965f)) {
            break;
        }
        if (D_00189E20.w340 != 0) {
            break;
        }
        a0[0x20] = 3;
        st[3] = 0;
        /* fall through */
    case 3:
        if (D_00189E20.w340 != 0) {
            a0[0x20] = 1;
            break;
        }
        here = *(TI128 *)&D_00189E20.x;
        if (func_L17_003CC798(a0, &here, 60.0f, 2.5f)) {
            func_002AA2E8(st + 3, st[2] * (0.020000001f), st[2] * 0.0015584417f);
        } else {
            func_002AA2E8(st + 3, 0.0f, st[2] * 0.0007894737f);
        }
        dir[0] = func_00283180(*(f32 *)(a0 + 0xF8)) * st[3];
        dir[1] = func_00283198(*(f32 *)(a0 + 0xF8)) * st[3];
        dir[2] = 0;
        func_00282CD8(&here, (u8 *)&D_00189E20 + 0x100, dir);
        break;
    }
    if (a0[0x20] != 3) {
        if (*(f32 *)(a0 + 0x18) <= D_00189E20.z) {
            *(TI128 *)dir = *(TI128 *)&D_00189E20.x;
            if (func_L17_003CC798(a0, (TI128 *)dir, st[0], st[1])) {
                a0[0x20] = 2;
                return;
            }
        }
        if (a0[0x20] != 3) {
            a0[0x20] = 1;
        }
    }
}
