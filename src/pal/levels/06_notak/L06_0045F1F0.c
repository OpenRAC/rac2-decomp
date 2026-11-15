#include "include_asm.h"

#include "common.h"
extern float math_step_value_toward_target(char *, char *, float, float, float, float);
extern int math_blend_scaled_count(char *, char *, int, int, float, float);
extern void FastVecScale(char *, char *, float);

void func_PAL_L06_0045F1F0(char *a0, char *a1, float f, float g, float h)
{
    char buf[16];
    char *q = a1;

    if (*(float *)(*(char **)(a1 + 0x11C)) - 0.3f < *(float *)(a0 + 0x18)) {
        *(float *)(a1 + 0xC8) -= 0.19600002f;
    }
    qcopy(buf, a0 + 0x10);
    math_step_value_toward_target(buf + 8, q + 0xC8, *(float *)(q + 0x128), f, g, h);
    if (math_blend_scaled_count(a0, q + 0xC0, 0x400, 0x10, 1.0f, 0.0f) != 0) {
        FastVecScale(q + 0xC0, q + 0xC0, 0.5f);
    }
}

