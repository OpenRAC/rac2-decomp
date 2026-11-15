#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern void matrix_mul_vec3(float *, float *, float *);
extern void FastVecAdd(float *, float *, float *);
extern char *func_PAL_002735D0(char *, int, int, int, char *, char *, float *, int, float, float);
extern int func_PAL_00303578(char *, float *, float *, int, int, int);
extern int D_L02_001B096C __attribute__((sda));

/* Spawns five particles at the actor (the ids 0xCA5 to 0xCA9, each with a random velocity in a
   0.0167-scaled box rotated by the matrix at +0xC0), then, while D_L02_001B096C stays above 0, up
   to five more (-5 each) through func_PAL_00303578 around a point near the actor. */
void func_PAL_L02_003EB760(char *arg0) {
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    char *pos = arg0 + 0x10;
    char *mat = arg0 + 0xC0;
    int i;

    for (i = 0xCA5; i < 0xCAA; i++) {
        qzero(a);
        a[0] = math_random_float_range(1.0f, 4.0f) * 0.020000001f;
        a[1] = math_random_signed_float_range(1.0f, 3.0f) * 0.020000001f;
        a[2] = math_random_float_range(4.0f, 9.0f) * 0.020000001f;
        matrix_mul_vec3(a, a, (float *)(arg0 + 0xC0));
        func_PAL_002735D0(arg0, 0, i, -1, arg0 + 0x10, arg0 + 0xF0, a, 0xFF,
                      math_random_float_range(90.0f, 180.0f), math_random_float_range(15.0f, 25.0f));
    }
    *(TI128 *)b = 0;
    b[2] = 1.5f;
    matrix_mul_vec3(b, b, (float *)mat);
    FastVecAdd(b, b, (float *)pos);
    for (i = 0; i < 5 && D_L02_001B096C > 0; i++) {
        qzero(a);
        a[0] = math_random_float_range(1.0f, 4.0f) * 0.020000001f;
        a[1] = math_random_signed_float_range(1.0f, 3.0f) * 0.020000001f;
        a[2] = math_random_float_range(4.0f, 9.0f) * 0.020000001f;
        matrix_mul_vec3(a, a, (float *)mat);
        func_PAL_00303578(arg0, b, a, 0, 5, 0);
        D_L02_001B096C -= 5;
    }
}
