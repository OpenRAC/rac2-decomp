#include "common.h"
/* Interfaces as the call sites load them; ignored results stay unqualified.
 * Retail's call to func_L16_00404E40 loads a1, f12 and f13 although the callee
 * never reads them, so this caller declares the arguments it really passes. */
extern int snivelak_boss_update(void *), flag_set_second_pending(void *);
extern int math_random_int_range(int, int), FastDecTimer(short *);
extern void anim_start_blended(void *, int, int, int), moby_set_state(void *, int, int);
extern void SetDeathBits(void *, int, int), vec_random_direction(void *, float, float);
extern float math_fabs(float), math_random_signed_float_range(float, float), math_random_float_range(float, float);
extern void FastVecAdd(void *, void *, void *), FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern u8 *cam_moby_create(void *, int, int, int, void *, void *, void *, u8, float, float);
extern void moby_fade_out_update(void *), hero_copy_field_to_moby(void *), moby_mark_spawned(void *);
extern int PlayMobySound(int, int, void *);
extern void *part_create_flash(void *, int, int, int, int, int, int, int, float, int, int);
extern int moby_start_effect_from_entry(int, float), path_check_entry_for_moby(char *, int);
extern int path_follow_points(void *, void *, float, float);
extern float mat_fast_helper_a(float, float), vec_distance_xy(void *, void *), FastDiffRots(float, float);
extern float math_approach_target_with_direction_mode(float *, float *, float, float, float, float, int);
extern int math_is_value_within_step(void *, float);
extern void moby_transform_joint_to_world(char *, int, char *);
extern void *snivelak_spawn_aimed_shot(void *, void *, void *, int, float);
extern int CollLine(void *, void *, int, void *, void *);
extern float math_step_value_toward_target(float *, float *, float, float, float, float);
extern void boss_turret_update(void *);
typedef struct {
    u8 unknown00[0x80];
    float position80[4];
    u8 unknown90[0x50];
    float aimPositionE0[4];
    u8 unknownF0[0x2290 - 0xf0];
    u8 *target2290;
} PlayerView;
extern PlayerView g_hero_state NOT_SDA;
extern float g_particle_template[4] __attribute__((sda));
extern u8 *g_aim_target_moby NOT_SDA;
/* Partial view shared with the matched sibling death/debris update. */
extern struct {
    u8 pad000[0x160];
    float strength;
    u8 pad164[4];
    int duration, timer;
    u8 pad170[0x10];
    float damping;
    u8 pad184[4];
    int lifetime;
} D_L16_001B99C0;

/* Both destruction exits are written out. Sched2 still sees func_0029F338 in
 * the debris block, and its extra dependence decides that block's order; jump2
 * then merges the exits, so the early-out branches into the debris tail. */
void UpdateSnivelakAimingAndDebris(u8 *moby)
{
    u8 *state = *(u8 **)(moby + 0x68);
    float position[4] __attribute__((aligned(16)));
    float aim[4] __attribute__((aligned(16)));
    u8 *child;
    int i, attack;
    float angle, pitch;
    float *pitchField3, *pitchField6, *pitchField7, *pitchField5;
    if (snivelak_boss_update(moby)) {
        moby_mark_spawned(moby);
        return;
    }
    switch (moby[0x95]) {
    case 0:
        if (flag_set_second_pending(moby)) *(short *)(state + 0x25e) = math_random_int_range(0, 30);
        if (*(int *)(state + 0x260) == 1) {
            if (moby[0x43] != 3) anim_start_blended(moby, 3, 0, 10);
            moby_set_state(moby, 5, 2);
            if (*(int *)(state + 0x288) || *(int *)(state + 0x2ac)) {
                if (moby[0x43]) anim_start_blended(moby, 0, 0, 10);
                moby_set_state(moby, 4, 2);
            }
            if (*(int *)(state + 0x294) != -1) {
                moby_set_state(moby, 3, 2);
                if (!*(int *)(state + 0x2a8) || *(int *)(state + 0x2ac))
                    if (moby[0x43]) anim_start_blended(moby, 0, 0, 10);
            }
        } else if (*(int *)(state + 0x264) && FastDecTimer((short *)(state + 0x25e))) {
            moby_set_state(moby, 2, 1);
            *(int *)(state + 0x264) = 0;
            if (*(int *)(state + 0x258) < 300)
                *(int *)(state + 0x258) = math_random_int_range(480, 600);
        }
        break;
    case 1:
        if (*(int *)(state + 0x260) == 1 || *(int *)(state + 0x2b4) == 1)
            moby_set_state(moby, 5, 2);
        break;
    case 2:
        if (*(int *)(state + 0x260) == 1) break;
        if (*(int *)(state + 0x2b4) != 1 && moby[0x20] != 4 && moby[0x20] != 3) {
            moby_set_state(moby, 1, 0);
            if (moby[0x43]) anim_start_blended(moby, 0, 0, 10);
            *(int *)(state + 0x258) = math_random_int_range(580, 600);
        }
        break;
    case 3:
        if (*(float *)(state + 0x20) <= 0.0f) {
            SetDeathBits(moby, 0, 3);
            for (i = 0; i < 5; i++) {
                vec_random_direction(position, 0.13333334f, 0.20000002f);
                position[2] = math_fabs(position[2]);
                position[2] *= 2.5f;
                FastVecAdd(position, position, g_particle_template);
                child = cam_moby_create(moby, 1, *(short *)(moby + 0xaa), i,
                    moby + 0x10, moby + 0xf0, position, 255, 30.0f, 15.0f);
                *(void (**)(void *))(child + 0x64) = moby_fade_out_update;
            }
            PlayMobySound(0, 0, moby);
            part_create_flash(moby + 0x10, 0, 15, 10, 10, 10, 15, 1, 2.0f, 1, 1);
            part_create_flash(moby + 0x10, 0, 15, 10, 10, 10, 15, 1, 1.0f, 1, 1);
            g_snivelak_hero_state.damping = 0.1f;
            g_snivelak_hero_state.lifetime = 90;
            g_snivelak_hero_state.strength = 0.2f;
            g_snivelak_hero_state.duration = 60;
            g_snivelak_hero_state.timer = 0;
            moby_mark_spawned(*(void **)(state + 0x274));
            position[0] = math_random_signed_float_range(0.5f, 4.0f) * 0.016666668f;
            position[1] = math_random_signed_float_range(0.0f, 4.0f) * 0.016666668f;
            position[2] = math_random_float_range(7.0f, 9.0f) * 0.016666668f;
            position[2] = math_fabs(position[2]);
            position[2] += position[2];
            FastVecAdd(position, position, g_particle_template);
            child = cam_moby_create(moby, 3, 0xecb, 0, moby + 0x10,
                moby + 0xf0, position, 255, 180.0f, 25.0f);
            hero_copy_field_to_moby(child);
            moby_mark_spawned(moby);
            return;
        }
        if (!(moby[0x60] & 2)) break;
        *(int *)(state + 0x2b8) = 0;
        *(short *)(state + 0x25c) = 0;
        if (*(int *)(state + 0x260) == 1) {
            if (moby[0x43] != 3) anim_start_blended(moby, 3, 0, 10);
            moby_set_state(moby, 5, 2);
            if (*(int *)(state + 0x298) != -1) moby_set_state(moby, 6, -1);
        } else {
            moby_set_state(moby, 2, 1);
            if (moby[0x43]) anim_start_blended(moby, 0, 0, 10);
            *(int *)(state + 0x258) = math_random_int_range(580, 600);
        }
        if (*(int *)(state + 0x2ac)) {
            moby_set_state(moby, 4, 2);
            if (moby[0x43]) anim_start_blended(moby, 0, 0, 10);
        }
        break;
    }
    attack = moby[0x20];
    switch (attack) {
    case 1:
    case 2:
        break;
    case 3:
        if (!*(int *)(state + 0x2ac))
            moby_start_effect_from_entry((int)moby, mat_fast_helper_a(g_hero_state.position80[0] - *(float *)(moby + 0x10),
                g_hero_state.position80[1] - *(float *)(moby + 0x14)));
        if (path_follow_points(moby, moby + 0x10, 0.0f, 0.0f)) {
            if (*(int *)(state + 0x298) != -1) {
                moby_set_state(moby, 6, -1);
                if (moby[0x43] != 3) anim_start_blended(moby, 3, 0, 10);
            } else {
                moby_set_state(moby, 5, -1);
                if (moby[0x43] != 3) anim_start_blended(moby, 3, 0, 10);
            }
            if (*(int *)(state + 0x288) || *(int *)(state + 0x2ac)) {
                if (moby[0x43]) anim_start_blended(moby, 0, 0, 10);
                moby_set_state(moby, 4, 2);
                *(float *)(state + 0x28c) = *(float *)(moby + 0x18) + 260.0f;
            }
        }
        if (!*(int *)(state + 0x2ac)) {
            pitchField3 = (float *)(moby + 0xf4);
            pitch = mat_fast_helper_a(vec_distance_xy(moby + 0x10, g_hero_state.target2290 + 0x10),
                *(float *)(g_hero_state.target2290 + 0x18) - *(float *)(moby + 0x18));
            math_approach_target_with_direction_mode(pitchField3, (float *)(state + 0x270),
                -pitch, 0.00349065894f, 0.00349065894f, 0.20943955f, 0);
        }
        if (!math_is_value_within_step(moby, 1.5f)) break;
        angle = mat_fast_helper_a(g_hero_state.position80[0] - *(float *)(moby + 0x10),
            g_hero_state.position80[1] - *(float *)(moby + 0x14));
        if (!(FastDiffRots(*(float *)(moby + 0xf8), angle) < 1.5707965f)) break;
        moby_transform_joint_to_world((char *)moby, 2, (char *)position);
        FastVecSub(aim, g_hero_state.aimPositionE0, position);
        vec_scale_to_length(aim, aim, 0.833333373f);
        snivelak_spawn_aimed_shot(moby, aim, position, 0, (float)state[0x34]);
        moby_transform_joint_to_world((char *)moby, 3, (char *)position);
        FastVecSub(aim, g_hero_state.aimPositionE0, position);
        vec_scale_to_length(aim, aim, 0.833333373f);
        snivelak_spawn_aimed_shot(moby, aim, position, 0, (float)state[0x34]);
        break;
    case 6:
        moby_start_effect_from_entry((int)moby, mat_fast_helper_a(g_hero_state.position80[0] - *(float *)(moby + 0x10),
            g_hero_state.position80[1] - *(float *)(moby + 0x14)));
        if (path_check_entry_for_moby((char *)moby, *(int *)(state + 0x298)) &&
            *(int *)(state + 0x29c) != -1) moby_set_state(moby, 7, -1);
        pitchField6 = (float *)(moby + 0xf4);
        pitch = mat_fast_helper_a(vec_distance_xy(moby + 0x10, g_hero_state.target2290 + 0x10),
            *(float *)(g_hero_state.target2290 + 0x18) - *(float *)(moby + 0x18));
        math_approach_target_with_direction_mode(pitchField6, (float *)(state + 0x270),
            -pitch, 0.00349065894f, 0.00349065894f, 0.20943955f, 0);
        if (!math_is_value_within_step(moby, 1.5f)) break;
        angle = mat_fast_helper_a(g_hero_state.position80[0] - *(float *)(moby + 0x10),
            g_hero_state.position80[1] - *(float *)(moby + 0x14));
        if (!(FastDiffRots(*(float *)(moby + 0xf8), angle) < 1.5707965f)) break;
        moby_transform_joint_to_world((char *)moby, 2, (char *)position);
        FastVecSub(aim, g_hero_state.aimPositionE0, position);
        vec_scale_to_length(aim, aim, 0.833333373f);
        if (!CollLine(position, g_hero_state.aimPositionE0, 0, moby, 0)) {
            snivelak_spawn_aimed_shot(moby, aim, position, 0, (float)state[0x34]);
        } else if (g_aim_target_moby && (g_aim_target_moby == g_hero_state.target2290 ||
                   *(short *)(g_aim_target_moby + 0xaa) != 0xebb)) {
            snivelak_spawn_aimed_shot(moby, aim, position, 0, (float)state[0x34]);
        }
        moby_transform_joint_to_world((char *)moby, 3, (char *)position);
        FastVecSub(aim, g_hero_state.aimPositionE0, position);
        vec_scale_to_length(aim, aim, 0.833333373f);
        if (!CollLine(position, g_hero_state.aimPositionE0, 0, moby, 0)) {
            snivelak_spawn_aimed_shot(moby, aim, position, 0, (float)state[0x34]);
        } else if (g_aim_target_moby && (g_aim_target_moby == g_hero_state.target2290 ||
                   *(short *)(g_aim_target_moby + 0xaa) != 0xebb)) {
            snivelak_spawn_aimed_shot(moby, aim, position, 0, (float)state[0x34]);
        }
        break;
    case 7:
        moby_start_effect_from_entry((int)moby, mat_fast_helper_a(g_hero_state.position80[0] - *(float *)(moby + 0x10),
            g_hero_state.position80[1] - *(float *)(moby + 0x14)));
        if (path_check_entry_for_moby((char *)moby, *(int *)(state + 0x29c)) &&
            *(int *)(state + 0x298) != -1) moby_set_state(moby, 6, -1);
        pitchField7 = (float *)(moby + 0xf4);
        pitch = mat_fast_helper_a(vec_distance_xy(moby + 0x10, g_hero_state.target2290 + 0x10),
            *(float *)(g_hero_state.target2290 + 0x18) - *(float *)(moby + 0x18));
        math_approach_target_with_direction_mode(pitchField7, (float *)(state + 0x270),
            -pitch, 0.00349065894f, 0.00349065894f, 0.20943955f, 0);
        if (!math_is_value_within_step(moby, 1.5f)) break;
        angle = mat_fast_helper_a(g_hero_state.position80[0] - *(float *)(moby + 0x10),
            g_hero_state.position80[1] - *(float *)(moby + 0x14));
        if (!(FastDiffRots(*(float *)(moby + 0xf8), angle) < 1.5707965f)) break;
        moby_transform_joint_to_world((char *)moby, 2, (char *)position);
        FastVecSub(aim, g_hero_state.aimPositionE0, position);
        vec_scale_to_length(aim, aim, 0.833333373f);
        if (!CollLine(position, g_hero_state.aimPositionE0, 0, moby, 0)) {
            snivelak_spawn_aimed_shot(moby, aim, position, 0, (float)state[0x34]);
        } else if (g_aim_target_moby && (g_aim_target_moby == g_hero_state.target2290 ||
                   *(short *)(g_aim_target_moby + 0xaa) != 0xebb)) {
            snivelak_spawn_aimed_shot(moby, aim, position, 0, (float)state[0x34]);
        }
        moby_transform_joint_to_world((char *)moby, 3, (char *)position);
        FastVecSub(aim, g_hero_state.aimPositionE0, position);
        vec_scale_to_length(aim, aim, 0.833333373f);
        if (!CollLine(position, g_hero_state.aimPositionE0, 0, moby, 0)) {
            snivelak_spawn_aimed_shot(moby, aim, position, 0, (float)state[0x34]);
        } else if (g_aim_target_moby && (g_aim_target_moby == g_hero_state.target2290 ||
                   *(short *)(g_aim_target_moby + 0xaa) != 0xebb)) {
            snivelak_spawn_aimed_shot(moby, aim, position, 0, (float)state[0x34]);
        }
        break;
    case 4:
        math_step_value_toward_target((float *)(moby + 0x18), (float *)(state + 0x290),
            *(float *)(state + 0x28c), 0.0125f, 0.0027777778f, 0.06666667f);
        if (!(*(float *)(state + 0x28c) - *(float *)(moby + 0x18) < 0.3f) ||
            *(int *)(state + 0x2ac)) break;
        if (moby[0x43] != 3) anim_start_blended(moby, 3, 0, 10);
        moby_set_state(moby, 5, -1);
        if (*(int *)(state + 0x298) != -1) moby_set_state(moby, 6, -1);
        break;
    case 5:
        moby_start_effect_from_entry((int)moby, mat_fast_helper_a(g_hero_state.position80[0] - *(float *)(moby + 0x10),
            g_hero_state.position80[1] - *(float *)(moby + 0x14)));
        pitchField5 = (float *)(moby + 0xf4);
        pitch = mat_fast_helper_a(vec_distance_xy(moby + 0x10, g_hero_state.target2290 + 0x10),
            *(float *)(g_hero_state.target2290 + 0x18) - *(float *)(moby + 0x18));
        math_approach_target_with_direction_mode(pitchField5, (float *)(state + 0x270),
            -pitch, 0.00349065894f, 0.00349065894f, 0.20943955f, 0);
        if (!math_is_value_within_step(moby, 1.5f)) break;
        angle = mat_fast_helper_a(g_hero_state.position80[0] - *(float *)(moby + 0x10),
            g_hero_state.position80[1] - *(float *)(moby + 0x14));
        if (!(FastDiffRots(*(float *)(moby + 0xf8), angle) < 1.5707965f)) break;
        moby_transform_joint_to_world((char *)moby, 2, (char *)position);
        FastVecSub(aim, g_hero_state.aimPositionE0, position);
        vec_scale_to_length(aim, aim, 0.833333373f);
        if (!CollLine(position, g_hero_state.aimPositionE0, 0, moby, 0)) {
            snivelak_spawn_aimed_shot(moby, aim, position, 0, (float)state[0x34]);
        } else if (g_aim_target_moby && (g_aim_target_moby == g_hero_state.target2290 ||
                   *(short *)(g_aim_target_moby + 0xaa) != 0xebb)) {
            snivelak_spawn_aimed_shot(moby, aim, position, 0, (float)state[0x34]);
        }
        moby_transform_joint_to_world((char *)moby, 3, (char *)position);
        FastVecSub(aim, g_hero_state.aimPositionE0, position);
        vec_scale_to_length(aim, aim, 0.833333373f);
        if (!CollLine(position, g_hero_state.aimPositionE0, 0, moby, 0)) {
            snivelak_spawn_aimed_shot(moby, aim, position, 0, (float)state[0x34]);
        } else if (g_aim_target_moby && (g_aim_target_moby == g_hero_state.target2290 ||
                   *(short *)(g_aim_target_moby + 0xaa) != 0xebb)) {
            snivelak_spawn_aimed_shot(moby, aim, position, 0, (float)state[0x34]);
        }
        break;
    }
    if ((unsigned int)moby[0x20] - 6 < 2) {
        if (moby[0x42] == 3) {
            if (++*(int *)(state + 0x2b8) > 240) {
                if (moby[0x43]) anim_start_blended(moby, 0, 0, 10);
                *(int *)(state + 0x2b8) = 0;
            }
        } else if (!moby[0x42] && ++*(short *)(state + 0x25c) > 60) {
            if (moby[0x43] != 3) anim_start_blended(moby, 3, 0, 10);
            *(short *)(state + 0x25c) = 0;
        }
    }
    boss_turret_update(moby);
}
