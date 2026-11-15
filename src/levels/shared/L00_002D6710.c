#include "names.h"


extern unsigned int D_001A79F0_1[] __attribute__((sda));

typedef int s32;

extern s32 D_001A79F0_2;

extern s32 func_L00_002D67A8(s32);

/* A13-eq-getter-20 freshly exact-verified under family reservation */
/* Returns 1 when the level mode is 25, otherwise 0. */
unsigned int func_L00_002D6710(void) { return D_001A79F0_1[0] == 0x19u; }

/* Return one when the resident mode word is25,5,10 or15, otherwise zero */
s32 func_L00_002D6728(void) {
    s32 matches = 0;
    if (D_001A79F0_2 == 25 || D_001A79F0_2 == 5 ||
        D_001A79F0_2 == 10 || D_001A79F0_2 == 15) {
        matches = 1;
    }
    return matches;
}

/* calls the measured integer callee with zero */
/* Runs the mode update with 0. */
void func_L00_002D6768(void) {
 IsTrackedObjectOfSelectedClass(0);
}

/* calls the measured integer callee with three */
/* Runs the mode update with 3. */
void func_L00_002D6788(void) {
 IsTrackedObjectOfSelectedClass(3);
}
