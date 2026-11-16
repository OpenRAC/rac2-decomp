#include "include_asm.h"
#include "names.h"

extern float func_002E3B10(float f12, float f13);
extern int func_003212C0(char *a0, char *a1, float f12);

int moby_l01_turn_toward_target_pal(char *a0, char *a1) {
    float v = func_002E3B10(*(float *)(a1 + 0) - *(float *)(a0 + 0x10),
                            *(float *)(a1 + 4) - *(float *)(a0 + 0x14));
    return func_003212C0(a0, a1, v);
}

