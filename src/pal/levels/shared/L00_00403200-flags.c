#include "include_asm.h"

extern unsigned char ref_L00_003FF890_00[];
extern void func_00282CF0(float *, void *, float *);
extern void func_00282F20(float *, float *, float);
extern void func_00282CC0(float *, float *, float *);
extern int func_00282948(void *);
extern float func_00283CE0(int);
extern float func_00282C48(float);
extern void *func_00283D38(unsigned int, unsigned int, float);
extern int func_00283CF0(float);
extern void *func_002C2FD8(void *, void *, int, int, int, int, int, float);
typedef struct { float phase[4]; float rate[4]; int alpha[4]; float size[4]; } GlowState;

void func_PAL_L00_004041C0(unsigned char *a0)
{
    GlowState *st = *(GlowState **)(a0 + 0x68);
    float m[4];
    float q[4];
    int i;

    func_00282CF0(m, ref_L00_003FF890_00, (float *)(a0 + 0x10));
    func_00282F20(m, m, -0.3f);
    func_00282F20(q, m, 0.1f);
    func_00282CC0(m, m, (float *)(a0 + 0x10));

    for (i = 0; i < 4; i++) {
        float v = st->phase[i] + st->rate[i];
        void *color;
        st->phase[i] = v;
        if (v >= 255.0f)
            st->phase[i] = v - 255.0f;
        else if (v <= 0.0f)
            st->phase[i] = v + 255.0f;
        if (func_00282948(&st->alpha[i]))
            st->alpha[i] = 0xD4;
        v = func_00282C48(0.5f - func_00283CE0(0xD4 - st->alpha[i]) * 0.004716981f);
        color = func_00283D38(0x4040FFFF, 0x1040FFFF, v);
        func_002C2FD8(m, color, func_00283CF0(st->phase[i]) & 0xFF, 0x35, 1, 2, 0, st->size[i]);
        func_00282CC0(m, m, q);
    }
}
