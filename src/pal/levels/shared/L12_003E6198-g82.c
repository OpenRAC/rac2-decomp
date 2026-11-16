#include "include_asm.h"

#include "common.h"
extern char *g_path_zone_table[];
extern float g_enemy_height_limit SDATA(D_L12_001B0B14);
extern float g_robot_guard_climb_speed SDATA(D_L12_001B0A54);
extern char g_str_debug_ground_height[];
extern int moby_l01_turn_toward_target_pal(void *, void *);
extern float mat_fast_helper_a(float, float);
extern void StepAngleTowardTarget(void *, float, float, int);
extern float coll_probe_ground_height_below(float, void *, int);
extern double __extendsfdf2(float);
extern void STUB_printf(const char *, ...);

/* Moves the enemy toward its next path point while keeping it above the ground, and turns it toward the target (PAL: 50 Hz speeds). */
void enemy_move_along_path_keep_height_pal(char *object)
{
    char *state = *(char **)(object + 0x68);
    float old_height = *(float *)(object + 0x18);
    char *path = g_path_zone_table[*(int *)(state + 0x158)];
    int flags;
    float ground;
    float probe_radius;
    float target_height;
    char *position;

    *(int *)(state + 0x218) = 0;
    flags = moby_l01_turn_toward_target_pal(object, path + ((*(int *)(state + 0x264) << 4) + 0x10));
    if (*(u8 *)(object + 0x95) == 6) {
        char *target = *(char **)(state + 0x270);
        float angle = mat_fast_helper_a(*(float *)(target + 0x10) - *(float *)(object + 0x10),
                                   *(float *)(target + 0x14) - *(float *)(object + 0x14));
        StepAngleTowardTarget(object + 0xF8, angle, 7.2000003f, 0);
    }
    probe_radius = 0.5f;
    position = object + 0x10;
    ground = coll_probe_ground_height_below(probe_radius, position, 0);
    if (flags & 0x20) {
        if (*(int *)(state + 0x248) == 0 || *(float *)(object + 0x18) - ground > g_enemy_height_limit) {
            *(float *)(object + 0x18) = old_height;
        } else if (*(float *)(object + 0x18) < *(float *)(state + 0x2A8)) {
            *(float *)(object + 0x18) = *(float *)(state + 0x2A8);
        } else {
            char *sink = g_str_debug_ground_height;
            float floor = coll_probe_ground_height_below(probe_radius, position, 0);
            double height_difference = __extendsfdf2(*(float *)(object + 0x18) - floor);
            STUB_printf(sink, height_difference, *(short *)(object + 0xB2));
        }
    }
    target_height = *(float *)(path + (*(int *)(state + 0x264) << 4) + 0x18);
    if (*(float *)(object + 0x18) < target_height) {
        target_height -= *(float *)(object + 0x18);
        if (target_height > 0.8f) {
            *(float *)(object + 0x18) += g_robot_guard_climb_speed * 0.020000001f;
            if (*(float *)(object + 0x18) < ground)
                *(float *)(object + 0x18) = ground;
        }
    }
    target_height = *(float *)(path + (*(int *)(state + 0x264) << 4) + 0x18);
    if (*(float *)(object + 0x18) > target_height) {
        target_height -= *(float *)(object + 0x18);
        if (target_height < -0.8f) {
            *(float *)(object + 0x18) -= g_robot_guard_climb_speed * 0.020000001f;
            if (*(float *)(object + 0x18) < ground)
                *(float *)(object + 0x18) = ground;
        }
    }
    if (flags & 0x80)
        *(int *)(state + 0x16C) = 0;
}
