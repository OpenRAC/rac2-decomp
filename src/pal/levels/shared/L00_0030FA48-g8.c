#include "include_asm.h"
#include "names.h"
extern int g_bolt_counter_base;
extern void UpdateBoltCounter(int);
extern int g_bolt_counter_base;

void hud_update_bolt_counter_if_enabled_pal(int argument)
{
    if (g_bolt_counter_base != 0) {
        UpdateBoltCounter(argument);
    }
}

extern void DrawBoltCounterDeltas(int);

void hud_draw_bolt_counter_deltas_if_enabled_pal(int argument)
{
    if (g_bolt_counter_base != 0) {
        DrawBoltCounterDeltas(argument);
    }
}
