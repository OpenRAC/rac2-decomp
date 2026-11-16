#include "common.h"

#define F(p, o) (*(f32 *)((u8 *)(p) + (o)))
#define I(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))

extern s32 g_current_map_index[] __attribute__((sda));
extern u8 g_moby_group_flags[] NOT_SDA;
extern u8 g_moby_nibble_table[] NOT_SDA;
extern struct { u8 header[0x464]; u8 collected[0]; } g_level_save_state_backup;
extern u8 g_hero_position[] NOT_SDA;
extern s32 IsPointInCuboid(void *, s32);
extern void moby_set_state(void *, s32, s32);
extern f32 math_fast_sin_or_cos_a(f32);
extern void FastVecScale(void *, void *, f32);
extern void euler_rotation_basis(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern f32 FastAddRotations(f32, f32);
extern f32 math_move_angle_toward_target(f32, f32, f32);
extern s32 math_fast_float_d(void *);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);
extern void gfx_draw_scrolling_ribbon(void *);
extern void mat_combine_and_store(void *, void *, void *, void *);

/* Saves the starting transform, waits for a trigger or saved activation, and
   eases the position and Euler angles through the outgoing and returning states.
   The branch-local counter pointers and blend values have separate lifetimes. */
/* Slides a platform to its second spot when triggered, then slides it back. */
void UpdateTriggeredTransformMover(u8 *moby)
{
    f32 oldPos[4] __attribute__((aligned(16)));
    f32 oldAngle[4] __attribute__((aligned(16)));
    f32 delta[4] __attribute__((aligned(16)));
    f32 rotation[12] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(moby + 0x68);
    s32 level, bits;
    u16 uid;
    u8 *entry;

    qcopy(oldPos, moby + 0x10);
    qcopy(oldAngle, moby + 0xF0);
    switch (moby[0x20]) {
    case 0:
        qcopy(vars + 0x60, moby + 0x10);
        qcopy(vars + 0x70, moby + 0xF0);
        level = g_current_map_index[0];
        I(vars, 0xAC) = 0;
        I(vars, 0xB8) = 0;
        if ((g_moby_group_flags[moby[0xB0] + (level << 4)] & 0x80) ||
            (uid = *(u16 *)(moby + 0xB2), g_level_save_state_backup.collected[(s16)uid]) ||
            (entry = g_moby_nibble_table + (((s16)uid >> 1) + (level << 10)),
            (bits = *entry, (uid & 1) ? (bits >> 4) & 7 : bits & 7))) {
            vars[0xA8] = 1;
            moby_set_state(moby, 2, -1);
        } else {
            moby_set_state(moby, 1, -1);
        }
        break;
    case 1: {
        u16 uid;

        if (moby[0xBC])
            moby_set_state(moby, 2, -1);
        if (I(vars, 0xA0) != -1 && IsPointInCuboid(g_hero_position, I(vars, 0xA0))) {
            uid = *(u16 *)(moby + 0xB2);
            if (uid & 1) {
                u8 *entry = g_moby_nibble_table + (((s16)uid >> 1) + (g_current_map_index[0] << 10));
                if (((*entry >> 4) & 7) != 7)
                    *entry += 0x10;
            } else {
                u8 *entry = g_moby_nibble_table + (((s16)uid >> 1) + (g_current_map_index[0] << 10));
                if ((*entry & 7) != 7)
                    ++*entry;
            }
            vars[0xA8] = 1;
            moby_set_state(moby, 2, -1);
        }
        break;
    }
    case 2: {
        f32 t;

        F(vars, 0xAC) += 1.0f / F(vars, 0xA4);
        if (F(vars, 0xAC) > 1.0f)
            F(vars, 0xAC) = 1.0f;
        else if (F(vars, 0xAC) < 0.0f)
            F(vars, 0xAC) = 0.0f;
        t = 1.0f - math_fast_sin_or_cos_a(F(vars, 0xAC) * 3.14159274f);
        t = t * 0.5f;
        FastVecScale(delta, vars + 0x80, t);
        euler_rotation_basis(rotation, vars + 0x70);
        matrix_mul_vec3(delta, delta, rotation);
        FastVecAdd(moby + 0x10, vars + 0x60, delta);
        F(moby, 0xF8) = math_move_angle_toward_target(F(vars, 0x78), FastAddRotations(F(vars, 0x78), F(vars, 0x98)), t);
        F(moby, 0xF4) = math_move_angle_toward_target(F(vars, 0x74), FastAddRotations(F(vars, 0x74), F(vars, 0x94)), t);
        F(moby, 0xF0) = math_move_angle_toward_target(F(vars, 0x70), FastAddRotations(F(vars, 0x70), F(vars, 0x90)), t);
        if (F(vars, 0xAC) >= 1.0f) {
            I(vars, 0xB0) = H(vars, 0xAA);
            moby_set_state(moby, 3, -1);
        }
        break;
    }
    case 3: {
        u16 uid;

        if (I(vars, 0xA0) != -1 && IsPointInCuboid(g_hero_position, I(vars, 0xA0))) {
            uid = *(u16 *)(moby + 0xB2);
            if (uid & 1) {
                u8 *entry = g_moby_nibble_table + (((s16)uid >> 1) + (g_current_map_index[0] << 10));
                if (((*entry >> 4) & 7) != 7)
                    *entry += 0x10;
            } else {
                u8 *entry = g_moby_nibble_table + (((s16)uid >> 1) + (g_current_map_index[0] << 10));
                if ((*entry & 7) != 7)
                    ++*entry;
            }
            vars[0xA8] = 1;
        }
        if (!vars[0xA8] && !moby[0xBC] && math_fast_float_d(vars + 0xB0))
            moby_set_state(moby, 4, -1);
        break;
    }
    case 4: {
        f32 t;

        F(vars, 0xAC) -= 1.0f / F(vars, 0xA4);
        if (F(vars, 0xAC) > 1.0f)
            F(vars, 0xAC) = 1.0f;
        else if (F(vars, 0xAC) < 0.0f)
            F(vars, 0xAC) = 0.0f;
        t = 1.0f - math_fast_sin_or_cos_a(F(vars, 0xAC) * 3.14159274f);
        t = t * 0.5f;
        FastVecScale(delta, vars + 0x80, t);
        euler_rotation_basis(rotation, vars + 0x70);
        matrix_mul_vec3(delta, delta, rotation);
        FastVecAdd(moby + 0x10, vars + 0x60, delta);
        F(moby, 0xF8) = math_move_angle_toward_target(F(vars, 0x78), FastAddRotations(F(vars, 0x78), F(vars, 0x98)), t);
        F(moby, 0xF4) = math_move_angle_toward_target(F(vars, 0x74), FastAddRotations(F(vars, 0x74), F(vars, 0x94)), t);
        F(moby, 0xF0) = math_move_angle_toward_target(F(vars, 0x70), FastAddRotations(F(vars, 0x70), F(vars, 0x90)), t);
        if (F(vars, 0xAC) >= 1.0f)
            moby_set_state(moby, 1, -1);
        if (moby[0xBC])
            moby_set_state(moby, 2, -1);
        if (I(vars, 0xA0) != -1 && IsPointInCuboid(g_hero_position, I(vars, 0xA0))) {
            vars[0xA8] = 1;
            moby_set_state(moby, 2, -1);
        }
        break;
    }
    }
    if (H(moby, 0xAA) == 0xA9D /* moby class 2717 */ && moby[0x20] >= 2 && moby[0x20] < 5)
        gfx_add_draw_callback_first(gfx_draw_scrolling_ribbon, moby);
    if (moby[0x20] < 5) {
        FastVecSub(delta, moby + 0x10, oldPos);
        mat_combine_and_store(vars + 0x20, delta, oldAngle, moby + 0xF0);
    }
    if (vars[0xA9])
        moby[0xBC] = 0;
}
