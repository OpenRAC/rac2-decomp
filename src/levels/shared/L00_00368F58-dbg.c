/* func_L00_00368F58 in its own unit (flags in config/cflags.txt: -O2 -G0 -ffunction-sections -g). */
#include "include_asm.h"
#include "names.h"

extern float D_001BD370;

extern float D_001B24DC __attribute__((sda));

extern float D_001B24E0[];

extern void SetTfragDists(int);

/* Works out three scale values from the frame time, using a limit between 1 and 4, then updates the display. */
void gfx_update_frame_time_scales(int force)
{
    float value = 0.62f / D_001BD370;
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
    base = D_001B24DC;
    fourValue = value * four;
    twice = base + base;
    sixValue = value * 6.0f;
    D_001B24E0[1] = base * fourValue;
    D_001B24E0[2] = twice * value;
    D_001B24E0[0] = base * sixValue;
    SetTfragDists(force);
}
