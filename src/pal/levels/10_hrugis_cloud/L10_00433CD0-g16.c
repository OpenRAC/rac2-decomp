#include "include_asm.h"

#include "common.h"
extern int math_random_int_below(int);
extern float math_random_float_range(float, float);
extern int math_fast_float_d(void *);
extern char g_cloud_path_points[];
extern char g_cloud_target_pos[16] __attribute__((sda));
extern float vec_spring_to_target(void *, void *, void *, float, float, float);
extern float fast_vec_dist(void *, void *);
extern void moby_set_state(void *, int, int);
extern void FastVecAdd(void *, void *, void *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern float FastAddRotations(float, float);
extern int cloud_check_object_blocked(void *);
extern char *moby_spawn_explosion_effect_pal(void *, int, int, int, int, int, int, int, float);
extern char *moby_spawn_large_explosion_pal(void *, int, int, int, int, int, int, int, int, int, int, float);
extern void moby_mark_spawned(void *);
extern void cloud_object_bounce_velocity_pal(void *);
extern void cloud_drop_reward(char *, int);
extern char *cloud_spawn_object_pal(int);

/* Update of a cloud object spawned by func_PAL_L10_00433CD0. State 0 waits for the timer at
   work+0x1C; state 1 steers to its point in D_L10_002BAC40 (state 2 within 2 units); state 2
   steers to the 16-byte target D_L10_001B1790 and bursts there. Then the velocity at work+0
   moves the object and decays, the angles spin, and leaving the 2..1021 box (or
   func_L10_0042E590) bursts it as well; otherwise func_PAL_L10_004342B0 runs on a random half of the frames.
   -G16 for the $gp target; -frac2-gcse-unsplit-edges keeps the object+0x10 PRE copy in the
   dispatch block, as retail (the split edge of the state-0 timer test would get its own). */
void cloud_object_update_pal(char *object)
{
    char *st = *(char **)(object + 0x68);

    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        if (math_fast_float_d(st + 0x1C))
            moby_set_state(object, 1, -1);
        break;
    case 1: {
        float speed = math_random_float_range(2.0f, 4.0f) * 0.020000001f;
        vec_spring_to_target(object + 0x10, g_cloud_path_points + *(int *)(st + 0x28) * 16, st + 0x18,
                      0.0012f, 0.040000003f, speed);
        if (fast_vec_dist(object + 0x10, g_cloud_path_points + *(int *)(st + 0x28) * 16) < 2.0f)
            moby_set_state(object, 2, -1);
        break;
    }
    case 2:
        vec_spring_to_target(object + 0x10, g_cloud_target_pos, st + 0x18, 0.0048f, 0.0048f,
                      0.16000001f);
        if (fast_vec_dist(object + 0x10, g_cloud_target_pos) < 0.5f) {
            if (*(short *)(object + 0xAA) == 0x1315)
                moby_spawn_explosion_effect_pal(object + 0x10, 0, 0, 0, 0, 15, 0, 1, 0.7f);
            else
                moby_spawn_large_explosion_pal(object + 0x10, 0, 0, 0, 0, 10, 20, 1, 1, 0, 0, 0.7f);
            cloud_spawn_object_pal(*(int *)(st + 0x14));
            moby_mark_spawned(object);
            return;
        }
        break;
    }
    FastVecAdd(object + 0x10, object + 0x10, st);
    vec_scale_to_length(st, st, FastVecLength(st) * 0.9875f);
    *(float *)(object + 0xF8) = FastAddRotations(*(float *)(object + 0xF8), 0.03f);
    *(float *)(object + 0xF0) = FastAddRotations(*(float *)(object + 0xF0), 0.01f);
    *(float *)(object + 0xF4) = FastAddRotations(*(float *)(object + 0xF4), -0.02f);
    if (cloud_check_object_blocked(object) || *(float *)(object + 0x10) < 2.0f || *(float *)(object + 0x10) > 1021.0f ||
        *(float *)(object + 0x14) < 2.0f || *(float *)(object + 0x14) > 1021.0f ||
        *(float *)(object + 0x18) < 2.0f || *(float *)(object + 0x18) > 1021.0f) {
        cloud_drop_reward(object, 0);
        if (*(short *)(object + 0xAA) == 0x1315)
            moby_spawn_explosion_effect_pal(object + 0x10, 0, 0, 0, 0, 30, 0, 1, 0.7f);
        else
            moby_spawn_large_explosion_pal(object + 0x10, 0, 0, 0, 0, 20, 40, 1, 1, 0, 0, 0.7f);
        cloud_spawn_object_pal(*(int *)(st + 0x14));
        moby_mark_spawned(object);
    } else if (math_random_int_below(2)) {
        cloud_object_bounce_velocity_pal(object);
    }
}
