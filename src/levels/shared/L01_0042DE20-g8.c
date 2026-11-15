#include "common.h"

extern void func_002ACEC0(void *, void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002B0520(void *);
extern void func_L01_00355BA0(int, int);
extern int func_L00_0035F640(int, int, void *, int);

extern struct {
    char prefix[0x140];
    float pos[4];
} D_L01_001B9380;

typedef struct {
    char prefix[0x74];
    unsigned char active;
    char pad[0x17];
    char *owner;
    float pos[4];
    char tail[0x40];
} TransitionSoundSlot;

extern char D_00188660[];
extern float D_L01_001B1D7C __attribute__((sda));
extern float D_001A7928 __attribute__((sda));

void func_L01_0042DE20(char *m)
{
    float sample[4], radius[4], axis[4];
    char *state = *(char **)(m + 8);
    float exposedFraction = 0, angle = 0;

    radius[0] = 4;
    radius[1] = 0;
    radius[2] = 0;
    radius[3] = 1;
    axis[0] = 0;
    axis[1] = 0;
    axis[2] = 1;
    do {
        func_002ACEC0(sample, radius, axis, angle);
        FastVecAdd(sample, D_L01_001B9380.pos, sample);
        if (func_002B0520(sample) < D_L01_001B9380.pos[2])
            exposedFraction += 0.05f;
        angle += 0.3141592741012573f;
    } while (angle < 6.2831854820251465f);

    if (D_L01_001B1D7C < exposedFraction)
        D_L01_001B1D7C += D_001A7928 * 0.2f;
    else
        D_L01_001B1D7C -= D_001A7928 * 0.75f;
    if (D_L01_001B1D7C > 1)
        D_L01_001B1D7C = 1;
    else if (D_L01_001B1D7C < 0)
        D_L01_001B1D7C = 0;

    if (((TransitionSoundSlot *)(D_00188660 + *(int *)(state + 8) * 0x70))->owner == m &&
        ((TransitionSoundSlot *)(D_00188660 + *(int *)(state + 8) * 0x70))->active)
        func_L01_00355BA0(*(int *)(state + 8),
                         (int)((*(float *)(state + 4) + D_L01_001B1D7C) /
                               (*(float *)(state + 4) + 1) * 1024));
    qcopy_nc(((TransitionSoundSlot *)(D_00188660 + *(int *)(state + 8) * 0x70))->pos,
             D_L01_001B9380.pos);
    if (((TransitionSoundSlot *)(D_00188660 + *(int *)(state + 8) * 0x70))->owner != m ||
        !((TransitionSoundSlot *)(D_00188660 + *(int *)(state + 8) * 0x70))->active)
        *(int *)(state + 8) = func_L00_0035F640(*(int *)state, 0x15, m, 0x400);
}
