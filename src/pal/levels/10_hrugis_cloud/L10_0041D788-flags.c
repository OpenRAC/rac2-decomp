#include "include_asm.h"

#include "common.h"
extern u8 *func_002ED688(u8 *);
extern f32 func_00283198(f32);
extern f32 func_00283180(f32);
extern void func_00282CC0(void *, void *, void *);
extern f32 func_00282E48(void *, void *);
extern f32 func_00282DB0(void *, void *);
extern f32 func_002831B0(f32);
extern f32 func_00282DF0(void *);
extern u8 D_L10_001B9680[];
extern u32 *func_0037BA88(u8 *arg0);
extern s32 func_003351C0(s32 mode);
extern s32 func_003737B8(s32 a, s32 b, u8 *c, s32 d);
extern void func_0037CCB0(u8 *arg0, s32 a1);
extern f32 func_00335320(void);
extern u8 *func_0037B670();
extern s32 func_003062A0(u8 *a0);
extern s32 func_0037D390(u8 *arg0, s32 a1, s32 a2, s32 a3);
extern s32 func_00335200(s32 a0, s32 a1);
extern f32 func_00309138(f32 f12);
extern f32 func_00309120(f32 f12);
extern void func_L10_004189D8(u8 *arg0);
extern s32 func_L05_0037B538(u8 *arg0, s32 a1, s32 a2, s32 a3);
extern s32 func_002E5DA0(s32 index, s32 value, u8 *object, s32 kind);
extern s32 func_0037D6E0(u8 *a0);
extern u8 *D_L10_0020B1E0[];
extern u8 *D_001B251C;
extern u8 D_L10_00265BA0[];
extern u8 D_L10_00188660[];
extern u8 D_L10_00221CD0[];
extern u8 D_00188660[];
extern s32 D_001B0F44 __attribute__((sda));
extern s32 D_001B0F48 __attribute__((sda));
extern f32 func_002A7878(f32, f32);
extern f32 func_002A7940(void);
extern void func_002AF000(void *, f32, f32, f32);
extern void func_00282CC0(void *, void *, void *);
extern u8 *D_001B2614 __attribute__((sda));
extern s32 func_L00_0042C818(void);
extern u8 *func_002ED688(u8 *arg0);
extern f32 func_002A7940(void);
extern f32 func_00283180(f32 f12);
extern s32 func_00283D38(s32 a0, s32 a1, f32 f12);
extern f32 func_00309B38(f32 f12, f32 f13);
extern u8 func_L10_00423780(void);
extern s32 func_00283D38(s32 a0, s32 a1, f32 f12);
extern s32 D_001A79F0[] __attribute__((sda));

void func_PAL_L10_0041D788(u8 *arg0) {
    u8 *s2 = *(u8 **)(arg0 + 0x68);
    u8 *table;
    f32 a, b, c;

    arg0[0x20] = 1;
    *(u16 *)(arg0 + 0x34) |= 0x100;
    *(s32 *)((u8 *)func_0037BA88(arg0) + 0x148) = 10;
    func_0037CCB0(arg0, 1);
    table = D_001B2614 + *(s32 *)D_L10_00221CD0 * 128;
    *(s32 *)(s2 + 0x26C) = -1;
    *(f32 *)(s2 + 0x180) = 10.0f;
    *(s32 *)(s2 + 0x268) = 0;
    *(f32 *)(arg0 + 0x2C) = 0.04f;
    a = func_002A7878(0.0f, *(f32 *)table);
    b = func_002A7940();
    c = func_002A7940();
    func_002AF000(arg0 + 0x10, a, b, c);
    func_00282CC0(arg0 + 0x10, table + 0x30, arg0 + 0x10);
}
