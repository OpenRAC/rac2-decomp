#include "names.h"
/* func_PAL_0034B088, the PAL copy of func_00348EC0: the same C, where the menu fields move to 0x4A4, the rows are 88 bytes and the colour call is func_PAL_002A9FA0. */
#include "common.h"

extern int math_ping_pong_blend_values_pal(int, int, int, int, int);
extern void gfx_draw_screen_element_stored(char *);
extern float *object_get_first_field(char *);
extern int *object_get_fourth_field(char *);
extern float g_list_menu_label_y __attribute__((sda));
extern float g_hud_scale[] MACRO_ADDR;
extern int g_screen_height[] MACRO_ADDR;
extern float g_centered_rows_rect_x_offset __attribute__((sda));
extern float g_centered_rows_rect_y_base[] MACRO_ADDR;
extern float g_centered_rows_rect_y_step __attribute__((sda));
extern float g_centered_rows_alt_x_offset __attribute__((sda));
extern float g_centered_rows_alt_y_base[] MACRO_ADDR;
extern float g_centered_rows_alt_y_step __attribute__((sda));

typedef struct { float x, y, w, h; } ListRect;
typedef struct {
    char pad[0x4A4];
    ListRect *origin;
    int unknown438;
    int selected;
    int enabled;
    int count;
    int show_special;
} ListMenu;
typedef struct { short pad[4]; short offset; short pad2; void (*call)(char *); } ListVtable;
typedef struct {
    ListRect *position;
    ListRect *scale;
    void *parameter08;
    unsigned int *colors;
    float *visibility;
    char lifetime[0x1C];
    ListVtable *table;
    void *metrics;
    unsigned long style;
    char *text;
    int alignment;
    int extra[4];
} ListSlot;

extern int g_hud_mode;

/* label_y, the HUD label idiom (the shared definition in src/levels/15_gorn/L15_00431590-g8.c, its
   mode word the boot's D_001B23A0). Its tests do not change the result: flow deletes their stores
   and jump2 their jumps, but only after allocation and both scheduling passes, which see the block
   they end. Here it rounds the list row spacing. */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = g_hud_mode;
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

/* Draws the list menu's background and its rows centered vertically on screen, highlighting the selected row. (PAL) */
void list_menu_draw_centered_rows_pal(char *list)
{
    int color = math_ping_pong_blend_values_pal(0x20FFFEED, 0x70FFFEED, 20, 0, 0);
    int first_y, i, row_height, half_height, row_count;
    float half, row_height_f;
    ListMenu *menu = (ListMenu *)list;

    if (menu->enabled) {
        gfx_draw_screen_element_stored(list);
        gfx_draw_screen_element_stored(list + 0x130);
        gfx_draw_screen_element_stored(list + 0x4C);
        gfx_draw_screen_element_stored(list + 0x98);
        gfx_draw_screen_element_stored(list + 0xE4);
        row_count = menu->count;
        half = (float)row_count * 0.5f;
        row_height = label_y(list, g_list_menu_label_y, g_hud_scale[0], 0.5f, 1);
        row_height_f = (float)row_height;
        half_height = g_screen_height[0] >> 1;
        first_y = (int)((float)half_height - row_height_f * half);
        for (i = 0; i < menu->count; i++) {
            ListRect *pos;
            char *slot;
            ListVtable *vtable;
            int row_color;

            if (i == 7 && !menu->show_special)
                continue;
            pos = (ListRect *)((float *)object_get_first_field(list + 0x17C));
            pos->x = g_centered_rows_rect_x_offset + menu->origin->x;
            pos->y = (g_centered_rows_rect_y_base[0] + (float)i * g_centered_rows_rect_y_step) + (float)first_y;
            row_color = i == menu->selected ? color : 0x55F0C070;
            *((int *)object_get_fourth_field(list + 0x1C8)) = row_color;
            gfx_draw_screen_element_stored(list + 0x17C);
            pos = (ListRect *)((float *)object_get_first_field(list + 0x1C8));
            pos->x = g_centered_rows_rect_x_offset + menu->origin->x;
            pos->y = (g_centered_rows_rect_y_base[0] + (float)i * g_centered_rows_rect_y_step) + (float)first_y;
            gfx_draw_screen_element_stored(list + 0x1C8);
            slot = (char *)&((ListSlot *)(list + 0x218))[i];
            pos = (ListRect *)((float *)object_get_first_field(slot));
            pos->x = g_centered_rows_alt_x_offset + menu->origin->x;
            pos->y = (g_centered_rows_alt_y_base[0] + (float)i * g_centered_rows_alt_y_step) + (float)first_y;
            vtable = *(ListVtable **)(list + i * 88 + 0x248);
            row_height = vtable->offset;
            vtable->call(slot + row_height);
        }
    }
}
