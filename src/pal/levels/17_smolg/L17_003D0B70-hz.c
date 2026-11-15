#include "names.h"
/* func_PAL_L17_003D0B70, the PAL copy of func_L17_003CC850: the same C, where 1.0f / 60.0f becomes
   0.020000001f; 0.0011111112544313073f becomes 0.0015584417f; 0.0005555556272156537f becomes
   0.0007894737f. */
#include "common.h"

extern f32 math_fast_sin_or_cos_b(f32);

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    u8 pad00[0x80];
    f32 x;
    f32 y;
    f32 z;
    u8 pad8C[0x340 - 0x8C];
    s32 w340;
} L17Player;

extern L17Player g_hero_state;
extern f32 D_L17_001B04BC SDATA(D_L17_001B04BC);
extern f32 mat_fast_helper_a(f32, f32);
extern f32 FastDiffRots(f32, f32);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 ApproachValue(void *, f32, f32);
extern void add_vectors(void *, void *, void *);

extern s32 coll_is_point_inside_bounds(u8 *a0, TI128 *a1, f32 f1, f32 f2);
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
        if (!(g_hero_state.z < *(f32 *)(a0 + 0x18))) {
            break;
        }
        if (!(FastDiffRots(*(f32 *)(a0 + 0xF8),
                          mat_fast_helper_a(g_hero_state.x - *(f32 *)(a0 + 0x10),
                                      g_hero_state.y - *(f32 *)(a0 + 0x14))) < 1.5707965f)) {
            break;
        }
        if (g_hero_state.w340 != 0) {
            break;
        }
        a0[0x20] = 3;
        st[3] = 0;
        /* fall through */
    case 3:
        if (g_hero_state.w340 != 0) {
            a0[0x20] = 1;
            break;
        }
        here = *(TI128 *)&g_hero_state.x;
        if (coll_is_point_inside_bounds(a0, &here, 60.0f, 2.5f)) {
            ApproachValue(st + 3, st[2] * (0.020000001f), st[2] * 0.0015584417f);
        } else {
            ApproachValue(st + 3, 0.0f, st[2] * 0.0007894737f);
        }
        dir[0] = math_fast_sin_or_cos_a(*(f32 *)(a0 + 0xF8)) * st[3];
        dir[1] = math_fast_sin_or_cos_b(*(f32 *)(a0 + 0xF8)) * st[3];
        dir[2] = 0;
        add_vectors(&here, (u8 *)&g_hero_state + 0x100, dir);
        break;
    }
    if (a0[0x20] != 3) {
        if (*(f32 *)(a0 + 0x18) <= g_hero_state.z) {
            *(TI128 *)dir = *(TI128 *)&g_hero_state.x;
            if (coll_is_point_inside_bounds(a0, (TI128 *)dir, st[0], st[1])) {
                a0[0x20] = 2;
                return;
            }
        }
        if (a0[0x20] != 3) {
            a0[0x20] = 1;
        }
    }
}
