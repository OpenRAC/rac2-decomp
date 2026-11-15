/* Update the oscillating effect parameter and submit a complete 144-byte quad packet.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float D_L23_001AFA18 __attribute__((sda));
extern float D_L23_001AFA1C __attribute__((sda));
extern float D_L23_001AFA20 __attribute__((sda));
extern int D_L23_001AFA24 __attribute__((sda));
extern int D_L23_001AFA28 __attribute__((sda));
extern int D_L23_001AFA2C __attribute__((sda));
extern int D_L23_001AFA30 __attribute__((sda));
extern int D_L23_001AFA34 __attribute__((sda));
extern int D_L23_001AFA38 __attribute__((sda));
extern float D_L23_001AFA3C __attribute__((sda));
extern float D_L23_001AFA40 __attribute__((sda));
extern float D_L23_001AFA44 __attribute__((sda));
extern int D_L23_001AFA48 __attribute__((sda));

extern char D_L23_001BA640[];

extern float func_002A7878(float, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern u64 func_0027C878(int);
extern void func_002FC560(u32, u64);
extern void func_00280B90(void *, int, int);

void func_L23_003C1E88(char *obj) {
    TI128 vE0;
    TI128 vD0;
    TI128 vC0;
    TI128 vB0;
    TI128 vA0;
    TI128 v90;
    char q[0x90] __attribute__((aligned(16)));
    char *state = *(char **)(obj + 0x68);
    TI128 *p90;
    TI128 *pB0;
    char *o10;
    char *oE0;
    float f20;
    float f;
    float lim;
    u64 x;
    int c;
    float z;
    long long bits;

    if (*(short *)(state + 0x3BC) > 0) {
        f = *(float *)(state + 0x3B8) + func_002A7878(D_L23_001AFA40, D_L23_001AFA44);
        lim = D_L23_001AFA3C;
        *(float *)(state + 0x3B8) = f;
        if (lim < f) {
            *(float *)(state + 0x3B8) = lim;
            *(short *)(state + 0x3BC) = -1;
        }
    } else {
        f = *(float *)(state + 0x3B8) - func_002A7878(D_L23_001AFA40, D_L23_001AFA44);
        lim = (float)D_L23_001AFA38;
        *(float *)(state + 0x3B8) = f;
        if (f < lim) {
            *(float *)(state + 0x3B8) = lim;
            *(short *)(state + 0x3BC) = 1;
        }
    }
    p90 = &v90;
    f20 = D_L23_001AFA18;
    qcopy(p90, obj + 0x10);
    o10 = obj + 0x10;
    FastVecSub(&vA0, *(char **)(state + 0x2A0) + 0x10, o10);
    FastVecScale(&vA0, &vA0, D_L23_001AFA1C);
    FastVecAdd(&vA0, &vA0, p90);
    oE0 = obj + 0xE0;
    pB0 = &vB0;
    qcopy(pB0, oE0);
    FastVecSub(&vC0, p90, D_L23_001BA640);
    FastVecCross(&vD0, pB0, &vC0);
    vec_scale_to_length(&vD0, &vD0, f20);
    vec_scale_to_length(&vE0, &vC0, -D_L23_001AFA20);
    FastVecAdd(p90, p90, &vE0);
    FastVecAdd(&vA0, &vA0, &vE0);
    FastVecAdd(q + 0x00, p90, &vD0);
    FastVecSub(q + 0x10, p90, &vD0);
    FastVecAdd(q + 0x20, &vA0, &vD0);
    FastVecSub(q + 0x30, &vA0, &vD0);
    x = GetEffectTextureDescriptor(D_L23_001AFA24);
    c = D_L23_001AFA48;
    *(int *)(q + 0x4C) = c;
    *(u64 *)(q + 0x78) = x;
    *(unsigned long long *)(q + 0x80) = 0xFF9000000260ULL;
    *(u64 *)(q + 0x70) = 0;
    *(int *)(q + 0x48) = c;
    *(int *)(q + 0x44) = c;
    *(int *)(q + 0x40) = c;
    VU1_addGSregister(0x47, 0x53001);
    bits = D_L23_001AFA28;
    bits |= (long long)D_L23_001AFA2C << 2;
    bits |= (long long)D_L23_001AFA30 << 4;
    bits |= (long long)D_L23_001AFA34 << 6;
    bits |= (long long)(int)*(float *)(state + 0x3B8) << 32;
    *(int *)(q + 0x54) = 0;
    *(float *)(q + 0x5C) = 1.0f;
    *(int *)(q + 0x50) = 0;
    *(long long *)(q + 0x88) = bits;
    *(int *)(q + 0x64) = 0;
    z = *(float *)(q + 0x50);
    *(float *)(q + 0x68) = z;
    *(float *)(q + 0x6C) = 1.0f;
    *(float *)(q + 0x60) = z;
    *(float *)(q + 0x58) = 0.99f;
    *(float *)(q + 0x50) = 0.99f;
    draw_world_quad(q, 0, 0);
}
