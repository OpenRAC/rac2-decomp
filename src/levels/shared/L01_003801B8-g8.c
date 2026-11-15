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

extern void euler_rotation_basis(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern long GetEffectTextureDescriptor(int);
extern void draw_world_quad(void *, int, int);

void DrawVendorEffects(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    BeamQuad beam_quad;
    long prim_tag[4];
    float q[4][4];
    float euler[4];
    float mtx[3][4];
    char *cam_block, *cam_block_again;
    float scroll;
    int k, i0, i1, i2, i3, glow_color;
    float *q0, *q1, *q2, *q3;

    cam_block = D_L01_001B9380;
    euler[2] = *(float *)(cam_block + 0x158);
    euler[0] = 0.0f;
    euler[1] = 0.0f;
    euler_rotation_basis(mtx, euler);

    D_L01_001AEF20 = D_L01_001AEF20 + 0.01f;
    if (1.0f < D_L01_001AEF20) {
        D_L01_001AEF20 = D_L01_001AEF20 - 1.0f;
    }

    prim_tag[2] = 1;
    prim_tag[3] = 0x4000000044L;
    prim_tag[0] = 0;
    prim_tag[1] = GetEffectTextureDescriptor(0x18);

    q0 = q[0];
    q1 = q[1];
    q2 = q[2];
    q3 = q[3];
    for (k = 0; k < 4; k++) {
        matrix_mul_vec3(q0, D_L01_00290030[D_L01_001AEEE0[k][0]], mtx);
        matrix_mul_vec3(q1, D_L01_00290030[D_L01_001AEEE4[k][0]], mtx);
        matrix_mul_vec3(q2, D_L01_00290030[D_L01_001AEEE8[k][0]], mtx);
        matrix_mul_vec3(q3, D_L01_00290030[D_L01_001AEEEC[k][0]], mtx);

        beam_quad.v[0][0] = *(float *)(moby + 0x10) + q[0][0] * *(float *)(vars + 0x90);
        beam_quad.v[0][1] = *(float *)(moby + 0x14) + q[0][1] * *(float *)(vars + 0x90);
        beam_quad.v[0][2] = *(float *)(moby + 0x18) + q[0][2] - 1.0f;
        beam_quad.v[1][0] = *(float *)(moby + 0x10) + q[1][0] * *(float *)(vars + 0x90);
        beam_quad.v[1][1] = *(float *)(moby + 0x14) + q[1][1] * *(float *)(vars + 0x90);
        beam_quad.v[1][2] = *(float *)(moby + 0x18) + q[1][2] - 1.0f;
        beam_quad.v[2][0] = *(float *)(moby + 0x10) + q[2][0] * *(float *)(vars + 0x90);
        beam_quad.v[2][1] = *(float *)(moby + 0x14) + q[2][1] * *(float *)(vars + 0x90);
        beam_quad.v[2][2] = *(float *)(moby + 0x18) + q[2][2] - 1.0f;
        beam_quad.v[3][0] = *(float *)(moby + 0x10) + q[3][0] * *(float *)(vars + 0x90);
        beam_quad.v[3][1] = *(float *)(moby + 0x14) + q[3][1] * *(float *)(vars + 0x90);
        beam_quad.v[3][2] = *(float *)(moby + 0x18) + q[3][2] - 1.0f;

        i0 = D_L01_001AEEE0[k][0];
        i1 = D_L01_001AEEE4[k][0];
        i2 = D_L01_001AEEE8[k][0];
        i3 = D_L01_001AEEEC[k][0];
        scroll = D_L01_001AEF20;
        {
            u32 o = i0 * 4;

            if (*(int *)(vars + 0x94) == 2)
                o += 36;
            beam_quad.col[0] = *(int *)((char *)D_L01_00290108 + o);
        }
        {
            u32 o = i1 * 4;

            if (*(int *)(vars + 0x94) == 2)
                o += 36;
            beam_quad.col[1] = *(int *)((char *)D_L01_00290108 + o);
        }
        {
            u32 o = i2 * 4;

            if (*(int *)(vars + 0x94) == 2)
                o += 36;
            beam_quad.col[2] = *(int *)((char *)D_L01_00290108 + o);
        }
        {
            u32 o = i3 * 4;

            if (*(int *)(vars + 0x94) == 2)
                o += 36;
            beam_quad.col[3] = *(int *)((char *)D_L01_00290108 + o);
        }
        beam_quad.uv[0][0] = D_L01_002900C0[i0][0];
        beam_quad.uv[0][1] = D_L01_002900C0[i0][1] + scroll;
        beam_quad.uv[1][0] = D_L01_002900C0[i1][0];
        beam_quad.uv[1][1] = D_L01_002900C0[i1][1] + scroll;
        beam_quad.uv[2][0] = D_L01_002900C0[i2][0];
        beam_quad.uv[2][1] = D_L01_002900C0[i2][1] + scroll;
        beam_quad.uv[3][0] = D_L01_002900C0[i3][0];
        beam_quad.uv[3][1] = D_L01_002900C0[i3][1] + scroll;
        draw_world_quad(&beam_quad, 0, 1);
    }

    prim_tag[1] = GetEffectTextureDescriptor(0x1B);

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

        t0.f[0] = n * (*(float *)(vars + 0x90) * 1.2f);
        t0.f[1] = n * (*(float *)(vars + 0x90) * 1.2f);
        t0.f[2] = z;
        t1.q = 0;
        t1.f[0] = pp * (*(float *)(vars + 0x90) * 1.2f);
        t1.f[1] = n * (*(float *)(vars + 0x90) * 1.2f);
        t1.f[2] = zz;
        t2.q = 0;
        t2.f[0] = n * (*(float *)(vars + 0x90) * 1.2f);
        t2.f[1] = pp * (*(float *)(vars + 0x90) * 1.2f);
        t2.f[2] = z;
        t3.q = 0;
        t3.f[0] = pp * (*(float *)(vars + 0x90) * 1.2f);
        t3.f[1] = pp * (*(float *)(vars + 0x90) * 1.2f);
        t3.f[2] = zz;
        c[0].q = t0.q;
        c[1].q = t1.q;
        c[2].q = t2.q;
        c[3].q = t3.q;

        cam_block_again = D_L01_001B9380;
        rz = *(float *)(cam_block_again + 0x158);
        euler[0] = 0.0f;
        euler[2] = rz;
        euler[1] = 0.0f;
        euler_rotation_basis(mtx, euler);
        matrix_mul_vec3(q0, &c[0], mtx);
        matrix_mul_vec3(q1, &c[1], mtx);
        matrix_mul_vec3(q2, &c[2], mtx);
        matrix_mul_vec3(q3, &c[3], mtx);
    }

    glow_color = ((int)((1.0f - D_L01_001AEF24) * 128.0f) << 24) | 0x808080;
    beam_quad.v[0][0] = *(float *)(moby + 0x10) + q[0][0];
    beam_quad.v[0][1] = *(float *)(moby + 0x14) + q[0][1];
    beam_quad.v[0][2] = *(float *)(moby + 0x18) + q[0][2] - 1.0f;
    beam_quad.v[1][0] = *(float *)(moby + 0x10) + q[1][0];
    beam_quad.v[1][1] = *(float *)(moby + 0x14) + q[1][1];
    beam_quad.v[1][2] = *(float *)(moby + 0x18) + q[1][2] - 1.0f;
    beam_quad.v[2][0] = *(float *)(moby + 0x10) + q[2][0];
    beam_quad.v[2][1] = *(float *)(moby + 0x14) + q[2][1];
    beam_quad.v[2][2] = *(float *)(moby + 0x18) + q[2][2] - 1.0f;
    beam_quad.v[3][0] = *(float *)(moby + 0x10) + q[3][0];
    beam_quad.v[3][1] = *(float *)(moby + 0x14) + q[3][1];
    beam_quad.v[3][2] = *(float *)(moby + 0x18) + q[3][2] - 1.0f;
    beam_quad.col[0] = glow_color;
    beam_quad.col[1] = glow_color;
    beam_quad.col[2] = glow_color;
    beam_quad.col[3] = glow_color;
    beam_quad.uv[0][0] = 0.0f;
    beam_quad.uv[0][1] = 0.0f;
    beam_quad.uv[1][0] = 1.0f;
    beam_quad.uv[1][1] = 0.0f;
    beam_quad.uv[2][0] = 0.0f;
    beam_quad.uv[2][1] = 1.0f;
    beam_quad.uv[3][0] = 1.0f;
    beam_quad.uv[3][1] = 1.0f;
    draw_world_quad(&beam_quad, 0, 1);
}
