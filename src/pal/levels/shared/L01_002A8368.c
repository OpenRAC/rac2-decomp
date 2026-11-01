#include "include_asm.h"

extern char D_L01_00189E20[];
extern void func_002C7CA8(void);
extern void func_002B4070(void);
extern void func_002ADDC8(void);
extern void func_002C37C8(void);
extern void func_002AEB80(void);
extern void func_002B9878(void);
extern void func_002A7740(void);
extern void func_002AB1C8(void);
extern void func_002A9520(void);
extern void func_002A9310(void);
extern void func_002FDB00(void *a0);
extern void func_002AB328(void);
extern void func_0030F444(int a0);
extern char D_L01_00189E20[];

void func_PAL_L01_002A8368(void) {
    char *p;

    func_002C7CA8();
    func_002B4070();
    func_002ADDC8();
    func_002C37C8();
    func_002AEB80();
    p = D_L01_00189E20;
    if (*(unsigned char *)(p + 0x22B4) != 0) {
        func_002B9878();
        func_002A7740();
        if (*(unsigned char *)(p + 0x22B4) != 0) {
            func_002AB1C8();
            func_002A9520();
            func_002A9310();
            func_002FDB00(p + 0x80);
            func_002AB328();
            func_0030F444(*(int *)(p + 0x2290));
        }
    }
}

#include "common.h"
extern char D_00189E20[];
extern int D_L01_001A8F40 MACRO_ADDR;
extern char D_00189EA0[];
extern void func_PAL_L01_002A8368(void);
extern void func_PAL_L00_002D29E8(void);
extern void func_PAL_L00_002B3608(void);
extern void func_L01_002ADDC8(void);
extern void func_PAL_L01_002AE010(char *a0, char *a1, char *a2);
extern void func_PAL_L01_002C3A10(void);
extern void func_L00_002D2E68(void);
extern void func_L00_002D3068(void);
extern void func_L00_002AE0C8(void);
extern void func_PAL_L00_002B9C20(void);
extern void func_PAL_L00_002AC088(void);
extern void func_PAL_L00_002AB0C0(void);
extern void func_PAL_L00_002AB308(void);
extern void func_PAL_L00_002ABA88(void);
extern void func_PAL_L00_002AB830(void);
extern void func_PAL_L00_002A53A8(void);
extern void func_PAL_L00_002A56D0(void);
extern void func_PAL_L00_002B7688(void);
extern void func_L00_002A5368(void);
extern void func_L00_002A9460(void);
extern void func_L00_002AA178(int a0);
extern void func_PAL_L00_002B2018(void);
extern void func_PAL_L00_002B2230(void);
extern void func_PAL_L00_002B20F8(void);
extern void func_L00_002AFBC0(void);
extern int func_L00_002D6418(void);
extern void func_L00_002A7958(void);
extern void func_L00_002A7748(void);
extern void func_PAL_L00_002A6688(void);
extern void func_PAL_L00_002D6408(void);
extern void func_PAL_L00_002A62B0(void);
extern void func_PAL_L00_002D5680(void);
extern int func_L00_002A7000(void);
extern void func_L00_003080D0(void *a0);
extern void func_002A677C(int a0);
extern void func_L01_002A9298(void);
extern void func_L00_002A9760(void);

INCLUDE_ASM("asm/pal/levels", func_PAL_L01_002A8B30);






