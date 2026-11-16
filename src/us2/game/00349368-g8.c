#include "common.h"

/* func_US2_00349C00, the v2.00 copy of func_00348EC0 (src/game/00345358-g8.c): the same C, where the
   menu's fields lie 0x70 bytes further in and each label slot is 88 bytes, not 72.
   func_00348EC0 draws the list menu's rows centred on the screen. The row spacing is rounded with
   label_y after the row count is read; that block end is what gives retail's count, spacing and
   0.5 registers. Standalone declarations, the boot's addresses. */

extern int math_ping_pong_blend_values(int, int, int, int, int);
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
    int showSpecial;
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
    char reserved48[0x10];
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

/* Draws the list menu's rows centred on the screen: the background pieces, then each row's highlight, label
   box and text, with the selected row brighter. (USA v2.00) */
void list_menu_draw_centered_rows_us2(char *object)
{
    int selected_color = math_ping_pong_blend_values(0x20FFFEED, 0x70FFFEED, 20, 0, 0);
    int top_y, i, row_height, half_height, row_count;
    float half_rows, row_height_f;
    ListMenu *menu = (ListMenu *)object;

    if (menu->enabled) {
        gfx_draw_screen_element_stored(object);
        gfx_draw_screen_element_stored(object + 0x130);
        gfx_draw_screen_element_stored(object + 0x4C);
        gfx_draw_screen_element_stored(object + 0x98);
        gfx_draw_screen_element_stored(object + 0xE4);
        row_count = menu->count;
        half_rows = (float)row_count * 0.5f;
        row_height = label_y(object, g_list_menu_label_y, g_hud_scale[0], 0.5f, 1);
        row_height_f = (float)row_height;
        half_height = g_screen_height[0] >> 1;
        top_y = (int)((float)half_height - row_height_f * half_rows);
        for (i = 0; i < menu->count; i++) {
            ListRect *rect;
            char *slot;
            ListVtable *vtable;
            int row_color;

            if (i == 7 && !menu->showSpecial)
                continue;
            rect = (ListRect *)((float *)object_get_first_field(object + 0x17C));
            rect->x = g_centered_rows_rect_x_offset + menu->origin->x;
            rect->y = (g_centered_rows_rect_y_base[0] + (float)i * g_centered_rows_rect_y_step) + (float)top_y;
            row_color = i == menu->selected ? selected_color : 0x55F0C070;
            *((int *)object_get_fourth_field(object + 0x1C8)) = row_color;
            gfx_draw_screen_element_stored(object + 0x17C);
            rect = (ListRect *)((float *)object_get_first_field(object + 0x1C8));
            rect->x = g_centered_rows_rect_x_offset + menu->origin->x;
            rect->y = (g_centered_rows_rect_y_base[0] + (float)i * g_centered_rows_rect_y_step) + (float)top_y;
            gfx_draw_screen_element_stored(object + 0x1C8);
            slot = (char *)&((ListSlot *)(object + 0x218))[i];
            rect = (ListRect *)((float *)object_get_first_field(slot));
            rect->x = g_centered_rows_alt_x_offset + menu->origin->x;
            rect->y = (g_centered_rows_alt_y_base[0] + (float)i * g_centered_rows_alt_y_step) + (float)top_y;
            vtable = *(ListVtable **)(object + i * 88 + 0x248);
            row_height = vtable->offset;
            vtable->call(slot + row_height);
        }
    }
}
