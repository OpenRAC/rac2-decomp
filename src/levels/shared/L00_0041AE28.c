#include "include_asm.h"
#include "names.h"
extern void func_002FC560(unsigned int reg, unsigned long value);
extern void func_L00_0041B1B8(char *, unsigned int, int, float);
extern void func_L00_0041AFD8(char *, void *, unsigned int, float);
extern void func_L00_0041BCC8(char *);

/* Draws the Lava Gun shot: a glowing trail, plus flashes at the front while the shot is still active. */
void func_L00_0041AE28(char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    VU1_addGSregister(0x47, 0x53001);
    DrawPositionRingTrail(moby, 0x7F7F7F7F, 0x4B, 0.05f);
    if (*(float *)(vars + 0x50) != 0.0f) {
        DrawCameraFacingGlowSprite(moby, vars + 0x10, 0x7F10307F, 0.25f);
        DrawCameraFacingGlowSprite(moby, vars + 0x10, 0x3F08183F, 0.5f);
    }
    DrawEffectSlots(moby);
    VU1_addGSregister(0x47, 0x5360B);
}
