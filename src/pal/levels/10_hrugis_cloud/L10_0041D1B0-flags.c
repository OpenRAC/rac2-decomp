#include "include_asm.h"

#include "common.h"
extern u8 *D_001B251C __attribute__((sda));
extern u8 D_L10_00188660[];
extern u8 *func_L00_00367720(u8 *arg0);
extern void func_PAL_L10_0041D788(u8 *arg0);
extern void func_00282C88(u8 *a0);
extern void func_L05_00379E60(u8 *arg0, s32 a1, s32 a2, s32 a3);
extern u8 *func_002ED688(u8 *arg0);
extern void func_PAL_L05_0037E8E0(u8 *a0);
extern s32 func_L05_0037B538(u8 *arg0, s32 a1, s32 a2, s32 a3);
extern void func_002E59F8(s32 a0);
extern s32 func_002E5DA0(s32 a, s32 b, u8 *c, s32 d);
extern void func_L05_0037B948(u8 *a0, s32 a1, f32 f12);
extern void func_PAL_L10_0041D888(u8 *arg0);
extern s32 func_L05_0037B888(u8 *a0);
extern void func_PAL_L05_0037DE20(u8 *a0);
extern void func_00282948(u8 *a0);
extern void func_PAL_L10_0041D950(u8 *arg0);
extern void func_L10_00418968(u8 *arg0);

void func_PAL_L10_0041D518(u8 *arg0) {
    u8 *s2 = *(u8 **)(arg0 + 0x68);
    u8 *s3;
    u8 *p;
    s32 id;
    s32 tmp[4];
    s32 one;

    if (arg0[0x20] == 0) {
        arg0[0x30] = 0xFF;
        if (func_L00_00367720(arg0) == 0)
            return;
        func_PAL_L10_0041D788(arg0);
        func_00282C88((u8 *)tmp);
        if (*(s32 *)(s2 + 0x264) != 0)
            func_L05_00379E60(arg0, (s32)func_L10_00418968, 0, 0);
        return;
    }
    s3 = func_002ED688(arg0);
    if (*(s32 *)(s3 + 0x110) == 0)
        return;
    func_PAL_L05_0037E8E0(arg0);
    one = 1;
    if (func_L05_0037B538(arg0, 0, 0, 0) == one) {
        id = *(s32 *)(s2 + 0x26C);
        if (id != -1) {
            p = D_L10_00188660 + id * 0x70;
            if (*(u8 **)(p + 0x88) == arg0 && p[0x74] != 0)
                func_002E59F8(id);
        }
        *(s32 *)(s2 + 0x26C) = -1;
        func_002E5DA0(2, 0, arg0, 0xF8E);
    }
    func_L05_0037B948(arg0, 0, 176.0f);
    if (*(s32 *)(s3 + 0x110) == 1) {
        if (*(s32 *)(s2 + 0x260) != -1) {
            *(s32 *)(s3 + 0x11C) = *(s32 *)(s3 + 0x110);
            *(u8 **)(s3 + 0x120) = D_001B251C + (*(s32 *)(s2 + 0x260) << 8);
        }
        if (*(s32 *)(s3 + 0x104) != 0)
            func_PAL_L10_0041D888(arg0);
        if (func_L05_0037B888(arg0) != 0)
            func_PAL_L05_0037DE20(arg0);
        func_00282948(s2 + 0x268);
        func_PAL_L10_0041D950(arg0);
    }
    p = D_L10_00188660 + *(s32 *)(s2 + 0x26C) * 0x70;
    if (*(u8 **)(p + 0x88) != arg0 || p[0x74] == 0)
        *(s32 *)(s2 + 0x26C) = func_002E5DA0(0, 6, arg0, 0xF8E);
}
