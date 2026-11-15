#include "include_asm.h"
#include "names.h"
extern void VU1_addGSregister(unsigned int reg, unsigned long value);
extern void DrawPositionRingTrail(char *, unsigned int, int, float);
extern void lava_gun_draw_glow_sprite(char *, void *, unsigned int, float);
extern void DrawEffectSlots(char *);

/* Draws the Lava Gun shot: a glowing trail, plus flashes at the front while the shot is still active. */
void lava_gun_draw_shot(char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    VU1_addGSregister(0x47, 0x53001);
    DrawPositionRingTrail(moby, 0x7F7F7F7F, 0x4B, 0.05f);
    if (*(float *)(vars + 0x50) != 0.0f) {
        lava_gun_draw_glow_sprite(moby, vars + 0x10, 0x7F10307F, 0.25f);
        lava_gun_draw_glow_sprite(moby, vars + 0x10, 0x3F08183F, 0.5f);
    }
    DrawEffectSlots(moby);
    VU1_addGSregister(0x47, 0x5360B);
}
