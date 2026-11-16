#include "names.h"
/* func_US2_L03_0041E914, the USA v2.00 copy of func_L03_0041D258: the same C, where case 5 of the
   second switch clears the s16 fields state+0x356 and state+0x354 in two places: inside the
   func_002B3868 test, and in a new `if (entity[0x60] & 2)` before the 12.0f test. */
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
void UpdateEndakoPathActor_us2(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    float spawnPosition[4] __attribute__((aligned(16)));
    float targetPosition[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float effectPosition[4] __attribute__((aligned(16)));
    int flags, hit;

    rivet_bot_init_check_hit(moby);

    switch (moby[0x95]) {
    case 0:
        if (flag_set_second_pending(moby))
            *(s16 *)(vars + 0x332) = math_random_int_range(20, 60);
        if ((*(int *)(vars + 0x204) == 1 || *(s16 *)(vars + 0x336) != 0) && FastDecTimer(vars + 0x332)) {
            moby_set_state(moby, 3, 2);
            if (moby[0x43] != 1)
                anim_start_blended(moby, 1, 0, 20);
            *(s16 *)(vars + 0x336) = 0;
        }
        break;
    case 1:
        if (flag_set_second_pending(moby))
            *(s16 *)(vars + 0x330) = math_random_int_range(120, 150);
        if (*(int *)(vars + 0x204) == 1 || *(s16 *)(vars + 0x336)) {
            moby_set_state(moby, 5, 2);
            if (moby[0x43] != 4)
                anim_start_blended(moby, 4, 0, 20);
            *(s16 *)(vars + 0x336) = 0;
        } else if (!*(s16 *)(vars + 0x330)) {
            if (vec_distance_xy(moby + 0x10, g_hero_position) > 24.0f) {
                moby_set_state(moby, 1, 0);
                if (moby[0x43] != 0)
                    anim_start_blended(moby, 0, 0, 20);
            } else {
                moby_set_state(moby, 4, 2);
                if (moby[0x43] != 3)
                    anim_start_blended(moby, 3, 0, 20);
            }
        }
        break;
    case 2:
        if (flag_set_second_pending(moby))
            *(int *)(vars + 0x34C) = math_random_int_range(400, 500);
        if (*(int *)(vars + 0x204) != 1 && moby[0x20] == 5 && !*(int *)(vars + 0x34C)) {
            moby_set_state(moby, 2, 1);
            if (moby[0x43] != 2)
                anim_start_blended(moby, 2, 0, 20);
        }
        break;
    case 3:
        flags = moby_dispatch_action_by_kind(moby, vars + 0x50);
        if ((flags & 1) || (moby[0x43] == 8 && math_is_value_within_step(moby, 8.0f))) {
            matrix_mul_vec3(spawnPosition, g_rivet_bot_spawn_offset, moby + 0xC0);
            FastVecAdd(spawnPosition, spawnPosition, moby + 0x10);
            part_spawn_explosion_with_sparks(moby, spawnPosition, -1, 0.5f, 13.0f);
            FastVecSub(targetPosition, moby + 0x10, g_hero_position);
            targetPosition[2] = 0;
            vec_scale_to_length(targetPosition, targetPosition, 0.10000001f);
            part_spawn_effect_burst(moby, 0xA0D, 5, 0, 0, 0, 0, g_effect_descriptor_default);
            PlayMobySound(6, 0, moby);
            if (*(int *)(vars + 0x350) != -1) {
                u8 *sound = g_sound_l03_slot_table + *(int *)(vars + 0x350) * 0x70;
                if (*(u8 **)(sound + 0x88) == moby && sound[0x74])
                    snd_stop_voice(*(int *)(vars + 0x350));
            }
            *(int *)(vars + 0x350) = -1;
            SetDeathBits(moby, 0, 3);
            moby_mark_spawned(moby);
            return;
        }
        if (flags & 2) {
            moby_set_state(moby, 5, 2);
            if (moby[0x43] != 4)
                anim_start_blended(moby, 4, 0, 20);
        }
        break;
    }

    switch (moby[0x20]) {
    case 1:
    case 2:
        break;
    case 3:
        {
            u8 *rotation = moby + 0xF8;
            float angle = mat_fast_helper_a(*(float *)(vars + 0x1F0) - *(float *)(moby + 0x10),
                                        *(float *)(vars + 0x1F4) - *(float *)(moby + 0x14));

            math_approach_target_with_direction_mode(rotation, angle, vars + 0x1B4,
                          0.0034906589426100254f, 0.0034906589426100254f, 0.20943955f, 0);
        }
        moby_set_state(moby, 4, -1);
        if (moby[0x43] != 3)
            anim_start_blended(moby, 3, 0, 20);
        break;
    case 4:
        {
            u8 *rotation = moby + 0xF8;
            float angle = mat_fast_helper_a(*(float *)(vars + 0x1F0) - *(float *)(moby + 0x10),
                                        *(float *)(vars + 0x1F4) - *(float *)(moby + 0x14));

            math_approach_target_with_direction_mode(rotation, angle, vars + 0x1B4,
                          0.0034906589426100254f, 0.0034906589426100254f, 0.20943955f, 0);
        }
        rivet_bot_move_along_path(moby);
        if (*(u16 *)(moby + 0x96) > 60) {
            moby_set_state(moby, 5, -1);
            if (moby[0x43] != 4)
                anim_start_blended(moby, 4, 0, 20);
        }
        break;
    case 5:
        if (flag_set_first_pending(moby)) {
            *(float *)(vars + 0x33C) = 4.0f;
            *(float *)(vars + 0x348) = math_random_float_range(3.5f, 4.5f) * 0.016666668f;
            *(s16 *)(vars + 0x356) = 0;
            *(s16 *)(vars + 0x354) = 0;
        }
        {
            u8 *rotation = moby + 0xF8;
            float angle = mat_fast_helper_a(*(float *)(vars + 0x1F0) - *(float *)(moby + 0x10),
                                        *(float *)(vars + 0x1F4) - *(float *)(moby + 0x14));

            math_approach_target_with_direction_mode(rotation, angle, vars + 0x1B4,
                          0.0034906589426100254f, 0.0034906589426100254f, 0.20943955f, 0);
        }
        rivet_bot_move_along_path(moby);
        {
            float first = mat_fast_helper_a(*(float *)(vars + 0x33C), g_rivet_bot_helper_arg);
            float second = g_rivet_bot_second_value;
            float value;

            *(float *)(vars + 0x280) = first;
            value = mat_fast_helper_a(*(float *)(vars + 0x33C), second);
            *(float *)(vars + 0x308) = value;
            *(float *)(vars + 0x288) = -value;
            *(float *)(vars + 0x300) = -*(float *)(vars + 0x280);
        }
        ApproachValue(vars + 0x33C, 16.0f, *(float *)(vars + 0x348));
        hit = 0;
        if (math_is_value_within_step(moby, 1.0f)) {
            hit = 1;
            moby_transform_joint_to_world(moby, 2, spawnPosition);
        } else if (math_is_value_within_step(moby, 11.0f)) {
            hit = 1;
            moby_transform_joint_to_world(moby, 3, spawnPosition);
        }
        if (hit) {
            float *target = targetPosition;
            float spread = math_random_signed_float_range(0, 0.5f);

            moby_compute_local_point(moby, target, *(float *)(vars + 0x33C), spread, 0);
            FastVecSub(direction, targetPosition, spawnPosition);
            vec_scale_to_length(direction, direction, g_rivet_bot_shot_speed * 0.016666668f);
            coll_sweep_from_object(moby, spawnPosition, 1, 0, 1, 0, 0.6660000085830688f, (float)vars[0x34], 1.0f);
            trail_projectile_spawn(moby, spawnPosition, direction, vars[0x34]);
            *(Quad *)effectPosition = 0;
            effectPosition[0] = 2.5f;
            effectPosition[2] = 0.5f;
            matrix_mul_vec3(effectPosition, effectPosition, moby + 0xC0);
            FastVecAdd(effectPosition, effectPosition, moby + 0x10);
            coll_sweep_from_object(moby, effectPosition, 1, 0, 1, 0, 1.5f, (float)vars[0x34], 3.0f);
        }
        if (moby[0x60] & 2) {
            *(s16 *)(vars + 0x356) = 0;
            *(s16 *)(vars + 0x354) = 0;
        }
        if (*(float *)(vars + 0x33C) >= 12.0f) {
            moby_set_state(moby, 6, -1);
            if (moby[0x43] != 5)
                anim_start_blended(moby, 5, 0, 20);
        }
        break;
    case 6:
        {
            u8 *rotation = moby + 0xF8;
            float angle = mat_fast_helper_a(*(float *)(vars + 0x1F0) - *(float *)(moby + 0x10),
                                        *(float *)(vars + 0x1F4) - *(float *)(moby + 0x14));

            math_approach_target_with_direction_mode(rotation, angle, vars + 0x1B4,
                          0.0034906589426100254f, 0.0034906589426100254f, 0.20943955f, 0);
        }
        rivet_bot_move_along_path(moby);
        if (moby[0x60] & 2) {
            moby_set_state(moby, 5, -1);
            if (moby[0x43] != 4)
                anim_start_blended(moby, 4, 0, 20);
        }
        break;
    }
    part_fire_blend_particles(moby);
}
