#include "include_asm.h"
#include "names.h"
/* Glow ring: four pulsing sprites along the actor's facing, each faded in. */
typedef int V4_L03_00425108 __attribute__((mode(TI)));
extern unsigned char ref_L03_00425108_00[];
extern void FastVecSub(float *, void *, float *);
extern void vec_scale_to_length(float *, float *, float);
extern void FastVecAdd(float *, float *, float *);
extern int math_fast_float_d(void *);
extern float IntToFloat(int);
extern float math_fabs(float);
extern void *FastTweenColor(unsigned int, unsigned int, float);
extern int FloatToInt(float);

typedef struct { unsigned char pad[9]; unsigned char fade; } Sprite_L03_00425108;
extern Sprite_L03_00425108 *part_spawn_fading(void *, void *, int, int, int, int, int, float);

typedef struct { char pad[0x10]; float phase[4]; float rate[4]; int alpha[4]; float size[4]; } GlowState_L03_00425108;
/* Draws four pulsing glow sprites in a row in front of the object. */
void gfx_draw_glow_ring_sprites(unsigned char *moby)
{
    GlowState_L03_00425108 *state = *(GlowState_L03_00425108 **)(moby + 0x68);
    float glowPos[4];
    float stepVec[4];
    float src[4];
    int i;

    *(V4_L03_00425108 *)src = *(V4_L03_00425108 *)(moby + 0x10);
    FastVecSub(glowPos, ref_L03_00425108_00, src);
    vec_scale_to_length(glowPos, glowPos, -0.3f);
    vec_scale_to_length(stepVec, glowPos, 0.1f);
    FastVecAdd(glowPos, glowPos, src);

    for (i = 0; i < 4; i++) {
        float v = state->phase[i] + state->rate[i];
        void *color;
        Sprite_L03_00425108 *s;
        state->phase[i] = v;
        if (v >= 255.0f)
            state->phase[i] = v - 255.0f;
        else if (v <= 0.0f)
            state->phase[i] = v + 255.0f;
        if (math_fast_float_d(&state->alpha[i]))
            state->alpha[i] = 0xFF;
        v = math_fabs(0.5f - IntToFloat(0xFF - state->alpha[i]) * 0.0039215689f);
        color = FastTweenColor(0x50C04020, 0x10804020, v);
        s = part_spawn_fading(glowPos, color, FloatToInt(state->phase[i]) & 0xFF, 0x35, 1, 2, 0, state->size[i]);
        if (s)
            s->fade = FloatToInt(1.0f) + 0x60;
        FastVecAdd(glowPos, glowPos, stepVec);
    }
}
