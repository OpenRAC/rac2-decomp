#include "common.h"

extern float IntToFloat(int);
extern u32 D_L04_001B2E84_1 MACRO_ADDR;
extern int g_particle_life_step MACRO_ADDR;
extern int g_particle_delay_reload MACRO_ADDR;
extern float g_particle_fade_scale MACRO_ADDR;
extern int ref_L04_003C6FE8_00 SDATA(ref_L04_003C6FE8_00);
extern float ref_L04_003C6FE8_01 SDATA(ref_L04_003C6FE8_01);
extern float ref_L04_003C6FE8_02 SDATA(ref_L04_003C6FE8_02);

/* Update for a water timer object: starts a 60-frame countdown, then keeps scrolling the water texture. */
void water_timer_update(u8 *moby)
{
    int frames;

    switch (moby[0x20]) {
    case 0:
        frames = 0x3C;
        D_L04_001B2E84_1 = 0;
        moby[0x20] = 1;
        moby[0x30] = 0xFF;
        g_particle_life_step = frames;
        ref_L04_003C6FE8_00 = frames;
        {
            float duration = IntToFloat(frames);
            ref_L04_003C6FE8_01 = 1.0f / duration;
        }
        g_particle_delay_reload = frames;
        g_particle_fade_scale = 0.016666668f;
        break;
    case 1:
        {
            float scroll = ref_L04_003C6FE8_02 - 0.0025f;

            ref_L04_003C6FE8_02 = scroll;
            if (scroll <= -8.0f)
                ref_L04_003C6FE8_02 = scroll + 8.0f;
        }
        break;
    }
}
