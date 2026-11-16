#include "include_asm.h"

#include "common.h"
extern float IntToFloat(int);
extern u32 D_L04_001B2E84_1 MACRO_ADDR;
extern int g_particle_life_step MACRO_ADDR;
extern int g_particle_delay_reload MACRO_ADDR;
extern float g_particle_fade_scale MACRO_ADDR;
extern int ref_L04_003C6FE8_00 SDATA(ref_L04_003C6FE8_00);
extern float ref_L04_003C6FE8_01 SDATA(ref_L04_003C6FE8_01);
extern float ref_L04_003C6FE8_02 SDATA(ref_L04_003C6FE8_02);

/* Sets up the particle fade timer once (50 frames) and then keeps scrolling its texture offset. */
void particle_fade_timer_update_pal(u8 *moby)
{
    int period;

    switch (moby[0x20]) {
    case 0:
        period = 0x32;
        D_L04_001B2E84_1 = 0;
        moby[0x20] = 1;
        moby[0x30] = 0xFF;
        g_particle_life_step = period;
        ref_L04_003C6FE8_00 = period;
        {
            float duration = IntToFloat(period);
            ref_L04_003C6FE8_01 = 1.0f / duration;
        }
        g_particle_delay_reload = period;
        g_particle_fade_scale = 0.02f;
        break;
    case 1:
        {
            float t = ref_L04_003C6FE8_02 - 0.003f;

            ref_L04_003C6FE8_02 = t;
            if (t <= -8.0f)
                ref_L04_003C6FE8_02 = t + 8.0f;
        }
        break;
    }
}
