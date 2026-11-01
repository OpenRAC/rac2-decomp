#include "include_asm.h"

typedef float f32_F7036ef03;
extern f32_F7036ef03 D_L04_001AE4A8 __attribute__((sda));
extern f32_F7036ef03 D_L04_001AE4B0 __attribute__((sda));
extern f32_F7036ef03 D_L04_001AE4B8 __attribute__((sda));
extern f32_F7036ef03 D_L04_001AE4C0 __attribute__((sda));
extern f32_F7036ef03 D_L04_001AE4C8 __attribute__((sda));
extern f32_F7036ef03 D_L04_001AE4AC;
extern f32_F7036ef03 D_L04_001AE4B4;
extern f32_F7036ef03 D_L04_001AE4BC;
extern f32_F7036ef03 D_L04_001AE4C4;
extern f32_F7036ef03 D_L04_001AE4CC;
extern void func_00335E38(void *a0, f32_F7036ef03 a1, f32_F7036ef03 a2, f32_F7036ef03 a3, f32_F7036ef03 a4);
extern void func_00343040(void *a0, f32_F7036ef03 a1, f32_F7036ef03 a2);
extern void func_US2_00344558(void *a0);
extern void func_US2_003444E8(void *a0);
extern int func_00342978(void *a0, int a1);

void func_US2_003446B8(char *self, int arg)
{
    f32_F7036ef03 *v;
    char *sub = self + 712;

    v = *(f32_F7036ef03 **)(self + 696);
    func_00335E38(self, D_L04_001AE4A8 + v[0], D_L04_001AE4AC + v[1], 0.0f, 0.0f);
    v = *(f32_F7036ef03 **)(self + 696);
    func_00335E38(self + 76, D_L04_001AE4B0 + v[0], D_L04_001AE4B4 + v[1], 0.0f, 0.0f);
    v = *(f32_F7036ef03 **)(self + 696);
    func_00335E38(self + 152, D_L04_001AE4B8 + v[0], D_L04_001AE4BC + v[1], 0.0f, 0.0f);
    v = *(f32_F7036ef03 **)(self + 696);
    func_00335E38(self + 608, D_L04_001AE4C0 + v[0], D_L04_001AE4C4 + v[1], 0.0f, 0.0f);
    v = *(f32_F7036ef03 **)(self + 696);
    func_00343040(sub, D_L04_001AE4C8 + v[0], D_L04_001AE4CC + v[1]);
    func_US2_00344558(self);
    func_US2_003444E8(self);
    *(int *)(self + 416) = func_00342978(sub, arg);
}
