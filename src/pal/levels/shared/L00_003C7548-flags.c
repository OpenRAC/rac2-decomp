#include "include_asm.h"

#include "common.h"
extern void math_random_int_below(int a);
extern float math_random_float_range(float a, float b);
extern unsigned int math_random_int_range(int a, int b);
extern void vec_random_direction(char *p, float a, float b);
extern char *func_PAL_002BE9A8(float fa, float fb, float fc, float fd, char *p, int z,
                     char *local, unsigned int v, int one);

/* Runs 20 local iterations; the first two calls each pass integer 2 to the same bound target; on each non-null final result, stores a short at +10, an int at +36, and bytes at +42 and +43. */
void func_PAL_L00_003C76A0(char *unused, char *arg)
{
    char local[16];
    float f;
    int i;
    unsigned int v;
    unsigned int w;
    unsigned int x;
    char *r;

    i = 19;
    do {
        math_random_int_below(2);
        i = i - 1;
        math_random_int_below(2);
        f = math_random_float_range(70000.0f, 1.5e+05f);
        v = math_random_int_range(10, 127);
        w = (v << 8) | 0x7f000000U;
        x = (v << 16) | w;
        v = x | v;
        vec_random_direction(local, 2.0000003e-05f,
                0.008f);
        r = func_PAL_002BE9A8(0.3f, 1.0f, 1.01f, f, arg, 0, local, v, 1);
        if (r != 0) {
            char *q = r + 32;

            *(short *)(r + 10) = 100;
            *(int *)(q + 4) = 2;
            *(char *)(q + 10) = 127;
            *(char *)(q + 11) = *(unsigned char *)(r + 10);
        }
    } while (i >= 0);
}
