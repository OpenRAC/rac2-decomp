#include "include_asm.h"
#include "common.h"

typedef int TI __attribute__((mode(TI)));

extern int D_001B53A0[];

extern TI func_00334710(int, TI *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern float func_00282DF0(void *);
extern float func_002831B0(float);

float func_003348A8(u8 *self, float t) {
    float m[4] __attribute__((aligned(16)));
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    int *root = D_001B53A0;
    float along;
    float d;
    float len;
    float r;

    func_00334710((int)self, (TI *)m);
    FastVecScale(a, root + 8, t);
    FastVecAdd(a, a, m);
    FastVecSub(b, a, self + 0x30);
    along = FastVecDot(b, self + 0x10);
    FastVecScale(c, self + 0x10, along);
    FastVecSub(b, b, c);
    d = FastVecDot(b, self);
    len = FastVecLength(b);
    if (len == 0.0f) {
        return 0.0f;
    }
    r = 1.5707964f - func_002831B0(d / len);
    if (FastVecDot(b, self + 0x20) < 0.0f) {
        r = -r;
    }
    return r;
}
