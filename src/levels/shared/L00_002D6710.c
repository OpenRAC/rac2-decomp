#include "names.h"


extern unsigned int D_001A79F0_1[] __attribute__((sda));

typedef int s32;

extern s32 D_001A79F0_2;

extern s32 level_is_tracked_object_of_selected_class(s32);

/* A13-eq-getter-20 freshly exact-verified under family reservation */
/* Returns 1 when the level mode is 25, otherwise 0. */
unsigned int level_is_mode_twenty_five(void) { return D_001A79F0_1[0] == 0x19u; }

/* Return one when the resident mode word is25,5,10 or15, otherwise zero */
s32 level_is_mode_in_set(void) {
    s32 matches = 0;
    if (D_001A79F0_2 == 25 || D_001A79F0_2 == 5 ||
        D_001A79F0_2 == 10 || D_001A79F0_2 == 15) {
        matches = 1;
    }
    return matches;
}

/* calls the measured integer callee with zero */
/* Runs the mode update with 0. */
void level_run_mode_update_zero(void) {
 level_is_tracked_object_of_selected_class(0);
}

/* calls the measured integer callee with three */
/* Runs the mode update with 3. */
void level_run_mode_update_three(void) {
 level_is_tracked_object_of_selected_class(3);
}
