#include "include_asm.h"
#include "names.h"

extern int math_random_int_below(int);

/* func_PAL_L04_003FA088, the PAL copy of func_L04_003F5F30: the same C, where the alpha steps take PAL's 50 Hz scale. */
void glow_l04_ring_init_pal(unsigned char *moby) {
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    float *phase;
    int *delay;
    int i;
    int j;

    phase = (float *)(vars + 0x14);
    for (i = 3; i >= 0; i--) {
        *phase++ = (float)math_random_int_below(0xFF);
    }
    *(float *)(vars + 0x24) = -1.0f;
    *(float *)(vars + 0x28) = -2.25f;
    *(float *)(vars + 0x2C) = 1.25f;
    *(float *)(vars + 0x30) = 2.5f;
    delay = (int *)(vars + 0x34);
    for (j = 0; j < 4; j++) {
        delay[j] = ((0x3F + j * 0x40) * 5 + 2) / 6;
    }
    *(float *)(vars + 0x44) = 2.0f;
    *(float *)(vars + 0x48) = 2.5f;
    *(float *)(vars + 0x4C) = 2.5f;
    *(float *)(vars + 0x50) = 2.0f;
}

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

/* Draws the glow ring: moves four pulsing sprites around the ring, fading their colour, and spawns one particle for each. */
void glow_ring_update_pal(unsigned char *moby)
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



/* func_PAL_L04_003FD168, the PAL copy of func_L04_003F8FA0: the same C as func_PAL_L04_003FA088, every field four bytes lower. */
void glow_ring_init_variant_pal(unsigned char *moby) {
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    float *phase;
    int *delay;
    int i;
    int j;

    phase = (float *)(vars + 0x10);
    for (i = 3; i >= 0; i--) {
        *phase++ = (float)math_random_int_below(0xFF);
    }
    *(float *)(vars + 0x20) = -1.0f;
    *(float *)(vars + 0x24) = -2.25f;
    *(float *)(vars + 0x28) = 1.25f;
    *(float *)(vars + 0x2C) = 2.5f;
    delay = (int *)(vars + 0x30);
    for (j = 0; j < 4; j++) {
        delay[j] = ((0x3F + j * 0x40) * 5 + 2) / 6;
    }
    *(float *)(vars + 0x40) = 2.0f;
    *(float *)(vars + 0x44) = 2.5f;
    *(float *)(vars + 0x48) = 2.5f;
    *(float *)(vars + 0x4C) = 2.0f;
}

