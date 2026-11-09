#include "common.h"

extern int func_001163B0(void);

extern int func_002A7820(int, int);

extern void func_002A7750(void *, int, int);

extern void func_L01_003BFDC8(void *, int, int, int);

extern void func_00282978(void *);

extern void func_002AB8C0(void *, void *);

extern void func_002B0990(void *, void *, int, int, float);

/* Small data reached through $gp: these are only one instruction at -G8. */
extern unsigned short D_L01_001AFED4 __attribute__((sda));

extern unsigned short D_L01_001AFED8 __attribute__((sda));

extern unsigned short D_L01_001AFEDC __attribute__((sda));

extern float D_L01_001AFEFC __attribute__((sda));

typedef struct L01_003C0760_OWNED {
    char pad0[0x2DC];
    unsigned short f2DC;
} L01_003C0760_OWNED;

typedef struct L01_003C0760_OBJ {
    char pad0[0x68];
    L01_003C0760_OWNED *f68;
} L01_003C0760_OBJ;

void func_L01_003C0760(L01_003C0760_OBJ *a0)
{
    L01_003C0760_OBJ *p = a0;
    L01_003C0760_OWNED *q = p->f68;
    int r = func_002A7820(7, 12);

    func_L01_003BFDC8(p, 8, 0, r);
    func_002A7750(p, 3, 3);
    q->f2DC = D_L01_001AFED4;
}

typedef struct L01_003C07C8_OWNED {
    char pad0[0x2DA];
    unsigned short f2DA;
} L01_003C07C8_OWNED;

typedef struct L01_003C07C8_OBJ {
    char pad0[0x68];
    L01_003C07C8_OWNED *f68;
} L01_003C07C8_OBJ;

void func_L01_003C07C8(L01_003C07C8_OBJ *a0)
{
    L01_003C07C8_OBJ *p = a0;
    L01_003C07C8_OWNED *q = p->f68;
    int r = func_002A7820(9, 11);

    func_L01_003BFDC8(p, 13, 0, r);
    func_002A7750(p, 2, 3);
    q->f2DA = D_L01_001AFED8;
}

typedef struct L01_003C0830_OWNED {
    char pad0[0x2DE];
    unsigned short f2DE;
} L01_003C0830_OWNED;

typedef struct L01_003C0830_OBJ {
    char pad0[0x68];
    L01_003C0830_OWNED *f68;
    char pad1[0x9C - 0x6C];
    int f9C;
} L01_003C0830_OBJ;

void func_L01_003C0830(L01_003C0830_OBJ *a0)
{
    L01_003C0830_OBJ *p = a0;
    L01_003C0830_OWNED *q = p->f68;
    int r = func_002A7820(7, 11);

    func_L01_003BFDC8(p, 14, 0, r);
    func_002A7750(p, 4, 3);
    p->f9C = p->f9C | 0x30;
    q->f2DE = D_L01_001AFEDC;
}

typedef struct L01_003C06E8_OWNED {
    char pad0[0x2DC];
    unsigned short f2DC;
} L01_003C06E8_OWNED;

typedef struct L01_003C06E8_OBJ {
    char pad0[0x68];
    L01_003C06E8_OWNED *f68;
} L01_003C06E8_OBJ;

void func_L01_003C06E8(L01_003C06E8_OBJ *a0)
{
    L01_003C06E8_OBJ *p = a0;
    L01_003C06E8_OWNED *q = p->f68;
    int v = (func_001163B0() & 1) + 6;
    int r = func_002A7820(10, 15);

    func_L01_003BFDC8(p, v, 0, r);
    func_002A7750(p, 1, 3);
    q->f2DC = D_L01_001AFED4;
}

typedef struct L01_003C0140_OWNED {
    char pad0[0x68];
    void *f68;
} L01_003C0140_OWNED;

typedef struct L01_003C0140_OBJ {
    char pad0[0x68];
    L01_003C0140_OWNED *f68;
    char pad1[0x96 - 0x6C];
    unsigned short f96;
} L01_003C0140_OBJ;

void func_L01_003C0140(L01_003C0140_OBJ *a0)
{
    L01_003C0140_OBJ *p = a0;
    L01_003C0140_OWNED *q = p->f68;

    func_002AB8C0(a0, (char *)q + 0x50);
    if (p->f96 <= 0xFFFE) {
        p->f96 = p->f96 + 1;
    }
    func_00282978((char *)q + 0x2DE);
    func_00282978((char *)q + 0x2DA);
    func_00282978((char *)q + 0x2DC);
    func_002B0990(p, (char *)q + 0x220, 10, 1, D_L01_001AFEFC);
}

/* Oozla debris update. */
extern int func_00282948(void *);
extern void func_0029F338(void *);
extern int func_00283CF0(float);
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern float func_00283180(float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern float D_L01_001AFE30 __attribute__((sda));
extern char D_L01_001BF920[];

void func_L01_003BCEC8(char *obj)
{
    char *s = *(char **)(obj + 0x68);
    float pos[4] __attribute__((aligned(16)));
    float saved, scale, tilt;

    qcopy(pos, obj + 0x10);
    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        func_0029F338(obj);
        return;
    case 1:
        if (func_00282948(s + 0x30)) {
            *(unsigned char *)(obj + 0x20) = 2;
            *(int *)(s + 0x30) = func_00283CF0(10.0f);
            *(unsigned short *)(obj + 0x34) |= 0x2000;
            return;
        }
        break;
    case 2:
        if (func_00282948(s + 0x30)) {
            func_0029F338(obj);
            return;
        }
        /* Fade while the removal timer runs. */
        *(unsigned char *)(obj + 0x23) = func_00283CF0((float)*(int *)(s + 0x30) * 12.8f);
        break;
    }
    *(float *)(s + 0x40) = func_00283B98(*(float *)(s + 0x40), 0.034906592f);
    *(float *)(obj + 0xF8) = func_00283B98(*(float *)(obj + 0xF8),
                                           *(float *)(s + 0x18) * func_00283198(*(float *)(s + 0x40)));
    *(float *)(obj + 0xF0) += (*(float *)(s + 0x44) - *(float *)(obj + 0xF0)) * 0.02f;
    if (*(unsigned char *)(obj + 0x20) != 2) {
        tilt = func_00283180(*(float *)(s + 0x40)) * 0.17453295f;
        scale = D_L01_001AFE30;
        *(float *)(obj + 0xF4) = tilt;
        saved = *(float *)(s + 8);
        *(float *)(s + 8) = 0.0f;
        func_00282D30(s, s, scale);
        *(float *)(s + 8) = saved;
        func_00282CC0(obj + 0x10, obj + 0x10, s);
        *(float *)(s + 8) -= *(float *)(s + 0x38);
        if (*(float *)(s + 8) < *(float *)(s + 0x3C))
            *(float *)(s + 8) = *(float *)(s + 0x3C);
    } else {
        *(float *)(obj + 0xF4) += (0.17453295f - *(float *)(obj + 0xF4)) * 0.1f;
    }
    pos[2] += 1.0f;
    if (func_002761F8(pos, obj + 0x10, 2, obj, 0)) {
        qcopy(obj + 0x10, D_L01_001BF920);
        /* qzero(state + 8): retail passes a misaligned pointer here (original bug; sq ignores the low four address bits). Allowed by owner ruling (2026-11-09). */
        qzero(s + 8);
        *(int *)(s + 0x38) = 0;
        qzero(s + 0x10);
        if (*(unsigned char *)(obj + 0x20) != 2) {
            *(unsigned char *)(obj + 0x20) = 2;
            *(int *)(s + 0x30) = func_00283CF0(10.0f);
            *(unsigned short *)(obj + 0x34) |= 0x2000;
        }
    }
}
