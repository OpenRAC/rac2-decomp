#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;

/* The measured table step is 0x80 bytes; count is unspecified. */
extern char *D_L14_001B268C __attribute__((sda));
extern char D_00188660[];
extern void func_002AA548(void *, void *, float, float, float, float);
extern void func_002AD6F0(void *, void *, void *, void *);
extern float func_00282C48(float);
extern int func_002E5CF8(int, int, void *);
extern void func_002E59F8(int);

/* Slides a platform toward its target height, moves whatever rides on it and keeps its motion sound playing. */
void func_L14_003DF6A0(char *self) {
    struct { Vector argument, rotation; } scratch;
    char *vars = *(char **)(self + 0x68);
    float target;
    int soundSlot;
    if (*(int *)(vars + 0x7C))
        target = *(float *)(((char (*)[0x80])D_L14_001B268C)[*(int *)(vars + 0x60)] + 0x38);
    else
        target = *(float *)(vars + 0x70);
    StepValueTowardTarget(self + 0x18, vars + 0x74, target,
                 0.0011111111f, 0.0022222222f, 1.0f);
    scratch.rotation.q = 0;
    scratch.rotation.f[2] = *(float *)(vars + 0x74);
    scratch.argument.q = scratch.rotation.q;
    CombineTransformsAndStore(vars + 0x20, &scratch.argument, self + 0xF0, self + 0xF0);
    if (0.01f < FloatAbs(*(float *)(vars + 0x74))) {
        char *soundEntry = gSoundState + *(int *)(vars + 0x78) * 0x70;
        if (*(char **)(soundEntry + 0x88) != self || *(unsigned char *)(soundEntry + 0x74) == 0)
            *(int *)(vars + 0x78) = PlayMobySound(0, 4, self);
    } else {
        soundSlot = *(int *)(vars + 0x78);
        if (soundSlot != -1) {
            char *soundEntry = gSoundState + soundSlot * 0x70;
            if (*(char **)(soundEntry + 0x88) == self && *(unsigned char *)(soundEntry + 0x74) != 0)
                StopSoundVoice(soundSlot);
        }
        *(int *)(vars + 0x78) = -1;
    }
}
