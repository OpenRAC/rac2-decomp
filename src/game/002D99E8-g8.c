/* Menu list page: draws a title, then one text row per entry of the scratchpad list. The selected
 * row is highlighted and scrolled into view; a check box beside each row shows its mask bit.
 * `limit` is one local for both the text's x and the top bound: being set twice sends it to
 * global-alloc, which is what gives the local scroll value $v0 and leaves it $v1. */
#include "common.h"

typedef struct { u16 top, bottom, left, right, x, y, width, height, line, flags, extra0, extra1; } TextBox_002D99E8;
typedef struct {
    char pad0[0x18];
    int x, y, width, height;      /* 0x18 */
    char pad1[0x30 - 0x28];
    int selected[29];             /* 0x30 */
    int scroll;                   /* 0xA4 */
} Menu_002D99E8;
extern int D_001AB910 __attribute__((sda));
extern int D_001ABB28 __attribute__((sda));
extern int g_map_overlay_state[];
extern void SetupGifPaging(int);
extern int menu_list_active_entries(int *, int *, int *, int);
extern void VU1_addGSregister(unsigned int, unsigned long);
extern char *GetLocalizedString(int);
extern void text_draw_small(int, int, long, signed char *, int);
extern void *memset(void *, int, unsigned int);
extern void gfx_draw_rounded_box(int, int, int, int, int, int);
extern void gfx_disable_screen_flag(void);
extern void gfx_enable_screen_flag(void);
extern void DoGifPaging(void);
extern void text_draw_window_medium(TextBox_002D99E8 *, int, signed char *, int);
extern void DrawMenuCheckBox(int, int, int);

int DrawMenuCheckList(Menu_002D99E8 *menu)
{
    TextBox_002D99E8 draw, initial;
    int mask;
    int x, y, count, i, selected, color, rows, iconY;
    int iconX, iconTop, limit;
    int *list;
    int *base;

    mask = 0;
    y = 4;
    x = 4;
    SetupGifPaging(0);
    list = (int *)0x70000000;
    count = menu_list_active_entries(list, &mask, 0, 0);
    VU1_addGSregister(0x42, 0x44);
    VU1_addGSregister(0x47, 0x10B);
    if (!D_001AB910) {
        x = menu->x;
        y = menu->y;
    }
    text_draw_small(x, y, 0x80FFA888, (signed char *)GetLocalizedString(0x2DC5), -1);
    y += 20;
    memset(&initial, 0, 24);
    initial.bottom = menu->height;
    initial.right = menu->width;
    initial.line = 16;
    initial.top = y;
    initial.left = x;
    draw = initial;
    if (D_001ABB28)
        gfx_draw_rounded_box(y, menu->height, x, menu->width, 64, 0x202020);
    for (i = 0; i < count; i++) {
        iconX = x + 4;
        iconY = y + 10;
        base = g_map_overlay_state;
        selected = menu->selected[base[0x230 / 4]] == i;
        color = selected ? 0x8020FFFF : 0x80FFA888;
        if (selected)
            gfx_disable_screen_flag();
        limit = x + 16;
        draw.x = limit;
        draw.y = y - menu->scroll;
        text_draw_window_medium(&draw, color, (signed char *)GetLocalizedString(list[i]), -1);
        if (selected) {
            if ((s16)draw.y < (limit = (s16)draw.top + 4))
                menu->scroll -= 4;
            if ((s16)draw.bottom - (s16)draw.height - 4 < (s16)draw.y)
                menu->scroll += 4;
            gfx_enable_screen_flag();
        }
        rows = (s16)draw.height / (s16)draw.line;
        if (rows == 2)
            iconY += 6;
        iconTop = iconY - menu->scroll;
        if ((s16)draw.top + 4 <= iconTop && iconTop <= (s16)draw.bottom - 4)
            DrawMenuCheckBox(iconX + 5, iconTop, (mask >> i) & 1);
        y += rows * 16;
    }
    DoGifPaging();
    return 2;
}
