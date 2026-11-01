#include "common.h"
extern u8 *D_L18_001B281C MACRO_ADDR;
extern int ref_L18_00428AE8_00 __attribute__((sda));
typedef union { u8 b[0x100]; s16 h[0x80]; int i[0x40]; float f[0x40]; } Obj;
extern u16 D_L18_001B1240 __attribute__((sda));
extern u16 D_L18_001B1264 __attribute__((sda));
extern void func_00282F20(void *, void *, float);
extern void func_00282CD8(void *, void *, void *);
extern void func_L01_00321178(void *, void *);
extern void func_002B4FF0(void *, void *, float);
extern void func_L01_00318638(void *, void *, void *);
extern float func_00282E80(void *, void *);
extern int ref_L18_00428AE8_01(void *, int);
extern int func_L18_00427130(void *, int, int);
extern int func_L18_004271C0(void *);
extern void func_L18_00426F28(void *, int, int, float);
extern void func_002A7750(void *, int, int);
extern void func_L18_00428138(void *);
extern int func_001163B0(void);
extern void func_002A6C58(void *, int, int);
void func_L18_00428AE8(u8 *o) {
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    u8 *s = *(u8 **)(o + 0x68);
    float old1, old2;
    int n = *(int *)(s + 0x3B4);
    if (n != -1) {
        u8 *m = (u8 *)((n << 8) + ref_L18_00428AE8_00);
        if (((Obj *)m)->h[0xAA/2] == 0x114D && ((Obj *)m)->b[0x20] != 0xFE && ((Obj *)m)->b[0x20] != 0xFD)
            ((Obj *)m)->i[0x98/4] = 0;
    }
    if (o[0x95] == 13) {
        func_00282F20(a, D_L18_001B281C + (*(int *)(s+0x3B4)<<8) + 0xC0, 5.0f);
        func_00282CD8(b, a, D_L18_001B281C + (*(int *)(s+0x3B4)<<8) + 0x10);
        a[2] = *(float *)(o+0x18);
        *(float *)(s+0x128) *= 10.0f;
        *(float *)(s+0x120) *= 10.0f;
        old1 = *(float *)(s+0x110);
        old2 = *(float *)(s+0x10C);
        *(float *)(s+0x110) = 3.1415927f;
        *(float *)(s+0x10C) = 0.5f;
        func_L01_00321178(o,a);
        *(float *)(s+0x128) *= 0.1f;
        *(float *)(s+0x120) *= 0.1f;
        *(float *)(s+0x110) = old1;
        *(float *)(s+0x10C) = old2;
        goto restore;
    } else {
        if (*(int *)(s+0x38C) != -1) {
            if (ref_L18_00428AE8_01(o, *(int *)(s+0x38C))) {
                switch (o[0x95]) {
                case 5:
                    if (s[0x399] & 2) s[0x399] = 0;
                    func_L18_00427130(o, *(int *)(s+0x374), -1);
                    *(u16 *)(s+0x392) = D_L18_001B1240;
                    func_L18_00426F28(o,2,0,10.0f);
                    func_002A7750(o,4,6);
                    break;
                case 6:
                    if (func_L18_004271C0(o)) {
                        *(u16 *)(s+0x392) = D_L18_001B1240;
                        func_L18_00426F28(o,2,0,10.0f);
                        func_002A7750(o,4,6);
                    }
                    if (*(s16 *)(o+0xAA) != 0xEC0) func_L18_00428138(o);
                    break;
                case 2:
                    func_L18_004271C0(o);
                    if (o[0x60] & 2) {
                        func_L18_00426F28(o,func_001163B0() & 1,0,10.0f);
                        func_002A7750(o,2,-1);
                    }
                    break;
                }
            }
                if (*(s16 *)(o+0xAA) == 0xEC0 && (unsigned)(o[0x95]-5) < 2) {
                    if (func_00282E80(o+0x10, *(u8 **)(s+0x230)+0x10) < *(float *)(s+0x3A0)) {
                        *(int *)(s+0x38C) = -1;
                        func_002A7750(o,4,6);
                    }
                }
                goto restore;

        } else if (o[0x95] == 6) {
            if (o[0x20] == o[0x95]) func_L01_00321178(o,s+0x220);
            else {
                func_002B4FF0(o,s+0x220,0.0f);
                func_L18_00428138(o);
            }
        } else {
wander:
            func_L01_00318638(o,s+0x1F0,s+0x100);
            if (*(s16 *)(s+0x392) == 0) {
                *(u16 *)(s+0x392) = D_L18_001B1264;
                func_L18_00426F28(o,func_001163B0() & 1,0,10.0f);
                func_002A7750(o,2,-1);
            }
        }
        if (*(float *)(o+0x18) < *(float *)(s+0x90)) {
            func_002A6C58(o,0,3);
            func_002A7750(o,12,10);
        }
restore:
        { int k = *(int *)(s+0x3B4);
        if (k != -1) {
            u8 *m = (u8 *)((k << 8) + ref_L18_00428AE8_00);
            if (((Obj *)m)->h[0xAA/2] == 0x114D && ((Obj *)m)->b[0x20] != 0xFE && ((Obj *)m)->b[0x20] != 0xFD)
                ((Obj *)m)->i[0x98/4] = *(int *)(((Obj *)m)->i[0x24/4]+0x10);
        } }
    }
}
