#include "include_asm.h"



#include "common.h"
extern u8 *func_002A9640(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_002E59B0(u8 *arg0, s32 arg1);
extern s32 func_002E5CF8(s32 arg0, s32 arg1, u8 *arg2);
extern s32 func_00283CF0(f32 arg0);
extern void func_002A93B0(u8 *arg0);
extern f32 func_00282E48(u8 *arg0, u8 *arg1);
extern void func_L11_003F1D18();
extern void func_L11_003F1DB0(u8 *arg0);
extern void func_L11_003F1F48(u8 *arg0);
extern void func_L11_003F2A30(u8 *arg0);
extern void func_L11_003F2C28(u8 *arg0);
extern s32 func_L11_003F2E00(u8 *arg0);
extern u8 D_L11_00188660[];
extern u8 D_L11_001BA8C0[];
extern s32 D_L11_001A8FF0 __attribute__((sda));
extern s32 D_L11_001A8FF4 __attribute__((sda));
extern f32 func_002B04E0(u8 *a0, f32 *a1, s32 a2);
extern f32 func_00282E80(u8 *a0, u8 *a1);
extern u8 D_L11_00189EA0[];

void func_PAL_L11_003F5F18(u8 *arg0) {
    u8 *s0 = arg0;
    if (*(u8 *)(s0 + 0x20) == 0) {
        func_L11_003F1D18();
    } else {
        if (func_L11_003F2E00(s0) != 0)
            return;
        if (*(u8 *)(s0 + 0x31) != 0
            && func_00282E48(s0 + 0x10, D_L11_001BA8C0) < 48.0f) {
            func_002A93B0(s0);
            *(u8 *)(s0 + 0x6F) = 0x2D;
        }
        func_L11_003F1DB0(s0);
        func_L11_003F1F48(s0);
        func_L11_003F2A30(s0);
        func_L11_003F2C28(s0);
    }
}

