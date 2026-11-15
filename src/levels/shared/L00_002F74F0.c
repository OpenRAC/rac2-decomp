#include "common.h"

extern int hud_init_counter_values(void *);

/* Resets an object's counters and sets its size and limit values, then hands it to the shared setup call. */
void level_reset_and_init_object(char *self) {
    *(short *)(self + 0x48) = 0;
    *(short *)(self + 0x4A) = 0;
    *(int *)(self + 0x58) = 0x20;
    *(int *)(self + 0x7C) = 0x28;
    *(int *)(self + 0x5C) = 0x20;
    hud_init_counter_values(self);
}
