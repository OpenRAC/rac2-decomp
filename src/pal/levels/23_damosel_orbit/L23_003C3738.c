#include "include_asm.h"
#include "names.h"


extern void func_323FF0(char *, int, int, int);

/* Plays an animation on the moby, on its linked part, or both (bits 1 and 2 of the mask). (PAL) */
void moby_play_anim_and_link_pal(char *moby, int anim, int unused_2, int unused_3, int mask, float blend) {
    char *vars = *(char **)(moby + 0x68);

    if (mask & 1)
        func_323FF0(moby, anim, 0, 3);
    if (mask & 2)
        func_323FF0(*(char **)(vars + 0x2A0), anim, 0, 3);
}

