#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
extern int func_00283CF0(float);
extern void func_L08_00425398(char *);
extern float func_L08_0032EF80(void *, int, int, int, int);
extern void func_L01_003377C8(void *);
extern float func_L08_00425328(void *, float, float, float);
extern int func_L08_003D3D80(void *);
extern void func_0026FEB8(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern int *D_L08_001FE7C0[];
extern char D_L08_001B1BD0[];

/* Fills the 0x68 context with its timing and animation defaults, sets the record's height from
   the sweep below it when the context has none, and updates the shared counters at +0x1F8..+0x200. */
void func_PAL_L08_0042B190(char *a) {
    float v[4];
    char *p = *(char **)(a + 0x68);
    float f;
    *(u8 *)(p + 0x48) = func_00283CF0(40.0f);
    *(u8 *)(p + 0x4A) = func_00283CF0(64.0f);
    *(u8 *)(p + 0x29) = 1;
    qcopy(p + 0x170, a + 0x10);
    *(float *)(p + 0x208) = *(float *)(a + 0xF8);
    func_L08_00425398(a);
    if (*(u8 *)(a + 0x21) != 255 && **(int **)(p + 0x200) != 0x4CB2F) {
        **(int **)(p + 0x1FC) = 0;
        **(int **)(p + 0x1F8) = 0;
        **(int **)(p + 0x200) = 0x4CB2F;
    }
    *(u8 *)(p + 0x20E) = *(u8 *)(a + 0x30);
    *(Quad *)v = *(Quad *)(a + 0x10);
    f = func_L08_0032EF80(v, *(int *)(p + 0x1D0), -1, *(int *)(p + 0x1D4), -1);
    if (f > 0.0f) *(u8 *)(a + 0x30) = func_00283CF0(f + 2.0f);
    *(u8 *)(p + 0x20E) = *(u8 *)(p + 0x20F) = *(u8 *)(a + 0x30);
    *(Quad *)v = *(Quad *)(a + 0x10);
    f = func_L08_0032EF80(v, *(int *)(p + 0x1D8), *(int *)(p + 0x1E0), *(int *)(p + 0x1DC), -1);
    if (f > 0.0f) *(u8 *)(p + 0x20E) = func_00283CF0(f + 2.0f);
    if (*(int *)(p + 0x1E4) != -1) func_L01_003377C8(D_L08_001FE7C0[*(int *)(p + 0x1E4)]);
    *(u8 *)(p + 0x60) = 5;
    *(int *)(p + 0x98) = -1;
    *(u8 *)(p + 0x61) = 8;
    *(u8 *)(p + 0x62) = 8;
    *(u8 *)(p + 0x66) = 10;
    *(u8 *)(p + 0x67) = 11;
    *(float *)(p + 0x6C) = 0.46000004f;
    *(float *)(p + 0x70) = 0.28000003f;
    *(float *)(p + 0x74) = 0.006f;
    *(float *)(p + 0x78) = 0.012f;
    *(float *)(p + 0x7C) = 0.004f;
    *(float *)(p + 0x80) = 2.75f;
    *(float *)(p + 0x84) = 0.0f;
    *(float *)(p + 0x8C) = 0.4f;
    *(u8 *)(p + 0xBC) = 7;
    *(u8 *)(p + 0xBD) = 24;
    *(u8 *)(p + 0xBE) = 6;
    *(u8 *)(p + 0xBF) = 13;
    *(u8 *)(p + 0xC2) = 7;
    *(u8 *)(p + 0xC3) = 14;
    *(u8 *)(p + 0xC6) = 1;
    *(u8 *)(p + 0xC4) = 0;
    *(u8 *)(p + 0xC5) = 0;
    *(u8 *)(p + 0xC7) = 1;
    *(int *)(p + 0xCC) = *(int *)(p + 0x1E4);
    *(u8 *)(p + 0x2E) = 3;
    *(u8 *)(p + 0x28) = 1;
    *(float *)(p + 0x30) = 0.0f;
    *(float *)(p + 0x1F0) = 1.0f;
    qzero_nc(p + 0x190);
    qcopy(p + 0x180, a + 0x10);
    qzero_nc(p + 0x1A0);
    if (*(float *)(p + 0x1C4) == 0.0f) {
        float height = func_L08_00425328(a + 0x10, *(float *)(a + 0x18) + 20.0f, *(float *)(p + 0x90), *(float *)(p + 0x90));
        *(float *)(p + 0x1C4) = height;
        *(float *)(p + 0x1C8) = height <= *(float *)(p + 0x178) ? height : *(float *)(p + 0x178);
    }
    if (*(float *)(p + 0x1C4) > 0.0f) *(float *)(a + 0x18) = *(float *)(p + 0x1C4) - 0.5f;
    *(int *)(p + 0x22C) = func_L08_003D3D80(a);
    *(s16 *)(p + 0x1BE) = 0;
    if (*(u8 *)(p + 0x20C) == 1 || *(u8 *)(p + 0x20C) == 4) {
        func_0026FEB8(D_L08_001B1BD0, *(s16 *)(a + 0xB2), *(u8 *)(p + 0x20C), *(u8 *)(p + 0x20C) + 1);
        *(u8 *)(p + 0x20C) += 1;
    }
    qcopy(p + 0x170, a + 0x10);
    *(u16 *)(a + 0x34) &= 0xEFFF;
    func_002A7750(a, 1, -1);
    if (*(u8 *)(a + 0x43)) func_PAL_002A7E68(a, 0, 0, 2);
    *(int *)(a + 0x98) = 0;
    *(u8 *)(a + 0x31) = 0;
    *(u16 *)(a + 0x34) |= 1;
    *(u8 *)(p + 0x20E) = *(s16 *)(a + 0x32) < *(u8 *)(p + 0x20E) ? *(u8 *)(p + 0x20E) : *(s16 *)(a + 0x32);
    if (*(u8 *)(a + 0x21) != 255) {
        if (*(u8 *)(p + 0x20D) < **(int **)(p + 0x1FC)) *(u8 *)(p + 0x20D) = **(u8 **)(p + 0x1FC);
        **(int **)(p + 0x1FC) += 1;
    }
}
