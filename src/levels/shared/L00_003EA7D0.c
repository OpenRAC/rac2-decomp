#include "include_asm.h"
#include "names.h"

extern void VU1_addGSregister(int, long long);

extern void gfx_draw_aimed_glow_sprite(char *a, unsigned int b, unsigned int c, float d);

/* the level's table, named twice: the address is materialised again for each
 * call instead of being kept in a register across them */
extern int g_meteor_gun_glow_position[];
extern int D_L00_001B2BA0_1[];

/* Puts the object in its 0x3C-tick state: a sound, two tinted texts and a
 * last sound, but only when the object is not already in it. */
/* Draws the Meteor Gun glow when the gun is visible. */
void meteor_gun_draw_glow(char *p)
{
    if (*(unsigned char *)(p + 0x31) == 0)
        return;

    VU1_addGSregister(0x47, 0x53001LL);
    gfx_draw_aimed_glow_sprite(p, (unsigned int)g_meteor_gun_glow_position, 0x7F10307F, 0.25f);
    gfx_draw_aimed_glow_sprite(p, (unsigned int)D_L00_001B2BA0_1, 0x3F08183F, 0.5f);
    VU1_addGSregister(0x47, 0x5360BLL);
}
