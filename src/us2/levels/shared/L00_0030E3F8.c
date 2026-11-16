#include "include_asm.h"
#include "names.h"

extern char *g_resident_data_base[] __attribute__((sda));
extern void hud_update_subsystems_us2(void *);

/* Updates the HUD subsystems of the resident data, if loaded. */
void hud_update_subsystems_resident_us2(void) {
    if (g_resident_data_base[0] != 0)
        hud_update_subsystems_us2(g_resident_data_base[0] + 0x36F28);
}


extern void hud_item_bolt_draw_us2(void *);

/* Draws the bolt HUD item of the resident data, if loaded. */
void hud_item_bolt_draw_resident_us2(void) {
    if (g_resident_data_base[0] != 0)
        hud_item_bolt_draw_us2(g_resident_data_base[0] + 0x36F28);
}


extern void list_menu_draw_centered_rows_us2(void *);

/* Runs the per-frame routine of the resident-data sub-object at +0x39160, if loaded. */
void resident_sub_39160_update_us2(void) {
    if (g_resident_data_base[0] != 0)
        list_menu_draw_centered_rows_us2(g_resident_data_base[0] + 0x39160);
}



extern void item_grid_menu_draw_us2(void *);

/* Runs the per-frame routine of the resident-data sub-object at +0x39620, if loaded. */
void resident_sub_39620_update_us2(void) {
    if (g_resident_data_base[0] != 0)
        item_grid_menu_draw_us2(g_resident_data_base[0] + 0x39620);
}


extern void menu_screen_large_draw_parts_us2(void *);

/* Runs the per-frame routine of the resident-data sub-object at +0x39AF0, if loaded. */
void resident_sub_39af0_update_us2(void) {
    if (g_resident_data_base[0] != 0)
        menu_screen_large_draw_parts_us2(g_resident_data_base[0] + 0x39AF0);
}


