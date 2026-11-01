#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef struct { float u, v; } ScrollLayer;
#define I32(p, o) (*(int *)((p) + (o)))
#define F32(p, o) (*(float *)((p) + (o)))
#define S16(p, o) (*(short *)((p) + (o)))

extern u8 D_00189E20[], D_00189EA0[];
extern float D_001A7928;
extern int D_L09_001C9F80[];
extern Quad D_L09_001B3100 SDATA(D_L09_001B3100);
extern u8 D_L09_001B9A00[];
extern u8 *D_L09_001B294C;
extern ScrollLayer D_L09_001B3110[] MACRO_ADDR;
extern float D_L09_001AEC38[] SDATA(D_L09_001AEC38);
extern float D_L09_001AEC48[] SDATA(D_L09_001AEC48);
extern float D_L09_001AEC4C[] MACRO_ADDR;
extern float D_L09_001B3120 MACRO_ADDR;
extern float D_L09_001B3124 MACRO_ADDR;
extern int D_L09_001B2388;

extern int func_002ACBC8(void *, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern int func_00283CF0(float);
extern float func_00283CE0(int), func_00283198(float);
extern void func_L09_0037FCE8(void *);
extern void func_L00_002E6DB8(void (*)(void *), void *);
extern void func_L00_002E6CF0(void (*)(void *), void *);

void func_L09_003806A0(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    float delta[4] __attribute__((aligned(16)));
    float scaled[4] __attribute__((aligned(16)));
    int i, index;
    int found;
    int *scan;

    if (D_L09_001C9F80[0] != I32(state, 0x30))
        return;
    if (object[0x20] == 0) {
        object[0x20] = 1;
        object[0x30] = 255;
        {
            for (i = 0; i < 2; i++) {
                D_L09_001B3110[i].u = 0.0f;
                D_L09_001B3110[i].v = 0.0f;
            }
        }
        qcopy(&D_L09_001B3100, D_L09_001B9A00);
        D_L09_001B3124 = F32(state, 0x14);
        return;
    }
    found = 0;
    for (i = 0; i < 4; i++) {
        if (I32(state, 0x40 + i * 4) == -1)
            continue;
        if (func_002ACBC8(D_00189EA0, I32(state, 0x40 + i * 4))) {
            { u8 *h = D_00189E20; S16(h, 0x1FE) = 0; }
            found = 1;
            break;
        }
    }
    if (found)
        return;
    D_L09_001B3124 = F32(state, 0x14);
    scan = (int *)(state + 0x50);
    for (i = 0; i < 4; i++) {
        if (scan[i] == -1)
            continue;
        if (func_002ACBC8(D_00189EA0, scan[i])) {
            D_L09_001B3124 = F32(D_L09_001B294C + scan[i] * 128, 0x38) + 0.15f;
            break;
        }
    }
    { u8 *h = D_00189E20; S16(h, 0x1FE) = 2; }
    func_00282CF0(delta, D_L09_001B9A00, &D_L09_001B3100);
    qcopy(&D_L09_001B3100, D_L09_001B9A00);
    if (!(F32(state, 0x20) < F32(D_L09_001B9A00, 8)))
        return;

    for (i = 0; i < 2; i++) {
        float numerator = D_L09_001AEC38[i] + D_L09_001AEC38[i];
        float denominator = F32(state, 0x18) * 5.0f;
        float scale = numerator / denominator;
        func_00282D30(scaled, delta, scale);
        /* Preserve the ordered comparisons, including the exact-1 and NaN paths. */
        if (1.0f < scaled[0] || scaled[0] < 1.0f)
            scaled[0] -= func_00283CE0(func_00283CF0(scaled[0]));
        if (1.0f < scaled[1] || scaled[1] < 1.0f)
            scaled[1] -= func_00283CE0(func_00283CF0(scaled[1]));
        D_L09_001B3110[i].u += scaled[0];
        D_L09_001B3110[i].v += scaled[1];
        if (1.0f < D_L09_001B3110[i].u)
            D_L09_001B3110[i].u -= 1.0f;
        if (D_L09_001B3110[i].u < -1.0f)
            D_L09_001B3110[i].u += 1.0f;
        if (1.0f < D_L09_001B3110[i].v)
            D_L09_001B3110[i].v -= 1.0f;
        if (D_L09_001B3110[i].v < -1.0f)
            D_L09_001B3110[i].v += 1.0f;
    }
    D_L09_001B3120 = D_L09_001B3124 +
        func_00283198(func_00283CE0(D_L09_001B2388 % 360) *
                     0.017444444820284843f - 3.140000104904175f) * F32(state, 0x34);
    for (i = 0; i < 2; i++) {
        D_L09_001B3110[i].u += D_L09_001AEC48[i * 2] * D_001A7928;
        if (1.0f < D_L09_001B3110[i].u)
            D_L09_001B3110[i].u -= 1.0f;
        if (D_L09_001B3110[i].u < -1.0f)
            D_L09_001B3110[i].u += 1.0f;
        D_L09_001B3110[i].v += D_L09_001AEC4C[i * 2] * D_001A7928;
        if (1.0f < D_L09_001B3110[i].v)
            D_L09_001B3110[i].v -= 1.0f;
        if (D_L09_001B3110[i].v < -1.0f)
            D_L09_001B3110[i].v += 1.0f;
    }
    if (I32(state, 0x38))
        func_L00_002E6DB8(func_L09_0037FCE8, object);
    else
        func_L00_002E6CF0(func_L09_0037FCE8, object);
}
