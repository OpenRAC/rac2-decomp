#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef signed int s32;

typedef int TI128 __attribute__((mode(TI)));

/* The effect's tuning, four resident tables copied onto the stack: the spread and fall speed of
   the sparks, the two sizes, the two colours and the two byte ranges of the kind. */
typedef struct { float f[4]; } SparkRange;
typedef struct { float f[2]; } SparkSizes;
typedef struct { int i[2]; } SparkColours;
typedef struct { u8 b[4]; } SparkKinds;
extern SparkRange g_spark_l02_range_2;
extern SparkSizes g_spark_sizes;
extern SparkColours g_spark_colours;
extern SparkKinds g_spark_kinds;
extern void vec_clear_128(void *);
extern void FastVecAdd(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern void vec_random_direction(void *, float, float);
extern void *part_spawn_hero_relative(void *, void *, int, int, int, int, float);

/* func_PAL_L02_00417490, the PAL copy of func_L02_00412808: the same C, where the per-frame
   0.016666668f becomes 0.020000001f and the spark kind is scaled to 50 Hz. */
void part_throw_front_sparks_pal(u8 *moby) {
    SparkRange range = g_spark_l02_range_2;
    SparkSizes sizes = g_spark_sizes;
    SparkColours colours = g_spark_colours;
    SparkKinds kinds = g_spark_kinds;
    float velocity[4];
    float front[4];
    float spot[4];

    *(TI128 *)front = 0;
    front[2] = 1.5f;
    matrix_mul_vec3(front, front, moby + 0xC0);
    FastVecAdd(front, front, moby + 0x10);
    vec_random_direction(velocity, range.f[0] * 0.020000001f, range.f[1] * 0.020000001f);
    part_spawn_hero_relative(front, velocity, colours.i[0],
                  (u8)(((s32)math_random_int_range(kinds.b[0], kinds.b[1]) * 5 + 2) / 6),
                  (u8)math_random_int_below(0xFF), 0, sizes.f[0]);
    vec_clear_128(velocity);
    vec_random_direction(spot, 0.0f, 1.5f);
    FastVecAdd(spot, spot, front);
    velocity[2] = -(math_random_float_range(range.f[2], range.f[3]) * 0.020000001f);
    part_spawn_hero_relative(spot, velocity, colours.i[1],
                  (u8)(((s32)math_random_int_range(kinds.b[2], kinds.b[3]) * 5 + 2) / 6),
                  (u8)math_random_int_below(0xFF), 0, sizes.f[1]);
}



