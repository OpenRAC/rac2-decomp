/* func_PAL_L01_002A8B30, the PAL copy of func_L01_002A8C48: the same C, where func_L01_002A84D8
   becomes func_PAL_L01_002A8368; func_L00_002B36E0 becomes func_PAL_L00_002B3608;
   func_L01_002AE128 becomes func_PAL_L01_002AE010; func_L01_002C37C8 becomes
   func_PAL_L01_002C3A10; func_L00_002AC1A0 becomes func_PAL_L00_002AC088; func_L00_002AB1D8
   becomes func_PAL_L00_002AB0C0; func_L00_002AB420 becomes func_PAL_L00_002AB308;
   func_L00_002ABBA0 becomes func_PAL_L00_002ABA88; func_L00_002AB948 becomes
   func_PAL_L00_002AB830; func_L00_002A5518 becomes func_PAL_L00_002A53A8; func_L00_002A5840
   becomes func_PAL_L00_002A56D0; func_L00_002B7718 becomes func_PAL_L00_002B7688;
   func_L00_002B2120 becomes func_PAL_L00_002B2018; func_L00_002B2318 becomes
   func_PAL_L00_002B2230; func_L00_002B2200 becomes func_PAL_L00_002B20F8; func_L00_002A67F8
   becomes func_PAL_L00_002A6688; func_L00_002D5EB8 becomes func_PAL_L00_002D6408;
   func_L00_002A6420 becomes func_PAL_L00_002A62B0; func_L00_002D5158 becomes
   func_PAL_L00_002D5680. */

#include "common.h"

extern char D_00189E20[];
extern int D_L01_001A8F40 MACRO_ADDR;
extern char D_00189EA0[];

extern void func_PAL_L01_002A8368(void);
extern void func_2C7CA8(void);
extern void func_PAL_L00_002B3608(void);
extern void func_L01_002ADDC8(void);
extern void func_PAL_L01_002AE010(char *a0, char *a1, char *a2);
extern void func_PAL_L01_002C3A10(void);
extern void func_2C8628(void);
extern void func_L00_002D3068(void);
extern void func_2AEB80(void);
extern void func_2B9878(void);
extern void func_PAL_L00_002AC088(void);
extern void func_PAL_L00_002AB0C0(void);
extern void func_PAL_L00_002AB308(void);
extern void func_PAL_L00_002ABA88(void);
extern void func_PAL_L00_002AB830(void);
extern void func_PAL_L00_002A53A8(void);
extern void func_PAL_L00_002A56D0(void);
extern void func_PAL_L00_002B7688(void);
extern void func_2A7740(void);
extern void func_2AB028(void);
extern void func_L00_002AA178(int a0);
extern void func_PAL_L00_002B2018(void);
extern void func_PAL_L00_002B2230(void);
extern void func_PAL_L00_002B20F8(void);
extern void func_L00_002AFBC0(void);
extern int func_L00_002D6418(void);
extern void func_2A9520(void);
extern void func_2A9310(void);
extern void func_PAL_L00_002A6688(void);
extern void func_PAL_L00_002D6408(void);
extern void func_PAL_L00_002A62B0(void);
extern void func_PAL_L00_002D5680(void);
extern int func_L00_002A7000(void);
extern void func_L00_003080D0(void *a0);
extern void func_30F444(int a0);
extern void func_L01_002A9298(void);
extern void func_2AB328(void);

void func_PAL_L01_002A8B30(void) {
    char *p;

    p = D_00189E20;
    *(short *)(p + 0x2162) = 0;
    *(short *)(p + 0x2160) = 0;
    if (*(unsigned char *)(p + 0x22B4) != 0) {
        func_PAL_L01_002A8368();
        return;
    }
    func_2C7CA8();
    func_PAL_L00_002B3608();
    func_L01_002ADDC8();
    func_PAL_L01_002AE010(p + 0x80, p + 0x90, p + 0x550);
    func_PAL_L01_002C3A10();
    if (D_L01_001A8F40 == 2 || D_L01_001A8F40 == 6) {
        if (*(unsigned char *)(p + 0x22B5) != 0)
            func_2C8628();
        else
            func_L00_002D3068();
        return;
    }
    func_2AEB80();
    if (*(unsigned char *)(p + 0x22B4) != 0)
        return;
    func_2B9878();
    func_PAL_L00_002AC088();
    func_PAL_L00_002AB0C0();
    func_PAL_L00_002AB308();
    func_PAL_L00_002ABA88();
    func_PAL_L00_002AB830();
    func_PAL_L00_002A53A8();
    func_PAL_L00_002A56D0();
    func_PAL_L00_002B7688();
    func_2A7740();
    func_2AB028();
    func_L00_002AA178(0);
    func_PAL_L00_002B2018();
    func_PAL_L00_002B2230();
    func_PAL_L00_002B20F8();
    func_L00_002AFBC0();
    if (*(unsigned char *)(p + 0x22B5) != 0 || func_L00_002D6418() != 0)
        func_2C8628();
    else
        func_L00_002D3068();
    func_2A9520();
    func_2A9310();
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
        func_30F444(*(int *)(q + 0x2290));
    }
    func_L01_002A9298();
    func_2AB328();
}
