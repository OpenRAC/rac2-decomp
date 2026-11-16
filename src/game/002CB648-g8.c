#include "names.h"
typedef struct { int count, selection; int *strings; int enabled[25]; } MenuList_2CB648;
extern MenuList_2CB648 g_pause_cinema_controller;
extern char g_str_level_select_row_fmt[];
extern int g_level_select_row_height __attribute__((sda));
extern int g_level_select_list_top __attribute__((sda));
extern void gfx_set_clear_color_packet(int, int, int, int);
extern char *GetLocalizedString(int);
extern int sprintf(char *, char *, ...);
extern void gfx_draw_rounded_box(int, int, int, int, int, int);
extern int text_draw_centered_small(int, int, unsigned long, char *, int);

/* Draws the level select list, one text row per planet, and highlights the chosen one. */
void menu_draw_level_select_list(void)
{
    char text[256];
    int entry = 0;
    int i = 0;
    int row;
    char *first;
    unsigned int colour;
    MenuList_2CB648 *list;
    int *item;
    text[255] = 0;
    gfx_set_clear_color_packet(0, 0, 0, 0x60);
    for (; i <= g_pause_cinema_controller.count * 2; i += 2, entry++) {
        list = &g_pause_cinema_controller;
        item = list->enabled + entry;
        if (*item) {
            row = entry == 24 ? 36 : i;
            first = GetLocalizedString(list->strings[i + 1]);
            sprintf(text, g_str_level_select_row_fmt, first, GetLocalizedString(list->strings[i]));
            gfx_draw_rounded_box(g_level_select_list_top + row * g_level_select_row_height,
                         g_level_select_list_top + row * g_level_select_row_height + 15,
                         64, 448, 96, 0x442D00);
            colour = list->selection == entry ? 0x80FFDE8D : 0x80808080;
            if (*item == 0) colour = 0x80000000;
            text_draw_centered_small(256, g_level_select_list_top + row * g_level_select_row_height, (unsigned long)colour, text, -1);
        }
    }
}
