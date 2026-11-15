#include "names.h"
/* func_PAL_002EE490, the PAL copy of func_002ED578: the same C, where expr 0.00027777778f becomes 0.00033333333f; lit 5.0f becomes 6.0f; rename func_00283CE0_6 becomes func_00283CE0; rename func_00283CF0_9 becomes func_00283CF0. */

extern float IntToFloat(int a0);

extern int FloatToInt(float x);

typedef int s32;

typedef unsigned char u8;

/* func_002EE6A8: owner ABI/declaration review retained. */
extern char *moby_get_motion_data(unsigned char *owner);

/* func_002ED870: owner ABI/declaration review retained. */
/* Decomposes a float returned by a bound producer into hours, minutes and hundredths written through three pointer arguments, rounding each step with a bound helper and clamping the last field at 99. */
int func_PAL_002EE490(int a0, int *p0, int *p1, int *p2)
{
    float t;
    int a;
    int b;
    int c;
    int d;
    int e;

    t = IntToFloat(a0);
    a = FloatToInt(t * (0.00033333333f));
    *p0 = a;
    b = FloatToInt((float)a * 3e+03f);
    t = t - (float)b;
    c = FloatToInt(t * 0.02f);
    *p1 = c;
    d = FloatToInt((float)c * 5e+01f);
    t = t - (float)d;
    e = FloatToInt(t * (6.0f / 3.0f));
    e = e > 99 ? 0 : e;
    *p2 = e;
    return e;
}

char *moby_get_motion_data(u8 *a0);

/* func_002ED6B0 is in 002ED6B0.c: its call to func_002ED870 has to be an external one. */

/* func_002EDA10 is in 002EDA10.c. */

/* func_002EE000 is in 002ED578-g8.c. */

/* func_002EE3B0 is in 002EE3B0-g8.c. */
