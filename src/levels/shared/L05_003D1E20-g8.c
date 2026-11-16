#include "names.h"
/* func_L05_003D1E20 (60 bytes; levels 05, 10, 15, 25): clears a $gp flag and two five-word
   tables. Both tables are built with the absolute la macro (MACRO_ADDR), which keeps each
   lui/addiu pair together. */
#include "common.h"
extern int g_effect_slot_state __attribute__((sda));
extern int g_glow_effect_blends[] MACRO_ADDR;
extern int g_spawned_effect_mobys[] MACRO_ADDR;

/* Clears the explosion counter and both explosion slot tables. */
void func_L05_003D1E20(void)
{
    int i;

    g_effect_slot_state = 0;
    for (i = 0; i < 5; i++) {
        g_spawned_effect_mobys[i] = 0;
        g_glow_effect_blends[i] = 0;
    }
}
