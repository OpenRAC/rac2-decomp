#include "include_asm.h"

#include "common.h"
extern void *func_002A9640(void *a0, s32 a1, s32 a2);
extern s32 func_002A77E0(s32 a0);
extern s32 func_002E5DA0(s32 a0, s32 a1, char *a2, s32 a3);
extern void func_PAL_002AD288(u8 *a0, void *a1, s32 a2, f32 f12, f32 f13);
extern s32 func_002E5CF8(s32 a0, s32 a1, char *a2);
extern void func_PAL_002B15D8(char *a0, s32 a1, f32 *a2, u8 a3, f32 f12, f32 f13, f32 f14,
                        f32 f15);
extern void func_0029F338(char *a0);
extern int func_002A77E0(int);
extern u8 *D_0018C0B0;
extern s32 D_L22_001B2128 __attribute__((sda));
extern u8 D_L22_001A7A78 __attribute__((sda));
extern s32 D_L22_001A903C __attribute__((sda));
extern s32 D_L22_0018B6A8 __attribute__((sda));
extern s32 func_2F36F0(s32);
extern void func_00282F20(void *, void *, f32);
extern f32 func_2F4AD0(f32, f32);
extern void func_L22_003FA1D0(s32, s32, s32);
extern u8 *D_L22_001AF314[] __attribute__((sda));
extern f32 D_L22_001B2A98 __attribute__((sda));
extern u8 *D_0018C0B0;
extern void func_0029F338(char *a0);

void func_PAL_L22_003FE960(s32 arg, s32 unused1, s32 unused2)
{
    char *a0 = (char *)arg;
    char *s1 = func_002A9640(a0, -1, 0);
    char buf[0x10];

    if (s1 == 0)
        return;
    func_002E5DA0(func_002A77E0(3) + 0xC, 0, a0, 0xE0B);
    func_PAL_002AD288((u8 *)a0, a0 + 0x10, -1, 2.0f, 13.0f);
    func_002E5CF8(0, 0, a0);
    func_00282F20(buf, s1 + 0x10, 0.3f);
    func_PAL_002B15D8(a0, 3, (f32 *)buf, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
    func_0029F338(a0);
}
