#include "names.h"
/* func_L11_00451178: the Joba sentry's patrol, alert, attack and launch states; the twin of
 * func_L02_0040A4A8 (L02_0040A4A8-gu.c). Own unit for -frac2-gcse-unsplit-edges.
 * - work[6] is one function-scope scratch array: retail reuses sp+0x10..0x5F across the head
 *   and cases 7, 9 and 12.
 * - Case 7 passes the particle template through tmpl, set just before the template is filled.
 *   Its short life wins it a saved register in global-alloc, which reload then takes back, so
 *   its slot (0xCC) is assigned with case 12's reaching registers (state+0x2B0, object+0xC0,
 *   object+0xF0), in pseudo order after &work[1] and &work[4] (0xC4, 0xC8). Through a register,
 *   the template also keeps the particle loop at 46 insns, so loop.c hoists all seven
 *   constants in its first pass (see the twin's header).
 * - Case 12 sets spin = state + 0x2B0 before its loop, as func_L11_0044AFC8 does: the address
 *   then enters gcse's expression table before object+0xF0, which orders the PRE copies.
 * - turn() is inlined; with it gcse sees retail's insn count (S 583), and the bucket order of
 *   the reaching registers gives retail's spill slots.
 * - Case 11 preserves func_002B1C20's unsigned 64-bit return. Its early exit keeps the
 *   low-bit test in control flow; the compound OR spelling adds a 32-bit normalization.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 quad; float f[4]; } ActorVector;
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;
extern u8 g_hero_state[];
typedef struct { u8 pad00[0x5C]; u8 *ids; } L11_Palette;
extern L11_Palette D_L11_00200440;
extern s32 D_L11_001A8FF4 __attribute__((sda));
extern float D_L11_001B1D04 __attribute__((sda));
extern float D_L11_001B1D08 __attribute__((sda));
extern s32 D_L11_001B1D0C __attribute__((sda));
extern u16 D_L11_001B1D10 __attribute__((sda));
extern float D_L11_001B1D14 __attribute__((sda));
extern float D_L11_001B1D18 __attribute__((sda));
extern float D_L11_001B1D1C __attribute__((sda));
extern float D_L11_001B1D20 __attribute__((sda));
extern float D_L11_001B1D24 __attribute__((sda));
extern u8 *D_L11_001C0D18[];
extern u8 *g_hero_moby __attribute__((nosda));
extern u8 *g_active_attacker_robot __attribute__((nosda));
extern char D_L11_001A8F20[] MACRO_ADDR;

extern void turret_enemy_update_b(u8 *);
extern void moby_set_state(u8 *, s32, s32);
extern s32 math_random_int_below(s32);
extern void anim_start_blended(u8 *, s32, s32, s32);
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
extern void moby_aim_at_target_offset(u8 *, void *);
extern int moby_l01_turn_toward_target(u8 *, void *);
extern s32 arena_is_point_in_polygon(u8 *, u8 *);
extern void moby_step_at_own_position_factor(u8 *, float);
extern s32 FastDecTimer(void *);
extern s32 CollLine(void *, void *, s32, void *, void *);
extern s32 enemy_aim_at_group_entity_in_cone_c(u8 *);
extern s32 moby_turn_toward_target_and_step(u8 *, float *, float);
extern int coll_update_controller(u8 *, void *, void *);
extern s32 moby_step_controller(u8 *, void *, float);
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
extern void *part_spawn_burst(void *, void *, s32, s32, u32, s32, float, float, float, float, float);
extern s32 math_random_int_range(s32, s32);
extern int coll_check_move_to_point(u8 *, void *);
extern float moby_get_anim_value(u8 *);
extern s32 math_is_value_within_step(u8 *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void *part_spawn_spinning_effect_moby(float, u8 *, void *, void *, s32, s32);
extern unsigned long moby_dispatch_action_by_kind(u8 *, void *);
extern void moby_set_anim_type_three(u8 *, s32, s32);
extern void flamethrower_robot_deactivate(u8 *);
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
    moby_set_controller_speed_limits(object, rate, speed, 0.0005817765f, 0.052359886f);
}

/* Update the Joba sentry's patrol, alert, attack and launch states. */
void flamethrower_l11_robot_update(u8 *object)
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
    if (object[0x20] == 1 || (*(s16 *)(state + 0x2D8) && !D_L11_001A8FF4 && object[0x20] != 12 && object[0x20] != 11))
        return;
    turret_enemy_update_b(object);
    if (object[0x20] == 1 || (*(s16 *)(state + 0x2D8) && !D_L11_001A8FF4))
        return;
    if (*(s16 *)(state + 0x2D2) == 0 && object[0x95] == 3) {
        moby_set_state(object, 4, 2);
        if (math_random_int_below(2)) {
            if (object[0x43] != 2)
                anim_start_blended(object, 2, 0, 10);
        } else if (object[0x43] != 3)
            anim_start_blended(object, 3, 0, 10);
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
                anim_start_blended(object, 9, 0, 10);
            object[0xBC] = 0;
            turn(object, 0.0044444446f, 0.13333334f);
            flamethrower_robot_pick_wander_point(object, arena_get_center_point(*(u8 **)(object + 0xB8)));
            *(u16 *)(object + 0x96) = 10000;
        }
        if (object[0xBC] == 1 && *(u16 *)(object + 0x96) >= 301) {
            switch (math_random_int_below(5)) {
            case 0: if (object[0x43] != 2) anim_start_blended(object, 2, 0, 10); break;
            case 1: if (object[0x43] != 3) anim_start_blended(object, 3, 0, 10); break;
            case 2: if (object[0x43] != 5) anim_start_blended(object, 5, 0, 10); break;
            case 3: if (object[0x43] != 6) anim_start_blended(object, 6, 0, 10); break;
            }
            *(u16 *)(object + 0x96) = math_random_int_below(100);
        }
        if (*(s16 *)(state + 0x2D2)) {
            moby_set_state(object, 5, 3);
            if (math_random_int_below(2)) {
                if (object[0x43] != 1) anim_start_blended(object, 1, 0, 10);
            } else if (object[0x43] != 4) anim_start_blended(object, 4, 0, 10);
        }
        if (angle > 2.7925272f)
            flamethrower_robot_start_turn_around(object);
        goal = state + 0x2A0;
        if (!object[0xBC] && vec_distance_xy(pos, goal) < 0.5f)
            object[0xBC] = 1;
        else if (*(s16 *)(state + 0x2D8))
            moby_aim_at_target_offset(object, goal);
        else
            moby_l01_turn_toward_target(object, goal);
    }
    switch (object[0x20]) {
    case 3:
        if (flag_set_first_pending(object)) {
            object[0xBC] = 0;
            if (object[0x43] != 2) anim_start_blended(object, 2, 0, 0);
            *(u16 *)(object + 0x96) = 0;
        }
        if (object[0xBC] == 0 && *(s16 *)(state + 0x2D4) < (s32)*(u16 *)(object + 0x96)) {
            if (object[0x43] != 9) anim_start_blended(object, 9, 0, 10);
            object[0xBC] = 1;
        } else if (object[0xBC] == 1) {
            if (arena_is_point_in_polygon(*(u8 **)(object + 0xB8), pos))
                moby_set_state(object, 4, 2);
            moby_l01_turn_toward_target(object, arena_get_center_point(*(u8 **)(object + 0xB8)));
        }
        break;
    case 5:
        if (object[0x60] & 2)
            moby_set_state(object, 7, -1);
        break;
    case 6:
        if (flag_set_first_pending(object)) {
            if (object[0x43] != 8) anim_start_blended(object, 8, 0, 10);
            moby_set_controller_speed_limits(object, 0.0044444446f, 0.13333334f, 0.003490659f, 0.4188791f);
        }
        moby_step_at_own_position_factor(object, heading);
        if (object[0x60] & 2)
            moby_set_state(object, 7, -1);
        break;
    case 7:
        if (flag_set_first_pending(object)) {
            if (object[0x43] != 9) anim_start_blended(object, 9, 0, 15);
            *(u16 *)(state + 0x2D6) = 0;
        }
        if (D_L11_001B1D24 < range)
            turn(object, 0.0044444446f, 0.13333334f);
        else if (range < D_L11_001B1D20)
            turn(object, 0.0011111111f, 0.033333335f);
        if (object[0x42] != 12 && range < D_L11_001B1D18 && angle < 1.5707965f) {
            if (object[0x43] != 12) anim_start_blended(object, 12, 0, 10);
        } else if (object[0x42] == 12 && D_L11_001B1D1C < range) {
            if (object[0x43] != 9) anim_start_blended(object, 9, 0, 15);
        } else if (object[0x42] != 12 && D_L11_001B1D04 < range && range < D_L11_001B1D08 && !math_random_int_below(D_L11_001B1D0C)) {
            if (FastDecTimer(state + 0x2D6) && object[0x31]) {
                u8 *other;
                s16 id;
                if (!CollLine(pos, &target, 1, object, 0) ||
                    ((other = D_L11_001C0D18[0]) != 0 && (id = *(s16 *)(other + 0xAA)) != 0xD98 /* moby class 3480 */ && id != 0xDCF /* moby class 3535 */ &&
                     id != 0xDF4 /* moby class 3572 */ && id != 0xDF7 /* moby class 3575 */ && id != 0xDF9 /* moby class 3577 */ && id != 0xD37 /* moby class 3383 */)) {
                    moby_set_state(object, 9, -1);
                    *(u16 *)(state + 0x2D6) = D_L11_001B1D10;
                }
            }
        } else if (range > 2.8f) {
            if (*(s16 *)(state + 0x2D8))
                moby_aim_at_target_offset(object, &target);
            else if (!enemy_aim_at_group_entity_in_cone_c(object))
                moby_turn_toward_target_and_step(object, target.f, *(float *)(state + 0x2C8));
        } else if (*(s16 *)(state + 0x2D8)) {
            FastVecSub(&work[0], &target, pos);
            coll_update_controller(object, pos, &work[0]);
        } else
            moby_step_controller(object, pos, heading);
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
                vec_scale_to_length(&velocity, work + 3, 0.25f);
                vec_scale_to_length(work + 1, work + 1, 3.0f);
                FastVecAdd(&near_point, &near_point, &effect);
                FastVecAdd(&far_point, &far_point, &effect);
                near_point.f[2] -= 0.1f;
                far_point.f[2] -= 0.1f;
                i = 2;
                do {
                    float first;
                    float second;
                    float third;
                    vec_add_random_offset(effect.f, 0.1f);
                    first = math_random_float_range(0.2f, 0.4f) * 210000.0f;
                    second = math_random_float_range(1.0f, 1.5f) * 210000.0f;
                    third = math_random_signed_float_range(0.0f, 0.01f);
                    part_spawn_gravity_fade(&effect, &velocity, 9, 0x808080, 30, 127, 32, first, second, third, 0);
                    if (range < 3.0f) {
                        coll_sweep_from_object(object, &effect, 0.3f, 0x4000001, (float)state[0x34], 1.0f, 0, 1, 0);
                        coll_sweep_from_object(object, &near_point, 0.3f, 0x4000001, (float)state[0x34], 1.0f, 0, 1, 0);
                        coll_sweep_from_object(object, &far_point, 0.3f, 0x4000001, (float)state[0x34], 1.0f, 0, 1, 0);
                    }
                } while (--i >= 0);
                tmpl = &particle;
                particle.f[0] = 0.0f;
                particle.f[1] = 0.0f;
                particle.f[2] = 0.1f;
                particle.f[3] = 1.0f;
                for (j = 0; j < 2; j++) {
                    u8 *part = part_spawn_burst(&near_point, tmpl, 15, 60, 0x606060, 3,
                        105000.0f, 21000.0f, 1.0f, -0.0002f, 0.0f);
                    if (part) {
                        part[2] = *D_L11_00200440.ids;
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
            if (object[0x43] != 7) anim_start_blended(object, 7, 0, 10);
        }
        if (!object[0xBC] && angle < D_L11_001B1D14 * 0.017453294f) {
            object[0xBC] = 1;
            if (object[0x43] != 17) anim_start_blended(object, 17, 0, 10);
        } else if (*(s16 *)(state + 0x2D8))
            coll_check_move_to_point(object, &target);
        else
            moby_step_at_own_position_factor(object, heading);
        if (object[0xBC] == 1) {
            float dist = moby_get_anim_value(object);
            if (math_is_value_within_step(object, 17.0f)) {
                work[2].quad = 0;
                work[2].f[2] = 1.0f;
                moby_transform_joint_to_world(object, 4, &work[0]);
                if (*(u8 **)(state + 0x2C4))
                    matrix_mul_vec3(&work[2], &work[2], *(u8 **)(state + 0x2C4) + 0xC0);
                else
                    matrix_mul_vec3(&work[2], &work[2], g_hero_moby + 0xC0);
                FastVecAdd(&work[2], &work[2], &target);
                FastVecSub(&work[1], &work[2], &work[0]);
                vec_scale_to_length(&work[1], &work[1], 0.33333334f);
                part_spawn_spinning_effect_moby((float)state[0x35], object, &work[1], &work[0], 0, 0);
            } else if (dist < 17.0f && object[0x43] == 17) {
                float first;
                float second;
                moby_transform_joint_to_world(object, 4, &work[0]);
                first = math_random_float_range(1.0f, 1.5f) * 210000.0f;
                second = math_random_float_range(0.2f, 0.4f) * 210000.0f;
                part_spawn_gravity_fade(&work[0], D_L11_001A8F20, 4, 0x808080, 9, 0x4F, 0, first, second, math_random_signed_float_range(0.0f, 0.1f), 0);
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
            anim_start_blended(object, 11, 0, 7);
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
                moby_set_anim_type_three(object, 0, -1);
                flamethrower_robot_deactivate(object);
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
            vec_scale_to_length(launch, launch, math_random_float_range(3.0f, 5.0f) * 0.016666668f);
            *(s16 *)(state + 0x2D8) = 0;
            spin = (float *)(state + 0x2B0);
            for (k = 0; k < 3; k++) {
                spin[k] = math_random_float_range(240.0f, 720.0f) * 0.00029088825f;
                qcopy(&work[k], &((ActorVector *)(object + 0xC0))[k]);
            }
            mat_get_euler_angles(work, object + 0xF0);
            if (object[0x43] != 18) anim_start_blended(object, 18, 0, 30);
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
            moby_set_anim_type_three(object, 0, -1);
            flamethrower_robot_deactivate(object);
        }
        break;
    }
    }
    flamethrower_robot_finish_frame(object);
    gfx_add_draw_callback_third(flamethrower_robot_add_lights, object);
}
