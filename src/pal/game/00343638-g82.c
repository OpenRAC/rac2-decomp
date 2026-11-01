#include "include_asm.h"

typedef float f32_Fd368add8;
extern f32_Fd368add8 D_L01_001AE3F8 __attribute__((sda));
extern f32_Fd368add8 D_L01_001AE408 __attribute__((sda));
extern f32_Fd368add8 D_L01_001AE400 __attribute__((sda));
extern f32_Fd368add8 D_L01_001AE410 __attribute__((sda));
extern f32_Fd368add8 D_L01_001AE418 __attribute__((sda));
extern f32_Fd368add8 D_L01_001AE3FC;
extern f32_Fd368add8 D_L01_001AE40C;
extern f32_Fd368add8 D_L01_001AE404;
extern f32_Fd368add8 D_L01_001AE414;
extern f32_Fd368add8 D_L01_001AE41C;
extern void func_00335E38(void *a0, f32_Fd368add8 a1, f32_Fd368add8 a2, f32_Fd368add8 a3, f32_Fd368add8 a4);
extern void *func_00335E20(void *a0);
extern int func_PAL_002A9FA0(int a0, int a1, int a2, int a3, int a4);
extern void func_PAL_00343838(void *a0, int a1);
extern void func_PAL_003437C8(void *a0);
extern void ref_L00_003418C0_00(void *a0);

int func_PAL_00343928(char *self, int arg1)
{
    f32_Fd368add8 *v;

    v = *(f32_Fd368add8 **)(self + 552);
    func_00335E38(self, D_L01_001AE3F8 + v[0], D_L01_001AE3FC + v[1], 0.0f, 0.0f);
    v = *(f32_Fd368add8 **)(self + 552);
    func_00335E38(self + 152, D_L01_001AE408 + v[0], D_L01_001AE40C + v[1], 0.0f, 0.0f);
    v = *(f32_Fd368add8 **)(self + 552);
    func_00335E38(self + 76, D_L01_001AE400 + v[0], D_L01_001AE404 + v[1], 0.0f, 0.0f);
    v = *(f32_Fd368add8 **)(self + 552);
    func_00335E38(self + 228, D_L01_001AE410 + v[0], D_L01_001AE414 + v[1], 0.0f, 0.0f);
    v = *(f32_Fd368add8 **)(self + 552);
    func_00335E38(self + 464, D_L01_001AE418 + v[0], D_L01_001AE41C + v[1], 0.0f, 0.0f);

    *(int *)func_00335E20(self + 304) = func_PAL_002A9FA0(0x60442D00, 0x70FFFEED, 20, 0, 0);
    func_PAL_00343838(self, arg1);
    func_PAL_003437C8(self);
    ref_L00_003418C0_00(self);
    return *(int *)(self + (*(int *)(self + 796) << 2) + 440);
}
