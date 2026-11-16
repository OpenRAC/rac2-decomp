#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int UpdateFourOptionMenuInput(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int four_option_panel_update_us2(int value) {
    if (g_resident_data_base != 0)
        return UpdateFourOptionMenuInput(g_resident_data_base + 0x3D4B8, value);
    return 0;
}

extern void four_option_menu_draw(void *);

/* Draws a menu panel, if the menu system exists. */
void four_option_panel_draw_us2(void) {
    if (g_resident_data_base != 0)
        four_option_menu_draw(g_resident_data_base + 0x3D4B8);
}

extern int two_toggle_a_update(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int two_toggle_a_panel_update_us2(int value) {
    if (g_resident_data_base != 0)
        return two_toggle_a_update(g_resident_data_base + 0x3D798, value);
    return 0;
}

extern void two_toggle_a_draw(void *);

/* Draws a menu panel, if the menu system exists. */
void two_toggle_a_panel_draw_us2(void) {
    if (g_resident_data_base != 0)
        two_toggle_a_draw(g_resident_data_base + 0x3D798);
}

extern int single_toggle_a_update(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int single_toggle_a_panel_update_us2(int value) {
    if (g_resident_data_base != 0)
        return single_toggle_a_update(g_resident_data_base + 0x3DDE8, value);
    return 0;
}

extern void single_toggle_a_draw(void *);

/* Draws a menu panel, if the menu system exists. */
void single_toggle_a_panel_draw_us2(void) {
    if (g_resident_data_base != 0)
        single_toggle_a_draw(g_resident_data_base + 0x3DDE8);
}

extern int screen_adjust_menu_update(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int screen_adjust_panel_update_us2(int value) {
    if (g_resident_data_base != 0)
        return screen_adjust_menu_update(g_resident_data_base + 0x3E0C8, value);
    return 0;
}

extern void onoff_menu_draw_with_help(void *);

/* Draws a menu panel, if the menu system exists. */
void onoff_help_panel_draw_us2(void) {
    if (g_resident_data_base != 0)
        onoff_menu_draw_with_help(g_resident_data_base + 0x3E0C8);
}

extern int onoff_menu_update(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int onoff_panel_update_us2(int value) {
    if (g_resident_data_base != 0)
        return onoff_menu_update(g_resident_data_base + 0x3E3A8, value);
    return 0;
}

extern void onoff_menu_draw(void *);

/* Draws a menu panel, if the menu system exists. */
void onoff_panel_draw_us2(void) {
    if (g_resident_data_base != 0)
        onoff_menu_draw(g_resident_data_base + 0x3E3A8);
}
