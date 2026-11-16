#include "names.h"
/* func_PAL_L04_0041B850 (PAL, levels 04 and 11): the timer box, the PAL copy of v2.00's
   func_US2_L04_004185D8 (src/us2/levels/shared/L04_004185D8-cc.c). It formats the elapsed time from
   the 50 Hz frame counter (hours / 180000, minutes / 3000, seconds / 50, tenths / 5), then draws the
   box (corners through menu_coord) and the centred text, whose y goes through label_y. For language
   byte 4 the box is larger (124 by 154, 35-pixel margins, text at 130); otherwise it is v2.00's
   (112 by 142, 50-pixel margins, text at 118). Each arm keeps its own constants.

   The language byte is read as D_001A7BB0[4], as in the PAL menu panels: an element at an offset is
   a two-word load, which keeps it out of the delay slot of the format branch's jump, as retail. */

extern int g_current_lap __attribute__((sda));
extern char *GetLocalizedString(int);
extern int sprintf(char *, const char *, ...);
extern int func_001157AC(char *);
extern void gfx_draw_rounded_box(int, int, int, int, int, int);
extern void level_set_rect_pal(float, float, float, float, int, int);
extern int text_draw_centered_large(int, int, unsigned long long, char *, int);
extern int D_L04_001B0920_gp __asm__("D_L04_001B0920__gp") __attribute__((section(".sdata")));
extern char g_str_race_time_label_format[];
extern char g_str_race_time_label_format_alt[];
extern float g_race_hud_layout_scale __attribute__((sda));
extern int g_screen_width __attribute__((sda));
extern unsigned char g_language_settings[] __attribute__((sda)); /* the language byte is [4] */

extern int g_race_hud_mode __attribute__((sda));
/* The shared HUD rounding helper; the dead mode arm leaves a scheduling boundary. */
static __inline__ int menu_coord(float value, float scale, float half, int active)
{
    int mode = g_race_hud_mode;
    float scaled = scale * value + half;
    int result = (int)scaled;

    if (result != 0 && mode == active)
        scaled = 1.0f;
    return result;
}

/* label_y, the HUD label idiom (the shared definition in src/levels/15_gorn/L15_00431590-g8.c, `active`
   the literal 1 at every call). Its tests do not change the result: flow deletes their stores and
   jump2 their jumps, but only after allocation and both scheduling passes, which see the block they
   end. */
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

void func_PAL_L04_0041B850(void) {
    float s;
    int x1, y1, x4, active;
    float fx, fy;
    char text[64], prefix[64];
    sprintf(prefix, GetLocalizedString(0xEA7), g_current_lap);
    if (D_L04_001B0920_gp / 50 % 60 < 10)
        sprintf(text, g_str_race_time_label_format, prefix, GetLocalizedString(0xEA8), D_L04_001B0920_gp / 180000, D_L04_001B0920_gp / 3000 % 60, D_L04_001B0920_gp / 50 % 60, D_L04_001B0920_gp / 5 % 10);
    else
        sprintf(text, g_str_race_time_label_format_alt, prefix, GetLocalizedString(0xEA8), D_L04_001B0920_gp / 180000, D_L04_001B0920_gp / 3000 % 60, D_L04_001B0920_gp / 50 % 60, D_L04_001B0920_gp / 5 % 10);
    active = 1;
    if (g_language_settings[4] == 4) {
        float kx = 124.0f;
        float half = 0.5f;
        float ky;

        s = g_race_hud_layout_scale;
        x1 = menu_coord(kx, s, half, active);
        ky = 154.0f;
        y1 = menu_coord(ky, s, half, active);
        gfx_draw_rounded_box(x1, y1, 35, g_screen_width - 35, 96, 0x60442D00);
        s = g_race_hud_layout_scale;
        fx = (float)menu_coord(kx, s, half, active);
        fy = (float)menu_coord(ky, s, half, active);
        level_set_rect_pal(fx, fy, 35.0f, (float)(g_screen_width - 35), 96, 0x55F0C070);
        x4 = g_screen_width / 2;
        text_draw_centered_large(x4, label_y((void *)x4, 130.0f, g_race_hud_layout_scale, half, 1), 0x80F0F0F0ULL, text, func_001157AC(text));
    } else {
        float kx = 112.0f;
        float half = 0.5f;
        float ky;

        s = g_race_hud_layout_scale;
        x1 = menu_coord(kx, s, half, active);
        ky = 142.0f;
        y1 = menu_coord(ky, s, half, active);
        gfx_draw_rounded_box(x1, y1, 50, g_screen_width - 50, 96, 0x60442D00);
        s = g_race_hud_layout_scale;
        fx = (float)menu_coord(kx, s, half, active);
        fy = (float)menu_coord(ky, s, half, active);
        level_set_rect_pal(fx, fy, 50.0f, (float)(g_screen_width - 50), 96, 0x55F0C070);
        x4 = g_screen_width / 2;
        text_draw_centered_large(x4, label_y((void *)x4, 118.0f, g_race_hud_layout_scale, half, 1), 0x80F0F0F0ULL, text, func_001157AC(text));
    }

}
