#include "names.h"
/* func_US2_L03_003C8620 (656 bytes, Endako): the USA v2.00 copy of func_L03_003C7018
 * (src/levels/03_endako/L03_003C7018-menu.c), the two-line menu panel: the same code, only
 * its addresses and its four text ids (v2.00 numbers its text differently) differ. Same C
 * and unit flags (config/cflags.txt); label_y/label_y2 are the dead-test helpers allowed by
 * owner ruling (7 November 2026). */
#include "common.h"

struct MenuCoordinate { float x, y; };
extern unsigned char *g_menu_data_base __attribute__((sda));
extern float g_panel_text_x SDATA(D_L03_001B014C);
extern float g_panel_title_y SDATA(D_L03_001B0150);
extern float g_panel_param_c SDATA(D_L03_001B0154);
extern float g_panel_param_d SDATA(D_L03_001B0158);
extern struct MenuCoordinate g_panel_line_coords[] SDATA(D_L03_001B0160);
extern int g_remote_view_index SDATA(D_L03_001B0140);
extern int g_screen_l03_mode __attribute__((sda));
extern float g_screen_l03_scale __attribute__((sda));
extern char g_str_panel_label_format[], g_str_menu_label_format[];
extern unsigned char g_panel_line_flag[] __attribute__((sda));
extern void *table_find_by_id(unsigned char *, int);
extern void gfx_draw_scaled_object_two_axes(char *, int, float, float, float, float, float);
extern char *GetLocalizedString(int);
extern int sprintf(char *, char *, ...);
extern int FloatToInt(float);
extern int text_draw_centered_medium(int, int, unsigned long, unsigned char *, int);
extern void sub_object_get_value_first(char *);
extern void sub_object_get_value_second(char *);

static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = g_screen_l03_mode;
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
static __inline__ int label_y2(void *handle, float value, float scale, float half, int active)
{
    int mode = g_screen_l03_mode;
    float scaled = value * scale + half;
    int result = (int)scaled;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = half;
    return result;
}

static __inline__ int screen_coord(int mode, float value, float offset, int one)
{
    float scaled = value * g_screen_l03_scale + 0.5f;

    if (mode == one)
        return (int)(scaled + offset);
    return (int)scaled;
}

int menu_draw_two_line_panel_us2(void)
{
    if (g_menu_data_base) {
        int one;
        int i;

        {
            char *title;
            float row, x, c, d;

            do {
                title = (char *)table_find_by_id(g_menu_data_base + 0x8710, 0xc6);
                row = (float)label_y(title, g_panel_title_y, g_screen_l03_scale, 0.5f, 1);
                x = g_panel_text_x;
                c = g_panel_param_c;
                d = g_panel_param_d;
            } while (0);
            gfx_draw_scaled_object_two_axes(title, 0x60442d00, x, row, c, d, 0.0f);
        }
        {
            char *title;
            float row, x, c, d;

            do {
            do {
                title = (char *)table_find_by_id(g_menu_data_base + 0x8710, 0xc7);
                row = (float)label_y2(title, g_panel_title_y, g_screen_l03_scale, 0.5f, 1);
                x = g_panel_text_x;
                c = g_panel_param_c;
                d = g_panel_param_d;
            } while (0);
            do {
                gfx_draw_scaled_object_two_axes(title, 0x55f0c070, x, row, c, d, 0.0f);
                i = 0;
            } while (0);
            } while (0);
        }
        one = 1;
        {
            int keys[4] = {11237,11754,12407,12408};
            unsigned char buffer[128];
            unsigned char *buf;
            buf = buffer;
            do {
                int shift = 5;
                int x;
                unsigned char *label = GetLocalizedString(keys[i]);
                if (i == one) {
                    sprintf((char *)buf, g_str_panel_label_format, label, g_remote_view_index + 1);
                    shift = -4;
                } else {
                    sprintf((char *)buf, g_str_menu_label_format, label);
                }
                x = FloatToInt(g_panel_line_coords[i].x);
                text_draw_centered_medium(x, FloatToInt((float)screen_coord(g_screen_l03_mode, g_panel_line_coords[i].y, (float)shift, one)), 0x80808080UL, buf, 0x80);
                i++;
            } while (i < 4);
        }
        if (g_panel_line_flag[0]) {
            sub_object_get_value_first((char *)g_menu_data_base + 0x36f28);
            sub_object_get_value_second((char *)g_menu_data_base + 0x36f28);
        }
    }
    return 1;
}
