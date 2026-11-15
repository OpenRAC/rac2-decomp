#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef struct { Quad q; } QuadBox;

typedef struct L01_003C2680_OWNED {
    char pad0[0x68];
    float f68;
    char pad1[0x120 - 0x6C];
    float f120;
    float f124;
    float f128;
    char pad2[0x130 - 0x12C];
    Quad f130;
    Quad f140;
} L01_003C2680_OWNED;

typedef struct L01_003C2680_OBJ {
    char pad0[0x18];
    float f18;
    char pad1[0x20 - 0x1C];
    unsigned char f20;
    char pad2[0x31 - 0x21];
    unsigned char f31;
    char pad3[0x68 - 0x32];
    L01_003C2680_OWNED *f68;
    char pad4[0xAA - 0x6C];
    short fAA;
    char pad5[0xB2 - 0xAC];
    short fB2;
} L01_003C2680_OBJ;

extern void func_002A6CF0(void *, int, int);
extern float func_00282E80(void *, void *);
extern float func_L01_003BAFB0();
extern float func_002A7940(void);
extern void func_002A7750(void *, int, int);
extern void func_002B41A8(void *, void *, int, int, void *, int, int, int, void *, void *, int);
extern void func_002B44C0(void *, void *, int);
extern char D_L01_001B94C0[];
extern float D_L01_001AFF6C __attribute__((sda));
extern long long D_L01_001AFF60 __attribute__((sda));
extern long long D_L01_001AFF50 __attribute__((sda));
extern long long D_L01_001AFF40 __attribute__((sda));
extern char D_L01_002A4C50[];

void func_L01_003C2680(L01_003C2680_OBJ *a0)
{
    char *p = (char *)a0;
    L01_003C2680_OWNED *s1 = a0->f68;
    Quad frame[2];

    if (s1 == 0) {
        func_002A6CF0(D_L01_002A4C50, a0->fAA, a0->fB2);
        return;
    }
    qcopy(&frame[0], p + 0x10);
    qcopy(&frame[1], p + 0xF0);
    switch (a0->f20) {
    case 0:
        if (func_L01_003BAFB0(p + 0x10) > 0.0f) {
            s1->f120 = func_002A7940();
            s1->f124 = func_002A7940();
            s1->f128 = 0.02f;
            qcopy(&s1->f130, p + 0xF0);
            qzero(&s1->f140);
            func_002A7750(a0, 1, -1);
        }
        a0->f18 = a0->f18 + D_L01_001AFF6C;
        func_002B41A8(a0, (char *)s1 + 0x60, 0, 0, &D_L01_001AFF40, 0, 0, 0, &D_L01_001AFF60, &D_L01_001AFF50, 0);
        return;
    case 1:
        if (a0->f31 != 0 && vec_distance_xy(p + 0x10, D_L01_001B94C0) < 32.0f) {
            s1->f68 = func_L01_003BAFB0() + D_L01_001AFF6C;
            func_002B44C0(a0, (char *)s1 + 0x60, 0);
        }
        return;
    }
}
