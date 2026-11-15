#include "common.h"
#include "structs.h"

   /* current buffer */
extern short r1_D_0015EDC4;
extern void hud_request_letterbox_bars(void);
extern int g_letterbox_grow_flag __attribute__((sda));

/* Asks for the screen bars at the top to grow. */
void hud_request_letterbox_bars(void) {
    g_letterbox_grow_flag = 1;
}


extern int g_letterbox_level __attribute__((sda));
extern int g_letterbox_grow_flag __attribute__((sda));
extern void gfx_set_clear_color_packet(int, int, int, int);

/* Moves the screen bar level up or down by one step and draws the bar at its current height. */
void hud_update_letterbox_bars(void)
{
    int level;
    int bar_height;

    if (g_letterbox_grow_flag != 0) {
        g_letterbox_grow_flag = 0;
        level = g_letterbox_level + 1;
        g_letterbox_level = level;
        if (level >= 11)
            g_letterbox_level = 10;
    } else {
        level = g_letterbox_level - 1;
        g_letterbox_level = level;
        if (level < 0)
            g_letterbox_level = 0;
    }
    bar_height = (int)((float)g_letterbox_level * 0.1f * 48.0f);
    if (bar_height != 0)
        gfx_set_clear_color_packet(0, 0, 0, bar_height);
}

extern int D_001A901C __attribute__((sda));

/* Clears a HUD flag. */
void hud_clear_flag_a(void) {
    D_001A901C = 0;
}

extern int D_001A9020 __attribute__((sda));

/* Clears a second HUD flag. */
void hud_clear_flag_b(void) {
    D_001A9020 = 0;
}
