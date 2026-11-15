#include "include_asm.h"
#include "names.h"

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
extern void func_L18_0043EDE8(u8 *);
extern void func_002A7750(u8 *, s32, s32);
extern f32 func_00283CE0(s32);
extern f32 func_00283180(f32);
extern s32 func_L01_0031BC68(s32, s32, f32);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern f32 func_00282DB0(void *, void *);
extern f32 func_00282C48(f32);
extern s32 func_L00_0031C998(s32, s32, f32);
extern void func_L18_0043EF40(u8 *);
extern void func_L00_002E6CF0(void *, void *);
extern void func_L18_0043EA90(u8 *);
extern void func_L18_0043E938(u8 *);
extern void func_L18_0043E9B0(u8 *);
extern void func_002AEE70(u8 *, f32 *, f32 *, f32, f32, f32);

/* Starts the banner object: on its first frame seeds the phase and copies its position, then
   every frame while it is live turns the frame counter into a phase over 60 frames, eases the
   rise and the two path samples from it, and queues the three updaters; finally hands the
   state's two coordinates to the shared mover. */
void func_L18_0043E760(u8 *obj) {
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
        *(f32 *)(state + 0x150) = RandomAngle();
        *(TI128 *)(state + 0x140) = *(TI128 *)(obj + 0x10);
        InitRibbonEmitters(obj);
        SetMobyState(obj, 1, -1);
    }
    if (obj[0x31] != 0) {
        period = 60;
        phase = IntToFloat(D_L18_001B2348 % period);
        rise = IntToFloat(60);
        phase = phase * 6.2831855f;
        phase = phase / rise;
        phase = phase - 3.1415927f;
        rise = FastSinOrCosA(phase);
        x = D_L18_001B1C28;
        y = D_L18_001B1C2C;
        *(f32 *)(state + 0x158) = rise * 0.5f + 0.5f;
        a = PulseColor(x, y, phase);
        b = PulseColor(D_L18_001B1C30, D_L18_001B1C34, phase);
        FastVecSub(buf, gCameraPosition_L18, obj + 0x10);
        vec_scale_to_length(buf, buf, 1.0f);
        rise = FloatAbs(FastVecDot(buf, obj + 0xC0));
        rise = rise * rise;
        *(f32 *)(state + 0x15C) = rise;
        *(s32 *)(obj + 0x78) = LerpIntegerFraction(b, a, rise);
        PickTableVectorsForBanner(obj);
        AddDrawCallbackToList1(DrawRibbonsAndBursts, obj);
        AddDrawCallbackToList1(PlaceObjectAtProbeHeight, obj);
        AddDrawCallbackToList1(EmitFadeLevelParticleBurst, obj);
    }
    UpdateWrappedAngleOffset(obj, (f32 *)(state + 0x150), (f32 *)(state + 0x154), D_L18_001B1C38, D_L18_001B1C3C * 0.00029088824f, *(f32 *)(state + 0x148));
}
