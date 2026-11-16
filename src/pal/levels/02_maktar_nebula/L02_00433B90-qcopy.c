#include "include_asm.h"
#include "names.h"

/* func_PAL_L02_00433B90, the PAL copy of func_L02_0042E680: the same C, where each count runs through
   the 50 Hz scale (x * 5 + 2) / 6 and k becomes 0.0036000002f. A unit of its own for the template's
   opt-in quadword-copy profile and scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier,
   config/cflags.txt). */

typedef unsigned char u8;
typedef int TI128 __attribute__((mode(TI)));

extern void vec_clear_128(void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float math_random_float_range(float, float);
extern int FloatToInt(float);
extern int FastTweenColor(int, int, float);
extern void *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);
extern void vec_add_random_offset(void *, float);
extern int g_spark_fan_colors_a[2] __attribute__((sda));
extern int g_spark_fan_colors_b[2] __attribute__((sda));

void func_PAL_L02_00433B90(u8 *a0, float lo, float hi) {
    float v10[4];
    float v20[4];
    float v30[4];
    float v40[4];
    float v50[4];
    float v60[4];
    float v70[4];
    int i;
    float r;
    int a, b, c;
    int c0, c1;
    float k = 0.0036000002f;

    v10[0] = 0.0f;
    v10[1] = 0.0f;
    v10[2] = 4.0f;
    v10[3] = 1.0f;
    FastVecAdd(v20, v10, a0 + 0x10);
    i = 29;
    do {
        vec_scale_to_length(v40, a0 + 0xC0, math_random_float_range(-0.8f, 0.8f));
        vec_scale_to_length(v30, a0 + 0xE0, math_random_float_range(0.25f, 1.0f));
        FastVecAdd(v50, a0 + 0xD0, v40);
        FastVecAdd(v50, v50, v30);
        vec_scale_to_length(v50, v50, math_random_float_range(lo, hi));
        r = math_random_float_range(0.5f, 1.5f);
        a = FloatToInt((r * 50.0f + 2.0f) * 0.16666667f);
        b = FloatToInt((r * 150.0f + 2.0f) * 0.16666667f);
        c = FloatToInt((r * 35.0f + 2.0f) * 0.16666667f);
        v50[3] = math_random_float_range(0.2f, 0.6f);
        vec_clear_128(v60);
        v60[2] = -k * (float)(a + b + c);
        FastVecAdd(v60, v60, v50);
        v60[3] = 0.01f;
        c0 = FastTweenColor(g_spark_fan_colors_a[0], g_spark_fan_colors_a[1], math_random_float_range(0.0f, 1.0f));
        c1 = FastTweenColor(g_spark_fan_colors_b[0], g_spark_fan_colors_b[1], math_random_float_range(0.0f, 1.0f));
        *(TI128 *)v70 = *(TI128 *)v20;
        vec_add_random_offset(v70, 0.25f);
        part_spawn_trail(v70, v50, v60, c0, c1, a, b, c, 0x1003C);
    } while (--i >= 0);
}
