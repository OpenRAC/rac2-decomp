#include "include_asm.h"

#include "common.h"
extern f32  D_L03_001B0340 __attribute__((sda));
extern void func_002A7750(char *a0, s32 a1, s32 a2);
extern s32  func_002A7820(s32 a0, s32 a1);
extern s32  func_002A77E0(s32 a0);
extern f32  func_00283B98(f32 a0, f32 a1);
extern void func_002A7750(char *a0, s32 a1, s32 a2);
extern f32  func_2EF670(f32 a0, f32 a1);
extern f32  func_2EF110(f32 *a0);
extern f32 D_L03_001B0350[] SDATA(D_L03_001B0350);
extern f32 D_L03_001B0648 __attribute__((sda));
extern u32 D_L03_001B3458;
extern s32  func_002B38B8(char *a0);
extern s32  func_002E5CF8(s32 a0, s32 a1, char *a2);
extern u8  *D_L03_001B2A1C;
extern u8   D_00188660[];
extern s32  D_L03_001B0438 __attribute__((sda));
extern f32  D_L03_001B043C __attribute__((sda));
extern s32  D_L03_001B0674 __attribute__((sda));
extern void func_002A7750(char *a0, s32 a1, s32 a2);
extern s32  func_002A8AF0(char *a0, void *a1, u32 a2);
extern f32  func_00282DF0(f32 *a0);
extern f32 func_002AAA00(char *a0, f32 *a1, f32 a3, f32 a4, f32 a5, f32 a6, s32 a2);

void func_PAL_L03_003CEA00(char *a0)
{
    if (*(u8 *)(a0 + 0x31) == 0) {
        return;
    }
    switch (*(u8 *)(a0 + 0x20)) {
    case 0:
        *(u8 *)(a0 + 0xBC) = (u8)func_002A7820(5, 10);
        if (func_002A77E0(2) != 0) {
            *(u8 *)(a0 + 0xBC) += 15;
        }
        func_002A7750(a0, 1, -1);
        break;
    case 1:
        *(f32 *)(a0 + 0xF8) = func_00283B98(*(f32 *)(a0 + 0xF8),
            D_L03_001B0340 * 0.0003490659f * (f32)(*(u8 *)(a0 + 0xBC) - 15));
        break;
    }
}
