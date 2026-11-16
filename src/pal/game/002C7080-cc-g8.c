#include "names.h"
/* func_PAL_002C7080, the PAL copy of func_002C6360: the same C, where rename func_002BFB38 becomes func_PAL_002C0838; wrap D_L00_001AA704 + f0 (({e}) * 1.44f); rename func_00282CC0_17 becomes func_00282CC0. */
extern int FastDecTimer(short *);
extern void FastVecAdd(char *, char *, char *);
extern void part_kill(void *);
extern float g_spark_random_range __attribute__((sda));
extern float g_spark_pull_base __attribute__((sda));
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern float IntToFloat(int);
extern void *part_spawn_drifting(char *, int, int, float, float);
extern void *part_spawn_spark_2_pal(char *, char *, int, int);

#ifndef RAC2_T_V4_G8
#define RAC2_T_V4_G8
typedef int V4_G8 __attribute__((mode(TI)));
#endif

extern int math_random_int_below(int);
extern float math_random_float_range(float, float);
/* Advances one object: the two motion floats grow and are stored back, the
   object's vector is copied out and its fourth word cleared, the colour and
   the counter byte are rebuilt, and the object is finally handed to the
   helper twice when the motion is below the limit. */
void part_update_spark_emitting_pal(char *self)
{
    char *part = self;
    char *state = self + 0x20;
    char *position = self + 0x10;
    V4_G8 velocity;
    float temp;
    float pull;
    float new_fall;
    float new_growth;

    temp = math_random_float_range(-g_spark_random_range, g_spark_random_range);
    pull = ((g_spark_pull_base + temp) * 1.44f);
    new_growth = *(float *)(state + 0x10) + 0.0075f;
    new_fall = *(float *)(state + 8) - pull;
    temp = *(float *)(state + 0x14) * new_growth * 210000.0f;
    *(float *)(state + 0x10) = new_growth;
    *(float *)(state + 8) = new_fall;
    velocity = *(V4_G8 *)(part + 0x20);
    *(float *)(part + 0xC) = temp;
    ((int *)&velocity)[3] = 0;
    IntToFloat(*(short *)(part + 0xA));
    *(unsigned int *)(part + 4) = 0x55503020;
    *(unsigned char *)(part + 8) = *(unsigned char *)(part + 8) + *(unsigned char *)(state + 0x1A);
    FastVecAdd(position, position, (char *)&velocity);
    if (*(float *)(part + 0x18) <= *(float *)(state + 0x1C)) {
        if (math_random_int_below(6) == 1)
            part_spawn_drifting(position, 0, -1, 0.4f, 210000.0f * 0.15f);
    }
    if (math_random_int_below(6) == 1) {
        if (*(short *)(state + 0x18) >= 0x32)
            part_spawn_spark_2_pal(part + 0x10, (char *)&velocity, 1, 0x11);
    }
    *(unsigned short *)(state + 0x18) = *(unsigned short *)(state + 0x18) + 1;
    if (FastDecTimer((short *)(part + 0xA)) != 0)
        part_kill(part);
}
