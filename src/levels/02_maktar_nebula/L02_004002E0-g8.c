#include "include_asm.h"
#include "names.h"

typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef int s32;

extern u16 g_screen_wipe_height_step __attribute__((sda));
extern s32 g_screen_wipe_band_color_start __attribute__((sda));
extern s32 g_screen_wipe_band_count __attribute__((sda));
extern s32 g_screen_wipe_fill_color __attribute__((sda));
extern s32 g_screen_wipe_max_band_height __attribute__((sda));
extern s32 g_screen_wipe_band_color_end __attribute__((sda));
extern s32 g_screen_wipe_margin __attribute__((sda));
extern short g_screen_adjust_offsets[];
extern float IntToFloat(short);
extern void VU1_addGSregister(int, long long);
extern void AppendScreenRectPacket(int, int, int, int, unsigned long, int);
extern long long GetEffectTextureDescriptor(int);
extern void DrawTexturedQuad(int, int, int, int, int, int, int, int, unsigned long long, unsigned long long);

/* Draws the transition overlay. The height at +0x124 of the object's state drops by D_L02_001B14F8;
   func_00283CE0 turns it into a ratio, which is divided by the screen height (D_001A6480[0xA9]) and
   squared, and scales the alpha byte of two colours. The first colour fills the screen
   D_L02_001B14F4 times under one blend mode; D_L02_001B14EC fills the band down to the height; a
   0x20 by 0x20 sprite (func_0027C878(0x10)) in the second colour is drawn over its lower edge,
   D_L02_001B1508 wider on each side and at most D_L02_001B1500 tall. Built with -g
   (config/cflags.txt): retail has two nops in front of the division, which the assembler puts after
   a line label, so the division is a statement of its own. */
/* Draws a screen-wipe transition that fades the screen and slides a band down it. */
void gfx_draw_screen_wipe(char *actor) {
    char *state = *(char **)(actor + 0x68);
    s32 color;
    float ratio;
    float height;
    long long spriteId;
    s32 i;
    s32 wipeHeight;
    s32 bandHeight;
    s32 margin;
    short *screen;

    color = g_screen_wipe_band_color_start;
    *(u16 *)(state + 0x124) -= g_screen_wipe_height_step;
    ratio = IntToFloat(*(u16 *)(state + 0x124));
    height = (float)g_screen_adjust_offsets[0xA9];
    ratio = ratio / height;
    ratio = ratio * ratio;
    {
        float scale = (float)(s32)((u32)color >> 24);

        color &= 0xFFFFFF;
        color |= (s32)(ratio * scale) << 24;
    }
    VU1_addGSregister(0x42, 0x8000000049LL);
    for (i = 0; i < g_screen_wipe_band_count; i++)
        AppendScreenRectPacket(0, 0, g_screen_adjust_offsets[0xA8], g_screen_adjust_offsets[0xA9], color, 0);
    VU1_addGSregister(0x42, 0x8000000044LL);
    screen = g_screen_adjust_offsets;
    AppendScreenRectPacket(0, 0, screen[0xA8], *(s16 *)(state + 0x124), g_screen_wipe_fill_color, 0);
    spriteId = GetEffectTextureDescriptor(0x10);
    color = g_screen_wipe_band_color_end;
    {
        float scale = (float)(s32)((u32)color >> 24);

        color &= 0xFFFFFF;
        color |= (s32)(ratio * scale) << 24;
    }
    VU1_addGSregister(0x42, 0x8000000048LL);
    wipeHeight = *(s16 *)(state + 0x124);
    bandHeight = screen[0xA9] - wipeHeight;
    if (g_screen_wipe_max_band_height < bandHeight)
        bandHeight = g_screen_wipe_max_band_height;
    margin = g_screen_wipe_margin;
    DrawTexturedQuad(-margin, wipeHeight - (bandHeight >> 1), screen[0xA8] + margin * 2, bandHeight, 0, 0, 0x20, 0x20, color, spriteId);
}
