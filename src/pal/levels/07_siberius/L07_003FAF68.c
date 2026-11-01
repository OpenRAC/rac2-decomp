#include "include_asm.h"

#include "common.h"
extern void *func_002A9640(void *, int, int);
extern float func_PAL_002AA108(void *, void *);
extern float func_002AA2E8(float *, float, float);
extern void func_PAL_002A7650(void *, int, int);
extern int func_002E5CF8(int, int, char *);
extern void func_002A7750(u8 *, int, int);
extern u8 *func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float, int, int, int, void *);
extern void func_002A7398(void *, int, int);

void func_PAL_L07_003FAF68(u8 *self)
{
    u8 *state = *(u8 **)(self + 0x68);
    float position[4] __attribute__((aligned(16)));
    float zero = 0.0f;
    float step = func_PAL_002AA108(self, func_002A9640(self, 0x10000, 0));
    u16 flags;
    func_002AA2E8((float *)(state + 0x20), zero, step);
    if (*(float *)(state + 0x20) <= zero) {
        func_PAL_002A7650(self, 0, 3);
        func_002E5CF8(1, 0, (char *)self);
        func_002A7750(self, 1, -1);
        flags = *(u16 *)(self + 0x34);
        self[0xA8] = 255;
        flags |= 0x41;
        *(u32 *)(self + 0x98) = 0;
        flags &= 0xEFFF;
        *(u16 *)(self + 0x34) = flags;
        qcopy(position, self + 0x10);
        position[2] += 0.5f;
        func_PAL_L00_003FB330(self + 0x10, 0, 0, 0, 0, 10, 20, 0, 1.0f, 20.0f, 1, 0, 0, 0);
        func_002A7398(self, 2, 0);
    }
}

