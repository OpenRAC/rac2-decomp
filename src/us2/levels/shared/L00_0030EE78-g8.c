#include "include_asm.h"
#include "names.h"
extern int g_bolt_counter_base;
extern void UpdateBoltCounter(int);
extern int g_bolt_counter_base;

void hud_update_bolt_counter_if_enabled_us2(int argument)
{
    if (g_bolt_counter_base != 0) {
        UpdateBoltCounter(argument);
    }
}
