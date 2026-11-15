#include "include_asm.h"

#include "common.h"
extern f32 FastAddRotations(f32 a, f32 b);
extern f32 func_2E4918(f32 a, f32 b);
extern f32 D_L07_001B0F84 __attribute__((sda));
extern u8 *g_moby_l07_array __attribute__((sda));
extern u8 *func_2CD050(s32 a);
extern s32 func_312FA8(u8 *a, s32 b, s32 c);
extern f32 func_313008(u8 *a, s32 b);
extern f32 D_L07_001B10B8 __attribute__((sda));
extern f32 D_L07_001B10BC __attribute__((sda));
extern u32 D_L07_001B10C0 __attribute__((sda));
extern f32 D_L07_001B0FD0 __attribute__((sda));
extern f32 D_L07_001B0E98 __attribute__((sda));
extern f32 D_L07_001B0E9C __attribute__((sda));
extern f32 D_L07_001B0EA0 __attribute__((sda));
extern f32 ApproachValue(f32 *value, f32 target, f32 step);
extern f32 FastAddRotations(f32 a, f32 b);
extern s32 coll_cast_object_line(void *a, void *b, void *c, s32 d, f32 e, f32 f, s32 g, s32 h, s32 i);
extern f32 D_L07_001B173C;
extern u8 D_L07_001B1730 __attribute__((sda));
extern u8 *D_L07_001B2954;
extern u8 *D_L07_001B295C;
extern s32 D_L07_001B1E90;
extern u8 *cam_alloc_override_slot(s32);
extern f32 mat_fast_helper_a(f32 a, f32 b);
extern f32 fast_subtract_rotations(f32 a, f32 b);
extern f32 math_approach_target_with_direction_mode(void *a0, void *a1, f32 a2, f32 a3, f32 a4, f32 a5, s32 a6);
extern f32 D_L07_001B17D4 __attribute__((sda));
extern f32 D_L07_001B17D8 __attribute__((sda));
extern u8 *D_L07_001B9250 __attribute__((nosda));
extern u8 *D_L07_001ADAAC MACRO_ADDR;
extern u8 D_L07_001B31A9;
extern u8 g_hero_state[];
extern u32 D_L07_001B1E08 MACRO_ADDR;
extern f32 fast_vec_dist(u8 *a, u8 *b);
extern f32 D_L07_001B0FD0 __attribute__((sda));
extern u8 *D_L07_001C36C0[];

/* Steers the object's two angles: the yaw toward the argument, the pitch from the shared
   record, and the two scaled fields of the state record. */
void func_PAL_L07_004143A0(u8 *a0)
{
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *v1;
    u8 *v0;
    f32 *p;
    f32 t;
    f32 r;
    f32 q;
    f32 f20;
    f32 f21;
    f32 f22;

    v1 = D_L07_001B9250;
    if (*(s16 *)(v1 + 0x86) != 0) {
        return;
    }
    v0 = D_L07_001ADAAC;
    if (v0 == 0) {
        return;
    }
    f22 = 3.14159274f;
    s0 = *(u8 **)(v1 + 0x70);
    s1 = *(u8 **)(a0 + 0x68);
    p = (f32 *)(s0 + 0x160);
    r = FastAddRotations(*(f32 *)(v0 + 0xF8), f22);
    s2 = s0 + 0x1C0;
    q = mat_fast_helper_a(p[0], p[1]);
    t = fast_subtract_rotations(r, q);
    f21 = D_L07_001B17D4 * 6.981318e-06f;
    f20 = D_L07_001B17D8 * 0.0003490659f;
    if (D_L07_001B31A9 == 0) {
        t = FastAddRotations(t, f22);
    }
    math_approach_target_with_direction_mode(&t, s1 + 0x1A8, 0.0f, f21, f21, f20, 0);
    *(f32 *)(s2 + 0x1C) = 1.0f;
    *(f32 *)(s2 + 0x14) = -*(f32 *)(s1 + 0x1A8);
}
