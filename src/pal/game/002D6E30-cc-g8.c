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

extern MenuSystem g_pause_menu_state;
extern MenuPage g_menu_page_main, g_menu_page_pause;
extern MenuDescriptor g_menu_widget_a, g_menu_widget_b, g_menu_widget_c, g_menu_widget_d, g_menu_widget_e, g_menu_widget_f;
extern unsigned char g_font_glyphs_small[], g_font_glyphs_medium[], g_font_glyphs_large[];
/* Pairs of text ids: the id to look for, then the id of the text it is formatted with. */
extern int g_menu_text_id_table[];
extern char g_menu_text_buffer[], g_str_render_text_fmt[];
extern int g_text_shadow_offset_x __attribute__((sda)), g_text_shadow_offset_y __attribute__((sda));
extern void VU1_addGSregister(unsigned int, unsigned long);
extern void SetupGifPaging(int);
extern void gfx_disable_screen_flag(void);
extern void gfx_enable_screen_flag(void);
extern void DoGifPaging(void);
extern void mem_clear(void *, int, int);
extern unsigned long GetEffectTextureDescriptor(int);
extern int measure_text_width(char *, int, unsigned char *);
extern int menu_blend_highlight_color_pal(int, int, int);
extern int sprintf(char *, char *, ...);
extern char *GetLocalizedString(int);
extern void text_draw_line(int, int, unsigned long, char *, int, unsigned long, unsigned char *);

/* RAC1 pause.c render_localized_ui_entry_list, with RaC2's formatted-text rows. */
int RenderLocalizedUiEntryList_pal(MenuDescriptor *menu) {
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
    char *text;
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
    glyphs = g_font_glyphs_small;
    focused = g_pause_menu_state.current->focus == menu;
    if (menu->flags & 4) {
        font_height = 14;
        font_texture_index = 3;
        glyphs = g_font_glyphs_large;
    }
    if (menu->flags & 8) {
        font_height = 10;
        font_texture_index = 2;
        glyphs = g_font_glyphs_medium;
    }
    VU1_addGSregister(0x42, 0x44);
    VU1_addGSregister(0x47, 0x2004B);
    SetupGifPaging(0);
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
                text_width = measure_text_width(
                    GetLocalizedString(scan_entry[entry_index].text_id), -1, glyphs);
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
                color = menu_blend_highlight_color_pal(selected_item->fade_timer, -1, -1);

            } else {
                color = 0x80303030;
            }
            text = GetLocalizedString(menu->items[selection_index].text_id);
            if ((g_pause_menu_state.current == &g_menu_page_main || g_pause_menu_state.current == &g_menu_page_pause) &&
                (menu == &g_menu_widget_a || menu == &g_menu_widget_b || menu == &g_menu_widget_c ||
                 menu == &g_menu_widget_d || menu == &g_menu_widget_e || menu == &g_menu_widget_f)) {
                int j, found = -1;
                j = 0;
                while (j < 14) {
                    if (g_menu_text_id_table[j] == menu->items[selection_index].text_id) {
                        found = j + 1;
                        break;
                    }
                    j += 2;
                }
                if (found >= 0) {
                    mem_clear(g_menu_text_buffer, 0, 256);
                    text = GetLocalizedString(menu->items[selection_index].text_id);
                    sprintf(g_menu_text_buffer, g_str_render_text_fmt,
                                 GetLocalizedString(g_menu_text_id_table[found]), text);
                    text = g_menu_text_buffer;
                }
            }
            if (menu->items[selection_index].enabled == 2) {
                text = GetLocalizedString(0xbd1);
            }
            x = half_width - (measure_text_width(text, -1, glyphs) >> 1);
            if (menu->flags & 0x40) {
                x = 4;
            } else if (menu->flags & 0x4000) {
                x = half_width - (maximum_text_width >> 1);
            }
            gfx_disable_screen_flag();
            text_draw_line(x + g_text_shadow_offset_x, y + g_text_shadow_offset_y, 0x80000000L, text, -1,
                       GetEffectTextureDescriptor(font_texture_index), glyphs);
            gfx_enable_screen_flag();
            if (menu->flags & 0x80) {
                gfx_disable_screen_flag();
            }
            text_draw_line(x, y, color, text, -1, GetEffectTextureDescriptor(font_texture_index), glyphs);
            y += row_height;
            if (menu->items[selection_index].secondary_text_id != 0) {
                gfx_disable_screen_flag();
                shadow_x = x + g_text_shadow_offset_x;
                shadow_y = y + g_text_shadow_offset_y;
                secondary_text = GetLocalizedString(menu->items[selection_index].secondary_text_id);
                text_draw_line(shadow_x, shadow_y, 0x80000000L, secondary_text, -1,
                           GetEffectTextureDescriptor(font_texture_index), glyphs);
                if (!(menu->flags & 0x80)) {
                    gfx_enable_screen_flag();
                }
                text_draw_line(x, y, color,
                           GetLocalizedString(menu->items[selection_index].secondary_text_id), -1,
                           GetEffectTextureDescriptor(font_texture_index), glyphs);
                y += row_height;
            }
            if (menu->flags & 0x80) {
                gfx_enable_screen_flag();
            }
            selection_index++;
        } while (menu->items[selection_index].text_id != 0);
    }
    DoGifPaging();
    return 2;
}
