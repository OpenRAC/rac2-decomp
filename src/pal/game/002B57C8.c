#include "include_asm.h"

extern int D_001A8A5C __attribute__((sda));
extern int D_PAL_001A8C64 __attribute__((sda));

int func_PAL_002B57C8(void) {
    return D_PAL_001A8C64;
}



extern float func_00283248(float, float);
extern char *func_002B5D28(void *);
extern float func_00283B98(float, float);
extern int func_00282978(short *);
extern int func_002A7820(int, int);
extern int func_002B50E0(void *, void *, float);
extern int func_002B50E0(void *, void *, float);

int func_PAL_002B5BA8(char *self, float *target, float amount)
{
    char *data = func_002B5D28(self);
    float angle;
    if (data == 0)
        return 8;
    angle = func_00283248(target[0] - *(float *)(self + 0x10),
                         target[1] - *(float *)(self + 0x14));
    angle = func_00283B98(angle, amount);
    if (*(float *)(data + 0xDC) != 0.0f) {
        angle = func_00283B98(angle, *(float *)(data + 0xDC));
        if (func_00282978((short *)(data + 0xE0))) {
            *(float *)(data + 0xDC) = -*(float *)(data + 0xDC);
            *(short *)(data + 0xE0) = func_002A7820(*(short *)(data + 0xE2), *(short *)(data + 0xE4));
        }
    }
    return func_002B50E0(self, target, angle);
}


void func_PAL_002B5E10(char *m) {
    func_002B50E0(m, m + 0x10, *(float *)(m + 0xF8));
}

