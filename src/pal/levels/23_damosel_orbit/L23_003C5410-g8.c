#include "include_asm.h"

extern float D_L23_001AFAA0 __attribute__((sda));
extern void func_0029F978(int, int, char *);
extern void func_00283898(char *, int, float);
extern float func_00283BE0(float, float);

void func_PAL_L23_003C5410(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    if (*(unsigned char *)(state + 0x371) == 0)
        func_0029F978(*(int *)(state + 0x2A0), 2, state + 0x370);
    func_00283898(state + 0x380, 2, *(float *)(state + 0x3B0));
    *(float *)(state + 0x3B0) = func_00283BE0(*(float *)(state + 0x3B0),
                                            D_L23_001AFAA0 * 0.0003490659f);
}
