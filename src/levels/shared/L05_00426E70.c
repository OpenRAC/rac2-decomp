#include "include_asm.h"
#include "names.h"
/* Glow ring: four pulsing sprites along the actor's facing, each faded in. */
typedef int V4_L05_00426E70 __attribute__((mode(TI)));
extern unsigned char ref_L05_00426E70_00[];
extern void FastVecSub(float *, void *, float *);
extern void vec_scale_to_length(float *, float *, float);
extern void FastVecAdd(float *, float *, float *);
extern int math_fast_float_d(void *);
extern float IntToFloat(int);
extern float math_fabs(float);
extern void *FastTweenColor(unsigned int, unsigned int, float);
extern int FloatToInt(float);

typedef struct { unsigned char pad[9]; unsigned char fade; } Sprite_L05_00426E70;
extern Sprite_L05_00426E70 *part_spawn_fading(void *, void *, int, int, int, int, int, float);

typedef struct { float phase[4]; float rate[4]; int alpha[4]; float size[4]; } GlowState_L05_00426E70;
/* Draws a glow ring of four pulsing sprites above the object. */
void glow_l05_ring_draw_4(unsigned char *object)
{
    GlowState_L05_00426E70 *glow = *(GlowState_L05_00426E70 **)(object + 0x68);
    float center[4];
    float step[4];
    float src[4];
    int i;

    *(V4_L05_00426E70 *)src = *(V4_L05_00426E70 *)(object + 0x10);
    src[2] += 0.25f;
    FastVecSub(center, ref_L05_00426E70_00, src);
    vec_scale_to_length(center, center, -0.3f);
    vec_scale_to_length(step, center, 0.1f);
    FastVecAdd(center, center, src);

    for (i = 0; i < 4; i++) {
        float v = glow->phase[i] + glow->rate[i];
        void *color;
        Sprite_L05_00426E70 *sprite;
        glow->phase[i] = v;
        if (v >= 255.0f)
            glow->phase[i] = v - 255.0f;
        else if (v <= 0.0f)
            glow->phase[i] = v + 255.0f;
        if (math_fast_float_d(&glow->alpha[i]))
            glow->alpha[i] = 0xFF;
        v = math_fabs(0.5f - IntToFloat(0xFF - glow->alpha[i]) * 0.0039215689f);
        color = FastTweenColor(0x50204FFF, 0x10204FFF, v);
        sprite = part_spawn_fading(center, color, FloatToInt(glow->phase[i]) & 0xFF, 0x35, 1, 2, 0, glow->size[i]);
        if (sprite)
            sprite->fade = FloatToInt(1.0f) + 0x60;
        FastVecAdd(center, center, step);
    }
}
