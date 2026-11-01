#include "include_asm.h"

#include "common.h"
extern char D_00189E20[];
extern int D_L03_001A8F00 MACRO_ADDR;
extern char D_00189EA0[];
extern void ref_L03_002AD540_00(void);
extern void func_PAL_L00_002D29E8(void);
extern void ref_L03_002AD540_01(void);
extern void ref_L03_002AD540_02(void);
extern void ref_L03_002AD540_03(char *a0, char *a1, char *a2);
extern void ref_L03_002AD540_04(void);
extern void ref_L03_002AD540_05(void);
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
extern void ref_L03_002AD540_06(void);
extern void func_L00_002A9760(void);

void func_PAL_L03_002AD428(void) {
    char *p;

    p = D_00189E20;
    *(short *)(p + 0x2162) = 0;
    *(short *)(p + 0x2160) = 0;
    if (*(unsigned char *)(p + 0x22B4) != 0) {
        ref_L03_002AD540_00();
        return;
    }
    func_PAL_L00_002D29E8();
    ref_L03_002AD540_01();
    ref_L03_002AD540_02();
    ref_L03_002AD540_03(p + 0x80, p + 0x90, p + 0x550);
    ref_L03_002AD540_04();
    ref_L03_002AD540_05();
    if (D_L03_001A8F00 == 2 || D_L03_001A8F00 == 6) {
        if (*(unsigned char *)(p + 0x22B5) != 0)
            func_L00_002D2E68();
        else
            func_L00_002D3068();
        return;
    }
    func_L00_002AE0C8();
    if (*(unsigned char *)(p + 0x22B4) != 0)
        return;
    func_PAL_L00_002B9C20();
    func_PAL_L00_002AC088();
    func_PAL_L00_002AB0C0();
    func_PAL_L00_002AB308();
    func_PAL_L00_002ABA88();
    func_PAL_L00_002AB830();
    func_PAL_L00_002A53A8();
    func_PAL_L00_002A56D0();
    func_PAL_L00_002B7688();
    func_L00_002A5368();
    func_L00_002A9460();
    func_L00_002AA178(0);
    func_PAL_L00_002B2018();
    func_PAL_L00_002B2230();
    func_PAL_L00_002B20F8();
    func_L00_002AFBC0();
    if (*(unsigned char *)(p + 0x22B5) != 0 || func_L00_002D6418() != 0)
        func_L00_002D2E68();
    else
        func_L00_002D3068();
    func_L00_002A7958();
    func_L00_002A7748();
    func_PAL_L00_002A6688();
    func_PAL_L00_002D6408();
    func_PAL_L00_002A62B0();
    func_PAL_L00_002D5680();
    {
        char *q = D_00189E20;
        if ((*(int *)(q + 0x229C) != 0x16 && *(int *)(q + 0x229C) != 0x1F
             && *(int *)(q + 0x2294) != 0x31) || func_L00_002A7000() != 0)
            func_L00_003080D0(D_00189EA0);
    }
    {
        char *q = D_00189E20;
        func_002A677C(*(int *)(q + 0x2290));
    }
    ref_L03_002AD540_06();
    func_L00_002A9760();
}

