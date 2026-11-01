#include "include_asm.h"

#include "common.h"
extern void func_002A7750(void *, int, int);
extern void func_L00_002E6CF0(void (*)(void *), void *);
extern void func_L04_0043BEE8(void *);
extern float func_002AA2E8(void *, float, float);
extern void *func_PAL_L00_003FB330(void *, int, float, int, int, int, int, int, int, int, int, int, int, float);
extern void func_002A0488(void *, int, int, int);
extern void func_0029F338(void *);
extern void func_L04_0043BE40(void *);
extern int func_002AD0E0(void *, void *, void *, void *, void *, void *);
extern float D_L04_001B1394 SDATA(D_L04_001B1394);
extern float D_L04_001B1398 SDATA(D_L04_001B1398);
extern int D_L04_001B139C SDATA(D_L04_001B139C);
extern int D_L04_001B13A0 SDATA(D_L04_001B13A0);
extern int D_L04_001B13A4 SDATA(D_L04_001B13A4);
extern int D_L04_001B13A8 SDATA(D_L04_001B13A8);
extern int D_L04_001B13AC SDATA(D_L04_001B13AC);
extern int D_L04_001B13B0 SDATA(D_L04_001B13B0);
extern int D_L04_001B13B4 SDATA(D_L04_001B13B4);
extern int D_L04_001B13B8 SDATA(D_L04_001B13B8);
extern int D_L04_001B13BC SDATA(D_L04_001B13BC);

void func_PAL_L04_004410A8(unsigned char *m)
{
    float temporary[4];
    unsigned char *p = *(unsigned char **)(m + 0x68);
    switch (m[0x20]) {
    case 0:
        func_002A7750(m, 1, -1);
        break;
    case 1:
        func_L00_002E6CF0(func_L04_0043BEE8, m);
        func_002AA2E8(p + 0x4c, 1.0f, *(float *)(p + 0x5c));
        if (*(float *)(p + 0x4c) >= 1.0f) {
            func_002A7750(m, 2, -1);
            func_PAL_L00_003FB330(p + 0x20, 0, D_L04_001B1398, D_L04_001B139C, D_L04_001B13A0, D_L04_001B13A4, D_L04_001B13A8, D_L04_001B13AC, D_L04_001B13B0, D_L04_001B13B4, D_L04_001B13B8, D_L04_001B13BC, *(int *)(p + 0x44), 20.0f);
        }
        break;
    case 2:
        if (!(*(float *)(p + 0x58) < 1.0f)) {
            *(unsigned short *)(*(unsigned char **)(p + 0x48) + 0x34) = *(unsigned short *)(p + 0x50);
            func_002A0488(*(void **)(p + 0x48), p[0x54], p[0x55], p[0x56]);
            func_0029F338(m);
            return;
        }
        func_L04_0043BE40(m);
        func_002AA2E8(p + 0x58, 1.0f, D_L04_001B1394 * 0.020000001f);
        break;
    }
    if (*(int *)(p + 0x40))
        func_002AD0E0(m, *(void **)(p + 0x40), p, temporary, p, temporary);
    if (*(int *)(p + 0x44)) {
        unsigned char *other = *(unsigned char **)(p + 0x48);
        func_002AD0E0(other, *(void **)(p + 0x44), other + 0x10, other + 0xf0, other + 0x10, other + 0xf0);
        qcopy(p + 0x20, other + 0x10);
    }
}
