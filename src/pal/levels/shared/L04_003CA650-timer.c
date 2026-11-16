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

/* Runs the water timer: on the first call it sets up the particle timing values (PAL: 50 Hz), then it scrolls a texture offset every frame. */
void water_timer_update_pal(u8 *moby_data)
{
    int v;

    switch (moby_data[0x20]) {
    case 0:
        v = 0x32;
        D_L04_001B2E84_1 = 0;
        moby_data[0x20] = 1;
        moby_data[0x30] = 0xFF;
        g_particle_life_step = v;
        ref_L04_003C6FE8_00 = v;
        {
            float duration = IntToFloat(v);
            ref_L04_003C6FE8_01 = 1.0f / duration;
        }
        g_particle_delay_reload = v;
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
