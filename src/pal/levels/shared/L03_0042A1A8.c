#include "include_asm.h"
#include "common.h"

extern int math_random_int_below(int x);

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
        *q = (float)math_random_int_below(255);
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
extern void FastVecSub(float *, void *, float *);
extern void vec_scale_to_length(float *, float *, float);
extern void FastVecAdd(float *, float *, float *);
extern int math_fast_float_d(void *);
extern float IntToFloat(int);
extern float math_fabs(float);
extern int FastTweenColor(unsigned int, unsigned int, float);
extern int FloatToInt(float);
typedef struct { unsigned char pad[9]; unsigned char fade; } Sprite_L03_00425108;
extern Sprite_L03_00425108 *part_spawn_fading(void *, void *, int, int, int, int, int, float);
typedef struct { char pad[0x10]; float phase[4]; float rate[4]; int alpha[4]; float size[4]; } GlowState_L03_00425108;

void func_PAL_L03_0042A6B0(unsigned char *a0)
{
    GlowState_L03_00425108 *st = *(GlowState_L03_00425108 **)(a0 + 0x68);
    float m[4];
    float q[4];
    float src[4];
    int i;

    *(V4_L03_00425108 *)src = *(V4_L03_00425108 *)(a0 + 0x10);
    FastVecSub(m, ref_L03_00425108_00, src);
    vec_scale_to_length(m, m, -0.3f);
    vec_scale_to_length(q, m, 0.1f);
    FastVecAdd(m, m, src);

    for (i = 0; i < 4; i++) {
        float v = st->phase[i] + st->rate[i];
        void *color;
        Sprite_L03_00425108 *s;
        st->phase[i] = v;
        if (v >= 255.0f)
            st->phase[i] = v - 255.0f;
        else if (v <= 0.0f)
            st->phase[i] = v + 255.0f;
        if (math_fast_float_d(&st->alpha[i]))
            st->alpha[i] = 0xD4;
        v = math_fabs(0.5f - IntToFloat(0xD4 - st->alpha[i]) * 0.004716981f);
        color = FastTweenColor(0x50C04020, 0x10804020, v);
        s = part_spawn_fading(m, color, FloatToInt(st->phase[i]) & 0xFF, 0x35, 1, 2, 0, st->size[i]);
        if (s)
            s->fade = FloatToInt(1.0f) + 0x60;
        FastVecAdd(m, m, q);
    }
}

