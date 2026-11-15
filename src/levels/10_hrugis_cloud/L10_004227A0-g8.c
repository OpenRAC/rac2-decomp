#include "common.h"

/* func_L10_004227A0: draws a Hrugis Cloud menu panel: two sprites, two button icons, the header
   line, then for the selected entry (D_L10_001B143C) its title, a wrapped text box, the reward
   line and one option label, or a locked-entry line; then three option labels. The same code as
   func_L05_0041EF00 and func_L15_0042EFE0, with this level's data and text ids.

   The row y values go through the HUD label helpers (label_y, label_y3, MenuSpriteY); their tests
   have no effect on the result. Each do-while(0) group holds real statements (allowed,
   docs/build/compiler-notes.md); it ends the scheduling block after the reward row's y. */

extern f32 IntToFloat(s32);
extern s32 FloatToInt(f32);
extern s32 FastTweenColor(s32, s32, f32);
extern s32 table_find_by_id(u8 *, s32);
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
extern u8 D_001A7A0A;
extern s32 D_L10_001A8F00;
extern u8 *D_L10_001A904C;
extern f32 D_L10_001B2D84;
extern s32 D_L10_001B2D80;
extern s32 D_L10_001B2048;
extern s32 D_L10_001B1454[] __attribute__((sda)), D_L10_001B1460[] __attribute__((sda)), D_L10_001B146C[] __attribute__((sda));
extern s32 D_L10_001B1F64 __attribute__((sda));
extern s32 g_selected_mission_index __attribute__((sda));
extern s32 g_mission_completion_counts[] __attribute__((sda));
extern s32 D_L10_001B1390_gp[] SDATA(D_L10_001B1390);
extern s32 D_L10_001B1448[] SDATA(D_L10_001B1448);

/* MenuY with label_y's two dead handle tests, for the two sprite rows (allowed by owner ruling,
   7 November 2026, as the dead-test helper). The tests do not change the result; they end blocks
   that allocation and both scheduling passes see. */
static __inline__ s32 MenuSpriteY(void *handle, f32 y, f32 adjustment) {
    f32 scaled = y * D_L10_001B2D84 + 0.5f;
    s32 result;
    void *copy;
    if (D_L10_001B2D80 == 1)
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
    f32 scaled = y * D_L10_001B2D84 + 0.5f;
    if (D_L10_001B2D80 == 1)
        return (s32)(scaled + adjustment);
    return (s32)scaled;
}

/* label_y: the accepted HUD label helper (src/levels/10_hrugis_cloud/L10_00421790-g8.c). */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L10_001B2D80;
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
    int mode = D_L10_001B2D80;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;
    if (handle != 0) scaled = scale;
    copy = handle;
    if (copy != 0) scaled = half;
    if (mode == active) scaled = scale;
    return result;
}

/* Draws the mission reward menu: the picked mission, its reward text and the coins it pays. */
s32 menu_draw_mission_reward(void) {
    char buf[128];
    f32 center, pulse, imageY;
    s32 sprite, remainder, color, blink, x, headerX, reward;
    char *text;

    center = IntToFloat(g_screen_width) * 0.5f;
    if (D_L10_001A8F00) return 1;
    if (D_L10_001A904C) {
    D_L10_001B1F64 = 0;
    sprite = table_find_by_id(D_L10_001A904C + 0x8710, 0x45);
    gfx_draw_scaled_object((void *)sprite, center, (f32)label_y((void *)sprite, 200.0f, D_L10_001B2D84, 0.5f, 1), 0x60442D00, 1.0f, 0.0f);
    sprite = table_find_by_id(D_L10_001A904C + 0x8710, 0x44);
    gfx_draw_scaled_object((void *)sprite, center, (f32)label_y((void *)sprite, 200.0f, D_L10_001B2D84, 0.5f, 1), 0x55F0C070, 1.0f, 0.0f);
    remainder = D_L10_001B2048 % 50;
    if (remainder >= 25) pulse = 1.0f - (remainder - 25) * 0.04f;
    else pulse = remainder * 0.04f;
    blink = FastTweenColor(0x80FFDE8D, 0x60442D00, pulse);
    color = (g_pad_state.buttons & 0x2000) ? 0x80007FFF : blink;
    sprite = table_find_by_id(D_L10_001A904C + 0x8710, 0x4A);
    imageY = (f32)MenuSpriteY((void *)sprite, 291.0f, 2.0f);
    gfx_draw_scaled_object_two_axes((char *)sprite, color, 259.0f, imageY, 1.0f, 1.0f, 0.0f);
    color = (g_pad_state.buttons & 0x8000) ? 0x80007FFF : blink;
    sprite = table_find_by_id(D_L10_001A904C + 0x8710, 0x4B);
    imageY = (f32)MenuSpriteY((void *)sprite, 291.0f, 2.0f);
    gfx_draw_scaled_object_two_axes((char *)sprite, color, 251.0f, imageY, 1.0f, 1.0f, 0.0f);
    sprintf(buf, GetLocalizedString(0x2F72), g_selected_mission_index + 1);
    headerX = FloatToInt(center);
    { s32 len;
    len = func_001157AC(buf);
    text_draw_centered_large(headerX, 46, 0x80F0F0F0ULL, buf, len); }
    x = FloatToInt(center);
    switch (g_selected_mission_index) {
    case 0:
        text = GetLocalizedString(0x2FE2);
        {
            s32 row = MenuY(101.0f, -2.0f);
            text_draw_centered_medium(x, row, 0x80F0F0F0ULL, text, func_001157AC(text));
        }
        text = GetLocalizedString(0x2FE7);
        {
            s32 len;
            s32 row;
            row = label_y(text, 131.0f, D_L10_001B2D84, 0.5f, 1);
            len = func_001157AC(text);
            text_print_wrapped_default(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)text, len);
        }
        {
            s32 index = D_L10_001B1390_gp[0];
            if (index >= 3) index = 2;
            reward = D_L10_001B1448[index];
        }
        if (D_001A7A0A) reward *= 10;
        if (reward) {
        {
            s32 len;
            s32 row;
            do {
                sprintf(buf, GetLocalizedString(0x2FE0), reward);
                row = label_y(buf, 242.0f, D_L10_001B2D84, 0.5f, 1);
            } while (0);
            len = func_001157AC(buf);
            text_print_wrapped_default(117, row, 280, 400, 0x80F0F0F0ULL, (u8 *)buf, len);
        }
        }
        text_draw_medium(181, MenuY(294.0f, 3.0f), 0x80F0F0F0ULL, GetLocalizedString(0x2F3F), -1);
        break;
    case 1:
        if (D_L10_001B1390_gp[0]) {
            text = GetLocalizedString(0x2FE3);
            {
                s32 row = MenuY(101.0f, -2.0f);
                text_draw_centered_small(x, row, 0x80F0F0F0ULL, text, func_001157AC(text));
            }
            {
                s32 len;
                s32 row;
                s32 len1, row1;
                text = GetLocalizedString(0x2FE8);
                row1 = label_y(text, 131.0f, D_L10_001B2D84, 0.5f, 1);
                do {
                    len1 = func_001157AC(text);
                    text_print_wrapped_default(117, row1, 280, 400, 0x80F0F0F0ULL, (u8 *)text, len1);
                    {
                        s32 index = g_mission_completion_counts[1];
                        if (index >= 3) index = 2;
                        reward = D_L10_001B1454[index];
                    }
                    if (D_001A7A0A) reward *= 10;
                    sprintf(buf, GetLocalizedString(0x2FE0), reward);
                    row = label_y3(buf, 242.0f, D_L10_001B2D84, 0.5f, 1);
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
                row = label_y((void *)x, 170.0f, D_L10_001B2D84, 0.5f, 1);
                len = func_001157AC(text);
                text_draw_centered_large(x, row, 0x80F0F0F0ULL, text, len);
            }
        }
        break;
    case 2:
        if (D_L10_001B1390_gp[0] && g_mission_completion_counts[1]) {
            text = GetLocalizedString(0x2FE5);
            {
                s32 row = MenuY(101.0f, -2.0f);
                text_draw_centered_medium(x, row, 0x80F0F0F0ULL, text, func_001157AC(text));
            }
            {
                s32 len;
                s32 row;
                s32 len1, row1;
                text = GetLocalizedString(0x2FE9);
                row1 = label_y(text, 131.0f, D_L10_001B2D84, 0.5f, 1);
                do {
                    len1 = func_001157AC(text);
                    text_print_wrapped_default(117, row1, 280, 400, 0x80F0F0F0ULL, (u8 *)text, len1);
                    {
                        s32 index = g_mission_completion_counts[2];
                        if (index >= 3) index = 2;
                        reward = D_L10_001B1460[index];
                    }
                    if (D_001A7A0A) reward *= 10;
                    sprintf(buf, GetLocalizedString(0x2FE0), reward);
                    row = label_y3(buf, 242.0f, D_L10_001B2D84, 0.5f, 1);
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
                row = label_y((void *)x, 170.0f, D_L10_001B2D84, 0.5f, 1);
                len = func_001157AC(text);
                text_draw_centered_large(x, row, 0x80F0F0F0ULL, text, len);
            }
        }
        break;
    case 3:
        if (D_L10_001B1390_gp[0] && g_mission_completion_counts[1] && g_mission_completion_counts[2]) {
            text = GetLocalizedString(0x2FE6);
            {
                s32 row = MenuY(101.0f, -2.0f);
                text_draw_centered_medium(x, row, 0x80F0F0F0ULL, text, func_001157AC(text));
            }
            text = GetLocalizedString(0x2FEB);
            {
                s32 len;
                s32 row;
                s32 len1, row1;
                row1 = label_y(text, 131.0f, D_L10_001B2D84, 0.5f, 1);
                do {
                    len1 = func_001157AC(text);
                    text_print_wrapped_default(117, row1, 280, 400, 0x80F0F0F0ULL, (u8 *)text, len1);
                    {
                        s32 index = g_mission_completion_counts[3];
                        if (index >= 3) index = 2;
                        reward = D_L10_001B146C[index];
                    }
                    if (D_001A7A0A) reward *= 10;
                    sprintf(buf, GetLocalizedString(0x2FE0), reward);
                    row = label_y3(buf, 242.0f, D_L10_001B2D84, 0.5f, 1);
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
                row = label_y((void *)x, 170.0f, D_L10_001B2D84, 0.5f, 1);
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
