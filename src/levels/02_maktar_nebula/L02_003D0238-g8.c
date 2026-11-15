#include "common.h"

extern int D_L02_001B0138 __attribute__((sda));
extern int D_L02_001B013C NOT_SDA;
extern int PulseColor(int, int, float);
extern void moby_set_state(char *, int, int);
extern void moby_set_flag_bit(char *, int);
extern int moby_fuse_linked_objects(void *, void *, void *, void *, int);

/* Puts the timed platform back in its starting place, ready to be used again. */
void platform_respawn_timed(char *self)
{
    char *state = *(char **)(self + 0x68);

    *(int *)(state + 0xD8) = 0;
    *(int *)(self + 0x78) = PulseColor(D_L02_001B0138, D_L02_001B013C, *(float *)(state + 0xD8));
    moby_set_state(self, 1, -1);
    qcopy(self + 0x10, state + 0xA0);
    qcopy(state + 0x60, state + 0xA0);
    qzero_nc(state + 0x50);
    self[0x31] = 1;
    *(unsigned short *)(self + 0x34) = (*(unsigned short *)(self + 0x34) & 0xFFFE) | 0x1000;
    moby_set_flag_bit(self, 0);
    moby_fuse_linked_objects(self, self + 0x10, self + 0xF0, 0, 0);
}
