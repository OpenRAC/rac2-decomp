#include "include_asm.h"

#include "common.h"
extern float D_L01_001AF628 __attribute__((sda));
extern float func_00283B98(float, float);
extern void func_00283898(char *, int, float);
extern void func_0029F978(char *, int, char *);
extern float func_002A7940(void);
extern float func_00283B98(float, float);

/* grows a moby out of the ground the first time, then spins it down */
void func_PAL_L01_0039C590(char *a0)
{
    char *s1 = *(char **)(a0 + 0x68);

    switch (*(unsigned char *)(a0 + 0x20)) {
    case 0:
        *(unsigned char *)(a0 + 0x20) = 1;
        *(unsigned char *)(a0 + 0x63) = 0x20;
        *(float *)(s1 + 0x40) = func_002A7940();
        func_0029F978(a0, 1, s1);
        break;
    case 1: {
        float f = D_L01_001AF628 * 0.0003490659f;

        *(float *)(a0 + 0xF8) = func_00283B98(*(float *)(a0 + 0xF8), f);
        *(float *)(s1 + 0x40) = func_00283B98(*(float *)(s1 + 0x40), f * -2.0f);
        func_00283898(s1 + 0x10, 2, *(float *)(s1 + 0x40));
        break;
    }
    }
}
