#include "names.h"
/* func_PAL_L11_00456D04, the PAL copy of func_L11_00451178: the Joba sentry's patrol, alert, attack
 * and launch states. The same C with 50 Hz values, where:
 * - Case 7's cooldown is rescaled in place and D_L11_001B1D10 is read as a word.
 * - Case 7's first particle loop counts up: dbra reversal sets i = 2 after the preheader's other
 *   insns, which orders the $f22 copy before it in sched2 and gives gcse retail's bucket count.
 * - Case 9 replaces the func_002AEB60 test with a one-shot flag at state + 0x2DA and dist > 17.0f.
 *   cse reuses the known object[0xBC] == 1 for the flag's store.
 * - -frac2-hazard-labels: that test's false branch lands on the nop after the 17.0f mtc1.
 * - Spill slots: tmpl 0xC4, then case 12's reaching registers state + 0x2B0, object + 0xC0,
 *   object + 0xF0, &work[1] and &work[4] from 0xC8 to 0xD8, in hash-bucket order.
 * - work[6] is one function-scope scratch array: retail reuses sp+0x10..0x5F across the head
 *   and cases 7, 9 and 12.
 * - Case 12 sets spin = state + 0x2B0 before its loop, as func_L11_0044AFC8 does: the address
 *   then enters gcse's expression table before object+0xF0, which orders the PRE copies.
 * - Case 11 preserves func_002B1C20's unsigned 64-bit return. Its early exit keeps the
 *   low-bit test in control flow; the compound OR spelling adds a 32-bit normalization.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 quad; float f[4]; } ActorVector;
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;
extern u8 g_hero_state[];
typedef struct { u8 pad00[0x5C]; u8 *ids; } L11_Palette;
extern L11_Palette g_flamethrower_palette;
extern s32 g_hero_l11_input_blocked __attribute__((sda));
extern float g_flamethrower_range_min __attribute__((sda));
extern float g_flamethrower_range_max __attribute__((sda));
extern s32 g_flamethrower_fire_chance __attribute__((sda));
extern s32 g_flamethrower_timer __attribute__((sda));
extern float g_flamethrower_cone_deg __attribute__((sda));
extern float g_flamethrower_attack_range __attribute__((sda));
extern float g_flamethrower_far_range __attribute__((sda));
extern float g_flamethrower_near_range __attribute__((sda));
extern float g_flamethrower_min_range __attribute__((sda));
extern u8 *g_hit_l11_result[];
extern u8 *g_hero_moby __attribute__((nosda));
extern u8 *g_active_attacker_robot __attribute__((nosda));
extern char g_identity_l11_matrix[] MACRO_ADDR;

extern void turret_enemy_update_b_pal(u8 *);
extern void moby_set_state(u8 *, s32, s32);
extern s32 math_random_int_below(s32);
extern void anim_start_blended_pal(u8 *, s32, s32, s32);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern void FastVecSub(void *, void *, void *);
extern float vec_get_heading_angle(u8 *, void *, u8 *);
extern float fast_vec_dist(void *, void *);
extern float vec_distance_xy(void *, void *);
extern s32 flag_set_second_pending(u8 *);
extern s32 flag_set_first_pending(u8 *);
extern void moby_set_controller_speed_limits(u8 *, float, float, float, float);
extern u8 *arena_get_center_point(u8 *);
extern void flamethrower_robot_pick_wander_point(u8 *, u8 *);
extern void flamethrower_robot_start_turn_around(u8 *);
extern void moby_aim_at_target_offset_pal(u8 *, void *);
extern int moby_l01_turn_toward_target_pal(u8 *, void *);
extern s32 arena_is_point_in_polygon(u8 *, u8 *);
extern int moby_step_at_own_position_factor_pal(u8 *, float);
extern s32 FastDecTimer(void *);
extern s32 CollLine(void *, void *, s32, void *, void *);
extern s32 enemy_aim_at_group_entity_in_cone_c_pal(u8 *);
extern s32 moby_turn_toward_target_and_step_pal(u8 *, float *, float);
extern int coll_update_controller_pal(u8 *, void *, void *);
extern s32 moby_step_controller_pal(u8 *, void *, float);
extern s32 math_fast_helper_a(void *, float);
extern void moby_transform_joint_point(u8 *, s32, void *);
extern void moby_transform_joint_to_world(u8 *, s32, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void vec_add_random_offset(float *, float);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern void *part_spawn_gravity_fade(void *, void *, s32, u32, s32, s32, s32, float, float, float, s32);
extern s32 coll_sweep_from_object(void *, void *, float, u32, float, float, s32, s32, s32);
extern void *part_spawn_burst_pal(void *, void *, s32, s32, u32, s32, float, float, float, float, float);
extern s32 math_random_int_range(s32, s32);
extern int coll_check_move_to_point_pal(u8 *, void *);
extern float moby_get_anim_value(u8 *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void *part_spawn_spinning_effect_moby_pal(float, u8 *, void *, void *, s32, s32);
extern unsigned long moby_dispatch_action_by_kind(u8 *, void *);
extern void moby_set_anim_type_three_pal(u8 *, s32, s32);
extern void flamethrower_robot_deactivate_pal(u8 *);
extern void mat_get_euler_angles(void *, void *);
extern int hero_set_control_motion_and_step(u8 *, void *);
extern void FastVecScale(void *, void *, float);
extern void get_moby_joint_matrices(u8 *, s32, s32 *, void *);
extern void moby_rotate_about_point(float, float, float, u8 *, void *);
extern void euler_rotation_basis(void *, void *);
extern void flamethrower_robot_finish_frame(u8 *);
extern void flamethrower_robot_add_lights(u8 *);
extern void gfx_add_draw_callback_third(void (*)(u8 *), void *);

/* Movement tuning with the sentry's usual turn limits. */
static __inline__ void turn(u8 *object, float rate, float speed)
{
    moby_set_controller_speed_limits(object, rate, speed, 0.0008377582f, 0.062831864f);
}

/* Update the Joba sentry's patrol, alert, attack and launch states. */
void flamethrower_l11_robot_update_pal(u8 *object)
{
    ActorVector target;
    ActorVector work[6];
    ActorVector effect;
    ActorVector near_point;
    ActorVector far_point;
    ActorVector velocity;
    ActorVector particle;
    s32 count;
    ActorVector *tmpl;
    u8 *state;
    u8 *pos;
    float heading;
    float angle;
    float range;

    state = *(u8 **)(object + 0x68);
    if (object[0x20] == 1 || (*(s16 *)(state + 0x2D8) && !g_hero_l11_input_blocked && object[0x20] != 12 && object[0x20] != 11))
        return;
    turret_enemy_update_b_pal(object);
    if (object[0x20] == 1 || (*(s16 *)(state + 0x2D8) && !g_hero_l11_input_blocked))
        return;
    if (*(s16 *)(state + 0x2D2) == 0 && object[0x95] == 3) {
        moby_set_state(object, 4, 2);
        if (math_random_int_below(2)) {
            if (object[0x43] != 2)
                anim_start_blended_pal(object, 2, 0, 8);
        } else if (object[0x43] != 3)
            anim_start_blended_pal(object, 3, 0, 8);
    }
    if (*(u8 **)(state + 0x2C4))
        target.quad = *(TI128 *)(*(u8 **)(state + 0x2C4) + 0x10);
    else
        target.quad = *(TI128 *)(g_hero_state + 0x80);
    if (*(s16 *)(state + 0x2D8)) {
        FastVecSub(&work[0], &target, object + 0x10);
        pos = object + 0x10;
        heading = 0.0f;
        angle = vec_get_heading_angle(object, &work[0], state + 0x230);
    } else {
        pos = object + 0x10;
        heading = mat_fast_helper_a(target.f[0] - *(float *)(object + 0x10), target.f[1] - *(float *)(object + 0x14));
        angle = FastDiffRots(heading, *(float *)(object + 0xF8));
    }
    range = fast_vec_dist(pos, &target);
    if (object[0x95] == 2) {
        u8 *goal;
        if (flag_set_second_pending(object)) {
            if (object[0x43] != 9)
                anim_start_blended_pal(object, 9, 0, 8);
            object[0xBC] = 0;
            turn(object, 0.0064000003f, 0.16000001f);
            flamethrower_robot_pick_wander_point(object, arena_get_center_point(*(u8 **)(object + 0xB8)));
            *(u16 *)(object + 0x96) = 10000;
        }
        if (object[0xBC] == 1 && *(u16 *)(object + 0x96) >= 251) {
            switch (math_random_int_below(5)) {
            case 0: if (object[0x43] != 2) anim_start_blended_pal(object, 2, 0, 8); break;
            case 1: if (object[0x43] != 3) anim_start_blended_pal(object, 3, 0, 8); break;
            case 2: if (object[0x43] != 5) anim_start_blended_pal(object, 5, 0, 8); break;
            case 3: if (object[0x43] != 6) anim_start_blended_pal(object, 6, 0, 8); break;
            }
            *(u16 *)(object + 0x96) = math_random_int_below(83);
        }
        if (*(s16 *)(state + 0x2D2)) {
            moby_set_state(object, 5, 3);
            if (math_random_int_below(2)) {
                if (object[0x43] != 1) anim_start_blended_pal(object, 1, 0, 8);
            } else if (object[0x43] != 4) anim_start_blended_pal(object, 4, 0, 8);
        }
        if (angle > 2.7925272f)
            flamethrower_robot_start_turn_around(object);
        goal = state + 0x2A0;
        if (!object[0xBC] && vec_distance_xy(pos, goal) < 0.5f)
            object[0xBC] = 1;
        else if (*(s16 *)(state + 0x2D8))
            moby_aim_at_target_offset_pal(object, goal);
        else
            moby_l01_turn_toward_target_pal(object, goal);
    }
    switch (object[0x20]) {
    case 3:
        if (flag_set_first_pending(object)) {
            object[0xBC] = 0;
            if (object[0x43] != 2) anim_start_blended_pal(object, 2, 0, 0);
            *(u16 *)(object + 0x96) = 0;
        }
        if (object[0xBC] == 0 && *(s16 *)(state + 0x2D4) < (s32)*(u16 *)(object + 0x96)) {
            if (object[0x43] != 9) anim_start_blended_pal(object, 9, 0, 8);
            object[0xBC] = 1;
        } else if (object[0xBC] == 1) {
            if (arena_is_point_in_polygon(*(u8 **)(object + 0xB8), pos))
                moby_set_state(object, 4, 2);
            moby_l01_turn_toward_target_pal(object, arena_get_center_point(*(u8 **)(object + 0xB8)));
        }
        break;
    case 5:
        if (object[0x60] & 2)
            moby_set_state(object, 7, -1);
        break;
    case 6:
        if (flag_set_first_pending(object)) {
            if (object[0x43] != 8) anim_start_blended_pal(object, 8, 0, 8);
            moby_set_controller_speed_limits(object, 0.0064000003f, 0.16000001f, 0.005026549f, 0.5026549f);
        }
        moby_step_at_own_position_factor_pal(object, heading);
        if (object[0x60] & 2)
            moby_set_state(object, 7, -1);
        break;
    case 7:
        if (flag_set_first_pending(object)) {
            if (object[0x43] != 9) anim_start_blended_pal(object, 9, 0, 12);
            *(u16 *)(state + 0x2D6) = 0;
        }
        if (g_flamethrower_min_range < range)
            turn(object, 0.0064000003f, 0.16000001f);
        else if (range < g_flamethrower_near_range)
            turn(object, 0.0016000001f, 0.040000003f);
        if (object[0x42] != 12 && range < g_flamethrower_attack_range && angle < 1.5707965f) {
            if (object[0x43] != 12) anim_start_blended_pal(object, 12, 0, 8);
        } else if (object[0x42] == 12 && g_flamethrower_far_range < range) {
            if (object[0x43] != 9) anim_start_blended_pal(object, 9, 0, 12);
        } else if (object[0x42] != 12 && g_flamethrower_range_min < range && range < g_flamethrower_range_max && !math_random_int_below(g_flamethrower_fire_chance)) {
            if (FastDecTimer(state + 0x2D6) && object[0x31]) {
                u8 *other;
                s16 id;
                if (!CollLine(pos, &target, 1, object, 0) ||
                    ((other = g_hit_l11_result[0]) != 0 && (id = *(s16 *)(other + 0xAA)) != 0xD98 && id != 0xDCF &&
                     id != 0xDF4 && id != 0xDF7 && id != 0xDF9 && id != 0xD37)) {
                    moby_set_state(object, 9, -1);
                    *(u16 *)(state + 0x2D6) = (g_flamethrower_timer * 5 + 2) / 6;
                }
            }
        } else if (range > 2.8f) {
            if (*(s16 *)(state + 0x2D8))
                moby_aim_at_target_offset_pal(object, &target);
            else if (!enemy_aim_at_group_entity_in_cone_c_pal(object))
                moby_turn_toward_target_and_step_pal(object, target.f, *(float *)(state + 0x2C8));
        } else if (*(s16 *)(state + 0x2D8)) {
            FastVecSub(&work[0], &target, pos);
            coll_update_controller_pal(object, pos, &work[0]);
        } else
            moby_step_controller_pal(object, pos, heading);
        if (angle > 2.7925272f)
            flamethrower_robot_start_turn_around(object);
        if (object[0x42] == 12) {
            work[1].quad = 0;
            work[1].f[0] = *(float *)(object + 0x10);
            work[1].f[1] = *(float *)(object + 0x14);
            work[1].f[2] = *(float *)(object + 0x18);
            work[1].f[3] = 2.0f;
            work[0].quad = work[1].quad;
            if (object[0x31] || math_fast_helper_a(work, 128.0f) > 0) {
                s32 i;
                s32 j;
                moby_transform_joint_point(object, 4, &work[2]);
                qcopy(&work[1], &work[3]);
                moby_transform_joint_to_world(object, 4, &effect);
                vec_scale_to_length(&near_point, work + 1, 0.85f);
                vec_scale_to_length(&far_point, work + 1, 1.6f);
                vec_scale_to_length(&velocity, work + 3, 0.3f);
                vec_scale_to_length(work + 1, work + 1, 3.0f);
                FastVecAdd(&near_point, &near_point, &effect);
                FastVecAdd(&far_point, &far_point, &effect);
                near_point.f[2] -= 0.1f;
                far_point.f[2] -= 0.1f;
                for (i = 0; i < 3; i++) {
                    float first;
                    float second;
                    float third;
                    vec_add_random_offset(effect.f, 0.1f);
                    first = math_random_float_range(0.2f, 0.4f) * 210000.0f;
                    second = math_random_float_range(1.0f, 1.5f) * 210000.0f;
                    third = math_random_signed_float_range(0.0f, 0.01f);
                    part_spawn_gravity_fade(&effect, &velocity, 7, 0x808080, 30, 127, 32, first, second, third, 0);
                    if (range < 3.0f) {
                        coll_sweep_from_object(object, &effect, 0.3f, 0x4000001, (float)state[0x34], 1.0f, 0, 1, 0);
                        coll_sweep_from_object(object, &near_point, 0.3f, 0x4000001, (float)state[0x34], 1.0f, 0, 1, 0);
                        coll_sweep_from_object(object, &far_point, 0.3f, 0x4000001, (float)state[0x34], 1.0f, 0, 1, 0);
                    }
                }
                tmpl = &particle;
                particle.f[0] = 0.0f;
                particle.f[1] = 0.0f;
                particle.f[2] = 0.1f;
                particle.f[3] = 1.0f;
                for (j = 0; j < 2; j++) {
                    u8 *part = part_spawn_burst_pal(&near_point, tmpl, 12, 60, 0x606060, 3,
                        105000.0f, 21000.0f, 1.0f, -0.0002f, 0.0f);
                    if (part) {
                        part[2] = *g_flamethrower_palette.ids;
                        part[3] = 0x44;
                        if (math_random_int_range(0, 1)) {
                            u8 *tail;
                            u16 alpha;
                            part[3] = 0x48;
                            alpha = 127;
                            *(u32 *)(part + 4) = 0x70707F;
                            tail = part + 0x20;
                            tail[0x11] = 0x70;
                            tail[0x12] = 0x70;
                            tail[0x13] = 0x70;
                            *(u16 *)(tail + 0x1E) = alpha;
                        }
                    }
                }
            }
        }
        break;
    case 9:
        if (flag_set_first_pending(object)) {
            object[0xBC] = 0;
            if (object[0x43] != 7) anim_start_blended_pal(object, 7, 0, 8);
            *(s16 *)(state + 0x2DA) = 0;
        }
        if (!object[0xBC] && angle < g_flamethrower_cone_deg * 0.017453294f) {
            object[0xBC] = 1;
            if (object[0x43] != 17) anim_start_blended_pal(object, 17, 0, 8);
        } else if (*(s16 *)(state + 0x2D8))
            coll_check_move_to_point_pal(object, &target);
        else
            moby_step_at_own_position_factor_pal(object, heading);
        if (object[0xBC] == 1) {
            float dist = moby_get_anim_value(object);
            if (*(s16 *)(state + 0x2DA) == 0 && 17.0f < dist) {
                *(s16 *)(state + 0x2DA) = 1;
                work[2].quad = 0;
                work[2].f[2] = 1.0f;
                moby_transform_joint_to_world(object, 4, &work[0]);
                if (*(u8 **)(state + 0x2C4))
                    matrix_mul_vec3(&work[2], &work[2], *(u8 **)(state + 0x2C4) + 0xC0);
                else
                    matrix_mul_vec3(&work[2], &work[2], g_hero_moby + 0xC0);
                FastVecAdd(&work[2], &work[2], &target);
                FastVecSub(&work[1], &work[2], &work[0]);
                vec_scale_to_length(&work[1], &work[1], 0.40000004f);
                part_spawn_spinning_effect_moby_pal((float)state[0x35], object, &work[1], &work[0], 0, 0);
            } else if (dist < 17.0f && object[0x43] == 17) {
                float first;
                float second;
                moby_transform_joint_to_world(object, 4, &work[0]);
                first = math_random_float_range(1.0f, 1.5f) * 210000.0f;
                second = math_random_float_range(0.2f, 0.4f) * 210000.0f;
                part_spawn_gravity_fade(&work[0], g_identity_l11_matrix, 3, 0x808080, 9, 0x4F, 0, first, second, math_random_signed_float_range(0.0f, 0.1f), 0);
            }
            if (object[0x60] & 2) {
                if (g_active_attacker_robot == object || !math_random_int_below(6))
                    moby_set_state(object, 10, -1);
                else
                    moby_set_state(object, 7, -1);
            }
        }
        break;
    case 10:
        if (flag_set_first_pending(object) && object[0x43] != 11)
            anim_start_blended_pal(object, 11, 0, 6);
        if (object[0x60] & 2)
            moby_set_state(object, 7, -1);
        break;
    case 11: {
        unsigned long flags = moby_dispatch_action_by_kind(object, state + 0x50);
        if (object[0x42] == 15) {
            if (math_random_int_below(30) && (flags & 1UL) == 0)
                break;
            if (moby_get_anim_value(object) < 15.0f && *(s16 *)(state + 0x2D8) && !math_random_int_below(2))
                moby_set_state(object, 12, -1);
            else {
                moby_set_anim_type_three_pal(object, 0, -1);
                flamethrower_robot_deactivate_pal(object);
            }
        } else if ((flags & 2UL) != 0)
            moby_set_state(object, 7, 3);
        break;
    }
    case 12: {
        u8 *launch = state + 0x1A0;
        s32 started = flag_set_first_pending(object);
        if (started) {
            s32 k;
            float *spin;
            FastVecSub(launch, arena_get_center_point(*(u8 **)(object + 0xB8)), pos);
            *(float *)(state + 0x1A8) = 0.0f;
            vec_scale_to_length(launch, launch, math_random_float_range(3.0f, 5.0f) * 0.020000001f);
            *(s16 *)(state + 0x2D8) = 0;
            spin = (float *)(state + 0x2B0);
            for (k = 0; k < 3; k++) {
                spin[k] = math_random_float_range(240.0f, 720.0f) * 0.0003490659f;
                qcopy(&work[k], &((ActorVector *)(object + 0xC0))[k]);
            }
            mat_get_euler_angles(work, object + 0xF0);
            if (object[0x43] != 18) anim_start_blended_pal(object, 18, 0, 25);
            *(u16 *)(object + 0x34) &= 0xEFFF;
        }
        *(float *)(state + 0x1A8) -= *(float *)(state + 0x12C);
        hero_set_control_motion_and_step(object, launch);
        FastVecScale(state + 0x2B0, state + 0x2B0, 0.98f);
        {
            float f = *(float *)(object + 0x2C) * 0.0009765625f;
            count = 3;
            get_moby_joint_matrices(object, 1, &count, &work[1]);
            FastVecScale(&work[0], &work[4], f);
        }
        moby_rotate_about_point(*(float *)(state + 0x2B0), *(float *)(state + 0x2B4), *(float *)(state + 0x2B8), object, work);
        euler_rotation_basis(object + 0xC0, object + 0xF0);
        if (*(float *)(object + 0x18) < ((float *)arena_get_center_point(*(u8 **)(object + 0xB8)))[2] + 5.0f ||
            !math_random_int_below(450) || *(u16 *)(object + 0x96) >= 301) {
            moby_set_anim_type_three_pal(object, 0, -1);
            flamethrower_robot_deactivate_pal(object);
        }
        break;
    }
    }
    flamethrower_robot_finish_frame(object);
    gfx_add_draw_callback_third(flamethrower_robot_add_lights, object);
}
