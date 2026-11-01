#include "include_asm.h"
#include "common.h"

extern s32 func_00282978(s16 *timer);
extern s32 func_00288E18(s32 key, s32 selection);
extern s32 func_002ACBC8(void *point, s32 index);
extern s32 func_002E5E58(s32 index, s32 value, void *object);
extern void func_002B0A18(s32 first, s32 second);

extern u16 D_0018CF40;
extern u8 D_001A7AFD[] __attribute__((sda));
extern u8 D_001A7A60[] MACRO_ADDR;
extern u8 D_00189EA0[];
extern u8 D_00189E20[];
extern u32 D_L18_001A903C[] __attribute__((sda));

typedef int u128 __attribute__((mode(TI)));

extern char *func_002A9640(char *, int, int);
extern void func_002B0ED8(char *, char *, int);
extern void func_002A6C58(char *, int, int);
extern void func_0029F338(char *);
extern void func_00282CC0(void *, void *, void *);
extern int func_002A8C28(char *, void *, float, float, float, int, int, int, int);
extern void func_L00_002E6EF8(void *, char *);
extern char D_L18_003F9018[];

extern void func_3F7CD8(s32);
extern void func_3F7EF8(s32);
extern void func_3F80A0(s32);
extern void func_3F8A98(s32);
extern void func_3F8C08(s32);

extern float func_309900(float, float);
extern float func_308EE8(float);
extern float func_308F00(float);
extern float func_3099E8(float, float);
extern float func_308860(float);
extern void func_34B1D0(s32);

extern char *func_002B9030(s32);
extern s32 func_001163B0(void);
extern s32 func_00283CF0(float);
extern float func_00283180(float);
extern float func_00283198(float);
extern u8 *D_L18_001FF4D4;

/* func_L18_002E68B0 is in the sibling file L18_002E68B0-decider.c (its own profile). */

INCLUDE_ASM("asm/levels", func_L18_003170F8);


/* Fills the record with the requested fields and derived coordinates. */
char *func_L18_0035B6B8(char *p0, float f0, float f1, float f2, float f3, float f4, s16 p1,
                         char *p2, s32 p3, char *p4)
{
    char *s0 = func_002B9030(0x65);
    char *s1 = s0 + 0x20;

    if (s0 != 0) {
        *(u8 *)(s0 + 3) = (p4 != 0) ? 0x48 : 0x44;
        *(u8 *)(s0 + 1) = 0;
        *(u8 *)(s0 + 2) = D_L18_001FF4D4[p3];
        *(u8 *)(s0 + 8) = func_001163B0();
        *(u8 *)(s0 + 9) = func_00283CF0(1.0f) + 0x40;
        *(u32 *)(s0 + 4) = p2;
        *(float *)(s0 + 0xC) = f3 * 210000.0f;
        *(u32 *)(s1 + 0) = p0;
        *(float *)(s1 + 4) = f0;
        *(float *)(s1 + 8) = f1;
        *(float *)(s1 + 0xC) = f2;
        *(u16 *)(s1 + 0x14) = p1;
        *(float *)(s1 + 0x10) = f4 * 210000.0f;
        *(float *)(s0 + 0x10) = *(float *)(*(char **)(s1 + 0)) +
                                *(float *)(s1 + 4) * func_00283180(f1);
        *(float *)(s0 + 0x18) = *(float *)(*(char **)(s1 + 0) + 8) +
                                *(float *)(s1 + 4) * func_00283198(*(float *)(s1 + 8));
        *(float *)(s0 + 0x14) = *(float *)(*(char **)(s1 + 0) + 4);
    }
    return s0;
}

void func_L18_0035B838(char *a0)
{
    char *s1 = a0;
    char *s0 = s1 + 0x20;
    float t;

    *(u8 *)(s1 + 8) = *(u8 *)(s1 + 8) + *(u8 *)(s0 + 0x14);
    *(float *)(s0 + 8) = func_309900(*(float *)(s0 + 8), *(float *)(s0 + 0xC));
    *(float *)(s1 + 0xC) = *(float *)(s1 + 0xC) + *(float *)(s0 + 0x10);
    *(float *)(s1 + 0x10) = *(float *)(*(char **)(s1 + 0x20)) +
                            *(float *)(s0 + 4) * func_308EE8(*(float *)(s0 + 8));
    *(float *)(s1 + 0x18) = *(float *)(*(char **)(s1 + 0x20) + 8) +
                            *(float *)(s0 + 4) * func_308F00(*(float *)(s0 + 8));
    t = func_3099E8(*(float *)(s0 + 8), *(float *)(*(char **)(s1 + 0x20) + 0x10));
    if (t < func_308860(*(float *)(s0 + 0xC) + *(float *)(s0 + 0xC)))
        func_34B1D0(s1);
}

void func_L18_003A0C28(u8 *entity) {
    u8 *state;
    u32 substate;
    u8 mode;

    state = *(u8 **)(entity + 0x68);
    if (entity[0x20] == 0) {
        entity[0x30] = 0xFF;
        *(u16 *)(state + 0xE) = 0x28;
        *(u16 *)(state + 0xC) = 0;
        entity[0x20] = 1;
    }
    if (D_0018CF40 != 0)
        goto after;
    if (D_001A7AFD[0] != 0) {
        if (func_00282978((s16 *)(state + 0xE)) != 0)
            func_00288E18(0xA27, 0x7E);
    }
after:
    mode = entity[0x20];
    if (mode != 1)
        goto end;
    substate = *(u32 *)(state + 0x8);
    switch (substate) {
    case 0: {
        u8 *block = D_00189EA0;
        if (func_002ACBC8(block, *(u32 *)(state + 0)) != 0) {
            if (*(u32 *)(block + 0x221C) == 15)
                *(u32 *)(state + 8) = mode;
        }
        break;
    }
    case 1: {
        u8 *block = D_00189E20;
        if (*(u32 *)(block + 0x2294) == 0x3E) {
            *(u32 *)(state + 8) = 0;
        } else if (func_002ACBC8(block + 0x80, *(u32 *)(state + 4)) != 0) {
            if (D_001A7A60[7] == 0) {
                D_001A7A60[7] = substate;
                func_002E5E58(1, 0, 0);
                func_002B0A18(0x1233, -1);
                D_L18_001A903C[0] = substate;
            }
        }
        break;
    }
    }
end:
    return;
}


void func_L18_003F7C70(s32 a0)
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

extern void func_002B60B0(u8 *, float, float, float, float);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern int func_L02_0032E508(u8 *, int, u8 *, int);
extern void func_L18_003F8FA8(u8 *);
extern void func_002A7750(u8 *, int, int);

void func_L18_003F7CD8(u8 *object) {
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
    *(float *)(state + 0x13C) = 0.0055555556900799274f;
    *(float *)(state + 0x114) = 0.5f;
    *(float *)(state + 0x118) = 0.5f;
    *(float *)(state + 0x11C) = 2.0f;
    *(float *)(state + 0x120) = 1.5707964897155762f;
    func_002B60B0(object, 0.0033333334140479565f, 0.10000000894069672f,
                  0.0034906589426100254f, 0.20943954586982727f);
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

void func_L18_003F7EF8(char *p)
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
    func_002B0ED8(p, data + 0x60, 0);
    if (*(unsigned char *)(p + 0x20) == 9 &&
        (*(unsigned char *)(p + 0x94) == 9 || *(unsigned char *)(p + 0x94) == 4 || *(unsigned char *)(p + 0x94) == 3))
        *(unsigned char *)(p + 0x94) = old;
    if (*(float *)(p + 0x18) < 90.0f) {
        func_002A6C58(p, 0, 3);
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
