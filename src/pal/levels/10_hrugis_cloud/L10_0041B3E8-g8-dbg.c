#include "include_asm.h"

#include "common.h"
typedef u32 VecQuad __attribute__((mode(TI), aligned(16)));
typedef union {
    VecQuad q;
    f32 f[4];
    s32 i[4];
} Vec4;
extern s32 func_L05_0037B538(u8 *,s32,s32,s32);
extern void func_L05_0037B948(u8 *,s32,f32);
extern s32 func_L00_00367720(void);
extern void func_PAL_L10_0041BD40(u8 *);
extern void func_L10_00417440(u8 *);
extern void func_L10_004174C8(u8 *);
extern void func_L05_00379E60(u8 *,void *,s32,void *);
extern u8 *func_L10_00417CE0(u8 *,s32);
extern s32 func_L10_0037CC20(void);
extern f32 func_00283CE0(s32);
extern u8 *func_002ED688(u8 *);
extern void func_PAL_L10_0041C2C8(u8 *);
extern f32 func_00283B98(f32,f32);
extern f32 func_00283198(f32);
extern f32 func_00283180(f32);
extern f32 func_00282E48(void *,void *);
extern s32 func_00283DB8(void *,f32);
extern void func_PAL_L10_0041C3C0(u8 *);
extern s32 func_00282948(void *);
extern f32 func_002A7878(f32,f32);
extern void func_PAL_L10_0041C508(u8 *,s32,f32);
extern void func_PAL_L10_0041C7A0(u8 *,s32,f32);
extern void func_PAL_L05_0042A240(void *,s32,f32,s32,s32,s32,s32,s32,s32,s32,s32,s32);
extern void func_0029F9F0(u8 *,void *);
extern void func_0029F338(u8 *);
extern void func_PAL_L10_0041BDF8(u8 *);
extern void func_L00_0031AA28(void *,void *,void *,void *,void *,f32);
extern void func_00282CF0(void *,void *,void *);
extern f32 func_00282DF0(void *);
extern void func_00282F20(void *,void *,f32);
extern void func_00282DD8(void *,void *,void *);
extern void func_0029FCC0(u8 *,s32,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_PAL_L10_003A0590(void *,void *,s32,s32,u32,u32,f32,s32,s32,f32,f32,f32);
extern void func_L05_0037AE40(u8 *);
extern u8 *D_001B251C MACRO_ADDR;
extern f32 D_L10_001B0F40 __attribute__((sda));
extern s32 D_L10_001B0F44 __attribute__((sda));
extern s32 D_L10_001B0F48 __attribute__((sda));
extern f32 D_L10_001B34D8 MACRO_ADDR;

void func_PAL_L10_0041B3E8(u8 *obj) {
    Vec4 up;
    Vec4 probe;
    Vec4 oldpos;
    Vec4 delta;
    Vec4 a, b;
    Vec4 c, d;
    Vec4 e, f;
    u8 *s = *(u8 **)(obj + 0x68);
    u8 *info, *child;
    s32 hit, i;
    f32 distance, t;
    u8 *childpos, *bank;

    up.q = 0;
    up.f[2] = 1.0f;
    hit = func_L05_0037B538(obj, 1, 1, 1);
    func_L05_0037B948(obj, 1, 32.0f);
    switch (obj[0x20]) {
    case 0:
        obj[0x30] = 0xFF;
        *(f32 *)(s + 0x2E0) = 1.0f;
        if (!func_L00_00367720())
            return;
        func_PAL_L10_0041BD40(obj);
        if (*(s32 *)(s + 0x2B4))
            func_L05_00379E60(obj, func_L10_00417440, 0, func_L10_004174C8);
        D_L10_001B0F44 = 0;
        D_L10_001B0F48 = 0;
        D_L10_001B34D8 = 1.0f / (D_L10_001B0F40 * 5e+01f);
        break;
    case 1:
        if (!*(u8 **)(s + 0x2C0))
            *(u8 **)(s + 0x2C0) = func_L10_00417CE0(obj, 1);
        if (!*(u8 **)(s + 0x2C4))
            *(u8 **)(s + 0x2C4) = func_L10_00417CE0(obj, 0);
        D_L10_001B0F40 = func_00283CE0(func_L10_0037CC20()) * 2.5f + 30.0f;
        if (D_L10_001B0F40 > 60.0f)
            D_L10_001B0F40 = 60.0f;
        info = func_002ED688(obj);
        if (*(s32 *)(s + 0x2B0) != -1) {
            *(s32 *)(info + 0x11C) = 1;
            bank = D_001B251C;
            *(u8 **)(info + 0x120) = bank + (*(s32 *)(s + 0x2B0) << 8);
        }
        func_PAL_L10_0041C2C8(obj);
        *(f32 *)(obj + 0xF8) = func_00283B98(*(f32 *)(obj + 0xF8), *(f32 *)(s + 0x2CC));
        *(f32 *)(s + 0x2BC) = func_00283B98(*(f32 *)(s + 0x2BC), *(f32 *)(s + 0x2D0));
        ((Vec4 *)(obj + 0x10))->f[2] = func_00283198(*(f32 *)(s + 0x2BC)) * 4.0f + *(f32 *)(s + 0x2B8);
        distance = func_00282E48(*(u8 **)(info + 0x120) + 0x10, obj + 0x10);
        qcopy(&probe, obj + 0x10);
        probe.f[3] = *(f32 *)(obj + 0xC) * 0.000976559997071f;
        if (func_00283DB8(&probe, 64.0f) != -1 && distance >= 24.0f)
            func_PAL_L10_0041C3C0(obj);
        func_00282948(s + 0x2E4);
        if (*(f32 *)(s + 0x180) < 25.0f)
            func_PAL_L10_0041C508(obj, 0, func_002A7878(2.0f, 3.0f));
        if (*(f32 *)(s + 0x180) < 15.0f)
            func_PAL_L10_0041C7A0(obj, 0, func_002A7878(1.8f, 2.8f));
        if (!hit)
            break;
        func_PAL_L05_0042A240(*(u8 **)(s + 0x2C0) + 0x10, 0, 1.0f, 50, 30, 30, 30, 40, 1, 1, 1, 0);
        func_PAL_L05_0042A240(*(u8 **)(s + 0x2C4) + 0x10, 0, 1.0f, 50, 30, 30, 30, 40, 1, 1, 0, 0);
        func_0029F9F0(*(u8 **)(s + 0x2C0), s + 0x2F0);
        func_0029F9F0(*(u8 **)(s + 0x2C0), s + 0x330);
        func_0029F9F0(*(u8 **)(s + 0x2C4), s + 0x370);
        func_0029F9F0(*(u8 **)(s + 0x2C4), s + 0x3B0);
        s[0x2F1] = 0;
        s[0x331] = 0;
        s[0x371] = 0;
        s[0x3B1] = 0;
        child = *(u8 **)(*(u8 **)(*(u8 **)(s + 0x2C0) + 0x68) + 0x18);
        if (child)
            func_0029F338(child);
        child = *(u8 **)(*(u8 **)(*(u8 **)(s + 0x2C4) + 0x68) + 0x18);
        if (child)
            func_0029F338(child);
        func_0029F338(*(u8 **)(s + 0x2C0));
        func_0029F338(*(u8 **)(s + 0x2C4));
        *(u8 **)(s + 0x2C0) = 0;
        *(u8 **)(s + 0x2C4) = 0;
        *(s32 *)(s + 0x2E0) = 0;
        obj[0x20] = 2;
        func_PAL_L10_0041BDF8(obj);
        break;
    case 2:
        func_PAL_L10_0041C2C8(obj);
        *(f32 *)(obj + 0xF8) = func_00283B98(*(f32 *)(obj + 0xF8), *(f32 *)(s + 0x2CC));
        *(f32 *)(s + 0x2BC) = func_00283B98(*(f32 *)(s + 0x2BC), *(f32 *)(s + 0x2D0));
        ((Vec4 *)(obj + 0x10))->f[2] = func_00283198(*(f32 *)(s + 0x2BC)) * 4.0f + *(f32 *)(s + 0x2B8);
        if (*(u8 **)(s + 0x2C8)) {
            info = func_002ED688(*(u8 **)(s + 0x2C8));
            if (!*(s32 *)(info + 0x110)) {
                *(s32 *)(s + 0x2DC) = 500;
                *(u8 **)(s + 0x2C8) = 0;
                break;
            }
            *(f32 *)(s + 0x2D4) += *(f32 *)(s + 0x2D8);
            if (*(f32 *)(s + 0x2D4) > 3.1415927f) {
                t = D_L10_001B34D8;
                *(f32 *)(s + 0x2D4) = 3.1415927f;
                *(f32 *)(s + 0x2E0) += t;
            }
            childpos = *(u8 **)(s + 0x2C8) + 0x10;
            qcopy(&oldpos, childpos);
            t = (func_00283180(*(f32 *)(s + 0x2D4) - 3.1415927f) + 1.0f) * 0.5f;
            func_L00_0031AA28(childpos, s + 0x260, s + 0x270, s + 0x280, s + 0x290, t);
            func_00282CF0(&delta, *(u8 **)(s + 0x2C8) + 0x10, &oldpos);
            if (func_00282DF0(&delta) >= 0.0001f) {
                func_00282F20(*(u8 **)(s + 0x2C8) + 0xC0, &delta, 1.0f);
                ((Vec4 *)(*(u8 **)(s + 0x2C8) + 0xC0))->i[3] = 0;
                func_00282DD8(*(u8 **)(s + 0x2C8) + 0xD0, *(u8 **)(s + 0x2C8) + 0xC0, &up);
                ((Vec4 *)(*(u8 **)(s + 0x2C8) + 0xD0))->i[3] = 0;
                func_00282F20(*(u8 **)(s + 0x2C8) + 0xD0, *(u8 **)(s + 0x2C8) + 0xD0, 1.0f);
                func_00282DD8(*(u8 **)(s + 0x2C8) + 0xE0, *(u8 **)(s + 0x2C8) + 0xD0, *(u8 **)(s + 0x2C8) + 0xC0);
                ((Vec4 *)(*(u8 **)(s + 0x2C8) + 0xE0))->i[3] = 0;
            } else {
                func_0029FCC0(*(u8 **)(s + 0x2C8), 0, &a);
                func_0029FCC0(*(u8 **)(s + 0x2C8), 1, &b);
                func_0029FCC0(*(u8 **)(s + 0x2C8), 2, &c);
                func_0029FCC0(*(u8 **)(s + 0x2C8), 3, &d);
                func_00282CF0(&e, &c, &a);
                func_00282CF0(&f, &d, &b);
                func_00282F20(&e, &e, 4.0f);
                func_00282F20(&f, &f, 4.0f);
                func_00282CC0(&e, &c, &e);
                func_00282CC0(&f, &d, &f);
                func_PAL_L10_003A0590(&c, &e, 2, 0, 0x7F7F7F, 0xFF1010, 0.5f, 70, 70, 0.2f, 0.402000010014f, 1.1222499609f);
                func_PAL_L10_003A0590(&d, &f, 2, 0, 0x7F7F7F, 0xFF1010, 0.5f, 70, 70, 0.2f, 0.402000010014f, 1.1222499609f);
            }
            for (i = 0; i < 16; i++) {
                func_L00_0031AA28(&a, s + 0x260, s + 0x270, s + 0x280, s + 0x290, func_00283CE0(i) * 0.0625f);
                func_L00_0031AA28(&b, s + 0x260, s + 0x270, s + 0x280, s + 0x290, func_00283CE0(i + 1) * 0.0625f);
            }
            if (*(f32 *)(s + 0x2E0) >= 1.0f) {
                *(s32 *)(s + 0x2DC) = 0;
                obj[0x20] = 1;
                func_L05_0037AE40(*(u8 **)(s + 0x2C8));
                *(f32 *)(s + 0x2E0) = 1.0f;
                *(u8 **)(s + 0x2C8) = 0;
                info = func_002ED688(obj);
                ((Vec4 *)(s + 0x180))->f[0] = (f32)*(s32 *)(info + 0x148);
                D_L10_001B0F48 = 1;
            }
        } else if (func_00282948(s + 0x2DC)) {
            func_PAL_L10_0041BDF8(obj);
        }
        if (*(f32 *)(s + 0x2E0) <= 0.5f)
            func_PAL_L10_0041C7A0(obj, 0, func_002A7878(1.9f, 2.25f) - *(f32 *)(s + 0x2E0));
        if (*(f32 *)(s + 0x2E0) <= 0.75f)
            func_PAL_L10_0041C508(obj, 0, func_002A7878(2.0f, 3.0f) - *(f32 *)(s + 0x2E0));
        break;
    }
    func_PAL_L10_0041C2C8(obj);
}
