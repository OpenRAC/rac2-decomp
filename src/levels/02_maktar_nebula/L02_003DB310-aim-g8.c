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
extern int moby_l01_turn_toward_target(char *, float *);
extern float vec_distance_xy(char *, void *);

/* Looks for a nearby enemy in front of the moby, and turns toward it, offset by a small angle. Returns 1 if one was found. */
int moby_turn_toward_nearby_enemy(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    float aim_target[4];
    u16 *group_entry;
    char *target_moby;
    float saved_turn_rate;
    float turn_angle;
    char *up_axis;

#define GROUP (*(int *)(vars + 0x4E0))
#define ANGLE()                                                                       \
    func_00283248(*(float *)(target_moby + 0x10) - *(float *)(moby + 0x10),                    \
                  *(float *)(target_moby + 0x14) - *(float *)(moby + 0x14))
    if (GROUP == -1)
        return 0;
    for (group_entry = g_entity_group_lists[GROUP];
         (GROUP & 0xFF) != 0xFF && GROUP <= g_group_max_index && group_entry != 0 &&
         ((group_entry != 0 && (s16)group_entry[-1] >= 0) || group_entry == g_entity_group_lists[GROUP]);
         group_entry++) {
        target_moby = (char *)D_L02_001B359C_1[0] + ((*group_entry & 0x7FFF) << 8);
        if (target_moby == 0)
            return 0;
        if (moby_get_busy_flag(target_moby) == 0)
            continue;
        if (!(vec_distance_xy(moby + 0x10, target_moby + 0x10) < g_moby_turn_max_distance))
            continue;
        if (!(FastDiffRots(*(float *)(moby + 0xF8), ANGLE()) < g_moby_turn_max_angle_deg * 0.017453294f))
            continue;
        if (group_entry == 0)
            return 0;

        FastVecSub(aim_target, (float *)(moby + 0x10), (float *)(target_moby + 0x10));
        up_axis = moby + 0xE0;
        turn_angle = g_moby_turn_angle_deg * 0.017453294f;
        math_apply_axis_rotation_to_quat(aim_target, aim_target, up_axis,
                      0.0f <= fast_subtract_rotations(*(float *)(moby + 0xF8), ANGLE()) ? -turn_angle : turn_angle);
        FastVecAdd(aim_target, aim_target, target_moby + 0x10);
        saved_turn_rate = *(float *)(vars + 0x144);
        *(float *)(vars + 0x144) = 0.0001f;
        moby_l01_turn_toward_target(moby, aim_target);
        *(float *)(vars + 0x144) = saved_turn_rate;
        return 1;
    }
#undef ANGLE
#undef GROUP
    return 0;
}
