#include "include_asm.h"

#include "common.h"

/* Switches a moby on the first time it runs. */
void moby_activate_once_2_pal(char *moby)
{
    if (*(unsigned char *)(moby + 0x20) == 0) {
        *(unsigned short *)(moby + 0x34) |= 0x800;
        *(unsigned char *)(moby + 0x20) = 1;
    }
}


/* Switches a moby on the first time it runs. */
void moby_activate_once_3_pal(char *moby)
{
    if (*(unsigned char *)(moby + 0x20) == 0) {
        *(unsigned short *)(moby + 0x34) |= 0x800;
        *(unsigned char *)(moby + 0x20) = 1;
    }
}


/* Switches a moby on the first time it runs. */
void moby_activate_once_4_pal(char *moby)
{
    if (*(unsigned char *)(moby + 0x20) == 0) {
        *(unsigned short *)(moby + 0x34) |= 0x800;
        *(unsigned char *)(moby + 0x20) = 1;
    }
}


/* Switches a moby on the first time it runs. */
void moby_activate_once_5_pal(char *moby)
{
    if (*(unsigned char *)(moby + 0x20) == 0) {
        *(unsigned short *)(moby + 0x34) |= 0x800;
        *(unsigned char *)(moby + 0x20) = 1;
    }
}


/* Switches a moby on the first time it runs. */
void moby_activate_once_6_pal(char *moby)
{
    if (*(unsigned char *)(moby + 0x20) == 0) {
        *(unsigned short *)(moby + 0x34) |= 0x800;
        *(unsigned char *)(moby + 0x20) = 1;
    }
}


/* Switches a moby on the first time it runs. */
void moby_activate_once_7_pal(char *moby)
{
    if (*(unsigned char *)(moby + 0x20) == 0) {
        *(unsigned short *)(moby + 0x34) |= 0x800;
        *(unsigned char *)(moby + 0x20) = 1;
    }
}

