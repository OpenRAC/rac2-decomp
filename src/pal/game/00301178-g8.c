#include "include_asm.h"
#include "names.h"

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

void shop_spawn_preview_light_burst_pal(void *unused_object)
{
    f32 scaled[4], start[4], offset[4], other[4];
    f32 *table = ref_L00_00300048_00;
    f32 *table_prev = table - 140;
    s32 i;
    s32 count;
    s32 scale = 6;

    i = 5;
    do {
        ref_L00_00300048_01(scaled, table, 9.0f);
        ref_L00_00300048_02(start, table_prev, scaled);
        ref_L00_00300048_03(offset, 0.1f, 3.0f);
        ref_L00_00300048_01(scaled, table, 3.0f);
        ref_L00_00300048_02(other, table_prev, scaled);
        ref_L00_00300048_02(offset, other, offset);
        count = ((s32)ref_L00_00300048_04(8, 12) * 5 + 2) / scale;
        ref_L00_00300048_05(start, offset, count, 0x00808080, 0x00808080, 0x00FF1010, 0x00FF1010,
                            0x00FF1010, ref_L00_00300048_06, ref_L00_00300048_07,
                            ref_L00_00300048_08, ref_L00_00300048_09);
        i--;
    } while (i >= 0);
}
