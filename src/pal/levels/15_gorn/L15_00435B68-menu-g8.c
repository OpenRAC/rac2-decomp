#include "common.h"

/* func_PAL_L15_00435B68: the PAL copy of v2.00's func_US2_L15_00431C88
 * (src/us2/levels/15_gorn/L15_00431C88-g8.c), itself the v2.00 copy of func_L15_00430168: a Gorn HUD
 * panel (two sprites, the counter line, a wrapped text box, the count line and two option labels).
 * The same C, with PAL's text ids. The v2.00 notes follow.

   Every sprite and box label y goes through label_y, the HUD label idiom (see its comment). Its
   tests have no effect on the result and leave no instruction, but retail shows them: after each y
   conversion retail ends a block, and the display-mode compare holds the 1 that the next real
   screen_coord mode test reads. The box text goes to func_L05_00303000, which returns the height
   used. */

extern s32 g_screen_width MACRO_ADDR;
extern u8 g_extras_unlocked_flag MACRO_ADDR;
extern u8 g_language MACRO_ADDR;
extern u8 *g_challenge_menu_data MACRO_ADDR;
extern f32 g_screen_l15_scale;
extern s32 g_screen_l15_mode MACRO_ADDR;
extern s32 g_gorn_finished_stage_num MACRO_ADDR;
extern s32 g_gorn_selected_challenge __attribute__((sda));
extern s32 g_challenge_completed_a[] SDATA(D_L15_001B1520);
extern s32 g_gorn_reward_table[][3] SDATA(D_L15_001B15D8);

extern f32 IntToFloat(s32);
extern s32 FloatToInt(f32);
extern void *table_find_by_id(void *, s32);
extern void gfx_draw_scaled_object(void *, f32, f32, s32, f32, f32);
extern char *GetLocalizedString(s32);
extern s32 sprintf(char *, char *, ...);
extern s32 func_001157AC(char *);
extern s32 text_draw_centered_medium(s32, s32, u64, char *, s32);
extern s32 text_print_wrapped_default(s32, s32, s32, s32, u64, u8 *, s32);
extern void text_draw_medium(s32, s32, u64, char *, s32);

/* The shape of scaled_screen_coord in src/game/002D3390.c, with this level's display scale. */
static __inline__ s32 screen_coord(s32 mode, f32 value, f32 offset)
{
    f32 scaled = value * g_screen_l15_scale + 0.5f;

    if (mode == 1)
        return (s32)(scaled + offset);
    return (s32)scaled;
}

/* label_y, the HUD label idiom for text and sprite label y coordinates (accepted 7 November 2026; one
   shared definition, `active` the literal 1 at every call). Its tests do not change the result: flow
   deletes their stores and jump2 their jumps, but only after allocation and both scheduling passes,
   which see the block they end. */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = g_screen_l15_mode;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}

/* Draws the Gorn reward panel: the finished stage's title, text and bolt reward, plus the option labels. */
s32 gorn_reward_panel_draw_pal(void) {
    char buf[128];
    f32 center = IntToFloat(g_screen_width) * 0.5f;
    void *sprite;
    char *text;
    s32 x, y, count, index;

    if (g_challenge_menu_data != 0) {
        sprite = table_find_by_id(g_challenge_menu_data + 0x8710, 0x45);
        gfx_draw_scaled_object(sprite, center, (f32)label_y(sprite, 200.0f, g_screen_l15_scale, 0.5f, 1), 0x60442D00, 1.0f, 0.0f);
        sprite = table_find_by_id(g_challenge_menu_data + 0x8710, 0x44);
        gfx_draw_scaled_object(sprite, center, (f32)label_y(sprite, 200.0f, g_screen_l15_scale, 0.5f, 1), 0x55F0C070, 1.0f, 0.0f);
        sprintf(buf, GetLocalizedString(0xE97), g_gorn_selected_challenge + 1);
        text = GetLocalizedString(0xEB8);
        x = FloatToInt(center);
        y = screen_coord(g_screen_l15_mode, 46.0f, -2.0f);
        text_draw_centered_medium(x, y, 0x80F0F0F0, text, func_001157AC(text));
        text = GetLocalizedString(0x10E3);
        {
            s32 ty = label_y(text, 131.0f, g_screen_l15_scale, 0.5f, 1);
            text_print_wrapped_default(117, ty, 280, 400, 0x80F0F0F0, (u8 *)text, func_001157AC(text));
        }
        index = g_challenge_completed_a[g_gorn_finished_stage_num] - 1;
        if (index >= 3)
            index = 2;
        count = g_gorn_reward_table[g_gorn_finished_stage_num][index];
        if (g_extras_unlocked_flag != 0)
            count *= 10;
        text = buf;
        if (count == 0)
            sprintf(buf, GetLocalizedString(0x11FF));
        else
            sprintf(buf, GetLocalizedString(0xEEB), count);
        {
            s32 ty = label_y(text, 210.0f, g_screen_l15_scale, 0.5f, 1);
            text_print_wrapped_default(117, ty, 280, 400, 0x80F0F0F0, (u8 *)text, func_001157AC(text));
        }
        y = screen_coord(g_screen_l15_mode, 294.0f, 3.0f);
        text_draw_medium(117, y, 0x80F0F0F0, GetLocalizedString(0x10E4), -1);
        if (g_language == 5) {
            y = screen_coord(g_screen_l15_mode, 294.0f, 3.0f);
            text_draw_medium(260, y, 0x80F0F0F0, GetLocalizedString(0x10E5), -1);
        } else if (g_language == 4) {
            y = screen_coord(g_screen_l15_mode, 294.0f, 3.0f);
            text_draw_medium(268, y, 0x80F0F0F0, GetLocalizedString(0x10E5), -1);
        } else if (g_language == 2) {
            y = screen_coord(g_screen_l15_mode, 294.0f, 3.0f);
            text_draw_medium(256, y, 0x80F0F0F0, GetLocalizedString(0x10E5), -1);
        } else {
            y = screen_coord(g_screen_l15_mode, 294.0f, 3.0f);
            text_draw_medium(274, y, 0x80F0F0F0, GetLocalizedString(0x10E5), -1);
        }
    }
    return 1;
}
