#include "names.h"
/* func_L00_00368F58 in its own unit (flags in config/cflags.txt: -O2 -G0 -ffunction-sections -g). */
#include "include_asm.h"
#include "names.h"

extern float g_frame_time_divisor;

extern float g_frame_time_base __attribute__((sda));

extern float g_frame_time_scales[];

extern void SetTfragDists(int);

/* Works out three scale values from the frame time, using a limit between 1 and 4, then updates the display. */
void gfx_update_frame_time_scales(int force)
{
    float value = 0.62f / g_frame_time_divisor;
    float four;
    float base;
    float fourValue;
    float sixValue;
    float twice;

    if (value < 1.0f)
        value = 1.0f;
    four = 4.0f;
    if (four < value)
        value = four;
    if (force)
        value = 1.0f;
    base = g_frame_time_base;
    fourValue = value * four;
    twice = base + base;
    sixValue = value * 6.0f;
    g_frame_time_scales[1] = base * fourValue;
    g_frame_time_scales[2] = twice * value;
    g_frame_time_scales[0] = base * sixValue;
    SetTfragDists(force);
}
