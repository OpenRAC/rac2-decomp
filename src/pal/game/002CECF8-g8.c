#include "common.h"

/* func_PAL_002CECF8, the PAL copy of func_002CDD88: the same C, where the string ids are renumbered and the two
   func_0027F5B8 prompts become func_0027FA10, one at the coordinates in D_PAL_001ABA68/6C, one at x = 470. */

typedef struct {
    short ids[4];
    short name;
    short value;
    short description;
    short detail;
    short stats[4];
} Item;

extern char *g_resident_data_base;
extern int g_screen_width;
extern int g_item_list_cursor __attribute__((sda));
extern int g_item_list_next_row __attribute__((sda));
extern int g_menu_title_y_a __attribute__((sda));
extern unsigned short g_kill_event_counts[][2];
extern Item g_item_menu_table[];
extern int g_pad_menu_flags NOT_SDA;
extern float g_menu_alpha_scale;
extern int g_hud_mode;
extern char g_str_menu_line_fmt[], g_str_menu_plain_text[], g_str_count_fmt[];
extern int math_ping_pong_blend_values(int, int, int, int, int);
extern void SetupGifPaging(long), DoGifPaging(void);
extern void *table_find_by_id(char *, int);
extern void gfx_draw_scaled_object_two_axes(char *, int, float, float, float, float, float);
extern char *GetLocalizedString(int);
extern void text_draw_medium(int, int, u64, char *, int);
extern int text_draw_centered_small(int, int, u64, char *, int);
extern int text_draw_centered_medium(int, int, u64, char *, int);
extern int sprintf(char *, char *, ...);
extern int func_001157AC(char *);
extern void AppendScreenRectPacket(int, int, int, int, u64, int);
extern void gfx_disable_screen_flag(void), gfx_enable_screen_flag(void);
extern void text_draw_right_aligned_medium(int, int, u64, char *, int);
extern int g_text_right_x_c __attribute__((sda));
extern int g_text_right_y_c[] __attribute__((sda));

int draw_item_stats_menu_pal(void)
{
    char text[64];
    int inactive, color, width, center, count;
    char *format, *count_format;
    int active = 1;
    float alpha, zero = 0.0f;

    inactive = math_ping_pong_blend_values(0x60442D00, 0x80FFDE8D, 25, 0, 0);
    SetupGifPaging(0);
    gfx_draw_scaled_object_two_axes(table_find_by_id(g_resident_data_base + 0x8710, 0xAE), 0x60442D00, (float)(g_screen_width / 2), (float)g_menu_title_y_a, 1.0f, g_menu_alpha_scale, zero);
    gfx_draw_scaled_object_two_axes(table_find_by_id(g_resident_data_base + 0x8710, 0xAF), 0x60241700, (float)(g_screen_width / 2), (float)g_menu_title_y_a, 1.0f, g_menu_alpha_scale, zero);
    gfx_draw_scaled_object_two_axes(table_find_by_id(g_resident_data_base + 0x8710, 0xB0), 0x55F0C070, (float)(g_screen_width / 2), (float)g_menu_title_y_a, 1.0f, g_menu_alpha_scale, zero);
    gfx_draw_scaled_object_two_axes(table_find_by_id(g_resident_data_base + 0x8710, 0xB1), 0x55F0C070, (float)(g_screen_width / 2), (float)g_menu_title_y_a, 1.0f, g_menu_alpha_scale, zero);
    text_draw_medium(31, 62, 0x80F0F0F0ULL, GetLocalizedString(0x1105), -1);
    text_draw_medium(31, 92, 0x80F0F0F0ULL, GetLocalizedString(0x1106), -1);
    text_draw_medium(31, 122, 0x80F0F0F0ULL, GetLocalizedString(0x1104), -1);
    text_draw_medium(31, 152, 0x80F0F0F0ULL, GetLocalizedString(0x1107), -1);

    format = g_str_menu_line_fmt;
    sprintf(text, format, GetLocalizedString(0x1108));
    count = func_001157AC(text);
    text_draw_medium(31, 184, 0x80F0F0F0ULL, text, count);
    sprintf(text, format, GetLocalizedString(0x1109));
    count = func_001157AC(text);
    text_draw_medium(31, 201, 0x80F0F0F0ULL, text, count);
    text_draw_right_aligned_medium(g_text_right_x_c, g_text_right_y_c[0], 0x80F0F0F0ULL, GetLocalizedString(0xE67), -1);
    text_draw_centered_small(154, 26, 0x80F0F0F0ULL, GetLocalizedString(0x10DE), -1);

    if (g_kill_event_counts[g_item_list_cursor][0] != 0 || g_kill_event_counts[g_item_list_cursor][1] != 0) {
        width = (int)((float)g_item_menu_table[g_item_list_cursor].stats[0] * 2.44f);
        if (width > 244)
            width = 244;
        AppendScreenRectPacket(31, 78, width + 31, 88, 0x55F0C070ULL, 0);
        width = (int)((float)g_item_menu_table[g_item_list_cursor].stats[1] * 2.44f);
        if (width > 244)
            width = 244;
        AppendScreenRectPacket(31, 108, width + 31, 118, 0x55F0C070ULL, 0);
        width = (int)((float)g_item_menu_table[g_item_list_cursor].stats[2] * 2.44f);
        if (width > 244)
            width = 244;
        AppendScreenRectPacket(31, 139, width + 31, 150, 0x55F0C070ULL, 0);
        width = (int)((float)g_item_menu_table[g_item_list_cursor].stats[3] * 2.44f);
        if (width > 244)
            width = 244;
        AppendScreenRectPacket(31, 169, width + 31, 180, 0x55F0C070ULL, 0);
        if (g_item_list_cursor < g_item_list_next_row) {
            color = (g_pad_menu_flags & 0x2000) ? 0x80F0F0F0 : inactive;
            {
                char *sprite = table_find_by_id(g_resident_data_base + 0x8710, 0x4A);
                {
                    float factor = 0.8f;
                    alpha = g_menu_alpha_scale * factor;
                }
                if (g_hud_mode == active)
                    alpha += -0.05f;
                gfx_draw_scaled_object_two_axes(sprite, color, 316.0f, 278.0f, 1.0f, alpha, zero);
            }
            text_draw_right_aligned_medium(470, 276, 0x80F0F0F0ULL, GetLocalizedString(0xE66), -1);
        }
        if (g_item_list_cursor >= 2) {
            color = (g_pad_menu_flags & 0x8000) ? 0x80F0F0F0 : inactive;
            {
                char *sprite = table_find_by_id(g_resident_data_base + 0x8710, 0x4B);
                {
                    float factor = 0.8f;
                    alpha = g_menu_alpha_scale * factor;
                }
                if (g_hud_mode == 1)
                    alpha += -0.05f;
                gfx_draw_scaled_object_two_axes(sprite, color, 207.0f, 278.0f, 1.0f, alpha, zero);
            }
            text_draw_medium(55, 276, 0x80F0F0F0ULL, GetLocalizedString(0xE65), -1);
        }
        gfx_disable_screen_flag();
        center = g_screen_width / 2;
        text_draw_centered_medium(center, 276, 0x80F0F0F0ULL, GetLocalizedString(g_item_menu_table[g_item_list_cursor].name), -1);
        gfx_enable_screen_flag();
        text_draw_medium(156, 185, 0x80F0F0F0ULL, GetLocalizedString(g_item_menu_table[g_item_list_cursor].description), -1);
        if (g_item_menu_table[g_item_list_cursor].detail == -1) {
            sprintf(text, g_str_menu_plain_text);
            count = func_001157AC(text);
            text_draw_medium(156, 202, 0x80F0F0F0ULL, text, count);
        } else {
            text_draw_medium(156, 202, 0x80F0F0F0ULL, GetLocalizedString(g_item_menu_table[g_item_list_cursor].detail), -1);
        }
        count = g_kill_event_counts[g_item_list_cursor][0];
        count_format = g_str_count_fmt;
        sprintf(text, count_format, count, GetLocalizedString(0xE86));
        count = func_001157AC(text);
        text_draw_centered_medium(152, 228, 0x80F0F0F0ULL, text, count);
    }
    DoGifPaging();
    return 0;
}
