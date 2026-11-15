#include "include_asm.h"
#include "names.h"
/* Glow ring: four pulsing sprites along the actor's facing, each faded in. */
typedef int V4_L05_0041D800 __attribute__((mode(TI)));
extern unsigned char ref_L05_0041D800_00[];
extern void FastVecSub(float *, void *, float *);
extern void vec_scale_to_length(float *, float *, float);
extern void FastVecAdd(float *, float *, float *);
extern int math_fast_float_d(void *);
extern float IntToFloat(int);
extern float math_fabs(float);
extern int FastTweenColor(unsigned int, unsigned int, float);
extern int FloatToInt(float);

typedef struct { unsigned char pad[9]; unsigned char fade; } Sprite_L05_0041D800;
extern Sprite_L05_0041D800 *part_spawn_fading(void *, void *, int, int, int, int, int, float);

typedef struct { float phase[4]; float rate[4]; int alpha[4]; float size[4]; } GlowState_L05_0041D800;
/* Draws four pulsing green glow sprites in a short line in front of the object, each fading in. */
void glow_l05_ring_draw_3(unsigned char *object)
{
    GlowState_L05_0041D800 *glow = *(GlowState_L05_0041D800 **)(object + 0x68);
    float m[4];
    float q[4];
    float src[4];
    int i;

    *(V4_L05_0041D800 *)src = *(V4_L05_0041D800 *)(object + 0x10);
    src[2] += 0.25f;
    FastVecSub(m, ref_L05_0041D800_00, src);
    vec_scale_to_length(m, m, -0.3f);
    vec_scale_to_length(q, m, 0.1f);
    FastVecAdd(m, m, src);

    for (i = 0; i < 4; i++) {
        float v = glow->phase[i] + glow->rate[i];
        void *color;
        Sprite_L05_0041D800 *sprite;
        glow->phase[i] = v;
        if (v >= 255.0f)
            glow->phase[i] = v - 255.0f;
        else if (v <= 0.0f)
            glow->phase[i] = v + 255.0f;
        if (math_fast_float_d(&glow->alpha[i]))
            glow->alpha[i] = 0xFF;
        v = math_fabs(0.5f - IntToFloat(0xFF - glow->alpha[i]) * 0.0039215689f);
        color = FastTweenColor(0x5040FF40, 0x1040FF40, v);
        sprite = part_spawn_fading(m, color, FloatToInt(glow->phase[i]) & 0xFF, 0x35, 1, 2, 0, glow->size[i]);
        if (sprite)
            sprite->fade = FloatToInt(1.0f) + 0x60;
        FastVecAdd(m, m, q);
    }
}
