#include "include_asm.h"
#include "common.h"

/* func_US2_L02_003C58E0 (USA v2.00, levels 2, 3, 4, 9, 12, 17, 20 and 30): the v2.00 copy of
   func_L02_003C43F0. It uses v2.00's text ids, and its two header labels move up one pixel
   when the display mode is 1. */

extern void *table_find_by_id(char *, int);
extern void gfx_draw_scaled_object_two_axes(char *, int, float, float, float, float, float);
extern void VU1_addGSregister(int, unsigned long);
extern char *GetLocalizedString(int);
extern int text_draw_centered_large(int, int, u64, char *, int);
extern char *g_arena_menu_base;
extern float g_hud_label_scale;
extern int g_hud_l02_mode;

static __inline__ int menu_coord(float scale, float value, float half, int active)
{
    float scaled = scale * value + half;
    int result = (int)scaled;

    if (result != 0 && g_hud_l02_mode == active)
        scaled = 1.0f;
    return result;
}

static __inline__ int header_y(float value, float scale, float half, int active)
{
    float scaled = scale * value + half;

    if (g_hud_l02_mode == active)
        return (int)(scaled + -1.0f);
    return (int)scaled;
}

static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = g_hud_l02_mode;
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

void func_US2_L02_003C58E0(char *obj) {
    char *text;
    int state;
    char *id;
    int y, on, entry;
    float one, zero, half, k, s;

    entry = 0x8710;
    k = 203.0f;
    half = 0.5f;
    on = 1;
    id = table_find_by_id(g_arena_menu_base + entry, 0x70);
    y = menu_coord(g_hud_label_scale, k, half, on);
    one = 1.0f;
    zero = 0.0f;
    s = (float)y;
    gfx_draw_scaled_object_two_axes(id, 0x60442D00, 258.0f, s, one, one, zero);
    gfx_draw_scaled_object_two_axes(table_find_by_id(g_arena_menu_base + entry, 0x6F), 0x60442D00, 258.0f,
                  (float)menu_coord(g_hud_label_scale, k, half, on), one, one, zero);
    gfx_draw_scaled_object_two_axes(table_find_by_id(g_arena_menu_base + entry, 0x71), 0x55F0C070, 258.0f,
                  (float)menu_coord(g_hud_label_scale, k, half, on), one, one, zero);
    id = table_find_by_id(g_arena_menu_base + entry, 0x72);
    y = menu_coord(g_hud_label_scale, k, half, on);
    s = one;
    gfx_draw_scaled_object_two_axes(id, 0x55F0C070, 258.0f, (float)y, s, s, zero);
    VU1_addGSregister(0x47, 0x5360BUL);
    state = *(unsigned char *)(obj + 0x20);
    if (state == 7) {
        text = GetLocalizedString(0x2DF2);
        text_draw_centered_large(254, header_y(23.0f, g_hud_label_scale, half, on), 0x88FFFFFF, text, -1);
    } else if (state != 8 && state != 5) {
        text = GetLocalizedString(0x2DF1);
        text_draw_centered_large(262, header_y(23.0f, g_hud_label_scale, half, on), 0x88FFFFFF, text, -1);
    }
    text = GetLocalizedString(0x2DF0);
    text_draw_centered_large(254, label_y(text, 373.0f, g_hud_label_scale, 0.5f, 1), 0x88FFFFFF, text, -1);
}
