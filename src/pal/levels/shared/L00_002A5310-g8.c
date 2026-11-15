#include "names.h"
/* Tick reads use the real SDA word and its absolute-address alias.
   PAL timing: initial delay 25 frames, subsequent bias 17 frames. */
typedef unsigned char u8;

typedef int s32;

extern u8 g_hero_state[];

extern s32 g_frame_l00_counter __attribute__((sda));

extern s32 ref_L00_002A5310_00;

extern s32 math_random_int_below(s32);

/* One-shot delay timer: the first pass stamps the resident block, the second one asks
   the helper twice and stores the sum of the two answers. */
void func_PAL_L00_002A5310(void)
{
    u8 *b = g_hero_state;
    s32 first_delay;
    s32 second_delay;
    s32 biased_delay;
    s32 tick;

    if (*(s32 *)(b + 0x1180) != 0)
        return;
    if (*(s32 *)(b + 0x1188) == 0) {
        *(s32 *)(b + 0x1184) = ref_L00_002A5310_00 + 25;
        return;
    }
    if (g_frame_l00_counter > *(s32 *)(b + 0x1184)) {
        *(s32 *)(b + 0x1180) = 1;
        first_delay = math_random_int_below(*(s32 *)(b + 0x1188));
        second_delay = math_random_int_below(*(s32 *)(b + 0x1188));
        biased_delay = first_delay + 17;
        tick = ref_L00_002A5310_00;
        tick = tick + biased_delay;
        tick = tick + second_delay;
        *(s32 *)(b + 0x1184) = tick;
    }
}
