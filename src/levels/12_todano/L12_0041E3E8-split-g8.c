#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern u8 *D_L12_001B2E9C MACRO_ADDR;
extern void moby_set_state(void *, int, int);
extern s32 PlayMobySound(s32, s32, s32);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern int IsPointInCuboid(void *, int);

extern char g_hero_position[];
extern char D_L12_001B9E00[];
extern float vec_distance_xy(void *, void *);
extern int math_fast_float_d(void *);
extern float math_step_value_toward_target(void *, void *, float, float, float, float);
extern void FastVecScale(float, void *, void *);

/* Slides the door open while the hero or buddy is near its switch, and closes it again a moment after they leave. */
void secret_door_update(u8 *self)
{
    s32 *vars = *(s32 **)(self + 0x68);
    int state = self[0x20];
    f32 vec[4];

    switch (state) {
    case 0:
        qcopy((u8 *)vars + 0x10, self + 0x10);
        moby_set_state(self, 1, -1);
        self[0x30] = 0x7F;
        break;
    case 1:
        if (vec_distance_xy(self + 0x10, D_L12_001B2E9C + (vars[0] << 8) + 0x10) < 5.0f) {
            vars[0xB] = state;
            vars[8] = 0x3C;
        } else if ((IsPointInCuboid(g_hero_position, vars[1]) && vars[0xB] != 0) ||
                   (IsPointInCuboid(D_L12_001B9E00, vars[1]) && vars[0xB] != 0)) {
            vars[8] = 0x3C;
        }
        if (math_fast_float_d((u8 *)vars + 0x20))
            math_step_value_toward_target((u8 *)vars + 0x24, (u8 *)vars + 0x28, 0.0f, 0.00055555557f, 0.00055555557f, 0.06666667f);
        else
            math_step_value_toward_target((u8 *)vars + 0x24, (u8 *)vars + 0x28, 1.0f, 0.00055555557f, 0.00055555557f, 0.06666667f);
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
