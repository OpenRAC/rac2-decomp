#include "include_asm.h"

#include "common.h"
extern int math_random_int_range(int, int);
extern int math_random_int_below(int);
extern float FastAddRotations(float, float);

/* The record's state byte is a small switch, not an if/else chain: the retail
   compares it against 0 and 1 in turn and falls straight out for anything else.
   State 0 draws a random duration in 150..200 and marks the record active;
   state 1 converts the drawn duration to a signed angle and folds it into the
   record's angle through the resident step body. */
void random_turn_update_pal(unsigned char *moby) {
    switch (moby[0x20]) {
    case 0:
        moby[0xBC] = math_random_int_range(0x96, 0xC8);
        if (math_random_int_below(2) != 0) {
            moby[0x95] = 1;
        }
        moby[0x20] = 1;
        break;
    case 1:
        if (moby[0x95] != 0) {
            *(float *)(moby + 0xF4) = FastAddRotations(
                *(float *)(moby + 0xF4), -((float)moby[0xBC] * 0.0003490659f));
        } else {
            *(float *)(moby + 0xF4) = FastAddRotations(
                *(float *)(moby + 0xF4), (float)moby[0xBC] * 0.0003490659f);
        }
        break;
    }
}
