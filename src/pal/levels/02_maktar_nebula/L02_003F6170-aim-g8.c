#include "include_asm.h"

#include "common.h"
extern u16 *g_entity_group_lists[];
extern u8 *D_L02_001B359C_1[] __attribute__((sda));
extern int g_group_max_index __attribute__((sda));
extern float g_moby_turn_max_distance __attribute__((sda));
extern float g_moby_turn_max_angle_deg __attribute__((sda));
extern float g_moby_turn_angle_deg __attribute__((sda));
extern void FastVecSub(float *, float *, float *);
extern int moby_get_busy_flag(u8 *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float fast_subtract_rotations(float, float);
extern void math_apply_axis_rotation_to_quat(float *, float *, char *, float);
extern void FastVecAdd(float *, float *, u8 *);
extern int moby_l01_turn_toward_target_pal(char *, float *);
extern float vec_distance_xy(char *, void *);

/* Looks through the actor's group for a nearby enemy in front of it and, if one is found, turns away from it slightly (PAL). Returns 1 when it turned, else 0. */
int moby_turn_toward_nearby_enemy_pal(char *self) {
    char *state = *(char **)(self + 0x68);
    float turn_point[4];
    u16 *entry;
    char *e;
    float saved_turn_speed;
    float turn_angle;
    char *axis;

#define GROUP (*(int *)(state + 0x4E0))
#define ANGLE()                                                                       \
    func_00283248(*(float *)(e + 0x10) - *(float *)(self + 0x10),                    \
                  *(float *)(e + 0x14) - *(float *)(self + 0x14))
    if (GROUP == -1)
        return 0;
    for (entry = g_entity_group_lists[GROUP];
         (GROUP & 0xFF) != 0xFF && GROUP <= g_group_max_index && entry != 0 &&
         ((entry != 0 && (s16)entry[-1] >= 0) || entry == g_entity_group_lists[GROUP]);
         entry++) {
        e = (char *)D_L02_001B359C_1[0] + ((*entry & 0x7FFF) << 8);
        if (e == 0)
            return 0;
        if (moby_get_busy_flag(e) == 0)
            continue;
        if (!(vec_distance_xy(self + 0x10, e + 0x10) < g_moby_turn_max_distance))
            continue;
        if (!(FastDiffRots(*(float *)(self + 0xF8), ANGLE()) < g_moby_turn_max_angle_deg * 0.017453294f))
            continue;
        if (entry == 0)
            return 0;

        FastVecSub(turn_point, (float *)(self + 0x10), (float *)(e + 0x10));
        axis = self + 0xE0;
        turn_angle = g_moby_turn_angle_deg * 0.017453294f;
        math_apply_axis_rotation_to_quat(turn_point, turn_point, axis,
                      0.0f <= fast_subtract_rotations(*(float *)(self + 0xF8), ANGLE()) ? -turn_angle : turn_angle);
        FastVecAdd(turn_point, turn_point, e + 0x10);
        saved_turn_speed = *(float *)(state + 0x144);
        *(float *)(state + 0x144) = 0.0001f;
        moby_l01_turn_toward_target_pal(self, turn_point);
        *(float *)(state + 0x144) = saved_turn_speed;
        return 1;
    }
#undef ANGLE
#undef GROUP
    return 0;
}
