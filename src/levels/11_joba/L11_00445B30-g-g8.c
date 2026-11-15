#include "include_asm.h"
#include "names.h"


typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef int s32;
extern u16 D_L11_001B1850 __attribute__((sda));
extern s32 D_L11_001B1848 __attribute__((sda));
extern s32 D_L11_001B184C __attribute__((sda));
extern s32 D_L11_001B1844 __attribute__((sda));
extern s32 D_L11_001B1858 __attribute__((sda));
extern s32 D_L11_001B185C __attribute__((sda));
extern s32 D_L11_001B1860 __attribute__((sda));
extern short D_001A6480[];
extern float func_00283CE0(short);
extern void func_002FC560(int, long long);
extern void func_0028FC48(int, int, int, int, unsigned long, int);
extern long long func_0027C878(int);
extern void func_0027E018(int, int, int, int, int, int, int, int, unsigned long long, unsigned long long);

/* Same body as func_L02_004002E0, with this function's own callees. */
/* Draws a full-screen fade and a sweeping bar that follow a countdown timer. */
void func_L11_00445B30(char *moby) {
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

    color = D_L11_001B1848;
    *(u16 *)(state + 0x1F4) -= D_L11_001B1850;
    fadeAmount = IntToFloat(*(u16 *)(state + 0x1F4));
    screenHeight = (float)gScreenAdjustOffsets[0xA9];
    fadeAmount = fadeAmount / screenHeight;
    fadeAmount = fadeAmount * fadeAmount;
    {
        float scale = (float)(s32)((u32)color >> 24);

        color &= 0xFFFFFF;
        color |= (s32)(fadeAmount * scale) << 24;
    }
    VU1_addGSregister(0x42, 0x8000000049LL);
    for (i = 0; i < D_L11_001B184C; i++)
        AppendScreenRectPacket(0, 0, gScreenAdjustOffsets[0xA8], gScreenAdjustOffsets[0xA9], color, 0);
    VU1_addGSregister(0x42, 0x8000000044LL);
    screen = gScreenAdjustOffsets;
    AppendScreenRectPacket(0, 0, screen[0xA8], *(s16 *)(state + 0x1F4), D_L11_001B1844, 0);
    texId = GetEffectTextureDescriptor(0x10);
    color = D_L11_001B185C;
    {
        float scale = (float)(s32)((u32)color >> 24);

        color &= 0xFFFFFF;
        color |= (s32)(fadeAmount * scale) << 24;
    }
    VU1_addGSregister(0x42, 0x8000000048LL);
    barY = *(s16 *)(state + 0x1F4);
    barHeight = screen[0xA9] - barY;
    if (D_L11_001B1858 < barHeight)
        barHeight = D_L11_001B1858;
    margin = D_L11_001B1860;
    DrawTexturedQuad(-margin, barY - (barHeight >> 1), screen[0xA8] + margin * 2, barHeight, 0, 0, 0x20, 0x20, color, texId);
}
