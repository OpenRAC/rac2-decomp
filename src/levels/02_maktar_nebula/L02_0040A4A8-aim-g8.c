#include "common.h"

/* Same aim routine as func_L02_003D26B0, with this enemy's group and tuning data.
 * Keep the list guard and block order to preserve the target-position copy. */

extern u16 *D_L02_001FC060[];
extern u8 *D_L02_001B359C_1[] __attribute__((sda));
extern int D_L02_001B35B8 __attribute__((sda));
extern float D_L02_001B1918 __attribute__((sda));
extern float D_L02_001B191C __attribute__((sda));
extern float D_L02_001B1920 __attribute__((sda));

extern void func_00282CF0(float *, float *, float *);
extern int func_L02_003D7300(u8 *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern float func_00283BE0(float, float);
extern void func_002ACEC0(float *, float *, char *, float);
extern void func_00282CC0(float *, float *, u8 *);
extern void func_L01_00321178(char *, float *);
extern float func_00282E80(char *, void *);

/* Looks for a nearby target in front of the robot and turns it toward that target. Returns 1 if it found one, otherwise 0. */
int func_L02_0040BBD8(char *self) {
    char *state = *(char **)(self + 0x68);
    float aimPoint[4];
    u16 *listEntry;
    char *target;
    float savedValue;
    float turnAngle;
    char *axis;

#define GROUP (*(int *)(state + 0x2D0))
#define ANGLE()                                                                       \
    FastMatrixHelperA(*(float *)(target + 0x10) - *(float *)(self + 0x10),                    \
                  *(float *)(target + 0x14) - *(float *)(self + 0x14))
    if (GROUP == -1)
        return 0;
    for (listEntry = gEntityGroupLists[GROUP];
         (GROUP & 0xFF) != 0xFF && GROUP <= D_L02_001B35B8 && listEntry != 0 &&
         ((listEntry != 0 && (s16)listEntry[-1] >= 0) || listEntry == gEntityGroupLists[GROUP]);
         listEntry++) {
        target = (char *)D_L02_001B359C_1[0] + ((*listEntry & 0x7FFF) << 8);
        if (target == 0)
            return 0;
        if (GetMobyBusyFlag(target) == 0)
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
        ApplyAxisRotationToQuaternion(aimPoint, aimPoint, axis,
                      0.0f <= fast_subtract_rotations(*(float *)(self + 0xF8), ANGLE()) ? -turnAngle : turnAngle);
        FastVecAdd(aimPoint, aimPoint, target + 0x10);
        savedValue = *(float *)(state + 0x134);
        *(float *)(state + 0x134) = 0.0001f;
        TurnMobyTowardTarget(self, aimPoint);
        *(float *)(state + 0x134) = savedValue;
        return 1;
    }
#undef ANGLE
#undef GROUP
    return 0;
}
