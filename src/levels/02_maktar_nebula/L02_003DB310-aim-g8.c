#include "common.h"

extern u16 *g_entity_group_lists[];
extern u8 *D_L02_001B359C_1[] __attribute__((sda));
extern int D_L02_001B35B8 __attribute__((sda));
extern float D_L02_001B0FA8 __attribute__((sda));
extern float D_L02_001B0FAC __attribute__((sda));
extern float D_L02_001B0FB0 __attribute__((sda));

extern void FastVecSub(float *, float *, float *);
extern int moby_get_busy_flag(u8 *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float fast_subtract_rotations(float, float);
extern void math_apply_axis_rotation_to_quat(float *, float *, char *, float);
extern void FastVecAdd(float *, float *, u8 *);
extern void moby_l01_turn_toward_target(char *, float *);
extern float vec_distance_xy(char *, void *);

/* Looks for a nearby enemy in front of the moby, and turns toward it, offset by a small angle. Returns 1 if one was found. */
int moby_turn_toward_nearby_enemy(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    float aimTarget[4];
    u16 *groupEntry;
    char *targetMoby;
    float savedTurnRate;
    float turnAngle;
    char *upAxis;

#define GROUP (*(int *)(vars + 0x4E0))
#define ANGLE()                                                                       \
    func_00283248(*(float *)(targetMoby + 0x10) - *(float *)(moby + 0x10),                    \
                  *(float *)(targetMoby + 0x14) - *(float *)(moby + 0x14))
    if (GROUP == -1)
        return 0;
    for (groupEntry = g_entity_group_lists[GROUP];
         (GROUP & 0xFF) != 0xFF && GROUP <= D_L02_001B35B8 && groupEntry != 0 &&
         ((groupEntry != 0 && (s16)groupEntry[-1] >= 0) || groupEntry == g_entity_group_lists[GROUP]);
         groupEntry++) {
        targetMoby = (char *)D_L02_001B359C_1[0] + ((*groupEntry & 0x7FFF) << 8);
        if (targetMoby == 0)
            return 0;
        if (moby_get_busy_flag(targetMoby) == 0)
            continue;
        if (!(vec_distance_xy(moby + 0x10, targetMoby + 0x10) < D_L02_001B0FA8))
            continue;
        if (!(FastDiffRots(*(float *)(moby + 0xF8), ANGLE()) < D_L02_001B0FAC * 0.017453294f))
            continue;
        if (groupEntry == 0)
            return 0;

        FastVecSub(aimTarget, (float *)(moby + 0x10), (float *)(targetMoby + 0x10));
        upAxis = moby + 0xE0;
        turnAngle = D_L02_001B0FB0 * 0.017453294f;
        math_apply_axis_rotation_to_quat(aimTarget, aimTarget, upAxis,
                      0.0f <= fast_subtract_rotations(*(float *)(moby + 0xF8), ANGLE()) ? -turnAngle : turnAngle);
        FastVecAdd(aimTarget, aimTarget, targetMoby + 0x10);
        savedTurnRate = *(float *)(vars + 0x144);
        *(float *)(vars + 0x144) = 0.0001f;
        moby_l01_turn_toward_target(moby, aimTarget);
        *(float *)(vars + 0x144) = savedTurnRate;
        return 1;
    }
#undef ANGLE
#undef GROUP
    return 0;
}
