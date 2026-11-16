#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int list_menu_update(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int resident_list_menu_update(int value) {
    if (g_resident_data_base != 0)
        return list_menu_update(g_resident_data_base + 0x3E810, value);
    return 0;
}

extern void menu_draw_if_active(void *);

/* Draws a menu panel, if the menu system exists. */
void resident_menu_draw_if_active(void) {
    if (g_resident_data_base != 0)
        menu_draw_if_active(g_resident_data_base + 0x3E810);
}

extern int list_menu_set_selection(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int resident_list_menu_set_selection(int value) {
    if (g_resident_data_base != 0)
        return list_menu_set_selection(g_resident_data_base + 0x3EA78, value);
    return 0;
}

extern void small_list_menu_draw_rows(void *);

/* Draws a menu panel, if the menu system exists. */
void resident_small_list_menu_draw_rows(void) {
    if (g_resident_data_base != 0)
        small_list_menu_draw_rows(g_resident_data_base + 0x3EA78);
}

extern void UpdateBoltCounter(void);

/* Updates the bolt counter, if the menu system exists. */
void resident_bolt_counter_update(void) {
    if (g_resident_data_base != 0)
        UpdateBoltCounter();
}

extern void DrawBoltCounterDeltas(void);

/* Draws the bolt gain and loss numbers, if the menu system exists. */
void resident_bolt_counter_deltas_draw(void) {
    if (g_resident_data_base != 0)
        DrawBoltCounterDeltas();
}
