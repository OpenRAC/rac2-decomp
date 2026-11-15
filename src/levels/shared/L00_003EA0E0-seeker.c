#include "common.h"

/* Homing shot. The short-lived t and the int reused for the trail delta are what keep retail's copies past cprop: it is reassigned in the loop. */
extern void FastVecScale(char *, char *, float);
extern void cam_compute_view_direction(void *, void *, int);
extern int weapon_can_target_object(char *);
extern char *moby_get_private_value_0(char *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float FastVecLength(void *);
extern void vec_transform_or_copy(void *, void *);
extern float FastAddRotations(float, float);
extern void moby_pulse_axis_scale(char *);
extern void vec_scale_to_length(void *, void *, float);
extern int CollLine(void *, void *, int, void *, void *);
extern void part_l00_spawn_impact_spark_burst(void *, int, int);
extern void weapon_start_health_drain(void *, int, int);
extern int math_fast_float_d(void *);
extern void part_spawn_small_spark_burst(void *);
extern int math_random_int_below(int);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern char *part_spawn_gravity_fade(void *, void *, int, unsigned int, int, int, int, float, float, float, int);
extern void ref_L00_003ED198_00(void *, void *);
extern void moby_mark_spawned(void *);
extern char g_item_slot_to_record[];
typedef struct { unsigned char flag[4]; unsigned char enabled; char pad[0x6B]; float value; char tail[0x6C]; } B0714Entry;
extern B0714Entry g_weapon_l00_table[];
extern char *g_hero_moby NOT_SDA;
typedef struct { char pad[0x18]; char *target; char pad1[4]; float position[4]; } B0714Hit;
extern B0714Hit g_collision_result;
extern char D_L00_001A8F20[] __attribute__((sda));
extern unsigned char *D_L00_001FEA14;
extern unsigned char *D_L00_001FE9F4;
extern int g_frame_l00_counter __attribute__((sda));
extern char homing_shot_draw_trail[];

/* Updates the homing shot: it steers toward its target, hits things, leaves a trail and explodes. */
void homing_l00_shot_update_2(char *obj)
{
    float old[4], scratch[4], previous[4], delta[4], temp[4];
    unsigned char hit[48];
    float particle[4];
    char *state = *(char **)(obj + 0x68);
    char *target;
    char *info;
    char *spark;
    float *tracking_delta;
    float length, speed, scale;
    int temp_word, i;

    qcopy(old, obj + 0x10);
    cam_compute_view_direction(obj + 0x10, scratch, 1);
    qcopy(previous, obj + 0x10);
    target = *(char **)(state + 0x1C);
    if (target) {
        if (*(unsigned char *)(target + 0x20) == 0xFE) goto clear_target;
        if (*(unsigned char *)(target + 0x20) == 0xFD) goto clear_target;
        if (weapon_can_target_object(target)) goto clear_target;
        {
            { float *t = delta;
            FastVecSub(t, *(char **)(state + 0x1C) + 0x10, obj + 0x10);
            tracking_delta = t; }
            info = moby_get_private_value_0(*(char **)(state + 0x1C));
            if (info) {
                FastVecScale((char *)temp, *(char **)(state + 0x1C) + 0xE0, *(float *)(info + 0x10));
                FastVecAdd(tracking_delta, tracking_delta, temp);
            }
            length = FastVecLength(tracking_delta);
            if (length == 0.0f) goto clear_target;
            {
                speed = *(float *)(state + 0x2C);
                FastVecScale(state + 0x20, (char *)tracking_delta, speed / length);
                *(float *)(state + 0x2C) = speed;
            }
        }
    }
    goto target_done;
clear_target:
    *(char **)(state + 0x1C) = 0;
target_done:
    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        FastVecAdd(obj + 0x10, obj + 0x10, state + 0x20);
        vec_transform_or_copy(obj + 0x10, obj + 0x10);
        *(float *)(obj + 0xF0) = FastAddRotations(*(float *)(obj + 0xF0), *(float *)(state + 0x44));
        *(float *)(obj + 0xF4) = FastAddRotations(*(float *)(obj + 0xF4), *(float *)(state + 0x48));
        *(float *)(obj + 0xF8) = FastAddRotations(*(float *)(obj + 0xF8), *(float *)(state + 0x4C));
        moby_pulse_axis_scale(obj);
        *(char **)(hit + 0x10) = obj;
        *(int *)(hit + 0x14) = 0x10000;
        *(float *)(hit + 0x1C) = ((B0714Entry *)((unsigned char)g_item_slot_to_record[0x1F] * 0xE0 + (char *)g_weapon_l00_table))->value;
        *(int *)(hit + 0x20) = 1;
        qcopy(hit, state + 0x20);
        vec_scale_to_length(hit, hit, 1.0f);
        *(float *)(hit + 0xC) = 5627.925f;
        *(short *)(hit + 0x1A) = *(unsigned short *)(obj + 0xAA);
        hit[0x18] = 1;
        hit[0x19] = 1;
        if (CollLine(previous, obj + 0x10, 0, g_hero_moby, hit)) {
            if (!g_collision_result.target) part_l00_spawn_impact_spark_burst(g_collision_result.position, 15, 0);
            else if (*(int *)(g_collision_result.target + 0x98)) {
                part_l00_spawn_impact_spark_burst(g_collision_result.position, 10, 1);
                if (((B0714Entry *)((unsigned char)g_item_slot_to_record[0x1F] * 0xE0 + (char *)g_weapon_l00_table))->enabled)
                    weapon_start_health_drain(g_collision_result.target, 0x3D, *(int *)(obj + 0xB8));
                else
                    weapon_start_health_drain(g_collision_result.target, 0x1F, *(int *)(obj + 0xB8));
            }
            *(unsigned char *)(obj + 0x20) = 1;
            *(char **)(state + 0x1C) = 0;
            *(unsigned short *)(obj + 0x34) |= 0x41;
            *(int *)(state + 0x38) = 6;
        } else if (math_fast_float_d(state + 0x38)) {
            part_spawn_small_spark_burst(obj + 0x10);
            *(unsigned char *)(obj + 0x20) = 1;
            *(char **)(state + 0x1C) = 0;
            *(unsigned short *)(obj + 0x34) |= 0x41;
            *(int *)(state + 0x38) = 6;
        }
        temp_word = math_random_int_below(255);
        spark = part_spawn_gravity_fade(obj + 0x10, D_L00_001A8F20, 2, 0x202080, temp_word, 64, 16, 420000.0f, 420000.0f, 0.0f, 1);
        if (spark) spark[2] = *D_L00_001FEA14;
        spark = part_spawn_gravity_fade(obj + 0x10, D_L00_001A8F20, 2, 0x202080, (temp_word + 128) % 255, 64, 16, 420000.0f, 420000.0f, 0.0f, 1);
        if (spark) spark[2] = *D_L00_001FEA14;
        temp_word = (int)delta;
        FastVecSub((void *)temp_word, obj + 0x10, previous);
        FastVecScale((char *)temp_word, (char *)temp_word, 0.1f);
        qcopy(temp, previous);
        tracking_delta = (float *)temp_word;
        for (i = 4; i >= 0; i--) {
            temp_word = math_random_int_below(255);
            scale = math_random_float_range(0.1f, 0.3f);
            particle[0] = temp[0] + math_random_signed_float_range(0.0f, 0.05f);
            particle[1] = temp[1] + math_random_signed_float_range(0.0f, 0.05f);
            particle[2] = temp[2] + math_random_signed_float_range(0.0f, 0.05f);
            part_spawn_gravity_fade(particle, D_L00_001A8F20, 15, 0x808080, temp_word, 32, 0, scale * 210000.0f, scale * 42000.0f, 0.0f, 1);
            FastVecAdd(temp, temp, tracking_delta);
        }
        if (g_frame_l00_counter % 10 == 0) {
            spark = part_spawn_gravity_fade(obj + 0x10, D_L00_001A8F20, 30, 0x202080, 0, 32, 0, 2100.0f, 420000.0f, 0.0f, 1);
            if (spark) spark[2] = *D_L00_001FE9F4;
        }
        ref_L00_003ED198_00(homing_shot_draw_trail, obj);
        break;
    case 1:
        if (math_fast_float_d(state + 0x38)) {
            moby_mark_spawned(obj);
            return;
        }
        ref_L00_003ED198_00(homing_shot_draw_trail, obj);
        break;
    }
    if (*(float *)(obj + 0x10) < 2.0f || *(float *)(obj + 0x10) > 1021.0f ||
        *(float *)(obj + 0x14) < 2.0f || *(float *)(obj + 0x14) > 1021.0f ||
        *(float *)(obj + 0x18) < 2.0f || *(float *)(obj + 0x18) > 1021.0f)
        moby_mark_spawned(obj);
}
