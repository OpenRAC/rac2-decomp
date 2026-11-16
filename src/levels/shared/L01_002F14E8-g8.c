#include "include_asm.h"
#include "names.h"


extern int g_hud_overlay_timer __attribute__((sda));
extern float g_hud_overlay_fade __attribute__((sda));
extern int g_hud_overlay_icon_id __attribute__((sda));
extern int g_hud_overlay_result_code __attribute__((sda));
extern int level_tick_timer_get_value(void);
extern int hud_draw_overlay(void);
extern int level_set_table_entry(int (*)(void),int (*)(void),int);

/* Starts the HUD overlay: stores the icon and a fade amount limited to 0 to 1, and registers the overlay update if it is not running. */
void hud_start_overlay(int iconId, int resultCode, float fade)
{
    if (g_hud_overlay_timer == 0)
        level_set_table_entry(level_tick_timer_get_value, hud_draw_overlay, 0);
    g_hud_overlay_timer = 5;
    g_hud_overlay_fade = fade;
    if (fade > 1.0f)
        g_hud_overlay_fade = 1.0f;
    else if (fade < 0.0f)
        g_hud_overlay_fade = 0.0f;
    g_hud_overlay_result_code = resultCode;
    g_hud_overlay_icon_id = iconId;
}
