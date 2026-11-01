#include "include_asm.h"

#include "common.h"
typedef int Snapshot128 __attribute__((mode(TI)));
extern u8 D_L01_002A4D50[],D_00189EA0[];
extern float D_L01_001B0420 __attribute__((sda));
extern float D_L01_001B0424 __attribute__((sda));
extern float D_L01_001B0428 __attribute__((sda));
extern float D_L01_001B042C __attribute__((sda));
extern float D_L01_001B0430 __attribute__((sda));
extern float D_L01_001B0434 __attribute__((sda));
extern void func_0026FEB8(void *,int,int);
extern float func_PAL_L01_003BEB40(void);
extern float func_002A7940(void);
extern void func_002A7750(void *,int,int);
extern void func_002AEF28(void *,void *,void *,float,float,float);
extern float func_PAL_L01_003D2900(float *,float *,float,float,float,float);
extern float func_00282E80(void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);

/* Initializes a floating object and keeps its motion above the water surface. */
void func_PAL_L01_003D29A0(u8 *a0)
{
    u8 *p = *(u8 **)(a0 + 0x68);
    float snapshots[2][4] __attribute__((aligned(16)));
    float d[4] __attribute__((aligned(16)));
    float h, dist, delta;

    if (!p) {
        func_0026FEB8(D_L01_002A4D50, *(s16 *)(a0 + 0xAA), *(s16 *)(a0 + 0xB2));
        return;
    }
    switch (a0[0x20]) {
    case 0:
        if (func_PAL_L01_003BEB40() > 0.0f) {
            *(float *)(p + 0x20) = func_002A7940();
            *(float *)(p + 0x24) = func_002A7940();
            *(float *)(p + 0x28) = 0.02f;
            qcopy(p, a0 + 0x10);
            func_002A7750(a0, 1, -1);
        }
        break;
    case 1:
        /* Retail takes two position snapshots before updating movement. */
        *(Snapshot128 *)snapshots[0] = *(Snapshot128 *)(a0 + 0x10);
        *(Snapshot128 *)snapshots[1] = *(Snapshot128 *)snapshots[0];
        h = func_PAL_L01_003BEB40();
        func_002AEF28(a0, p + 0x20, p + 0x24, D_L01_001B0420,
                      D_L01_001B0424 * 0.0003490659f,
                      D_L01_001B0428 * 0.0003490659f);
        func_PAL_L01_003D2900((float *)(a0 + 0x10), (float *)(p + 0x10), *(float *)p,
                          D_L01_001B042C * 0.00040000002f, D_L01_001B0430, 3.0f);
        func_PAL_L01_003D2900((float *)(a0 + 0x14), (float *)(p + 0x14), *(float *)(p + 4),
                          D_L01_001B042C * 0.00040000002f, D_L01_001B0430, 3.0f);
        dist = func_00282E80(a0 + 0x10, D_00189EA0);
        if (dist < D_L01_001B0434 &&
            *(float *)(D_00189EA0 + 8) < *(float *)(a0 + 0x18) + 0.8f) {
            func_00282CF0(d, a0 + 0x10, D_00189EA0);
            d[2] = 0;
            func_00282F20(d, d, (D_L01_001B0434 - dist) * 0.08f);
            func_00282CC0(a0 + 0x10, a0 + 0x10, d);
        }
        delta = h + *(float *)(p + 0x28) - *(float *)(a0 + 0x18);
        if (delta > 0.060000002f)
            delta = 0.060000002f;
        else if (delta < -0.060000002f)
            delta = -0.060000002f;
        *(float *)(a0 + 0x18) += delta;
        break;
    }
}
