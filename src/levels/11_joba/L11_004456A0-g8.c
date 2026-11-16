#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef short s16;

extern void joba_menu_draw_help_prompts(char *, int);
extern char *GetLocalizedString(int);
extern long long GetEffectTextureDescriptor(int);
extern void FontPrintScaled(float, float, long long, char *, float, int, long long, char *);
extern void FontSetWindow(char *, int, int, int, int, int, int, int, int);
extern int arena_get_challenge_flag_index(int);
extern unsigned int func_001157AC(char *);
extern void text_draw_window_large(char *, long long, char *, int);
extern void text_draw_window_small(char *, long long, char *, int);
extern int sprintf(char *, char *, ...);

extern float g_header_box_title_scale __attribute__((sda));
extern int g_header_box_title_color __attribute__((sda));
extern int g_header_box_title_x __attribute__((sda));
extern int g_header_box_title_y __attribute__((sda));
extern int g_header_box_large_window_color __attribute__((sda));
extern int g_header_box_a_window_arg __attribute__((sda));
extern int g_header_box_a_height __attribute__((sda));
extern int g_header_box_small_window_color __attribute__((sda));
extern int g_header_box_b_window_arg __attribute__((sda));
extern int g_header_box_b_height __attribute__((sda));
extern int g_header_box_x __attribute__((sda));
extern int g_header_box_y;
extern int g_header_box_window_left;
extern int g_header_box_window_right;
extern int g_header_box_window_last_arg __attribute__((sda));
extern float g_hud_label_y_param;
extern char g_str_count_line_format[];
extern char g_str_header_count_box[];
extern u8 g_game_flag_table[0x100];

extern int g_hud_coord_mode;

/* A coordinate scaled for the display and rounded to a whole pixel. The display-mode test has no
   effect on the result, but it is real: its load and compare go at flow2, after allocation. */
static __inline__ int scaled_coord(int value, float scale, float half, int active)
{
    int mode = g_hud_coord_mode;
    float scaled = (float)value * scale + half;
    int result = (int)scaled;

    if (result != 0 && mode == active)
        scaled = 1.0f;
    return result;
}

/* Draws the Joba menu header and the count box with its message. */
void joba_menu_draw_header_count_box(char *moby) {
    char boxBuf[0x20];
    char lineBuf[0x70];
    char *state;
    char *text;
    char *unitText;
    float titleX, scale, half;
    int titleY, boxX, boxY, boxH, one;

    joba_menu_draw_help_prompts(moby, 0);
    half = 0.5f;
    state = *(char **)(moby + 0x68);
    text = (char *)GetLocalizedString(0x2F45);
    one = 1;
    scale = g_hud_label_y_param;
    titleX = (float)g_header_box_title_x;
    titleY = scaled_coord(g_header_box_title_y, scale, half, one);
    FontPrintScaled(titleX, (float)titleY, g_header_box_title_color, text, g_header_box_title_scale, -1,
                  GetEffectTextureDescriptor(1), g_str_header_count_box);
    scale = g_hud_label_y_param;
    boxX = scaled_coord(g_header_box_x, scale, half, one);
    boxY = scaled_coord(g_header_box_y, scale, half, one);
    boxH = scaled_coord(g_header_box_a_height, scale, half, one);
    FontSetWindow(boxBuf, boxX, boxY, g_header_box_window_left, g_header_box_window_right, g_header_box_a_window_arg, boxH,
                  g_header_box_window_last_arg, 3);
    if (*(s16 *)(state + 0x1E8) == 0 && g_game_flag_table[arena_get_challenge_flag_index(0)] < 2) {
        text = (char *)GetLocalizedString(0x2F96);
        text_draw_window_large(boxBuf, g_header_box_large_window_color, text, func_001157AC(text));
    } else if (*(s16 *)(state + 0x1E8) == 1 && g_game_flag_table[arena_get_challenge_flag_index(1)] < 2) {
        text = (char *)GetLocalizedString(0x2F97);
        text_draw_window_large(boxBuf, g_header_box_large_window_color, text, func_001157AC(text));
    } else {
        text = (char *)GetLocalizedString(0x2F62);
        unitText = (char *)GetLocalizedString(0x2F5E);
        sprintf(lineBuf, g_str_count_line_format, text, *(int *)(state + 0x1E0), unitText);
        text_draw_window_large(boxBuf, g_header_box_large_window_color, lineBuf, func_001157AC(lineBuf));
    }
    text = (char *)GetLocalizedString(0x2F47);
    {
        float half = 0.5f;
        int one = 1;

        scale = g_hud_label_y_param;
        boxX = scaled_coord(g_header_box_x, scale, half, one);
        boxY = scaled_coord(g_header_box_y, scale, half, one);
        boxH = scaled_coord(g_header_box_b_height, scale, half, one);
        FontSetWindow(boxBuf, boxX, boxY, g_header_box_window_left, g_header_box_window_right, g_header_box_b_window_arg, boxH,
                      g_header_box_window_last_arg, 3);
    }
    text_draw_window_small(boxBuf, g_header_box_small_window_color, text, func_001157AC(text));
}
