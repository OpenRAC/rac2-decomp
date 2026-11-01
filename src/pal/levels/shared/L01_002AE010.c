#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L01_002AE010);


#include "common.h"
extern void func_PAL_L00_002AF6C0(void);
extern void func_PAL_L00_002B1E88(void);
extern void func_L00_002D2E68(void);
extern void func_L00_002A6708(void);
extern void func_L00_002A53B8(void);
extern void func_L00_002D24B8(void);
extern void func_002A677C(int);
extern char D_00189E20[];
extern void func_PAL_L00_002AF6C0(void);
extern void func_PAL_L00_002B1E88(void);
extern void func_L00_00322EC8(char *a0);
extern void func_L00_002D2E68(void);
extern void func_L00_002A6708(void);
extern void func_L00_002A53B8(void);
extern void func_L00_002D24B8(void);
extern void func_002A677C(int a0);
extern void func_PAL_L01_002BEC60(int a0, int a1);
extern void func_PAL_L01_002B3C40(void);
extern char D_00189E20[];

void func_PAL_L01_002B3370(int a0, int a1, int a2) {
    char *s0 = D_00189E20;

    func_PAL_L00_002AF6C0();
    s0[0x22B6] = 1;
    func_PAL_L00_002B1E88();
    *(int *)(s0 + 0x2290) = *(int *)(s0 + 0xC18);
    func_L00_00322EC8(s0 + 0x18E0);
    func_L00_00322EC8(s0 + 0x1A30);
    *(int *)(*(int *)(s0 + 0x2290) + 0x9C) = -1;
    if (a0 != 4 || *(unsigned char *)(s0 + 0x22B4) != a0)
        func_L00_002D2E68();
    func_L00_002A6708();
    func_L00_002A53B8();
    {
        char *s1 = D_00189E20;

        *(unsigned char *)(s1 + 0x22B4) = a0;
        *(int *)(s1 + 0xC14) = a2;
        *(int *)(s1 + 0x2290) = a2;
    }
    func_PAL_L01_002B3C40();
    {
        char *s2 = D_00189E20;

        *(float *)(s2 + 0x250) = *(float *)(s2 + 0x258);
        *(float *)(s2 + 0x254) = *(float *)(s2 + 0x25C);
        *(unsigned short *)(*(int *)(s2 + 0x2290) + 0x34) |= 6;
        *(float *)(s2 + 0xC20) = 1.0f;
        *(float *)(s2 + 0xC24) = 1.0f;
        func_L00_002D24B8();
        func_002A677C(*(int *)(s2 + 0x2290));
        *(unsigned short *)(s2 + 0x24F2) = a1;
    }
    func_PAL_L01_002BEC60(a1, 2);
}

