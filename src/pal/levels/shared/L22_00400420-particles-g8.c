/* func_PAL_L22_00400420, the PAL copy of func_L22_003FBBF0: the same C, where the slots'
   initial value is an int scaled for 50 Hz, computed in a count-up loop. */
#include "common.h"

typedef int TI __attribute__((mode(TI)));
typedef struct {
    u8 pad[0x40];
    unsigned short initialValues[4];
    u8 pad48[8];
    float randomValues[4];
    void * particles[8];
} Controller;

extern int ref_L22_003FBBF0_00 __attribute__((sda));
extern float ref_L22_003FBBF0_01 __attribute__((sda));
extern u8 * D_L22_001B1D6C;
extern u8 D_L22_00255820[], D_L22_002558A0[];
extern int func_002A77E0(int);
extern float func_002A7878(float, float), func_002A78D8(float, float);
extern void func_002833F0(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_002AF000(void *, float, float, float);

/* Initialize the particle slots and their direction tables. */
void func_PAL_L22_00400420(u8 * obj) {
    Controller * ctl = *(Controller **)(obj + 0x68);
    int i;
    float a, b;

    for (i = 0; i < 4; i++) ctl->randomValues[i] = (float)func_002A77E0(255);
    for (i = 0; i < 4; i++)
        ctl->initialValues[i] = ((s32)(ref_L22_003FBBF0_00) * 5 + 2) / 6;
    for (i = 7; i >= 0; i--) ctl->particles[i] = 0;
    if (D_L22_001B1D6C == 0) {
        u8 * x = obj + 0xC0, *y, *z = obj + 0xE0;
        u8 * v, *w;
        func_002833F0(x, obj + 0xF0);
        D_L22_001B1D6C = obj;
        obj[0x30] = 255;
        v = D_L22_00255820;
        func_00282F20(v, x, ref_L22_003FBBF0_01);
        w = D_L22_002558A0;
        *(TI *)w = *(TI *)z;
        y = obj + 0xD0;
        func_00282F20(v + 0x10, y, ref_L22_003FBBF0_01);
        *(TI *)(w + 0x10) = *(TI *)x;
        func_00282F20(v + 0x20, z, ref_L22_003FBBF0_01);
        *(TI *)(w + 0x20) = *(TI *)y;
        func_00282CC0(v + 0x30, x, z);
        func_00282F20(v + 0x30, v + 0x30, ref_L22_003FBBF0_01);
        func_00282DD8(w + 0x30, v + 0x30, y);
        func_00282CC0(v + 0x40, x, y);
        func_00282F20(v + 0x40, v + 0x40, ref_L22_003FBBF0_01);
        func_00282DD8(w + 0x40, v + 0x40, z);
        func_00282CF0(v + 0x50, y, z);
        func_00282F20(v + 0x50, v + 0x50, ref_L22_003FBBF0_01);
        func_00282DD8(w + 0x50, v + 0x50, x);
        func_00282CF0(v + 0x60, x, z);
        func_00282F20(v + 0x60, v + 0x60, ref_L22_003FBBF0_01);
        func_00282DD8(w + 0x60, v + 0x60, y);
        func_00282CF0(v + 0x70, x, y);
        func_00282F20(v + 0x70, v + 0x70, ref_L22_003FBBF0_01);
        func_00282DD8(w + 0x70, v + 0x70, z);
    }
    a = func_002A7878(0.0f, 6.2831855f);
    b = func_002A7878(-1.5707964f, 1.5707964f);
    func_002AF000((u8 *)ctl + 0x10, 1.0f, a, b);
    *(float *)((u8 *)ctl + 0x1C) = func_002A78D8(0.785398f, 1.5707964f);
}
