#include "common.h"

/* func_PAL_0032F3B8, the PAL copy of func_0032DA58: the same C, where the small-data timers
   are ints scaled for 50 Hz, and each float goes straight to its field ahead of the next scale. */
extern char *func_0029EFD0(int);
extern void func_002AFFD8(void *, void *, int);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A7940(void), func_00283CE0(int);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00283DB8(void *, float);
extern void func_PAL_0032F7C8(void *, void *);
extern char D_001B5340[];
extern float D_001B081C __attribute__((sda));
extern int D_001B0750 __attribute__((sda)), D_001B0778 __attribute__((sda));
extern int D_001B0754 __attribute__((sda)), D_001B077C __attribute__((sda));
extern int D_001B0828 __attribute__((sda)), D_001B082C __attribute__((sda));
extern int D_001B0834 __attribute__((sda)), D_001B0838 __attribute__((sda));
char *func_PAL_0032F3B8(int unused, float *position, float *direction, float height)
{
    float basis[4], offset[4], sphere[4];
    char *self = func_0029EFD0(0xD4E);
    char *state;
    int extra;
    if (self) {
        *(unsigned char *)(self + 0x30) = 255;
        *(short *)(self + 0x32) = 255;
        state = *(char **)(self + 0x68);
        *(char *)(self + 0x20) = 0;
        qcopy(self + 0x10, position);
        *(float *)(self + 0x1C) = 1.0f;
        func_002AFFD8(self + 0x10, basis, 1);
        qcopy(self + 0xC0, direction);
        func_00282DD8(self + 0xD0, self + 0xC0, basis);
        func_00282F20(self + 0xD0, self + 0xD0, 1.0f);
        func_00282DD8(self + 0xE0, self + 0xD0, self + 0xC0);
        *(float *)(self + 0xCC) = *(float *)(self + 0xDC) = *(float *)(self + 0xEC) = 0.0f;
        func_00282D30(offset, self + 0xC0, 0.5f);
        func_00282CC0(self + 0x10, self + 0x10, offset);
        if (height != 0.0f) {
            if (D_001B081C * 1.5f <= *(float *)(self + 0x18) - height) height = 0.0f;
        }
        *(float *)(state + 0x18) = height;
        *(float *)(state + 0) = func_002A7940();
        *(float *)(state + 4) = func_002A7940();
        *(float *)(state + 8) = func_002A7940();
        *(float *)(state + 12) = func_002A7940();
        *(float *)(state + 16) = func_002A7940();
        *(float *)(state + 20) = func_002A7940();
        *(short *)(state + 0x1C) = ((s32)(D_001B0750) * 5 + 2) / 6;
        *(short *)(state + 0x1E) = ((s32)(D_001B0778) * 5 + 2) / 6;
        *(float *)(state + 0x20) = 1.0f / func_00283CE0(*(short *)(state + 0x1C));
        *(float *)(state + 0x24) = 1.0f / func_00283CE0(*(short *)(state + 0x1E));
        *(short *)(state + 0x28) = *(short *)(state + 0x1C) - ((s32)(D_001B0754) * 5 + 2) / 6;
        *(float *)(state + 0x2C) = 1.0f / func_00283CE0(*(short *)(state + 0x28));
        *(short *)(state + 0x2A) = *(short *)(state + 0x1E) - ((s32)(D_001B077C) * 5 + 2) / 6;
        *(float *)(state + 0x30) = 1.0f / func_00283CE0(*(short *)(state + 0x2A));
        if (func_002761F8(self + 0x10, D_001B5340, 18, 0, 0)) {
            *(short *)(state + 0x36) = 0;
        } else {
            *(short *)(state + 0x36) = (((int)(D_001B0828) * 5 + 2) / 6);
            *(float *)(state + 0x38) = 1.0f / func_00283CE0(*(short *)(state + 0x36));
            qcopy(sphere, self + 0x10);
            sphere[3] = 1.0f;
            if (func_00283DB8(sphere, 128.0f) == 1) {
                *(short *)(state + 0x34) = (((int)(D_001B082C) * 5 + 2) / 6);
                *(float *)(state + 0x3C) = 1.0f / func_00283CE0(*(short *)(state + 0x34));
                *(int *)(state + 0x40) = (((int)(D_001B0834) * 5 + 2) / 6);
                *(float *)(state + 0x44) = 1.0f / func_00283CE0(*(int *)(state + 0x40));
                extra = (((int)(D_001B0838) * 5 + 2) / 6);
                *(int *)(state + 0x40) += extra;
            } else {
                *(short *)(state + 0x34) = 0;
                *(int *)(state + 0x40) = 0;
            }
        }
        func_PAL_0032F7C8(self, basis);
    }
    return self;
}
