#include "include_asm.h"
#include "common.h"

extern char D_00189EA0[];
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);

typedef union {
    int q __attribute__((mode(TI)));
    float f[4];
} Quad __attribute__((aligned(16)));

void func_L04_0046D6A8(char *obj) {
    Quad v;
    Quad u;
    char *s1;
    char *p = *(char **)(obj + 0x70);

    qcopy(&v, D_00189EA0);
    v.f[2] = v.f[2] + *(float *)(p + 0x90);
    u.q = 0;
    u.f[2] = 1.0f;
    u.f[3] = 1.0f;
    FastVecSub(obj, &v, obj + 0x30);
    vec_scale_to_length(obj, obj, 1.0f);
    s1 = obj + 0x10;
    FastVecCross(s1, obj, &u);
    vec_scale_to_length(s1, s1, 1.0f);
    FastVecCross(obj + 0x20, s1, obj);
}
