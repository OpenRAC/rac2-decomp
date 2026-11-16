#include "include_asm.h"

#include "common.h"
typedef int TI __attribute__((mode(TI)));
extern int FastDecTimer(short *p);
extern void part_kill(void *p);
extern float IntToFloat(int n);
extern int moby_forward_two_values_and_amount(int a, int b, float f);
extern void FastVecAdd(void *out, void *a, void *b);
extern float math_random_float_range(float lo, float hi);
extern int math_random_int_range(int lo, int hi);
extern float FastVecLength(void *v);
extern void vec_scale_to_length(void *dst, void *src, float len);
extern void FastVecScale(void *dst, void *src, float scale);
extern void *part_spawn_trailing_spark(void *a0, void *a1, int a2, int a3, int a4, int a5, float f);
extern int g_game_time __attribute__((sda));

/* Updates a trailing spark: it falls, changes colour, and now and then leaves a short-lived spark behind it (PAL: 50 Hz timings). */
void part_update_trailing_spark_pal(char *p)
{
    char *s = p + 0x20;
    float inv;
    float len;
    float keep[4] __attribute__((aligned(16)));
    float v[4] __attribute__((aligned(16)));
    float w[4] __attribute__((aligned(16)));

    if (FastDecTimer((short *)(p + 0xA))) {
        part_kill(p);
        return;
    }
    inv = 1.0f / IntToFloat(*(short *)(s + 0x18));
    *(float *)(p + 0xC) = IntToFloat(*(short *)(p + 0xA)) * *(float *)(s + 0x1C) * inv;
    *(int *)(p + 4) = moby_forward_two_values_and_amount(*(int *)(s + 0x14), *(int *)(s + 0x10), IntToFloat(*(short *)(p + 0xA)) * inv);
    FastVecAdd((p + 0x10), (p + 0x10), s);
    *(float *)(s + 8) -= 0.0014400001f;
    qcopy(keep, p + 0x10);
    if (*(short *)(s + 0x1A) != 0 && (g_game_time & 1)) {
        *(TI *)w = 0;
        w[0] = math_random_float_range(-1.0f, 1.0f);
        w[1] = math_random_float_range(-1.0f, 1.0f);
        w[2] = math_random_float_range(-1.0f, 1.0f);
        *(TI *)v = *(TI *)w;
        len = FastVecLength(s);
        vec_scale_to_length(v, v, len * math_random_float_range(0.21f, 0.25f));
        FastVecAdd(v, v, s);
        FastVecScale(v, v, math_random_float_range(0.75f, 0.95f));
        part_spawn_trailing_spark((p + 0x10), v, *(int *)(p + 4), *(int *)(s + 0x14), ((s32)(math_random_int_range(15, 20)) * 5 + 2) / 6, 0, *(float *)(p + 0xC));
    } else {
        FastVecScale(s, s, 0.96f);
    }
}
