#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern unsigned char *D_L22_001AF314[] __attribute__((sda));
extern unsigned char *D_L22_001C00D8 NOT_SDA;
extern unsigned char D_00189F00[], D_L22_001B9C80[];
extern int D_L22_001AF304[] __attribute__((sda));
extern float D_L22_001AF308 __attribute__((sda));
extern float D_L22_001B2AA0;
extern float D_L22_001B2AA4;
extern float D_L22_001B11A0 __attribute__((sda));
extern float D_L22_001B11A4 __attribute__((sda));
extern float D_L22_001B11A8 __attribute__((sda));
extern float D_L22_001B11AC __attribute__((sda));
extern float D_L22_001B11B0 __attribute__((sda));
extern float D_L22_001B11B4 __attribute__((sda));
extern float D_L22_001B11BC __attribute__((sda));
extern float D_L22_001B11C0 __attribute__((sda));
extern float D_L22_001B11C4 __attribute__((sda));
extern void flying_enemy_update_states(void *), flyer_update_timers_anim(void *), moby_call_with_zero_vector(void *);
extern float fast_vec_dist(void *, void *), moby_measure_step_angle(void *, void *, int), gravity_get_center_distance(void *);
extern void moby_set_state(void *, int, int), anim_start_blended(void *, int, int, int);
extern void FastVecSub(void *, void *, void *), FastVecAdd(void *, void *, void *), matrix_mul_vec3(void *, void *, void *);
extern int WalkPathIsClear(void *, void *, void *), flag_set_second_pending(void *), moby_dispatch_action_by_kind(void *, void *);
extern void arena_push_point_out(void *, float);
extern int coll_test_point(void *, int, void *, float);
extern char *SpawnExplosion(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern void moby_mark_spawned(void *);
extern int math_random_int_below(int), math_random_int_range(int, int);
extern void part_spawn_joint_trails(void *, void *, float), moby_l22_steer_toward_target(void *, void *, int, float);
extern int moby_check_target_point_from_offset(void *, void *);
extern int snd_start_in_slot(int, int, int);
extern int moby_is_counter_below_limit(void);
extern void stored_object_forward(void *, int), vec_random_direction(void *, float, float);
extern float math_fabs(float);
extern unsigned char *cam_moby_create(void *, int, int, int, void *, void *, void *, int, float, float);
extern void moby_fade_out_update(void);
extern void vec_scale_to_length(void *, void *, float), FastVecScale(void *, void *, float);
extern void lane_find_nearest_point(void *, void *, void *, int);
extern int math_is_value_within_step(void *, float);
extern float math_random_float_range(float, float);
extern void part_spawn_random_direction_effect(void *, float, float);

typedef struct { unsigned char pad[0x80]; Vec position; unsigned char gap[0x2200]; unsigned char *moby; } HeroView;
extern HeroView g_hero_state;

/* Per-frame update of a flying enemy. It chases and attacks the hero, dodges, and breaks off with a burst when it hits something. */
void flying_l22_enemy_update(unsigned char *obj) {
    Vec delta, temp, push, old, posx, negx, posy, negy, offset, scatter;
    unsigned char *ctx = *(unsigned char **)(obj + 0x68);
    unsigned char *hit, *part;
    int collision, facing, visible, flags, i, choice;
    float distance;
    flying_enemy_update_states(obj);
    if (!D_L22_001AF314[0]) return;
    collision = 0; facing = 0; distance = 0.0f; visible = 0;
    if (obj[0x20] != 6 && obj[0x95] != 5) {
        if (fast_vec_dist(D_L22_001AF314[0] + 0x10, obj + 0x10) < D_L22_001B11A0) {
            collision = 1;
            moby_set_state(obj, 5, 3);
        }
        FastVecSub(&delta, (&g_hero_state.position), obj + 0x10);
        if (moby_measure_step_angle(obj, &delta, 0) <= 0.785398185f) facing = 1;
        if (WalkPathIsClear(D_L22_001AF314[0], (&g_hero_state.position), obj + 0x10)) visible = 1;
        distance = fast_vec_dist((&g_hero_state.position), obj + 0x10);
        if (gravity_get_center_distance(obj + 0x10) - D_L22_001B2AA4 > 9.19999981f) {
            qcopy(&temp, obj + 0x10);
            arena_push_point_out(&temp, 2.0f);
            if (coll_test_point(&temp, 0, obj, 5.0f) && (hit = D_L22_001C00D8) && *(short *)(hit + 0xAA) == 0xDCE /* moby class 3534 */) {
                SpawnExplosion(hit + 0x10, 0, 0x19, 0x14, 0x14, 0xA, 0xF, 1, 1, 0, 0, 0, 1.5f, 20.0f);
                moby_mark_spawned(hit);
            }
        }
    }
    switch (obj[0x95]) {
        case 0:
            if (flag_set_second_pending(obj) && obj[0x43] != 1) anim_start_blended(obj, 1, 0, 20);
            if (D_L22_001AF304[0]) break;
            if (visible && distance < 40.0f) {
                moby_set_state(obj, 3, 1);
                if (*(int *)(ctx + 0x258) < 300) *(int *)(ctx + 0x258) = math_random_int_range(480, 600);
            } else if (obj[0x31] && distance < 80.0f) {
                moby_l22_steer_toward_target(obj, ctx + 0x2A0, 1, D_L22_001B11AC);
            } else moby_call_with_zero_vector(obj);
            break;
        case 1:
            if (flag_set_second_pending(obj) && obj[0x43] != 1) anim_start_blended(obj, 1, 0, 20);
            if (!*(int *)(ctx + 0x258)) {
                moby_set_state(obj, 2, 0);
            } else if (visible && facing && distance < 30.0f) {
                moby_set_state(obj, 4, 2);
                moby_call_with_zero_vector(obj);
            } else moby_l22_steer_toward_target(obj, (&g_hero_state.position), 1, D_L22_001B11B4);
            break;
        case 2:
            if (facing || flag_set_second_pending(obj)) {
                if (obj[0x43] != 3) anim_start_blended(obj, 3, 0, 10);
                *(float *)(obj + 0x48) = D_L22_001B2AA0;
            } else if ((obj[0x60] & 2) && obj[0x43] == 3) anim_start_blended(obj, 1, 0, 10);
            if (!visible || distance > 50.0f) {
                moby_set_state(obj, 2, 0);
                *(int *)(ctx + 0x258) = 0;
            } else if (distance > 20.0f) moby_l22_steer_toward_target(obj, (&g_hero_state.position), 1, D_L22_001B11B4);
            else moby_check_target_point_from_offset(obj, (&g_hero_state.position));
            break;
        case 3:
            flags = moby_dispatch_action_by_kind(obj, ctx + 0x140);
            if ((flags & 1) || collision) {
                Vec *saved_position;
                snd_start_in_slot(17, 0, 0);
                if (*(void **)(ctx + 0x38) == g_hero_state.moby && moby_is_counter_below_limit()) stored_object_forward((&g_hero_state.position), 0);
                for (i = 0; i < 5; i++) {
                    vec_random_direction(&delta, D_L22_001B11BC * 0.0166666675f, D_L22_001B11C0 * 0.0166666675f);
                    delta.f[2] = math_fabs(delta.f[2]) * D_L22_001B11C4;
                    matrix_mul_vec3(&delta, &delta, obj + 0xC0);
                    part = cam_moby_create(obj, 1, *(short *)(obj + 0xAA), i, obj + 0x10, obj + 0xF0, &delta, 255, 30.0f, 15.0f);
                    *(void **)(part + 0x64) = moby_fade_out_update;
                }
                FastVecSub(&temp, D_L22_001B9C80, &delta);
                vec_scale_to_length(&temp, &temp, 1.0f);
                SpawnExplosion(obj + 0x10, 0, 25, 20, 20, 10, 15, 1, 1, 0, 0, 0, 1.5f, 20.0f);
                *(short *)(ctx + 0x178) = 0;
                *(int *)(obj + 0x98) = *(int *)(*(char **)(obj + 0x24) + 0x10);
                *(float *)(ctx + 0x20) = *(short *)(ctx + 0x24);
                saved_position = &old;
                /* This fresh scratch vector is consumed through calls; no C field
                 * access depends on moving across its copy. */
                qcopy_nc(saved_position, (&g_hero_state.position));
                arena_push_point_out(saved_position, 0.0f);
                FastVecScale(&push, g_hero_state.moby + 0xE0, -80.0f);
                switch (math_random_int_below(7)) {
                case 0: FastVecScale(&offset, g_hero_state.moby + 0xC0, -50.0f); break;
                case 1: FastVecScale(&offset, g_hero_state.moby + 0xD0, 50.0f); break;
                case 2: FastVecScale(&offset, g_hero_state.moby + 0xD0, -50.0f); break;
                case 3:
                    FastVecScale(&posy, g_hero_state.moby + 0xD0, 50.0f);
                    FastVecScale(&posx, g_hero_state.moby + 0xC0, 50.0f);
                    FastVecAdd(&offset, &posy, &posx); FastVecScale(&offset, &offset, 0.5f); break;
                case 4:
                    FastVecScale(&posx, g_hero_state.moby + 0xC0, 50.0f);
                    FastVecScale(&negy, g_hero_state.moby + 0xD0, -50.0f);
                    FastVecAdd(&offset, &posx, &negy); FastVecScale(&offset, &offset, 0.5f); break;
                case 5:
                    FastVecScale(&negy, g_hero_state.moby + 0xD0, -50.0f);
                    FastVecScale(&negx, g_hero_state.moby + 0xC0, -50.0f);
                    FastVecAdd(&offset, &negy, &negx); FastVecScale(&offset, &offset, 0.5f); break;
                case 6:
                    FastVecScale(&negx, g_hero_state.moby + 0xC0, -50.0f);
                    FastVecScale(&posy, g_hero_state.moby + 0xD0, 50.0f);
                    FastVecAdd(&offset, &negx, &posy); FastVecScale(&offset, &offset, 0.5f); break;
                }
                FastVecAdd(&push, &push, &offset);
                FastVecAdd(&push, &push, saved_position);
                lane_find_nearest_point(D_L22_001AF314[0], obj + 0x10, &push, 1);
                arena_push_point_out(obj + 0x10, 7.19999981f);
                if (coll_test_point(obj + 0x10, 1, 0, 3.0f) && *(short *)(D_L22_001C00D8 + 0xAA) == 0xEDD /* moby class 3805 */ && D_L22_001C00D8[0x20] != 6) {
                    FastVecScale(&scatter, obj + 0xC0 + math_random_int_below(2) * 16,
                                  2.0f * (math_random_int_below(2) ? D_L22_001AF308 : -D_L22_001AF308));
                    FastVecAdd(obj + 0x10, obj + 0x10, &scatter);
                    arena_push_point_out(obj + 0x10, 7.19999981f);
                }
                qcopy(ctx + 0x2A0, obj + 0x10);
                moby_set_state(obj, 2, 0);
            } else if (flags & 2) {
                moby_set_state(obj, 3, 1);
                *(int *)(ctx + 0x258) = math_random_int_range(580, 600);
            }
            break;
        case 4: case 5: break;
        }
    switch (obj[0x20]) {
    case 2: case 3: case 5: case 6: break;
    case 4:
        if (math_is_value_within_step(obj, 1.5f)) part_spawn_joint_trails(obj, D_00189F00, 0.0f);
        break;
    case 9:
        qcopy(&delta, obj + 0x10);
        arena_push_point_out(&delta, 7.19999981f);
        if (*(unsigned short *)(obj + 0x96) >= 61 && !(*(unsigned short *)(obj + 0x96) & 63)) part_spawn_joint_trails(obj, ctx + 0x2A0, 50.0f);
        if (fast_vec_dist(obj + 0x10, &delta) < 0.1f) {
            moby_set_state(obj, 2, 0);
            *(int *)(ctx + 0x88) &= ~0x10;
        } else moby_l22_steer_toward_target(obj, &delta, 0, D_L22_001B11B0);
        break;
    case 7:
        if ((*(unsigned short *)(obj + 0x96) & 7) == 7) {
            qcopy(&delta, *(void **)(ctx + 0x2B0));
            vec_scale_to_length(&delta, &delta, *(float *)(ctx + 0x2B4));
            FastVecAdd(&delta, (&g_hero_state.position), &delta);
            arena_push_point_out(&delta, 7.19999981f);
            qcopy(ctx + 0x2A0, &delta);
        }
        if (*(unsigned short *)(obj + 0x96) >= 61 && !(*(unsigned short *)(obj + 0x96) & 511)) part_spawn_joint_trails(obj, ctx + 0x2A0, 50.0f);
        if (fast_vec_dist(obj + 0x10, ctx + 0x2A0) < 2.0f || fast_vec_dist(obj + 0x10, (&g_hero_state.position)) < 20.0f) {
            moby_set_state(obj, 9, 5);
            *(int *)(ctx + 0x280) = 0;
        } else moby_l22_steer_toward_target(obj, ctx + 0x2A0, 0, D_L22_001B11B4);
        break;
    case 8: {
        float min, max;
        *(float *)(ctx + 0x2B4) = math_random_float_range(0.0f, 15.0f) + 10.0f;
        choice = math_random_int_below(4);
        switch (choice) {
        case 0: qcopy(&temp, g_hero_state.moby + 0xD0); FastVecScale(&temp, &temp, -1.0f); break;
        case 1: qcopy(&temp, g_hero_state.moby + 0xD0); break;
        case 2: qcopy(&temp, g_hero_state.moby + 0xC0); FastVecScale(&temp, &temp, -1.0f); break;
        case 3: qcopy(&temp, g_hero_state.moby + 0xC0); break;
        }
        min = D_L22_001B11A4; max = D_L22_001B11A8;
        *(void **)(ctx + 0x2B0) = g_hero_state.moby + 0xC0;
        FastVecScale(&delta, &temp, math_random_float_range(min, max));
        FastVecAdd(&delta, &delta, (&g_hero_state.position));
        part_spawn_random_direction_effect(&push, 0.1f, D_L22_001B11A4 * 0.333333343f);
        FastVecAdd(&delta, &delta, &push);
        qcopy(obj + 0x10, &delta);
        qcopy(&old, *(void **)(ctx + 0x2B0));
        vec_scale_to_length(&old, &old, *(float *)(ctx + 0x2B4));
        FastVecAdd(&old, (&g_hero_state.position), &old);
        arena_push_point_out(&old, 7.19999981f);
        qcopy(ctx + 0x2A0, &old);
        moby_set_state(obj, 7, 5);
        *(int *)(ctx + 0x28C) = 0;
        *(int *)(ctx + 0x88) |= 0x10;
        break;
    }
    }
    flyer_update_timers_anim(obj);
}
