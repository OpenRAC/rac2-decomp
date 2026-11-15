#include "common.h"
typedef int Snapshot128 __attribute__((mode(TI)));
extern u8 D_L01_002A4D50[],g_hero_position[];
extern float D_L01_001B0420 __attribute__((sda));
extern float D_L01_001B0424 __attribute__((sda));
extern float D_L01_001B0428 __attribute__((sda));
extern float D_L01_001B042C __attribute__((sda));
extern float D_L01_001B0430 __attribute__((sda));
extern float D_L01_001B0434 __attribute__((sda));
extern void STUB_printf(void *,int,int);
extern float level_get_water_height(void);
extern float math_random_angle(void);
extern void moby_set_state(void *,int,int);
extern void moby_scale_owner_words_by_angles(void *,void *,void *,float,float,float);
extern float math_step_damped_spring(float *,float *,float,float,float,float);
extern float vec_distance_xy(void *,void *);
extern void FastVecSub(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
/* Initializes a floating object and keeps its motion above the water surface. */
/* Drifts on the water, bobbing with the waves. It is nudged aside when the hero gets close. */
void water_floater_update(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    float snapshots[2][4] __attribute__((aligned(16)));
    float pushVec[4] __attribute__((aligned(16)));
    float waterHeight, heroDistance, delta;

    if (!vars) {
        STUB_printf(D_L01_002A4D50, *(s16 *)(moby + 0xAA), *(s16 *)(moby + 0xB2));
        return;
    }
    switch (moby[0x20]) {
    case 0:
        if (level_get_water_height() > 0.0f) {
            *(float *)(vars + 0x20) = math_random_angle();
            *(float *)(vars + 0x24) = math_random_angle();
            *(float *)(vars + 0x28) = 0.02f;
            qcopy(vars, moby + 0x10);
            moby_set_state(moby, 1, -1);
        }
        break;
    case 1:
        /* Retail takes two position snapshots before updating movement. */
        *(Snapshot128 *)snapshots[0] = *(Snapshot128 *)(moby + 0x10);
        *(Snapshot128 *)snapshots[1] = *(Snapshot128 *)snapshots[0];
        waterHeight = level_get_water_height();
        moby_scale_owner_words_by_angles(moby, vars + 0x20, vars + 0x24, D_L01_001B0420,
                      D_L01_001B0424 * 0.00029088825f,
                      D_L01_001B0428 * 0.00029088825f);
        math_step_damped_spring((float *)(moby + 0x10), (float *)(vars + 0x10), *(float *)vars,
                          D_L01_001B042C * 0.00027777778f, D_L01_001B0430, 3.0f);
        math_step_damped_spring((float *)(moby + 0x14), (float *)(vars + 0x14), *(float *)(vars + 4),
                          D_L01_001B042C * 0.00027777778f, D_L01_001B0430, 3.0f);
        heroDistance = vec_distance_xy(moby + 0x10, g_hero_position);
        if (heroDistance < D_L01_001B0434 &&
            *(float *)(g_hero_position + 8) < *(float *)(moby + 0x18) + 0.8f) {
            FastVecSub(pushVec, moby + 0x10, g_hero_position);
            pushVec[2] = 0;
            vec_scale_to_length(pushVec, pushVec, (D_L01_001B0434 - heroDistance) * 0.08f);
            FastVecAdd(moby + 0x10, moby + 0x10, pushVec);
        }
        delta = waterHeight + *(float *)(vars + 0x28) - *(float *)(moby + 0x18);
        if (delta > 0.050000004f)
            delta = 0.050000004f;
        else if (delta < -0.050000004f)
            delta = -0.050000004f;
        *(float *)(moby + 0x18) += delta;
        break;
    }
}
