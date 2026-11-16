#include "names.h"
/* func_US2_L11_0044709C, the USA v2.00 copy of func_L11_004456A0: the same C, with v2.00's message ids,
   and the x position read from an int table indexed by the byte D_US2_001A7BBC. */
#include "common.h"

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
extern int g_header_box_title_x[] SDATA(D_L11_001B1810);
extern unsigned char g_display_mode_index;
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

void func_US2_L11_0044709C(char *a0) {
    char buf1[0x20];
    char buf2[0x70];
    char *state;
    char *text;
    char *msg;
    float x, s, half;
    int r0, r1, r2, r3, one;

    joba_menu_draw_help_prompts(a0, 0);
    half = 0.5f;
    state = *(char **)(a0 + 0x68);
    text = (char *)GetLocalizedString(0x2DDB);
    one = 1;
    s = g_hud_label_y_param;
    x = (float)g_header_box_title_x[g_display_mode_index];
    r0 = scaled_coord(g_header_box_title_y, s, half, one);
    FontPrintScaled(x, (float)r0, g_header_box_title_color, text, g_header_box_title_scale, -1,
                  GetEffectTextureDescriptor(1), g_str_header_count_box);
    s = g_hud_label_y_param;
    r1 = scaled_coord(g_header_box_x, s, half, one);
    r2 = scaled_coord(g_header_box_y, s, half, one);
    r3 = scaled_coord(g_header_box_a_height, s, half, one);
    FontSetWindow(buf1, r1, r2, g_header_box_window_left, g_header_box_window_right, g_header_box_a_window_arg, r3,
                  g_header_box_window_last_arg, 3);
    if (*(s16 *)(state + 0x1E8) == 0 && g_game_flag_table[arena_get_challenge_flag_index(0)] < 2) {
        text = (char *)GetLocalizedString(0x2E2C);
        text_draw_window_large(buf1, g_header_box_large_window_color, text, func_001157AC(text));
    } else if (*(s16 *)(state + 0x1E8) == 1 && g_game_flag_table[arena_get_challenge_flag_index(1)] < 2) {
        text = (char *)GetLocalizedString(0x2E2D);
        text_draw_window_large(buf1, g_header_box_large_window_color, text, func_001157AC(text));
    } else {
        text = (char *)GetLocalizedString(0x2DF8);
        msg = (char *)GetLocalizedString(0x2DF4);
        sprintf(buf2, g_str_count_line_format, text, *(int *)(state + 0x1E0), msg);
        text_draw_window_large(buf1, g_header_box_large_window_color, buf2, func_001157AC(buf2));
    }
    text = (char *)GetLocalizedString(0x2DDD);
    {
        float half = 0.5f;
        int one = 1;

        s = g_hud_label_y_param;
        r1 = scaled_coord(g_header_box_x, s, half, one);
        r2 = scaled_coord(g_header_box_y, s, half, one);
        r3 = scaled_coord(g_header_box_b_height, s, half, one);
        FontSetWindow(buf1, r1, r2, g_header_box_window_left, g_header_box_window_right, g_header_box_b_window_arg, r3,
                      g_header_box_window_last_arg, 3);
    }
    text_draw_window_small(buf1, g_header_box_small_window_color, text, func_001157AC(text));
}
