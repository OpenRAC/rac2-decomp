#include "include_asm.h"

#include "common.h"
extern int D_001B1594[] MACRO_ADDR;
extern int D_001B169C[] MACRO_ADDR;
extern int D_001A8BB0[] MACRO_ADDR;
extern float D_001B15A0[] MACRO_ADDR;
extern float D_001B15A4[] MACRO_ADDR;
extern char *ref_0027BD70_00[] MACRO_ADDR;
extern int D_001B1608[] MACRO_ADDR, D_001B160C[] MACRO_ADDR, D_001B1610[] MACRO_ADDR;
extern int D_001B1614[] MACRO_ADDR, D_001B1638[] MACRO_ADDR;
extern int D_001A8770[] SDATA(D_001A8770);
extern char D_0010FFC0[];
extern unsigned short D_0010FFB0 NOT_SDA;
extern int ref_0027BD70_01 NOT_SDA;
extern unsigned long ref_0027BD70_02 NOT_SDA;
extern float D_00189E20[];
extern float ref_0027BD70_03[];
extern char ref_0027BD70_04[], ref_0027BD70_05[];
extern int D_001A7344[] MACRO_ADDR;
extern int ref_0027BD70_06 NOT_SDA;
extern unsigned char D_001AD580[] MACRO_ADDR, D_001AD581[] MACRO_ADDR;
extern unsigned char D_001AD582[] MACRO_ADDR, D_001AD583[] MACRO_ADDR;
extern int D_001A86F4 __attribute__((sda)), D_001A8758 __attribute__((sda));
extern char D_00100AE0[];
extern int D_001A7B90[] MACRO_ADDR;
extern float D_001B1690[] MACRO_ADDR;
extern char ref_0027BD70_07[], ref_0027BD70_08[];
extern int D_001B170C[] MACRO_ADDR;
extern void func_00284F40(int);
extern void func_0027C540(int);
extern void func_002FCF90(int);
extern void func_002FC560(int, unsigned long);
extern void func_0027DCE8(void *);
extern void func_002FC410(void *, int);
extern void func_0011AEA0(int);
extern int func_002B49C8(int);
extern double func_001234F0(float);
extern int func_00115DA8(char *, char *, ...);
extern void func_0027F5B8(int, int, long, char *, int);
extern void func_0027DDC0(int, int, int, int);
extern int func_00283CF0(float);
extern void func_002FC070(void *);
extern float func_00283CE0(int);
extern void func_002FC3C0(int);
extern void func_002F0468(void *);
extern void func_002E2C38(void *);
extern void func_00279D18(void);
extern void func_0029FB20(void);
extern void func_0027A9A0(void);
extern void func_0027B858(void);
extern void func_00291268(void);
extern void func_002EF3B0(void);
extern void func_002F0EF8(void);
extern void func_002FC808(void);
extern void func_0027CEE0(void);
extern void func_0027C660(void);
extern void func_002FC7A8(void);
extern void func_002E11C0(void);
extern void func_0027CF58(void);
extern void func_0027BA68(void);
extern void func_002A03C0(void);
extern void func_0027CE18(void);
extern void func_002725E0(void);
extern void func_0027D160(void);
extern void func_002B9420(void);
extern void func_0027D020(void);
extern void func_002824B8(void);
extern void func_0027D0E8(void);
extern void func_PAL_002732B8(void);
extern void func_002852D8(void);
extern void func_0027D900(void);
extern void func_0029BF08(void);
extern void func_PAL_0028ECD8(void);
extern void func_PAL_0028A470(void);
extern void func_0027D5C0(void);
extern void func_0027DB68(void);
extern void func_002EF310(void);
extern void func_002F3E78(void);
extern void func_002F0E38(void);
extern void func_002E10B8(void);
extern void func_0029FEE0(void);
extern void func_00279FF0(void);

void func_PAL_0027C258(void)
{
    char text[64];
    float ticks;

    if (!ref_0027BD70_00[0] || *(short *)(ref_0027BD70_00[0] + 4) ||
        ((D_001B1594[0] ^ 1) & 1))
        func_00284F40(0);
    func_00279D18();
    func_0029FB20();
    func_0027A9A0();
    func_0027B858();
    D_001B169C[0] = -1;
    if (ref_0027BD70_00[0] && (D_001B1594[0] & 1))
        func_00291268();
    if (D_001B1594[0] & 2)
        func_002EF3B0();
    func_002FCF90(0x02010000);
    if (D_001B1594[0] & 4)
        func_002F0EF8();
    func_002FCF90(0x02020000);
    if (D_001B1610[0]) {
        func_002FC808();
        func_0027C540(1);
        func_0027CEE0();
        func_0027C660();
        func_002FC7A8();
    }
    if (D_001B1594[0] & 8)
        func_002E11C0();
    func_002FCF90(0x02040000);
    if (D_001A8770[0])
        func_0027DCE8(D_001A8770);
    if (D_001B1614[0]) {
        func_002FC808();
        func_0027C540(1);
        func_0027CF58();
        func_0027C660();
        func_002FC7A8();
    }
    if (D_001B1594[0] & 0x10) {
        if (D_001A8BB0[0] == 2)
            func_0027BA68();
        else
            func_002A03C0();
    }
    func_002FCF90(0x02080000);
    func_0027C540(0);
    if ((D_001B1594[0] & 0x20) && D_001B169C[0] != 6) {
        func_002FC410(D_0010FFC0, D_0010FFB0);
        D_001B169C[0] = 6;
    }
    if (D_001B1594[0] & 0x20) {
        func_002FC808();
        if (D_001B1608[0])
            func_0027CE18();
        func_002FC560(0x42, 0x8000000048UL);
        func_002725E0();
        func_002FC808();
        func_0027D160();
        func_002FC560(8, 5);
        func_002FC808();
        func_0011AEA0(0);
        func_002B9420();
        D_001B169C[0] = 9;
        if (D_001B160C[0]) {
            func_002FC808();
            func_0027D020();
        }
        func_002824B8();
        if (D_001B1638[0]) {
            func_002FC808();
            func_0027D0E8();
        }
        func_002FC560(0x42, 0x8000000044UL);
        func_PAL_002732B8();
    }
    func_002852D8();
    func_002FC808();
    if ((D_001B1594[0] & 0x180) && !func_002B49C8(3)) {
        func_002FC560(0x47, 0x33001);
        func_0027D900();
        if (D_001B1594[0] & 0x80) {
            func_0029BF08();
            func_PAL_0028ECD8();
            func_PAL_0028A470();
        }
    }
    if (D_001A8BB0[0] == 2)
        func_0027D5C0();
    if (ref_0027BD70_01 && (ref_0027BD70_02 & 5) == 5) {
        func_00115DA8(text, ref_0027BD70_04,
            func_001234F0(D_00189E20[32]),
            func_001234F0(D_00189E20[33]),
            func_001234F0(D_00189E20[34]));
        func_0027F5B8(24, D_001A7344[0] - 54, 0x80F0F0F0L, text, -1);
        func_00115DA8(text, ref_0027BD70_05,
            func_001234F0(ref_0027BD70_03[80]),
            func_001234F0(ref_0027BD70_03[81]),
            func_001234F0(ref_0027BD70_03[82]));
        func_0027F5B8(24, D_001A7344[0] - 40, 0x80F0F0F0L, text, -1);
    }
    func_0027C660();
    if (D_001B1594[0] & 0x40) {
        func_002FC560(0x42, 0x8000000044UL);
        if (ref_0027BD70_06)
            func_0027DDC0(D_001AD580[0], D_001AD581[0], D_001AD582[0], D_001AD583[0]);
        if (D_001B15A0[0] > 0.0f) {
            if (D_001B15A0[0] > 1.0f)
                D_001B15A0[0] = 1.0f;
            func_0027DDC0(0, 0, 0, func_00283CF0(D_001B15A0[0] * 128.0f));
        }
        if (D_001B15A4[0] > 0.0f) {
            if (D_001B15A4[0] > 1.0f)
                D_001B15A4[0] = 1.0f;
            func_0027DDC0(255, 255, 255, func_00283CF0(D_001B15A4[0] * 128.0f));
        }
        if (D_001A86F4 && D_001A8758)
            func_0027DB68();
    }
    func_002FC070(D_00100AE0);
    func_0011AEA0(0);
    ticks = func_00283CE0(*(volatile int *)0x10000800);
    D_001B1690[0] = ticks * (D_001A7B90[0] ? (1.0f / 11520.0f) : (1.0f / 9600.0f));
    func_002FC3C0(2);
    if (D_001B1594[0] & 2) {
        func_002F0468(ref_0027BD70_07);
        func_002EF310();
    }
    func_002FC3C0(4);
    if (D_001B1594[0] & 4) {
        func_002F3E78();
        func_002F0E38();
    }
    func_002FC3C0(8);
    if (D_001B1594[0] & 8) {
        func_002E2C38(ref_0027BD70_08);
        func_002E10B8();
    }
    func_002FC3C0(16);
    if (D_001B1594[0] & 16)
        func_0029FEE0();
    func_00279FF0();
    D_001B170C[0] = 0;
}
