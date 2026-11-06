#include "include_asm.h"
#include "common.h"

/* func_PAL_002D74D8, the PAL copy of func_002D68D8: the same C, with the frame count at 50 Hz. */
extern int ref_L00_002D68D8_00 __attribute__((sda));
extern int func_00283D38(int, int, float);

int func_PAL_002D74D8(int start, int first, int second)
{
    float fraction;
    if (start < 0) start = 0;
    if (first == -1) first = (int)0x80FFA888u;
    if (second == -1) second = (int)0x8020FFFFu;
    if (((s32)(ref_L00_002D68D8_00) * 5 + 2) / 6 >= start)
        fraction = 1.0f - (float)(((s32)(ref_L00_002D68D8_00) * 5 + 2) / 6 - start) / (float)(((s32)(ref_L00_002D68D8_00) * 5 + 2) / 6);
    else
        fraction = 1.0f;
    return func_00283D38(first, second, fraction);
}
