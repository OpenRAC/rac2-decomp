#include "names.h"
/* func_PAL_0034B088, the PAL copy of func_00348EC0: the same C, where the menu fields move to 0x4A4, the rows are 88 bytes and the colour call is func_PAL_002A9FA0. */
#include "common.h"

extern int func_PAL_002A9FA0(int, int, int, int, int);
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

void list_menu_draw_centered_rows_pal(char *o)
{
    int color = func_PAL_002A9FA0(0x20FFFEED, 0x70FFFEED, 20, 0, 0);
    int start, i, sp, h, n;
    float half, spf;
    ListMenu *menu = (ListMenu *)o;

    if (menu->enabled) {
        gfx_draw_screen_element_stored(o);
        gfx_draw_screen_element_stored(o + 0x130);
        gfx_draw_screen_element_stored(o + 0x4C);
        gfx_draw_screen_element_stored(o + 0x98);
        gfx_draw_screen_element_stored(o + 0xE4);
        n = menu->count;
        half = (float)n * 0.5f;
        sp = label_y(o, g_list_menu_label_y, g_hud_scale[0], 0.5f, 1);
        spf = (float)sp;
        h = g_screen_height[0] >> 1;
        start = (int)((float)h - spf * half);
        for (i = 0; i < menu->count; i++) {
            ListRect *p;
            char *slot;
            ListVtable *v;
            int c;

            if (i == 7 && !menu->showSpecial)
                continue;
            p = (ListRect *)((float *)object_get_first_field(o + 0x17C));
            p->x = g_centered_rows_rect_x_offset + menu->origin->x;
            p->y = (g_centered_rows_rect_y_base[0] + (float)i * g_centered_rows_rect_y_step) + (float)start;
            c = i == menu->selected ? color : 0x55F0C070;
            *((int *)object_get_fourth_field(o + 0x1C8)) = c;
            gfx_draw_screen_element_stored(o + 0x17C);
            p = (ListRect *)((float *)object_get_first_field(o + 0x1C8));
            p->x = g_centered_rows_rect_x_offset + menu->origin->x;
            p->y = (g_centered_rows_rect_y_base[0] + (float)i * g_centered_rows_rect_y_step) + (float)start;
            gfx_draw_screen_element_stored(o + 0x1C8);
            slot = (char *)&((ListSlot *)(o + 0x218))[i];
            p = (ListRect *)((float *)object_get_first_field(slot));
            p->x = g_centered_rows_alt_x_offset + menu->origin->x;
            p->y = (g_centered_rows_alt_y_base[0] + (float)i * g_centered_rows_alt_y_step) + (float)start;
            v = *(ListVtable **)(o + i * 88 + 0x248);
            sp = v->offset;
            v->call(slot + sp);
        }
    }
}
