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
int math_split_time_into_parts_pal(int value, int *out_hours, int *out_minutes, int *out_hundredths)
{
    float remaining;
    int hours;
    int hour_seconds;
    int minutes;
    int minute_seconds;
    int hundredths;

    remaining = IntToFloat(value);
    hours = FloatToInt(remaining * (0.00033333333f));
    *out_hours = hours;
    hour_seconds = FloatToInt((float)hours * 3e+03f);
    remaining = remaining - (float)hour_seconds;
    minutes = FloatToInt(remaining * 0.02f);
    *out_minutes = minutes;
    minute_seconds = FloatToInt((float)minutes * 5e+01f);
    remaining = remaining - (float)minute_seconds;
    hundredths = FloatToInt(remaining * (6.0f / 3.0f));
    hundredths = hundredths > 99 ? 0 : hundredths;
    *out_hundredths = hundredths;
    return hundredths;
}

char *moby_get_motion_data(u8 *a0);

/* func_002ED6B0 is in 002ED6B0.c: its call to func_002ED870 has to be an external one. */

/* func_002EDA10 is in 002EDA10.c. */

/* func_002EE000 is in 002ED578-g8.c. */

/* func_002EE3B0 is in 002EE3B0-g8.c. */
