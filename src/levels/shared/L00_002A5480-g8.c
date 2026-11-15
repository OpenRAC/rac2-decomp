#include "names.h"
/* Tick reads use the real SDA word and its absolute-address alias.
   USA timing: initial delay 30 frames, subsequent bias 20 frames. */
typedef unsigned char u8;

typedef int s32;

extern u8 D_00189E20[];

extern s32 D_L00_001B19C8 __attribute__((sda));

extern s32 ref_L00_002A5480_00;

extern s32 func_002A77E0(s32);

/* One-shot delay timer: the first pass stamps the resident block, the second one asks
   the helper twice and stores the sum of the two answers. */
void func_L00_002A5480(void)
{
    u8 *b = gHeroState;
    s32 first_delay;
    s32 second_delay;
    s32 biased_delay;
    s32 tick;

    if (*(s32 *)(b + 0x1180) != 0)
        return;
    if (*(s32 *)(b + 0x1188) == 0) {
        *(s32 *)(b + 0x1184) = ref_L00_002A5480_00 + 30;
        return;
    }
    if (gFrameCounter_L00 > *(s32 *)(b + 0x1184)) {
        *(s32 *)(b + 0x1180) = 1;
        first_delay = RandomIntBelow(*(s32 *)(b + 0x1188));
        second_delay = RandomIntBelow(*(s32 *)(b + 0x1188));
        biased_delay = first_delay + 20;
        tick = ref_L00_002A5480_00;
        tick = tick + biased_delay;
        tick = tick + second_delay;
        *(s32 *)(b + 0x1184) = tick;
    }
}
