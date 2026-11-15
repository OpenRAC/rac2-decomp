#include "names.h"
/* func_PAL_L05_0042BD38, the PAL copy of func_L05_003CD598: the same C, where 0xFF becomes 0xD4;
   0.0039215689f becomes 0.004716981f; 0x50FF4040 becomes 0x502020FF; 0x10FF4040 becomes
   0x102020FF. */
#include "include_asm.h"
typedef int V4_L05_003CD598 __attribute__((mode(TI)));
extern unsigned char ref_L05_003CD598_00[];
extern void FastVecSub(float *, void *, float *);
extern void vec_scale_to_length(float *, float *, float);
extern void FastVecAdd(float *, float *, float *);
extern int math_fast_float_d(void *);
extern float IntToFloat(int);
extern float math_fabs(float);
extern int FastTweenColor(unsigned int, unsigned int, float);
extern int FloatToInt(float);

typedef struct { unsigned char pad[9]; unsigned char fade; } Sprite_L05_003CD598;
extern Sprite_L05_003CD598 *part_spawn_fading(void *, void *, int, int, int, int, int, float);

typedef struct { float phase[4]; float rate[4]; int alpha[4]; float size[4]; } GlowState_L05_003CD598;
void func_PAL_L05_0042BD38(unsigned char *a0)
{
    GlowState_L05_003CD598 *st = *(GlowState_L05_003CD598 **)(a0 + 0x68);
    float m[4];
    float q[4];
    float src[4];
    int i;

    *(V4_L05_003CD598 *)src = *(V4_L05_003CD598 *)(a0 + 0x10);
    src[2] += 0.25f;
    FastVecSub(m, ref_L05_003CD598_00, src);
    vec_scale_to_length(m, m, -0.3f);
    vec_scale_to_length(q, m, 0.1f);
    FastVecAdd(m, m, src);

    for (i = 0; i < 4; i++) {
        float v = st->phase[i] + st->rate[i];
        void *color;
        Sprite_L05_003CD598 *s;
        st->phase[i] = v;
        if (v >= 255.0f)
            st->phase[i] = v - 255.0f;
        else if (v <= 0.0f)
            st->phase[i] = v + 255.0f;
        if (math_fast_float_d(&st->alpha[i]))
            st->alpha[i] = 0xD4;
        v = math_fabs(0.5f - IntToFloat(0xD4 - st->alpha[i]) * 0.004716981f);
        color = FastTweenColor(0x502020FF, 0x102020FF, v);
        s = part_spawn_fading(m, color, FloatToInt(st->phase[i]) & 0xFF, 0x35, 1, 2, 0, st->size[i]);
        if (s)
            s->fade = FloatToInt(1.0f) + 0x60;
        FastVecAdd(m, m, q);
    }
}
