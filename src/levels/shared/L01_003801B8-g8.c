/*
 * func_L01_003801B8: draw callback of the light-beam moby (RAC1's draw_vendor_effects,
 * func_L00_002A62D0). Draws four scrolling-UV quads of the beam from the corner tables, then
 * a glow quad that grows and fades with D_L01_001AEF24.
 *
 * t0's zero value is written as its initializer: a union initializer expands to a CLOBBER of t0
 * before the zero store. The CLOBBER emits nothing, but sched1 counts it as a memory reference,
 * so the c[3] copy is the first store with more than 32 refs pending and flushes the pending
 * lists (haifa-sched.c sched_analyze_1). That keeps the second camera read below the copies,
 * as retail has it.
 */
#include "common.h"

typedef struct {
    float v[4][4];
    int col[4];
    float uv[4][2];
} BeamQuad;
typedef unsigned int BeamQword __attribute__((mode(TI), aligned(16)));
typedef float BeamVec[4] __attribute__((aligned(16)));
typedef union { BeamVec f; BeamQword q; } BeamGlowCorner;

extern char D_L01_001B9380[];
extern float D_L01_001AEF20 __attribute__((sda));
extern float D_L01_001AEF24 __attribute__((sda));
extern int D_L01_001AEEE0[][4] SDATA(D_L01_001AEEE0);
extern int D_L01_001AEEE4[][4] __attribute__((sda));
extern int D_L01_001AEEE8[][4] __attribute__((sda));
extern int D_L01_001AEEEC[][4] __attribute__((sda));
extern float D_L01_00290030[][4];
extern float D_L01_002900C0[][2];
extern int D_L01_00290108[];

extern void func_002833F0(void *, void *);
extern void func_00283098(void *, void *, void *);
extern long func_0027C878(int);
extern void func_00280B90(void *, int, int);

void func_L01_003801B8(char *m)
{
    char *p = *(char **)(m + 0x68);
    BeamQuad qd;
    long pk[4];
    float q[4][4];
    float d0[4];
    float mtx[3][4];
    char *g, *h;
    float off;
    int k, i0, i1, i2, i3, col;
    float *q0, *q1, *q2, *q3;

    g = D_L01_001B9380;
    d0[2] = *(float *)(g + 0x158);
    d0[0] = 0.0f;
    d0[1] = 0.0f;
    func_002833F0(mtx, d0);

    D_L01_001AEF20 = D_L01_001AEF20 + 0.01f;
    if (1.0f < D_L01_001AEF20) {
        D_L01_001AEF20 = D_L01_001AEF20 - 1.0f;
    }

    pk[2] = 1;
    pk[3] = 0x4000000044L;
    pk[0] = 0;
    pk[1] = func_0027C878(0x18);

    q0 = q[0];
    q1 = q[1];
    q2 = q[2];
    q3 = q[3];
    for (k = 0; k < 4; k++) {
        func_00283098(q0, D_L01_00290030[D_L01_001AEEE0[k][0]], mtx);
        func_00283098(q1, D_L01_00290030[D_L01_001AEEE4[k][0]], mtx);
        func_00283098(q2, D_L01_00290030[D_L01_001AEEE8[k][0]], mtx);
        func_00283098(q3, D_L01_00290030[D_L01_001AEEEC[k][0]], mtx);

        qd.v[0][0] = *(float *)(m + 0x10) + q[0][0] * *(float *)(p + 0x90);
        qd.v[0][1] = *(float *)(m + 0x14) + q[0][1] * *(float *)(p + 0x90);
        qd.v[0][2] = *(float *)(m + 0x18) + q[0][2] - 1.0f;
        qd.v[1][0] = *(float *)(m + 0x10) + q[1][0] * *(float *)(p + 0x90);
        qd.v[1][1] = *(float *)(m + 0x14) + q[1][1] * *(float *)(p + 0x90);
        qd.v[1][2] = *(float *)(m + 0x18) + q[1][2] - 1.0f;
        qd.v[2][0] = *(float *)(m + 0x10) + q[2][0] * *(float *)(p + 0x90);
        qd.v[2][1] = *(float *)(m + 0x14) + q[2][1] * *(float *)(p + 0x90);
        qd.v[2][2] = *(float *)(m + 0x18) + q[2][2] - 1.0f;
        qd.v[3][0] = *(float *)(m + 0x10) + q[3][0] * *(float *)(p + 0x90);
        qd.v[3][1] = *(float *)(m + 0x14) + q[3][1] * *(float *)(p + 0x90);
        qd.v[3][2] = *(float *)(m + 0x18) + q[3][2] - 1.0f;

        i0 = D_L01_001AEEE0[k][0];
        i1 = D_L01_001AEEE4[k][0];
        i2 = D_L01_001AEEE8[k][0];
        i3 = D_L01_001AEEEC[k][0];
        off = D_L01_001AEF20;
        {
            u32 o = i0 * 4;

            if (*(int *)(p + 0x94) == 2)
                o += 36;
            qd.col[0] = *(int *)((char *)D_L01_00290108 + o);
        }
        {
            u32 o = i1 * 4;

            if (*(int *)(p + 0x94) == 2)
                o += 36;
            qd.col[1] = *(int *)((char *)D_L01_00290108 + o);
        }
        {
            u32 o = i2 * 4;

            if (*(int *)(p + 0x94) == 2)
                o += 36;
            qd.col[2] = *(int *)((char *)D_L01_00290108 + o);
        }
        {
            u32 o = i3 * 4;

            if (*(int *)(p + 0x94) == 2)
                o += 36;
            qd.col[3] = *(int *)((char *)D_L01_00290108 + o);
        }
        qd.uv[0][0] = D_L01_002900C0[i0][0];
        qd.uv[0][1] = D_L01_002900C0[i0][1] + off;
        qd.uv[1][0] = D_L01_002900C0[i1][0];
        qd.uv[1][1] = D_L01_002900C0[i1][1] + off;
        qd.uv[2][0] = D_L01_002900C0[i2][0];
        qd.uv[2][1] = D_L01_002900C0[i2][1] + off;
        qd.uv[3][0] = D_L01_002900C0[i3][0];
        qd.uv[3][1] = D_L01_002900C0[i3][1] + off;
        func_00280B90(&qd, 0, 1);
    }

    pk[1] = func_0027C878(0x1B);

    D_L01_001AEF24 = D_L01_001AEF24 + 0.01f;
    if (1.0f < D_L01_001AEF24) {
        D_L01_001AEF24 = 0.0f;
    }

    {
        float ph = D_L01_001AEF24;
        float n = -ph;
        float pp = ph;
        float z = ph * 1.4f + 1.1f;
        float zz = z - 0.2f;
        BeamGlowCorner c[4], t0 = { .q = 0 }, t1, t2, t3;
        float rz;

        t0.f[0] = n * (*(float *)(p + 0x90) * 1.2f);
        t0.f[1] = n * (*(float *)(p + 0x90) * 1.2f);
        t0.f[2] = z;
        t1.q = 0;
        t1.f[0] = pp * (*(float *)(p + 0x90) * 1.2f);
        t1.f[1] = n * (*(float *)(p + 0x90) * 1.2f);
        t1.f[2] = zz;
        t2.q = 0;
        t2.f[0] = n * (*(float *)(p + 0x90) * 1.2f);
        t2.f[1] = pp * (*(float *)(p + 0x90) * 1.2f);
        t2.f[2] = z;
        t3.q = 0;
        t3.f[0] = pp * (*(float *)(p + 0x90) * 1.2f);
        t3.f[1] = pp * (*(float *)(p + 0x90) * 1.2f);
        t3.f[2] = zz;
        c[0].q = t0.q;
        c[1].q = t1.q;
        c[2].q = t2.q;
        c[3].q = t3.q;

        h = D_L01_001B9380;
        rz = *(float *)(h + 0x158);
        d0[0] = 0.0f;
        d0[2] = rz;
        d0[1] = 0.0f;
        func_002833F0(mtx, d0);
        func_00283098(q0, &c[0], mtx);
        func_00283098(q1, &c[1], mtx);
        func_00283098(q2, &c[2], mtx);
        func_00283098(q3, &c[3], mtx);
    }

    col = ((int)((1.0f - D_L01_001AEF24) * 128.0f) << 24) | 0x808080;
    qd.v[0][0] = *(float *)(m + 0x10) + q[0][0];
    qd.v[0][1] = *(float *)(m + 0x14) + q[0][1];
    qd.v[0][2] = *(float *)(m + 0x18) + q[0][2] - 1.0f;
    qd.v[1][0] = *(float *)(m + 0x10) + q[1][0];
    qd.v[1][1] = *(float *)(m + 0x14) + q[1][1];
    qd.v[1][2] = *(float *)(m + 0x18) + q[1][2] - 1.0f;
    qd.v[2][0] = *(float *)(m + 0x10) + q[2][0];
    qd.v[2][1] = *(float *)(m + 0x14) + q[2][1];
    qd.v[2][2] = *(float *)(m + 0x18) + q[2][2] - 1.0f;
    qd.v[3][0] = *(float *)(m + 0x10) + q[3][0];
    qd.v[3][1] = *(float *)(m + 0x14) + q[3][1];
    qd.v[3][2] = *(float *)(m + 0x18) + q[3][2] - 1.0f;
    qd.col[0] = col;
    qd.col[1] = col;
    qd.col[2] = col;
    qd.col[3] = col;
    qd.uv[0][0] = 0.0f;
    qd.uv[0][1] = 0.0f;
    qd.uv[1][0] = 1.0f;
    qd.uv[1][1] = 0.0f;
    qd.uv[2][0] = 0.0f;
    qd.uv[2][1] = 1.0f;
    qd.uv[3][0] = 1.0f;
    qd.uv[3][1] = 1.0f;
    func_00280B90(&qd, 0, 1);
}
