#include "include_asm.h"

#include "common.h"
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
typedef struct {
    s32 lo;
    s32 hi;
} L02Range_C4ED8;
typedef struct {
    f32 a;
    f32 b;
} L02Pair_C4ED8;
extern L02Range_C4ED8 g_spark_l02_range NOT_SDA;
extern L02Pair_C4ED8 g_spark_speed_pair NOT_SDA;
extern f32 g_spark_origin_vector[] SDATA(D_L02_001AFE60);
extern f32 D_L02_001AFE70_gp[] SDATA(D_L02_001AFE70);
extern f32 g_spark_dir_a[] __attribute__((sda));
extern f32 g_spark_dir_b[] __attribute__((sda));
extern int math_fast_float_d(void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void part_spawn_spark_burst_line_pal(void *, void *, void *, int, int, int, int, float);
extern int math_random_int_range(int, int);
extern int snd_play_from_class_bank(int, int, char *, int);

/* Every so often fires two sparks from the object and plays a sound. */
void spark_emitter_update_pal(u8 *self)
{
    L02Range_C4ED8 range = g_spark_l02_range;
    L02Pair_C4ED8 speed = g_spark_speed_pair;
    f32 origin[4] __attribute__((aligned(16)));
    f32 dir0[4] __attribute__((aligned(16)));
    f32 dir1[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(self + 0x68);

    if (math_fast_float_d(state + 0x124) == 0)
        return;
    if (*(s32 *)(state + 0x18) != 0) {
        qcopy(origin, self + 0x10);
    } else {
        matrix_mul_vec3(origin, g_spark_origin_vector, self + 0xC0);
        FastVecAdd(origin, origin, self + 0x10);
    }
    matrix_mul_vec3(dir0, D_L02_001AFE70_gp, self + 0xC0);
    vec_scale_to_length(dir0, dir0, speed.a * 0.020000001f);
    matrix_mul_vec3(dir1, g_spark_dir_b, self + 0xC0);
    vec_scale_to_length(dir1, dir1, speed.b * 0.020000001f);
    g_spark_dir_a[1] = -g_spark_dir_a[1];
    g_spark_dir_b[1] = -g_spark_dir_b[1];
    part_spawn_spark_burst_line_pal(origin, dir0, dir1, 12, 0, 0, 0, 15.0f);
    *(s32 *)(state + 0x124) = ((s32)(math_random_int_range(range.lo, range.hi)) * 5 + 2) / 6;
    snd_play_from_class_bank(4, 0, (char *)self, 0x896);
}
