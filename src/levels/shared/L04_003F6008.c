#include "include_asm.h"
#include "names.h"
/* Glow ring: four pulsing sprites along the actor's facing. */
typedef int V4_003F6008 __attribute__((mode(TI)));
extern unsigned char ref_L04_003F6008_00[];
extern void func_00282CF0(float *, void *, float *);
extern void func_00282F20(float *, float *, float);
extern void func_00282CC0(float *, float *, float *);
extern int func_00282948(void *);
extern float func_00283CE0(int);
extern float func_00282C48(float);
extern void *func_00283D38(unsigned int, unsigned int, float);
extern int func_00283CF0(float);
extern void *func_002C2FD8(void *, void *, int, int, int, int, int, float);

typedef struct { char pad[0x14]; float phase[4]; float rate[4]; int alpha[4]; float size[4]; } GlowState;
void func_L04_003F6008(unsigned char *moby)
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
        if (FastFloatHelperD(&glow->alpha[i]))
            glow->alpha[i] = 0xFF;
        value = FloatAbs(0.5f - IntToFloat(0xFF - glow->alpha[i]) * 0.0039215689f);
        color = FastTweenColor(0x4040FFFF, 0x1040FFFF, value);
        SpawnFadingParticle_002C2FD8(ringPos, color, FloatToInt(glow->phase[i]) & 0xFF, 0x35, 1, 2, 0, glow->size[i]);
        FastVecAdd(ringPos, ringPos, ringStep);
    }
}
