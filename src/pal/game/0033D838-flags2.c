#include "include_asm.h"
#include "names.h"

typedef struct { int ids[2]; } SolTextPair2;
extern SolTextPair2 g_toggle_menu_text_pair;
extern char g_str_toggle_menu_format[];
extern unsigned char g_subtitles_option __attribute__((sda));
extern unsigned char g_toggle_option_a __attribute__((sda));
extern void prompt_bar_draw_pal(void *);
extern char *GetLocalizedString(int);
extern int sprintf(char *, const char *, ...);
extern int text_draw_centered_small(int, int, unsigned long, char *, int);

/* Draws the two-toggle option page: the prompt bar and one centred line per option, the selected one brighter. */
void two_toggle_a_draw_pal(char *object)
{
    char buffer[128];
    SolTextPair2 pair;
    char *first;
    char *label;
    char *second;
    char *format;
    int color;

    prompt_bar_draw_pal(object + 8);
    color = *(int *)(object + 0x2D8) == 0 ? (int)0x80D0D0D0 : 0x70808080;
    pair = g_toggle_menu_text_pair;
    format = g_str_toggle_menu_format;
    first = GetLocalizedString(0xBF0);
    second = GetLocalizedString(pair.ids[g_toggle_option_a != 0]);
    sprintf(buffer, format, first, second);
    text_draw_centered_small(0x100, 0x96, color, buffer, -1);

    color = *(int *)(object + 0x2D8) == 1 ? (int)0x80D0D0D0 : 0x70808080;
    label = GetLocalizedString(0xBEF);
    second = GetLocalizedString(pair.ids[g_subtitles_option != 0]);
    sprintf(buffer, format, label, second);
    text_draw_centered_small(0x100, 0xBE, color, buffer, -1);
}

extern void prompt_bar_draw_pal();
extern int DrawMenuPreviewImage();
extern void text_label_draw_pal();
extern void hud_draw_colored_quad_widget();
extern void gfx_draw_screen_element_stored();
extern void info_panel_draw_counters_pal();

/* Forwards one object pointer, eight pointer-plus-constant arguments and a null to ten calls in a fixed order. */
void info_panel_draw_pal(char *object)
{
    prompt_bar_draw_pal(object + 8);
    DrawMenuPreviewImage(0);
    text_label_draw_pal(object + 792);
    text_label_draw_pal(object + 880);
    text_label_draw_pal(object + 968);
    hud_draw_colored_quad_widget(object + 732);
    gfx_draw_screen_element_stored(object + 1056);
    text_label_draw_pal(object + 1576);
    text_label_draw_pal(object + 1488);
    info_panel_draw_counters_pal(object);
}

extern unsigned char g_pal_language_flag_a __attribute__((sda));
extern unsigned char g_pal_language_flag_b __attribute__((sda));

/* Draws the two-toggle option page (language flags): the prompt bar and one centred line per option, the selected one brighter. */
void two_toggle_b_draw_pal(char *object)
{
    char buffer[128];
    SolTextPair2 pair;
    char *first;
    char *label;
    char *second;
    char *format;
    int color;

    prompt_bar_draw_pal(object + 8);
    color = *(int *)(object + 0x2D8) == 0 ? (int)0x80D0D0D0 : 0x70808080;
    pair = g_toggle_menu_text_pair;
    format = g_str_toggle_menu_format;
    first = GetLocalizedString(0xBAB);
    second = GetLocalizedString(pair.ids[g_pal_language_flag_a != 0]);
    sprintf(buffer, format, first, second);
    text_draw_centered_small(0x100, 0x96, color, buffer, -1);

    color = *(int *)(object + 0x2D8) == 1 ? (int)0x80D0D0D0 : 0x70808080;
    label = GetLocalizedString(0x10FB);
    second = GetLocalizedString(pair.ids[g_pal_language_flag_b != 0]);
    sprintf(buffer, format, label, second);
    text_draw_centered_small(0x100, 0xBE, color, buffer, -1);
}
