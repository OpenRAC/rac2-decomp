#include "common.h"

/* Widen the packed high channels before combining the low channel, retaining
 * the original color-expression grouping with the pinned compiler. */

extern char *D_L14_001B259C __attribute__((sda));
extern char D_00189EA0[];
/* One unsplit `la`: it cannot fill the guard branch's delay slot, so the slot comes from the target. */
extern char D_L14_001A8F20[] MACRO_ADDR;
extern void func_002A7750(void *, int, int);
extern int func_002B3868(void *);
extern float func_00282E48(void *, void *);
extern int func_002ACBC8(void *, int);
extern float func_00283198(float);
extern void func_L00_003294F0(void *, int);
extern void func_002B4090(void *, void *, float, float, float);
extern void func_002833F0(void *, void *);

/* Updates a moby of class 2791: a glowing light that pulses, swings around to a half turn and then settles, carrying a linked object with it. */
void func_L14_003DE9B0(char *self) {
    float linkPos[4] __attribute__((aligned(16)));
    char *vars = *(char **)(self + 0x68);
    int glow, baseGlow, scaledGlow;

    switch ((unsigned char)self[0x20]) {
    case 0:
        if (*(int *)vars >= 0) {
            *(char **)(vars + 0x10) = gMobyPool_L14 + (*(int *)vars << 8);
            *(int *)(self + 0x78) = 0x80404040;
            *(unsigned short *)(self + 0x34) |= 0x10;
            *(int *)(vars + 0x14) = 0;
        } else {
            *(int *)(vars + 0x10) = 0;
        }
        SetMobyState(self, 1, -1);
        break;
    case 1:
        glow = *(int *)(vars + 0x18);
        *(int *)(self + 0x78) = (long long)(int)(0x80000000 | (glow << 16) | (glow << 8)) | glow;
        if (*(int *)(vars + 0xC) == -1) {
            if (fast_vec_dist(gHeroPosition, self + 0x10) < 10.0f) {
                SetMobyState(self, 2, -1);
            }
        } else if (IsPointInCuboid(gHeroPosition, *(int *)(vars + 0xC))) {
            SetMobyState(self, 2, -1);
        }
        break;
    case 2:
        if (SetFirstPendingFlag(self)) {
            *(int *)(vars + 0x1C) = 100;
        }
        if (*(int *)(vars + 0x1C)) {
            --*(int *)(vars + 0x1C);
        }
        baseGlow = *(int *)(vars + 0x18);
        scaledGlow = (int)((float)baseGlow * (float)*(int *)(vars + 0x1C) * 0.01f);
        *(int *)(self + 0x78) = (long long)(int)(0x80000000 | (scaledGlow << 16) | (scaledGlow << 8)) | baseGlow;
        if ((*(float *)(self + 0xF8) >= 3.1415927f && !*(int *)(vars + 8)) ||
            (*(float *)(self + 0xF4) <= -3.1415927f && *(int *)(vars + 8))) {
            SetMobyState(self, 3, -1);
            break;
        }
        if (*(int *)(vars + 8)) {
            *(float *)(self + 0xF4) -= *(float *)(vars + 4);
        } else {
            *(float *)(self + 0xF8) += *(float *)(vars + 4);
        }
        if (*(char **)(vars + 0x10)) {
            qcopy(linkPos, D_L14_001A8F20);
            linkPos[2] -= 0.5f;
            RotateObjectAboutPoint(*(char **)(vars + 0x10), linkPos, *(float *)(vars + 4), 0.0f, 0.0f);
            euler_rotation_basis(*(char **)(vars + 0x10) + 0xC0, *(char **)(vars + 0x10) + 0xF0);
        }
        break;
    case 3:
        if (SetFirstPendingFlag(self)) {
            *(float *)(self + 0xF8) = 3.1415927f;
            if (*(char **)(vars + 0x10)) {
                SetObjectFlagBit(*(char **)(vars + 0x10), 1);
            }
        }
        *(int *)(self + 0x78) = *(int *)(vars + 0x18) | 0x80000000;
        break;
    }
    ++*(int *)(vars + 0x14);
    *(int *)(vars + 0x18) = (int)(FastSinOrCosB((float)(*(int *)(vars + 0x14) % 150) * 0.041887905f) * 48.0f) + 80;
}
