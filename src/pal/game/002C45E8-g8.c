#include "include_asm.h"
#include "names.h"

extern int FastDecTimer(short *);
extern void FastVecAdd(char *, char *, char *);
extern void part_kill(void *);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern int g_bounce_split_chance __attribute__((sda));
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern void *func_PAL_002BD790(char *, char *, int, int, int, int, int, int, int, float);

void func_PAL_002C45E8(char *self)
{
    char *motion = self + 0x20;
    char *position;
    int ttl;
    if (FastDecTimer((short *)(self + 0xA)))
        *(float *)(motion + 8) -= *(float *)(motion + 0x14);
    position = self + 0x10;
    FastVecAdd(position, position, motion);
    *(unsigned char *)(self + 8) += 2;
    if (*(float *)(self + 0x18) < *(float *)(motion + 0x10)) {
        if (math_random_int_below(g_bounce_split_chance - 1) == 0) {
            *(float *)(self + 0x18) = *(float *)(motion + 0x10);
            *(float *)(self + 0x20) *= math_random_float_range(1.0f, 3.5f);
            *(float *)(motion + 4) *= math_random_float_range(1.0f, 3.5f);
            *(float *)(motion + 8) *= math_random_float_range(-1.0f, -1.5f);
            ttl = math_random_int_range(50, 100);
            func_PAL_002BD790(position, motion, *(int *)(self + 4), *(int *)(motion + 0x18),
                ttl, 0, *(unsigned char *)(self + 2), *(unsigned char *)(self + 3), 0,
                *(float *)(self + 0xC) * 0.5f);
        } else {
            *(float *)(self + 0x18) = *(float *)(motion + 0x10);
            *(float *)(self + 0x20) += math_random_float_range(-5.0f, 5.0f) * 0.020000001f;
            *(float *)(motion + 4) += math_random_float_range(-5.0f, 5.0f) * 0.020000001f;
            *(float *)(motion + 8) *= math_random_float_range(-0.5f, -1.0f);
            ttl = math_random_int_range(25, 50);
            func_PAL_002BD790(position, motion, *(int *)(self + 4), *(int *)(motion + 0x18),
                ttl, 0, *(unsigned char *)(self + 2), *(unsigned char *)(self + 3), 0,
                *(float *)(self + 0xC) * 0.25f);
        }
        part_kill(self);
    }
}
