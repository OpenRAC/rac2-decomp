#include "include_asm.h"
#include "names.h"

typedef int V4_003F6008 __attribute__((mode(TI)));
extern unsigned char ref_L04_003F6008_00[];
extern void FastVecSub(float *, void *, float *);
extern void vec_scale_to_length(float *, float *, float);
extern void FastVecAdd(float *, float *, float *);
extern int math_fast_float_d(void *);
extern float IntToFloat(int);
extern float math_fabs(float);
extern void *FastTweenColor(unsigned int, unsigned int, float);
extern int FloatToInt(float);
extern void *part_spawn_fading(void *, void *, int, int, int, int, int, float);
typedef struct { char pad[0x10]; float phase[4]; float rate[4]; int alpha[4]; float size[4]; } GlowState;

void func_PAL_L04_003FD250(unsigned char *a0)
{
    GlowState *st = *(GlowState **)(a0 + 0x68);
    float m[4];
    float q[4];
    float src[4];
    int i;

    *(V4_003F6008 *)src = *(V4_003F6008 *)(a0 + 0x10);
    src[2] += 0.25f;
    FastVecSub(m, ref_L04_003F6008_00, src);
    vec_scale_to_length(m, m, -0.3f);
    vec_scale_to_length(q, m, 0.1f);
    FastVecAdd(m, m, src);

    for (i = 0; i < 4; i++) {
        float v = st->phase[i] + st->rate[i];
        void *color;
        st->phase[i] = v;
        if (v >= 255.0f)
            st->phase[i] = v - 255.0f;
        else if (v <= 0.0f)
            st->phase[i] = v + 255.0f;
        if (math_fast_float_d(&st->alpha[i]))
            st->alpha[i] = 0xD4;
        v = math_fabs(0.5f - IntToFloat(0xD4 - st->alpha[i]) * 0.004716981f);
        color = FastTweenColor(0x4040FFFF, 0x1040FFFF, v);
        part_spawn_fading(m, color, FloatToInt(st->phase[i]) & 0xFF, 0x35, 1, 2, 0, st->size[i]);
        FastVecAdd(m, m, q);
    }
}
