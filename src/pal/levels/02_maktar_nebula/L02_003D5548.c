#include "include_asm.h"

#include "common.h"
extern void moby_set_state(void *, int, int);
extern void anim_start_blended(void *, int, int, int);

/* Sends the enemy back to its idle pose, with or without its held object. */
void armed_enemy_return_to_idle_pal(char *self) {
    char *state = *(char **)(self + 0x68);
    if (*(int *)(state + 0x2E4) != 0) {
        moby_set_state(self, 4, 2);
        if (*(unsigned char *)(self + 0x43) != 0)
            anim_start_blended(self, 0, 0, 0x8);
    } else {
        moby_set_state(self, 5, 2);
        if (*(unsigned char *)(self + 0x43) != 1)
            anim_start_blended(self, 1, 0, 0x8);
    }
}

