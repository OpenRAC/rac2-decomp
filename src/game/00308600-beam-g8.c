#include "common.h"
/* Adapted from RAC1 walloper_and_beam_effects.c (OpenRAC, GPL-3.0). */
extern int func_0027C878(int);
extern void func_00282CF0(void*,void*,void*), func_00282DD8(void*,void*,void*), func_00282CC0(void*,void*,void*);
extern float func_00282DF0(void*);
extern void func_00282D30(void*,void*,float), func_00280B90(void*,void*,int), func_002FC560(int,long);
extern float D_001B5340[];
extern int D_001AEE98 __attribute__((sda));
extern int D_001AEE54 __attribute__((sda));
extern int D_001AEE9C __attribute__((sda));
extern int D_001AEE58 __attribute__((sda));
extern float D_001AEE4C __attribute__((sda));
extern int D_001AEE5C __attribute__((sda));
typedef float RW_2BBDE8[4] __attribute__((aligned(16)));
typedef struct { float v[4]; } P_2BBDE8;
typedef struct {
    int c[4];
    float f[8];
    long z4, q0, q1, q2;
} RT_2BBDE8;

/* The EE ABI independently orders integer and floating-point arguments.
 * This interleaving preserves a0-a3 and f12-f14. */
// Draws a ribbon of quads along a polyline, in two passes with edge colouring and a scrolled texture (colours from globals).
void func_0030BBA0(void *m, int a, int b, float sx, float sy, int n, float sz) {
    RW_2BBDE8 q[4];
    RT_2BBDE8 t;
    RW_2BBDE8 q2[4];
    RT_2BBDE8 u;
    RW_2BBDE8 w120, w130, w140, w150, r160, r170, a180, b190, s1A0, s1B0;
    int i, col0, col1;
    float len, len0, len2, l0, l1;
    t.q0 = GetEffectTextureDescriptor(*(int *)&D_001AEE98);
    col0 = *(int *)&D_001AEE54 | (a << 24);
    t.q2 = 0x8000000048L;
    t.q1 = 0xFF9000000260L;
    t.z4 = 0;
    t.c[3] = col0;
    t.c[2] = col0;
    t.c[1] = col0;
    t.c[0] = col0;
    u.q0 = GetEffectTextureDescriptor(*(int *)&D_001AEE9C);
    col1 = *(int *)&D_001AEE58 | (b << 24);
    u.q2 = t.q2;
    u.q1 = t.q1;
    u.z4 = t.z4;
    u.c[3] = col1;
    u.c[2] = col1;
    u.c[1] = col1;
    u.c[0] = col1;
    u.f[0] = 0; u.f[1] = 0; u.f[2] = 0; u.f[3] = 1.0f; u.f[4] = 1.0f; u.f[5] = 0; u.f[6] = 1.0f; u.f[7] = 1.0f;
    t.f[0] = D_001AEE4C;
    t.f[1] = 0;
    t.f[2] = D_001AEE4C;
    t.f[3] = 1.0f;
    t.f[4] = 1.0f + D_001AEE4C;
    t.f[5] = 0;
    t.f[6] = 1.0f + D_001AEE4C;
    t.f[7] = 1.0f;
    FastVecSub(w140, m, D_001B5340);
    FastVecSub(w150, &((P_2BBDE8 *)m)[1], m);
    FastVecCross(w120, w150, w140);
    len0 = FastVecLength(w120);
    if (len0 != 0) len0 = 1.0f / len0;
    FastVecScale(w120, w120, *(float *)&D_001AEE5C * len0);
    FastVecAdd(q[0], m, w120);
    FastVecSub(q[1], m, w120);
    for (i = 1; i < n - 1; i++) {
        FastVecSub(w140, &((P_2BBDE8 *)m)[i], D_001B5340);
        FastVecSub(w150, &((P_2BBDE8 *)m)[i + 1], &((P_2BBDE8 *)m)[i]);
        FastVecCross(w120, w150, w140);
        len = FastVecLength(w120);
        if (len != 0) len = 1.0f / len;
        FastVecScale(w120, w120, *(float *)&D_001AEE5C * len);
        FastVecAdd(q[2], &((P_2BBDE8 *)m)[i], w120);
        FastVecSub(q[3], &((P_2BBDE8 *)m)[i], w120);
        if (i == 1) {
            t.c[1] = *(int *)&D_001AEE54;
            t.c[0] = *(int *)&D_001AEE54;
        } else if (i == n - 2) {
            t.c[3] = *(int *)&D_001AEE54;
            t.c[2] = *(int *)&D_001AEE54;
        } else if (i == 2) {
            t.c[1] = col0;
            t.c[0] = col0;
        }
        draw_world_quad(q, 0, 0);
        qcopy(q[0], q[2]);
        qcopy(q[1], q[3]);
    }
    for (i = 0; i < n - 1; i++) {
        FastVecSub(a180, &((P_2BBDE8 *)m)[i], D_001B5340);
        FastVecSub(b190, &((P_2BBDE8 *)m)[i + 1], D_001B5340);
        l0 = FastVecLength(a180);
        l1 = FastVecLength(b190);
        if (l1 < l0) {
            if (l1 == 0) qcopy(b190, a180);
            else FastVecScale(b190, b190, l0 / l1);
        } else {
            if (l0 == 0) qcopy(a180, b190);
            else FastVecScale(a180, a180, l1 / l0);
        }
        FastVecAdd(r160, D_001B5340, a180);
        FastVecAdd(r170, D_001B5340, b190);
        FastVecSub(w150, r170, r160);
        FastVecScale(s1B0, w150, sz);
        FastVecSub(r160, r160, s1B0);
        FastVecAdd(r170, r170, s1B0);
        FastVecSub(s1A0, D_001B5340, r160);
        FastVecCross(w120, s1A0, w150);
        len2 = FastVecLength(w120);
        if (len2 != 0) len2 = 1.0f / len2;
        FastVecScale(w130, w120, sy * len2);
        FastVecAdd(q2[0], r160, w130);
        FastVecSub(q2[1], r160, w130);
        FastVecAdd(q2[2], r170, w130);
        FastVecSub(q2[3], r170, w130);
        if (i == 0) {
            u.c[1] = *(int *)&D_001AEE58;
            u.c[0] = *(int *)&D_001AEE58;
        } else if (i == n - 2) {
            u.c[3] = *(int *)&D_001AEE58;
            u.c[2] = *(int *)&D_001AEE58;
        } else if (i == 1) {
            u.c[1] = col1;
            u.c[0] = col1;
        }
        draw_world_quad(q2, 0, 0);
    }
    VU1_addGSregister(0x47, 0x5360B);
}
