#include "include_asm.h"
#include "common.h"

/* func_PAL_L00_003EEF94, the PAL copy of func_L00_003EACC0: the same C, where the frame counts
 * scale to 50 Hz (20 becomes 17, 300 becomes 250, and both func_002A7820 draws take
 * ((s32)(x) * 5 + 2) / 6) and the speed 0.41666669f becomes 0.50000006f. */

extern int math_fast_float_d(int *);
extern int math_random_int_range(int, int);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float math_random_signed_float_range(float, float);
extern float math_random_float_range(float, float);
extern int FloatToInt(float);
/* EE integer and floating-point argument banks retain their independent order. */
extern void aranos_spark_spawn(void *, void *, int, float, int, int);

void func_PAL_L00_003EEF94(unsigned char *p) {
    float v[4], pos[4];
    float radius, secondRadius, z;
    int *s = *(int **)(p + 0x68);
    unsigned char *base;

    if (p[0x20] == 0) {
        p[0x30] = 0x80;
        p[0x20] = 1;
        s[1] = 17;
        s[0] = 0;
    }
    if (p[0x20] == 1) {
        if (math_fast_float_d(s)) {
            p[0x20] = 2;
            s[0] = ((s32)math_random_int_range(50, 120) * 5 + 2) / 6;
        }
    }
    if (p[0x20] == 2) {
        if (math_fast_float_d(s + 1)) {
            p[0x20] = 1;
            s[1] = ((s32)math_random_int_range(10, 25) * 5 + 2) / 6;
        } else {
            v[0] = math_fast_sin_or_cos_a(*(float *)(p + 0xf8) - 1.570796489715576171875f)
                   * 0.50000006f;
            v[1] = math_fast_sin_or_cos_b(*(float *)(p + 0xf8) - 1.570796489715576171875f)
                   * 0.50000006f;
            v[2] = 0.0f;
            base = p + 0x10;
            qcopy(pos, base);
            z = v[2];
            pos[2] += math_random_signed_float_range(z, 0.5f);
            radius = math_random_float_range(0.1f, 3.0f);
            aranos_spark_spawn(pos, v, 250, radius,
                             FloatToInt(math_random_signed_float_range(1.0f, 4.0f)), 0x40808080);
            qcopy(pos, base);
            pos[2] += math_random_signed_float_range(z, 0.5f);
            secondRadius = math_random_float_range(0.1f, 3.0f);
            aranos_spark_spawn(pos, v, 250, secondRadius,
                             FloatToInt(math_random_signed_float_range(1.0f, 4.0f)), 0x40808080);
        }
    }
}
