#include "include_asm.h"

/* func_PAL_L08_003DC0D0, the PAL copy of func_L08_003D7FB8: the same C at 50 Hz, where 0.016666668f
   becomes 0.020000001f, 0.16666667f becomes 0.2f, 0.0083333338f becomes 0.010000001f, 10 and 30 go
   through the 50 Hz scale and the func_002A7878(15.0f, 75.0f) value goes through its float form.

   Retail hoists 5.0f out of the inner loop but not 2.0f, 0.16666667f or -1. The inner body's w, v and
   u leave in the first loop pass, in retail's order, so 5.0f goes first in the second pass, and
   col1's initial value holds that pass at 59 real insns, which keeps 2.0f in the loop. */

typedef int TI128 __attribute__((mode(TI)));
typedef int s32;

extern void func_002ACB48(float *, float);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern void func_00282D30(void *, void *, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_00283D38(int, int, float);
extern int func_00283CF0(float);
extern void func_002BAA28(void *, void *, void *, int, int, int, int, int, int);

void func_PAL_L08_003DC0D0(char *arg0, char *arg1) {
    float a[4];
    float b[4];
    float c[4];
    int n;
    int i;
    float angle;
    float r;
    float z;
    char *src = arg0 + 0x10;

    for (n = 0; n < 20; n++) {
        *(TI128 *)a = *(TI128 *)src;
        func_002ACB48(a, 0.25f);
        a[2] += 0.25f;
        angle = func_002A7940();
        r = func_002A7878(1.0f, 8.0f);
        z = func_002A7878(2.0f, 6.0f);
        func_00282D30(b, arg1, func_002A7878(0.0f, 0.0f) * 0.020000001f);
        b[0] += func_00283180(angle) * 0.020000001f * r;
        b[1] += func_00283198(angle) * 0.020000001f * r;
        b[2] += z * 0.020000001f;
        *(TI128 *)c = *(TI128 *)b;
        c[2] -= 0.2f;
        for (i = 0; i < 10; i++) {
            float w = 0.125f;
            float v = 1.0f;
            float u = 0.065f;
            float k = func_002A7878(0.5f, 1.5f);
            int col1 = 0;
            int col2;

            b[3] = k * w;
            c[3] = k * u;
            func_002ACB48(a, w);
            func_002ACB48(c, 0.010000001f);
            col1 = func_00283D38(0x8000EEEE, 0x8000FF90, func_002A7878(0.0f, v));
            col2 = func_00283D38(0xFFEE, 0xFFEE, func_002A7878(0.0f, v));
            func_002BAA28(a, b, c, col1, col2, ((s32)(10) * 5 + 2) / 6, ((s32)(30) * 5 + 2) / 6, func_00283CF0((func_002A7878(15.0f, 75.0f) * 5.0f + 2.0f) * 0.16666667f), -1);
        }
    }
}
