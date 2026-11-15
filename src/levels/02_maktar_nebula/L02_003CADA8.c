#include "include_asm.h"
#include "names.h"

/* func_L02_003CADA8 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern void moby_set_state(char *, int, int);

/* Sets the object's state to 7, then copies the 16-byte vector at A1 into its state at +0xF0. */
/* Makes the enemy start falling, pushed with the given speed. */
void path_enemy_start_fall(char *self, char *velocity) {
    char *state = *(char **)(self + 0x68);

    moby_set_state(self, 7, -1);
    *(TI128 *)(state + 0xF0) = *(TI128 *)velocity;
}
