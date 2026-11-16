#include "include_asm.h"
#include "names.h"

extern void arena_draw_menu_help_prompts(char *, int);
extern char *GetLocalizedString(int);
extern long long GetEffectTextureDescriptor(int);
extern void FontPrintScaled(float, float, long long, char *, float, int, long long, char *);
extern void FontSetWindow(char *, int, int, int, int, int, int, int, int);
extern unsigned int func_001157AC(char *);
extern void text_draw_window_large(char *, long long, char *, int);
extern void text_draw_window_small(char *, long long, char *, int);
extern int sprintf(char *, char *, ...);
extern int arena_get_challenge_save_index(int);
extern unsigned char g_game_flag_table[0x100];
extern unsigned char g_display_mode_index;
extern int g_text_l02_x_by_mode_2[2] __attribute__((sda));
extern float g_text_l02_print_scale_2 __attribute__((sda));
extern int g_text_l02_print_color_2 __attribute__((sda));
extern int g_text_l02_window_coord_a_2 __attribute__((sda));
extern int g_text_l02_window_large_param_2 __attribute__((sda));
extern int g_font_l02_window_flags_a_2 __attribute__((sda));
extern int g_text_l02_window_coord_b_2 __attribute__((sda));
extern int g_text_l02_window_small_param_2 __attribute__((sda));
extern int g_font_l02_window_flags_b_2 __attribute__((sda));
extern int g_text_l02_window_coord_c_2 __attribute__((sda));
extern int g_text_l02_window_coord_d_2 __attribute__((sda));
extern int g_font_l02_window_param_c_2 __attribute__((sda));
extern int g_text_l02_window_coord_e_2;
extern int g_font_l02_window_param_a_2;
extern int g_font_l02_window_param_b_2;
extern float g_text_l02_layout_scale_2;
extern int g_text_l02_layout_mode_2;
extern char g_str_text_format[];
extern char g_str_l02_effect_texture_2[];

static __inline__ int scaled_coord(int value, float scale, float half, int active)
{
    int mode = g_text_l02_layout_mode_2;
    float scaled = (float)value * scale + half;
    int result = (int)scaled;

    if (result != 0 && mode == active)
        scaled = 1.0f;
    return result;
}

/* func_US2_L02_00400E04, the v2.00 copy of func_PAL_L02_00403FF0 (src/pal/levels/02_maktar_nebula/
   L02_00403FF0-g8.c), itself the PAL copy of func_L02_003FF6E8: the same C with this release's data
   and text ids 0x2DDB, 0x2DDC, 0x2DF8, 0x2DF4 and 0x2DDD. The first x is taken per language from
   D_US2_L02_001B1460, as in PAL. Its data is named D_US2_L02_<v2.00 address>. */
void arena_draw_info_panel_us2(char *moby) {
    char buf1[0x20];
    char buf2[0x70];
    char *state;
    char *text;
    char *msg;
    float x, s, half;
    int r0, r1, r2, r3, one;

    arena_draw_menu_help_prompts(moby, 0);
    half = 0.5f;
    state = *(char **)(moby + 0x68);
    text = (char *)GetLocalizedString(0x2DDB);
    one = 1;
    s = g_text_l02_layout_scale_2;
    x = (float)g_text_l02_x_by_mode_2[g_display_mode_index];
    r0 = scaled_coord(g_text_l02_window_coord_a_2, s, half, one);
    FontPrintScaled(x, (float)r0, g_text_l02_print_color_2, text, g_text_l02_print_scale_2, -1,
                  GetEffectTextureDescriptor(1), g_str_l02_effect_texture_2);
    s = g_text_l02_layout_scale_2;
    r1 = scaled_coord(g_text_l02_window_coord_d_2, s, half, one);
    r2 = scaled_coord(g_text_l02_window_coord_e_2, s, half, one);
    r3 = scaled_coord(g_text_l02_window_coord_b_2, s, half, one);
    FontSetWindow(buf1, r1, r2, g_font_l02_window_param_a_2, g_font_l02_window_param_b_2, g_font_l02_window_flags_a_2, r3,
                  g_font_l02_window_param_c_2, 3);
    if (*(short *)(state + 0x118) == 0 && g_game_flag_table[arena_get_challenge_save_index(0)] < 2) {
        text = (char *)GetLocalizedString(0x2DDC);
        text_draw_window_large(buf1, g_text_l02_window_large_param_2, text, func_001157AC(text));
    } else {
        text = (char *)GetLocalizedString(0x2DF8);
        msg = (char *)GetLocalizedString(0x2DF4);
        sprintf(buf2, g_str_text_format, text, *(int *)(state + 0x110), msg);
        text_draw_window_large(buf1, g_text_l02_window_large_param_2, buf2, func_001157AC(buf2));
    }
    text = (char *)GetLocalizedString(0x2DDD);
    {
        float half = 0.5f;
        int one = 1;

        s = g_text_l02_layout_scale_2;
        r1 = scaled_coord(g_text_l02_window_coord_d_2, s, half, one);
        r2 = scaled_coord(g_text_l02_window_coord_e_2, s, half, one);
        r3 = scaled_coord(g_text_l02_window_coord_c_2, s, half, one);
        FontSetWindow(buf1, r1, r2, g_font_l02_window_param_a_2, g_font_l02_window_param_b_2, g_font_l02_window_flags_b_2, r3,
                      g_font_l02_window_param_c_2, 3);
    }
    text_draw_window_small(buf1, g_text_l02_window_small_param_2, text, func_001157AC(text));
}
