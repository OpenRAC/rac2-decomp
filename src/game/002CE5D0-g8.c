#include "common.h"

extern int g_hud_mode;
extern float g_hud_scale;
extern float g_menu_screen_y_scale_a __attribute__((sda));
extern float g_menu_alpha_scale __attribute__((sda));
extern char *g_resident_data_base;
extern struct { int w0, w1, w2; } g_pad_menu_flags;
extern void *table_find_by_id(void *, int);
extern int math_ping_pong_blend_values(int, int, int, int, int);
extern void AppendScreenRectPacket(int, int, int, int, u64, int);
extern void gfx_draw_scaled_object_two_axes(char *, int, float, float, float, float, float);

static __inline__ int menu_screen_y(float value, float offset)
{
    float y = value * g_hud_scale + 0.5f;
    if (g_hud_mode != 1)
        return (int)y;
    return (int)(y + offset);
}

/* Draws the two small frames at the bottom and the left and right arrows used to page through a menu. */
void DrawMenuNavigationFramesAndLabels(int show_left, int show_right)
{
    int dim_color, sprite;

    AppendScreenRectPacket(42, menu_screen_y(318.0f, g_menu_screen_y_scale_a), 44, menu_screen_y(343.0f, g_menu_screen_y_scale_a), 0x55F0C070, 0);
    AppendScreenRectPacket(64, menu_screen_y(318.0f, g_menu_screen_y_scale_a), 66, menu_screen_y(343.0f, g_menu_screen_y_scale_a), 0x55F0C070, 0);
    AppendScreenRectPacket(42, menu_screen_y(317.0f, g_menu_screen_y_scale_a), 66, menu_screen_y(319.0f, g_menu_screen_y_scale_a), 0x55F0C070, 0);
    AppendScreenRectPacket(42, menu_screen_y(342.0f, g_menu_screen_y_scale_a), 66, menu_screen_y(344.0f, g_menu_screen_y_scale_a), 0x55F0C070, 0);
    AppendScreenRectPacket(463, menu_screen_y(318.0f, g_menu_screen_y_scale_a), 465, menu_screen_y(343.0f, g_menu_screen_y_scale_a), 0x55F0C070, 0);
    AppendScreenRectPacket(485, menu_screen_y(318.0f, g_menu_screen_y_scale_a), 487, menu_screen_y(343.0f, g_menu_screen_y_scale_a), 0x55F0C070, 0);
    AppendScreenRectPacket(463, menu_screen_y(317.0f, g_menu_screen_y_scale_a), 487, menu_screen_y(319.0f, g_menu_screen_y_scale_a), 0x55F0C070, 0);
    AppendScreenRectPacket(463, menu_screen_y(342.0f, g_menu_screen_y_scale_a), 487, menu_screen_y(344.0f, g_menu_screen_y_scale_a), 0x55F0C070, 0);
    dim_color = math_ping_pong_blend_values(0x60241700, 0x55F0C070, 25, 0, 0);
    if (show_left) {
        char *root = g_resident_data_base;
        int selected = 0x80F0F0F0;
        if (!(g_pad_menu_flags.w0 & 0x8000))
            selected = dim_color;
        sprite = table_find_by_id(root + 0x8710, 75);
        gfx_draw_scaled_object_two_axes((char *)sprite, selected, 213.0f, 322.0f, 1.0f, g_menu_alpha_scale, 0.0f);
    }
    if (show_right) {
        char *root = g_resident_data_base;
        int selected = 0x80F0F0F0;
        if (!(g_pad_menu_flags.w0 & 0x2000))
            selected = dim_color;
        sprite = table_find_by_id(root + 0x8710, 74);
        gfx_draw_scaled_object_two_axes((char *)sprite, selected, 311.0f, 322.0f, 1.0f, g_menu_alpha_scale, 0.0f);
    }
}
