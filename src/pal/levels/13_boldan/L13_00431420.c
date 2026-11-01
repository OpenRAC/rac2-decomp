#include "include_asm.h"

typedef float f32;
typedef unsigned char u8;
typedef int s32;
typedef unsigned int u32;
typedef unsigned short u16;
extern f32 func_2F9748(f32, f32);
extern s32 func_32A4D0(u8 *, s32);
extern s32 func_31A718(u8 *);
extern s32 func_3248E0(u8 *, s32, s32);
extern s32 func_2AF870(u8 *);
extern f32 D_L13_001B2568 __attribute__((sda));
extern u32 D_L13_001B291C[] __attribute__((sda));
extern u8 D_L13_001B1E60[];
extern u8 D_0019B2E8[];
extern s32 D_001A79F0 __attribute__((sda));
extern u8 *D_L13_001B2A0C __attribute__((sda));
extern u8 *D_L13_001B291C_2;
extern u8 D_00189E20[];
extern int D_001A79F0 __attribute__((sda));
extern f32 func_00282E80(void *, void *);
extern f32 func_00282E48(void *, void *);
extern u8 D_0012EA0[];
extern u8 D_00188660[];
extern u8 D_L13_001B1C20[];
extern u8 D_L13_001B1C48[];
extern u16 *D_L13_001FB420[];
extern s32 D_L13_001B2938 __attribute__((sda));
extern s32 func_002ACBC8(u8 *, s32);
extern s32 func_002B3868(u8 *);
extern s32 func_L00_0035F5A0(s32, s32, u8 *);
extern s32 func_00282948(u8 *);
extern s32 func_002ACBC8(u8 *, s32);
extern u8 D_001395B8[];
extern void func_002E5CF8(s32, s32, u8 *);
extern void func_002AA548(f32 *, f32 *, f32, f32, f32, f32);
extern s32 func_2AF870(u8 *);
extern u8 D_L13_001B1E60[];

void func_PAL_L13_00431420(u8 *a0) {
    u8 *ptr = *(u8 **)(a0 + 0x68);
    if (a0[0x20] == 0) {
        *(u16 *)(a0 + 0x34) |= 0x800;
        *(f32 *)(ptr + 0x8) = *(f32 *)(a0 + 0x18);
        *(f32 *)(ptr + 0x4) = *(f32 *)(a0 + 0x18) - 6.0f;
        a0[0x20] = 1;
    }
    if (a0[0x20] == 1) {
        u8 v = *((u8 *)D_L13_001B291C[0] + (*(u32 *)ptr << 8) + 0x20);
        if (v == 2) {
            func_002E5CF8(0, 0, a0);
            a0[0x20] = v;
        }
    }
    if (a0[0x20] == 2) {
        func_002AA548((f32 *)(a0 + 0x18), (f32 *)(ptr + 0xC), *(f32 *)(ptr + 0x4),
                      0.0024f, 0.0024f, 0.24000001f);
    }
}


extern s32 func_0026FEB8(u8 *);
extern s32 func_0026FEB8(u8 *);

void func_PAL_L13_00431518(u8 *a0) {
    u8 *ptr = *(u8 **)(a0 + 0x68);
    if (a0[0x20] == 0) {
        *(u16 *)(a0 + 0x34) |= 0x800;
        *(f32 *)(ptr + 0x8) = *(f32 *)(a0 + 0x18);
        *(f32 *)(ptr + 0x4) = *(f32 *)(a0 + 0x18) - 6.0f;
        a0[0x20] = 1;
    }
    if (a0[0x20] == 1) {
        u8 v = *((u8 *)D_L13_001B291C[0] + (*(u32 *)ptr << 8) + 0x20);
        if (v == 2) {
            a0[0x20] = v;
            func_0026FEB8(D_L13_001B1E60);
        }
    }
    if (a0[0x20] == 2) {
        func_002AA548((f32 *)(a0 + 0x18), (f32 *)(ptr + 0xC), *(f32 *)(ptr + 0x4),
                    0.0024f, 0.0024f, 0.24000001f);
    }
}

