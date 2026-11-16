#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef short s16;

extern void arena_draw_menu_help_prompts(char *, int);
extern char *GetLocalizedString(int);
extern long long GetEffectTextureDescriptor(int);
extern void FontPrintScaled(float, float, long long, char *, float, int, long long, char *);
extern void FontSetWindow(char *, int, int, int, int, int, int, int, int);
extern int arena_get_challenge_save_index(int);
extern unsigned int func_001157AC(char *);
extern void text_draw_window_large(char *, long long, char *, int);
extern void text_draw_window_small(char *, long long, char *, int);
extern int sprintf(char *, char *, ...);

extern float g_arena_info_title_scale __attribute__((sda));
extern int g_arena_info_title_x __attribute__((sda));
extern int g_arena_info_text_x __attribute__((sda));
extern int g_arena_info_title_y __attribute__((sda));
extern int g_arena_info_large_window_id __attribute__((sda));
extern int g_arena_info_large_window_height __attribute__((sda));
extern int g_arena_info_large_box_height __attribute__((sda));
extern int g_arena_info_small_window_id __attribute__((sda));
extern int g_arena_info_small_window_height __attribute__((sda));
extern int g_arena_info_small_box_height __attribute__((sda));
extern int g_arena_info_box_x __attribute__((sda));
extern int g_arena_info_box_y;
extern int g_arena_info_window_left;
extern int g_arena_info_window_right;
extern int g_arena_info_text_color __attribute__((sda));
extern float g_hud_label_scale;
extern char g_str_arena_panel_format[];
extern char g_arena_info_panel_data[];
extern u8 g_game_flag_table[0x100];

extern int g_hud_l02_mode;

/* A coordinate scaled for the display and rounded to a whole pixel. The display-mode test has no
   effect on the result, but it is real: its load and compare go at flow2, after allocation. */
static __inline__ int scaled_coord(int value, float scale, float half, int active)
{
    int mode = g_hud_l02_mode;
    float scaled = (float)value * scale + half;
    int result = (int)scaled;

    if (result != 0 && mode == active)
        scaled = 1.0f;
    return result;
}

/* Level 2 copy of func_L11_004456A0 (src/levels/11_joba/L11_004456A0-g8.c), transcribed
   with this level's data. */
/* Draws the info panel for the selected challenge: a title, a box and a line with the best result so far. */
void arena_draw_info_panel(char *actor) {
    char rect[0x20];
    char lineBuf[0x70];
    char *state;
    char *text;
    char *msg;
    float x, scale, half;
    int titleY, boxX, boxY, boxHeight, one;

    arena_draw_menu_help_prompts(actor, 0);
    half = 0.5f;
    state = *(char **)(actor + 0x68);
    text = (char *)GetLocalizedString(0x2F45);
    one = 1;
    scale = g_hud_label_scale;
    x = (float)g_arena_info_text_x;
    titleY = scaled_coord(g_arena_info_title_y, scale, half, one);
    FontPrintScaled(x, (float)titleY, g_arena_info_title_x, text, g_arena_info_title_scale, -1,
                  GetEffectTextureDescriptor(1), g_arena_info_panel_data);
    scale = g_hud_label_scale;
    boxX = scaled_coord(g_arena_info_box_x, scale, half, one);
    boxY = scaled_coord(g_arena_info_box_y, scale, half, one);
    boxHeight = scaled_coord(g_arena_info_large_box_height, scale, half, one);
    FontSetWindow(rect, boxX, boxY, g_arena_info_window_left, g_arena_info_window_right, g_arena_info_large_window_height, boxHeight,
                  g_arena_info_text_color, 3);
    if (*(s16 *)(state + 0x118) == 0 && g_game_flag_table[arena_get_challenge_save_index(0)] < 2) {
        text = (char *)GetLocalizedString(0x2F46);
        text_draw_window_large(rect, g_arena_info_large_window_id, text, func_001157AC(text));
    } else {
        text = (char *)GetLocalizedString(0x2F62);
        msg = (char *)GetLocalizedString(0x2F5E);
        sprintf(lineBuf, g_str_arena_panel_format, text, *(int *)(state + 0x110), msg);
        text_draw_window_large(rect, g_arena_info_large_window_id, lineBuf, func_001157AC(lineBuf));
    }
    text = (char *)GetLocalizedString(0x2F47);
    {
        float half = 0.5f;
        int one = 1;

        scale = g_hud_label_scale;
        boxX = scaled_coord(g_arena_info_box_x, scale, half, one);
        boxY = scaled_coord(g_arena_info_box_y, scale, half, one);
        boxHeight = scaled_coord(g_arena_info_small_box_height, scale, half, one);
        FontSetWindow(rect, boxX, boxY, g_arena_info_window_left, g_arena_info_window_right, g_arena_info_small_window_height, boxHeight,
                      g_arena_info_text_color, 3);
    }
    text_draw_window_small(rect, g_arena_info_small_window_id, text, func_001157AC(text));
}
