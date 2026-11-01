#include "include_asm.h"

extern int func_00282978(short *);
extern void func_00282CC0(char *, char *, char *);
extern void func_002B9180(void *);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern int D_001AA39C __attribute__((sda));
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern void func_PAL_002BD790(char *, char *, int, int, int, int, int, int, int, float);

void func_PAL_002C45E8(char *self)
{
    char *motion = self + 0x20;
    char *position;
    int ttl;
    if (func_00282978((short *)(self + 0xA)))
        *(float *)(motion + 8) -= *(float *)(motion + 0x14);
    position = self + 0x10;
    func_00282CC0(position, position, motion);
    *(unsigned char *)(self + 8) += 2;
    if (*(float *)(self + 0x18) < *(float *)(motion + 0x10)) {
        if (func_002A77E0(D_001AA39C - 1) == 0) {
            *(float *)(self + 0x18) = *(float *)(motion + 0x10);
            *(float *)(self + 0x20) *= func_002A7878(1.0f, 3.5f);
            *(float *)(motion + 4) *= func_002A7878(1.0f, 3.5f);
            *(float *)(motion + 8) *= func_002A7878(-1.0f, -1.5f);
            ttl = func_002A7820(50, 100);
            func_PAL_002BD790(position, motion, *(int *)(self + 4), *(int *)(motion + 0x18),
                ttl, 0, *(unsigned char *)(self + 2), *(unsigned char *)(self + 3), 0,
                *(float *)(self + 0xC) * 0.5f);
        } else {
            *(float *)(self + 0x18) = *(float *)(motion + 0x10);
            *(float *)(self + 0x20) += func_002A7878(-5.0f, 5.0f) * 0.020000001f;
            *(float *)(motion + 4) += func_002A7878(-5.0f, 5.0f) * 0.020000001f;
            *(float *)(motion + 8) *= func_002A7878(-0.5f, -1.0f);
            ttl = func_002A7820(25, 50);
            func_PAL_002BD790(position, motion, *(int *)(self + 4), *(int *)(motion + 0x18),
                ttl, 0, *(unsigned char *)(self + 2), *(unsigned char *)(self + 3), 0,
                *(float *)(self + 0xC) * 0.25f);
        }
        func_002B9180(self);
    }
}
