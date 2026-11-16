#include "include_asm.h"
#include "names.h"

extern char *g_resident_data_base;
extern int g_screen_width, g_menu_toggle_option;
extern int g_toggle_option_title_y __attribute__((sda));
extern float g_menu_alpha_scale;
extern char g_str_menu_line_fmt[], g_str_localized_text_fmt[];
extern void SetupGifPaging(long);
extern void DoGifPaging(void);
extern void *table_find_by_id(char *, int);
extern void gfx_draw_scaled_object_two_axes(char *, int, float, float, float, float, float);
extern char *GetLocalizedString(int);
extern int text_draw_centered_small(int, int, unsigned long, char *, int);
extern void text_draw_small(int, int, unsigned long, char *, int);
extern int sprintf(char *, char *, ...);
extern int func_001157AC(char *);

/* Draws the toggle option screen with the option name and its current on or off text. */
int menu_toggle_option_draw_us2(void)
{
    char text[64];
    char *heading_format;
    char *option_format;
    float depth;

    SetupGifPaging(0);
    depth = 0.56f;
    gfx_draw_scaled_object_two_axes(table_find_by_id(g_resident_data_base + 0x8710, 0x8B), 0x60442D00,
                 (float)(g_screen_width / 2), (float)g_toggle_option_title_y,
                 1.0f, g_menu_alpha_scale, depth);
    gfx_draw_scaled_object_two_axes(table_find_by_id(g_resident_data_base + 0x8710, 0x8C), 0x55F0C070,
                 (float)(g_screen_width / 2), (float)g_toggle_option_title_y,
                 1.0f, g_menu_alpha_scale, depth);
    gfx_draw_scaled_object_two_axes(table_find_by_id(g_resident_data_base + 0x8710, 0x8D), 0x55F0C070,
                 (float)(g_screen_width / 2), (float)g_toggle_option_title_y,
                 1.0f, g_menu_alpha_scale, depth);
    text_draw_centered_small(g_screen_width / 2, 65, 0x80F0F0F0UL, GetLocalizedString(0x30D5), -1);
    text_draw_centered_small(g_screen_width / 2, 321, 0x80F0F0F0UL, GetLocalizedString(0x2BE4), -1);
    text_draw_centered_small(g_screen_width / 2, 346, 0x80F0F0F0UL, GetLocalizedString(0x2BE5), -1);

    heading_format = g_str_menu_line_fmt;
    sprintf(text, heading_format, GetLocalizedString(0x30D5));
    text_draw_small(134, 186, 0x80F0F0F0UL, text, func_001157AC(text));
    option_format = g_str_localized_text_fmt;
    sprintf(text, option_format, GetLocalizedString(g_menu_toggle_option ? 0x2C5C : 0x2C5D));
    text_draw_centered_small(349, 186, 0x80F0F0F0UL, text, func_001157AC(text));
    DoGifPaging();
    return 0;
}
