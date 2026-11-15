#include "common.h"

/* -G8 for the HUD layout words. Incomplete sda arrays keep the resource pointer and the screen
   width as plain absolute loads. The early return sets v0 in the first branch's delay slot, and
   `result` shares v0 with it: with a single `return 0` block after the print code, reorg moves
   `li v0,1` into a jump over that block, and its USE keeps v0 live at the print block, which
   stops the blink test taking `andi v0` in the range branch's delay slot. */
extern u8 *D_L18_001A904C[] __attribute__((sda));
extern u8 g_hero_state[];
extern s32 g_screen_width[] __attribute__((sda));
extern u32 D_L18_001B12C4 __attribute__((sda)), D_L18_001B12C8 __attribute__((sda));
extern u32 D_L18_001B12CC __attribute__((sda)), D_L18_001B12D0 __attribute__((sda));
extern s32 D_L18_001B12D4 __attribute__((sda)), D_L18_001B12D8 __attribute__((sda));
extern s32 D_L18_001B12DC __attribute__((sda)), D_L18_001B12E0 __attribute__((sda));
extern s32 D_L18_001B12E4 __attribute__((sda)), D_L18_001B12E8 __attribute__((sda));
extern char D_L18_001B1300[];
extern void *table_find_by_id(u8 *, s32);
extern void gfx_draw_scaled_object_two_axes(char *, s32, float, float, float, float, float);
extern float IntToFloat(s32);
extern s32 FastTweenColor(s32, s32, float);
extern void gfx_draw_screen_rectangle(s32, s32, s32, s32, s32, void *);
extern s32 sprintf(char *, char *, ...);
extern void FontPrintCenterScaled(s32, s32, s64, char *, s32, float);
/* Draws the on-screen timer bar and countdown number when the player is in this special mode. Returns 1 if it drew. */
s32 hud_draw_timer_bar(void)
{
    s32 colors[2];
    char text[16];
    u8 *state;
    u8 *hero = g_hero_state;
    s32 middle;
    float ratio;
    float amount;
    s32 handle;
    u16 remaining;
    s32 result;

    if (hero[0x22B4] != 4) {
        return 0;
    }
    result = 0;
    if (D_L18_001A904C[0]) {
        handle = table_find_by_id(D_L18_001A904C[0] + 0x8710, 0xDB);
        gfx_draw_scaled_object_two_axes((char *)handle, 0x60442D00, (float)(g_screen_width[0] / 2),
                      (float)(D_L18_001B12D8 + D_L18_001B12E8), 1.0f, 1.0f, 0.0f);
        handle = table_find_by_id(D_L18_001A904C[0] + 0x8710, 0xDC);
        gfx_draw_scaled_object_two_axes((char *)handle, 0x55F0C070, (float)(g_screen_width[0] / 2),
                      (float)(D_L18_001B12D8 + D_L18_001B12E8), 1.0f, 1.0f, 0.0f);
        state = *(u8 **)(*(u8 **)(hero + 0x2290) + 0x68);
        amount = IntToFloat(*(s16 *)(state + 0x3BC));
        ratio = amount / IntToFloat(*(s16 *)(state + 0x3BE));
        colors[0] = FastTweenColor(D_L18_001B12C4, D_L18_001B12CC, ratio);
        colors[1] = FastTweenColor(D_L18_001B12C8, D_L18_001B12D0, ratio);
        middle = g_screen_width[0] / 2;
        gfx_draw_screen_rectangle(middle + D_L18_001B12D4, D_L18_001B12D8,
                      (s32)((float)(middle + D_L18_001B12D4) + (float)D_L18_001B12DC * ratio),
                      D_L18_001B12D8 + D_L18_001B12E0, 0xFFFFF1, colors);
        gfx_draw_screen_rectangle(middle - D_L18_001B12D4, D_L18_001B12D8,
                      (s32)((float)(middle - D_L18_001B12D4) - (float)D_L18_001B12DC * ratio),
                      D_L18_001B12D8 + D_L18_001B12E0, 0xFFFFF1, colors);
        remaining = *(u16 *)(state + 0x3BC);
        if (remaining < 32 || remaining > 300 || (remaining & 24)) {
            sprintf(text, D_L18_001B1300, (s16)remaining / 60);
            FontPrintCenterScaled(middle, D_L18_001B12E4 + 1, 0xFF000000, text, 3, 0.96f);
            FontPrintCenterScaled(middle, D_L18_001B12E4 - 1, 0xFF000000, text, 3, 1.04f);
            FontPrintCenterScaled(middle, D_L18_001B12E4, colors[0], text, 3, 1.0f);
        }
        result = 1;
    }
    return result;
}
