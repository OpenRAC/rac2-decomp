#include "include_asm.h"
#include "names.h"
/* Glow ring: four pulsing sprites along the actor's facing. */
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

typedef struct { char pad[0x14]; float phase[4]; float rate[4]; int alpha[4]; float size[4]; } GlowState;
void glow_ring_update(unsigned char *moby)
{
    GlowState *glow = *(GlowState **)(moby + 0x68);
    float ringPos[4];
    float ringStep[4];
    float origin[4];
    int i;

    *(V4_003F6008 *)origin = *(V4_003F6008 *)(moby + 0x10);
    origin[2] += 0.25f;
    FastVecSub(ringPos, ref_L04_003F6008_00, origin);
    vec_scale_to_length(ringPos, ringPos, -0.3f);
    vec_scale_to_length(ringStep, ringPos, 0.1f);
    FastVecAdd(ringPos, ringPos, origin);

    for (i = 0; i < 4; i++) {
        float value = glow->phase[i] + glow->rate[i];
        void *color;
        glow->phase[i] = value;
        if (value >= 255.0f)
            glow->phase[i] = value - 255.0f;
        else if (value <= 0.0f)
            glow->phase[i] = value + 255.0f;
        if (math_fast_float_d(&glow->alpha[i]))
            glow->alpha[i] = 0xFF;
        value = math_fabs(0.5f - IntToFloat(0xFF - glow->alpha[i]) * 0.0039215689f);
        color = FastTweenColor(0x4040FFFF, 0x1040FFFF, value);
        part_spawn_fading(ringPos, color, FloatToInt(glow->phase[i]) & 0xFF, 0x35, 1, 2, 0, glow->size[i]);
        FastVecAdd(ringPos, ringPos, ringStep);
    }
}
