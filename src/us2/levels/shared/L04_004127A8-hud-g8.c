#include "names.h"
/* func_US2_L04_004127A8, the USA v2.00 copy of func_L04_00411298 (the race HUD: lap panels, record
 * time and the ranking list): the same C, where the lap cap becomes 3, the text ids move
 * (0x2F93 -> 0x2E29, 0x2FC6 -> 0x2E5C, 0x2F7F/0x2F80/0x2F81 -> 0x2E15/0x2E16/0x2E17,
 * 0x2F42 -> 0x2DD8, 0x2FB0 -> 0x2E46, 0x2F83 -> 0x2E19 in all four places), the bottom label is
 * drawn with func_0027FA10 at x 390 instead of func_0027F5B8 at 339, and the last row's time sits
 * at x 196 instead of 220. It needs -G8, so it has a unit of its own.
 * label_y and hud_coord are the template's HUD rounding helpers with dead display-mode tests
 * (allowed by owner ruling). The ranking list's 175 row passes the colour as label_y's handle (an
 * int cast to (void *), allowed by owner ruling) and `one`, a local holding 1, as `active` (allowed
 * by owner ruling); a literal 1 there is shared by cse with the later D_L04_001B0A24 == 1 test.
 * `half` holds the 0.5f rounding offset per row, so loop.c does not hoist it. */
#include "common.h"

extern u8 *g_race_controller __attribute__((sda));
extern s32 g_race_extra_ticks __attribute__((sda));
extern s32 g_current_race_index __attribute__((sda));
extern s32 g_race_hud_message_timer __attribute__((sda));
extern s32 g_race_status_message_phase __attribute__((sda));
extern s32 g_hud_top_scroll_stopped __attribute__((sda));
extern s32 g_hud_bottom_scroll_stopped __attribute__((sda));
extern s32 g_hud_racer_ahead_flag __attribute__((sda));
extern f32 g_hud_top_scroll_pos __attribute__((sda));
extern f32 g_hud_bottom_scroll_pos __attribute__((sda));
extern f32 g_race_hud_layout_scale;
extern s32 g_race_time_ticks;
extern s32 g_screen_width, g_is_pal_video;
extern u8 g_extras_unlocked_flag;
extern u8 *g_popup_resource_table;
typedef struct { u8 pad[0xB0]; f32 tangent; } HudCamera;
extern HudCamera g_water_camera;
typedef struct { s32 pad[2]; s32 times[14]; } RecordRow;
extern RecordRow g_race_challenge_table[] NOT_SDA;
extern s32 g_race_rank_string_ids[] NOT_SDA;
extern char g_str_race_label_format[] NOT_SDA, g_str_race_rank_format[] NOT_SDA;
extern char g_str_race_message_format_a[] NOT_SDA, g_str_race_message_format_b[] NOT_SDA;
extern char g_str_race_message_format_c[] NOT_SDA, g_str_race_message_format_d[] NOT_SDA;
extern char g_str_race_time_format[] NOT_SDA, g_str_race_time_format_alt[] NOT_SDA;
extern f32 math_fast_sin_or_cos_a(f32), math_fast_sin_or_cos_b(f32);
extern void UpdateViewContext(void);
extern s32 race_get_course_win_count(s32);
extern void *table_find_by_id(void *, s32);
extern void gfx_draw_scaled_object_two_axes(void *, s32, f32, f32, f32, f32, f32);
extern char *GetLocalizedString(s32);
extern s32 func_001157AC(char *);
extern s32 sprintf(char *, char *, ...);
extern s32 text_draw_centered_small(s32, s32, u64, char *, s32);
extern void text_draw_medium(s32, s32, u64, char *, s32);
extern void text_draw_right_aligned_medium(s32, s32, u64, char *, s32);
extern s32 text_draw_centered_medium(s32, s32, u64, char *, s32);
extern s32 FastTweenColor(s32, s32, f32);
extern s32 PlayMobySound(s32, s32, void *);
extern void VU1_addGSregister(u32, u64);

extern int g_race_hud_mode;
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = g_race_hud_mode;
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

static __inline__ int hud_coord(float value, float scale, float half)
{
    int mode = g_race_hud_mode;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;

    if (mode == 1)
        scaled = scale;
    if (result != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    return result;
}

s32 DrawRaceStandingsHud_us2(void) {
    char text[64];
    u8 *object = g_race_controller;
    u8 *state = *(u8 **)(object + 0x68);
    s32 row = 0, bottom, ahead, playerSeen = 0;
    s32 rank, time, y, lap, flag;
    u8 *racer;
    f32 alpha, fy, angle, fade;
    char *str, *str2, *str3;
    void *sprite;
    f32 fbottom;
    s32 color1, color2;
    s32 color;
    f32 half;
    s32 one;
    if (g_race_extra_ticks < 10) g_hud_racer_ahead_flag = 0;
    if (*(s32 *)(state + 0x320) >= 10) {
        if (g_race_extra_ticks < 601) {
            g_hud_top_scroll_pos = 0;
            g_hud_bottom_scroll_pos = 0;
            g_hud_top_scroll_stopped = 0;
            g_hud_bottom_scroll_stopped = 0;
            goto tick;
        }
        goto animate;
    }
    if (g_hud_racer_ahead_flag) {
animate:
        if (!g_hud_top_scroll_stopped) g_hud_top_scroll_pos += 0.41666669f;
        if (!g_hud_bottom_scroll_stopped) g_hud_bottom_scroll_pos += 0.41666669f;
    } else {
        g_hud_top_scroll_pos = 0;
        g_hud_bottom_scroll_pos = 0;
        g_hud_top_scroll_stopped = 0;
        g_hud_bottom_scroll_stopped = 0;
    }
tick:
    if (g_race_extra_ticks % 15 == 0) {
        g_race_status_message_phase++;
        if (g_race_status_message_phase >= 4) g_race_status_message_phase = 0;
    }
    angle = 0.56217057f;
    g_water_camera.tangent = math_fast_sin_or_cos_b(angle) / math_fast_sin_or_cos_a(angle);
    UpdateViewContext();
    flag = *(s32 *)(state + 0x320);
    if (flag == 1) {
        lap = race_get_course_win_count(g_current_race_index);
        if (lap > 3) lap = 3;
        sprite = table_find_by_id(g_popup_resource_table + 0x8710, 0x39);
        gfx_draw_scaled_object_two_axes(sprite, 0x60442D00, (f32)(g_screen_width / 2), (f32)label_y(sprite, 194.0f, g_race_hud_layout_scale, 0.5f, 1), 0.92f, g_is_pal_video ? 0.9f : 0.92f, 0.0f);
        sprite = table_find_by_id(g_popup_resource_table + 0x8710, 0x38);
        gfx_draw_scaled_object_two_axes(sprite, 0x55F0C070, (f32)(g_screen_width / 2), (f32)label_y(sprite, 194.0f, g_race_hud_layout_scale, 0.5f, 1), 0.92f, g_is_pal_video ? 0.9f : 0.92f, 0.0f);
        { char *str_ = GetLocalizedString(0x2e29); int x_ = g_screen_width / 2; int row_ = label_y((void *)x_, 32.0f, g_race_hud_layout_scale, 0.5f, 1); int len_ = func_001157AC(str_); text_draw_centered_small(x_, row_, 0x80F0F0F0ULL, str_, len_); }
        if (g_race_hud_message_timer > 0) {
            { int x_ = g_screen_width / 2; int row_ = label_y((void *)x_, 65.0f, g_race_hud_layout_scale, 0.5f, 1); char *str_ = GetLocalizedString(0x1233); text_draw_centered_small(x_, row_, 0x80F0F0F0ULL, str_, -1); }
            g_race_hud_message_timer--;
        } else if (g_race_challenge_table[g_current_race_index].times[lap - 1]) {
            s32 recordTime;
            char *recordFormat = GetLocalizedString(0x2e5c);
            recordTime = g_race_challenge_table[g_current_race_index].times[lap - 1];
            if (g_extras_unlocked_flag) recordTime *= 10;
            { int n_ = sprintf(text, recordFormat, recordTime); int x_ = g_screen_width / 2; int row_ = label_y((void *)x_, 65.0f, g_race_hud_layout_scale, 0.5f, 1); int len_ = func_001157AC(text); text_draw_centered_small(x_, row_, 0x80F0F0F0ULL, text, len_); }
        }
    }
    bottom = 315 - (s32)g_hud_bottom_scroll_pos;
    if (bottom <= 156) bottom = 157;
    if (bottom == 157) g_hud_bottom_scroll_stopped = 1;
    flag = 1;
    fbottom = (f32)bottom;
    alpha = (1.0f - (315.0f - fbottom) * 0.006329114f) * 0.72f + 0.08f;
    sprite = table_find_by_id(g_popup_resource_table + 0x8710, 0x47);
    gfx_draw_scaled_object_two_axes(sprite, 0x60442D00, (f32)(g_screen_width / 2), (f32)label_y(sprite, 196.0f, g_race_hud_layout_scale, 0.5f, 1), 0.92f, g_is_pal_video ? 0.9f : 0.92f, alpha);
    sprite = table_find_by_id(g_popup_resource_table + 0x8710, 0x46);
    gfx_draw_scaled_object_two_axes(sprite, 0x55F0C070, (f32)(g_screen_width / 2), (f32)label_y(sprite, 196.0f, g_race_hud_layout_scale, 0.5f, 1), 0.92f, g_is_pal_video ? 0.9f : 0.92f, alpha);
    { int x_, row_, len_; sprintf(text, g_str_race_label_format, GetLocalizedString(0x2e15),
        GetLocalizedString(g_race_rank_string_ids[*(s32 *)(state + 0x320) - 1]), GetLocalizedString(0x2e16));
      x_ = g_screen_width / 2; row_ = label_y((void *)x_, 106.0f, g_race_hud_layout_scale, 0.5f, 1); len_ = func_001157AC(text); text_draw_centered_small(x_, row_, 0x80F0F0F0ULL, text, len_); }
    { int row_ = hud_coord(fbottom, g_race_hud_layout_scale, 0.5f); char *str_ = GetLocalizedString(0x2dd8); text_draw_right_aligned_medium(390, row_, 0x80F0F0F0ULL, str_, -1); }
    y = 138;
    ahead = 0;
    racer = *(u8 **)(state + 0x39C);
    g_hud_racer_ahead_flag = flag;
    while (racer) {
        s32 scroll = (s32)g_hud_top_scroll_pos - 138;
        fade = 0.1f;
        one = 1;
        rank = 0;
        time = 0;
        y = row * 15 - scroll;
        if (*(s16 *)(racer + 0xAA) == 0xBBC) {
            if (y <= 138) { y = 138; g_hud_top_scroll_stopped = 1; }
            rank = *(s32 *)(state + 0x320);
            time = g_race_time_ticks;
            playerSeen = 1;
            racer = *(u8 **)(state + 0x3A0);
        } else if (*(s16 *)(racer + 0xAA) == 0xB2D) {
            u8 *rs = *(u8 **)(racer + 0x68);
            rank = *(u8 *)(rs + 0xA2);
            time = *(s32 *)(rs + 0x1A0);
            racer = *(u8 **)(rs + 0x1A4);
            if (rank > 10) continue;
            if (*(s32 *)(state + 0x320) < rank) {
                s32 projected = g_race_time_ticks + g_race_extra_ticks;
                if (projected < time) { g_hud_racer_ahead_flag = 0; ahead++; }
                if (time == projected) PlayMobySound(22, 17, object);
            }
        }
        if (y < 128) { if (rank <= 10) row++; continue; }
        if (y > bottom - 10) continue;
        if (rank == *(s32 *)(state + 0x320)) { color2 = 0x8000C0C0; color1 = 0x8000C0C0; }
        else { color2 = 0x80F0F0F0; color1 = 0xF0F0F0; }
        if (y < 138) {
            color = FastTweenColor(color1, color2, ((f32)y - 128.0f) * fade);
        }
        else if (*(s32 *)(state + 0x320) < rank && bottom - y <= 20)
        {
            color = FastTweenColor(color1, color2, (f32)(bottom - y - 10) * fade);
        }
        else { color = color2; }
        fy = (f32)y;
        sprintf(text, g_str_race_rank_format, GetLocalizedString(g_race_rank_string_ids[rank - 1]), GetLocalizedString(0x2e17));
        half = 0.5f;
        text_draw_centered_medium(175, label_y((void *)color, fy, g_race_hud_layout_scale, half, one), (s64)color, text, -1);
        if (ahead > 0) {
            if (g_race_status_message_phase == 3 || ahead >= 2) sprintf(text, g_str_race_message_format_a, GetLocalizedString(0x2e46));
            else if (g_race_status_message_phase == 2) sprintf(text, g_str_race_message_format_b, GetLocalizedString(0x2e46));
            else if (g_race_status_message_phase == 1) sprintf(text, g_str_race_message_format_c, GetLocalizedString(0x2e46));
            else sprintf(text, g_str_race_message_format_d, GetLocalizedString(0x2e46));
        } else {
            if (time / 60 % 60 < 10)
                sprintf(text, g_str_race_time_format, GetLocalizedString(0x2e19), time / 216000, time / 3600 % 60, time / 60 % 60, time / 6 % 10);
            else
                sprintf(text, g_str_race_time_format_alt, GetLocalizedString(0x2e19), time / 216000, time / 3600 % 60, time / 60 % 60, time / 6 % 10);
        }
        half = 0.5f;
        text_draw_medium(220, hud_coord(fy, g_race_hud_layout_scale, half), (s64)color, text, -1); row++;
        if (row >= 10) break;
    }
    if (*(s32 *)(state + 0x320) > 10 && !g_hud_top_scroll_stopped && !playerSeen) {
        sprintf(text, g_str_race_rank_format, GetLocalizedString(g_race_rank_string_ids[*(s32 *)(state + 0x320) - 1]), GetLocalizedString(0x2e17));
        y += 15;
        { int row_ = hud_coord((f32)y, g_race_hud_layout_scale, 0.5f); text_draw_centered_medium(175, row_, 0x8000C0C0ULL, text, -1); }
        if (g_race_time_ticks / 60 % 60 < 10)
            sprintf(text, g_str_race_time_format, GetLocalizedString(0x2e19), g_race_time_ticks / 216000, g_race_time_ticks / 3600 % 60, g_race_time_ticks / 60 % 60, g_race_time_ticks / 6 % 10);
        else
            sprintf(text, g_str_race_time_format_alt, GetLocalizedString(0x2e19), g_race_time_ticks / 216000, g_race_time_ticks / 3600 % 60, g_race_time_ticks / 60 % 60, g_race_time_ticks / 6 % 10);
        { int row_ = hud_coord((f32)y, g_race_hud_layout_scale, 0.5f); text_draw_medium(196, row_, 0x8000C0C0ULL, text, -1); }
    }
    if (*(u8 *)(object + 0x20) != 3) {
        f32 angle;
        angle = *(f32 *)(state + 0x28C) * 0.008726647f;
        g_water_camera.tangent = math_fast_sin_or_cos_b(angle) / math_fast_sin_or_cos_a(angle);
        UpdateViewContext();
    }
    VU1_addGSregister(0x47, 0x5360B);
    return 1;
}
