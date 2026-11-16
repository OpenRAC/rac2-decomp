#include "names.h"
/* func_PAL_L14_0042C988, the PAL copy of func_L14_004272D8: the same C, where the particle count
   n gets the 50 Hz scale. Built with -g: the line label before the div.s gives retail's two nops. */
#include "include_asm.h"
#include "common.h"

extern f32 g_spark_side_float_params[2] __attribute__((sda));
extern s32 g_spark_side_color_params[2] __attribute__((sda));
extern s32 g_spark_side_count_ranges[4] __attribute__((sda));
extern f32 g_spark_spawn_chance __attribute__((sda));
extern f32 g_spark_side_offsets[2][4] __attribute__((sda));

extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern float IntToFloat(int);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern void *part_spawn_hero_relative(void *, void *, int, int, int, int, float);

/* Spawns a burst of sparks from a random side of the object (PAL: particle count scaled for
 * 50 Hz). */
void part_spawn_spark_side_pal(u8 *moby) {
    f32 pos[4] __attribute__((aligned(16)));
    f32 step[4] __attribute__((aligned(16)));
    s32 side;
    s32 kind;
    s32 count;

    side = math_random_int_below(2);
    kind = 1;
    if (!(math_random_float_range(0.0f, 1.0f) < g_spark_spawn_chance)) {
        kind = 0;
    }
    count = (math_random_int_range(g_spark_side_count_ranges[kind * 2], g_spark_side_count_ranges[kind * 2 + 1]) * 5 + 2) / 6;
    matrix_mul_vec3(pos, g_spark_side_offsets[side], moby + 0xC0);
    FastVecAdd(pos, pos, moby + 0x10);
    FastVecSub(step, g_spark_side_offsets[(side + 1) & 1], g_spark_side_offsets[side]);
    matrix_mul_vec3(step, step, moby + 0xC0);
    FastVecScale(step, step, 1.0f / IntToFloat(count));
    {
        s32 *cp = &g_spark_side_color_params[kind];
        f32 *fp = &g_spark_side_float_params[kind];
        part_spawn_hero_relative(pos, step, *cp, count & 0xFF, math_random_int_below(0xFF) & 0xFF, 0, *fp);
    }
}
