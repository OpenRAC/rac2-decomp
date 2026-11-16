#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int audio_menu_update(void *, int);

/* Passes a value to a menu panel and returns its answer; returns 0 if the menu system does not exist. */
int audio_panel_update_us2(int value) {
    if (g_resident_data_base != 0)
        return audio_menu_update(g_resident_data_base + 0x3DA78, value);
    return 0;
}

extern void audio_menu_draw(void *);

/* Draws a menu panel, if the menu system exists. */
void audio_panel_draw_us2(void) {
    if (g_resident_data_base != 0)
        audio_menu_draw(g_resident_data_base + 0x3DA78);
}
