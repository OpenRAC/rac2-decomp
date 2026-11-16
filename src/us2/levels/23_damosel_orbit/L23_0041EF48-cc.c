#include "names.h"
/* func_US2_L23_0041EF48, the USA v2.00 copy of func_L23_0041DA48: the same C, where rename func_L00_0030DD70 becomes func_US2_L00_0030EFB8; rename func_0029CC50 becomes func_US2_0029DA88; rename func_0029B888 becomes func_US2_0029C678; rename func_L00_0030CF60 becomes func_US2_0029CC48. */
/* Level 23 encounter HUD: three backing sprites, two EAA4 icons, the two ratio bars, the
 * EAA5 icon with its counter text and up to two counter icons, a pending prompt message and the
 * optional prompt panel. It is the one-sided counterpart of func_L22_003A5018 (levels 22 and
 * 23), whose layout and helpers it follows. Its 16-byte colour block D_L23_001B1770 is reached
 * through $gp, hence -G16 (with -g, which keeps the nop pairs before each div.s) in a unit of
 * its own.
 *
 * NOTE REVIEW: three sites use the accepted dead-test HUD idioms as written: label_y at the two
 * EAA4 icon y coordinates, and upstream's scaled_coord at the counter text y and at the panel's
 * box coordinate (the same func_002802E0 argument upstream rounds with it). Their tests leave no
 * instruction, but retail allocates and schedules those sites as if a block ended there. The
 * plain conversion and a one-pass group were measured at each site and do not match.
 */
#include "common.h"

typedef unsigned long long U64;
typedef union ColorView {
    U64 half[2];
    unsigned int word[4];
} ColorView;
typedef struct {
    char pad[0x18];
    int counter;
    int icons;
} HudCounters;

extern char *g_hud_l23_sprite_base;
extern char *g_mothership_boss_moby __attribute__((sda));
extern float g_hud_label_y_scale __attribute__((sda));
extern float g_hud_label_x_position __attribute__((sda));
extern float g_hud_scale_y MACRO_ADDR;
extern int g_hud_l23_layout_mode MACRO_ADDR;
extern char g_hero_state[];
extern int g_screen_width MACRO_ADDR;
extern U64 g_hud_label_color_top __attribute__((sda));
extern U64 g_hud_label_color_bottom MACRO_ADDR;
extern U64 g_hud_label_color_top_alt __attribute__((sda));
extern U64 g_hud_label_color_bottom_alt MACRO_ADDR;
extern int g_hud_gradient_colors[4] __attribute__((sda));
extern char g_str_hud_counter_format[];
extern HudCounters g_hud_counters;
extern int g_boss_hud_stat_index MACRO_ADDR;
extern int g_boss_hud_stat_value MACRO_ADDR;
extern int g_boss_hud_display_timer MACRO_ADDR;
extern int g_boss_hud_timer __attribute__((sda));
extern int g_boss_part_age_counter __attribute__((sda));
extern int g_hud_bar_inset_x __attribute__((sda));
extern int g_hud_bar_row_height __attribute__((sda));
extern int g_hud_bar_margin_x __attribute__((sda));
extern int g_hud_bar_top_y __attribute__((sda));
extern int g_hud_bar_thickness __attribute__((sda));
extern int g_hud_bar_full_width __attribute__((sda));
extern int g_hud_bar_fill_pad_x __attribute__((sda));
extern int g_hud_icon_a_x __attribute__((sda));
extern int g_hud_icon_a_y __attribute__((sda));
extern int g_hud_icon_a_width __attribute__((sda));
extern int g_hud_icon_a_height __attribute__((sda));
extern int g_hud_icon_b_x __attribute__((sda));
extern int g_hud_icon_b_y __attribute__((sda));
extern int g_hud_icon_b_width __attribute__((sda));
extern int g_hud_icon_b_height __attribute__((sda));
extern int g_hud_icon_c_x __attribute__((sda));
extern int g_hud_icon_c_y __attribute__((sda));
extern int g_hud_icon_c_width __attribute__((sda));
extern int g_hud_icon_c_height __attribute__((sda));
extern int g_hud_text_param __attribute__((sda));
extern int g_hud_counter_text_x __attribute__((sda));
extern int g_hud_counter_text_y __attribute__((sda));
extern int g_hud_icon_d_x __attribute__((sda));
extern int g_hud_icon_d_y __attribute__((sda));
extern int g_hud_icon_d_width __attribute__((sda));
extern int g_hud_icon_d_height __attribute__((sda));
extern int g_hud_icon_d_offset_x __attribute__((sda));
extern int g_hud_draw_counter __attribute__((sda));

extern void *table_find_by_id(unsigned char *, int);
extern void gfx_draw_scaled_object_two_axes(char *, int, float, float, float, float, float);
extern int GetIconFrame(int, int);
extern void hud_draw_sprite_gradient(int, int, int, int, int, int *);
extern void gfx_draw_screen_rectangle(int, int, int, int, int, void *);
extern int sprintf(char *, char *, ...);
extern int func_001157AC(char *);
extern int text_draw_centered_medium(int, int, U64, unsigned char *, int);
extern char *GetLocalizedString(int);
extern int level_l00_call_module_handler_with_arg_9_us2(int, int);
extern void func_US2_0029DA88(int, int, int);
extern int math_fast_float_d(void *);
extern void FontSetWindow(unsigned short *, int, int, int, int, int, int, int, int);
extern void level_forward_draw_args_us2(int, int, int, int, int, int, int, int, int, int);
extern void hud_draw_scaled_us2(void);

/* Screen-space y coordinates take an extra offset in display mode 1. */
static __inline__ int Y3(float y) {
    if (g_hud_l23_layout_mode == 1)
        return (int)(y + 3.0f);
    return (int)y;
}
static __inline__ int Y1x(float y, int one, float unit) {
    if (g_hud_l23_layout_mode == one)
        return (int)(y + unit);
    return (int)y;
}
static __inline__ int Coord(float value, float offset) {
    float scaled = value * g_hud_scale_y + 0.5f;
    if (g_hud_l23_layout_mode == 1)
        return (int)(scaled + offset);
    return (int)scaled;
}

/* A coordinate scaled for the display and rounded to a whole pixel (upstream's scaled_coord,
   src/levels/02_maktar_nebula/L02_003FF6E8-g8.c, with this level's display-mode word). */
static __inline__ int scaled_coord(int value, float scale, float half, int active)
{
    int mode = g_hud_l23_layout_mode;
    float scaled = (float)value * scale + half;
    int result = (int)scaled;

    if (result != 0 && mode == active)
        scaled = 1.0f;
    return result;
}

/* A text or sprite label's y, scaled for the display and rounded (the accepted label_y). */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = g_hud_l23_layout_mode;
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

/* Draw the encounter's meters, counters and optional prompt panel. */
int L23_DrawEncounterHud_us2(void) {
    char text_buffer[64];
    char *text;
    ColorView color;
    unsigned short panel[16];
    char *state = *(char **)(g_mothership_boss_moby + 0x68);
    int x, y, right, width, width2;
    int one, one2;
    float half, half2, unit, round;
    float ratio, ratio2;
    HudCounters *hud;
    int label, hint;

    {
        int sprite = table_find_by_id((unsigned char *)g_hud_l23_sprite_base + 0x8710, 195);
        float sy = g_hud_label_y_scale * g_hud_scale_y + 0.5f;
        sy = (float)Y3(sy);
        gfx_draw_scaled_object_two_axes((char *)sprite, 0x60442D00, g_hud_label_x_position, sy, 1.0f, 1.0f, 0.0f);
    }
    {
        int sprite = table_find_by_id((unsigned char *)g_hud_l23_sprite_base + 0x8710, 196);
        float sy = g_hud_label_y_scale * g_hud_scale_y + 0.5f;
        sy = (float)Y3(sy);
        gfx_draw_scaled_object_two_axes((char *)sprite, 0x60241700, g_hud_label_x_position, sy, 1.0f, 1.0f, 0.0f);
    }
    {
        int sprite = table_find_by_id((unsigned char *)g_hud_l23_sprite_base + 0x8710, 197);
        float sy = g_hud_label_y_scale * g_hud_scale_y + 0.5f;
        sy = (float)Y3(sy);
        unit = 1.0f;
        half = 0.5f;
        one = 1;
        gfx_draw_scaled_object_two_axes((char *)sprite, 0x55F0C070, g_hud_label_x_position, sy, unit, unit, 0.0f);
    }
    {
        int sprite = GetIconFrame(0xEAA4, one);
        int v = label_y((void *)sprite, (float)g_hud_icon_a_y, g_hud_scale_y, half, 1);
        hud_draw_sprite_gradient(sprite, g_hud_icon_a_x, v, g_hud_icon_a_width, g_hud_icon_a_height, g_hud_gradient_colors);
    }
    {
        int sprite = GetIconFrame(0xEAA4, 2);
        int v = label_y((void *)sprite, (float)g_hud_icon_b_y, g_hud_scale_y, half, 1);
        hud_draw_sprite_gradient(sprite, g_hud_icon_b_x, v, g_hud_icon_b_width, g_hud_icon_b_height, g_hud_gradient_colors);
    }
    ratio = (float)*(int *)(g_hero_state + 0x1874) / (float)*(short *)(state + 0x2F4);
    x = g_hud_bar_margin_x + g_hud_bar_inset_x + g_hud_bar_fill_pad_x;
    y = g_hud_bar_top_y + g_hud_bar_row_height / 2 - g_hud_bar_thickness / 2;
    width = g_hud_bar_full_width;
    color.half[0] = g_hud_label_color_top;
    color.half[1] = g_hud_label_color_bottom;
    color.word[1] = (color.word[1] & 0xFFFF00FF) | ((int)(ratio * 255.0f) << 8);
    g_hud_draw_counter++;
    gfx_draw_screen_rectangle(x, y, x + (int)(ratio * (float)width), y + g_hud_bar_thickness, 0xFFFFF1, &color);
    ratio2 = *(float *)(state + 0x20) / (float)*(short *)(state + 0x2F6);
    width2 = g_hud_bar_full_width;
    color.half[0] = g_hud_label_color_top_alt;
    color.half[1] = g_hud_label_color_bottom_alt;
    right = g_screen_width - g_hud_bar_margin_x - g_hud_bar_inset_x - 4;
    color.word[0] = (color.word[1] & 0xFFFF00FF) | ((int)(ratio2 * 255.0f) << 8);
    gfx_draw_screen_rectangle(right - (int)(ratio2 * (float)width2), y, right, y + g_hud_bar_thickness, 0xFFFFF1, &color);
    {
        int sprite = GetIconFrame(0xEAA5, 0);
        float sy = (float)g_hud_icon_c_y * g_hud_scale_y + half;
        hud_draw_sprite_gradient(sprite, g_hud_icon_c_x, Y1x(sy, one, unit), g_hud_icon_c_width, g_hud_icon_c_height, g_hud_gradient_colors);
    }
    one2 = 1;
    half2 = 0.5f;
    hud = &g_hud_counters;
    sprintf(text_buffer, g_str_hud_counter_format, hud->counter);
    text = text_buffer;
    text_draw_centered_medium(g_hud_counter_text_x, scaled_coord(g_hud_counter_text_y, g_hud_scale_y, half2, 1),
                  g_hud_text_param, (unsigned char *)text, func_001157AC(text));
    if (hud->icons) {
        int sprite = GetIconFrame(0xEAA5, one2);
        float sy = (float)g_hud_icon_d_y * g_hud_scale_y + half2;
        hud_draw_sprite_gradient(sprite, g_hud_icon_d_x, Y1x(sy, one2, 1.0f), g_hud_icon_d_width, g_hud_icon_d_height, g_hud_gradient_colors);
    }
    if (g_hud_counters.icons >= 2) {
        int sprite = GetIconFrame(0xEAA5, 1);
        int x2 = g_hud_icon_d_x + g_hud_icon_d_offset_x;
        hud_draw_sprite_gradient(sprite, x2, Coord((float)g_hud_icon_d_y, 1.0f), g_hud_icon_d_width, g_hud_icon_d_height, g_hud_gradient_colors);
    }
    if (g_boss_hud_stat_index != -1 && g_boss_hud_timer == 0) {
        switch (g_boss_hud_stat_index) {
        case 0:
            level_l00_call_module_handler_with_arg_9_us2(GetLocalizedString(0x2e39), -1);
            break;
        case 2:
            GetLocalizedString(0x1241);
            func_US2_0029DA88(0x1241, *(short *)(state + 0x2FC), -1);
            break;
        case 1:
            GetLocalizedString(0x1240);
            func_US2_0029DA88(0x1240, g_boss_hud_stat_value, -1);
            break;
        }
        g_boss_hud_display_timer = 0;
        math_fast_float_d(&g_boss_hud_display_timer);
        if (g_boss_hud_display_timer <= 0)
            g_boss_hud_stat_index = -1;
    }
    round = 0.5f;
    if (g_boss_part_age_counter) {
        FontSetWindow(panel, 240, 480, 44, 468, 256, scaled_coord(320, g_hud_scale_y, round, 1), 16, 3);
        label = GetLocalizedString(0x9FC);
        hint = GetLocalizedString(0x2dc2);
        level_forward_draw_args_us2((int)panel, 0x80F0F0F0, label, 0, 0, -1, 0, hint, 0, 0);
    }
    hud_draw_scaled_us2();
    return 1;
}
