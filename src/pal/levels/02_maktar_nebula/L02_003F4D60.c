#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L02_003F4D60);

#include "common.h"
extern char D_L02_001BA500;
extern float func_00282E48();
extern void func_002A93B0();
extern int func_00283CF0(float);
extern float func_00283B98(float, float);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern int func_00283CF0(float);
extern float func_00283B98(float, float);
extern void func_00325B70(void *, void *, int, int);
extern void func_PAL_003273B8(float, void *, void *, int, void *);
extern void func_00325DA0(void *, void *);
extern void *func_002A9640(void *, int, int);
extern int func_PAL_002B1A50(void *, void *, int);
extern void func_PAL_L02_003F5EB0(char *);
extern void func_L02_003F16F0(char *);
extern char D_L02_001A8F20[] __attribute__((sda));
typedef struct {
    u8 pad0[0x18];
    char *p18;
    u8 pad1c[0xC];
    u8 b28;
    u8 pad29[5];
    u8 b2E;
    u8 pad2f[0x19];
    u8 b48;
    u8 pad49;
    u8 b4A;
    u8 pad4b[0x15];
    u8 x60[0x10];
    u8 b70;
    u8 pad71[0x1F];
    float f90;
    float f94;
    u8 pad98[4];
    float f9C;
    u8 pada0[8];
    int fA8;
    u8 padac[0x44];
    int fF0;
    float fF4;
    u8 padf8[0x18];
    float f110;
    float f114;
    float f118;
    float f11C;
    float f120;
    u8 pad124[0x18];
    float f13C;
    float f140;
    u8 pad144[0x370];
    float f4B4;
    u8 pad4b8[4];
    float f4BC;
    u8 x4C0[0xC];
    float f4CC;
    u8 pad4d0[0xC];
    u8 x4DC[0xE];
    short s4EA;
} St003F1298;
extern u8 D_L02_00220730;

/* Update with a lazy start: the first call (state byte +0x20 still 0) sets the actor up (a random
   sway angle of 15 to 40 degrees, either sign, two random bytes from 15 and 12, its speed and
   timing words), registers it and runs func_PAL_L02_003F5EB0; every call then fires func_002A93B0 when
   the player is within 24 units, turns the angle by the rate at +0x4CC, updates the effect,
   and for a visible actor of state 3 or more looks for the object of class 0xA03 / 0xB89 that
   it is attached to and releases it. */
void func_PAL_L02_003F5860(char *arg0) {
    St003F1298 *s = *(St003F1298 **)(arg0 + 0x68);
    float f;

    if (*(u8 *)(arg0 + 0x20) == 0) {
        s->p18 = (char *)&s->f110;
        f = func_002A7878(15.0f, 40.0f) * 0.017453294f;
        s->f4B4 = (func_002A77E0(2) != 0) ? -f : f;
        s->b48 = func_00283CF0(15.0f);
        s->b4A = func_00283CF0(12.0f);
        if (func_002A77E0(2) == 1)
            *(u16 *)(arg0 + 0x34) |= 0x8000;
        s->f4CC = 8.0f;
        s->f90 = 0.8f;
        s->b70 = 10;
        s->fA8 = 5;
        s->f94 = 0.8f;
        s->f9C = 0.4f;
        s->f118 = 0.4f;
        s->f110 = 0.6f;
        s->f114 = 0.2f;
        s->f11C = 0.4f;
        s->f4BC = 0.0f;
        s->f120 = 1.5707965f;
        s->f140 = 0.52359885f;
        s->f13C = 0.008f;
        s->b28 = 3;
        s->b2E = 1;
        func_00325B70(arg0, s->x4C0, 0, 1);
        s->s4EA = 0;
        func_PAL_L02_003F5EB0(arg0);
    }
    if (*(u8 *)(arg0 + 0x31) != 0) {
        if (func_00282E48(arg0 + 0x10, &D_L02_001BA500) < 24.0f) {
            func_002A93B0(arg0);
            *(u8 *)(arg0 + 0x6F) = 0x16;
        }
    }
    s->f4BC = func_00283B98(s->f4BC, s->f4CC * 0.017453294f);
    func_PAL_003273B8(s->f4BC, arg0, s->x4C0, 1, D_L02_001A8F20);
    func_00325DA0(arg0, s->x4DC);
    if (*(u8 *)(arg0 + 0x31) != 0 && *(u8 *)(arg0 + 0x20) >= 3) {
        char *t = func_002A9640(arg0, 0x10000, 1);

        if (t != 0 && *(char **)(t + 0x20) != 0 && *(u8 *)(arg0 + 0x31) == 0 &&
            (*(short *)(*(char **)(t + 0x20) + 0xAA) == 0xA03 ||
             *(short *)(*(char **)(t + 0x20) + 0xAA) == 0xB89))
            *(int *)(t + 0x2C) = 0;
        if (func_PAL_002B1A50(arg0, s->x60, 0) == 5) {
            s->fF0 = 0;
            s->fF4 = 1.0053098f;
        }
        if (*(u8 *)(arg0 + 0x20) >= 2 && s->b2E == 2)
            func_PAL_L02_003F5EB0(arg0);
        func_L02_003F16F0(arg0);
    }
}

