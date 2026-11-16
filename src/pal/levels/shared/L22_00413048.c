#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef float f32;
extern u8 D_001A63A8_4[];
extern u8 g_hero_state[];
extern f32 fast_vec_dist(void *a0, void *a1);
extern f32 math_random_float_range(f32 low, f32 high);
extern char *SpawnExplosion(void *a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7,
                          int a8, int a9, int a10, int a11, f32 f12, f32 f13);

void part_start_random_scale_effect_pal(u8 *a0) {
    f32 f = math_random_float_range(0.8f, 1.2f);
    SpawnExplosion(a0, 0, 5, 4, 4, 4, 4, 0, 0, 0, 0, 0, f, 20.0f);
}

