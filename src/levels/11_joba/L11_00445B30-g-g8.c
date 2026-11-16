#include "include_asm.h"
#include "names.h"


typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef int s32;
extern u16 g_fade_bar_height_step __attribute__((sda));
extern s32 g_fade_bar_color_a __attribute__((sda));
extern s32 g_fade_bar_count __attribute__((sda));
extern s32 g_fade_bar_packet_arg __attribute__((sda));
extern s32 g_fade_bar_max_height __attribute__((sda));
extern s32 g_fade_bar_color_b __attribute__((sda));
extern s32 g_fade_bar_margin __attribute__((sda));
extern short g_screen_adjust_offsets[];
extern float IntToFloat(short);
extern void VU1_addGSregister(int, long long);
extern void AppendScreenRectPacket(int, int, int, int, unsigned long, int);
extern long long GetEffectTextureDescriptor(int);
extern void DrawTexturedQuad(int, int, int, int, int, int, int, int, unsigned long long, unsigned long long);

/* Same body as func_L02_004002E0, with this function's own callees. */
/* Draws a full-screen fade and a sweeping bar that follow a countdown timer. */
void hud_draw_fade_bar(char *moby) {
    char *state = *(char **)(moby + 0x68);
    s32 color;
    float fadeAmount;
    float screenHeight;
    long long texId;
    s32 i;
    s32 barY;
    s32 barHeight;
    s32 margin;
    short *screen;

    color = g_fade_bar_color_a;
    *(u16 *)(state + 0x1F4) -= g_fade_bar_height_step;
    fadeAmount = IntToFloat(*(u16 *)(state + 0x1F4));
    screenHeight = (float)g_screen_adjust_offsets[0xA9];
    fadeAmount = fadeAmount / screenHeight;
    fadeAmount = fadeAmount * fadeAmount;
    {
        float scale = (float)(s32)((u32)color >> 24);

        color &= 0xFFFFFF;
        color |= (s32)(fadeAmount * scale) << 24;
    }
    VU1_addGSregister(0x42, 0x8000000049LL);
    for (i = 0; i < g_fade_bar_count; i++)
        AppendScreenRectPacket(0, 0, g_screen_adjust_offsets[0xA8], g_screen_adjust_offsets[0xA9], color, 0);
    VU1_addGSregister(0x42, 0x8000000044LL);
    screen = g_screen_adjust_offsets;
    AppendScreenRectPacket(0, 0, screen[0xA8], *(s16 *)(state + 0x1F4), g_fade_bar_packet_arg, 0);
    texId = GetEffectTextureDescriptor(0x10);
    color = g_fade_bar_color_b;
    {
        float scale = (float)(s32)((u32)color >> 24);

        color &= 0xFFFFFF;
        color |= (s32)(fadeAmount * scale) << 24;
    }
    VU1_addGSregister(0x42, 0x8000000048LL);
    barY = *(s16 *)(state + 0x1F4);
    barHeight = screen[0xA9] - barY;
    if (g_fade_bar_max_height < barHeight)
        barHeight = g_fade_bar_max_height;
    margin = g_fade_bar_margin;
    DrawTexturedQuad(-margin, barY - (barHeight >> 1), screen[0xA8] + margin * 2, barHeight, 0, 0, 0x20, 0x20, color, texId);
}
