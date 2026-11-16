#include "common.h"

/* func_PAL_L20_003A1B00, the PAL copy of func_L20_0039EBB8: the same C, where state 0 also scales
   the timer reload at state + 0x78 to 50 Hz when it records the start position. */

/* Built with -g as well as the grouped-copy profile: the line notes of -g give the nop pair
   retail has in front of the div.s. */
typedef int TI128 __attribute__((mode(TI)));

/* A vector of four floats, copied as one quadword. */
typedef union {
    TI128 q;
    float f[4];
} Vector;

extern int flag_set_first_pending(unsigned char *);

extern void moby_set_state(unsigned char *, int, int);

extern int math_fast_float_d(int *);

extern void FastVecSub(void *, const void *, const void *);

extern void mat_combine_and_store(void *, const void *, const void *, const void *);

/* Two-state mover. State 0 records the start position (object + 0x10) in state + 0x60 when
   func_002B3868 returns nonzero, and switches to state 1. State 1 steps the timer at
   state + 0x7C (set from state + 0x78 when func_002B3868 returns nonzero), restores the start
   position and adds to its height (object + 0x14) a value interpolated between the bounds at
   state + 0x74 and state + 0x70 by the timer phase, brought down to at most 1. Both states
   then pass the position change, the old rotation and the rotation at object + 0xF0 to
   func_002AD6F0. */
/* Moves a platform up and down in a repeating wave and passes its movement on to what rides on it (PAL: 50 Hz timer). */
void bobbing_l20_platform_update_pal(unsigned char *object) {
    Vector old_position, old_rotation, delta;
    unsigned char *state = *(unsigned char **)(object + 0x68);
    float phase, low, high, z;

    old_position.q = *(TI128 *)(object + 0x10);
    old_rotation.q = *(TI128 *)(object + 0xF0);
    switch (object[0x20]) {
    case 0:
        if (flag_set_first_pending(object)) {
            *(TI128 *)(state + 0x60) = *(TI128 *)(object + 0x10);
            *(int *)(state + 0x78) = ((s32)*(int *)(state + 0x78) * 5 + 2) / 6;
        }
        moby_set_state(object, 1, -1);
        break;
    case 1:
        if (flag_set_first_pending(object)) *(int *)(state + 0x7C) = *(int *)(state + 0x78);
        if (math_fast_float_d((int *)(state + 0x7C))) moby_set_state(object, 1, -1);
        *(TI128 *)(object + 0x10) = *(TI128 *)(state + 0x60);
        phase = (float)*(int *)(state + 0x7C) / (float)*(int *)(state + 0x78) + *(float *)(state + 0x80);
        high = *(float *)(state + 0x70);
        low = *(float *)(state + 0x74);
        z = *(float *)(object + 0x14);
        while (1.0f < phase) phase -= 1.0f;
        *(float *)(object + 0x14) = z + (low + (high - low) * phase);
        break;
    }
    FastVecSub(&delta, object + 0x10, &old_position);
    mat_combine_and_store(state + 0x20, &delta, &old_rotation, object + 0xF0);
}
