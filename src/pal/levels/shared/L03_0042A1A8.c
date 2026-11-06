#include "include_asm.h"
#include "common.h"

extern int func_002A77E0(int x);

/* func_PAL_L03_0042A5C8, the PAL copy of func_L03_00425030: four random floats, four fixed ones,
   then the fade table at +0x20 scaled to 50 Hz, which turns its loop into a count-up one. */
void func_PAL_L03_0042A5C8(char *self)
{
    float *p = *(float **)(self + 104);
    float *q = p + 4;
    int *w;
    int i;
    int j;

    for (i = 3; i >= 0; i--)
    {
        *q = (float)func_002A77E0(255);
        q++;
    }

    p[8] = -1.0f;
    p[9] = -2.25f;
    p[10] = 1.25f;
    p[11] = 2.5f;

    w = (int *)(p + 12);
    for (j = 0; j < 4; j++)
    {
        w[j] = ((s32)(j * 64 + 63) * 5 + 2) / 6;
    }

    p[16] = 2.0f;
    p[17] = 2.46f;
    p[19] = 2.0f;
    p[18] = 2.46f;
}

typedef int V4_L03_00425108 __attribute__((mode(TI)));
extern unsigned char ref_L03_00425108_00[];
extern void func_00282CF0(float *, void *, float *);
extern void func_00282F20(float *, float *, float);
extern void func_00282CC0(float *, float *, float *);
extern int func_00282948(void *);
extern float func_00283CE0(int);
extern float func_00282C48(float);
extern void *func_00283D38(unsigned int, unsigned int, float);
extern int func_00283CF0(float);
typedef struct { unsigned char pad[9]; unsigned char fade; } Sprite_L03_00425108;
extern Sprite_L03_00425108 *func_002C2FD8(void *, void *, int, int, int, int, int, float);
typedef struct { char pad[0x10]; float phase[4]; float rate[4]; int alpha[4]; float size[4]; } GlowState_L03_00425108;

void func_PAL_L03_0042A6B0(unsigned char *a0)
{
    GlowState_L03_00425108 *st = *(GlowState_L03_00425108 **)(a0 + 0x68);
    float m[4];
    float q[4];
    float src[4];
    int i;

    *(V4_L03_00425108 *)src = *(V4_L03_00425108 *)(a0 + 0x10);
    func_00282CF0(m, ref_L03_00425108_00, src);
    func_00282F20(m, m, -0.3f);
    func_00282F20(q, m, 0.1f);
    func_00282CC0(m, m, src);

    for (i = 0; i < 4; i++) {
        float v = st->phase[i] + st->rate[i];
        void *color;
        Sprite_L03_00425108 *s;
        st->phase[i] = v;
        if (v >= 255.0f)
            st->phase[i] = v - 255.0f;
        else if (v <= 0.0f)
            st->phase[i] = v + 255.0f;
        if (func_00282948(&st->alpha[i]))
            st->alpha[i] = 0xD4;
        v = func_00282C48(0.5f - func_00283CE0(0xD4 - st->alpha[i]) * 0.004716981f);
        color = func_00283D38(0x50C04020, 0x10804020, v);
        s = func_002C2FD8(m, color, func_00283CF0(st->phase[i]) & 0xFF, 0x35, 1, 2, 0, st->size[i]);
        if (s)
            s->fade = func_00283CF0(1.0f) + 0x60;
        func_00282CC0(m, m, q);
    }
}

