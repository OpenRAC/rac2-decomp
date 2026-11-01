#include "include_asm.h"

#include "common.h"
extern void func_002A7750(void *, int, int);
extern int func_002A9640(void *, int, int);
extern void func_PAL_L00_0032C328(void *, void *, void *, void *, int, int, int, int,
                               int, int, int);
extern void func_L01_0031A278(char *, float *, float, float, float);
extern float func_00283B98(float, float);
extern int func_002E5CF8(int, int, char *);
extern u8 D_00188660[];
extern void *D_L06_002E1DA0[];
extern void func_PAL_L06_00401AA0(int);
extern void func_PAL_L06_00401D78(char *);
extern int func_L00_00329520(void *, int);
extern int func_00282948(void *);
extern int func_002A77E0(int);
extern void func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_002833F0(void *, void *);
extern void func_PAL_L01_002E2968(float *, float *, int, int, int, float, float, float);
extern int D_L06_001B2838 __attribute__((sda));
extern char *D_L06_001B281C_abs[3] __attribute__((sda));
extern unsigned short *D_L06_001FB3A0[];
extern char D_L06_001B9840[];
extern int D_L06_001AFC80 __attribute__((sda));
extern int D_L06_001AFC70 __attribute__((sda));
extern int D_L06_001AFC68 __attribute__((sda));
typedef int TI128 __attribute__((mode(TI)));
#define GROUP (*(unsigned char *)(s1 + 0x21))
#define FOR_EACH_ID(p) \
    for (p = D_L06_001FB3A0[GROUP]; \
         GROUP != 0xFF && GROUP <= D_L06_001B2838 && p != 0 && \
         ((p != 0 && (short)p[-1] >= 0) || p == D_L06_001FB3A0[GROUP]); \
         p++)

void func_PAL_L06_004015EC(char *a0)
{
    static void *cases[5] = {&&c0, &&c1, &&c2, &&done, &&c4};
    char *s1 = a0;
    char *s2;
    unsigned short *p;
    char *e;
    char *t;
    char *q;
    unsigned short *p4;
    int cls;
    unsigned int sel;
    float vec[4];
    float buf[4];

    sel = *(unsigned char *)(s1 + 0x20);
    s2 = *(char **)(s1 + 0x68);
    if (sel < 5)
        goto *D_L06_002E1DA0[sel];
    goto done;
c0:
    *(unsigned char *)(s1 + 0x30) = 0xFE;
    func_PAL_L06_00401AA0(*(unsigned char *)(s1 + 0x21));
    goto done;
c1:
    if (*(int *)(s2 + 0x64) != -1 && func_L00_00329520(D_L06_001B9840, *(int *)(s2 + 0x64)) != 0) {
        FOR_EACH_ID(p) {
            e = D_L06_001B281C_abs[0] + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            *(unsigned char *)(e + 0x31) = 0;
            *(unsigned short *)(e + 0x34) |= 1;
        }
        func_002A7750(s1, 4, -1);
    }
    func_PAL_L06_00401D78(s1);
    t = D_00188660 + *(int *)(s2 + 0x54) * 0x70;
    if (*(int *)(t + 0x88) != (int)s1 || *(unsigned char *)(t + 0x74) == 0)
        *(int *)(s2 + 0x54) = func_002E5CF8(0, 4, s1);
    if (*(unsigned char *)(s1 + 0x31) == 0)
        goto done;
    if (func_00282948(s2 + 0x44)) {
        if (*(unsigned short *)(s1 + 0x34) & 0x10) {
            *(unsigned short *)(s1 + 0x34) &= 0xFFEF;
            *(int *)(s2 + 0x44) = *(int *)(s2 + 0x48);
        } else {
            *(unsigned short *)(s1 + 0x34) |= 0x10;
            *(int *)(s2 + 0x44) = 4;
        }
    }
    if (func_002A9640(s1, 0x4010000, 0)) {
        cls = *(short *)(s1 + 0xAA) == 0x86B ? 2 : 3;
        func_PAL_L00_0032C328(s1, &D_L06_001AFC80, &D_L06_001AFC70, &D_L06_001AFC68, 0xFFFF, 1, cls, 0, 0xFFFF,
                          0xFF, 0);
        *(short *)(s1 + 0x7C) = (1 << cls) - 0x8000;
        func_PAL_L00_003FB330(s1 + 0x10, 0, 0x19, 0x14, 0x14, 0x14, 0x14, 1, 1.0f, 20.0f, 1, 0, 0, 0);
        func_002A7750(s1, 2, -1);
        *(int *)(s2 + 0x38) = 0;
        *(int *)(s2 + 0x14) = 0;
        *(int *)(s2 + 0x58) = 0x96;
        *(int *)(s1 + 0x98) = 0;
    }
    *(unsigned char *)(s1 + 0xA8) = 0xFF;
    *(float *)(s1 + 0xF8) = func_00283B98(*(float *)(s1 + 0xF8), 3.141593f);
    func_002833F0(s1 + 0xC0, s1 + 0xF0);
    goto done;
c4:
    if (func_L00_00329520(D_L06_001B9840, *(int *)(s2 + 0x64)) == 0) {
        FOR_EACH_ID(p4) {
            q = D_L06_001B281C_abs[0] + ((*p4 & 0x7FFF) << 8);
            if (q == 0)
                break;
            *(unsigned char *)(q + 0x31) = 1;
            *(unsigned short *)(q + 0x34) &= 0xFFFE;
        }
        func_002A7750(s1, 1, -1);
    }
    goto done;
c2:
    *(float *)(s1 + 0xF4) = (*(float *)(s1 + 0xF4) - 0.7853982f) * 0.94f + 0.7853982f;
    func_002833F0(s1 + 0xC0, s1 + 0xF0);
    *(float *)(s1 + 0x18) = *(float *)(s1 + 0x18) - 0.024000002f;
    if (func_002A77E0(4) == 0 && *(short *)(s1 + 0xAA) == 0x86B) {
        *(TI128 *)vec = 0;
        vec[2] = 0.10000001f;
        func_L01_0031A278(s1, buf, -1.5f, 0.0f, 1.0f);
        func_PAL_L01_002E2968(buf, vec, 1, 0x40F0E0D0, 0, 0.050000004f, 2.0f, 1.02f);
    }
    if (func_00282948(s2 + 0x58)) {
        *(unsigned char *)(s1 + 0x31) = 0;
        *(unsigned short *)(s1 + 0x34) |= 1;
        func_002A7750(s1, 3, -1);
    }
done:
    return;
}
