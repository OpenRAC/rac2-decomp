#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern u8 *D_L12_001B2E9C MACRO_ADDR;
extern void func_002A7750(void *, int, int);
extern s32 func_002E5CF8(s32, s32, s32);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_002ACBC8(void *, int);

extern char D_00189EA0[];
extern char D_L12_001B9E00[];
extern float func_00282E80(void *, void *);
extern int func_00282948(void *);
extern float func_002AA548(void *, void *, float, float, float, float);
extern void func_00282D30(float, void *, void *);

/* Slides the door open while the hero or buddy is near its switch, and closes it again a moment after they leave. */
void func_L12_0041EDB8(u8 *self)
{
    s32 *vars = *(s32 **)(self + 0x68);
    int state = self[0x20];
    f32 vec[4];

    switch (state) {
    case 0:
        qcopy((u8 *)vars + 0x10, self + 0x10);
        SetMobyState(self, 1, -1);
        self[0x30] = 0x7F;
        break;
    case 1:
        if (vec_distance_xy(self + 0x10, D_L12_001B2E9C + (vars[0] << 8) + 0x10) < 5.0f) {
            vars[0xB] = state;
            vars[8] = 0x3C;
        } else if ((IsPointInCuboid(gHeroPosition, vars[1]) && vars[0xB] != 0) ||
                   (IsPointInCuboid(D_L12_001B9E00, vars[1]) && vars[0xB] != 0)) {
            vars[8] = 0x3C;
        }
        if (FastFloatHelperD((u8 *)vars + 0x20))
            StepValueTowardTarget((u8 *)vars + 0x24, (u8 *)vars + 0x28, 0.0f, 0.00055555557f, 0.00055555557f, 0.06666667f);
        else
            StepValueTowardTarget((u8 *)vars + 0x24, (u8 *)vars + 0x28, 1.0f, 0.00055555557f, 0.00055555557f, 0.06666667f);
        if (*(f32 *)((u8 *)vars + 0x28) != 0.0f) {
            *(TI128 *)vec = 0;
            vec[0] = 1.0f;
            vec[2] = 3.0f;
            matrix_mul_vec3(vec, vec, self + 0xC0);
            FastVecScale(*(f32 *)((u8 *)vars + 0x24), vec, vec);
            FastVecAdd(self + 0x10, (u8 *)vars + 0x10, vec);
            if (vars[0xC] % 120 == 0)
                PlayMobySound(0, 0, (s32)self);
            vars[0xC]++;
        } else {
            vars[0xC] = 0;
        }
        break;
    }
}
