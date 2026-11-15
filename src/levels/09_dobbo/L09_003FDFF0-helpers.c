#include "common.h"

typedef int TI __attribute__((mode(TI)));

extern int func_002A77E0(int);
extern float func_00283CE0(int);
extern int func_00283DB8(float *, float);
extern void func_0029FC20(char *, int, char *);
extern void func_00282F20(float *, float *, float);

/* If the object is on screen, rebuilds its camera-facing frame and asks for it to be drawn. */
void func_L09_003FDFF0(unsigned char *moby) {
    unsigned char *mobyBytes = moby;
    unsigned char *vars = *(unsigned char **)(mobyBytes + 0x68);
    float sphere[4] __attribute__((aligned(16)));
    if (RandomIntBelow(5) == 0)
        return;
    qcopy(sphere, mobyBytes + 0x10);
    sphere[3] = 4.0f;
    if (FastMathHelperA(sphere, IntToFloat(*(short *)(mobyBytes + 0x32))) == -1)
        return;
    TransformMobyJointPoint((char *)mobyBytes, 1, (char *)(vars + 0x340));
    vec_scale_to_length((float *)(vars + 0x340), (float *)(vars + 0x340), 1.0f);
    vec_scale_to_length((float *)(vars + 0x350), (float *)(vars + 0x350), 1.0f);
    vec_scale_to_length((float *)(vars + 0x360), (float *)(vars + 0x360), 1.0f);
    *(int *)(vars + 0x42C) = 2;
}
