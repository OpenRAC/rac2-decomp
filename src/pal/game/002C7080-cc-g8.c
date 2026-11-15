#include "names.h"
/* func_PAL_002C7080, the PAL copy of func_002C6360: the same C, where rename func_002BFB38 becomes func_PAL_002C0838; wrap D_L00_001AA704 + f0 (({e}) * 1.44f); rename func_00282CC0_17 becomes func_00282CC0. */
extern int FastDecTimer(short *);
extern void FastVecAdd(char *, char *, char *);
extern void part_kill(void *);
extern float D_L00_001AA708 __attribute__((sda));
extern float D_L00_001AA704 __attribute__((sda));
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern float IntToFloat(int);
extern void *part_spawn_drifting(char *, int, int, float, float);
extern void *func_PAL_002C0838(char *, char *, int, int);

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
void func_PAL_002C7080(char *self)
{
    char *s0 = self;
    char *s1 = self + 0x20;
    char *s2 = self + 0x10;
    V4_G8 buf;
    float f0;
    float f1;
    float f2;
    float f3;

    f0 = math_random_float_range(-D_L00_001AA708, D_L00_001AA708);
    f1 = ((D_L00_001AA704 + f0) * 1.44f);
    f3 = *(float *)(s1 + 0x10) + 0.0075f;
    f2 = *(float *)(s1 + 8) - f1;
    f0 = *(float *)(s1 + 0x14) * f3 * 210000.0f;
    *(float *)(s1 + 0x10) = f3;
    *(float *)(s1 + 8) = f2;
    buf = *(V4_G8 *)(s0 + 0x20);
    *(float *)(s0 + 0xC) = f0;
    ((int *)&buf)[3] = 0;
    IntToFloat(*(short *)(s0 + 0xA));
    *(unsigned int *)(s0 + 4) = 0x55503020;
    *(unsigned char *)(s0 + 8) = *(unsigned char *)(s0 + 8) + *(unsigned char *)(s1 + 0x1A);
    FastVecAdd(s2, s2, (char *)&buf);
    if (*(float *)(s0 + 0x18) <= *(float *)(s1 + 0x1C)) {
        if (math_random_int_below(6) == 1)
            part_spawn_drifting(s2, 0, -1, 0.4f, 210000.0f * 0.15f);
    }
    if (math_random_int_below(6) == 1) {
        if (*(short *)(s1 + 0x18) >= 0x32)
            func_PAL_002C0838(s0 + 0x10, (char *)&buf, 1, 0x11);
    }
    *(unsigned short *)(s1 + 0x18) = *(unsigned short *)(s1 + 0x18) + 1;
    if (FastDecTimer((short *)(s0 + 0xA)) != 0)
        part_kill(s0);
}
