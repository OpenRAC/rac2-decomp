#include "common.h"

/* func_L02_003D26B0, split out of L02_003D26B0.c: its unit needs -frac2-keep-block-order. The
 * list-pointer guard in front of the aim code is deleted by the compiler's null-pointer-check
 * pass (p was just dereferenced); without the block merge it leaves retail's CSE block boundary
 * there, which keeps the second saved copy of the target position (daddu of e + 0x10). The same
 * body, with a visibility test in front, is func_L11_00449C70. */

extern u16 *g_entity_group_lists[];
extern u8 *D_L02_001B359C_1[] __attribute__((sda));
extern int D_L02_001B35B8 __attribute__((sda));
extern float D_L02_001B016C __attribute__((sda));
extern float D_L02_001B0170 __attribute__((sda));
extern float D_L02_001B0174 __attribute__((sda));

extern void FastVecSub(float *, float *, float *);
extern int moby_get_busy_flag(u8 *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float fast_subtract_rotations(float, float);
extern void math_apply_axis_rotation_to_quat(float *, float *, char *, float);
extern void FastVecAdd(float *, float *, u8 *);
extern void moby_l01_turn_toward_target(char *, float *);
extern float vec_distance_xy(char *, void *);

/* Looks for a group member in front of the enemy and turns the enemy toward it. Returns 1 if one was found. */
int AimAtGroupEntityInConeL02(char *self) {
    char *state = *(char **)(self + 0x68);
    float aimPoint[4];
    u16 *idPtr;
    char *entity;
    float savedStep;
    float turnAngle;
    char *upAxis;

#define GROUP (*(int *)(state + 0x2EC))
#define ANGLE()                                                                       \
    func_00283248(*(float *)(entity + 0x10) - *(float *)(self + 0x10),                    \
                  *(float *)(entity + 0x14) - *(float *)(self + 0x14))
    if (GROUP == -1)
        return 0;
    for (idPtr = g_entity_group_lists[GROUP];
         (GROUP & 0xFF) != 0xFF && GROUP <= D_L02_001B35B8 && idPtr != 0 &&
         ((idPtr != 0 && (s16)idPtr[-1] >= 0) || idPtr == g_entity_group_lists[GROUP]);
         idPtr++) {
        entity = (char *)D_L02_001B359C_1[0] + ((*idPtr & 0x7FFF) << 8);
        if (entity == 0)
            return 0;
        if (moby_get_busy_flag(entity) == 0)
            continue;
        if (!(vec_distance_xy(self + 0x10, entity + 0x10) < D_L02_001B016C))
            continue;
        if (!(FastDiffRots(*(float *)(self + 0xF8), ANGLE()) < D_L02_001B0170 * 0.017453294f))
            continue;
        if (idPtr == 0)
            return 0;

        FastVecSub(aimPoint, (float *)(self + 0x10), (float *)(entity + 0x10));
        upAxis = self + 0xE0;
        turnAngle = D_L02_001B0174 * 0.017453294f;
        math_apply_axis_rotation_to_quat(aimPoint, aimPoint, upAxis,
                      0.0f <= fast_subtract_rotations(*(float *)(self + 0xF8), ANGLE()) ? -turnAngle : turnAngle);
        FastVecAdd(aimPoint, aimPoint, entity + 0x10);
        savedStep = *(float *)(state + 0x134);
        *(float *)(state + 0x134) = 0.0001f;
        moby_l01_turn_toward_target(self, aimPoint);
        *(float *)(state + 0x134) = savedStep;
        return 1;
    }
#undef ANGLE
#undef GROUP
    return 0;
}
