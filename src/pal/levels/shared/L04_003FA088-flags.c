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
extern int FastTweenColor(unsigned int, unsigned int, float);
extern int FloatToInt(float);
extern void *part_spawn_fading(void *, void *, int, int, int, int, int, float);
typedef struct { char pad[0x10]; float phase[4]; float rate[4]; int alpha[4]; float size[4]; } GlowState;

/* Draws the glow ring: moves four pulsing sprites around the ring, fading their colour, and spawns one particle for each. */
void glow_ring_update_variant_pal(unsigned char *moby)
{
    GlowState *glow = *(GlowState **)(moby + 0x68);
    float point[4];
    float step[4];
    float src[4];
    int i;

    *(V4_003F6008 *)src = *(V4_003F6008 *)(moby + 0x10);
    src[2] += 0.25f;
    FastVecSub(point, ref_L04_003F6008_00, src);
    vec_scale_to_length(point, point, -0.3f);
    vec_scale_to_length(step, point, 0.1f);
    FastVecAdd(point, point, src);

    for (i = 0; i < 4; i++) {
        float value = glow->phase[i] + glow->rate[i];
        void *color;
        glow->phase[i] = value;
        if (value >= 255.0f)
            glow->phase[i] = value - 255.0f;
        else if (value <= 0.0f)
            glow->phase[i] = value + 255.0f;
        if (math_fast_float_d(&glow->alpha[i]))
            glow->alpha[i] = 0xD4;
        value = math_fabs(0.5f - IntToFloat(0xD4 - glow->alpha[i]) * 0.004716981f);
        color = FastTweenColor(0x4040FFFF, 0x1040FFFF, value);
        part_spawn_fading(point, color, FloatToInt(glow->phase[i]) & 0xFF, 0x35, 1, 2, 0, glow->size[i]);
        FastVecAdd(point, point, step);
    }
}
