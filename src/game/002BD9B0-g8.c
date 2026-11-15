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

/* Moves a spark particle and fades its size and colour over its life. It also drops smaller sparks behind it and disappears when its time is up. */
void part_update_trailing_spark(char *particle)
{
    char *motion = particle + 0x20;
    float invLife;
    float speed;
    float savedPos[4] __attribute__((aligned(16)));
    float sparkVel[4] __attribute__((aligned(16)));
    float randomVec[4] __attribute__((aligned(16)));

    if (FastDecTimer((short *)(particle + 0xA))) {
        part_kill(particle);
        return;
    }
    invLife = 1.0f / IntToFloat(*(short *)(motion + 0x18));
    *(float *)(particle + 0xC) = IntToFloat(*(short *)(particle + 0xA)) * *(float *)(motion + 0x1C) * invLife;
    *(int *)(particle + 4) = moby_forward_two_values_and_amount(*(int *)(motion + 0x14), *(int *)(motion + 0x10), IntToFloat(*(short *)(particle + 0xA)) * invLife);
    FastVecAdd((particle + 0x10), (particle + 0x10), motion);
    *(float *)(motion + 8) -= 0.001f;
    qcopy(savedPos, particle + 0x10);
    if (*(short *)(motion + 0x1A) != 0 && (g_game_time & 1)) {
        *(TI *)randomVec = 0;
        randomVec[0] = math_random_float_range(-1.0f, 1.0f);
        randomVec[1] = math_random_float_range(-1.0f, 1.0f);
        randomVec[2] = math_random_float_range(-1.0f, 1.0f);
        *(TI *)sparkVel = *(TI *)randomVec;
        speed = FastVecLength(motion);
        vec_scale_to_length(sparkVel, sparkVel, speed * math_random_float_range(0.21f, 0.25f));
        FastVecAdd(sparkVel, sparkVel, motion);
        FastVecScale(sparkVel, sparkVel, math_random_float_range(0.75f, 0.95f));
        part_spawn_trailing_spark((particle + 0x10), sparkVel, *(int *)(particle + 4), *(int *)(motion + 0x14), math_random_int_range(15, 20), 0, *(float *)(particle + 0xC));
    } else {
        FastVecScale(motion, motion, 0.96f);
    }
}
