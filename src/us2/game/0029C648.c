#include "include_asm.h"
#include "names.h"

extern char *g_resident_data_base[] __attribute__((sda));
extern void hud_update_subobject_primary(void *);

void level_run_update_us2(void) {
    if (g_resident_data_base[0] != 0)
        hud_update_subobject_primary(g_resident_data_base[0] + 0x36F28);
}

extern int D_L00_001A904C_6 __attribute__((sda));
extern void text_draw_framed_box(int *p, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10);

/* Loads a 32-bit global pointer from a fixed data address; if non-null, tail-forwards it (offset by 0x36F28) plus ten incoming arguments to an overlay-local callee. */
void level_forward_draw_args_us2(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
{
    int value = D_L00_001A904C_6;

    if (value != 0)
        text_draw_framed_box((int *)(value + 0x36F28), a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
}








extern void hud_update_subsystems_us2(void *);

/* Updates the HUD subsystems, if the resident data exists. */
void hud_update_subsystems_call_us2(void) {
    if (g_resident_data_base[0] != 0)
        hud_update_subsystems_us2(g_resident_data_base[0] + 0x36F28);
}


extern void hud_item_bolt_draw_us2(void *);

/* Draws the HUD bolt counter, if the resident data exists. */
void hud_item_bolt_draw_call_us2(void) {
    if (g_resident_data_base[0] != 0)
        hud_item_bolt_draw_us2(g_resident_data_base[0] + 0x36F28);
}


extern void list_menu_draw_centered_rows_us2(void *);

/* Calls a resident menu panel function, if the resident data exists. */
void resident_panel_call_a_us2(void) {
    if (g_resident_data_base[0] != 0)
        list_menu_draw_centered_rows_us2(g_resident_data_base[0] + 0x39160);
}



extern void item_grid_menu_draw_us2(void *);

/* Calls a resident menu panel function, if the resident data exists. */
void resident_panel_call_b_us2(void) {
    if (g_resident_data_base[0] != 0)
        item_grid_menu_draw_us2(g_resident_data_base[0] + 0x39620);
}


extern void menu_screen_large_draw_parts_us2(void *);

/* Calls a resident menu panel function, if the resident data exists. */
void resident_panel_call_c_us2(void) {
    if (g_resident_data_base[0] != 0)
        menu_screen_large_draw_parts_us2(g_resident_data_base[0] + 0x39AF0);
}



