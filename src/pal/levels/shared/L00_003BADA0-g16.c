#include "include_asm.h"
#include "names.h"

/* func_PAL_L00_003BADA0, the PAL copy of func_L00_003B72B0: the same C, where 1.0f / 60.0f becomes 0.020000001f and both
   func_002A7820 results are scaled to 50 Hz. The loop's result has a local of its own, so it stays in one block. */

extern int math_random_int_range(int, int);
extern int math_random_int_below(int);
extern void vec_random_direction(float *, float, float);
extern void FastVecAdd(float *, float *, float *);
extern void matrix_mul_vec3(float *, float *, void *);
extern void *part_spawn_hero_relative(void *, void *, int, int, int, int, float);
extern float D_L00_001AFAE8 __attribute__((sda));
extern float D_L00_001AFAEC;
extern float D_L00_001AFAF8 __attribute__((sda));
extern float D_L00_001AFAFC;
extern int D_L00_001AFB00 __attribute__((sda));
extern int D_L00_001AFB04;
extern int D_L00_001AFB08 __attribute__((sda));
extern int D_L00_001AFB0C[] __attribute__((sda));
extern int D_L00_001AFB18 __attribute__((sda));
extern float D_L00_001AFB20[4] __attribute__((sda));
extern char g_camera_l00_position[];
extern float D_L00_001A8F20[4];

void func_PAL_L00_003BADA0(void)
{
    float point[4], velocity[4], scatter[4];
    int i = 0;
    unsigned char kind, kind2, random;
    matrix_mul_vec3(point, D_L00_001AFB20, g_camera_l00_position + 0x230);
    FastVecAdd(point, point, (float *)g_camera_l00_position);
    kind = ((int)math_random_int_range(D_L00_001AFB08, D_L00_001AFB0C[0]) * 5 + 2) / 6;
    random = math_random_int_below(255);
    part_spawn_hero_relative(point, D_L00_001A8F20, D_L00_001AFB00, kind, random, 0, D_L00_001AFAF8);
    vec_random_direction(velocity, D_L00_001AFAE8 * 0.020000001f, D_L00_001AFAEC * 0.020000001f);
    while (i < D_L00_001AFB18) {
        i++;
        vec_random_direction(scatter, 0.0f, 0.25f);
        FastVecAdd(scatter, scatter, point);
        kind2 = ((int)math_random_int_range(D_L00_001AFB0C[1], D_L00_001AFB0C[2]) * 5 + 2) / 6;
        random = math_random_int_below(255);
        part_spawn_hero_relative(scatter, velocity, D_L00_001AFB04, kind2, random, 0, D_L00_001AFAFC);
    }
}
