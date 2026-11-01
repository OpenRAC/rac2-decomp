#include "include_asm.h"

typedef unsigned char u8;
typedef signed int s32;
typedef float f32;
typedef int TI128 __attribute__((mode(TI)));
extern s32 D_L18_001B2348 __attribute__((sda));
extern s32 D_L18_001B1C28 __attribute__((sda));
extern s32 D_L18_001B1C2C __attribute__((sda));
extern s32 D_L18_001B1C30 __attribute__((sda));
extern s32 D_L18_001B1C34 __attribute__((sda));
extern f32 D_L18_001B1C38 __attribute__((sda));
extern f32 D_L18_001B1C3C __attribute__((sda));
extern char D_L18_001B97C0[];
extern f32 func_002A7940(void);
extern void func_PAL_L18_00444240(u8 *);
extern void func_002A7750(u8 *, s32, s32);
extern f32 func_00283CE0(s32);
extern f32 func_00283180(f32);
extern s32 func_L01_0031BC68(s32, s32, f32);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern f32 func_00282DB0(void *, void *);
extern f32 func_00282C48(f32);
extern s32 func_L00_0031C998(s32, s32, f32);
extern void func_PAL_L18_00444398(u8 *);
extern void func_L00_002E6CF0(void *, void *);
extern void func_L18_0043EA90(u8 *);
extern void func_L18_0043E938(u8 *);
extern void func_L18_0043E9B0(u8 *);
extern void func_002AEE70(u8 *, f32 *, f32 *, f32, f32, f32);

/* Starts the banner object: on its first frame seeds the phase and copies its position, then
   every frame while it is live turns the frame counter into a phase over 60 frames, eases the
   rise and the two path samples from it, and queues the three updaters; finally hands the
   state's two coordinates to the shared mover. */
void func_PAL_L18_00443BB8(u8 *obj) {
    u8 *state = *(u8 **)(obj + 0x68);
    f32 phase;
    f32 rise;
    s32 a;
    s32 b;
    s32 period;
    s32 x;
    s32 y;
    f32 buf[4];

    if (obj[0x20] == 0) {
        *(f32 *)(state + 0x150) = func_002A7940();
        *(TI128 *)(state + 0x140) = *(TI128 *)(obj + 0x10);
        func_PAL_L18_00444240(obj);
        func_002A7750(obj, 1, -1);
    }
    if (obj[0x31] != 0) {
        period = 50;
        phase = func_00283CE0(D_L18_001B2348 % period);
        rise = func_00283CE0(50);
        phase = phase * 6.2831855f;
        phase = phase / rise;
        phase = phase - 3.1415927f;
        rise = func_00283180(phase);
        x = D_L18_001B1C28;
        y = D_L18_001B1C2C;
        *(f32 *)(state + 0x158) = rise * 0.5f + 0.5f;
        a = func_L01_0031BC68(x, y, phase);
        b = func_L01_0031BC68(D_L18_001B1C30, D_L18_001B1C34, phase);
        func_00282CF0(buf, D_L18_001B97C0, obj + 0x10);
        func_00282F20(buf, buf, 1.0f);
        rise = func_00282C48(func_00282DB0(buf, obj + 0xC0));
        rise = rise * rise;
        *(f32 *)(state + 0x15C) = rise;
        *(s32 *)(obj + 0x78) = func_L00_0031C998(b, a, rise);
        func_PAL_L18_00444398(obj);
        func_L00_002E6CF0(func_L18_0043EA90, obj);
        func_L00_002E6CF0(func_L18_0043E938, obj);
        func_L00_002E6CF0(func_L18_0043E9B0, obj);
    }
    func_002AEE70(obj, (f32 *)(state + 0x150), (f32 *)(state + 0x154), D_L18_001B1C38, D_L18_001B1C3C * 0.0003490659f, *(f32 *)(state + 0x148));
}
