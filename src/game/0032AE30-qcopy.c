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
    unsigned char *base = D_002329A0;
    int flag = 0x800000;
    int *count = *(int **)(owner + 0x68);
    unsigned char *position_field = base + 0x10;
    unsigned char *slot = base;
    unsigned char *end = slot + 0x2800;
    float angle;
    int lifetime;

    do {
        if (*(int *)(slot + 0x44) == 0) {
            *(char **)(slot + 0x44) = owner;
            *(int *)(slot + 0x30) = value;
            *(TrailQuad *)slot = *(TrailQuad *)position;
            func_00282C88(position_field);
            *(int *)(slot + 0x38) = flag;
            *(float *)(slot + 0x20) = func_002A7878(0.1f, 0.3f);
            *(float *)(slot + 0x24) = func_002A7878(0.4f, 0.5f);
            lifetime = func_002A7820(0x19, 0x28);
            *(int *)(slot + 0x3C) = lifetime;
            *(int *)(slot + 0x40) = lifetime;
            *(float *)(slot + 0x2C) = func_002A7940();
            angle = func_002A78D8(180.0f, 360.0f);
            *(float *)(slot + 0x28) = angle * 0.00029088824f;
            *count += 1;
            break;
        }
        slot += 0x50;
        position_field += 0x50;
    } while ((long)slot < (long)end);
}
