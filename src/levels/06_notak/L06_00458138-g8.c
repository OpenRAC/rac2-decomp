#include "common.h"

extern float D_L06_001B234C __attribute__((sda));

extern float D_001B2350 __attribute__((sda));

extern int func_0035CBA0(char *, int, int);

extern void func_L06_0045BE30(char *, int, float, float, float, float);

extern int func_003A0948(int, int, char *);

extern void func_00350388(char *);

extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_002A77E0(int);
extern void func_00282CC0(void *, void *, void *);
extern void func_L06_0037E6B0(void *, void *, int, float, float);
extern float D_L06_001B1AC0 __attribute__((sda));
extern float D_L06_001B1AC4 __attribute__((sda));
extern float D_L06_001B1AC8 __attribute__((sda));
extern float D_L06_001B1ACC __attribute__((sda));
extern float D_L06_001B1AD0 __attribute__((sda));
extern float D_L06_001B1AD4 __attribute__((sda));
extern float D_L06_001B1AD8 __attribute__((sda));
extern float D_L06_001B1ADC __attribute__((sda));
extern int D_L06_001B1AE0 __attribute__((sda));
extern int D_L06_001B1AE4 __attribute__((sda));
extern int D_L06_001B1AE8 __attribute__((sda));

extern u8 *D_L06_001B281C MACRO_ADDR;
extern char D_00188660[];
extern void func_003514C8(void *, int, void *);
extern void func_00282CF0(float *, const float *, const float *);
extern float func_00282DF0(void *);
extern float func_00282C48(float);
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern void func_L06_004583A8(char *);
extern int func_002E59B0(char *, int);
extern void func_002E59F8(int);

extern u8 *D_L06_001B290C MACRO_ADDR;
extern char D_L06_001B1990[];
extern char D_L06_001B19C8[];
extern char D_L06_001B1A00[];
extern char D_L06_001B1A30[];
extern u8 *D_L06_001FE500[];

extern void func_0026FEB8(char *, ...);
extern int func_001163B0(void);
extern void func_L06_00459B18(char *a0);
extern int func_L06_00459BA8(char *a0, char *a1);
extern void func_L06_00459C38(unsigned char *a0, u8 *a1);

void func_L06_00458568(char *a0) {
    char *state = *(char **)(a0 + 0x68);
    char *other;
    float tmp[4];
    switch (*(unsigned char *)(a0 + 0x20)) {
    case 0:
        *(float *)(state + 8) = *(float *)(a0 + 0xF8);
        *(float *)(state + 0x18) = *(float *)(a0 + 0xF4);
        *(int *)(state + 0x10) = 0;
        func_003514C8(a0, 0, tmp);
        FastVecSub(tmp, tmp, (float *)(a0 + 0x10));
        {
            float f = FastVecLength(tmp);
            *(float *)(state + 4) -= f;
            *(float *)(state + 0x1C) = f;
        }
        if (*(float *)(state + 0xC) == 0.0f) *(float *)(state + 0xC) = 1.0f;
        func_L06_004583A8(a0);
        *(float *)(state + 0x24) = 0;
        a0[0x20] = 1;
        break;
    case 1:
        if (*(int *)state != -1) {
            other = D_L06_001B281C + *(int *)state * 256;
            if (other) {
                char *data = *(char **)(other + 0x68);
                if (func_00282C48(*(float *)(state + 0xC)) > 0.0f)
                    *(float *)(state + 0x14) = *(float *)data * (*(float *)(state + 0xC) * 3.1415927f);
                else *(float *)(state + 0x14) = 0;
                *(float *)(a0 + 0xF8) = FastAddRotations(*(float *)(state + 8), *(float *)(state + 0x14));
                if (*(float *)data > 0.6f)
                    *(float *)(a0 + 0xF4) = fast_subtract_rotations(*(float *)(state + 0x18), (*(float *)data - 0.6f) * 0.13089971244335175f);
                if (*(int *)(state + 0x10) == 0) {
                    if (*(float *)data != *(float *)(state + 0x24) && *(float *)data != 1.0f && *(float *)data != 0.0f) {
                        if (!func_002E59B0(a0, *(int *)(state + 0x20)))
                            *(int *)(state + 0x20) = func_003A0948(0, 4, a0);
                    } else if (func_002E59B0(a0, *(int *)(state + 0x20))) {
                        if (*(int *)(state + 0x20) != -1) {
                        char *snd = D_00188660 + *(int *)(state + 0x20) * 0x70;
                        if (*(char **)(snd + 0x88) == a0 && *(unsigned char *)(snd + 0x74)) func_002E59F8(*(int *)(state + 0x20));
                        }
                        *(int *)(state + 0x20) = -1;
                    }
                }
                *(float *)(state + 0x24) = *(float *)data;
            }
        }
        if (*(int *)(state + 0x10)) func_003514C8((void *)*(int *)(state + 0x10), 0, a0 + 0x10);
        break;
    }
}

/* Resolves the table entries a spawn record names; returns 1 after reporting a missing one. */
int func_L06_00459D08(u8 *a0, u8 *a1)
{
    s32 i1, i2, i3, i4;
    u8 *e1, *e2;

    i1 = *(s32 *)(a1 + 0x100);
    if (i1 == -1) {
        STUB_printf(D_L06_001B1990, (a0 - D_L06_001B281C) >> 8);
        return 1;
    }
    e1 = D_L06_001FE500[i1];
    *(u8 **)(a1 + 0x118) = e1;
    func_L06_00459B18((char *)e1);
    i2 = *(s32 *)(a1 + 0x134);
    if (i2 == -1) {
        STUB_printf(D_L06_001B19C8, (a0 - D_L06_001B281C) >> 8);
        return 1;
    }
    e2 = D_L06_001FE500[i2];
    *(u8 **)(a1 + 0x138) = e2;
    func_L06_00459B18((char *)e2);
    i3 = *(s32 *)(a1 + 0x108);
    if (i3 == -1) {
        STUB_printf(D_L06_001B1A00, (a0 - D_L06_001B281C) >> 8);
        return 1;
    }
    *(u8 **)(a1 + 0x11C) = D_L06_001B281C + (i3 << 8) + 0x18;
    a0[0xBC] = func_L06_00459BA8((char *)a0, (char *)a1);
    i4 = *(s32 *)(a1 + 0x104);
    if (i4 == -1) {
        STUB_printf(D_L06_001B1A30, (a0 - D_L06_001B281C) >> 8);
        return 1;
    }
    qcopy(a1 + 0xE0, D_L06_001B290C + 0x30 + (i4 << 7));
    qcopy(a1 + 0xD0, a0 + 0x10);
    func_L06_00459C38(a0, a1);
    *(s32 *)(a1 + 0x124) = func_001163B0() % 120;
    if (func_001163B0() & 1)
        *(f32 *)(a1 + 0x130) = 0.3490659f;
    else
        *(f32 *)(a1 + 0x130) = -0.3490659f;
    *(s32 *)(a1 + 0x13C) = 0;
    a1[0x29] = 1;
    return 0;
}

void func_L06_0045C6D0(char *a0) {
    float velocity[4], pos[4], offset[4];
    qcopy(pos, a0 + 0x10);
    pos[2] += 3.3f + func_002A7878(-0.05f, 0.05f);
    pos[0] += func_002A7878(-0.1f, 0.1f);
    pos[1] += func_002A7878(-0.1f, 0.1f);
    offset[0] = func_00283180(*(float *)(a0 + 0xF8)) * 1.5f;
    offset[1] = func_00283198(*(float *)(a0 + 0xF8)) * 1.5f;
    offset[2] = 0;
    FastVecAdd(pos, pos, offset);
    velocity[0] = func_00283180(*(float *)(a0 + 0xF8)) * func_002A7878(D_L06_001B1AC0 * 0.0166666675f, D_L06_001B1AC4 * 0.0166666675f);
    velocity[1] = func_00283198(*(float *)(a0 + 0xF8)) * func_002A7878(D_L06_001B1AC0 * 0.0166666675f, D_L06_001B1AC4 * 0.0166666675f);
    velocity[2] = 0;
    velocity[2] = func_002A7878(D_L06_001B1AC8 * 0.0166666675f, D_L06_001B1ACC * 0.0166666675f);
    func_L06_0037E6B0(pos, velocity, D_L06_001B1AE4, 0.5f, 50.4f);
    func_L06_0037E6B0(pos, velocity, D_L06_001B1AE4, 0.5f, 50.4f);
    if (func_002A77E0(D_L06_001B1AE8) != 1) {
    velocity[0] = func_00283180(*(float *)(a0 + 0xF8)) * func_002A7878(D_L06_001B1AC0 * 0.0166666675f, D_L06_001B1AC4 * 0.0166666675f);
    velocity[1] = func_00283198(*(float *)(a0 + 0xF8)) * func_002A7878(D_L06_001B1AC0 * 0.0166666675f, D_L06_001B1AC4 * 0.0166666675f);
    velocity[2] = 0;
    velocity[2] = func_002A7878(D_L06_001B1AC8 * 0.0166666675f, D_L06_001B1ACC * 0.0166666675f);
        func_L06_0037E6B0(pos, velocity, D_L06_001B1AE0, 0.5f, 50.4f);
    }
    if (func_002A77E0(D_L06_001B1AE8) != 1) {
    velocity[0] = func_00283180(*(float *)(a0 + 0xF8)) * func_002A7878(D_L06_001B1AD0 * 0.0166666675f, D_L06_001B1AD4 * 0.0166666675f);
    velocity[1] = func_00283198(*(float *)(a0 + 0xF8)) * func_002A7878(D_L06_001B1AD0 * 0.0166666675f, D_L06_001B1AD4 * 0.0166666675f);
    velocity[2] = 0;
    velocity[2] = func_002A7878(D_L06_001B1AD8 * 0.0166666675f, 0.0300000012f);
        func_L06_0037E6B0(pos, velocity, D_L06_001B1AE0, 0.75f, 50.4f);
    }
    if (func_002A77E0(D_L06_001B1AE8) == 1) {
    velocity[0] = func_00283180(*(float *)(a0 + 0xF8)) * func_002A7878(D_L06_001B1AD0 * 0.0166666675f, D_L06_001B1AD4 * 0.0166666675f);
    velocity[1] = func_00283198(*(float *)(a0 + 0xF8)) * func_002A7878(D_L06_001B1AD0 * 0.0166666675f, D_L06_001B1AD4 * 0.0166666675f);
    velocity[2] = 0;
    velocity[2] = func_002A7878(D_L06_001B1AD8 * 0.0166666675f, D_L06_001B1ADC * 0.0166666675f);
        func_L06_0037E6B0(pos, velocity, D_L06_001B1AE0, 0.75f, 50.4f);
    }
}
