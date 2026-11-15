#include "include_asm.h"

#include "common.h"
extern float FastAddRotations(float f12, float f13);
extern float math_fast_sin_or_cos_b(float f12);
extern int FastTweenColor(int a0, int a1, float f12);
extern float math_random_float_range(float f12, float f13);
extern void moby_set_light_color(void *a0, int a1);
extern float FastAddRotations(float, float);
extern float math_random_float_range(float low, float high);

void func_PAL_L01_00322798(void *a0, float *a1, int a2) {
    unsigned char *p = (unsigned char *)a0;
    float r;
    int i;

    if (p[0x23] == 0 && a2 == 0)
        return;

    r = FastAddRotations(*a1, 0.17453296f);
    *a1 = r;
    r = math_fast_sin_or_cos_b(r);
    i = FastTweenColor(0x8000C020, 0x80008000, (r + 0.5f) * 0.5f);
    if (math_random_float_range(0.0f, 1.0f) < 0.05f)
        i = FastTweenColor(i, 0x8080FFFF, 0.3f);
    moby_set_light_color(a0, i);

    if (a2 != 0) {
        if (p[0x23] < 0x3D)
            p[0x23] = p[0x23] + 3;
        else
            p[0x23] = 0x40;
    } else {
        if (p[0x23] >= 4)
            p[0x23] = p[0x23] - 3;
        else
            p[0x23] = 0;
    }
}

