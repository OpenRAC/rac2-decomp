#include "include_asm.h"

#include "common.h"

/* Switches a moby on the first time it runs. */
void moby_activate_once_pal(char *moby)
{
    if (*(unsigned char *)(moby + 0x20) == 0) {
        *(unsigned short *)(moby + 0x34) |= 0x800;
        *(unsigned char *)(moby + 0x20) = 1;
    }
}

