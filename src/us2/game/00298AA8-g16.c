#include "common.h"

/* func_US2_00298AA8: new in USA v2.00, no v1.01 counterpart. On levels 8 and 19 it pulses a marker
 * on the map (an arrow with a shadow, or an icon) over every moby of the classes the level lists. */
typedef struct MapMarkerMoby {
    char pad_00[0x10];
    float x;
    float y;
    char pad_18[0x8];
    unsigned char state;
    char pad_21[0x89];
    short oClass;
    char pad_ac[0x54];
} MapMarkerMoby;

extern int g_current_map_index MACRO_ADDR;
extern MapMarkerMoby *g_moby_context_first MACRO_ADDR;
extern MapMarkerMoby *g_moby_context_second MACRO_ADDR;
extern int g_screen_line_table_a[4] __attribute__((sda));
extern int g_screen_line_table_b[4] __attribute__((sda));
extern int g_screen_line_color_a __attribute__((sda));
extern int g_screen_line_color_b __attribute__((sda));
extern unsigned char g_pulse_alpha __attribute__((sda));
extern unsigned char g_pulse_step_up __attribute__((sda));
extern unsigned char g_pulse_step_down __attribute__((sda));
extern int g_pulse_rising __attribute__((sda));
extern int g_screen_line_spread __attribute__((sda));
extern s32 g_screen_line_offset __attribute__((sda));

/* The callers load all five arguments, though this body reads only the two pointers. */
extern int GetSpecialMapCoordinates(float x, float y, float *u, float *v, int level);
extern void map_convert_world_to_map_position(float x, float y, float *u, float *v, int level);
extern int GetIconFrame(int key, int index);
extern void DrawHudSpriteSubpixel(int icon, int x, int y, int w, int h, int alpha, unsigned int color);
extern void gfx_draw_screen_line(int x0, int y0, int x1, int y1, u64 color, int flags);

void map_draw_class_markers_us2(float x0, float x1, float y0, float y1, float scale)
{
    float u;
    float v;
    int *table;
    int color;
    int i;
    int j;
    int y;
    int px;
    float size;
    int icon;
    MapMarkerMoby *m;

    switch (g_current_map_index) {
    case 8:
        table = g_screen_line_table_a;
        color = g_screen_line_color_a;
        break;
    case 19:
        table = g_screen_line_table_b;
        color = g_screen_line_color_b;
        break;
    default:
        return;
    }

    g_pulse_alpha = g_pulse_rising ? g_pulse_alpha + g_pulse_step_up : g_pulse_alpha - g_pulse_step_down;
    if (g_pulse_alpha < 0x60 || g_pulse_alpha > 0xF0) {
        g_pulse_rising ^= 1;
        if (g_pulse_alpha > 0xF0) {
            g_pulse_alpha = 0xF0;
        }
        if (g_pulse_alpha < 0x30) {
            g_pulse_alpha = 0x30;
        }
    }

    for (i = 0; table[i] != 0 && i < 10; i++) {
        for (m = g_moby_context_first; m < g_moby_context_second; m++) {
            if (m == 0 || m->oClass != table[i] || m->state == 0xFE || m->state == 0xFD) {
                continue;
            }
            if (GetSpecialMapCoordinates(m->x, m->y, &u, &v, g_current_map_index) == 0) {
                map_convert_world_to_map_position(m->x, m->y, &u, &v, g_current_map_index);
            }
            u = x0 + u * (x1 - x0);
            v = y0 + v * (y1 - y0);
            if (g_current_map_index == 8) {
                px = (int)u >> 4;
                y = ((int)v >> 4) - 8;
                for (j = 0; j < 3; j++, y++) {
                    gfx_draw_screen_line(px - g_screen_line_spread - j + g_screen_line_offset, y + g_screen_line_offset,
                                  px + g_screen_line_spread + j + g_screen_line_offset, y + g_screen_line_offset,
                                  (g_pulse_alpha << 23) | 0x80000000, 0);
                }
                for (j = 0; j < 5; j++, y++) {
                    gfx_draw_screen_line(px - g_screen_line_spread + j + g_screen_line_offset, y + g_screen_line_offset,
                                  px + g_screen_line_spread - j + g_screen_line_offset, y + g_screen_line_offset,
                                  (g_pulse_alpha << 23) | 0x80000000, 0);
                }
                y = ((int)v >> 4) - 8;
                for (j = 0; j < 3; j++, y++) {
                    gfx_draw_screen_line(px - g_screen_line_spread - j, y, px + g_screen_line_spread + j, y,
                                  color | (g_pulse_alpha << 23), 0);
                }
                for (j = 0; j < 5; j++, y++) {
                    gfx_draw_screen_line(px - g_screen_line_spread + j, y, px + g_screen_line_spread - j, y,
                                  color | (g_pulse_alpha << 23), 0);
                }
            } else {
                icon = GetIconFrame(0xE99E, 0);
                size = scale * 128.0f;
                DrawHudSpriteSubpixel(icon, u, v, size + 24.0f, size + 24.0f, g_pulse_alpha, 0x80000000);
                DrawHudSpriteSubpixel(GetIconFrame(0xE99E, 0), u, v, size, size, g_pulse_alpha, color);
            }
        }
    }
}
