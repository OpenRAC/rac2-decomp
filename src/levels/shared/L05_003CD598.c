#include "include_asm.h"
#include "names.h"
/* Glow ring: four pulsing sprites along the actor's facing, each faded in. */
typedef int V4_L05_003CD598 __attribute__((mode(TI)));
extern unsigned char ref_L05_003CD598_00[];
extern void func_00282CF0(float *, void *, float *);
extern void func_00282F20(float *, float *, float);
extern void func_00282CC0(float *, float *, float *);
extern int func_00282948(void *);
extern float func_00283CE0(int);
extern float func_00282C48(float);
extern void *func_00283D38(unsigned int, unsigned int, float);
extern int func_00283CF0(float);

typedef struct { unsigned char pad[9]; unsigned char fade; } Sprite_L05_003CD598;
extern Sprite_L05_003CD598 *func_002C2FD8(void *, void *, int, int, int, int, int, float);

typedef struct { float phase[4]; float rate[4]; int alpha[4]; float size[4]; } GlowState_L05_003CD598;
/* Draws four pulsing red glow sprites trailing behind the pickup. */
void func_L05_003CD598(unsigned char *actor)
{
    GlowState_L05_003CD598 *st = *(GlowState_L05_003CD598 **)(actor + 0x68);
    float m[4];
    float q[4];
    float src[4];
    int i;

    *(V4_L05_003CD598 *)src = *(V4_L05_003CD598 *)(actor + 0x10);
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
        if (FastFloatHelperD(&st->alpha[i]))
            st->alpha[i] = 0xFF;
        v = FloatAbs(0.5f - IntToFloat(0xFF - st->alpha[i]) * 0.0039215689f);
        color = FastTweenColor(0x50FF4040, 0x10FF4040, v);
        s = SpawnFadingParticle_002C2FD8(m, color, FloatToInt(st->phase[i]) & 0xFF, 0x35, 1, 2, 0, st->size[i]);
        if (s)
            s->fade = FloatToInt(1.0f) + 0x60;
        FastVecAdd(m, m, q);
    }
}
