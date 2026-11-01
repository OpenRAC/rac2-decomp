#include "include_asm.h"

extern char *D_L23_001B1484 __attribute__((sda));
extern void func_0029F978(char *, int, char *);
extern void func_00283898(void *, int, float);
extern float func_00283BE0(float, float);
extern float D_L23_001B1570 __attribute__((sda));
extern float D_L23_001B1574 __attribute__((sda));

/* Relatches the two measured pairs at +0x580 and +0x584 from the two float arguments. */
void func_PAL_L23_00420FF8(char *arg0, float arg1, float arg2) {
    char *state = *(char **)(D_L23_001B1484 + 0x68);

    if (*(unsigned char *)(state + 0x4F1) == 0)
        func_0029F978(arg0, 0x28, state + 0x4F0);
    func_00283898(state + 0x500, 0, *(float *)(state + 0x580));
    *(float *)(state + 0x580) = func_00283BE0(*(float *)(state + 0x580), arg1 * D_L23_001B1570 * 0.0003490659f);
    if (*(unsigned char *)(state + 0x531) == 0)
        func_0029F978(arg0, 0x29, state + 0x530);
    func_00283898(state + 0x540, 0, *(float *)(state + 0x584));
    *(float *)(state + 0x584) = func_00283BE0(*(float *)(state + 0x584), arg2 * D_L23_001B1574 * 0.0003490659f);
}
