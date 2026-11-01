#include "include_asm.h"


typedef unsigned char u8;
extern u8 D_001C97C0[];
extern u8 *D_L18_001B281C[] __attribute__((sda));
extern u8 D_0019B2E8[];
extern void func_L18_004302B0(u8 *a0);
extern void func_L18_004308F0(u8 *a0);
extern void func_L18_00430E58(u8 *a0);
extern void func_L18_00432070(u8 *a0);
extern void func_L18_00432310(u8 *a0);
extern u8 *D_L18_001B281C[] __attribute__((sda));
extern u8 D_00190000[];

void func_PAL_L18_00435260(u8 *a0) {
    u8 v = *(u8 *)(a0 + 0x20);
    if (v == 0) {
        func_L18_004302B0(a0);
        return;
    }
    if (v == 1) return;
    func_L18_004308F0(a0);
    func_L18_00430E58(a0);
    func_L18_00432070(a0);
    func_L18_00432310(a0);
}



INCLUDE_ASM("asm/pal/levels", func_PAL_L18_00435E70);


