#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern int D_L23_001AFA64 __attribute__((sda));
extern char D_00189EA0[];
extern void func_0029FCC0(void *, int, void *);
extern void func_002AF1D0(void *, void *, int, int);
extern void func_0029FC20(void *, int, void *);
extern void func_00283098(void *, void *, void *);
extern float func_002B04E0(void *, void *, int);
extern float func_002AAA00(void *, float, float, float, float, void *, int);
extern void func_002833F0(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_PAL_002A0F68(void *);
extern void func_002A0F48(void *);
extern void func_00282D30(void *, void *, float);
extern void func_002B0408(void *, void *, void *);
extern int func_00282978(short *);
extern void func_00282CF0(void *, void *, void *);

extern float D_L23_001B36A4 MACRO_ADDR;
extern int D_L23_001AFA54 __attribute__((sda));
extern TI128 D_L23_001C0AA0[];
extern char D_00189ED0[];
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern void func_L22_002F3B38(void *, void *, void *);
extern int func_002761F8(void *, void *, int, int, int);

#define F(i, k) (((float *)&loc[i])[k])

/* func_PAL_L23_003C4CE8, the PAL copy of func_L23_003C1420: the same C, with the follow timer scaled to 50 Hz. */
int func_PAL_L23_003C4CE8(char *obj) {
    TI128 loc[8];
    char *state = *(char **)(obj + 0x68);
    int r;
    TI128 *pg;
    TI128 *pl;
    TI128 *ps;
    TI128 *pd;

    loc[1] = 0;
    F(1, 2) = *(float *)(state + 0x54) + *(float *)(state + 0x50);
    loc[2] = 0;
    F(2, 0) = 4.0f;
    loc[0] = loc[1];
    r = func_002A77E0(8);
    F(2, 1) = (float)r * 0.4285714626f + -1.5f;
    F(2, 2) = *(float *)(state + 0x54) + *(float *)(state + 0x50);
    loc[1] = loc[2];
    func_00282D30(&loc[0], obj + 0xE0, F(0, 2));
    func_00282CC0(&loc[0], &loc[0], obj + 0x10);
    func_00283098(&loc[1], &loc[1], obj + 0xC0);
    func_00282CC0(&loc[1], &loc[1], obj + 0x10);
    if (func_002761F8(&loc[0], &loc[1], 0x12, 0, 0) != 0) {
    pg = &D_L23_001C0AA0[2];
    pl = &loc[2];
    qcopy(pl, pg);
    loc[5] = 0;
    F(5, 0) = 0.0009765625f;
    F(5, 1) = 0.0009765625f;
    F(5, 2) = 0.0009765625f;
    func_L22_002F3B38(pl, pl, &loc[5]);
    pg -= 2;
    func_00282F20(pl, pl, 1.0f);
    func_00282CF0(&loc[3], &loc[0], pg);
    { float d = func_00282DB0(&loc[3], pl);
    func_00282D30(&loc[4], pl, d); }
    func_00282CF0(&loc[6], &loc[3], &loc[4]);
    func_00282F20(&loc[6], &loc[6], -30.0f);
    ps = (TI128 *)(state + 0x2D0);
    func_00282CC0(ps, obj + 0x10, &loc[6]);
    pd = &loc[7];
    func_00282CF0(pd, ps, D_00189ED0);
    func_00282F20(pd, pd, D_L23_001B36A4);
    func_00282CC0(pd, pd, D_00189ED0);
    qcopy(ps, pd);
    r = D_L23_001AFA54;
    *(short *)(state + 0x26C) = 1;
    *(unsigned short *)(state + 0x26E) = ((s32)(D_L23_001AFA54 + func_002A7820(-r / 2, r / 2)) * 5 + 2) / 6;
    func_00282F20(pl, pl, 10.0f);
    func_00282CC0(pl, pl, pg);
    return 1;
    }
    return 0;
}

void func_PAL_L23_003C4FC0(char *obj) {
    TI128 v0[1], v1[3], t[1], u[1], r3[3], r4[1];
    float fz0, fz1;
    char *state = *(char **)(obj + 0x68);
    float r;
    float a1;
    float b1;
    float c1;

    if (*(unsigned char *)(obj + 0x95) == 2 || *(short *)(state + 0x2A6) != 0)
        func_0029FCC0(obj, 1, *(char **)(state + 0x2A0) + 0x10);
    else
        func_002AF1D0(obj, *(char **)(state + 0x2A0), 1, 0);
    if (*(unsigned char *)(obj + 0x95) == 2) {
        if (*(short *)(state + 0x2A6) == 0)
            *(int *)(state + 0x2AC) = 0;
        func_00282CF0(v0, D_00189EA0, *(char **)(state + 0x2A0) + 0x10);
        r = func_002B04E0(*(char **)(state + 0x2A0), v0, 0);
        b1 = *(float *)(state + 0x68) + *(float *)(state + 0x68);
        a1 = *(float *)(state + 0x64);
        c1 = *(float *)(state + 0x6C);
        fz0 = 0;
        func_002AAA00(&fz0, r, a1, b1, c1, state + 0x2AC, 0);
        qzero_nc(t);
        ((float *)t)[2] = *(float *)(state + 0x2AC);
        func_002833F0(v1, t);
        func_00283738(*(char **)(state + 0x2A0) + 0xC0, *(char **)(state + 0x2A0) + 0xC0, v1);
        func_PAL_002A0F68(*(char **)(state + 0x2A0));
        *(unsigned short *)(*(char **)(state + 0x2A0) + 0x34) |= 0x106;
        func_002A0F48(*(char **)(state + 0x2A0));
        func_00282D30(u, state + 0x280, -1.0f);
        func_002B0408(*(char **)(state + 0x2A0) + 0xC0, u, 0);
        *(short *)(state + 0x2A6) = ((s32)(D_L23_001AFA64) * 5 + 2) / 6;
        return;
    }
    {
        short v = *(short *)(state + 0x2A6);

        if (v != 0) {
            if (v == ((s32)(D_L23_001AFA64) * 5 + 2) / 6)
                *(int *)(state + 0x2AC) = 0;
            *v0 = 0;
            ((float *)v0)[0] = 1.0f;
            ((float *)v0)[3] = 1.0f;
            func_0029FC20(obj, 1, v1);
            qzero_nc(t);
            func_00283098(v0, v0, v1);
            r = func_002B04E0(*(char **)(state + 0x2A0), v0, 0);
            a1 = *(float *)(state + 0x64) + *(float *)(state + 0x64);
            c1 = *(float *)(state + 0x6C);
            b1 = *(float *)(state + 0x68) * 4.0f;
            fz1 = 0;
            func_002AAA00(&fz1, r, a1, b1, c1, state + 0x2AC, 0);
            qzero_nc(u);
            ((float *)u)[2] = *(float *)(state + 0x2AC);
            func_002833F0(r3, u);
            func_00283738(*(char **)(state + 0x2A0) + 0xC0, *(char **)(state + 0x2A0) + 0xC0, r3);
            func_PAL_002A0F68(*(char **)(state + 0x2A0));
            *(unsigned short *)(*(char **)(state + 0x2A0) + 0x34) |= 0x106;
            func_002A0F48(*(char **)(state + 0x2A0));
            func_00282D30(r4, state + 0x280, -1.0f);
            func_002B0408(*(char **)(state + 0x2A0) + 0xC0, r4, 0);
            func_00282978((short *)(state + 0x2A6));
        }
    }
}
