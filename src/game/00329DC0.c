#include "common.h"

extern unsigned char *ref_L00_00329DC0_01[];
extern char ref_L00_00329DC0_00[];
extern void *g_hero_moby;
extern int CollLine(void *, void *, int, void *, int);

/* The twin of func_003286D0 that also mirrors the placed vector into its state block. */
int moby_place_at_collision_point_mirror(char *self, void *previous_pos)
{
    char *state = *(char **)(self + 0x68);
    char *current_object;

    if (CollLine(previous_pos, self + 0x10, 0, self, 0) != 0) {
        current_object = (char *)ref_L00_00329DC0_01[0];
        if (current_object != 0 && (*(short *)(current_object + 0xAA) == MOBY_CLASS_THERMANATOR || current_object == (char *)g_hero_moby))
            return 0;
        qcopy(self + 0x10, ref_L00_00329DC0_00);
        qcopy(state + 0x20, self + 0x10);
        return 1;
    }
    return 0;
}
