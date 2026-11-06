#include "include_asm.h"

extern int func_002A77E0(int);

/* func_PAL_L04_003FA088, the PAL copy of func_L04_003F5F30: the same C, where the alpha steps take PAL's 50 Hz scale. */
void func_PAL_L04_003FA088(unsigned char *a0) {
    unsigned char *obj = *(unsigned char **)(a0 + 0x68);
    float *p;
    int *q;
    int i;
    int j;

    p = (float *)(obj + 0x14);
    for (i = 3; i >= 0; i--) {
        *p++ = (float)func_002A77E0(0xFF);
    }
    *(float *)(obj + 0x24) = -1.0f;
    *(float *)(obj + 0x28) = -2.25f;
    *(float *)(obj + 0x2C) = 1.25f;
    *(float *)(obj + 0x30) = 2.5f;
    q = (int *)(obj + 0x34);
    for (j = 0; j < 4; j++) {
        q[j] = ((0x3F + j * 0x40) * 5 + 2) / 6;
    }
    *(float *)(obj + 0x44) = 2.0f;
    *(float *)(obj + 0x48) = 2.5f;
    *(float *)(obj + 0x4C) = 2.5f;
    *(float *)(obj + 0x50) = 2.0f;
}

typedef int V4_003F6008 __attribute__((mode(TI)));
extern unsigned char ref_L04_003F6008_00[];
extern void func_00282CF0(float *, void *, float *);
extern void func_00282F20(float *, float *, float);
extern void func_00282CC0(float *, float *, float *);
extern int func_00282948(void *);
extern float func_00283CE0(int);
extern float func_00282C48(float);
extern void *func_00283D38(unsigned int, unsigned int, float);
extern int func_00283CF0(float);
extern void *func_002C2FD8(void *, void *, int, int, int, int, int, float);
typedef struct { char pad[0x14]; float phase[4]; float rate[4]; int alpha[4]; float size[4]; } GlowState;

void func_PAL_L04_003FA170(unsigned char *a0)
{
    GlowState *st = *(GlowState **)(a0 + 0x68);
    float m[4];
    float q[4];
    float src[4];
    int i;

    *(V4_003F6008 *)src = *(V4_003F6008 *)(a0 + 0x10);
    src[2] += 0.25f;
    func_00282CF0(m, ref_L04_003F6008_00, src);
    func_00282F20(m, m, -0.3f);
    func_00282F20(q, m, 0.1f);
    func_00282CC0(m, m, src);

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



/* func_PAL_L04_003FD168, the PAL copy of func_L04_003F8FA0: the same C as func_PAL_L04_003FA088, every field four bytes lower. */
void func_PAL_L04_003FD168(unsigned char *a0) {
    unsigned char *obj = *(unsigned char **)(a0 + 0x68);
    float *p;
    int *q;
    int i;
    int j;

    p = (float *)(obj + 0x10);
    for (i = 3; i >= 0; i--) {
        *p++ = (float)func_002A77E0(0xFF);
    }
    *(float *)(obj + 0x20) = -1.0f;
    *(float *)(obj + 0x24) = -2.25f;
    *(float *)(obj + 0x28) = 1.25f;
    *(float *)(obj + 0x2C) = 2.5f;
    q = (int *)(obj + 0x30);
    for (j = 0; j < 4; j++) {
        q[j] = ((0x3F + j * 0x40) * 5 + 2) / 6;
    }
    *(float *)(obj + 0x40) = 2.0f;
    *(float *)(obj + 0x44) = 2.5f;
    *(float *)(obj + 0x48) = 2.5f;
    *(float *)(obj + 0x4C) = 2.0f;
}

