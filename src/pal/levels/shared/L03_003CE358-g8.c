#include "include_asm.h"

#include "common.h"
typedef unsigned int quadword __attribute__((mode(TI)));
extern void func_002A7750(u8 *, int, int);
extern void func_L00_003294F0(u8 *, int);
extern u8 *D_L03_001B2A20[3] __attribute__((sda));
extern unsigned short D_L03_001B0300 __attribute__((sda));
extern unsigned short D_L03_001B0304 __attribute__((sda));
extern int D_L03_001B2548[3] __attribute__((sda));
extern int D_L03_001B02F8 __attribute__((sda));
extern int D_L03_001B02FC[3] __attribute__((sda));
extern int D_L03_001B0308;
extern float D_L03_001B030C __attribute__((sda));
extern float D_L03_001B0310 __attribute__((sda));
extern float D_L03_001B0314 __attribute__((sda));
extern float D_L03_001B0318 __attribute__((sda));
extern u8 D_L03_001A8F20[16] __attribute__((sda));
extern void func_L03_003CA4B0(void);
extern void func_L00_002E6CF0(void *, void *);
extern float func_00283198(float);
extern int func_00283D38(int, int, float);
extern int func_002A9640(void *, int, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_PAL_L00_00328480(void *, void *, float, float, float, float, int, int, void *, int, int);
extern void func_PAL_002B15D8(void *, int, void *, int, float, float, float, float);
extern int func_002E5CF8(int, int, void *);

void func_PAL_L03_003CE358(u8 *m) {
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    switch (m[0x20]) {
    case 0:
        if ((int)m < (int)D_L03_001B2A20[0]) {
            *(int *)(m+0x9c) = 15;
            func_002A7750(m, 3, -1);
        } else {
            *(unsigned short *)(m+0x7c) = D_L03_001B0300;
            func_002A7750(m, 1, -1);
        }
        break;
    case 1:
        if (m[0x31]) {
            func_L00_002E6CF0(func_L03_003CA4B0, m);
            *(int *)(m+0x78) = func_00283D38(D_L03_001B02F8, D_L03_001B02FC[0],
                (func_00283198((D_L03_001B2548[0] % 150) * 0.04188786819577217f - 3.14159f) + 1.0f) * 0.5f);
        }
        if (func_002A9640(m, 0x10000, 0)) {
            *(quadword *)a = 0; *(quadword *)b = 0;
            b[2] = 0.060000002f;
            a[2] = 0.5f;
            func_00282CC0(a, a, m+0x10);
            func_PAL_L00_00328480(m,a,0.333000004f,3.0f,0.5f,1.0f,5,1,b,0x504040c0,0);
            func_PAL_002B15D8(m,D_L03_001B0308,D_L03_001A8F20,255,D_L03_001B030C,D_L03_001B0310,D_L03_001B0314,D_L03_001B0318);
            func_002E5CF8(0,0,m);
            *(unsigned short *)(m+0x7c) = D_L03_001B0304;
            func_L00_003294F0(m,1);
            *(int *)(m+0x9c) = 15;
            *(unsigned short *)(m+0x34) |= 2;
            func_002A7750(m,2,-1);
        }
        break;
    }
}
