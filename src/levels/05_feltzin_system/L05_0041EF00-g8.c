#include "common.h"

/* func_L05_0041EF00: draws a Feltzin System menu panel: two sprites, two button icons, the header
   line, then for the selected entry (D_L05_001B13EC) its title, a wrapped text box, the reward
   line and one option label, or a locked-entry line; then three option labels. The same code as
   func_L10_004227A0 and func_L15_0042EFE0, with this level's data and text ids.

   The row y values go through the HUD label helpers (label_y, label_y3, MenuSpriteY); their tests
   have no effect on the result. Each do-while(0) group holds real statements (allowed,
   docs/build/compiler-notes.md); it ends the scheduling block after the reward row's y. */

extern f32 IntToFloat(s32);
extern s32 FloatToInt(f32);
extern s32 FastTweenColor(s32, s32, f32);
extern void *table_find_by_id(u8 *, s32);
extern void gfx_draw_scaled_object(void *, f32, f32, s32, f32, f32);
extern void gfx_draw_scaled_object_two_axes(char *, s32, f32, f32, f32, f32, f32);
extern char *GetLocalizedString(s32);
extern s32 sprintf(char *, char *, ...);
extern s32 func_001157AC(char *);
extern s32 text_draw_centered_large(s32, s32, u64, char *, s32);
extern s32 text_draw_centered_medium(s32, s32, u64, char *, s32);
extern s32 text_draw_centered_small(s32, s32, u64, char *, s32);
extern void text_draw_medium(s32, s32, u64, char *, s32);
/* Retail builds the colour with the 64-bit ori/dsll/ori form, so the caller passes a u64, as
   func_L05_00302CE8 (which the wrapper forwards to) takes it; the wrapper's matched C still says int. */
extern s32 text_print_wrapped_default(s32, s32, s32, s32, u64, u8 *, s32);
extern s32 g_screen_width;
typedef struct { u8 pad[0x1A0]; s32 buttons; } MenuInput;
extern MenuInput g_pad_state;
extern u8 g_extras_unlocked_flag;
extern s32 g_game_mode_a;
extern u8 *g_feltzin_mission_data;
extern f32 g_screen_l05_scale;
extern s32 g_label_mode;
extern s32 g_feltzin_mission_index;
extern s32 g_feltzin_reward_table_b[] __attribute__((sda)), g_feltzin_reward_table_c[] __attribute__((sda)), g_feltzin_reward_table_d[] __attribute__((sda));
extern s32 g_ship_fade_level_b __attribute__((sda));
extern s32 g_feltzin_selected_entry __attribute__((sda));
extern s32 g_feltzin_challenge_data[] __attribute__((sda));
extern s32 D_L05_001B1350_gp[] SDATA(D_L05_001B1350);
extern s32 g_feltzin_reward_table[] SDATA(D_L05_001B13F8);

/* MenuY with label_y's two dead handle tests, for the two sprite rows (allowed by owner ruling,
   7 November 2026, as the dead-test helper). The tests do not change the result; they end blocks
   that allocation and both scheduling passes see. */
static __inline__ s32 MenuSpriteY(void *handle, f32 y, f32 adjustment) {
    f32 scaled = y * g_screen_l05_scale + 0.5f;
    s32 result;
    void *copy;
    if (g_label_mode == 1)
        result = (s32)(scaled + adjustment);
    else
        result = (s32)scaled;
    if (handle != 0)
        scaled = y;
    copy = handle;
    if (copy != 0)
        scaled = adjustment;
    return result;
}
static __inline__ s32 MenuY(f32 y, f32 adjustment) {
    f32 scaled = y * g_screen_l05_scale + 0.5f;
    if (g_label_mode == 1)
        return (s32)(scaled + adjustment);
    return (s32)scaled;
}

/* label_y: the accepted HUD label helper (src/levels/10_hrugis_cloud/L10_00421790-g8.c). */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = g_label_mode;
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

/* label_y3: label_y with the mode test after its two dead handle tests (allowed by owner ruling,
   9 November 2026). */
static __inline__ int label_y3(void *handle, float value, float scale, float half, int active)
{
    int mode = g_label_mode;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;
    if (handle != 0) scaled = scale;
    copy = handle;
    if (copy != 0) scaled = half;
    if (mode == active) scaled = scale;
    return result;
}

/* Draws the mission result menu: the selected mission's title, description and bolt reward,
   or a message that it is still locked, plus the button labels. */
s32 menu_draw_feltzin_mission_result(void) {
    char buf[128];
    f32 center, pulse, imageY;
    s32 sprite, remainder, color, blink, x, headerX, reward;
    char *text;

    center = IntToFloat(g_screen_width) * 0.5f;
    if (g_game_mode_a) return 1;
    if (g_feltzin_mission_data) {
    g_ship_fade_level_b = 0;
    sprite = table_find_by_id(g_feltzin_mission_data + 0x8710, 0x45);
    gfx_draw_scaled_object((void *)sprite, center, (f32)label_y((void *)sprite, 200.0f, g_screen_l05_scale, 0.5f, 1), 0x60442D00, 1.0f, 0.0f);
    sprite = table_find_by_id(g_feltzin_mission_data + 0x8710, 0x44);
    gfx_draw_scaled_object((void *)sprite, center, (f32)label_y((void *)sprite, 200.0f, g_screen_l05_scale, 0.5f, 1), 0x55F0C070, 1.0f, 0.0f);
    remainder = g_feltzin_mission_index % 50;
    if (remainder >= 25) pulse = 1.0f - (remainder - 25) * 0.04f;
    else pulse = remainder * 0.04f;
    blink = FastTweenColor(0x80FFDE8D, 0x60442D00, pulse);
    color = (g_pad_state.buttons & 0x2000) ? 0x80007FFF : blink;
    sprite = table_find_by_id(g_feltzin_mission_data + 0x8710, 0x4A);
    imageY = (f32)MenuSpriteY((void *)sprite, 291.0f, 2.0f);
    gfx_draw_scaled_object_two_axes((char *)sprite, color, 259.0f, imageY, 1.0f, 1.0f, 0.0f);
    color = (g_pad_state.buttons & 0x8000) ? 0x80007FFF : blink;
    sprite = table_find_by_id(g_feltzin_mission_data + 0x8710, 0x4B);
    imageY = (f32)MenuSpriteY((void *)sprite, 291.0f, 2.0f);
    gfx_draw_scaled_object_two_axes((char *)sprite, color, 251.0f, imageY, 1.0f, 1.0f, 0.0f);
    sprintf(buf, GetLocalizedString(0x2F72), g_feltzin_selected_entry + 1);
    headerX = FloatToInt(center);
    { s32 len;
    len = func_001157AC(buf);
    text_draw_centered_large(headerX, 46, 0x80F0F0F0ULL, buf, len); }
    x = FloatToInt(center);
    switch (g_feltzin_selected_entry) {
    case 0:
        text = GetLocalizedString(0x2FD6);
        {
            s32 row = MenuY(101.0f, -2.0f);
            text_draw_centered_small(x, row, 0x80F0F0F0ULL, text, func_001157AC(text));
        }
        text = GetLocalizedString(0x2FDB);
        {
            s32 len;
            s32 row;
            row = label_y(text, 131.0f, g_screen_l05_scale, 0.5f, 1);
            len = func_001157AC(text);
            text_print_wrapped_default(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)text, len);
        }
        {
            s32 index = D_L05_001B1350_gp[0];
            if (index >= 3) index = 2;
            reward = g_feltzin_reward_table[index];
        }
        if (g_extras_unlocked_flag) reward *= 10;
        if (reward) {
        {
            s32 len;
            s32 row;
            do {
                sprintf(buf, GetLocalizedString(0x2FE0), reward);
                row = label_y(buf, 242.0f, g_screen_l05_scale, 0.5f, 1);
            } while (0);
            len = func_001157AC(buf);
            text_print_wrapped_default(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)buf, len);
        }
        }
        text_draw_medium(181, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, GetLocalizedString(0x2F3F), -1);
        break;
    case 1:
        if (D_L05_001B1350_gp[0]) {
            text = GetLocalizedString(0x2FD8);
            {
                s32 row = MenuY(101.0f, -2.0f);
                text_draw_centered_medium(x, row, 0x80F0F0F0ULL, text, func_001157AC(text));
            }
            {
                s32 len;
                s32 row;
                s32 len1, row1;
                text = GetLocalizedString(0x2FDD);
                row1 = label_y(text, 131.0f, g_screen_l05_scale, 0.5f, 1);
                do {
                    len1 = func_001157AC(text);
                    text_print_wrapped_default(117, row1, 280, 400, 0x80F0F0F0ULL, (u8 *)text, len1);
                    {
                        s32 index = g_feltzin_challenge_data[1];
                        if (index >= 3) index = 2;
                        reward = g_feltzin_reward_table_b[index];
                    }
                    if (g_extras_unlocked_flag) reward *= 10;
                    sprintf(buf, GetLocalizedString(0x2FE0), reward);
                    row = label_y3(buf, 242.0f, g_screen_l05_scale, 0.5f, 1);
                } while (0);
                len = func_001157AC(buf);
                text_print_wrapped_default(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)buf, len);
            }
            text_draw_medium(181, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, GetLocalizedString(0x2F3F), -1);
        } else {
            text = GetLocalizedString(0x2F73);
            {
                s32 len;
                s32 row;
                row = label_y((void *)x, 170.0f, g_screen_l05_scale, 0.5f, 1);
                len = func_001157AC(text);
                text_draw_centered_large(x, row, 0x80F0F0F0ULL, text, len);
            }
        }
        break;
    case 2:
        if (D_L05_001B1350_gp[0] && g_feltzin_challenge_data[1]) {
            text = GetLocalizedString(0x2FD7);
            {
                s32 row = MenuY(101.0f, -2.0f);
                text_draw_centered_small(x, row, 0x80F0F0F0ULL, text, func_001157AC(text));
            }
            {
                s32 len;
                s32 row;
                s32 len1, row1;
                text = GetLocalizedString(0x2FDC);
                row1 = label_y(text, 131.0f, g_screen_l05_scale, 0.5f, 1);
                do {
                    len1 = func_001157AC(text);
                    text_print_wrapped_default(117, row1, 280, 400, 0x80F0F0F0ULL, (u8 *)text, len1);
                    {
                        s32 index = g_feltzin_challenge_data[2];
                        if (index >= 3) index = 2;
                        reward = g_feltzin_reward_table_c[index];
                    }
                    if (g_extras_unlocked_flag) reward *= 10;
                    sprintf(buf, GetLocalizedString(0x2FE0), reward);
                    row = label_y3(buf, 242.0f, g_screen_l05_scale, 0.5f, 1);
                } while (0);
                len = func_001157AC(buf);
                text_print_wrapped_default(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)buf, len);
            }
            text_draw_medium(181, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, GetLocalizedString(0x2F3F), -1);
        } else {
            text = GetLocalizedString(0x2F73);
            {
                s32 len;
                s32 row;
                row = label_y((void *)x, 170.0f, g_screen_l05_scale, 0.5f, 1);
                len = func_001157AC(text);
                text_draw_centered_large(x, row, 0x80F0F0F0ULL, text, len);
            }
        }
        break;
    case 3:
        if (D_L05_001B1350_gp[0] && g_feltzin_challenge_data[1] && g_feltzin_challenge_data[2]) {
            text = GetLocalizedString(0x2FDA);
            {
                s32 row = MenuY(101.0f, -2.0f);
                text_draw_centered_small(x, row, 0x80F0F0F0ULL, text, func_001157AC(text));
            }
            text = GetLocalizedString(0x2FDF);
            {
                s32 len;
                s32 row;
                s32 len1, row1;
                row1 = label_y(text, 131.0f, g_screen_l05_scale, 0.5f, 1);
                do {
                    len1 = func_001157AC(text);
                    text_print_wrapped_default(117, row1, 280, 400, 0x80F0F0F0ULL, (u8 *)text, len1);
                    {
                        s32 index = g_feltzin_challenge_data[3];
                        if (index >= 3) index = 2;
                        reward = g_feltzin_reward_table_d[index];
                    }
                    if (g_extras_unlocked_flag) reward *= 10;
                    sprintf(buf, GetLocalizedString(0x2FE0), reward);
                    row = label_y3(buf, 242.0f, g_screen_l05_scale, 0.5f, 1);
                } while (0);
                len = func_001157AC(buf);
                text_print_wrapped_default(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)buf, len);
            }
            text_draw_medium(181, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, GetLocalizedString(0x2F3F), -1);
        } else {
            text = GetLocalizedString(0x2F73);
            {
                s32 len;
                s32 row;
                row = label_y((void *)x, 170.0f, g_screen_l05_scale, 0.5f, 1);
                len = func_001157AC(text);
                text_draw_centered_large(x, row, 0x80F0F0F0ULL, text, len);
            }
        }
        break;
    }
    text_draw_medium(119, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, GetLocalizedString(0x2F40), -1);
    text_draw_medium(356, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, GetLocalizedString(0x2F41), -1);
    text_draw_medium(279, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, GetLocalizedString(0x2F42), -1);
    }
    return 1;
}
