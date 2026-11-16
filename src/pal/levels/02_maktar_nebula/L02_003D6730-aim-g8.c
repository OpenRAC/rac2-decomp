#include "include_asm.h"

#include "common.h"
extern u16 *g_entity_group_lists[];
extern u8 *D_L02_001B359C_1[] __attribute__((sda));
extern int g_group_max_index __attribute__((sda));
extern float g_enemy_aim_range __attribute__((sda));
extern float g_enemy_l02_aim_cone_degrees __attribute__((sda));
extern float g_enemy_turn_angle_degrees __attribute__((sda));
extern void FastVecSub(float *, float *, float *);
extern int moby_get_busy_flag(u8 *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float fast_subtract_rotations(float, float);
extern void math_apply_axis_rotation_to_quat(float *, float *, char *, float);
extern void FastVecAdd(float *, float *, u8 *);
extern int moby_l01_turn_toward_target_pal(char *, float *);
extern float vec_distance_xy(char *, void *);

int AimAtGroupEntityInConeL02_pal(char *self) {
    char *state = *(char **)(self + 0x68);
    float buf[4];
    u16 *p;
    char *e;
    float saved;
    float r;
    char *ax;

#define GROUP (*(int *)(state + 0x2EC))
#define ANGLE()                                                                       \
    func_00283248(*(float *)(e + 0x10) - *(float *)(self + 0x10),                    \
                  *(float *)(e + 0x14) - *(float *)(self + 0x14))
    if (GROUP == -1)
        return 0;
    for (p = g_entity_group_lists[GROUP];
         (GROUP & 0xFF) != 0xFF && GROUP <= g_group_max_index && p != 0 &&
         ((p != 0 && (s16)p[-1] >= 0) || p == g_entity_group_lists[GROUP]);
         p++) {
        e = (char *)D_L02_001B359C_1[0] + ((*p & 0x7FFF) << 8);
        if (e == 0)
            return 0;
        if (moby_get_busy_flag(e) == 0)
            continue;
        if (!(vec_distance_xy(self + 0x10, e + 0x10) < g_enemy_aim_range))
            continue;
        if (!(FastDiffRots(*(float *)(self + 0xF8), ANGLE()) < g_enemy_l02_aim_cone_degrees * 0.017453294f))
            continue;
        if (p == 0)
            return 0;

        FastVecSub(buf, (float *)(self + 0x10), (float *)(e + 0x10));
        ax = self + 0xE0;
        r = g_enemy_turn_angle_degrees * 0.017453294f;
        math_apply_axis_rotation_to_quat(buf, buf, ax,
                      0.0f <= fast_subtract_rotations(*(float *)(self + 0xF8), ANGLE()) ? -r : r);
        FastVecAdd(buf, buf, e + 0x10);
        saved = *(float *)(state + 0x134);
        *(float *)(state + 0x134) = 0.0001f;
        moby_l01_turn_toward_target_pal(self, buf);
        *(float *)(state + 0x134) = saved;
        return 1;
    }
#undef ANGLE
#undef GROUP
    return 0;
}
