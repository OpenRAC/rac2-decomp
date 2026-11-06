#include "include_asm.h"

typedef int s32;

typedef float f32;

/* func_PAL_00301178, the PAL copy of func_00300048: the same C, where the count
   ref_L00_00300048_04 returns is scaled to 50 Hz before it is passed on.  The
   divisor sits in a local set before the loop's counter, which keeps the
   counter in $s3 and the divisor in $s4. */

extern float ref_L00_00300048_06 __attribute__((sda));

extern float ref_L00_00300048_07 __attribute__((sda));

extern float ref_L00_00300048_08 __attribute__((sda));

extern float ref_L00_00300048_09 __attribute__((sda));

extern float ref_L00_00300048_00[];

extern void ref_L00_00300048_01(f32 *, f32 *, f32);

extern void ref_L00_00300048_02(f32 *, f32 *, f32 *);

extern void ref_L00_00300048_03(f32 *, f32, f32);

extern int ref_L00_00300048_04(int, int);

extern void ref_L00_00300048_05(f32 *, f32 *, int, int, int, int, int, int, f32, f32, f32, f32);

void func_PAL_00301178(void *unused_object)
{
    f32 a[4], b[4], c[4], d[4];
    f32 *p = ref_L00_00300048_00;
    f32 *q = p - 140;
    s32 i;
    s32 ret;
    s32 scale = 6;

    i = 5;
    do {
        ref_L00_00300048_01(a, p, 9.0f);
        ref_L00_00300048_02(b, q, a);
        ref_L00_00300048_03(c, 0.1f, 3.0f);
        ref_L00_00300048_01(a, p, 3.0f);
        ref_L00_00300048_02(d, q, a);
        ref_L00_00300048_02(c, d, c);
        ret = ((s32)ref_L00_00300048_04(8, 12) * 5 + 2) / scale;
        ref_L00_00300048_05(b, c, ret, 0x00808080, 0x00808080, 0x00FF1010, 0x00FF1010,
                            0x00FF1010, ref_L00_00300048_06, ref_L00_00300048_07,
                            ref_L00_00300048_08, ref_L00_00300048_09);
        i--;
    } while (i >= 0);
}
