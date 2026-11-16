#include "common.h"

/* func_US2_L05_00420420, the v2.00 copy of func_L05_0041EF00 (src/levels/05_feltzin_system/L05_0041EF00-g8.c): draws this level's menu panel
   (two sprites, two button icons, the header line, the selected entry's title, text box,
   reward line and option label or a locked-entry line, then three option labels).
   v2.00's changes: its own text ids, and the entry option label's x depends on the
   language byte (168 for 5, 164 for 4, 160 for 2, 181 otherwise). Entry 1 draws its title with func_L08_002F5CB8 at scale 0.85 (y 102.0, offset -1.0); entry 3 uses func_0027FB40 when the language byte is 3.

   The language byte is read as D_001A7BB0[4] (as in func_US2_0034E8D8): an element at an
   offset is a two-word load, which keeps it out of the entry-0 reward branch's delay slot
   as in retail (docs/contributing/matching-blockers.md). The y values go through the HUD
   label helpers, whose tests have no effect on the result; each do-while(0) group holds
   real statements. The unit builds with -malign-loops=2. */

extern s32 g_screen_width MACRO_ADDR;
extern s32 g_hero_mode_state MACRO_ADDR;
extern u8 g_extras_unlocked_flag MACRO_ADDR;
extern u8 g_language_settings[] __attribute__((sda)); /* the language byte is [4] */
extern s32 g_pad_state[];
extern u8 *g_feltzin_mission_data MACRO_ADDR;
extern f32 g_screen_l05_scale;
extern s32 g_label_mode MACRO_ADDR;
extern f32 D_L05_001B2D84_gp SDATA(D_L05_001B2D84);
extern s32 D_L05_001B2D80_gp SDATA(D_L05_001B2D80);
extern s32 g_feltzin_mission_index MACRO_ADDR;
extern s32 g_ship_fade_level_b __attribute__((sda));
extern s32 g_feltzin_selected_entry __attribute__((sda));
extern s32 g_feltzin_challenge_data[] MACRO_ADDR;
extern s32 g_feltzin_reward_table[][3] MACRO_ADDR;
extern s32 D_L05_001B1350_gp[] SDATA(D_L05_001B1350);
extern s32 D_L05_001B13F8_gp[][3] SDATA(D_L05_001B13F8);

extern f32 IntToFloat(s32);
extern s32 FloatToInt(f32);
extern u32 FastTweenColor(u32, u32, f32);
extern void *table_find_by_id(void *, s32);
extern void gfx_draw_scaled_object(void *, f32, f32, s32, f32, f32);
extern void gfx_draw_scaled_object_two_axes(void *, s32, f32, f32, f32, f32, f32);
extern char *GetLocalizedString(s32);
extern s32 sprintf(char *, char *, ...);
extern s32 func_001157AC(char *);
extern s32 text_draw_centered_large(s32, s32, u64, char *, s32);
extern s32 text_draw_centered_small(s32, s32, u64, char *, s32);
extern s32 text_draw_centered_medium(s32, s32, u64, char *, s32);
extern void DrawCenteredScaledText(s32, s32, u64, void *, s32, f32);
extern s32 text_print_wrapped_default(s32, s32, s32, s32, u64, u8 *, s32);
extern void text_draw_medium(s32, s32, u64, char *, s32);

static __inline__ s32 screen_coord(s32 mode, f32 value, f32 offset)
{
    f32 scaled = value * g_screen_l05_scale + 0.5f;

    if (mode == 1)
        return (s32)(scaled + offset);
    return (s32)scaled;
}

static __inline__ s32 screen_coord_gp(s32 mode, f32 value, f32 offset)
{
    f32 scaled = value * D_L05_001B2D84_gp + 0.5f;

    if (mode == 1)
        return (s32)(scaled + offset);
    return (s32)scaled;
}

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

static __inline__ int label_y3(void *handle, float value, float scale, float half, int active)
{
    int mode = g_label_mode;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    if (mode == active)
        scaled = scale;
    return result;
}

static __inline__ s32 sprite_y(void *handle, f32 y, f32 adjustment)
{
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

s32 menu_draw_feltzin_mission_result_us2(void) {
    char buf[128];
    f32 center, fade, image_y;
    void *sprite;
    char *text;
    s32 x, y, t, hx;
    s32 count;
    u32 blend, color;

    center = IntToFloat(g_screen_width) * 0.5f;
    if (g_hero_mode_state != 0)
        return 1;
    if (g_feltzin_mission_data != 0) {
        g_ship_fade_level_b = 0;
        sprite = table_find_by_id(g_feltzin_mission_data + 0x8710, 0x45);
        gfx_draw_scaled_object(sprite, center, (f32)label_y(sprite, 200.0f, g_screen_l05_scale, 0.5f, 1), 0x60442D00, 1.0f, 0.0f);
        sprite = table_find_by_id(g_feltzin_mission_data + 0x8710, 0x44);
        gfx_draw_scaled_object(sprite, center, (f32)label_y(sprite, 200.0f, g_screen_l05_scale, 0.5f, 1), 0x55F0C070, 1.0f, 0.0f);
        t = g_feltzin_mission_index % 50;
        if (t >= 25)
            fade = 1.0f - (f32)(t - 25) * 0.04f;
        else
            fade = (f32)t * 0.04f;
        blend = FastTweenColor(0x80FFDE8D, 0x60442D00, fade);
        color = (g_pad_state[0x68] & 0x2000) ? 0x80007FFF : blend;
        sprite = table_find_by_id(g_feltzin_mission_data + 0x8710, 0x4A);
        image_y = (f32)sprite_y(sprite, 291.0f, 2.0f);
        gfx_draw_scaled_object_two_axes(sprite, color, 259.0f, image_y, 1.0f, 1.0f, 0.0f);
        color = (g_pad_state[0x68] & 0x8000) ? 0x80007FFF : blend;
        sprite = table_find_by_id(g_feltzin_mission_data + 0x8710, 0x4B);
        image_y = (f32)sprite_y(sprite, 291.0f, 2.0f);
        gfx_draw_scaled_object_two_axes(sprite, color, 251.0f, image_y, 1.0f, 1.0f, 0.0f);
        sprintf(buf, GetLocalizedString(0x2E08), g_feltzin_selected_entry + 1);
        {
            s32 len;

            hx = FloatToInt(center);
            len = func_001157AC(buf);
            text_draw_centered_large(hx, 46, 0x80F0F0F0, buf, len);
        }
        x = FloatToInt(center);
        switch (g_feltzin_selected_entry) {
        case 0:
        {
            s32 index;

            text = GetLocalizedString(0x2E6C);
            y = screen_coord(g_label_mode, 101.0f, -2.0f);
            text_draw_centered_small(x, y, 0x80F0F0F0, text, func_001157AC(text));
            text = GetLocalizedString(0x2E71);
            {
                s32 ty = label_y(text, 131.0f, g_screen_l05_scale, 0.5f, 1);
                text_print_wrapped_default(117, ty, 280, 400, 0x80F0F0F0, (u8 *)text, func_001157AC(text));
            }
            index = D_L05_001B1350_gp[0];
            if (index >= 3)
                index = 2;
            count = D_L05_001B13F8_gp[0][index];
            if (g_extras_unlocked_flag != 0)
                count *= 10;
            if (count != 0) {
                s32 len, ty;
                do {
                    sprintf(buf, GetLocalizedString(0x2E76), count);
                    ty = label_y(buf, 242.0f, g_screen_l05_scale, 0.5f, 1);
                } while (0);
                len = func_001157AC(buf);
                text_print_wrapped_default(117, ty, 280, 400, 0x80F0F0F0, (u8 *)buf, len);
            }
            if (g_language_settings[4] == 5) {
                text_draw_medium(168, screen_coord(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0x2DD5), -1);
            } else if (g_language_settings[4] == 4) {
                text_draw_medium(164, screen_coord(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0x2DD5), -1);
            } else if (g_language_settings[4] == 2) {
                text_draw_medium(160, screen_coord(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0x2DD5), -1);
            } else {
                text_draw_medium(181, screen_coord(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0x2DD5), -1);
            }
        }
            break;
        case 1:
            if (D_L05_001B1350_gp[0] != 0) {
                s32 index;
    
                text = GetLocalizedString(0x2E6E);
                y = screen_coord(g_label_mode, 102.0f, -1.0f);
                DrawCenteredScaledText(x, y, 0x80F0F0F0, text, func_001157AC(text), 0.85f);
                text = GetLocalizedString(0x2E73);
                {
                    s32 len, ty, len1, ty1;
                    ty1 = label_y(text, 131.0f, g_screen_l05_scale, 0.5f, 1);
                    do {
                        len1 = func_001157AC(text);
                        text_print_wrapped_default(117, ty1, 280, 400, 0x80F0F0F0, (u8 *)text, len1);
                        index = g_feltzin_challenge_data[1];
                        if (index >= 3)
                            index = 2;
                        count = g_feltzin_reward_table[1][index];
                        if (g_extras_unlocked_flag != 0)
                            count *= 10;
                        sprintf(buf, GetLocalizedString(0x2E76), count);
                        ty = label_y3(buf, 242.0f, g_screen_l05_scale, 0.5f, 1);
                    } while (0);
                    len = func_001157AC(buf);
                    text_print_wrapped_default(117, ty, 280, 400, 0x80F0F0F0, (u8 *)buf, len);
                }
                if (g_language_settings[4] == 5) {
                    text_draw_medium(168, screen_coord(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0x2DD5), -1);
                } else if (g_language_settings[4] == 4) {
                    text_draw_medium(164, screen_coord_gp(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0x2DD5), -1);
                } else if (g_language_settings[4] == 2) {
                    text_draw_medium(160, screen_coord(D_L05_001B2D80_gp, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0x2DD5), -1);
                } else {
                    text_draw_medium(181, screen_coord(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0x2DD5), -1);
                }
            } else {
                text = GetLocalizedString(0x2E09);
                text_draw_centered_large(x, label_y(text, 170.0f, g_screen_l05_scale, 0.5f, 1), 0x80F0F0F0, text, func_001157AC(text));
            }
            break;
        case 2:
            if (D_L05_001B1350_gp[0] != 0 && g_feltzin_challenge_data[1] != 0) {
                s32 index;
    
                text = GetLocalizedString(0x2E6D);
                y = screen_coord(g_label_mode, 101.0f, -2.0f);
                text_draw_centered_small(x, y, 0x80F0F0F0, text, func_001157AC(text));
                text = GetLocalizedString(0x2E72);
                {
                    s32 len, ty, len1, ty1;
                    ty1 = label_y(text, 131.0f, g_screen_l05_scale, 0.5f, 1);
                    do {
                        len1 = func_001157AC(text);
                        text_print_wrapped_default(117, ty1, 280, 400, 0x80F0F0F0, (u8 *)text, len1);
                        index = g_feltzin_challenge_data[2];
                        if (index >= 3)
                            index = 2;
                        count = g_feltzin_reward_table[2][index];
                        if (g_extras_unlocked_flag != 0)
                            count *= 10;
                        sprintf(buf, GetLocalizedString(0x2E76), count);
                        ty = label_y3(buf, 242.0f, g_screen_l05_scale, 0.5f, 1);
                    } while (0);
                    len = func_001157AC(buf);
                    text_print_wrapped_default(117, ty, 280, 400, 0x80F0F0F0, (u8 *)buf, len);
                }
                if (g_language_settings[4] == 5) {
                    text_draw_medium(168, screen_coord(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0x2DD5), -1);
                } else if (g_language_settings[4] == 4) {
                    text_draw_medium(164, screen_coord_gp(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0x2DD5), -1);
                } else if (g_language_settings[4] == 2) {
                    text_draw_medium(160, screen_coord(D_L05_001B2D80_gp, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0x2DD5), -1);
                } else {
                    text_draw_medium(181, screen_coord(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0x2DD5), -1);
                }
            } else {
                text = GetLocalizedString(0x2E09);
                text_draw_centered_large(x, label_y(text, 170.0f, g_screen_l05_scale, 0.5f, 1), 0x80F0F0F0, text, func_001157AC(text));
            }
            break;
        case 3:
            if (D_L05_001B1350_gp[0] != 0 && g_feltzin_challenge_data[1] != 0 && g_feltzin_challenge_data[2] != 0) {
                s32 index;
    
                text = GetLocalizedString(0x2E70);
                if (g_language_settings[4] == 3) {
                    y = screen_coord(g_label_mode, 101.0f, -2.0f);
                    text_draw_centered_medium(x, y, 0x80F0F0F0, text, func_001157AC(text));
                } else {
                    y = screen_coord(g_label_mode, 101.0f, -2.0f);
                    text_draw_centered_small(x, y, 0x80F0F0F0, text, func_001157AC(text));
                }
                text = GetLocalizedString(0x2E75);
                {
                    s32 len, ty, len1, ty1;
                    ty1 = label_y(text, 131.0f, g_screen_l05_scale, 0.5f, 1);
                    do {
                        len1 = func_001157AC(text);
                        text_print_wrapped_default(117, ty1, 280, 400, 0x80F0F0F0, (u8 *)text, len1);
                        index = g_feltzin_challenge_data[3];
                        if (index >= 3)
                            index = 2;
                        count = g_feltzin_reward_table[3][index];
                        if (g_extras_unlocked_flag != 0)
                            count *= 10;
                        sprintf(buf, GetLocalizedString(0x2E76), count);
                        ty = label_y3(buf, 242.0f, g_screen_l05_scale, 0.5f, 1);
                    } while (0);
                    len = func_001157AC(buf);
                    text_print_wrapped_default(117, ty, 280, 400, 0x80F0F0F0, (u8 *)buf, len);
                }
                if (g_language_settings[4] == 5) {
                    text_draw_medium(168, screen_coord(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0x2DD5), -1);
                } else if (g_language_settings[4] == 4) {
                    text_draw_medium(164, screen_coord_gp(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0x2DD5), -1);
                } else if (g_language_settings[4] == 2) {
                    text_draw_medium(160, screen_coord_gp(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0x2DD5), -1);
                } else {
                    text_draw_medium(181, screen_coord_gp(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0x2DD5), -1);
                }
            } else {
                text = GetLocalizedString(0x2E09);
                text_draw_centered_large(x, label_y(text, 170.0f, g_screen_l05_scale, 0.5f, 1), 0x80F0F0F0, text, func_001157AC(text));
            }
            break;
        }
        text_draw_medium(119, screen_coord(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0x2DD6), -1);
        text_draw_medium(356, screen_coord(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0x2DD7), -1);
        if (g_language_settings[4] == 5)
            text_draw_medium(285, screen_coord(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0x2DD8), -1);
        else
            text_draw_medium(279, screen_coord(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0x2DD8), -1);
    }
    return 1;
}
