#include "common.h"

extern float func_002A7878(float, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282E80(void *, void *);
extern u8 D_00189E20[];
extern float D_L12_001B1844 __attribute__((sda));

/* Picks the point the guard aims at. It uses a spot above the object the guard is holding, or
   the hero, or the guard's current target. */
void func_L12_00414028(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *target;
    u8 *hero;
    u8 *heroAgain;
    f32 aimPoint[4] __attribute__((aligned(16)));
    f32 offset[4] __attribute__((aligned(16)));

    if (vars[0x30F] != 0 && (target = *(u8 **)(vars + 0x2F8)) != 0 && *(s16 *)(target + 0xAA) == 0x114B /* moby class 4427 */
        && target[0x20] != 0xFE && target[0x20] != 0xFD) {
        qcopy(aimPoint, moby + 0x10);
        aimPoint[2] += RandomFloatRange(0.0f, 1.0f);
        vec_scale_to_length(offset, *(u8 **)(vars + 0x2F8) + 0xC0, 4.0f);
        FastVecAdd(vars + 0x1F0, aimPoint, offset);
        return;
    }
    hero = gHeroState;
    if (*(int *)(vars + 0x200) == *(int *)(hero + 0x2290)) {
        if (D_L12_001B1844 < vec_distance_xy(moby + 0x10, hero + 0x80)) {
            qcopy(vars + 0x1F0, hero + 0xD0);
        } else {
            qcopy(vars + 0x1F0, hero + 0xE0);
        }
        heroAgain = gHeroState;
        if (*(int *)(heroAgain + 0x229C) == 0xC) {
            *(f32 *)(vars + 0x1F8) += 0.2f;
        } else {
            *(f32 *)(vars + 0x1F8) += 0.4f;
        }
    } else {
        qcopy(vars + 0x1F0, *(u8 **)(vars + 0x200) + 0x10);
        *(f32 *)(vars + 0x1F8) += 0.8f;
    }
}
