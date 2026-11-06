#include "common.h"

/* func_US2_L14_003DFE88, the USA v2.00 copy of func_L14_003DE9B0: case 0 also records the
 * current angle at s + 0x1C, and case 2 fades the colour by the angle left to turn instead
 * of a hit timer. */

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

void func_US2_L14_003DFE88(char *self) {
    float v[4] __attribute__((aligned(16)));
    char *s = *(char **)(self + 0x68);
    int c, t;

    switch ((unsigned char)self[0x20]) {
    case 0:
        if (*(int *)s >= 0) {
            *(char **)(s + 0x10) = D_L14_001B259C + (*(int *)s << 8);
            *(int *)(self + 0x78) = 0x80404040;
            *(unsigned short *)(self + 0x34) |= 0x10;
            *(int *)(s + 0x14) = 0;
        } else {
            *(int *)(s + 0x10) = 0;
        }
        if (*(int *)(s + 8)) {
            *(float *)(s + 0x1C) = *(float *)(self + 0xF4);
        } else {
            *(float *)(s + 0x1C) = *(float *)(self + 0xF8);
        }
        func_002A7750(self, 1, -1);
        break;
    case 1:
        c = *(int *)(s + 0x18);
        *(int *)(self + 0x78) = (long long)(int)(0x80000000 | (c << 16) | (c << 8)) | c;
        if (*(int *)(s + 0xC) == -1) {
            if (func_00282E48(D_00189EA0, self + 0x10) < 10.0f) {
                func_002A7750(self, 2, -1);
            }
        } else if (func_002ACBC8(D_00189EA0, *(int *)(s + 0xC))) {
            func_002A7750(self, 2, -1);
        }
        break;
    case 2:
        if (*(int *)(s + 8)) {
            t = (int)((float)*(int *)(s + 0x18) * (*(float *)(self + 0xF4) + 3.1415927f) * 0.31830987f);
        } else {
            t = (int)((float)*(int *)(s + 0x18) * (3.1415927f - *(float *)(self + 0xF8)) * 0.31830987f);
        }
        *(int *)(self + 0x78) = (long long)(int)(0x80000000 | (t << 16) | (t << 8)) | *(int *)(s + 0x18);
        if ((*(float *)(self + 0xF8) >= 3.1415927f && !*(int *)(s + 8)) ||
            (*(float *)(self + 0xF4) <= -3.1415927f && *(int *)(s + 8))) {
            func_002A7750(self, 3, -1);
            break;
        }
        if (*(int *)(s + 8)) {
            *(float *)(self + 0xF4) -= *(float *)(s + 4);
        } else {
            *(float *)(self + 0xF8) += *(float *)(s + 4);
        }
        if (*(char **)(s + 0x10)) {
            qcopy(v, D_L14_001A8F20);
            v[2] -= 0.5f;
            func_002B4090(*(char **)(s + 0x10), v, *(float *)(s + 4), 0.0f, 0.0f);
            func_002833F0(*(char **)(s + 0x10) + 0xC0, *(char **)(s + 0x10) + 0xF0);
        }
        break;
    case 3:
        if (func_002B3868(self)) {
            *(float *)(self + 0xF8) = 3.1415927f;
            if (*(char **)(s + 0x10)) {
                func_L00_003294F0(*(char **)(s + 0x10), 1);
            }
        }
        *(int *)(self + 0x78) = *(int *)(s + 0x18) | 0x80000000;
        break;
    }
    ++*(int *)(s + 0x14);
    *(int *)(s + 0x18) = (int)(func_00283198((float)(*(int *)(s + 0x14) % 150) * 0.041887905f) * 48.0f) + 80;
}
