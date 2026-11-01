#include "include_asm.h"

#include "common.h"
extern void func_3F7CD8(s32);
extern void func_3F7EF8(s32);
extern void func_3F80A0(s32);
extern void func_3F8A98(s32);
extern void func_3F8C08(s32);
extern s32 func_001163B0(void);
extern s32 func_00283CF0(float);
extern u8 *D_L18_001FF4D4;

void func_PAL_L18_003FBD28(s32 a0)
{
    u8 v = *(u8 *)(a0 + 0x20);

    if (v == 0) {
        func_3F7CD8(a0);
        return;
    }
    if (v == 1)
        return;
    func_3F7EF8(a0);
    func_3F80A0(a0);
    func_3F8A98(a0);
    func_3F8C08(a0);
}

extern u16 D_0018CF40;
extern u8 D_001A7AFD[] __attribute__((sda));
extern u8 D_001A7A60[] MACRO_ADDR;
extern u8 D_00189EA0[];
extern u8 D_00189E20[];
extern void func_002B60B0(u8 *, float, float, float, float);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern int func_L02_0032E508(u8 *, int, u8 *, int);
extern void func_L18_003F8FA8(u8 *);
extern void func_002A7750(u8 *, int, int);

void func_PAL_L18_003FBD90(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    float rate, spin;

    state[0x70] = 9;
    *(int *)(state + 0xA8) = 4;
    *(float *)(state + 0x90) = 0.8f;
    *(float *)(state + 0x94) = 0.9f;
    *(float *)(state + 0x9C) = 0.4f;
    if (*(short *)(state + 0x24) == 0) {
        *(short *)(state + 0x24) = 16;
        *(float *)(state + 0x20) = 16;
    }
    state[0x28] = 3;
    *(float *)(state + 0x144) = 0.25f;
    *(float *)(state + 0x110) = 0.8f;
    *(float *)(state + 0x13C) = 0.008f;
    *(float *)(state + 0x114) = 0.5f;
    *(float *)(state + 0x118) = 0.5f;
    *(float *)(state + 0x11C) = 2.0f;
    *(float *)(state + 0x120) = 1.5707964897155762f;
    func_002B60B0(object, 0.0048f, 0.120000005f,
                  0.005026549f, 0.25132746f);
    *(u8 **)(state + 0x158) = state + 0x680;
    *(u8 **)(state + 0x15C) = state + 0x600;
    rate = func_002A7878(5.0f, 20.0f);
    if (func_002A77E0(2) != 0)
        spin = rate * -0.01745329424738884f;
    else
        spin = rate * 0.01745329424738884f;
    *(float *)(state + 0x720) = spin;
    *(int *)(state + 0x14C) = *(int *)(state + 0x718);
    if (*(int *)(state + 0x71C) != -1)
        *(int *)(state + 0x730) = func_L02_0032E508(object,
            *(int *)(state + 0x71C), state + 0x200, 0x20);
    *(short *)(state + 0x76C) = func_002A77E0(2);
    *(float *)(state + 0x72C) = func_002A7878(5.0f, 7.0f);
    *(u16 *)(object + 0x7C) |= 1 << func_002A77E0(6);
    switch (*(short *)(state + 0x764)) {
    case 1:
        func_L18_003F8FA8(object);
        break;
    case 2:
        func_002A7750(object, 2, 1);
        break;
    }
}


typedef int u128 __attribute__((mode(TI)));
extern char *func_002A9640(char *, int, int);
extern void func_PAL_002B1A50(char *, char *, int);
extern void func_PAL_002A7650(char *, int, int);
extern void func_0029F338(char *);
extern void func_00282CC0(void *, void *, void *);
extern int func_002A8C28(char *, void *, float, float, float, int, int, int, int);
extern void func_L00_002E6EF8(void *, char *);
extern char D_L18_003F9018[];

void func_PAL_L18_003FBFB0(char *p)
{
    char *data = *(char **)(p + 0x68);
    char *hit = func_002A9640(p, 0x10000, 1);
    int old;
    float v[4] __attribute__((aligned(16)));
    float temp[4] __attribute__((aligned(16)));
    float zero[4] __attribute__((aligned(16)));
    if (hit && *(char **)(hit + 0x20)) {
        int type = *(short *)(*(char **)(hit + 0x20) + 0xAA);
        if (type == 0xB69) {
            if (*(unsigned char *)(p + 0x31)) *(float *)(hit + 0x2C) = 4.0f;
            else *(float *)(hit + 0x2C) = 0;
        } else if (type == 0xF0A || type == 0xF9E) *(float *)(hit + 0x2C) = 0;
    }
    old = *(unsigned char *)(p + 0x94);
    func_PAL_002B1A50(p, data + 0x60, 0);
    if (*(unsigned char *)(p + 0x20) == 9 &&
        (*(unsigned char *)(p + 0x94) == 9 || *(unsigned char *)(p + 0x94) == 4 || *(unsigned char *)(p + 0x94) == 3))
        *(unsigned char *)(p + 0x94) = old;
    if (*(float *)(p + 0x18) < 90.0f) {
        func_PAL_002A7650(p, 0, 3);
        func_0029F338(p);
        return;
    }
    *(u128 *)zero = 0;
    zero[2] = *(float *)(data + 0x114) + *(float *)(data + 0x110);
    *(u128 *)temp = *(u128 *)zero;
    func_00282CC0(v, p + 0x10, temp);
    func_002A8C28(p, v, *(float *)(data + 0x110) + 0.2f, 10.0f, 1.0f, 0x4000000, 0, 1, 0);
    if (*(unsigned char *)(p + 0x20) >= 2) func_L00_002E6EF8(D_L18_003F9018, p);
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L18_003FC158);


