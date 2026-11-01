#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L03_003D5360);




#include "common.h"
extern void func_324168(s32 a0, s32 a1);
extern void func_30D710(s32 a0, s32 a1);
extern s32  func_32AB10(char *a0);
extern s32  func_360A80(s32 a0, s32 a1, char *a2);
extern s32  func_312898(s32 a0, s32 a1, void *a2);
extern void func_30D710(s32 a0, s32 a1);

void func_PAL_L03_003D6150(char *a0)
{
    char *s0 = *(char **)(a0 + 0x68);

    func_324168(*(s32 *)(s0 + 0x18), *(s32 *)(s0 + 0x1C));
    func_30D710(0, -1);
    *(u16 *)(*(s32 *)(s0 + 0x2C) + 0x34) |= 0x41;
    *(u16 *)(*(s32 *)(s0 + 0x2C) + 0x34) &= ~0x1000;
    *(s32 *)(*(s32 *)(s0 + 0x2C) + 0x98) = 0;
    *(u16 *)(*(s32 *)(s0 + 0x2C) + 0x96) = 0;
}

extern u8 *D_L03_001B2A1C[] __attribute__((sda));
extern f32  func_00283B98(f32 a0, f32 a1);
extern void func_PAL_L00_002B9CD8(char *a0, char *a1, s32 a2, s32 a3);
extern void func_PAL_L00_002B2958(s32 a0, s32 a1, char *a2);
extern void func_L00_0042A500(s32 a0);
extern void func_L01_00323310(s32 a0, s32 a1);
extern char D_00189E20[];
extern u8   D_001395BF;
typedef int TI128 __attribute__((mode(TI)));

/* The actor's per-frame update: the entry's flags are cleared, its record is copied
   and rotated by pi/3, and the resident block's float is turned the other way. */
void func_PAL_L03_003D61B8(char *a0)
{
    char *s1 = *(char **)(a0 + 0x68);
    char *s0 = D_L03_001B2A1C[0] + *(s32 *)s1 * 0x100;
    u16 v1 = *(u16 *)(s0 + 0x34);
    char *p = s0 + 0xF0;
    s32 v0 = *(s32 *)(s0 + 0x24);
    TI128 v2;
    f32 *f;
    char *base;

    v1 = (v1 & 0xFFBE) | 0x1000;
    *(u16 *)(s0 + 0x34) = v1;
    *(s32 *)(s0 + 0x98) = *(s32 *)(v0 + 0x10);
    qcopy(&v2, p);
    f = (f32 *)((char *)&v2 + 8);
    *f = func_00283B98(*f, -1.0471977f);
    func_PAL_L00_002B9CD8(s0 + 0x10, (char *)&v2, 0, 1);
    func_PAL_L00_002B2958(1, 0x3F, s0);
    base = D_00189E20;
    *(f32 *)(base + 0x98) = func_00283B98(*(f32 *)(base + 0x98), 1.0471977f);
    func_L00_0042A500(*(s32 *)(s1 + 0x28));
    func_L01_00323310(*(s32 *)(s1 + 0x20), -1);
    D_001395BF = 1;
}



