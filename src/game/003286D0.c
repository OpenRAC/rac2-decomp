#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern int CollLine(void *a, void *b, int mode, void *self, int flag);
extern char *ref_L00_003286D0_00;
extern char ref_L00_003286D0_01[];
extern char *g_hero_moby;

/* Ask the shared helper to place a1's vector at self+0x10; on success, unless the
   level's current object is excluded (its +0xAA id is 0xFB0, or it is the object at
   D_0018C0B0), copy the resident vector there and answer 1. */

int moby_place_at_collision_point(char *self, void *previous_pos)
{
    char *current_object;

    if (CollLine(previous_pos, self + 0x10, 0, self, 0) != 0) {
        current_object = ref_L00_003286D0_00;
        if (current_object != 0 && (*(short *)(current_object + 0xAA) == MOBY_CLASS_THERMANATOR || current_object == g_hero_moby))
            return 0;
        qcopy(self + 0x10, ref_L00_003286D0_01);
        return 1;
    }
    return 0;
}
