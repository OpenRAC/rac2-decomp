#include "include_asm.h"
#include "names.h"

extern float func_002E3B10(float f12, float f13);
extern int func_003212C0(char *a0, char *a1, float f12);

/* Turns a moby toward a target point by the angle between them and returns the helper result (PAL). */
int moby_l01_turn_toward_target_pal(char *moby, char *target) {
    float angle = func_002E3B10(*(float *)(target + 0) - *(float *)(moby + 0x10),
                            *(float *)(target + 4) - *(float *)(moby + 0x14));
    return func_003212C0(moby, target, angle);
}

