#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern float g_active_slot_effect_count __attribute__((sda));
extern s32 g_slot_effect_in_use[5] MACRO_ADDR;
extern u8 g_hero_l23_state_block[];
extern void *CreateMoby(s32);
extern float math_random_signed_float_range(float, float);
extern s32 math_fast_helper_a(void *, float);
extern float fast_vec_dist(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecDot(void *, void *);
extern float math_fast_angle_helper(float);
extern void part_spawn_fire_explosion_pal(void *);

/* spawns object 0x11DF at pos with parent's orientation, when one of the five slots is free:
   fills its vars from the arguments and, if it is in view, grades it against the reference
   point at D_L23_001BA500 + 0x140 */
void *slot_effect_create_pal(u8 *pos, u8 *parent, s32 flag, float scale, s32 value3, s32 value4, s32 value5,
                        s32 value6, s32 value7, s32 value8, s32 value9, s32 value10, s32 value11, s32 value12) {
    TI128 sphere;
    TI128 dir;
    s32 i;
    u8 *effect;
    u8 *vars;
    float angle;

    if (g_active_slot_effect_count == -1.0f) {
        for (i = 0; i < 5; i++) {
            g_slot_effect_in_use[i] = 0;
        }
        g_active_slot_effect_count = 0.0f;
    }
    if (g_active_slot_effect_count >= 5.0f) {
        return 0;
    }
    for (i = 0; i < 5; i++) {
        if (g_slot_effect_in_use[i] == 0) {
            break;
        }
    }
    g_active_slot_effect_count += 1.0f;
    g_slot_effect_in_use[i] = 1;
    effect = CreateMoby(0x11DF);
    if (effect != 0) {
        vars = *(u8 **)(effect + 0x68);
        effect[0x30] = 0xFF;
        *(s16 *)(effect + 0x32) = 0xFF;
        effect[0x20] = 0;
        *(s32 *)(vars + 0x3C) = i;
        qcopy(effect + 0x10, pos);
        *(float *)(effect + 0x1C) = 1.0f;
        qcopy(effect + 0xC0, parent + 0xC0);
        qcopy(effect + 0xD0, parent + 0xD0);
        qcopy(effect + 0xE0, parent + 0xE0);
        *(float *)(effect + 0xCC) = *(float *)(effect + 0xDC) = *(float *)(effect + 0xEC) = 0.0f;
        *(s32 *)(vars + 0x20) = value3;
        *(s32 *)(vars + 0x24) = value4;
        *(s32 *)(vars + 0x28) = value5;
        *(s32 *)(vars + 0x2C) = value6;
        *(float *)(vars + 0x14) = scale;
        *(s32 *)(vars + 0x30) = value7;
        *(s32 *)(vars + 0x34) = value9;
        *(s32 *)(vars + 0x48) = value12;
        *(s16 *)vars = 0x32;
        *(s16 *)(vars + 2) = 0x32;
        *(float *)(vars + 8) = scale + scale;
        *(float *)(vars + 0xC) = scale * 4.0f;
        *(s32 *)(vars + 0x1C) = value10;
        *(s32 *)(vars + 0x38) = value11;
        *(s32 *)(vars + 0x18) = value8;
        *(float *)(vars + 0x44) = math_random_signed_float_range(65.0f, 80.0f);
        qcopy(&sphere, effect + 0x10);
        ((float *)&sphere)[3] = scale * 3.0f;
        if (math_fast_helper_a(&sphere, 128.0f) == 1) {
            *(s16 *)(vars + 4) = 0x15;
            *(float *)(vars + 0x10) = 0.04761905f;
            if (fast_vec_dist(pos, g_hero_l23_state_block + 0x140) < 48.0f && flag != 0) {
                u8 *ref = g_hero_l23_state_block;
                *(s32 *)(ref + 0x16C) = 0;
                *(s32 *)(ref + 0x168) = 0x21;
                *(float *)(ref + 0x160) = 0.075f;
            }
            if (*(s32 *)(vars + 0x18) != 0) {
                FastVecSub(&dir, effect + 0x10, g_hero_l23_state_block + 0x140);
                vec_scale_to_length(&dir, &dir, 1.0f);
                angle = math_fast_angle_helper(FastVecDot(&dir, g_hero_l23_state_block + 0x370));
                if (1.5707964f - angle < 0.45378566f) {
                    *(s32 *)(vars + 0x18) = 1;
                } else {
                    *(s32 *)(vars + 0x18) = 0;
                }
            }
        } else {
            *(s16 *)(vars + 4) = 0;
            *(s32 *)(vars + 0x18) = 0;
        }
        part_spawn_fire_explosion_pal(effect);
    }
    return effect;
}
