#include "common.h"
extern float D_L19_001B1D5C __attribute__((sda));
extern float D_L19_001B1D60 __attribute__((sda));
extern float D_L19_001B1D64 __attribute__((sda));
extern float D_L19_001B1D68 __attribute__((sda));
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00282E80(void *, void *);
extern void func_002A7750(void *, int, int);
extern int func_002B3868(void *);
extern void func_002E5CF8(int, int, void *);
typedef struct { u8 *other; float angle, height, time; } LiftState;
/* Lowers and rotates the lift, waits for the linked object to leave, then resets it. */
void func_L19_0041E5B0(u8 *moby)
{
    LiftState *vars = *(LiftState **)(moby + 0x68);
    switch (moby[0x20]) {
    case 0: {
        float angle, height;
        vars->other = 0;
        vars->angle = *(float *)(moby + 0xF8);
        vars->height = *(float *)(moby + 0x18);
        angle = FastAddRotations(*(float *)(moby + 0xF8), 3.1415927f);
        height = *(float *)(moby + 0x18) - D_L19_001B1D5C;
        *(float *)(moby + 0xF8) = angle;
        *(float *)(moby + 0x18) = height;
        SetMobyState(moby, 1, -1);
        break;
    }
    case 1:
        if (vars->other && vars->other[0x20] != 0xFE && vars->other[0x20] != 0xFD) {
            vars->time = 0;
            SetMobyState(moby, 2, -1);
        }
        break;
    case 2:
        if (SetFirstPendingFlag(moby)) PlayMobySound(0, 0, moby);
        vars->time += 1.0f / D_L19_001B1D60;
        if (vars->time > 1.0f) {
            vars->time = 0;
            *(float *)(moby + 0x18) = vars->height;
            moby[0xBC] = 1;
            SetMobyState(moby, 3, -1);
        } else {
            float ease = (FastSinOrCosA(vars->time * 3.1415927f) + 1.0f) * 0.5f;
            if (ease > 1.0f) ease = 1.0f;
            else if (ease < 0.0f) ease = 0.0f;
            *(float *)(moby + 0x18) = vars->height - ease * D_L19_001B1D5C;
        }
        break;
    case 3:
        vars->time += 1.0f / D_L19_001B1D64;
        if (vars->time > 1.0f) {
            vars->time = 0;
            *(float *)(moby + 0xF8) = vars->angle;
            moby[0xBC] = 2;
            SetMobyState(moby, 4, -1);
        } else {
            float ease = (FastSinOrCosA(vars->time * 3.1415927f) + 1.0f) * 0.5f;
            *(float *)(moby + 0xF8) = FastAddRotations(vars->angle, ease * 3.1415927f);
        }
        break;
    case 4:
        if (!vars->other || vars->other[0x20] == 0xFE || vars->other[0x20] == 0xFD ||
            vec_distance_xy(moby + 0x10, vars->other + 0x10) > D_L19_001B1D68) {
            moby[0xBC] = 3;
            vars->other = 0;
            vars->time = 1.0f;
            SetMobyState(moby, 5, -1);
        }
        break;
    case 5:
        if (SetFirstPendingFlag(moby)) PlayMobySound(1, 0, moby);
        vars->time -= 1.0f / D_L19_001B1D64;
        if (vars->time <= 0.0f) {
            vars->time = 1.0f;
            *(float *)(moby + 0xF8) = FastAddRotations(vars->angle, 3.1415927f);
            SetMobyState(moby, 6, -1);
        } else {
            float ease = (FastSinOrCosA(vars->time * 3.1415927f) + 1.0f) * 0.5f;
            *(float *)(moby + 0xF8) = FastAddRotations(vars->angle, ease * 3.1415927f);
        }
        break;
    case 6:
        vars->time -= 1.0f / D_L19_001B1D60;
        if (vars->time <= 0.0f) {
            float height = vars->height - D_L19_001B1D5C;
            vars->time = 0;
            moby[0xBC] = 0;
            *(float *)(moby + 0x18) = height;
            SetMobyState(moby, 1, -1);
        } else {
            float ease = (FastSinOrCosA(vars->time * 3.1415927f) + 1.0f) * 0.5f;
            if (ease > 1.0f) ease = 1.0f;
            else if (ease < 0.0f) ease = 0.0f;
            *(float *)(moby + 0x18) = vars->height - ease * D_L19_001B1D5C;
        }
        break;
    }
}
