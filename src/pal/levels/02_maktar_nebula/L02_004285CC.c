#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

extern void vec_clear_128(void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern int FloatToInt(float);
extern int FastTweenColor(int, int, float);
extern float math_random_float_range(float, float);
extern void *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);
extern int D_L02_001B2050[2] __attribute__((sda));
extern int D_L02_001B2058[2] __attribute__((sda));

/* func_PAL_L02_004288E8, the PAL copy of func_L02_00423838: the same C, where the three frame counts are
   scaled to 50 Hz and the downward pull per frame becomes 0.002f. */
void func_PAL_L02_004288E8(u8 *a0, float lo, float hi) {
    float v10[4];
    float v20[4];
    float v30[4];
    float v40[4];
    float v50[4];
    float v60[4];
    int i;
    float r;
    int a, b, c;
    int c0, c1;
    float k = 0.002f;

    FastVecScale(v10, a0 + 0xE0, 1.75f);
    FastVecAdd(v20, v10, a0 + 0x10);
    FastVecScale(v10, a0 + 0xC0, -0.5f);
    FastVecAdd(v20, v10, v20);
    i = 19;
    do {
        vec_scale_to_length(v40, a0 + 0xD0, math_random_float_range(-1.0f, 1.0f));
        vec_scale_to_length(v30, a0 + 0xE0, math_random_float_range(-0.15f, 1.0f));
        FastVecAdd(v50, a0 + 0xC0, v40);
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
        c0 = FastTweenColor(D_L02_001B2050[0], D_L02_001B2050[1], math_random_float_range(0.0f, 1.0f));
        c1 = FastTweenColor(D_L02_001B2058[0], D_L02_001B2058[1], math_random_float_range(0.0f, 1.0f));
        part_spawn_trail(v20, v50, v60, c0, c1, a, b, c, 0x1003C);
    } while (--i >= 0);
}
