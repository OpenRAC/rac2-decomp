#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned int u32;
typedef short s16;
typedef int s32;
typedef unsigned short u16;

typedef struct {
    s32 pad0;
    s32 pad1;
    s32 pad2;
    s32 fieldC;
} L06Entry;

extern L06Entry D_L06_00139A28[];

extern s32 func_L01_003246F8();

extern u8 D_001A7BC8[] __attribute__((sda));
extern u8 D_001A7BE0 __attribute__((sda));
extern char D_00189EA0[];
extern int D_L06_001B2348 __attribute__((sda));
extern void func_002A7750(void *, int, int);
extern float func_00282E80(void *, void *);
extern float func_00282DF0(void *);
extern void func_002AD7B8(int);
extern float func_002AA2E8(float *, float, float);
extern void func_L00_002E6CF0(void *, void *);
extern void func_L06_003E1040(void);
extern int func_00282948(int *);
extern void func_0029F338(void *);
extern void func_00282F20(void *, void *, float);


typedef struct { float point[4][4]; u32 color[4]; float uv[8]; unsigned long tag[4]; } L06Quad;
extern void func_002FC560(int, unsigned long);
extern void func_00281DE8(void *, int, int, int);
extern void func_L01_0031A278(void *, void *, float, float, float);
extern void func_00280B90(void *, int, int);

/* func_L06_0035EA68 is defined in L06_0035EA68-fall.c. */

void func_L06_0036F728(s32 a0, s32 a1) {
    s32 v1 = func_L01_003246F8(a0);
    if (v1 != -1)
        D_L06_00139A28[v1].fieldC = a1;
}

INCLUDE_ASM("asm/levels", func_L06_00382608);

extern float func_00282E48(char *, char *);
extern float func_00282C48(float);

s32 func_L06_00382850(char *a0, char *a1, float f12) {
    s32 i;
    s32 best = 0;
    float best_val = 1.0e11f;
    float base = f12;

    for (i = 0; i < *(s32 *)a1; i++) {
        float v = func_00282E48(a1 + 0x10 + i * 0x10, a0);
        if (func_00282C48(v - base) < best_val) {
            best_val = v;
            best = i;
        }
    }
    return best;
}


extern void ref_L06_0039A2F0_00(void *, s32, s32);

void func_L06_0039A2F0(s32 a0, s32 a1, s32 a2, s32 a3, s32 *list)
{
    char *shot;
    s32 count;
    s32 score;
    s32 tag = a3;
    s16 d;
    s16 fc = *(s16 *)(a2 + 0xB2);
    s16 fa = *(s16 *)(a2 + 0xAA);

    if (a3 == 1)
        d = (s16)(a0 - a2);
    else
        d = (s16)(a0 - *(u16 *)(a2 + 0x68));

    for (score = 0; score < list[0]; score++) {
        char *entry = (char *)list + 4 + score * 16;
        if (*(s32 *)entry != d) continue;
        if (*(u16 *)(entry + 8) != a1) continue;
        if (fc != *(s16 *)(entry + 0xC)) continue;
        if (fa != *(s16 *)(entry + 0xE)) continue;
        tag = *(s16 *)(entry + 0xA);
        if (tag != 0) {
            ref_L06_0039A2F0_00(entry + 4, a0, a1);
            return;
        }
    }
    count = list[0];
    shot = (char *)list + 4 + count * 16;
    list[0] = count + 1;
    *(s32 *)shot = d;
    ref_L06_0039A2F0_00(shot + 4, a0, a1);
    *(u16 *)(shot + 8) = a1;
    *(s16 *)(shot + 0xA) = tag;
    *(s16 *)(shot + 0xC) = fc;
    *(s16 *)(shot + 0xE) = fa;
}

void func_L06_003E0D88(u8 *moby)
{
    char *st = *(char **)(moby + 0x68);
    float scale, inverse;
    switch ((u8)moby[0x20]) {
    case 0:
        moby[0x30] = 0xFF;
        if (!D_001A7BC8[*(int *)st]) func_002A7750(moby, 1, -1);
        else func_0029F338(moby);
        break;
    case 1:
        if (func_00282E80(moby + 0x10, D_00189EA0) < 2.0f &&
            func_00282C48(*(float *)(moby + 0x18) - *(float *)(D_00189EA0 + 8)) < 2.0f) {
            func_002AD7B8(*(int *)st);
            func_002A7750(moby, 2, -1);
            *(u16 *)(moby + 0x34) |= 0x100;
            *(int *)(st + 8) = 180;
        }
        if (*(int *)st == 24 && D_001A7BE0) {
            func_002AD7B8(24);
            func_002A7750(moby, 2, -1);
            *(u16 *)(moby + 0x34) |= 0x100;
            *(int *)(st + 8) = 180;
        }
        break;
    case 2:
        if ((*(u16 *)(moby + 0x34) ^ 1) & 1) {
            scale = func_00282DF0(moby + 0xC0);
            func_002AA2E8(&scale, 0, 0.06666667014360428f);
            inverse = 2.0f - scale;
            func_00282F20(moby + 0xC0, moby + 0xC0, scale);
            func_00282F20(moby + 0xD0, moby + 0xD0, scale);
            func_00282F20(moby + 0xE0, moby + 0xE0, inverse);
            if (scale <= 0) {
                moby[0x31] = 0;
                *(u16 *)(moby + 0x34) |= 1;
            }
        }
        func_L00_002E6CF0(func_L06_003E1040, moby);
        if ((D_L06_001B2348 ^ 1) & 1) (*(int *)(st + 4))++;
        if (func_00282948((int *)(st + 8))) {
            func_002AA2E8((float *)(st + 12), 0, 0.05000000447034836f);
            if (*(float *)(st + 12) <= 0) func_0029F338(moby);
        } else {
            func_002AA2E8((float *)(st + 12), 1, 0.05000000447034836f);
        }
        break;
    }
}



s32 func_L06_003E3CC8(u8 *a0) {
    if (*(s16 *)(a0 + 0xAA) != 0x330)
        return 0;
    return (u32)(a0[0x20] - 2) < 5;
}







extern char D_L17_001FE880[];
extern char D_L17_00296F80[];
extern u8 D_00189E20[];
extern void func_00283098(void *, void *, void *);
extern void func_2EEEB8(void *, void *, void *);

/* Same body as func_L17_003C3250, with this function's own callees. */
void func_L06_003E4FA0(char *a2)
{
    char *s5;
    char *s0;
    char *s2;
    char *s4;
    char *s3;
    char *base;
    int v1;
    int i;

    s5 = *(char **)(a2 + 0x68);
    v1 = *(int *)(s5 + 0xF8);
    if (v1 == -1)
        return;
    v1 = *(int *)(D_L17_001FE880 + v1 * 4);
    if (*(int *)v1 != 7)
        return;
    s3 = a2 + 0xC0;
    s4 = a2 + 0x10;
    s2 = D_L17_00296F80;
    s0 = v1 + 0x10;
    for (i = 6; i >= 0; i--) {
        func_00283098(s0, s2, s3);
        s2 += 0x10;
        func_2EEEB8(s0, s0, s4);
        s0 += 0x10;
    }
    base = D_00189E20;
    *(unsigned short *)(base + 0x24FE) = *(unsigned short *)(s5 + 0xF8);
}



INCLUDE_ASM("asm/levels", func_L06_003E5D30);

/* func_L06_004009B8 is defined in L06_004009B8-g8.c. */

/* func_L06_00402570 is defined in L06_00402570.c. */

INCLUDE_ASM("asm/levels", func_L06_00403130);

/* func_L06_00403710 is defined in L06_00403710-g8.c. */

/* func_L06_00403DA8 is defined in L06_00403DA8.c. */


/* func_L06_00444D00 is defined in L06_00444D00.c. */

/* func_L06_004638F0 is defined in L06_004638F0.c. */


void func_L06_00463FC0(char *moby)
{
    L06Quad q;
    u8 *st = *(u8 **)(moby + 0x68);
    if (st[0x4D]) {
        q.uv[0] = 0; q.uv[1] = 0; q.uv[2] = 0; q.uv[3] = 1;
        q.uv[4] = 1; q.uv[5] = 0; q.uv[6] = 1; q.uv[7] = 1;
    } else {
        q.uv[0] = 0; q.uv[1] = 0; q.uv[2] = 1; q.uv[3] = 0;
        q.uv[4] = 0; q.uv[5] = 1; q.uv[6] = 1; q.uv[7] = 1;
    }
    *(u32 *)(st + 0x58) &= 0xFFFFFF;
    *(u32 *)(st + 0x58) += (u8)moby[0x23] << 24;
    q.color[0] = q.color[1] = q.color[2] = q.color[3] = *(u32 *)(st + 0x58);
    q.tag[0] = 0;
    func_002FC560(0x42, 0x8000000048UL);
    func_002FC560(0x14, 0xFF9000000260UL);
    func_002FC560(0x47, 0x50000);
    func_00281DE8(&q, st[0x4E], 0, 0x80);
    func_L01_0031A278(moby, q.point[0], 0, *(float *)(st + 0x50), -*(float *)(st + 0x54));
    func_L01_0031A278(moby, q.point[1], 0, *(float *)(st + 0x50), *(float *)(st + 0x54));
    func_L01_0031A278(moby, q.point[2], 0, -*(float *)(st + 0x50), -*(float *)(st + 0x54));
    func_L01_0031A278(moby, q.point[3], 0, -*(float *)(st + 0x50), *(float *)(st + 0x54));
    func_00280B90(&q, 0, 0);
    func_00281DE8(&q, st[0x4F], 0, 0x80);
    func_002FC560(0x47, 0x50000);
    func_L01_0031A278(moby, q.point[0], -0.001f, *(float *)(st + 0x50), -*(float *)(st + 0x54));
    func_L01_0031A278(moby, q.point[1], -0.001f, *(float *)(st + 0x50), *(float *)(st + 0x54));
    func_L01_0031A278(moby, q.point[2], -0.001f, -*(float *)(st + 0x50), -*(float *)(st + 0x54));
    func_L01_0031A278(moby, q.point[3], -0.001f, -*(float *)(st + 0x50), *(float *)(st + 0x54));
    func_00280B90(&q, 0, 0);
}

extern s32 D_L06_001B9890;

void func_L06_00475C10(float a0) {
    s32 v1 = D_L06_001B9890;
    if (*(s16 *)(v1 + 0x86) == 0)
        *(float *)(*(s32 *)(v1 + 0x70) + 0x24C) = a0;
}



INCLUDE_ASM("asm/levels", func_L06_0047A408);

/* func_L06_0047AC68 is defined in L06_0047AC68-g8.c. */

INCLUDE_ASM("asm/levels", func_L06_0047C1D0);
