#include "names.h"
typedef struct { int count, selection; int *strings; int enabled[25]; } MenuList_2CB648;
extern MenuList_2CB648 D_00210A40;
extern char D_001AB900[];
extern int D_001AB8F4 __attribute__((sda));
extern int D_001AB8F8 __attribute__((sda));
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
    for (; i <= D_00210A40.count * 2; i += 2, entry++) {
        list = &D_00210A40;
        item = list->enabled + entry;
        if (*item) {
            row = entry == 24 ? 36 : i;
            first = GetLocalizedString(list->strings[i + 1]);
            sprintf(text, D_001AB900, first, GetLocalizedString(list->strings[i]));
            gfx_draw_rounded_box(D_001AB8F8 + row * D_001AB8F4,
                         D_001AB8F8 + row * D_001AB8F4 + 15,
                         64, 448, 96, 0x442D00);
            colour = list->selection == entry ? 0x80FFDE8D : 0x80808080;
            if (*item == 0) colour = 0x80000000;
            text_draw_centered_small(256, D_001AB8F8 + row * D_001AB8F4, (unsigned long)colour, text, -1);
        }
    }
}
