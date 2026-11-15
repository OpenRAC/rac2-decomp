#include "common.h"

extern void func_002A91F0(void *, float *);

/* Advance the four-slot history and capture the attached object position. */
void func_L02_003F1608(char *actor) {
    char *state = *(char **)(actor + 0x68);

    *(int *)(state + 0x4D8) = 0;
    *(int *)(state + 0x4D4) = (*(int *)(state + 0x4D4) + 1) % 4;
    if (*(int *)(state + 0x4D0) < 4)
        (*(int *)(state + 0x4D0))++;
    BuildRotationFromAngles(state + (*(int *)(state + 0x4D4) * 16 + 0x3A0), (float *)(actor + 0xF0));
    if (*(int *)(state + 0x4C4) != 0)
        qcopy(state + *(int *)(state + 0x4D4) * 16 + 0x2A0,
              (char *)(*(int *)(state + 0x4C4) + 0x10));
}
