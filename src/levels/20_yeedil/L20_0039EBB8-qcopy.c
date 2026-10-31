#include "common.h"

/* Built with -g as well as the grouped-copy profile: the line notes of -g give the nop pair
   retail has in front of the div.s. */
typedef int TI128 __attribute__((mode(TI)));

/* A vector of four floats, copied as one quadword. */
typedef union {
    TI128 q;
    float f[4];
} Vector;

extern int func_002B3868(unsigned char *);

extern void func_002A7750(unsigned char *, int, int);

extern int func_00282948(int *);

extern void func_00282CF0(void *, const void *, const void *);

extern void func_002AD6F0(void *, const void *, const void *, const void *);

/* Two-state mover. State 0 records the start position (object + 0x10) in state + 0x60 when
   func_002B3868 returns nonzero, and switches to state 1. State 1 steps the timer at
   state + 0x7C (set from state + 0x78 when func_002B3868 returns nonzero), restores the start
   position and adds to its height (object + 0x14) a value interpolated between the bounds at
   state + 0x74 and state + 0x70 by the timer phase, brought down to at most 1. Both states
   then pass the position change, the old rotation and the rotation at object + 0xF0 to
   func_002AD6F0. */
void func_L20_0039EBB8(unsigned char *object) {
    Vector oldPosition, oldRotation, delta;
    unsigned char *state = *(unsigned char **)(object + 0x68);
    float phase, low, high, z;

    oldPosition.q = *(TI128 *)(object + 0x10);
    oldRotation.q = *(TI128 *)(object + 0xF0);
    switch (object[0x20]) {
    case 0:
        if (func_002B3868(object)) *(TI128 *)(state + 0x60) = *(TI128 *)(object + 0x10);
        func_002A7750(object, 1, -1);
        break;
    case 1:
        if (func_002B3868(object)) *(int *)(state + 0x7C) = *(int *)(state + 0x78);
        if (func_00282948((int *)(state + 0x7C))) func_002A7750(object, 1, -1);
        *(TI128 *)(object + 0x10) = *(TI128 *)(state + 0x60);
        phase = (float)*(int *)(state + 0x7C) / (float)*(int *)(state + 0x78) + *(float *)(state + 0x80);
        high = *(float *)(state + 0x70);
        low = *(float *)(state + 0x74);
        z = *(float *)(object + 0x14);
        while (1.0f < phase) phase -= 1.0f;
        *(float *)(object + 0x14) = z + (low + (high - low) * phase);
        break;
    }
    func_00282CF0(&delta, object + 0x10, &oldPosition);
    func_002AD6F0(state + 0x20, &delta, &oldRotation, object + 0xF0);
}
