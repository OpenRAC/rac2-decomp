/* func_PAL_002D6E30, the PAL copy of func_002D6230: the same C, where rename func_002D68D8 becomes func_PAL_002D74D8. */
#include "common.h"

/* A row of a text list: its label, its state (0 disabled, 2 shows the "unavailable" text),
 * the action's value, a second line and the timer of its highlight fade. */
typedef struct {
    short text_id;
    short enabled;
    int action_value;
    short secondary_text_id;
    short fade_timer;
} MenuItem_1C1B0;

typedef struct {
    unsigned char pad0[0x20];
    int width;
    int height;
    unsigned char pad28[8];
    int flags;
    MenuItem_1C1B0 *items;
    unsigned char pad38[8];
    int selected_entry;
} MenuDescriptor;

/* A menu page: the menu taking input is at +0xE8. */
typedef struct {
    char pad00[0xE8];
    MenuDescriptor *focus;
} MenuPage;

/* The menu system: its current page. */
typedef struct {
    char pad00[0x14];
    MenuPage *current;
} MenuSystem;

extern MenuSystem D_001F2840;
extern MenuPage D_00258EE8, D_00259018;
extern MenuDescriptor D_00259148, D_00259198, D_002591E8, D_00259238, D_00259288, D_002592D8;
extern unsigned char D_00263B50[], D_00263EF0[], D_00264290[];
/* Pairs of text ids: the id to look for, then the id of the text it is formatted with. */
extern int D_00258D70[];
extern char D_00210C40[], D_001ABAC8[];
extern int D_001AA444 __attribute__((sda)), D_001AA448 __attribute__((sda));
extern void func_002FC560(unsigned int, unsigned long);
extern void func_0027C540(int);
extern void func_0027F120(void);
extern void func_0027F110(void);
extern void func_0027C660(void);
extern void func_00282A60(void *, int, int);
extern unsigned long func_0027C878(int);
extern int func_0027F128(char *, int, unsigned char *);
extern int func_PAL_002D74D8(int, int, int);
extern int func_00115DA8(char *, char *, ...);
extern char *func_00288FB8(int);
extern void func_0027F2A8(int, int, unsigned long, char *, int, unsigned long, unsigned char *);

/* RAC1 pause.c render_localized_ui_entry_list, with RaC2's formatted-text rows. */
int func_PAL_002D6E30(MenuDescriptor *menu) {
    int selection_index;
    int entry_index;
    int focused;
    unsigned char *glyphs;
    int font_texture_index;
    int row_height;
    int half_width;
    int maximum_text_width;
    int font_height;
    int entry_count;
    MenuItem_1C1B0 *entry;
    MenuItem_1C1B0 *scan_entry;
    int selected_entry;
    int enabled;
    int color;
    char *text_id;
    char *secondary_text;
    int x;
    int y;
    int text_width;
    int flags;
    int menu_width;
    MenuItem_1C1B0 *selected_item;
    int shadow_y;
    int shadow_x;
    font_height = 12;
    font_texture_index = 1;
    glyphs = D_00263B50;
    focused = D_001F2840.current->focus == menu;
    if (menu->flags & 4) {
        font_height = 14;
        font_texture_index = 3;
        glyphs = D_00264290;
    }
    if (menu->flags & 8) {
        font_height = 10;
        font_texture_index = 2;
        glyphs = D_00263EF0;
    }
    func_002FC560(0x42, 0x44);
    func_002FC560(0x47, 0x2004B);
    func_0027C540(0);
    entry_count = 0;
    entry = menu->items;
    while (entry->text_id != 0) {
        entry++;
        entry_count++;
    }

    if (menu->flags & 0x10) {
        row_height = font_height + 3;
    } else {
        row_height = menu->height / (entry_count + 1);
    }
    half_width = menu->width >> 1;
    maximum_text_width = 0;
    y = (row_height - (font_height / 2)) - 1;
    if (menu->flags & 0x4000) {
        scan_entry = menu->items;
        if (scan_entry[0].text_id != 0) {
            entry_index = 0;
            do {
                text_width = func_0027F128(
                    func_00288FB8(scan_entry[entry_index].text_id), -1, glyphs);
                entry_index++;
                maximum_text_width =
                    (maximum_text_width < text_width) ? (text_width) : (maximum_text_width);
                scan_entry = menu->items;
            } while (menu->items[entry_index].text_id != 0);
        }
    }
    flags = menu->flags;
    menu_width = menu->width;
    if (flags & 0x20000) {
        if (menu_width < (maximum_text_width + 6)) {
            if (!(flags & 8)) {
                menu->flags = flags | 8;
                return 1;
            }
        }
    }
    selection_index = 0;
    maximum_text_width = (menu_width < maximum_text_width) ? (menu_width) : (maximum_text_width);
    if (menu->items[0].text_id != 0) {
        do {
            selected_entry = 0;
            if (focused) {
                selected_entry = menu->selected_entry == selection_index;
            }
            selected_item = (MenuItem_1C1B0 *)((unsigned int)(selection_index * sizeof(MenuItem_1C1B0)) + (unsigned int)menu->items);
            enabled = selected_item->enabled != 0;
            if (menu->flags & 2) {
                color = 0x80FFA888;
            } else if (selected_entry) {
                if (enabled) {
                    goto fade_timer;
                }
                color = 0x80006060;
            } else if (enabled) {
            fade_timer:
                color = func_PAL_002D74D8(selected_item->fade_timer, -1, -1);

            } else {
                color = 0x80303030;
            }
            text_id = func_00288FB8(menu->items[selection_index].text_id);
            if ((D_001F2840.current == &D_00258EE8 || D_001F2840.current == &D_00259018) &&
                (menu == &D_00259148 || menu == &D_00259198 || menu == &D_002591E8 ||
                 menu == &D_00259238 || menu == &D_00259288 || menu == &D_002592D8)) {
                int j, found = -1;
                j = 0;
                while (j < 14) {
                    if (D_00258D70[j] == menu->items[selection_index].text_id) {
                        found = j + 1;
                        break;
                    }
                    j += 2;
                }
                if (found >= 0) {
                    func_00282A60(D_00210C40, 0, 256);
                    text_id = func_00288FB8(menu->items[selection_index].text_id);
                    func_00115DA8(D_00210C40, D_001ABAC8,
                                 func_00288FB8(D_00258D70[found]), text_id);
                    text_id = D_00210C40;
                }
            }
            if (menu->items[selection_index].enabled == 2) {
                text_id = func_00288FB8(0xbd1);
            }
            x = half_width - (func_0027F128(text_id, -1, glyphs) >> 1);
            if (menu->flags & 0x40) {
                x = 4;
            } else if (menu->flags & 0x4000) {
                x = half_width - (maximum_text_width >> 1);
            }
            func_0027F120();
            func_0027F2A8(x + D_001AA444, y + D_001AA448, 0x80000000L, text_id, -1,
                       func_0027C878(font_texture_index), glyphs);
            func_0027F110();
            if (menu->flags & 0x80) {
                func_0027F120();
            }
            func_0027F2A8(x, y, color, text_id, -1, func_0027C878(font_texture_index), glyphs);
            y += row_height;
            if (menu->items[selection_index].secondary_text_id != 0) {
                func_0027F120();
                shadow_x = x + D_001AA444;
                shadow_y = y + D_001AA448;
                secondary_text = func_00288FB8(menu->items[selection_index].secondary_text_id);
                func_0027F2A8(shadow_x, shadow_y, 0x80000000L, secondary_text, -1,
                           func_0027C878(font_texture_index), glyphs);
                if (!(menu->flags & 0x80)) {
                    func_0027F110();
                }
                func_0027F2A8(x, y, color,
                           func_00288FB8(menu->items[selection_index].secondary_text_id), -1,
                           func_0027C878(font_texture_index), glyphs);
                y += row_height;
            }
            if (menu->flags & 0x80) {
                func_0027F110();
            }
            selection_index++;
        } while (menu->items[selection_index].text_id != 0);
    }
    func_0027C660();
    return 2;
}
