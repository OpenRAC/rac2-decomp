#include "common.h"

/* Own unit: the 32-byte D_L14_001B03B8 table is gp-relative only under -G32. */
typedef int Quad128 __attribute__((mode(TI)));
typedef union { float f[4]; Quad128 q; } Vec;
typedef struct { Vec pos[4]; u32 color[4]; float uv[4][2]; char tail[24]; u64 regs; } DrawPacket;

extern unsigned char *D_L14_001B259C[] __attribute__((sda));
extern unsigned char D_001A7A44[] __attribute__((sda));
extern float D_L14_001B03BC[];
extern float D_L14_001B03B8[8] __attribute__((sda));
extern int D_L14_001B0394 __attribute__((sda));
extern float D_L14_001B039C __attribute__((sda));
extern float D_L14_001B03A0 __attribute__((sda));
extern float D_L14_001B03A4 __attribute__((sda));
extern float D_L14_001B03A8 __attribute__((sda));
extern int D_L14_001B03AC __attribute__((sda));
extern float D_L14_001B03B0 __attribute__((sda));
extern int func_L03_004197A8(void *);
extern void func_00283658(void *, void *);
extern void func_L03_002EFB60(void *, void *, float);
extern void func_00281DE8(void *, int, int, int);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282F20(void *, void *, float);
extern void func_00280B90(void *, void *, int);

void func_L14_003DFA60(char *self) {
    float mtx[16] __attribute__((aligned(16)));
    DrawPacket p __attribute__((aligned(16)));
    int n, i;
    float angle, u, den;
    float *v, *uv, *src, *src2;
    n = func_L03_004197A8(D_L14_001B259C[0] + (*(int *)(*(char **)(self + 0x68) + 4) << 8));
    func_00283658(mtx, self + 0xC0);
    func_L03_002EFB60(mtx, mtx, *(float *)(self + 0x2C) / *(float *)(*(char **)(self + 0x24) + 0x24));
    qcopy(mtx + 12, self + 0x10);
    mtx[15] = 1.0f;
    func_00281DE8(p.pos, D_L14_001B0394, 0, 0x80);
    src = D_L14_001B03BC;
    src2 = D_L14_001B03B8;
    for (i = 0; i < 4; i++, src2 += 2) {
        angle = func_00283B98(D_L14_001B03A0 * 0.01745329424738884f, (float)i * 1.5707964f);
        p.pos[i].f[0] = func_00283180(angle) * D_L14_001B03A4;
        p.pos[i].f[1] = func_00283198(angle) * D_L14_001B03A4;
        p.pos[i].f[2] = 0;
        qzero_nc(&p.pos[i]);
        p.pos[i].f[1] = (i >= 2) ? -1.0f : 1.0f;
        if (i & 1)
            p.pos[i].f[2] = -1.0f;
        else
            p.pos[i].f[2] = 1.0f;
        v = p.pos[i].f;
        if (D_001A7A44[0])
            v[1] = -v[1];
        func_00282F20(v, v, D_L14_001B03A4);
        v[0] = D_L14_001B03A8;
        v[3] = 1.0f;
        v[2] += D_L14_001B03B0;
        p.color[i] = D_L14_001B03AC;
        uv = p.uv[i];
        u = *src2;
        uv[0] = u;
        if (i < 2)
            den = u + (float)n / D_L14_001B039C;
        else
            den = u + (float)(n + 1) / D_L14_001B039C;
        uv[0] = den;
        p.uv[i][1] = *src;
        src += 2;
    }
    func_00280B90(&p, mtx, 0);
}
