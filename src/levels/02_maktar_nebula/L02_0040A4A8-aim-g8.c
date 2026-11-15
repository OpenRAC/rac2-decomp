#include "common.h"

/* Same aim routine as func_L02_003D26B0, with this enemy's group and tuning data.
 * Keep the list guard and block order to preserve the target-position copy. */

extern u16 *g_entity_group_lists[];
extern u8 *D_L02_001B359C_1[] __attribute__((sda));
extern int D_L02_001B35B8 __attribute__((sda));
extern float D_L02_001B1918 __attribute__((sda));
extern float D_L02_001B191C __attribute__((sda));
extern float D_L02_001B1920 __attribute__((sda));

extern void FastVecSub(float *, float *, float *);
extern int moby_get_busy_flag(u8 *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float fast_subtract_rotations(float, float);
extern void math_apply_axis_rotation_to_quat(float *, float *, char *, float);
extern void FastVecAdd(float *, float *, u8 *);
extern void moby_l01_turn_toward_target(char *, float *);
extern float vec_distance_xy(char *, void *);

/* Looks for a nearby target in front of the robot and turns it toward that target. Returns 1 if it found one, otherwise 0. */
int robot_turn_toward_target(char *self) {
    char *state = *(char **)(self + 0x68);
    float aimPoint[4];
    u16 *listEntry;
    char *target;
    float savedValue;
    float turnAngle;
    char *axis;

#define GROUP (*(int *)(state + 0x2D0))
#define ANGLE()                                                                       \
    func_00283248(*(float *)(target + 0x10) - *(float *)(self + 0x10),                    \
                  *(float *)(target + 0x14) - *(float *)(self + 0x14))
    if (GROUP == -1)
        return 0;
    for (listEntry = g_entity_group_lists[GROUP];
         (GROUP & 0xFF) != 0xFF && GROUP <= D_L02_001B35B8 && listEntry != 0 &&
         ((listEntry != 0 && (s16)listEntry[-1] >= 0) || listEntry == g_entity_group_lists[GROUP]);
         listEntry++) {
        target = (char *)D_L02_001B359C_1[0] + ((*listEntry & 0x7FFF) << 8);
        if (target == 0)
            return 0;
        if (moby_get_busy_flag(target) == 0)
            continue;
        if (!(vec_distance_xy(self + 0x10, target + 0x10) < D_L02_001B1918))
            continue;
        if (!(FastDiffRots(*(float *)(self + 0xF8), ANGLE()) < D_L02_001B191C * 0.017453294f))
            continue;
        if (listEntry == 0)
            return 0;

        FastVecSub(aimPoint, (float *)(self + 0x10), (float *)(target + 0x10));
        axis = self + 0xE0;
        turnAngle = D_L02_001B1920 * 0.017453294f;
        math_apply_axis_rotation_to_quat(aimPoint, aimPoint, axis,
                      0.0f <= fast_subtract_rotations(*(float *)(self + 0xF8), ANGLE()) ? -turnAngle : turnAngle);
        FastVecAdd(aimPoint, aimPoint, target + 0x10);
        savedValue = *(float *)(state + 0x134);
        *(float *)(state + 0x134) = 0.0001f;
        moby_l01_turn_toward_target(self, aimPoint);
        *(float *)(state + 0x134) = savedValue;
        return 1;
    }
#undef ANGLE
#undef GROUP
    return 0;
}
