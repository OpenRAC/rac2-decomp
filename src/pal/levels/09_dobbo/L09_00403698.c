#include "include_asm.h"

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union EffectVector { Quadword bits; float value[4]; } EffectVector;
extern float IntToFloat(int a0);
extern int math_fast_helper_a(float *a0, float f12);
extern float math_random_float_range(float lo, float hi);
extern void moby_transform_joint_to_world(char *a0, int a1, float *a2);
extern char *part_spawn_scaling(float *a0, float *a1, int a2, int a3, int t0, int t1, int t2, int t3);
extern int FloatToInt(float a);

/* func_L09_003FEA48 is defined in L09_003FEA48-g8.c (this unit has no $gp access for it). */

/* func_L09_003FEAE8 is defined in L09_003FEAE8-g8.c. */

void func_PAL_L09_00403900(char *a0) {
    EffectVector a;
    EffectVector b;
    EffectVector c;
    EffectVector w;
    int i;
    int j;
    char *p;

    qcopy(a.value, a0 + 0x10);
    a.value[3] = 6.0f;
    if (math_fast_helper_a(a.value, IntToFloat(*(s16 *)(a0 + 0x32))) == -1)
        return;
    for (i = 12; i < 14; i++) {
        w.bits = 0;
        w.value[2] = -(math_random_float_range(3.5f, 4.5f) * 0.020000001f);
        c.bits = w.bits;
        for (j = 0; j < 2; j++) {
            moby_transform_joint_to_world(a0, i, b.value);
            b.value[2] += IntToFloat(j) * 0.015f + 0.5f;
            if (j & 1)
                p = part_spawn_scaling(b.value, c.value, 0x77FF0000, 0x00FF0060, 0x10, 200, -100, 1);
            else
                p = part_spawn_scaling(b.value, c.value, 0x77FF0060, 0x00FF0000, 0x11, 300, -100, 1);
            if (p)
                p[9] = ((*(s16 *)(a0 + 0x32) >> 5) << 4) + FloatToInt(0.0f);
            p = part_spawn_scaling(b.value, c.value, 0x77FFFFFF, 0x00FF0000, 0xA, 100, -100, 1);
            if (p)
                p[9] = ((*(s16 *)(a0 + 0x32) >> 5) << 4) + FloatToInt(0.0f);
        }
    }
}



