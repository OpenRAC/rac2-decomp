#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 quad; float f[4]; u32 word[4]; } PatrolVector;
typedef struct {
    char pad0[0x80];
    PatrolVector pos;
    char pad1[0x249C - 0x90];
    u8 *contact;
} HeroBlock;
extern HeroBlock g_hero_state;
extern u8 *g_route_polygons[];
extern float g_blade_ball_turn_rate_x __attribute__((sda));
extern float g_blade_ball_turn_rate_y[] __attribute__((sda));
extern float g_blade_ball_turn_rate_z[] __attribute__((sda));
extern float g_blade_ball_size_min __attribute__((sda));
extern float g_blade_ball_size_max __attribute__((sda));
extern float g_blade_ball_spread_min __attribute__((sda));
extern float g_blade_ball_spread_max __attribute__((sda));
extern float g_blade_ball_up_speed_min __attribute__((sda));
extern float g_blade_ball_up_speed_max __attribute__((sda));
extern float g_blade_ball_ground_effect_param __attribute__((sda));
extern void blade_ball_update_common(u8 *);
extern float mat_fast_helper_a(float, float);
extern float vec_distance_xy(void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern s32 CollLine(void *, void *, s32, void *, s32);
extern s32 coll_test_point(void *, s32, void *, float);
extern s32 math_random_int_below(s32);
extern s32 coll_sweep_from_object(void *, void *, u32, float, float, float, s32, s32, s32);
extern void moby_set_state(u8 *, u8, s32);
extern void anim_start_blended(void *, s32, s32, s32);
extern void moby_set_anim_type_three(void *, s32, s32);
extern void blade_ball_explode(u8 *);
extern char *arena_get_camera_point(char *);
extern s32 flag_set_first_pending(u8 *);
extern s32 flag_set_second_pending(u8 *);
extern void moby_set_controller_speed_limits(u8 *, float, float, float, float);
extern s32 arena_get_state_word(char *);
extern s32 coll_point_inside_record_volume(void *, s32);
extern int moby_l01_turn_toward_target(char *, char *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void func_002A677C(void *);
extern s32 moby_turn_toward_target_and_step(char *, float *, float);
extern float math_step_value_toward_target(float *, float *, float, float, float, float);
extern float math_random_float_range(float, float);
extern float math_fabs(float);
/* The second GPR is a bone index, consumed by func_0029FCC0. */
extern s32 coll_test_hit_at_bone(float, float, float, void *, s32, s32, s32, s32, s32);
extern float math_move_angle_toward_target(float, float, float);
extern float FastAddRotations(float, float);
extern void vec_random_direction(float *, float, float);
extern void *part_spawn_ground_effect(float, float, float, void *, s32, u32, s32, s32, float *, s32);
extern void blade_ball_update_hit_reaction(u8 *);

/* Follow the patrol path, handle landing and contact states, then emit the trail. */
/* Update handler of the PX6 BladeBall (moby class 3134). */
void blade_ball_update(u8 *object)
{
    PatrolVector target;
    PatrolVector point;
    PatrolVector velocity;
    u8 *state;
    u8 *ground;
    float range;
    float height;
    s32 i;

    if (object[0x20] == 1 || object == 0 || object[0x20] == 0xFE || object[0x20] == 0xFD)
        return;
    state = *(u8 **)(object + 0x68);
    blade_ball_update_common(object);
    if (*(u8 **)(state + 0x184)) {
        target.quad = *(TI128 *)(*(u8 **)(state + 0x184) + 0x10);
        mat_fast_helper_a(*(float *)(*(u8 **)(state + 0x184) + 0x10) - *(float *)(object + 0x10), *(float *)(*(u8 **)(state + 0x184) + 0x14) - *(float *)(object + 0x14));
    } else {
        target.quad = *(TI128 *)&g_hero_state.pos;
        mat_fast_helper_a(g_hero_state.pos.f[0] - *(float *)(object + 0x10), g_hero_state.pos.f[1] - *(float *)(object + 0x14));
    }
    range = vec_distance_xy(object + 0x10, &target);
    if (object[0x20] == 1 || object == 0 || object[0x20] == 0xFE || object[0x20] == 0xFD)
        return;
    if (object[0x95] == 4) {
        qcopy(&point, object + 0x10);
        *(float *)(state + 0x108) -= *(float *)(state + 0x8C);
        FastVecAdd(object + 0x10, object + 0x10, state + 0x100);
        if (CollLine(&point, object + 0x10, 0, object, 0) ||
            coll_test_point(object + 0x10, 4, object, 0.3f) || math_random_int_below(30) == 0) {
            coll_sweep_from_object(object, object + 0x10, 0x10000, 0.5f, (float)(state[0x34] * 3), 1.0f, 0, 1, 0);
            if (*(float *)(state + 0x20) > 0.0f) {
                moby_set_state(object, 8, 3);
                if (object[0x43]) anim_start_blended(object, 0, 0, 5);
            } else {
                moby_set_anim_type_three(object, 0, 1);
                blade_ball_explode(object);
            }
        }
    }
    ground = 0;
    if (*(char **)(object + 0xB8))
        ground = (u8 *)arena_get_camera_point(*(char **)(object + 0xB8));
    switch (object[0x20]) {
    case 3:
        if (flag_set_first_pending(object)) {
            moby_set_controller_speed_limits(object, 0.016666668f, 0.33333334f, 0.001163553f, 0.10471977f);
            object[0xBC] = 0;
        }
        if (!object[0xBC] && (s32)*(u16 *)(object + 0x96) > *(s16 *)(state + 0x1BA))
            object[0xBC] = 1;
        else if (object[0xBC] == 1) {
            if (coll_point_inside_record_volume(object + 0x10, arena_get_state_word(*(char **)(object + 0xB8))))
                moby_set_state(object, 7, 3);
            moby_l01_turn_toward_target((char *)object, arena_get_camera_point(*(char **)(object + 0xB8)));
        }
        break;
    case 4:
        if (*(u16 *)(object + 0x96) > 25) {
            if (object[0x43]) anim_start_blended(object, 0, 0, 5);
            moby_set_state(object, 8, 3);
        }
        break;
    case 7:
        {
            u8 *path = g_route_polygons[*(s32 *)(state + 0x180)];
            if (flag_set_first_pending(object)) {
                u8 *cursor = path + 0x10;
                s32 closest = 0;
                s32 index;
                float best;
                moby_set_controller_speed_limits(object, 0.027777778f, 3.3333335f, 0.001163553f, 0.10471977f);
                *(float *)(state + 0x188) = *(float *)(ground + 8) + math_random_float_range(1.0f, 3.0f);
                best = vec_distance_xy(object + 0x10, cursor);
                for (index = 0; index < *(s32 *)path - 1; index++) {
                    float next = vec_distance_xy(object + 0x10, cursor);
                    if (next < best) { best = next; closest = index; }
                    cursor += 0x10;
                }
                *(s32 *)(state + 0x194) = closest;
                *(u16 *)(state + 0x1B4) = math_random_int_below(2);
            } else {
                qcopy(&point, &((PatrolVector *)(path + 0x10))[*(s32 *)(state + 0x194)]);
                point.f[2] = *(float *)(state + 0x188);
                FastVecSub(&velocity, &point, object + 0x10);
                vec_scale_to_length(&velocity, &velocity, *(float *)(state + 0x198));
                FastVecAdd(object + 0x10, object + 0x10, &velocity);
                if (*(s16 *)(state + 0x1B4)) {
                    if (vec_distance_xy(object + 0x10, &point) < 2.0f)
                        --*(s32 *)(state + 0x194);
                    if (*(s32 *)(state + 0x194) < 0)
                        *(s32 *)(state + 0x194) = *(s32 *)path - 1;
                } else {
                    if (vec_distance_xy(object + 0x10, &point) < 2.0f)
                        ++*(s32 *)(state + 0x194);
                    if (*(s32 *)(state + 0x194) >= *(s32 *)path)
                        *(s32 *)(state + 0x194) = 0;
                }
                if (*(s32 *)(state + 0x194) >= *(s32 *)path - 6 && *(float *)(state + 0x198) >= 0.10000001f)
                    *(float *)(state + 0x198) -= 0.0025f;
                func_002A677C(object);
                moby_turn_toward_target_and_step((char *)object, point.f, *(float *)(state + 0x190));
                math_step_value_toward_target((float *)(object + 0x18), (float *)(state + 0x108), *(float *)(state + 0x188), 0.0027777778f, 0.0027777778f, 0.16666667f);
            }
            if (*(s16 *)(state + 0x1B8)) moby_set_state(object, 8, 3);
        }
        break;
    case 8:
        if (flag_set_first_pending(object))
            moby_set_controller_speed_limits(object, 0.008333334f, 1.0f, 0.001163553f, 0.10471977f);
        if (range >= 1.7f)
            moby_turn_toward_target_and_step((char *)object, target.f, *(float *)(state + 0x190));
        height = *(float *)(ground + 8) + 0.7f;
        math_step_value_toward_target((float *)(object + 0x18), (float *)(state + 0x108), height, 0.0027777778f, 0.0027777778f, 0.16666667f);
        if (range < 1.7f && math_fabs(*(float *)(object + 0x18) - height) < 0.1f) {
            *(u16 *)(object + 0x96) = 0;
            moby_set_state(object, 10, -1);
        }
        break;
    case 9:
        if (flag_set_first_pending(object) && object[0x43] != 2) anim_start_blended(object, 2, 0, 3);
        if (object[0x60] & 2) {
            if (object[0x43] != 3) anim_start_blended(object, 3, 0, 5);
            moby_set_state(object, 11, -1);
        }
        /* Emits nothing, but keeps a label here, so case 9's tail stays apart from case 12's. */
        height = 0.0f;
        break;
    case 11:
        if (flag_set_second_pending(object)) {
            moby_set_controller_speed_limits(object, 0.0011111111380159855f, 0.033333335f, 0.001163553f, 0.10471977f);
            *(u16 *)(object + 0x96) = 0;
        }
        *(float *)(object + 0x48) = 1.75f;
        math_step_value_toward_target((float *)(object + 0x18), (float *)(state + 0x108), *(float *)(ground + 8) + 0.7f, 0.0027777778f, 0.0027777778f, 0.16666667f);
        if (range >= 1.7f)
            moby_l01_turn_toward_target((char *)object, (char *)&target);
        else if (range < 1.7f) {
            FastVecSub(&point, object + 0x10, &target);
            vec_scale_to_length(&point, &point, 2.0f);
            FastVecAdd(&point, &point, object + 0x10);
            moby_l01_turn_toward_target((char *)object, (char *)&point);
        }
        i = 0;
        do {
            coll_test_hit_at_bone(0.5f, (float)state[0x34], 1.0f, object, i, 0x4000001, 0, 1, 0);
        } while (++i < 4);
        if (g_hero_state.contact == object) {
            moby_set_state(object, 12, -1);
            if (object[0x43] != 4) anim_start_blended(object, 4, 0, 5);
            *(float *)(object + 0x48) = 1.0f;
        }
        if (range > 4.0f && *(u16 *)(object + 0x96) > 120) {
            if (object[0x43] != 5) anim_start_blended(object, 5, 0, 15);
            moby_set_state(object, 4, -1);
            *(float *)(object + 0x48) = 1.0f;
        }
        break;
    case 12:
        if (object[0x60] & 2) {
            if (object[0x43]) anim_start_blended(object, 0, 0, 15);
            moby_set_state(object, 8, -1);
        }
        break;
    case 10:
        if (*(u16 *)(object + 0x96) > 44) {
            moby_set_state(object, 9, -1);
            if (object[0x43] != 2) anim_start_blended(object, 2, 0, 2);
            *(float *)(object + 0x48) = 1.0f;
        }
        break;
    }
    *(float *)(state + 0x170) = math_move_angle_toward_target(*(float *)(state + 0x170), g_blade_ball_turn_rate_x * 0.00029088825f, 0.0625f);
    *(float *)(state + 0x174) = math_move_angle_toward_target(*(float *)(state + 0x174), g_blade_ball_turn_rate_y[0] * 0.00029088825f, 0.0625f);
    *(float *)(state + 0x178) = math_move_angle_toward_target(*(float *)(state + 0x178), g_blade_ball_turn_rate_z[0] * 0.00029088825f, 0.0625f);
    *(float *)(object + 0xF0) = FastAddRotations(*(float *)(object + 0xF0), *(float *)(state + 0x170));
    *(float *)(object + 0xF4) = FastAddRotations(*(float *)(object + 0xF4), *(float *)(state + 0x174));
    *(float *)(object + 0xF8) = FastAddRotations(*(float *)(object + 0xF8), *(float *)(state + 0x178));
    if (ground && *(float *)(object + 0x18) <= *(float *)(ground + 8) + 0.4f) {
        if (!object[0x31]) {
            *(float *)(state + 0x108) = 0.016666668f;
            *(float *)(object + 0x18) = *(float *)(ground + 8) + 0.3f;
        } else if (coll_test_point(object + 0x10, 6, 0, 0.3f)) {
            float size;
            s32 side;
            *(float *)(state + 0x108) = 0.016666668f;
            *(float *)(object + 0x18) = *(float *)(ground + 8) + 0.3f;
            point.f[0] = *(float *)(object + 0x10) + math_random_float_range(-0.01f, 0.01f);
            point.f[1] = *(float *)(object + 0x14) + math_random_float_range(-0.01f, 0.01f);
            point.f[2] = *(float *)(object + 0x18) - 0.3f;
            size = math_random_float_range(g_blade_ball_size_min, g_blade_ball_size_max);
            side = math_random_int_below(2);
            if (!side) side--;
            vec_random_direction(velocity.f, g_blade_ball_spread_min * 0.016666668f, g_blade_ball_spread_max * 0.016666668f);
            velocity.f[2] = math_random_float_range(g_blade_ball_up_speed_min, g_blade_ball_up_speed_max) * 0.016666668f;
            part_spawn_ground_effect(size * 0.1f, size, g_blade_ball_ground_effect_param, &point, 60, 0x7F007F7F, 0, side, velocity.f, 0);
        }
    }
    if (*(s32 *)(state + 0xE0) > 180) {
        moby_set_anim_type_three(object, 0, 1);
        blade_ball_explode(object);
        *(s32 *)(state + 0xE0) = 0;
    }
    coll_sweep_from_object(object, object + 0x10, 0x4000000, 0.8f, 1.0f, 1.0f, 0, 1, 0);
    blade_ball_update_hit_reaction(object);
}
