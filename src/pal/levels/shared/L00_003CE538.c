#include "include_asm.h"
#include "names.h"

extern void part_spawn_glow_in_front(char *);

void func_PAL_L00_003CE538(char *object)
{
    if (*(unsigned char *)(object + 0x20) == 1)
        part_spawn_glow_in_front(object);
}

