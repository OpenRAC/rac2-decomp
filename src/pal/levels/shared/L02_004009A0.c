#include "include_asm.h"

#include "common.h"
extern void SetDeathBits(void *, int, int);

/* Forwards the first argument with a null second and a third of three. */
void moby_set_anim_type_three_pal(void *moby) {
    SetDeathBits(moby, 0, 3);
}

