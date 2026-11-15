#include "include_asm.h"
#include "common.h"
extern f32 func_2E5318(f32 a, f32 b);
extern f32 func_2E4918(f32 a, f32 b);
extern f32 D_L07_001B0F84 __attribute__((sda));
extern u8 *g_moby_l07_array __attribute__((sda));
extern u8 *func_2CD050(s32 a);
extern s32 func_312FA8(u8 *a, s32 b, s32 c);
extern f32 func_313008(u8 *a, s32 b);
extern f32 D_L07_001B10B8 __attribute__((sda));
extern f32 D_L07_001B10BC __attribute__((sda));
extern f32 D_L07_001B0FD0 __attribute__((sda));
extern f32 D_L07_001B0E98 __attribute__((sda));
extern f32 D_L07_001B0E9C __attribute__((sda));
extern f32 D_L07_001B0EA0 __attribute__((sda));
extern f32 ApproachValue(f32 *value, f32 target, f32 step);
extern f32 FastAddRotations(f32 a, f32 b);
extern s32 coll_cast_object_line(void *a, void *b, void *c, s32 d, f32 e, f32 f, s32 g, s32 h, s32 i);
typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    u8 pad00[0x34];
    u16 flags34;
    u8 pad36[0x68 - 0x36];
    u8 *state;
    u8 pad6c[0x98 - 0x6C];
    s32 f98;
} SibObj;
typedef struct {
    u8 pad00[0xCC];
    s32 groupCC;
    s32 groupD0;
} SibGroups;
extern f32 D_L07_001B173C;
extern u8 D_L07_001B1730 __attribute__((sda));
extern u16 **D_L07_001A9014;
extern u8 *D_L07_001B2954;
extern u8 *D_L07_001B295C;
extern s32 D_L07_001B1E90;
extern void hero_reset_position_and_direction(void *obj, void *pos, s32 a2, s32 a3);
extern void gfx_setup_scale_record(s32 id, s32 a1);

/* Switches the object to its second phase. */
void func_PAL_L07_00415868(SibObj *a0)
{
    f32 arg[4];
    f32 v[4];
    SibGroups *state;
    u16 *p;
    u16 *q;
    u8 *e;

    *(TI128 *)v = 0;
    v[2] = D_L07_001B173C;
    *(TI128 *)arg = *(TI128 *)v;
    state = (SibGroups *)a0->state;
    hero_reset_position_and_direction(&D_L07_001B1730, arg, 0, 1);
    a0->flags34 |= 2;
    a0->f98 = 0;
    for (p = D_L07_001A9014[state->groupD0];
         p != 0 && ((s16)p[-1] >= 0 || p == D_L07_001A9014[state->groupD0]) &&
         (e = D_L07_001B2954 + ((*p & 0x7FFF) << 5)) != 0;
         p++) {
        e[0x1E] &= 0xFB;
    }
    for (p = D_L07_001A9014[state->groupCC];
         p != 0 && ((s16)p[-1] >= 0 || p == D_L07_001A9014[state->groupCC]) &&
         (e = D_L07_001B2954 + ((*p & 0x7FFF) << 5)) != 0;
         p++) {
        e[0x1E] |= 4;
    }
    for (q = D_L07_001A9014[state->groupCC];
         q != 0 && ((s16)q[-1] >= 0 || q == D_L07_001A9014[state->groupCC]) &&
         (e = D_L07_001B295C + ((*q & 0x7FFF) << 6)) != 0;
         q++) {
        *(f32 *)(e + 0x38) -= 100.0f;
        gfx_setup_scale_record(*q & 0x7FFF, 1);
    }
    D_L07_001B1E90 = 2;
}
