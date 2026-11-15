#include "common.h"

extern void func_00282CC0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(float, void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_00282CF0(void *, void *, void *);
extern int func_00277258(void *, float, int, void *);
extern float func_00282E20(void *);
extern float func_00283248(float, float);
extern float D_001BAFA0[];
extern float D_001BAFB0[];
extern char D_001BAF80[];

int func_002A8240(char *object, float *movement, int flags,
                  float height, float radius, float offset)
{
    float previous[4] __attribute__((aligned(16)));
    float from[4] __attribute__((aligned(16)));
    float to[4] __attribute__((aligned(16)));
    float scaled[4] __attribute__((aligned(16)));
    float *position = (float *)(object + 0x10);
    int mask = (flags << 1) & 0x20;
    int result = 0;
    int retries;
    float base;
    char *hit;

    qcopy(previous, position);
    FastVecAdd(position, position, movement);
    if (FastVecLength(movement) > radius) {
        qcopy(from, previous);
        from[2] += height;
        vec_scale_to_length(radius, scaled, movement);
        FastVecAdd(to, scaled, position);
        to[2] += height;
        if (CollLine(from, to, mask, object, 0)) {
            FastVecSub(position, D_001BAFA0, scaled);
            result = 1;
            *(float *)(object + 0x18) -= height;
        }
    }
    retries = 0;
    position = (float *)(object + 0x10);

    for (;;) {
        qcopy(from, position);
        from[2] += height;
        if (!func_00277258(from, radius, mask | 4, object))
            break;
        qcopy(position, D_001BAFB0);
        ++retries;
        result |= 1;
        *(float *)(object + 0x18) -= height;
        if (retries >= 6)
            break;
    }
    base = *(float *)(object + 0x18) - offset;
    qcopy(from, position);
    qcopy(to, position);
    from[2] += height;
    to[2] = base - 0.05f;
    if (CollLine(from, to, mask | 2, object, 0)) {
        hit = D_001BAF80;
        if (*(int *)(hit + 0x1C) > 0) {
            float normal;
            result |= 2;
            normal = vec_length_xy(hit + 0x40);
            if (func_00283248(*(float *)(hit + 0x48), normal) > 0.5f)
                result |= 4;
            if (base < *(float *)(hit + 0x28))
                *(float *)(object + 0x18) += (*(float *)(hit + 0x28) - base) * 0.3f;
        }
    }
    FastVecSub(movement, position, previous);
    return result;
}
