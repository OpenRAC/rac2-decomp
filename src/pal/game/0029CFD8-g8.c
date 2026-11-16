#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int simple_page_update(void *, int);

/* Updates the frame page menu panel and returns its answer; returns 0 if the menu system does not exist. (PAL address) */
int menu_update_frame_page_pal(int value) {
    if (g_resident_data_base != 0)
        return simple_page_update(g_resident_data_base + 0x3C898, value);
    return 0;
}

extern void two_toggle_b_draw(void *);

/* Draws the two toggle b menu panel, if the menu system exists. (PAL address) */
void menu_draw_two_toggle_b_pal(void) {
    if (g_resident_data_base != 0)
        two_toggle_b_draw(g_resident_data_base + 0x3D288);
}

extern int two_toggle_b_update(void *, int);

/* Updates the two toggle b menu panel and returns its answer; returns 0 if the menu system does not exist. (PAL address) */
int menu_update_two_toggle_b_pal(int value) {
    if (g_resident_data_base != 0)
        return two_toggle_b_update(g_resident_data_base + 0x3D288, value);
    return 0;
}

extern int UpdateFourOptionMenuInput(void *, int);

/* Updates the four option menu panel and returns its answer; returns 0 if the menu system does not exist. (PAL address) */
int menu_update_four_option_pal(int value) {
    if (g_resident_data_base != 0)
        return UpdateFourOptionMenuInput(g_resident_data_base + 0x3D568, value);
    return 0;
}

extern void four_option_menu_draw(void *);

/* Draws the four option menu panel, if the menu system exists. (PAL address) */
void menu_draw_four_option_pal(void) {
    if (g_resident_data_base != 0)
        four_option_menu_draw(g_resident_data_base + 0x3D568);
}

extern int two_toggle_a_update(void *, int);

/* Updates the two toggle a menu panel and returns its answer; returns 0 if the menu system does not exist. (PAL address) */
int menu_update_two_toggle_a_pal(int value) {
    if (g_resident_data_base != 0)
        return two_toggle_a_update(g_resident_data_base + 0x3D848, value);
    return 0;
}

extern void two_toggle_a_draw(void *);

/* Draws the two toggle a menu panel, if the menu system exists. (PAL address) */
void menu_draw_two_toggle_a_pal(void) {
    if (g_resident_data_base != 0)
        two_toggle_a_draw(g_resident_data_base + 0x3D848);
}

extern int single_toggle_a_update(void *, int);

/* Updates the single toggle a menu panel and returns its answer; returns 0 if the menu system does not exist. (PAL address) */
int menu_update_single_toggle_a_pal(int value) {
    if (g_resident_data_base != 0)
        return single_toggle_a_update(g_resident_data_base + 0x3DE98, value);
    return 0;
}

extern void single_toggle_a_draw(void *);

/* Draws the single toggle a menu panel, if the menu system exists. (PAL address) */
void menu_draw_single_toggle_a_pal(void) {
    if (g_resident_data_base != 0)
        single_toggle_a_draw(g_resident_data_base + 0x3DE98);
}

extern int screen_adjust_menu_update(void *, int);

/* Updates the screen adjust menu panel and returns its answer; returns 0 if the menu system does not exist. (PAL address) */
int menu_update_screen_adjust_pal(int value) {
    if (g_resident_data_base != 0)
        return screen_adjust_menu_update(g_resident_data_base + 0x3E178, value);
    return 0;
}

extern void onoff_menu_draw_with_help(void *);

/* Draws the screen adjust menu panel, if the menu system exists. (PAL address) */
void menu_draw_screen_adjust_pal(void) {
    if (g_resident_data_base != 0)
        onoff_menu_draw_with_help(g_resident_data_base + 0x3E178);
}

extern int onoff_menu_update(void *, int);

/* Updates the onoff menu panel and returns its answer; returns 0 if the menu system does not exist. (PAL address) */
int menu_update_onoff_pal(int value) {
    if (g_resident_data_base != 0)
        return onoff_menu_update(g_resident_data_base + 0x3E458, value);
    return 0;
}

extern void onoff_menu_draw(void *);

/* Draws the onoff menu panel, if the menu system exists. (PAL address) */
void menu_draw_onoff_pal(void) {
    if (g_resident_data_base != 0)
        onoff_menu_draw(g_resident_data_base + 0x3E458);
}

extern int list_page_update(void *, int);

/* Updates the list page menu panel and returns its answer; returns 0 if the menu system does not exist. (PAL address) */
int menu_update_list_page_pal(int value) {
    if (g_resident_data_base != 0)
        return list_page_update(g_resident_data_base + 0x3F4A0, value);
    return 0;
}

extern void list_page_draw(void *);

/* Draws the list page menu panel, if the menu system exists. (PAL address) */
void menu_draw_list_page_pal(void) {
    if (g_resident_data_base != 0)
        list_page_draw(g_resident_data_base + 0x3F4A0);
}

extern int audio_menu_update(void *, int);

/* Updates the audio menu panel and returns its answer; returns 0 if the menu system does not exist. (PAL address) */
int menu_update_audio_pal(int value) {
    if (g_resident_data_base != 0)
        return audio_menu_update(g_resident_data_base + 0x3DB28, value);
    return 0;
}

extern void audio_menu_draw(void *);

/* Draws the audio menu panel, if the menu system exists. (PAL address) */
void menu_draw_audio_pal(void) {
    if (g_resident_data_base != 0)
        audio_menu_draw(g_resident_data_base + 0x3DB28);
}

extern int single_toggle_c_update(void *, int);

/* Updates the single toggle c menu panel and returns its answer; returns 0 if the menu system does not exist. (PAL address) */
int menu_update_single_toggle_c_pal(int value) {
    if (g_resident_data_base != 0)
        return single_toggle_c_update(g_resident_data_base + 0x3EC00, value);
    return 0;
}

extern void single_toggle_c_draw(void *);

/* Draws the single toggle c menu panel, if the menu system exists. (PAL address) */
void menu_draw_single_toggle_c_pal(void) {
    if (g_resident_data_base != 0)
        single_toggle_c_draw(g_resident_data_base + 0x3EC00);
}
