#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
extern u32 D_L03_0024A7B0;
extern u32 func_002B38B8(u8 *);
typedef float f32;
extern f32 D_L04_001B1C88 __attribute__((sda));
extern u8 *D_L03_001B2A1C __attribute__((sda));
extern s32 func_00277258(void *, s32, void *, f32);
s32 func_L03_00419BD8(u32 a0, u8 *first, u8 *second);
extern s32 func_L03_00419C58(u32, f32 *);
extern f32 func_00282E80(void *, f32 *);
extern f32 func_002A89A8(f32 *, s32, f32);
extern f32 func_00283B98(f32, f32);
extern f32 func_002A7878(f32, f32);
extern s32 func_002A77E0(s32);
extern void func_002A7A00(f32 *, f32, f32);
extern void func_00282CC0(void *, void *, void *);
extern void func_002C2210(void *, u32, u32, u32, s32, s32, s32, f32, f32, f32);
extern u32 D_0024A7B0;
extern s32 ref_L03_003E3750_00(u8 *, u32);
extern u8 *func_0029EFD0(s32);
extern s32 g_activeGadgetItem;
extern f32 D_001B9C14;
extern f32 D_001B2464 __attribute__((sda));
extern f32 func_00282C48(f32);
extern u32 func_L03_00329EF0(u8 *, u8 *, u8 *, s32);
extern s32 func_L02_0032E998(u8 *, u8 *, void *, u8 *, s32, s32 *, s32 *, float, float);
extern s32 func_L02_0032EDD8(u8 *, u8 *, s32, s32 *);
s32 func_L03_00419C00(u8 *, u8 *, u8 *);
extern s32 func_002A77E0(s32);
extern f32 D_L03_001B9BEC;

void func_PAL_L03_003D5148(u8 *a0, s32 a1, s32 a2) {
    f32 buf[3];
    f32 f20, f21;
    s32 s1, s2;

    s2 = a2;
    f20 = func_002A7878(0.25f, 1.0f);
    s1 = func_002A77E0(2);
    f21 = func_002A7878(3.0f, 7.0f) * (0.00040000002f);
    func_002A7A00(buf, 0.0f, 0.1f);
    func_00282CC0(buf, buf, a1);
    func_002C2210(buf, 0x21, 0x7F800000, 0, s1, s2, 0, f20 * 0.2f, f20, f21);
    func_002C2210(buf, 0x32, 0x7F7F7F7F, 1, -s1, s2, 0, f20 * 0.14f, f20 * 0.7f, f21);
}

