#include "common.h"

/* Homing missile, the sibling of func_L00_003ED198 (L00_003EA0E0-seeker.c). The lead correction
 * and the length call share a tail that jump2 cross-jumps, so func_00282CC0 is not the last call
 * of its block, which is what lets a1 be set before a0 for func_00282D30. The store to t on the
 * other arm is dead: it stops gcse propagating t over tracking_delta past the join, which would
 * keep t alive in a saved register. */
extern int save_is_record_value(int, int);
extern void FastVecScale(char *, char *, float);
extern void cam_compute_view_direction(void *, void *, int);
extern int coll_is_living_hittable_target(char *);
extern char *moby_get_private_value_0(char *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float FastVecLength(void *);
extern void part_steer_effect_direction(int, void *, int);
extern void vec_transform_or_copy(void *, void *);
extern float FastAddRotations(float, float);
extern void moby_update_color_scale(char *);
extern void vec_scale_to_length(void *, void *, float);
extern int CollLine(void *, void *, int, void *, void *);
extern void part_l00_spawn_spark_burst_3(void *, int, int);
extern void weapon_start_health_drain(void *, int, int);
extern int PlayMobySound(int, int, char *);
extern int math_fast_float_d(void *);
extern void part_spawn_small_spark_spray(void *);
extern int math_random_int_below(int);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern char *part_spawn_gravity_fade(void *, void *, int, unsigned int, int, int, int, float, float, float, int);
/* func_L00_002E6EF8 in 23 programs, its twin in levels 08, 09, 19 and 30. */
extern void ref_L00_003E2510_00(void *, void *);
extern void table_clear_entry_flag(int);
extern void moby_mark_spawned(void *);
extern char g_item_slot_to_record[];
typedef struct { unsigned char flag[4]; unsigned char enabled; char pad[0x6B]; float value; char tail[0x6C]; } B2510Entry;
extern B2510Entry g_weapon_l00_table[];
extern char *g_hero_moby NOT_SDA;
typedef struct { char pad[0x18]; char *target; char pad1[4]; float position[4]; } B2510Hit;
extern B2510Hit g_collision_result;
extern char D_L00_001A8F20[] __attribute__((sda));
extern unsigned char *D_L00_001FEA14;
extern unsigned char *D_L00_001FE9F4;
extern int g_frame_l00_counter __attribute__((sda));
extern char glowing_trail_update[];

/* Per-frame update of the homing missile. It steers toward its target, flies forward, damages what it hits, leaves a smoke trail, then explodes and removes itself. */
void UpdateHomingMissile(char *missile)
{
    float scratch[4], previous[4], delta[4], temp[4];
    unsigned char damageInfo[48];
    float particle[4];
    char *vars = *(char **)(missile + 0x68);
    char *target;
    char *info;
    char *effect;
    float *tracking_delta;
    float length, speed, scale;
    int randomValue, i;

    if (!save_is_record_value(*(int *)(vars + 0x18), *(int *)(vars + 0x14))) {
        table_clear_entry_flag(*(int *)(vars + 0x34));
        moby_mark_spawned(missile);
        return;
    }
    cam_compute_view_direction(missile + 0x10, scratch, 1);
    qcopy(previous, missile + 0x10);
    target = *(char **)(vars + 0x1C);
    if (target) {
        if (*(unsigned char *)(target + 0x20) == 0xFE) goto clear_target;
        if (*(unsigned char *)(target + 0x20) == 0xFD) goto clear_target;
        if (coll_is_living_hittable_target(target)) goto clear_target;
        {
            { float *t = delta;
            FastVecSub(t, *(char **)(vars + 0x1C) + 0x10, missile + 0x10);
            tracking_delta = t;
            info = moby_get_private_value_0(*(char **)(vars + 0x1C));
            if (info) {
                FastVecScale((char *)temp, (char *)scratch, *(float *)(info + 0x10));
                FastVecAdd(tracking_delta, tracking_delta, temp);
                length = FastVecLength(tracking_delta);
            } else {
                t = 0;
                length = FastVecLength(tracking_delta);
            } }
            if (length == 0.0f) goto clear_target;
            {
                speed = *(float *)(vars + 0x2C);
                FastVecScale(vars + 0x20, (char *)tracking_delta, speed / length);
                *(float *)(vars + 0x2C) = speed;
            }
        }
    }
    goto target_done;
clear_target:
    *(char **)(vars + 0x1C) = 0;
target_done:
    switch (*(unsigned char *)(missile + 0x20)) {
    case 0:
        part_steer_effect_direction(*(int *)(vars + 0x34), vars + 0x20, 0);
        FastVecAdd(missile + 0x10, missile + 0x10, vars + 0x20);
        vec_transform_or_copy(missile + 0x10, missile + 0x10);
        *(float *)(missile + 0xF0) = FastAddRotations(*(float *)(missile + 0xF0), *(float *)(vars + 0x44));
        *(float *)(missile + 0xF4) = FastAddRotations(*(float *)(missile + 0xF4), *(float *)(vars + 0x48));
        *(float *)(missile + 0xF8) = FastAddRotations(*(float *)(missile + 0xF8), *(float *)(vars + 0x4C));
        moby_update_color_scale(missile);
        *(char **)(damageInfo + 0x10) = missile;
        *(int *)(damageInfo + 0x14) = 0x10000;
        *(float *)(damageInfo + 0x1C) = ((B2510Entry *)((unsigned char)g_item_slot_to_record[0x1E] * 0xE0 + (char *)g_weapon_l00_table))->value;
        *(int *)(damageInfo + 0x20) = 1;
        qcopy(damageInfo, vars + 0x20);
        vec_scale_to_length(damageInfo, damageInfo, 1.0f);
        *(float *)(damageInfo + 0xC) = 5627.925f;
        *(short *)(damageInfo + 0x1A) = *(unsigned short *)(missile + 0xAA);
        damageInfo[0x18] = 1;
        damageInfo[0x19] = 1;
        if (CollLine(previous, missile + 0x10, 0, g_hero_moby, damageInfo)) {
            if (!g_collision_result.target) part_l00_spawn_spark_burst_3(g_collision_result.position, 15, 0);
            else if (*(int *)(g_collision_result.target + 0x98)) {
                part_l00_spawn_spark_burst_3(g_collision_result.position, 10, 1);
                weapon_start_health_drain(g_collision_result.target, 0x1E, *(int *)(missile + 0xB8));
            }
            PlayMobySound(0, 0, missile);
            *(unsigned char *)(missile + 0x20) = 1;
            *(char **)(vars + 0x1C) = 0;
            *(unsigned short *)(missile + 0x34) |= 0x41;
            *(int *)(vars + 0x38) = 6;
        } else if (math_fast_float_d(vars + 0x38)) {
            part_spawn_small_spark_spray(missile + 0x10);
            *(unsigned char *)(missile + 0x20) = 1;
            *(char **)(vars + 0x1C) = 0;
            *(unsigned short *)(missile + 0x34) |= 0x41;
            *(int *)(vars + 0x38) = 6;
        }
        randomValue = math_random_int_below(255);
        effect = part_spawn_gravity_fade(missile + 0x10, D_L00_001A8F20, 2, 0x202080, randomValue, 64, 16, 420000.0f, 420000.0f, 0.0f, 1);
        if (effect) effect[2] = *D_L00_001FEA14;
        effect = part_spawn_gravity_fade(missile + 0x10, D_L00_001A8F20, 2, 0x202080, (randomValue + 128) % 255, 64, 16, 420000.0f, 420000.0f, 0.0f, 1);
        if (effect) effect[2] = *D_L00_001FEA14;
        randomValue = (int)delta;
        FastVecSub((void *)randomValue, missile + 0x10, previous);
        FastVecScale((char *)randomValue, (char *)randomValue, 0.2f);
        qcopy(temp, previous);
        tracking_delta = (float *)randomValue;
        for (i = 4; i >= 0; i--) {
            randomValue = math_random_int_below(255);
            scale = math_random_float_range(0.1f, 0.3f);
            particle[0] = temp[0] + math_random_signed_float_range(0.0f, 0.1f);
            particle[1] = temp[1] + math_random_signed_float_range(0.0f, 0.1f);
            particle[2] = temp[2] + math_random_signed_float_range(0.0f, 0.1f);
            part_spawn_gravity_fade(particle, D_L00_001A8F20, 15, 0x808080, randomValue, 32, 0, scale * 210000.0f, scale * 42000.0f, 0.0f, 1);
            FastVecAdd(temp, temp, tracking_delta);
        }
        if (g_frame_l00_counter % 10 == 0) {
            effect = part_spawn_gravity_fade(missile + 0x10, D_L00_001A8F20, 30, 0x202080, 0, 32, 0, 2100.0f, 420000.0f, 0.0f, 1);
            if (effect) effect[2] = *D_L00_001FE9F4;
        }
        ref_L00_003E2510_00(glowing_trail_update, missile);
        break;
    case 1:
        if (math_fast_float_d(vars + 0x38)) {
            table_clear_entry_flag(*(int *)(vars + 0x34));
            moby_mark_spawned(missile);
            return;
        }
        ref_L00_003E2510_00(glowing_trail_update, missile);
        break;
    }
    if (*(float *)(missile + 0x10) < 2.0f || *(float *)(missile + 0x10) > 1021.0f ||
        *(float *)(missile + 0x14) < 2.0f || *(float *)(missile + 0x14) > 1021.0f ||
        *(float *)(missile + 0x18) < 2.0f || *(float *)(missile + 0x18) > 1021.0f) {
        table_clear_entry_flag(*(int *)(vars + 0x34));
        moby_mark_spawned(missile);
    }
}
