#include "include_asm.h"

#include "common.h"
extern void func_002A77E0(int a);
extern float func_002A7878(float a, float b);
extern unsigned int func_002A7820(int a, int b);
extern void func_002A7A00(char *p, float a, float b);
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
        func_002A77E0(2);
        i = i - 1;
        func_002A77E0(2);
        f = func_002A7878(70000.0f, 1.5e+05f);
        v = func_002A7820(10, 127);
        w = (v << 8) | 0x7f000000U;
        x = (v << 16) | w;
        v = x | v;
        func_002A7A00(local, 2.0000003e-05f,
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
