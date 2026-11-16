#include "include_asm.h"

#include "common.h"
extern int hud_init_counter_values(void *);

/* Resets an object's counters and sets its size and limit values, then hands it to the shared setup call. */
void level_reset_and_init_object_pal(char *self) {
    *(short *)(self + 0x48) = 0;
    *(short *)(self + 0x4A) = 0;
    *(int *)(self + 0x58) = 0x20;
    *(int *)(self + 0x7C) = 0x26;
    *(int *)(self + 0x5C) = 0x20;
    hud_init_counter_values(self);
}


extern int r1_func_0011CC38();

/* rac1-decomp src/core/00119D88.c: func_0011CCB0 */
/* Returns its callee's value: retail keeps the frame and calls, and
   2.9-ee would tail-call it (a bare `j`) if it were void. */
int level_call_helper_a_pal(void) {
    return r1_func_0011CC38();
}

