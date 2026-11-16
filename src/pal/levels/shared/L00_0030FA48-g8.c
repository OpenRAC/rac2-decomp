#include "include_asm.h"
#include "names.h"
extern int g_bolt_counter_base;
extern void UpdateBoltCounter(int);
extern int g_bolt_counter_base;

/* Updates the bolt counter when it is enabled (PAL). */
void hud_update_bolt_counter_if_enabled_pal(int amount)
{
    if (g_bolt_counter_base != 0) {
        UpdateBoltCounter(amount);
    }
}

extern void DrawBoltCounterDeltas(int);

/* Draws the bolt counter deltas when it is enabled (PAL). */
void hud_draw_bolt_counter_deltas_if_enabled_pal(int amount)
{
    if (g_bolt_counter_base != 0) {
        DrawBoltCounterDeltas(amount);
    }
}
