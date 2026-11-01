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

void func_PAL_L11_003D5F64(u8 *a0) {
    if (*(u8 *)(a0 + 0x31) == 0)
        return;
    *(f32 *)(a0 + 0xF4) = func_00283B98(*(f32 *)(a0 + 0xF4),
                                        0.12566373f);
    *(f32 *)(a0 + 0xF8) = func_00283B98(*(f32 *)(a0 + 0xF8),
                                        0.055850547f);
}
