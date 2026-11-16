#include "include_asm.h"
#include "names.h"


typedef unsigned char u8;
extern u8 D_001A63A8_4[];
extern u8 g_hero_state[];
extern void moby_explode(u8 *a0, int a1, int a2);

/* Runs the explosion routine for the object and makes it fully visible. */
void moby_trigger_explosion_pal(u8 *moby) {
    int explode_arg = *(int *)(moby + 0x68);
    moby_explode(moby, explode_arg, explode_arg);
    *(u8 *)(moby + 0x30) = 0xFF;
}

