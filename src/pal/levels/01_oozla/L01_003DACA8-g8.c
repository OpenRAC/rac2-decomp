#include "include_asm.h"

#include "common.h"
typedef struct {
    int active;
    int timer;
} OozlaCountdown;
typedef struct {
    u8 pad0[0x20];
    u8 state;
    u8 pad21[0x10];
    u8 field31;
    u16 field32;
    u16 flags;
    u8 pad36[0x32];
    OozlaCountdown *p;
    u8 pad6c[0x2C];
    int field98;
    u8 pad9c[12];
    u8 fielda8;
} OozlaStateMoby;
extern int D_L01_001AEC38 MACRO_ADDR;
extern float D_L01_001B2090, D_L01_001B208C;
extern int D_L01_001B3468 MACRO_ADDR;
extern int D_L01_001B15E0 MACRO_ADDR;
extern void *func_002A9640(void *, int, int);
extern void func_002A7750(void *, int, int);
extern void func_L01_003D6B00(void *, int, float, float, float, float);
extern void func_002E5CF8(int, int, void *);
extern void func_PAL_L00_003281C0(void *, int, float);
extern void func_L00_00326620(void *, int, int);
extern int func_002B3868(void *);
extern int func_00282948(void *);
extern void func_0029F338(void *);

void func_PAL_L01_003DACA8(OozlaStateMoby *a0)
{
    OozlaCountdown *p = a0->p;

    switch (a0->state) {
    case 0: {
        D_L01_001AEC38++;
        a0->flags |= 0x800;
        func_002A7750(a0, 1, -1);
        break;
    }
    case 1:
        if (func_002A9640(a0, 0x4010000, 0) && !p->active) {
            D_L01_001AEC38 = D_L01_001AEC38 - 1;
            func_002A7750(a0, 2, -1);
        }
        a0->fielda8 = 255;
        break;
    case 2:
        if (a0->field31 && D_L01_001B2090 < 0.9f && D_L01_001B208C < 0.9f &&
            D_L01_001B3468 < D_L01_001B15E0)
            func_L01_003D6B00(a0, 15, 1.5f, 6.5f, 1.5f, 0.080000006f);
        else
            func_L01_003D6B00(a0, 6, 1.5f, 6.5f, 1.5f, 0.080000006f);
        func_002E5CF8(0, 0, a0);
        func_PAL_L00_003281C0(a0, 1, 0.0f);
        func_L00_00326620(a0, 0xF94, 0);
        func_002A7750(a0, 3, -1);
        break;
    case 3:
        if (func_002B3868(a0)) {
            a0->flags |= 1;
            a0->field31 = 0;
            a0->field98 = 0;
            p->timer = 100;
            D_L01_001B3468++;
        }
        if (func_00282948(&p->timer)) {
            D_L01_001B3468--;
            func_0029F338(a0);
        }
        break;
    }
}
