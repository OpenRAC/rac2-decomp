#include "include_asm.h"
#include "common.h"

/* func_PAL_002D74D8, the PAL copy of func_002D68D8: the same C, with the frame count at 50 Hz. */
extern int ref_L00_002D68D8_00 __attribute__((sda));
extern int FastTweenColor(int, int, float);

/* Blends two menu colors by how far a highlight fade timer has run (PAL: 50 Hz timing). */
int menu_blend_highlight_color_pal(int timer, int from_color, int to_color)
{
    float fraction;
    if (timer < 0) timer = 0;
    if (from_color == -1) from_color = (int)0x80FFA888u;
    if (to_color == -1) to_color = (int)0x8020FFFFu;
    if (((s32)(ref_L00_002D68D8_00) * 5 + 2) / 6 >= timer)
        fraction = 1.0f - (float)(((s32)(ref_L00_002D68D8_00) * 5 + 2) / 6 - timer) / (float)(((s32)(ref_L00_002D68D8_00) * 5 + 2) / 6);
    else
        fraction = 1.0f;
    return FastTweenColor(from_color, to_color, fraction);
}
