#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern float g_tethered_body_param_a __attribute__((sda));
extern float g_tethered_body_param_b __attribute__((sda));
extern float g_tethered_body_param_c __attribute__((sda));
extern void FastVecSub(void *, void *, void *);
extern void moby_set_state(char *, int, int);
extern void mat_combine_and_store(char *, char *, char *, char *);
extern void pushable_moby_update_pal(void *, void *, f32, f32, f32, s32);

/* func_PAL_L20_0043A00C, the PAL copy of func_L18_00426AB0: the same C as func_PAL_L18_0042B5F8, with
   the bar maximum scaled to 50 Hz, the blink cut-off 250 and the seconds divided by 50. */

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
/* Draws the on-screen timer bar and countdown number when the player is in this special mode (PAL: 50 Hz timings). Returns 1 if it drew. */
s32 hud_l20_draw_timer_bar_pal(void)
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

/* The three floats of case 1 are read through $gp, and the two 128-bit copies are
   qcopy (retail materialises both addresses: addiu; lq 0; sq 0). */
void tethered_body_update_pal(char *moby) {
    char *state = *(char **)(moby + 0x68);
    TI128 pos;
    TI128 rot;
    TI128 out;

    qcopy(&pos, moby + 0x10);
    qcopy(&rot, moby + 0xF0);

    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        *(u16 *)(moby + 0x34) |= 0x1000;
        *(f32 *)(state + 0x84) = 7.0f;
        *(int *)(state + 0xDC) |= 1;
        *(f32 *)(state + 0x88) = *(f32 *)(state + 0xE4);
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        pushable_moby_update_pal(moby, state + 0x50, g_tethered_body_param_a, g_tethered_body_param_b,
                          g_tethered_body_param_c, *(s32 *)(state + 0xE0));
        break;
    }
    FastVecSub(&out, moby + 0x10, &pos);
    mat_combine_and_store(state + 0xA0, (char *)&out, (char *)&rot, moby + 0xF0);
}
