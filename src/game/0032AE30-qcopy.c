/* SPDX-License-Identifier: MIT */
#include "common.h"

typedef int TrailQuad __attribute__((mode(TI)));
extern unsigned char D_002329A0[];
extern void func_00282C88(void *);
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);
extern float func_002A7940(void);
extern float func_002A78D8(float, float);

/* Initializes a free resident trail node and increments its owner's count. */
void func_0032AE30(char *owner, void *position, int value)
{
    unsigned char *base = gTrailNodes;
    int flag = 0x800000;
    int *trailCount = *(int **)(owner + 0x68);
    unsigned char *velocityField = base + 0x10;
    unsigned char *node = base;
    unsigned char *end = node + 0x2800;
    float angle;
    int lifetime;

    do {
        if (*(int *)(node + 0x44) == 0) {
            *(char **)(node + 0x44) = owner;
            *(int *)(node + 0x30) = value;
            *(TrailQuad *)node = *(TrailQuad *)position;
            ClearVector128(velocityField);
            *(int *)(node + 0x38) = flag;
            *(float *)(node + 0x20) = RandomFloatRange(0.1f, 0.3f);
            *(float *)(node + 0x24) = RandomFloatRange(0.4f, 0.5f);
            lifetime = RandomIntRange(0x19, 0x28);
            *(int *)(node + 0x3C) = lifetime;
            *(int *)(node + 0x40) = lifetime;
            *(float *)(node + 0x2C) = RandomAngle();
            angle = RandomSignedFloatRange(180.0f, 360.0f);
            *(float *)(node + 0x28) = angle * 0.00029088824f;
            *trailCount += 1;
            break;
        }
        node += 0x50;
        velocityField += 0x50;
    } while ((long)node < (long)end);
}
