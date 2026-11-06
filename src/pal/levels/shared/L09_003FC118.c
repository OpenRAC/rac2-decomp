#include "include_asm.h"

extern unsigned int D_L09_001FE6C0[];
extern float func_00282E80(char *a, int b);

/* reports whether the index still names a reachable entry, or whether the frame moved close enough */
int func_PAL_L09_003FC418(char *object, int index) {
    char *frame = *(char **)(object + 0x68);
    int entry = func_L09_00329028(object, index);

    if (entry == 0 && index != -1) {
        int off = (*(short *)(frame + 0x1CA) << 4) + 0x10;

        if (func_00282E80(object + 0x10, D_L09_001FE6C0[index] + off) <
            *(float *)(frame + 0x134))
            entry = 1;
    }
    return entry;
}

