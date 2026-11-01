#include "include_asm.h"

#include "common.h"
extern void func_0029F338(void *);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_002AF000(void *, float, float, float);
extern void func_0029FCC0(void *, int, void *);
extern void func_PAL_L08_003B6448(void *, void *, void *, int);
extern float func_002A7878(float, float);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002A7820(int, int);
extern void func_L04_00358AE8(void *, void *, int, int, float);
typedef int TI128 __attribute__((mode(TI)));
extern u8 D_001A7A40[] __attribute__((sda));
extern u8 D_L08_001B22E0[] __attribute__((sda));
extern u8 D_001A7A00[] __attribute__((sda));
extern u8 D_L08_001A7C80[] __attribute__((sda));
extern u8 D_001395B8[];
extern u8 D_L08_001BFD00[];

void func_PAL_L08_003D8718(u8 *self)
{
    float direction[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float random[4] __attribute__((aligned(16)));
    u8 *target = *(u8 **)*(u32 *)(self + 0x68);
    int i;
    if (!target || target[0x20] == 0xFE || target[0x20] == 0xFD) {
        func_0029F338(self);
        return;
    }
    if ((self[0x60] & 2) && self[0x43])
        func_PAL_002A7E68(self, 0, 0, 0);
    if (self[0xBC]) {
        self[0xBC] = 0;
        if (self[0x43] != 1) func_PAL_002A7E68(self, 1, 0, 0);
        func_002AF000(direction, 1.2f, *(float *)(self+0xF8), -*(float *)(self+0xF4));
        func_0029FCC0(self, 0, position);
        func_PAL_L08_003B6448(self, position, direction, 0x4B);
        i = 4;
        do {
            *(TI128 *)random = 0;
            random[0] = func_002A7878(-1.0f, 1.0f);
            random[1] = func_002A7878(-1.0f, 1.0f);
            random[2] = func_002A7878(-1.0f, 1.0f);
            *(TI128 *)velocity = *(TI128 *)random;
            func_00282F20(velocity, velocity, func_00282DF0(direction)*0.5799999f);
            func_00282CC0(velocity, direction, velocity);
            func_00282F20(velocity, velocity, func_002A7878(0.060000002f, 0.120000005f));
            func_L04_00358AE8(position, velocity, 0x5F2F4F6F, func_002A7820(4,8), 50000.0f);
        } while (--i >= 0);
        func_00282F20(direction, direction, 0.010000001f);
        func_L04_00358AE8(position, direction, 0x2F4F7F7F, func_002A7820(3,6), 500000.0f);
    }
}

