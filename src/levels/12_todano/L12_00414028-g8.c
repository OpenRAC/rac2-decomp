#include "common.h"

extern float math_random_float_range(float, float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float vec_distance_xy(void *, void *);
extern u8 g_hero_state[];
extern float D_L12_001B1844 __attribute__((sda));

/* Picks the point the guard aims at. It uses a spot above the object the guard is holding, or
   the hero, or the guard's current target. */
void guard_update_aim_point(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *target;
    u8 *hero;
    u8 *hero_again;
    f32 aim_point[4] __attribute__((aligned(16)));
    f32 offset[4] __attribute__((aligned(16)));

    if (vars[0x30F] != 0 && (target = *(u8 **)(vars + 0x2F8)) != 0 && *(s16 *)(target + 0xAA) == 0x114B /* moby class 4427 */
        && target[0x20] != 0xFE && target[0x20] != 0xFD) {
        qcopy(aim_point, moby + 0x10);
        aim_point[2] += math_random_float_range(0.0f, 1.0f);
        vec_scale_to_length(offset, *(u8 **)(vars + 0x2F8) + 0xC0, 4.0f);
        FastVecAdd(vars + 0x1F0, aim_point, offset);
        return;
    }
    hero = g_hero_state;
    if (*(int *)(vars + 0x200) == *(int *)(hero + 0x2290)) {
        if (D_L12_001B1844 < vec_distance_xy(moby + 0x10, hero + 0x80)) {
            qcopy(vars + 0x1F0, hero + 0xD0);
        } else {
            qcopy(vars + 0x1F0, hero + 0xE0);
        }
        hero_again = g_hero_state;
        if (*(int *)(hero_again + 0x229C) == 0xC) {
            *(f32 *)(vars + 0x1F8) += 0.2f;
        } else {
            *(f32 *)(vars + 0x1F8) += 0.4f;
        }
    } else {
        qcopy(vars + 0x1F0, *(u8 **)(vars + 0x200) + 0x10);
        *(f32 *)(vars + 0x1F8) += 0.8f;
    }
}
