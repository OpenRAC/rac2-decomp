#include "include_asm.h"

#include "common.h"
extern void func_0029B3E0(s32 a0, s32 a1);
extern s32  func_32AB10(char *a0);
extern s32  func_360A80(s32 a0, s32 a1, char *a2);
extern void func_0029F338(void *a0);
extern s32  func_312898(s32 a0, s32 a1, void *a2);
extern u8  *D_L03_001B2A1C;
extern u8   D_001395BF;
extern void func_PAL_L00_002B9CD8(char *a0, char *a1, s32 a2, s32 a3);
extern void func_L01_00323310(s32 a0, s32 a1);
extern char D_00189E20_11[];
extern u8   D_001395C0;
extern u8   D_001A7AFA;
extern u8   D_001A7B32;
extern u8   D_001A7AFB;
extern u8   D_001A7B33;
extern u8   D_001A7AFC;
extern u8   D_001A7B34;
extern void func_L02_002B5F50(s32 a0);
extern void func_002A0430(s32 a0);
extern void func_002DF3F8(char *a0, char *a1);
extern void func_0029B3E0(s32 a0, s32 a1);
extern u8 *D_L03_001B2A1C_tbl[] __asm__("D_L03_001B2A1C") __attribute__((sda));

void func_PAL_L03_003D6298(char *a0)
{
    char *s0 = a0;
    char *s1 = *(char **)(s0 + 0x68);
    char *s2;
    void *p;

    func_L02_002B5F50(0);
    s2 = D_00189E20_11;
    *(u16 *)(s2 + 0x24FC) = 0;
    func_002A0430(*(u8 *)(s0 + 0xB0));
    D_001395C0 = 1;
    /* Resident bytes shared by all programs, written at their constant addresses
       (retail's lui $at,0x1A; sb form), as in 0033CB18.c. */
    *(u8 *)0x1A7BBA = 1;
    *(u8 *)0x1A7B83 = 1;
    *(u8 *)0x1A7BBB = 1;
    *(u8 *)0x1A7B84 = 1;
    *(u8 *)0x1A7BBC = 1;
    *(u8 *)0x1A7B82 = 1;
    func_PAL_L00_002B9CD8(s0 + 0x10, s0 + 0xF0, 0, 1);
    p = *(void **)(s1 + 0x2C);
    if (p != 0) {
        func_0029F338(p);
    }
    func_0029F338(D_L03_001B2A1C_tbl[0] + (*(s32 *)s1 << 8));
    *(s32 *)(s0 + 0x78) = 0x80468CDC;
    func_L01_00323310(*(s32 *)(s1 + 0x24), -1);
    func_002DF3F8(s2 + 0x80, s2 + 0x90);
    func_0029B3E0(0, -1);
}
