#include "common.h"

/* func_PAL_L05_00423C50: the PAL copy of v2.00's func_US2_L05_00420420 (src/us2/levels/
   05_feltzin_system/L05_00420420-g8.c), itself the v2.00 copy of func_L05_0041EF00: draws this
   level's menu panel (two sprites, two button icons, the header line, the selected entry's title,
   text box, reward line and option label or a locked-entry line, then three option labels). The
   same C and flags, with PAL's text ids and entry titles drawn by PAL's language byte
   D_PAL_001A7C3C: entry 0's with func_0027FB40 for 3, entry 2's for 2, 3 and 5, else with
   func_0027FAA8; entry 1's with func_L08_002F5CB8 at 0.85 (y 101, one pixel up in display mode 1)
   for 4, 5, 0 and 1, func_0027FB40 for 3 and func_0027FAA8 otherwise, held in a block-local
   title. Entry 3's keeps v2.00's language-3 choice.

   As in v2.00, the language byte of the option labels and entry 3's title is read as
   D_001A7BB0[4]: an element at an offset is a two-word load, which keeps it out of the entry-0
   reward branch's delay slot (docs/contributing/matching-blockers.md). The y values go through the
   HUD label helpers, whose tests have no effect on the result; each do-while(0) group holds real
   statements. The unit builds with -malign-loops=2. */

extern s32 g_screen_width MACRO_ADDR;
extern s32 g_hero_mode_state MACRO_ADDR;
extern u8 g_extras_unlocked_flag MACRO_ADDR;
extern u8 g_language_settings[] __attribute__((sda)); /* the language byte is [4] */
extern unsigned char g_pal_region_mode;
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

s32 menu_draw_feltzin_mission_result_pal(void) {
    char buf[128];
    f32 center, fade, image_y;
    void *sprite;
    char *text;
    s32 center_x, title_y, phase, header_x;
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
        phase = g_feltzin_mission_index % 50;
        if (phase >= 25)
            fade = 1.0f - (f32)(phase - 25) * 0.04f;
        else
            fade = (f32)phase * 0.04f;
        blend = FastTweenColor(0x80FFDE8D, 0x60442D00, fade);
        color = (g_pad_state[0x68] & 0x2000) ? 0x80007FFF : blend;
        sprite = table_find_by_id(g_feltzin_mission_data + 0x8710, 0x4A);
        image_y = (f32)sprite_y(sprite, 291.0f, 2.0f);
        gfx_draw_scaled_object_two_axes(sprite, color, 259.0f, image_y, 1.0f, 1.0f, 0.0f);
        color = (g_pad_state[0x68] & 0x8000) ? 0x80007FFF : blend;
        sprite = table_find_by_id(g_feltzin_mission_data + 0x8710, 0x4B);
        image_y = (f32)sprite_y(sprite, 291.0f, 2.0f);
        gfx_draw_scaled_object_two_axes(sprite, color, 251.0f, image_y, 1.0f, 1.0f, 0.0f);
        sprintf(buf, GetLocalizedString(0xE97), g_feltzin_selected_entry + 1);
        {
            s32 len;

            header_x = FloatToInt(center);
            len = func_001157AC(buf);
            text_draw_centered_large(header_x, 46, 0x80F0F0F0, buf, len);
        }
        center_x = FloatToInt(center);
        switch (g_feltzin_selected_entry) {
        case 0:
        {
            s32 index;

            text = GetLocalizedString(0xEFA);
            if (g_pal_region_mode == 3) {
                text_draw_centered_medium(center_x, screen_coord(g_label_mode, 101.0f, -2.0f), 0x80F0F0F0, text, func_001157AC(text));
            } else {
                text_draw_centered_small(center_x, screen_coord(g_label_mode, 101.0f, -2.0f), 0x80F0F0F0, text, func_001157AC(text));
            }
            text = GetLocalizedString(0xEFF);
            {
                s32 text_y = label_y(text, 131.0f, g_screen_l05_scale, 0.5f, 1);
                text_print_wrapped_default(117, text_y, 280, 400, 0x80F0F0F0, (u8 *)text, func_001157AC(text));
            }
            index = D_L05_001B1350_gp[0];
            if (index >= 3)
                index = 2;
            count = D_L05_001B13F8_gp[0][index];
            if (g_extras_unlocked_flag != 0)
                count *= 10;
            if (count != 0) {
                s32 len, text_y;
                do {
                    sprintf(buf, GetLocalizedString(0xF04), count);
                    text_y = label_y(buf, 242.0f, g_screen_l05_scale, 0.5f, 1);
                } while (0);
                len = func_001157AC(buf);
                text_print_wrapped_default(117, text_y, 280, 400, 0x80F0F0F0, (u8 *)buf, len);
            }
            if (g_language_settings[4] == 5) {
                text_draw_medium(168, screen_coord(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0xE64), -1);
            } else if (g_language_settings[4] == 4) {
                text_draw_medium(164, screen_coord(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0xE64), -1);
            } else if (g_language_settings[4] == 2) {
                text_draw_medium(160, screen_coord(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0xE64), -1);
            } else {
                text_draw_medium(181, screen_coord(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0xE64), -1);
            }
        }
            break;
        case 1:
            if (D_L05_001B1350_gp[0] != 0) {
                s32 index;
    
                {
                    char *title = GetLocalizedString(0xEFC);

                    if (g_pal_region_mode == 4 || g_pal_region_mode == 5 || g_pal_region_mode == 0 || g_pal_region_mode == 1) {
                        title_y = screen_coord(g_label_mode, 101.0f, -1.0f);
                        DrawCenteredScaledText(center_x, title_y, 0x80F0F0F0, title, func_001157AC(title), 0.85f);
                    } else if (g_pal_region_mode == 3) {
                        title_y = screen_coord(g_label_mode, 101.0f, -2.0f);
                        text_draw_centered_medium(center_x, title_y, 0x80F0F0F0, title, func_001157AC(title));
                    } else {
                        title_y = screen_coord(g_label_mode, 101.0f, -2.0f);
                        text_draw_centered_small(center_x, title_y, 0x80F0F0F0, title, func_001157AC(title));
                    }
                }
                text = GetLocalizedString(0xF01);
                {
                    s32 len, text_y, len1, text_y1;
                    text_y1 = label_y(text, 131.0f, g_screen_l05_scale, 0.5f, 1);
                    do {
                        len1 = func_001157AC(text);
                        text_print_wrapped_default(117, text_y1, 280, 400, 0x80F0F0F0, (u8 *)text, len1);
                        index = g_feltzin_challenge_data[1];
                        if (index >= 3)
                            index = 2;
                        count = g_feltzin_reward_table[1][index];
                        if (g_extras_unlocked_flag != 0)
                            count *= 10;
                        sprintf(buf, GetLocalizedString(0xF04), count);
                        text_y = label_y3(buf, 242.0f, g_screen_l05_scale, 0.5f, 1);
                    } while (0);
                    len = func_001157AC(buf);
                    text_print_wrapped_default(117, text_y, 280, 400, 0x80F0F0F0, (u8 *)buf, len);
                }
                if (g_language_settings[4] == 5) {
                    text_draw_medium(168, screen_coord(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0xE64), -1);
                } else if (g_language_settings[4] == 4) {
                    text_draw_medium(164, screen_coord_gp(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0xE64), -1);
                } else if (g_language_settings[4] == 2) {
                    text_draw_medium(160, screen_coord(D_L05_001B2D80_gp, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0xE64), -1);
                } else {
                    text_draw_medium(181, screen_coord(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0xE64), -1);
                }
            } else {
                text = GetLocalizedString(0xE98);
                text_draw_centered_large(center_x, label_y(text, 170.0f, g_screen_l05_scale, 0.5f, 1), 0x80F0F0F0, text, func_001157AC(text));
            }
            break;
        case 2:
            if (D_L05_001B1350_gp[0] != 0 && g_feltzin_challenge_data[1] != 0) {
                s32 index;
    
                text = GetLocalizedString(0xEFB);
                if (g_pal_region_mode == 2 || g_pal_region_mode == 3 || g_pal_region_mode == 5) {
                    text_draw_centered_medium(center_x, screen_coord(g_label_mode, 101.0f, -2.0f), 0x80F0F0F0, text, func_001157AC(text));
                } else {
                    text_draw_centered_small(center_x, screen_coord(g_label_mode, 101.0f, -2.0f), 0x80F0F0F0, text, func_001157AC(text));
                }
                text = GetLocalizedString(0xF00);
                {
                    s32 len, text_y, len1, text_y1;
                    text_y1 = label_y(text, 131.0f, g_screen_l05_scale, 0.5f, 1);
                    do {
                        len1 = func_001157AC(text);
                        text_print_wrapped_default(117, text_y1, 280, 400, 0x80F0F0F0, (u8 *)text, len1);
                        index = g_feltzin_challenge_data[2];
                        if (index >= 3)
                            index = 2;
                        count = g_feltzin_reward_table[2][index];
                        if (g_extras_unlocked_flag != 0)
                            count *= 10;
                        sprintf(buf, GetLocalizedString(0xF04), count);
                        text_y = label_y3(buf, 242.0f, g_screen_l05_scale, 0.5f, 1);
                    } while (0);
                    len = func_001157AC(buf);
                    text_print_wrapped_default(117, text_y, 280, 400, 0x80F0F0F0, (u8 *)buf, len);
                }
                if (g_language_settings[4] == 5) {
                    text_draw_medium(168, screen_coord(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0xE64), -1);
                } else if (g_language_settings[4] == 4) {
                    text_draw_medium(164, screen_coord_gp(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0xE64), -1);
                } else if (g_language_settings[4] == 2) {
                    text_draw_medium(160, screen_coord(D_L05_001B2D80_gp, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0xE64), -1);
                } else {
                    text_draw_medium(181, screen_coord(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0xE64), -1);
                }
            } else {
                text = GetLocalizedString(0xE98);
                text_draw_centered_large(center_x, label_y(text, 170.0f, g_screen_l05_scale, 0.5f, 1), 0x80F0F0F0, text, func_001157AC(text));
            }
            break;
        case 3:
            if (D_L05_001B1350_gp[0] != 0 && g_feltzin_challenge_data[1] != 0 && g_feltzin_challenge_data[2] != 0) {
                s32 index;
    
                text = GetLocalizedString(0xEFE);
                if (g_language_settings[4] == 3) {
                    title_y = screen_coord(g_label_mode, 101.0f, -2.0f);
                    text_draw_centered_medium(center_x, title_y, 0x80F0F0F0, text, func_001157AC(text));
                } else {
                    title_y = screen_coord(g_label_mode, 101.0f, -2.0f);
                    text_draw_centered_small(center_x, title_y, 0x80F0F0F0, text, func_001157AC(text));
                }
                text = GetLocalizedString(0xF03);
                {
                    s32 len, text_y, len1, text_y1;
                    text_y1 = label_y(text, 131.0f, g_screen_l05_scale, 0.5f, 1);
                    do {
                        len1 = func_001157AC(text);
                        text_print_wrapped_default(117, text_y1, 280, 400, 0x80F0F0F0, (u8 *)text, len1);
                        index = g_feltzin_challenge_data[3];
                        if (index >= 3)
                            index = 2;
                        count = g_feltzin_reward_table[3][index];
                        if (g_extras_unlocked_flag != 0)
                            count *= 10;
                        sprintf(buf, GetLocalizedString(0xF04), count);
                        text_y = label_y3(buf, 242.0f, g_screen_l05_scale, 0.5f, 1);
                    } while (0);
                    len = func_001157AC(buf);
                    text_print_wrapped_default(117, text_y, 280, 400, 0x80F0F0F0, (u8 *)buf, len);
                }
                if (g_language_settings[4] == 5) {
                    text_draw_medium(168, screen_coord(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0xE64), -1);
                } else if (g_language_settings[4] == 4) {
                    text_draw_medium(164, screen_coord_gp(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0xE64), -1);
                } else if (g_language_settings[4] == 2) {
                    text_draw_medium(160, screen_coord_gp(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0xE64), -1);
                } else {
                    text_draw_medium(181, screen_coord_gp(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0xE64), -1);
                }
            } else {
                text = GetLocalizedString(0xE98);
                text_draw_centered_large(center_x, label_y(text, 170.0f, g_screen_l05_scale, 0.5f, 1), 0x80F0F0F0, text, func_001157AC(text));
            }
            break;
        }
        text_draw_medium(119, screen_coord(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0xE65), -1);
        text_draw_medium(356, screen_coord(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0xE66), -1);
        if (g_language_settings[4] == 5)
            text_draw_medium(285, screen_coord(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0xE67), -1);
        else
            text_draw_medium(279, screen_coord(g_label_mode, 294.0f, 3.0f), 0x80F0F0F0, GetLocalizedString(0xE67), -1);
    }
    return 1;
}
