#include "common.h"

extern void muckdweller_update_targeting(void *);
extern void muckdweller_init(void *);
extern void part_spawn_moving_bubbles(void *);
extern void muckdweller_tick_timers(void *);
extern void muckdweller_find_farthest_anchor(void *, void *);
extern void moby_move_keeping_transform_alt(void *, void *);
extern s32 moby_move_keeping_transform(void *, void *);
extern void muckdweller_fire_spit_shot(void *, s32);
extern void part_spawn_puffs_around_point(void *, s32);
extern void part_queue_moby_for_glow(void *, s32, s32);
extern s32 FastDecTimer(void *);
extern s32 func_001163B0(void);
extern s32 math_random_int_range(s32, s32);
extern s32 math_random_int_below(s32);
extern s32 moby_dispatch_action_by_kind(void *, void *);
extern s32 level_has_pending_inner_flag(void *);
extern void anim_start_blended(void *, s32, s32, s32);
extern void moby_set_state(void *, s32, s32);
extern void SetDeathBits(void *, s32, s32);
extern f32 math_fabs(f32);
extern f32 FastVecLength(void *);
extern f32 vec_distance_xy(void *, void *);
extern f32 mat_fast_helper_a(f32, f32);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern f32 moby_get_anim_value(void *);
extern f32 math_random_signed_float_range(f32, f32);
extern f32 coll_probe_ground_height_below(void *, s32, f32);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void matrix_mul_vec3(void *, void *, void *);
extern void euler_to_matrix(void *, void *);
extern void matrix_from_basis_rows(void *, void *);
extern f32 weapon_compute_shot_launch_speed(void *, void *, void *, f32, f32);
extern void MobySpringTurn(void *, f32, f32, f32, f32, void *);
extern f32 math_approach_target_with_direction_mode(void *, f32, f32, f32, f32, void *, s32);
extern int coll_test_hit_at_bone(void *, s32, s32, s32, s32, s32, f32, f32, f32);
extern u8 g_hero_state[];
extern u8 g_monster_vector_template[] MACRO_ADDR;

/* A 16-bit struct stays in HImode, so a local copy loads with lhu and tests with sll. */
typedef struct { s16 value; } Timer16;
typedef unsigned int UpdateQuad __attribute__((mode(TI)));

#define F(p, o) (*(f32 *)((p) + (o)))
#define I(p, o) (*(s32 *)((p) + (o)))
#define H(p, o) (*(s16 *)((p) + (o)))
#define U(p, o) (*(u16 *)((p) + (o)))

/* Runs the moby's state machine on obj[0x95]; from state 3 on, except 5, it then eases the
   rotation at 0xF4 and 0xF0 towards a direction, each angle clamped to 40 degrees. */
/* Update handler for the Mutant Muckdweller moby. */
void muckdweller_update(u8 *obj)
{
    f32 delta[4] __attribute__((aligned(16)));
    f32 pos[4] __attribute__((aligned(16)));
    f32 matrix[16] __attribute__((aligned(16)));
    f32 inverse[16] __attribute__((aligned(16)));
    f32 oldInverse[16] __attribute__((aligned(16)));
    f32 height;
    u8 *state = *(u8 **)(obj + 0x68);
    f32 rate, speed, angle, pitch;
    s32 result;

    if (obj[0x95])
        muckdweller_update_targeting(obj);
    switch (obj[0x95]) {
    case 0:
        muckdweller_init(obj);
        break;
    case 1:
        if (state[0x3D0]) {
            U(obj, 0x34) |= 1;
            I(obj, 0x98) = 0;
            obj[0x31] = 0;
        }
        if (I(state, 0x2F4) == 1 && FastDecTimer(state + 0x3D4)) {
            if (state[0x3D0]) {
                muckdweller_find_farthest_anchor(obj, pos);
                FastVecSub(delta, pos, obj + 0x10);
                rate = 0.033333335071802139282f;
                if (FastVecLength(delta) * rate < 0.13333334028720855713f)
                    speed = FastVecLength(delta) * rate;
                else
                    speed = 0.13333334028720855713f;
                vec_scale_to_length(delta, delta, speed);
                height = 0;
                delta[2] = weapon_compute_shot_launch_speed(obj + 0x10, pos, &height, speed, -0.005f);
                qcopy(state + 0x190, delta);
                qcopy(state + 0x390, pos);
                if (obj[0x43] != 12)
                    anim_start_blended(obj, 12, 0, 2);
                if (height > 0)
                    F(obj, 0x48) = 51.0f / height;
                I(obj, 0x98) = I(*(u8 **)(obj + 0x24), 0x10);
                obj[0x31] = 1;
                U(obj, 0x34) &= 0xfffe;
                moby_set_state(obj, 0, 2);
            } else {
                if (I(state, 0x41C) != -1)
                    I(state, 0x3F8) = I(state, 0x41C);
                if (obj[0x43] != 7)
                    anim_start_blended(obj, 7, 0, math_random_int_range(7, 12));
                moby_set_state(obj, 3, 3);
            }
        }
        break;
    case 2: {
        f32 distance;

        FastVecAdd(obj + 0x10, obj + 0x10, state + 0x190);
        MobySpringTurn(obj, mat_fast_helper_a(F(state, 0x2E0) - F(obj, 0x10), F(state, 0x2E4) - F(obj, 0x14)),
                      F(state, 0x1D4), F(state, 0x1E4), F(state, 0x1DC) * 2, state + 0x274);
        F(state, 0x198) -= 0.005f;
        if (F(state, 0x198) <= 0 && math_fabs(F(obj, 0x18) - F(state, 0x398)) < -F(state, 0x198)) {
            F(obj, 0x48) = 1;
            F(obj, 0x18) = F(state, 0x398);
            F(state, 0x198) = 0;
            distance = vec_distance_xy(obj + 0x10, state + 0x390);
            if (distance < FastVecLength(state + 0x190)) {
                qcopy(obj + 0x10, state + 0x390);
                qzero(state + 0x190);
            }
            if (obj[0x60] & 2) {
                qcopy(state + 0x2B0, obj + 0x10);
                if (obj[0x43] != 6)
                    anim_start_blended(obj, 6, 0, 10);
                F(obj, 0x48) = 1;
                F(state, 0x3DC) = math_random_signed_float_range(20, 45) * 0.01745329424738884f;
                if (I(state, 0x41C) != -1)
                    I(state, 0x3F8) = I(state, 0x41C);
                if (state[0x3D3])
                    moby_set_state(obj, 2, 3);
                else {
                    if (I(state, 0x3C0) != -1)
                        I(state, 0x1FC) = I(state, 0x3C0);
                    moby_set_state(obj, 3, 3);
                }
            }
        }
        break;
    }
    case 3:
        switch (obj[0x20]) {
        case 1:
            if ((obj[0x60] & 2) && !H(state, 0x3D8)) {
                H(state, 0x3D8) = math_random_int_range(180, 440);
                if (obj[0x43] != 6)
                    anim_start_blended(obj, 6, 7, math_random_int_range(7, 12));
                moby_set_state(obj, 2, -1);
            }
            break;
        case 2:
            moby_move_keeping_transform_alt(obj, state + 0x2B0);
            if (!obj[0x40]) {
                if ((I(state, 0x2F4) == 1 || H(state, 0x3D6)) &&
                    (I(state, 0x408) != -1 || (**(s32 **)(state + 0x400) == H(obj, 0xB2) && !I(state, 0x404)))) {
                    if (I(state, 0x3C0) != -1)
                        I(state, 0x1FC) = I(state, 0x3C0);
                    H(state, 0x3D6) = 360;
                    if (I(state, 0x408) != -1) {
                        if (obj[0x43] != 7)
                            anim_start_blended(obj, 7, 0, math_random_int_range(7, 12));
                        moby_set_state(obj, 3, -1);
                    } else {
                        if (obj[0x43] != (func_001163B0() & 1) + 2)
                            anim_start_blended(obj, (func_001163B0() & 1) + 2, 0, math_random_int_range(7, 12));
                        moby_set_state(obj, 5, -1);
                    }
                } else {
                    Timer16 timer = *(Timer16 *)(state + 0x3D8);

                    if (H(state, 0x3D8))
                        break;
                    if (!H(state, 0x3D6) && I(state, 0x408) == -1) {
                        H(state, 0x3D8) = 120;
                        if (obj[0x43] != (func_001163B0() & 1))
                            anim_start_blended(obj, func_001163B0() & 1, 0, 12);
                        moby_set_state(obj, 1, 3);
                    } else if (!timer.value && I(state, 0x408) == -1) {
                        if (obj[0x43] != (func_001163B0() & 1) + 4)
                            anim_start_blended(obj, (func_001163B0() & 1) | 4, 0, 12);
                        moby_set_state(obj, 1, 3);
                    }
                }
            }
            break;
        case 3: {
            f32 distance;

            moby_move_keeping_transform(obj, state + 0x390);
            distance = vec_distance_xy(obj + 0x10, state + 0x390);
            if (obj[0x60] & 2) {
                if ((H(*(u8 **)(state + 0x2F0), 0xAA) != 0xB1A && distance <= 3) ||
                    (H(*(u8 **)(state + 0x2F0), 0xAA) == 0xB1A && distance < 1)) {
                    I(state, 0x404) = 180;
                    F(state, 0x3F4) = 0.3f;
                    I(state, 0x3F0) = 0;
                    if (obj[0x43] != 8)
                        anim_start_blended(obj, 8, 0, math_random_int_range(4, 7));
                    moby_set_state(obj, 0, 4);
                }
                if (I(state, 0x2F4) != 1 && !H(state, 0x3D6) && I(state, 0x408) == -1 && !math_random_int_below(39)) {
                    if (!math_random_int_below(3)) {
                        I(state, 0x404) = 180;
                        F(state, 0x3F4) = 0.3f;
                        I(state, 0x3F0) = 0;
                        if (obj[0x43] != 8)
                            anim_start_blended(obj, 8, 0, math_random_int_range(4, 7));
                        moby_set_state(obj, 0, 4);
                    } else {
                        if (obj[0x43] != 6)
                            anim_start_blended(obj, 6, 0, math_random_int_range(12, 18));
                        moby_set_state(obj, 4, 3);
                    }
                }
            }
            break;
        }
        case 4:
            moby_move_keeping_transform_alt(obj, state + 0x2B0);
            if (obj[0x60] & 2) {
                if (!I(state, 0x404) || vec_distance_xy(obj + 0x10, g_hero_state + 0x80) > 7) {
                    H(state, 0x3D8) = 60;
                    if (obj[0x43] != (func_001163B0() & 1) + 4)
                        anim_start_blended(obj, (func_001163B0() & 1) | 4, 0, 12);
                    moby_set_state(obj, 1, 3);
                }
            }
            break;
        case 5:
            MobySpringTurn(obj, mat_fast_helper_a(F(state, 0x2E0) - F(obj, 0x10), F(state, 0x2E4) - F(obj, 0x14)),
                          F(state, 0x1D4) * 2, F(state, 0x1E4), F(state, 0x1DC) * 2, state + 0x274);
            if (obj[0x60] & 2) {
                if (obj[0x43] != 7)
                    anim_start_blended(obj, 7, 0, math_random_int_range(7, 12));
                moby_set_state(obj, 3, -1);
            }
            break;
        }
        break;
    case 4: {
        f32 distance;
        u8 *target;

        distance = moby_get_anim_value(obj);
        target = *(u8 **)(state + 0x2F0);
        math_approach_target_with_direction_mode(obj + 0xF8, mat_fast_helper_a(F(target, 0x10) - F(obj, 0x10), F(target, 0x14) - F(obj, 0x14)),
                      F(state, 0x1D4), F(state, 0x1D8), F(state, 0x1DC), state + 0x274, 0);
        if (obj[0x42] == 8 && distance >= 18 && distance <= 23) {
            F(obj, 0x48) = 0.4f;
            coll_test_hit_at_bone(obj, 0, 0x4000001, 0, 1, 0, 0.2f, (f32)state[0x34], 1);
            muckdweller_fire_spit_shot(obj, 0);
        } else {
            F(obj, 0x48) = 1;
            muckdweller_fire_spit_shot(obj, 1);
        }
        if (obj[0x42] == 8 && distance >= 25) {
            F(state, 0x380) = math_fast_sin_or_cos_a(F(obj, 0xF8)) * 3.25f;
            F(state, 0x384) = math_fast_sin_or_cos_b(F(obj, 0xF8)) * 3.25f;
            I(state, 0x388) = 0;
            FastVecAdd(state + 0x380, state + 0x380, obj + 0x10);
            F(state, 0x388) = coll_probe_ground_height_below(state + 0x380, 0, 0.5f) + 0.025f;
            part_spawn_puffs_around_point(obj, 1);
        }
        if (obj[0x60] & 2) {
            if (obj[0x43] != 6)
                anim_start_blended(obj, 6, 0, math_random_int_range(12, 18));
            moby_set_state(obj, 4, 3);
        }
        break;
    }
    case 5:
        result = moby_dispatch_action_by_kind(obj, state + 0x110);
        if (result & 1)
            moby_set_state(obj, 0, 6);
        else if (result & 2) {
            I(state, 0x410) = -1;
            part_spawn_moving_bubbles(obj);
            if (I(state, 0x3C0) != -1)
                I(state, 0x1FC) = I(state, 0x3C0);
            if (I(state, 0x41C) != -1)
                I(state, 0x3F8) = I(state, 0x41C);
            H(state, 0x3D6) = 600;
            H(state, 0x3D8) = 30;
            if (obj[0x43] != (func_001163B0() & 1) + 4)
                anim_start_blended(obj, (func_001163B0() & 1) | 4, 0, 12);
            moby_set_state(obj, 1, 3);
        }
        break;
    case 6:
        SetDeathBits(obj, 0, 3);
        part_spawn_moving_bubbles(obj);
        part_spawn_puffs_around_point(obj, 1);
        part_queue_moby_for_glow(obj, 0, 0);
        break;
    }
    if (obj[0x95] != 5 && obj[0x95] >= 3) {
        *(UpdateQuad *)pos = 0;
        pos[2] = F(obj, 0xF8);
        *(UpdateQuad *)delta = *(UpdateQuad *)pos;
        euler_to_matrix(matrix, delta);
        matrix_from_basis_rows(inverse, matrix);
        matrix_from_basis_rows(oldInverse, obj + 0xC0);
        {
            f32 *v;
            u8 *target = *(u8 **)(state + 0x248);

            if (target && !level_has_pending_inner_flag(target)) {
                v = pos;
                qcopy(v, g_monster_vector_template);
            } else
                vec_scale_to_length(pos, state + 0x210, 1);
            v = pos;
            matrix_mul_vec3(v, v, inverse);
        }
        angle = mat_fast_helper_a(pos[2], pos[0]);
        pitch = -mat_fast_helper_a(pos[2], pos[1]);
        if (angle > 0.69813179969787597656f)
            angle = 0.69813179969787597656f;
        else if (angle < -0.69813179969787597656f)
            angle = -0.69813179969787597656f;
        if (pitch > 0.69813179969787597656f)
            pitch = 0.69813179969787597656f;
        else if (pitch < -0.69813179969787597656f)
            pitch = -0.69813179969787597656f;
        math_approach_target_with_direction_mode(obj + 0xF4, angle, 0.0017453294713050127f, 0.0017453294713050127f,
                      0.10471977293491363525f, state + 0x3EC, 0);
        math_approach_target_with_direction_mode(obj + 0xF0, pitch, 0.0017453294713050127f, 0.0017453294713050127f,
                      0.10471977293491363525f, state + 0x3E8, 0);
    }
    muckdweller_tick_timers(obj);
}
