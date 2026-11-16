#include "include_asm.h"
#include "names.h"

extern void anim_start_blended(void *, int, int, int);

/* Releases the object linked to this one: plays its release animation and clears the link (PAL). */
void object_release_linked_pal(char *moby)
{
    char *state = *(char **)(moby + 0x68);

    if (*(char **)(state + 0x2AC) != 0) {
        anim_start_blended(*(char **)(state + 0x2AC), 9, 0, 2);
        *(int *)(*(char **)(*(char **)(state + 0x2AC) + 0x68) + 0x27C) = 0;
        *(char **)(state + 0x2AC) = 0;
    }
}

