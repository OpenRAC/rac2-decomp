#include "names.h"
/* func_PAL_L00_003E6790, the PAL copy of func_L00_003E2510: the same C, where rename func_L00_003E3258 becomes func_PAL_L00_003E74D8; rename func_00334160 becomes func_PAL_00335DD0; rename func_L00_003E3668 becomes func_PAL_L00_003E78E8. */
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
extern void func_PAL_L00_003E74D8(void *, int, int);
extern int func_PAL_00335DD0(void *, int, int);
extern int PlayMobySound(int, int, char *);
extern int math_fast_float_d(void *);
extern void func_PAL_L00_003E78E8(void *);
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

void func_PAL_L00_003E6790(char *obj)
{
    float scratch[4], previous[4], delta[4], temp[4];
    unsigned char hit[48];
    float particle[4];
    char *state = *(char **)(obj + 0x68);
    char *target;
    char *info;
    char *p;
    float *tracking_delta;
    float length, speed, scale;
    int work, i;

    if (!save_is_record_value(*(int *)(state + 0x18), *(int *)(state + 0x14))) {
        table_clear_entry_flag(*(int *)(state + 0x34));
        moby_mark_spawned(obj);
        return;
    }
    cam_compute_view_direction(obj + 0x10, scratch, 1);
    qcopy(previous, obj + 0x10);
    target = *(char **)(state + 0x1C);
    if (target) {
        if (*(unsigned char *)(target + 0x20) == 0xFE) goto clear_target;
        if (*(unsigned char *)(target + 0x20) == 0xFD) goto clear_target;
        if (coll_is_living_hittable_target(target)) goto clear_target;
        {
            { float *t = delta;
            FastVecSub(t, *(char **)(state + 0x1C) + 0x10, obj + 0x10);
            tracking_delta = t;
            info = moby_get_private_value_0(*(char **)(state + 0x1C));
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
        part_steer_effect_direction(*(int *)(state + 0x34), state + 0x20, 0);
        FastVecAdd(obj + 0x10, obj + 0x10, state + 0x20);
        vec_transform_or_copy(obj + 0x10, obj + 0x10);
        *(float *)(obj + 0xF0) = FastAddRotations(*(float *)(obj + 0xF0), *(float *)(state + 0x44));
        *(float *)(obj + 0xF4) = FastAddRotations(*(float *)(obj + 0xF4), *(float *)(state + 0x48));
        *(float *)(obj + 0xF8) = FastAddRotations(*(float *)(obj + 0xF8), *(float *)(state + 0x4C));
        moby_update_color_scale(obj);
        *(char **)(hit + 0x10) = obj;
        *(int *)(hit + 0x14) = 0x10000;
        *(float *)(hit + 0x1C) = ((B2510Entry *)((unsigned char)g_item_slot_to_record[0x1E] * 0xE0 + (char *)g_weapon_l00_table))->value;
        *(int *)(hit + 0x20) = 1;
        qcopy(hit, state + 0x20);
        vec_scale_to_length(hit, hit, 1.0f);
        *(float *)(hit + 0xC) = 5627.925f;
        *(short *)(hit + 0x1A) = *(unsigned short *)(obj + 0xAA);
        hit[0x18] = 1;
        hit[0x19] = 1;
        if (CollLine(previous, obj + 0x10, 0, g_hero_moby, hit)) {
            if (!g_collision_result.target) func_PAL_L00_003E74D8(g_collision_result.position, 15, 0);
            else if (*(int *)(g_collision_result.target + 0x98)) {
                func_PAL_L00_003E74D8(g_collision_result.position, 10, 1);
                func_PAL_00335DD0(g_collision_result.target, 0x1E, *(int *)(obj + 0xB8));
            }
            PlayMobySound(0, 0, obj);
            *(unsigned char *)(obj + 0x20) = 1;
            *(char **)(state + 0x1C) = 0;
            *(unsigned short *)(obj + 0x34) |= 0x41;
            *(int *)(state + 0x38) = 5;
        } else if (math_fast_float_d(state + 0x38)) {
            func_PAL_L00_003E78E8(obj + 0x10);
            *(unsigned char *)(obj + 0x20) = 1;
            *(char **)(state + 0x1C) = 0;
            *(unsigned short *)(obj + 0x34) |= 0x41;
            *(int *)(state + 0x38) = 5;
        }
        work = math_random_int_below(255);
        p = part_spawn_gravity_fade(obj + 0x10, D_L00_001A8F20, 2, 0x202080, work, 64, 16, 420000.0f, 420000.0f, 0.0f, 1);
        if (p) p[2] = *D_L00_001FEA14;
        p = part_spawn_gravity_fade(obj + 0x10, D_L00_001A8F20, 2, 0x202080, (work + 128) % 255, 64, 16, 420000.0f, 420000.0f, 0.0f, 1);
        if (p) p[2] = *D_L00_001FEA14;
        work = (int)delta;
        FastVecSub((void *)work, obj + 0x10, previous);
        FastVecScale((char *)work, (char *)work, 0.2f);
        qcopy(temp, previous);
        tracking_delta = (float *)work;
        for (i = 4; i >= 0; i--) {
            work = math_random_int_below(255);
            scale = math_random_float_range(0.1f, 0.3f);
            particle[0] = temp[0] + math_random_signed_float_range(0.0f, 0.1f);
            particle[1] = temp[1] + math_random_signed_float_range(0.0f, 0.1f);
            particle[2] = temp[2] + math_random_signed_float_range(0.0f, 0.1f);
            part_spawn_gravity_fade(particle, D_L00_001A8F20, 12, 0x808080, work, 32, 0, scale * 210000.0f, scale * 42000.0f, 0.0f, 1);
            FastVecAdd(temp, temp, tracking_delta);
        }
        if (g_frame_l00_counter % 10 == 0) {
            p = part_spawn_gravity_fade(obj + 0x10, D_L00_001A8F20, 25, 0x202080, 0, 32, 0, 2100.0f, 420000.0f, 0.0f, 1);
            if (p) p[2] = *D_L00_001FE9F4;
        }
        ref_L00_003E2510_00(glowing_trail_update, obj);
        break;
    case 1:
        if (math_fast_float_d(state + 0x38)) {
            table_clear_entry_flag(*(int *)(state + 0x34));
            moby_mark_spawned(obj);
            return;
        }
        ref_L00_003E2510_00(glowing_trail_update, obj);
        break;
    }
    if (*(float *)(obj + 0x10) < 2.0f || *(float *)(obj + 0x10) > 1021.0f ||
        *(float *)(obj + 0x14) < 2.0f || *(float *)(obj + 0x14) > 1021.0f ||
        *(float *)(obj + 0x18) < 2.0f || *(float *)(obj + 0x18) > 1021.0f) {
        table_clear_entry_flag(*(int *)(state + 0x34));
        moby_mark_spawned(obj);
    }
}
