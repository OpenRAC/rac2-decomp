#include "common.h"

extern int func_0028B950(void *);

/* Resets an object's counters and sets its size and limit values, then hands it to the shared setup call. */
int func_L00_002F74F0(char *self) {
    *(short *)(self + 0x48) = 0;
    *(short *)(self + 0x4A) = 0;
    *(int *)(self + 0x58) = 0x20;
    *(int *)(self + 0x7C) = 0x28;
    *(int *)(self + 0x5C) = 0x20;
    return InitHudCounterValues(self);
}
