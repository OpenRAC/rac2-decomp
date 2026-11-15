#include "include_asm.h"
#include "names.h"

/* func_L02_003D01F0 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern void func_002A7750(char *, int, int);

/* Sets the object's state to 4, then copies the 16-byte vector at A1 into its state at +0xB0. */
/* Makes the platform piece start falling, pushed with the given speed. */
void func_L02_003D01F0(char *self, char *velocity) {
    char *state = *(char **)(self + 0x68);

    SetMobyState(self, 4, -1);
    *(TI128 *)(state + 0xB0) = *(TI128 *)velocity;
}
