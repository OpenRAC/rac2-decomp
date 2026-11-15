#include "names.h"
/* func_L00_003CA650 in its own unit (flags in config/cflags.txt: -O2 -G0 -ffunction-sections). */
#include "include_asm.h"
#include "names.h"

extern void part_spawn_glow_in_front(char *);

/* Runs the effect update when the object is in state 1. */
void effect_update_in_state_one(char *object)
{
    if (*(unsigned char *)(object + 0x20) == 1)
        part_spawn_glow_in_front(object);
}
