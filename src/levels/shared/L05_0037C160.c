#include "common.h"

extern char *moby_get_motion_data(char *);
extern int func_001163B0(void);
extern float math_random_float_range(float, float);
extern void FastVecAdd(void *, void *, void *), matrix_mul_vec3(void *, void *, void *);
extern int follower_get_state(char *);
extern void follower_clamp_range_spawn_sparks(char *), follower_check_hazard_contact(char *), follower_move_toward_target(char *), follower_limit_speed(char *), UpdateBankedOrientation(char *);
extern void follower_set_push_vector(char *, void *), follower_set_state(char *, int);
extern int follower_has_reached_target(char *), follower_try_place_at_saved_spot(char *);
extern void moby_release_motion_slot(char *), follower_start_random_push(char *), follower_start_push_from_target(char *);
extern float math_fast_sin_or_cos_b(float), math_fast_sin_or_cos_a(float), FastAddRotations(float, float);
extern void vec_scale_to_length(void *, void *, float), FastVecCross(void *, void *, void *);
extern int math_fast_helper_a(void *, float), math_random_int_range(int, int);
extern char *D_L05_001B9710;

typedef unsigned int U128_C160 __attribute__((mode(TI)));

/* Update the movement state and target position of this object. */
void moby_update_movement_state(char *obj)
{
    float v[4], v1[4], v2[4], v3[4], v4[4];
    U128_C160 axes[2];
    float v7[4], v8[4], v9[4], probe[4], tmp[4];
    char *s = moby_get_motion_data(obj);
    char *player, *p;
    float direction;
    if (!s) return;
    axes[0] = 0;
    axes[1] = 0;
    ((float *)&axes[0])[2] = 1.0f;
    ((float *)&axes[1])[0] = 1.0f;
    qcopy(s + 0xB0, obj + 0x10);
    if (follower_get_state(obj) != 8) FastVecAdd(obj + 0x10, s + 0x90, obj + 0x10);
    follower_clamp_range_spawn_sparks(obj);
    follower_check_hazard_contact(obj);
    follower_move_toward_target(obj);
    follower_limit_speed(obj);
    UpdateBankedOrientation(obj);
    player = D_L05_001B9710;
    switch (follower_get_state(obj)) {
    case 7:
        vec_scale_to_length(v, *(char **)(s + 0x120) + 0xC0, -50.0f);
        FastVecAdd(v, *(char **)(s + 0x120) + 0x10, v);
        follower_set_push_vector(obj, v);
        if (follower_has_reached_target(obj)) {
            follower_set_state(obj, 8);
            *(int *)(s + 0x130) = 900;
            direction = (func_001163B0() & 1) ? -1.0f : 1.0f;
            *(float *)(s + 0x140) = direction;
            *(float *)(s + 0x134) = direction < 0.0f ? 1.5707964f : -1.5707964f;
            *(float *)(s + 0x144) = math_random_float_range(5.0f, 15.0f);
        }
        break;
    case 8: {
            float *basis;
            v[2] = 0;
            v[0] = math_fast_sin_or_cos_b(*(float *)(s + 0x134)) * *(float *)(s + 0x144);
            v[1] = -math_fast_sin_or_cos_a(*(float *)(s + 0x134)) * *(float *)(s + 0x144);
            v[3] = 0;
            *(float *)(s + 0x134) = FastAddRotations(*(float *)(s + 0x134), *(float *)(s + 0x140) * 0.013089972f);
            qcopy(v9, player + 0x20);
            basis = v7;
            FastVecCross(v8, &axes[1], v9);
            vec_scale_to_length(v8, v8, 1.0f);
            FastVecCross(basis, v9, v8);
            matrix_mul_vec3(v, v, basis);
            FastVecAdd(obj + 0x10, *(char **)(s + 0x120) + 0x10, v);
            follower_set_push_vector(obj, v);
            if (follower_try_place_at_saved_spot(obj))follower_set_state(obj, 9);
            if (follower_has_reached_target(obj)) {
                qcopy(probe, obj + 0x10);
                probe[3] = 5;
                if (math_fast_helper_a(probe, 256.0f) == -1) {
                    moby_release_motion_slot(obj);
                    follower_set_state(obj, 1);
                }
            }
            break;
        }
    case 9:
        qcopy(probe, obj + 0x10);
        probe[3] = 5;
        if (math_fast_helper_a(probe, 256.0f) == -1) {
            moby_release_motion_slot(obj);
            follower_set_state(obj, 1);
        }
        break;
    case 4:
        if (!*(char **)(s + 0x120)) {
            moby_release_motion_slot(obj);
            follower_set_state(obj, 1);
            break;
        }
        vec_scale_to_length(v, *(char **)(s + 0x120) + 0xC0, 25.0f);
        if (*(int *)(s + 0xFC)) {
            matrix_mul_vec3(tmp, s + 0x70, *(char **)(s + 0x120) + 0xC0);
            FastVecAdd(v, tmp, v);
        }
        FastVecAdd(v, *(char **)(s + 0x120) + 0x10, v);
        follower_set_push_vector(obj, v);
        if (follower_has_reached_target(obj)) {
            follower_set_state(obj, 5);
            *(int *)(s + 0x130) = math_random_int_range(300, 600);
        }
        break;
    case 5:
        if (!*(char **)(s + 0x120)) {
            moby_release_motion_slot(obj);
            follower_set_state(obj, 1);
            break;
        }
        vec_scale_to_length(v, *(char **)(s + 0x120) + 0xC0, 5.0f);
        if (*(int *)(s + 0xFC)) {
            matrix_mul_vec3(tmp, s + 0x70, *(char **)(s + 0x120) + 0xC0);
            FastVecAdd(v, tmp, v);
        }
        FastVecAdd(v, *(char **)(s + 0x120) + 0x10, v);
        follower_set_push_vector(obj, v);
        if (follower_has_reached_target(obj)) {
            moby_release_motion_slot(obj);
            follower_set_state(obj, 1);
        }
        break;
    case 6:
        if (!*(char **)(s + 0x120)) {
            moby_release_motion_slot(obj);
            follower_set_state(obj, 1);
            break;
        }
        vec_scale_to_length(v, *(char **)(s + 0x120) + 0xC0, 10.0f);
        vec_scale_to_length(v1, *(char **)(s + 0x120) + 0xE0, 0.05f);
        if (*(int *)(s + 0xFC)) {
            matrix_mul_vec3(tmp, s + 0x70, *(char **)(s + 0x120) + 0xC0);
            FastVecAdd(v, tmp, v);
        }
        FastVecAdd(v, v1, v);
        FastVecAdd(v, *(char **)(s + 0x120) + 0x10, v);
        follower_set_push_vector(obj, v);
        if (follower_has_reached_target(obj)) {
            moby_release_motion_slot(obj);
            follower_set_state(obj, 1);
        }
        break;
    case 3:
        p = *(char **)(s + 0x10);
        qcopy(v2, p + 0xC0);
        FastVecCross(v3, v2, &axes[0]);
        vec_scale_to_length(v3, v3, 1.0f);
        FastVecCross(v4, v3, v2);
        matrix_mul_vec3(v, s, v2);
        FastVecAdd(v, p + 0x10, v);
        follower_set_push_vector(obj, v);
        break;
    case 1: if (follower_has_reached_target(obj))follower_start_random_push(obj);
        break;
    case 13: if (follower_has_reached_target(obj))follower_start_push_from_target(obj);
        break;
    }
}
