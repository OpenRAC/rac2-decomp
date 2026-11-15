#include "common.h"

extern void mat_build_rotation_from_angles(void *, float *);

/* Advance the four-slot history and capture the attached object position. */
void actor_record_position_history(char *actor) {
    char *state = *(char **)(actor + 0x68);

    *(int *)(state + 0x4D8) = 0;
    *(int *)(state + 0x4D4) = (*(int *)(state + 0x4D4) + 1) % 4;
    if (*(int *)(state + 0x4D0) < 4)
        (*(int *)(state + 0x4D0))++;
    mat_build_rotation_from_angles(state + (*(int *)(state + 0x4D4) * 16 + 0x3A0), (float *)(actor + 0xF0));
    if (*(int *)(state + 0x4C4) != 0)
        qcopy(state + *(int *)(state + 0x4D4) * 16 + 0x2A0,
              (char *)(*(int *)(state + 0x4C4) + 0x10));
}
