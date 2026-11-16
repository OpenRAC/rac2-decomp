#include "common.h"

typedef int Quad __attribute__((mode(TI)));
extern f32 ApproachValue(void *, float, float);
extern void rivet_bot_init_check_hit(void *), rivet_bot_move_along_path(void *), part_fire_blend_particles(void *);
extern int flag_set_second_pending(void *), flag_set_first_pending(void *);
extern int math_random_int_range(int, int), FastDecTimer(void *);
extern void moby_set_state(void *, int, int), anim_start_blended(void *, int, int, int);
extern float vec_distance_xy(void *, void *), mat_fast_helper_a(float, float), math_random_float_range(float, float), math_random_signed_float_range(float, float);
extern int moby_dispatch_action_by_kind(void *, void *), math_is_value_within_step(void *, float);
extern void matrix_mul_vec3(void *, void *, void *), FastVecAdd(void *, void *, void *), FastVecSub(void *, void *, void *), vec_scale_to_length(void *, void *, float);
extern void part_spawn_explosion_with_sparks(void *, void *, int, float, float);
extern void part_spawn_effect_burst(void *, int, int, int, int, int, int, void *);
extern int PlayMobySound(int, int, void *);
extern void snd_stop_voice(int), SetDeathBits(void *, int, int), moby_mark_spawned(void *);
/* Integer and FP arguments retain their independent EE register-bank order. */
extern f32 math_approach_target_with_direction_mode(void *, float, void *, float, float, float, int);
extern void moby_compute_local_point(void *, void *, float, float, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern int coll_sweep_from_object(void *, void *, int, int, int, int, float, float, float);
extern char *trail_projectile_spawn(void *, void *, void *, int);
extern u8 g_hero_position[], g_sound_l03_slot_table[];
extern u8 g_effect_descriptor_default[] __attribute__((sda));
extern float g_rivet_bot_helper_arg __attribute__((sda));
extern float g_rivet_bot_second_value __attribute__((sda));
extern float g_rivet_bot_shot_speed __attribute__((sda));
/* The transform reads one complete vector; the file uses -G16 for its address. */
extern u8 g_rivet_bot_spawn_offset[16] __attribute__((sda));

/* Advance the path actor's behaviour, movement, animation and attack effects. */
void UpdateEndakoPathActor(u8 *entity)
{
    u8 *state = *(u8 **)(entity + 0x68);
    float spawnPosition[4] __attribute__((aligned(16)));
    float targetPosition[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float effectPosition[4] __attribute__((aligned(16)));
    int flags, hit;

    rivet_bot_init_check_hit(entity);

    switch (entity[0x95]) {
    case 0:
        if (flag_set_second_pending(entity))
            *(s16 *)(state + 0x332) = math_random_int_range(20, 60);
        if ((*(int *)(state + 0x204) == 1 || *(s16 *)(state + 0x336) != 0) && FastDecTimer(state + 0x332)) {
            moby_set_state(entity, 3, 2);
            if (entity[0x43] != 1)
                anim_start_blended(entity, 1, 0, 20);
            *(s16 *)(state + 0x336) = 0;
        }
        break;
    case 1:
        if (flag_set_second_pending(entity))
            *(s16 *)(state + 0x330) = math_random_int_range(120, 150);
        if (*(int *)(state + 0x204) == 1 || *(s16 *)(state + 0x336)) {
            moby_set_state(entity, 5, 2);
            if (entity[0x43] != 4)
                anim_start_blended(entity, 4, 0, 20);
            *(s16 *)(state + 0x336) = 0;
        } else if (!*(s16 *)(state + 0x330)) {
            if (vec_distance_xy(entity + 0x10, g_hero_position) > 24.0f) {
                moby_set_state(entity, 1, 0);
                if (entity[0x43] != 0)
                    anim_start_blended(entity, 0, 0, 20);
            } else {
                moby_set_state(entity, 4, 2);
                if (entity[0x43] != 3)
                    anim_start_blended(entity, 3, 0, 20);
            }
        }
        break;
    case 2:
        if (flag_set_second_pending(entity))
            *(int *)(state + 0x34C) = math_random_int_range(400, 500);
        if (*(int *)(state + 0x204) != 1 && entity[0x20] == 5 && !*(int *)(state + 0x34C)) {
            moby_set_state(entity, 2, 1);
            if (entity[0x43] != 2)
                anim_start_blended(entity, 2, 0, 20);
        }
        break;
    case 3:
        flags = moby_dispatch_action_by_kind(entity, state + 0x50);
        if ((flags & 1) || (entity[0x43] == 8 && math_is_value_within_step(entity, 8.0f))) {
            matrix_mul_vec3(spawnPosition, g_rivet_bot_spawn_offset, entity + 0xC0);
            FastVecAdd(spawnPosition, spawnPosition, entity + 0x10);
            part_spawn_explosion_with_sparks(entity, spawnPosition, -1, 0.5f, 13.0f);
            FastVecSub(targetPosition, entity + 0x10, g_hero_position);
            targetPosition[2] = 0;
            vec_scale_to_length(targetPosition, targetPosition, 0.10000001f);
            part_spawn_effect_burst(entity, 0xA0D, 5, 0, 0, 0, 0, g_effect_descriptor_default);
            PlayMobySound(6, 0, entity);
            if (*(int *)(state + 0x350) != -1) {
                u8 *sound = g_sound_l03_slot_table + *(int *)(state + 0x350) * 0x70;
                if (*(u8 **)(sound + 0x88) == entity && sound[0x74])
                    snd_stop_voice(*(int *)(state + 0x350));
            }
            *(int *)(state + 0x350) = -1;
            SetDeathBits(entity, 0, 3);
            moby_mark_spawned(entity);
            return;
        }
        if (flags & 2) {
            moby_set_state(entity, 5, 2);
            if (entity[0x43] != 4)
                anim_start_blended(entity, 4, 0, 20);
        }
        break;
    }

    switch (entity[0x20]) {
    case 1:
    case 2:
        break;
    case 3:
        {
            u8 *rotation = entity + 0xF8;
            float angle = mat_fast_helper_a(*(float *)(state + 0x1F0) - *(float *)(entity + 0x10),
                                        *(float *)(state + 0x1F4) - *(float *)(entity + 0x14));

            math_approach_target_with_direction_mode(rotation, angle, state + 0x1B4,
                          0.0034906589426100254f, 0.0034906589426100254f, 0.20943955f, 0);
        }
        moby_set_state(entity, 4, -1);
        if (entity[0x43] != 3)
            anim_start_blended(entity, 3, 0, 20);
        break;
    case 4:
        {
            u8 *rotation = entity + 0xF8;
            float angle = mat_fast_helper_a(*(float *)(state + 0x1F0) - *(float *)(entity + 0x10),
                                        *(float *)(state + 0x1F4) - *(float *)(entity + 0x14));

            math_approach_target_with_direction_mode(rotation, angle, state + 0x1B4,
                          0.0034906589426100254f, 0.0034906589426100254f, 0.20943955f, 0);
        }
        rivet_bot_move_along_path(entity);
        if (*(u16 *)(entity + 0x96) > 60) {
            moby_set_state(entity, 5, -1);
            if (entity[0x43] != 4)
                anim_start_blended(entity, 4, 0, 20);
        }
        break;
    case 5:
        if (flag_set_first_pending(entity)) {
            *(float *)(state + 0x33C) = 4.0f;
            *(float *)(state + 0x348) = math_random_float_range(3.5f, 4.5f) * 0.016666668f;
        }
        {
            u8 *rotation = entity + 0xF8;
            float angle = mat_fast_helper_a(*(float *)(state + 0x1F0) - *(float *)(entity + 0x10),
                                        *(float *)(state + 0x1F4) - *(float *)(entity + 0x14));

            math_approach_target_with_direction_mode(rotation, angle, state + 0x1B4,
                          0.0034906589426100254f, 0.0034906589426100254f, 0.20943955f, 0);
        }
        rivet_bot_move_along_path(entity);
        {
            float first = mat_fast_helper_a(*(float *)(state + 0x33C), g_rivet_bot_helper_arg);
            float second = g_rivet_bot_second_value;
            float value;

            *(float *)(state + 0x280) = first;
            value = mat_fast_helper_a(*(float *)(state + 0x33C), second);
            *(float *)(state + 0x308) = value;
            *(float *)(state + 0x288) = -value;
            *(float *)(state + 0x300) = -*(float *)(state + 0x280);
        }
        ApproachValue(state + 0x33C, 16.0f, *(float *)(state + 0x348));
        hit = 0;
        if (math_is_value_within_step(entity, 1.0f)) {
            hit = 1;
            moby_transform_joint_to_world(entity, 2, spawnPosition);
        } else if (math_is_value_within_step(entity, 11.0f)) {
            hit = 1;
            moby_transform_joint_to_world(entity, 3, spawnPosition);
        }
        if (hit) {
            float *target = targetPosition;
            float spread = math_random_signed_float_range(0, 0.5f);

            moby_compute_local_point(entity, target, *(float *)(state + 0x33C), spread, 0);
            FastVecSub(direction, targetPosition, spawnPosition);
            vec_scale_to_length(direction, direction, g_rivet_bot_shot_speed * 0.016666668f);
            coll_sweep_from_object(entity, spawnPosition, 1, 0, 1, 0, 0.6660000085830688f, (float)state[0x34], 1.0f);
            trail_projectile_spawn(entity, spawnPosition, direction, state[0x34]);
            *(Quad *)effectPosition = 0;
            effectPosition[0] = 2.5f;
            effectPosition[2] = 0.5f;
            matrix_mul_vec3(effectPosition, effectPosition, entity + 0xC0);
            FastVecAdd(effectPosition, effectPosition, entity + 0x10);
            coll_sweep_from_object(entity, effectPosition, 1, 0, 1, 0, 1.5f, (float)state[0x34], 3.0f);
        }
        if (*(float *)(state + 0x33C) >= 12.0f) {
            moby_set_state(entity, 6, -1);
            if (entity[0x43] != 5)
                anim_start_blended(entity, 5, 0, 20);
        }
        break;
    case 6:
        {
            u8 *rotation = entity + 0xF8;
            float angle = mat_fast_helper_a(*(float *)(state + 0x1F0) - *(float *)(entity + 0x10),
                                        *(float *)(state + 0x1F4) - *(float *)(entity + 0x14));

            math_approach_target_with_direction_mode(rotation, angle, state + 0x1B4,
                          0.0034906589426100254f, 0.0034906589426100254f, 0.20943955f, 0);
        }
        rivet_bot_move_along_path(entity);
        if (entity[0x60] & 2) {
            moby_set_state(entity, 5, -1);
            if (entity[0x43] != 4)
                anim_start_blended(entity, 4, 0, 20);
        }
        break;
    }
    part_fire_blend_particles(entity);
}
