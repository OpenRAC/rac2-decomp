#include "include_asm.h"
#include "names.h"
typedef unsigned int u32;
typedef int s32;
typedef int TI128 __attribute__((mode(TI)));

extern char g_spark_burst_vectors[8] __attribute__((sda));
extern float g_spark_burst_speed_min __attribute__((sda));
extern float g_spark_burst_speed_max;
extern u32 g_spark_burst_a_word0 __attribute__((sda));
extern u32 g_spark_burst_a_word1;
extern u32 g_spark_burst_b_word0;
extern u32 g_spark_burst_b_word1;
extern u32 g_spark_burst_c_word0;
extern u32 g_spark_burst_c_word1;
extern u32 g_spark_burst_a_color __attribute__((sda));
extern u32 g_spark_burst_b_color;
extern u32 g_spark_burst_c_color;
extern s32 g_frame_l02_counter;

extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float math_random_float_range(float, float);
extern s32 math_random_int_range(s32, s32);
extern char *part_spawn_scaling(void *, void *, u32, s32, s32, s32, s32, s32);

/* func_PAL_L02_00406698, the PAL copy of func_L02_00401D38: the same C, where 1/60 becomes 1/50
   and the three picks of func_002A7820 are scaled to 50 Hz. Retail shows no interblock motion in
   this loop: i and p step in its last block, so this unit builds with -fno-sched-interblock and
   p steps at the end of the body. */
void func_PAL_L02_00406698(char *a0, char *a1) {
    float v0[4];
    float v1[4];
    float v2[4];
    float *w = v1;
    char *p = g_spark_burst_vectors;
    s32 i;
    float f;

    for (i = 1; i >= 0; i--) {
        matrix_mul_vec3(v0, p, a0 + 0xC0);
        FastVecAdd(v0, v0, a0 + 0x10);
        *(TI128 *)v2 = 0;
        f = math_random_float_range(g_spark_burst_speed_min, g_spark_burst_speed_max);
        v2[2] = -(f * 0.020000001f);
        *(TI128 *)v1 = *(TI128 *)v2;
        FastVecAdd(v1, v1, a1);
        if (g_frame_l02_counter & 1) {
            part_spawn_scaling(v0, w, g_spark_burst_a_word0, g_spark_burst_a_word1, ((s32)math_random_int_range(0x12, 0x16) * 5 + 2) / 6, g_spark_burst_a_color, -10, 1);
        } else {
            part_spawn_scaling(v0, w, g_spark_burst_b_word0, g_spark_burst_b_word1, ((s32)math_random_int_range(0x14, 0x18) * 5 + 2) / 6, g_spark_burst_b_color, -10, 1);
        }
        part_spawn_scaling(v0, w, g_spark_burst_c_word0, g_spark_burst_c_word1, ((s32)math_random_int_range(0xA, 0xF) * 5 + 2) / 6, g_spark_burst_c_color, -10, 1);
        p += 0x10;
    }
}
