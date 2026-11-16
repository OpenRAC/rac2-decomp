#include "common.h"

/* func_PAL_L18_0042B5F8, the PAL copy of func_L18_00426AB0: the same C, with the bar maximum scaled to
   50 Hz, the blink cut-off 250 instead of 300 and the seconds divided by 50 instead of 60. */

/* -G8 for the HUD layout words. Incomplete sda arrays keep the resource pointer and the screen
   width as plain absolute loads. The early return sets v0 in the first branch's delay slot, and
   `result` shares v0 with it: with a single `return 0` block after the print code, reorg moves
   `li v0,1` into a jump over that block, and its USE keeps v0 live at the print block, which
   stops the blink test taking `andi v0` in the range branch's delay slot. */
extern u8 *g_hud_l18_resource_base[] __attribute__((sda));
extern u8 g_hero_state[];
extern s32 g_screen_width[] __attribute__((sda));
extern u32 g_timer_bar_color_a_start __attribute__((sda)), g_timer_bar_color_b_start __attribute__((sda));
extern u32 g_timer_bar_color_a_end __attribute__((sda)), g_timer_bar_color_b_end __attribute__((sda));
extern s32 g_timer_bar_half_gap __attribute__((sda)), g_timer_bar_y __attribute__((sda));
extern s32 g_timer_bar_width __attribute__((sda)), g_timer_bar_height __attribute__((sda));
extern s32 g_timer_text_y __attribute__((sda)), g_timer_bar_y_offset __attribute__((sda));
extern char g_str_l18_timer_format[];
extern void *table_find_by_id(u8 *, s32);
extern void gfx_draw_scaled_object_two_axes(char *, s32, float, float, float, float, float);
extern float IntToFloat(s32);
extern s32 FastTweenColor(s32, s32, float);
extern void gfx_draw_screen_rectangle(s32, s32, s32, s32, s32, void *);
extern s32 sprintf(char *, char *, ...);
extern void FontPrintCenterScaled_pal(s32, s32, s64, char *, s32, float);
/* Draws the timer bar and the remaining seconds while the hero is on the timed vehicle; returns 1 if drawn (PAL: 50 Hz timings). */
s32 hud_l18_draw_timer_bar_pal(void)
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
    if (g_hud_l18_resource_base[0]) {
        handle = table_find_by_id(g_hud_l18_resource_base[0] + 0x8710, 0xDB);
        gfx_draw_scaled_object_two_axes((char *)handle, 0x60442D00, (float)(g_screen_width[0] / 2),
                      (float)(g_timer_bar_y + g_timer_bar_y_offset), 1.0f, 1.0f, 0.0f);
        handle = table_find_by_id(g_hud_l18_resource_base[0] + 0x8710, 0xDC);
        gfx_draw_scaled_object_two_axes((char *)handle, 0x55F0C070, (float)(g_screen_width[0] / 2),
                      (float)(g_timer_bar_y + g_timer_bar_y_offset), 1.0f, 1.0f, 0.0f);
        state = *(u8 **)(*(u8 **)(hero + 0x2290) + 0x68);
        amount = IntToFloat(*(s16 *)(state + 0x3BC));
        ratio = amount / IntToFloat(((int)((*(s16 *)(state + 0x3BE))) * 5 + 2) / 6);
        colors[0] = FastTweenColor(g_timer_bar_color_a_start, g_timer_bar_color_a_end, ratio);
        colors[1] = FastTweenColor(g_timer_bar_color_b_start, g_timer_bar_color_b_end, ratio);
        middle = g_screen_width[0] / 2;
        gfx_draw_screen_rectangle(middle + g_timer_bar_half_gap, g_timer_bar_y,
                      (s32)((float)(middle + g_timer_bar_half_gap) + (float)g_timer_bar_width * ratio),
                      g_timer_bar_y + g_timer_bar_height, 0xFFFFF1, colors);
        gfx_draw_screen_rectangle(middle - g_timer_bar_half_gap, g_timer_bar_y,
                      (s32)((float)(middle - g_timer_bar_half_gap) - (float)g_timer_bar_width * ratio),
                      g_timer_bar_y + g_timer_bar_height, 0xFFFFF1, colors);
        remaining = *(u16 *)(state + 0x3BC);
        if (remaining < 32 || remaining > 250 || (remaining & 24)) {
            sprintf(text, g_str_l18_timer_format, (s16)remaining / 50);
            FontPrintCenterScaled_pal(middle, g_timer_text_y + 1, 0xFF000000, text, 3, 0.96f);
            FontPrintCenterScaled_pal(middle, g_timer_text_y - 1, 0xFF000000, text, 3, 1.04f);
            FontPrintCenterScaled_pal(middle, g_timer_text_y, colors[0], text, 3, 1.0f);
        }
        result = 1;
    }
    return result;
}
