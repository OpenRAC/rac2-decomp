#include "include_asm.h"

#include "common.h"
extern s32 math_random_int_below(s32 arg0);
extern s32 arena_get_fighter_count(s32 arg0);
extern s32 D_L11_001B056C __attribute__((sda));
extern s32 D_L11_001B058C __attribute__((sda));
extern f32 D_L11_001B0670;
extern u8 *part_find_owned_effect_slot(s32 arg0, s32 arg1, s32 arg2);
extern f32 moby_update_aim_target_strength(u8 *arg0, u8 *arg1);
extern s32 part_spawn_damage_debris(u8 *arg0, u8 *arg1, u8 *arg2);
extern s32 weapon_select_aim_target(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5);
extern f32 D_L11_001B0570 __attribute__((sda));
extern s32 D_L11_001FFA78[];
extern void matrix_mul_vec3(void *out, void *in, void *matrix);
extern void FastVecAdd(void *out, void *in, void *matrix);
extern f32 mat_fast_helper_a(f32 a0, f32 a1);
extern void euler_rotation_basis(void *a0, void *a1);
extern s32 FloatToInt(f32 a0);
extern void func_PAL_L11_0043BE90(u8 *a0, s32 a1, s32 a2);
extern void func_PAL_L11_0044F150(u8 *a0, s32 a1, s32 a2);
extern void func_PAL_L11_00451E08(u8 *a0, s32 a1, s32 a2);
extern void func_PAL_L11_00458828(u8 *a0, s32 a1, s32 a2);
extern void func_PAL_L11_0045A848(u8 *a0, s32 a1, s32 a2);
extern void func_PAL_L11_0045C028(u8 *a0, s32 a1);
extern u32 D_L11_001B0D9C __attribute__((sda));
extern u8 g_hero_state[];

/* Places the measured point on the state's three vertices, then walks them: each one gets
   its angle to the shared origin and the class call its identifier names. */
void func_PAL_L11_0041C088(u8 *arg0) {
    u8 *s0 = arg0;
    u8 *s1 = *(u8 **)(s0 + 0x68);
    u8 *p;
    u8 *base;
    f32 loc[4];
    s32 total;
    s32 i;

    loc[0] = 0.0f;
    loc[1] = -9.0f;
    loc[2] = -3.0f;
    loc[3] = 0.0f;
    matrix_mul_vec3(loc, loc, s0 + 0xC0);
    FastVecAdd(loc, loc, s0 + 0x10);

    if (*(u8 **)(s1 + 0x10) != 0) {
        *(f32 *)(*(u8 **)(s1 + 0x10) + 0x10) = loc[0] - 2.0f;
        *(f32 *)(*(u8 **)(s1 + 0x10) + 0x14) = loc[1];
        *(f32 *)(*(u8 **)(s1 + 0x10) + 0x18) = loc[2];
        *(f32 *)(*(u8 **)(s1 + 0x10) + 0x1C) = loc[3];
    }
    if (*(u8 **)(s1 + 0x14) != 0) {
        *(f32 *)(*(u8 **)(s1 + 0x14) + 0x10) = loc[0];
        *(f32 *)(*(u8 **)(s1 + 0x14) + 0x14) = loc[1] + 1.0f;
        *(f32 *)(*(u8 **)(s1 + 0x14) + 0x18) = loc[2];
        *(f32 *)(*(u8 **)(s1 + 0x14) + 0x1C) = loc[3];
    }
    if (*(u8 **)(s1 + 0x18) != 0) {
        *(f32 *)(*(u8 **)(s1 + 0x18) + 0x10) = loc[0];
        *(f32 *)(*(u8 **)(s1 + 0x18) + 0x14) = loc[1] - 1.0f;
        *(f32 *)(*(u8 **)(s1 + 0x18) + 0x18) = loc[2];
        *(f32 *)(*(u8 **)(s1 + 0x18) + 0x1C) = loc[3];
    }

    base = g_hero_state;
    p = *(u8 **)(s1 + 0x10);
    total = 0;
    for (i = 0; i < 3; i++) {
        if (i == 1) {
            p = *(u8 **)(s1 + 0x14);
        }
        if (i == 2) {
            p = *(u8 **)(s1 + 0x18);
        }
        if (p == 0) {
            continue;
        }
        *(s32 *)(p + 0xF0) = 0;
        *(f32 *)(p + 0xF4) = 0.0f;
        *(f32 *)(p + 0xF8) = mat_fast_helper_a(*(f32 *)(base + 0x80) - *(f32 *)(p + 0x10),
                                          *(f32 *)(base + 0x84) - *(f32 *)(p + 0x14));
        *(s32 *)(p + 0xFC) = 0;
        euler_rotation_basis(p + 0xC0, p + 0xF0);
        switch (*(s16 *)(p + 0xAA)) {
        case 0xD98:
            func_PAL_L11_0044F150(p, total, 0);
            break;
        case 0xDCF:
            func_PAL_L11_00451E08(p, total, 0);
            break;
        case 0xDF4:
            func_PAL_L11_00458828(p, total, 0);
            break;
        case 0xDF7:
            *(f32 *)(p + 0x18) += 0.5f;
            func_PAL_L11_0045A848(p, FloatToInt((f32)total * 0.16666667f), 0);
            break;
        case 0xDF9:
            func_PAL_L11_0045C028(p, total);
            break;
        case 0xD37:
            func_PAL_L11_0043BE90(p, total, 0);
            break;
        }
        total += ((s32)(D_L11_001B0D9C) * 5 + 2) / 6;
    }

    *(u8 **)(s1 + 0x10) = 0;
    *(u8 **)(s1 + 0x14) = 0;
    *(u8 **)(s1 + 0x18) = 0;
}
