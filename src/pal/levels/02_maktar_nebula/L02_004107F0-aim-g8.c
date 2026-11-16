#include "include_asm.h"

#include "common.h"
extern u16 *g_entity_group_lists[];
extern u8 *D_L02_001B359C_1[] __attribute__((sda));
extern int g_group_max_index __attribute__((sda));
extern float g_robot_aim_distance_limit __attribute__((sda));
extern float g_robot_aim_tolerance_degrees __attribute__((sda));
extern float g_robot_turn_angle_degrees __attribute__((sda));
extern void FastVecSub(float *, float *, float *);
extern int moby_get_busy_flag(u8 *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float fast_subtract_rotations(float, float);
extern void math_apply_axis_rotation_to_quat(float *, float *, char *, float);
extern void FastVecAdd(float *, float *, u8 *);
extern int moby_l01_turn_toward_target_pal(char *, float *);
extern float vec_distance_xy(char *, void *);

/* Looks through the robot's entity group for one in front of it and close enough; if found,
   turns the robot a little away from it and returns 1, otherwise returns 0 (PAL: 50 Hz timings). */
int robot_turn_toward_target_pal(char *self) {
    char *state = *(char **)(self + 0x68);
    float aim_point[4];
    u16 *id_ptr;
    char *e;
    float saved_turn_rate;
    float turn_angle;
    char *axis;

#define GROUP (*(int *)(state + 0x2D0))
#define ANGLE()                                                                       \
    func_00283248(*(float *)(e + 0x10) - *(float *)(self + 0x10),                    \
                  *(float *)(e + 0x14) - *(float *)(self + 0x14))
    if (GROUP == -1)
        return 0;
    for (id_ptr = g_entity_group_lists[GROUP];
         (GROUP & 0xFF) != 0xFF && GROUP <= g_group_max_index && id_ptr != 0 &&
         ((id_ptr != 0 && (s16)id_ptr[-1] >= 0) || id_ptr == g_entity_group_lists[GROUP]);
         id_ptr++) {
        e = (char *)D_L02_001B359C_1[0] + ((*id_ptr & 0x7FFF) << 8);
        if (e == 0)
            return 0;
        if (moby_get_busy_flag(e) == 0)
            continue;
        if (!(vec_distance_xy(self + 0x10, e + 0x10) < g_robot_aim_distance_limit))
            continue;
        if (!(FastDiffRots(*(float *)(self + 0xF8), ANGLE()) < g_robot_aim_tolerance_degrees * 0.017453294f))
            continue;
        if (id_ptr == 0)
            return 0;

        FastVecSub(aim_point, (float *)(self + 0x10), (float *)(e + 0x10));
        axis = self + 0xE0;
        turn_angle = g_robot_turn_angle_degrees * 0.017453294f;
        math_apply_axis_rotation_to_quat(aim_point, aim_point, axis,
                      0.0f <= fast_subtract_rotations(*(float *)(self + 0xF8), ANGLE()) ? -turn_angle : turn_angle);
        FastVecAdd(aim_point, aim_point, e + 0x10);
        saved_turn_rate = *(float *)(state + 0x134);
        *(float *)(state + 0x134) = 0.0001f;
        moby_l01_turn_toward_target_pal(self, aim_point);
        *(float *)(state + 0x134) = saved_turn_rate;
        return 1;
    }
#undef ANGLE
#undef GROUP
    return 0;
}
