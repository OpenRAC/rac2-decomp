#include "common.h"
extern void func_37BB30(int, unsigned long long);
extern void func_302298(int, int, int, int, int, int);
extern void func_2F0670(int, int, unsigned long long, char *, int);
extern int sprintf(char *, char *, ...);
extern int g_museum_menu_box_left __attribute__((sda));
extern int g_museum_menu_line_height __attribute__((sda));
extern int g_museum_menu_label_x __attribute__((sda));
extern int g_museum_menu_text_y __attribute__((sda));
extern int g_museum_menu_value_x __attribute__((sda));
extern int g_museum_menu_box_color __attribute__((sda));
extern int g_museum_menu_box_top, g_museum_menu_box_right;
extern int g_museum_menu_title_color;
extern char g_str_museum_menu_title[];
extern char g_str_museum_menu_label_format[];
extern char g_str_museum_menu_blank[];
extern char g_str_museum_menu_int_format[];
extern char g_str_museum_menu_float_format[];
extern void *g_tweak_item_ptrs[];
extern char *g_tweak_item_labels[];
extern unsigned char g_tweak_item_types[] __attribute__((sda)) NOT_SDA;
/* Draws the tuning menu: a box, the visible rows with their labels, the cursor, and each value as a number. */
void museum_tweak_menu_draw(char *moby) {
    char text[256];
    int i = 0, count = 0;
    int *vars = *(int **)(moby + 0x68);
    func_37BB30(0x42, 0x8000000044ULL);
    func_302298(g_museum_menu_box_left, g_museum_menu_box_top, g_museum_menu_box_right, g_museum_menu_box_top + g_museum_menu_line_height * (vars[1] < 17 ? vars[1] : 16), g_museum_menu_box_color, 0);
    func_2F0670(2, 8, g_museum_menu_title_color, g_str_museum_menu_title, -1);
    for (; i < 32 - vars[2] && count < vars[1] && count < 16; i++) {
        if (!g_tweak_item_ptrs[i + vars[2]]) continue;
        count++;
        if (g_tweak_item_labels[i]) {
            sprintf(text, g_str_museum_menu_label_format, g_tweak_item_labels[i + vars[2]]);
            func_2F0670(g_museum_menu_label_x, g_museum_menu_text_y + i * g_museum_menu_line_height, g_museum_menu_title_color, text, -1);
        }
        if (vars[0] == i + vars[2]) {
            sprintf(text, g_str_museum_menu_blank);
            func_2F0670(g_museum_menu_label_x - 16, g_museum_menu_text_y + i * g_museum_menu_line_height, 0x80008000ULL, text, -1);
        }
        switch (g_tweak_item_types[i + vars[2]]) {
        case 0:
            sprintf(text, g_str_museum_menu_int_format, *(int *)g_tweak_item_ptrs[i + vars[2]]);
            func_2F0670(g_museum_menu_value_x, g_museum_menu_text_y + i * g_museum_menu_line_height, 0x80008080ULL, text, -1);
            break;
        case 1:
            sprintf(text, g_str_museum_menu_float_format, (double)*(float *)g_tweak_item_ptrs[i + vars[2]]);
            func_2F0670(g_museum_menu_value_x, g_museum_menu_text_y + i * g_museum_menu_line_height, 0x80008080ULL, text, -1);
            break;
        case 2:
            sprintf(text, g_str_museum_menu_int_format, *(unsigned char *)g_tweak_item_ptrs[i + vars[2]]);
            func_2F0670(g_museum_menu_value_x, g_museum_menu_text_y + i * g_museum_menu_line_height, 0x80008080ULL, text, -1);
            break;
        case 3:
            sprintf(text, g_str_museum_menu_int_format, *(short *)g_tweak_item_ptrs[i + vars[2]]);
            func_2F0670(g_museum_menu_value_x, g_museum_menu_text_y + i * g_museum_menu_line_height, 0x80008080ULL, text, -1);
            break;
        }
    }
}
