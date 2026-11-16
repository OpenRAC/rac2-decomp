#include "include_asm.h"
#include "common.h"

extern int math_random_int_below(int x);

/* func_PAL_L03_0042A5C8, the PAL copy of func_L03_00425030: four random floats, four fixed ones,
   then the fade table at +0x20 scaled to 50 Hz, which turns its loop into a count-up one. */
void moby_init_random_colors_pal(char *moby)
{
    float *vars = *(float **)(moby + 104);
    float *randoms = vars + 4;
    int *fade_table;
    int i;
    int j;

    for (i = 3; i >= 0; i--)
    {
        *randoms = (float)math_random_int_below(255);
        randoms++;
    }

    vars[8] = -1.0f;
    vars[9] = -2.25f;
    vars[10] = 1.25f;
    vars[11] = 2.5f;

    fade_table = (int *)(vars + 12);
    for (j = 0; j < 4; j++)
    {
        fade_table[j] = ((s32)(j * 64 + 63) * 5 + 2) / 6;
    }

    vars[16] = 2.0f;
    vars[17] = 2.46f;
    vars[19] = 2.0f;
    vars[18] = 2.46f;
}

typedef int V4_L03_00425108 __attribute__((mode(TI)));
extern unsigned char ref_L03_00425108_00[];
extern void FastVecSub(float *, void *, float *);
extern void vec_scale_to_length(float *, float *, float);
extern void FastVecAdd(float *, float *, float *);
extern int math_fast_float_d(void *);
extern float IntToFloat(int);
extern float math_fabs(float);
extern int FastTweenColor(unsigned int, unsigned int, float);
extern int FloatToInt(float);
typedef struct { unsigned char pad[9]; unsigned char fade; } Sprite_L03_00425108;
extern Sprite_L03_00425108 *part_spawn_fading(void *, void *, int, int, int, int, int, float);
typedef struct { char pad[0x10]; float phase[4]; float rate[4]; int alpha[4]; float size[4]; } GlowState_L03_00425108;

/* Spawns four fading glow sprites in a row next to the object, their brightness pulsing (PAL: 50 Hz timings). */
void gfx_draw_glow_ring_sprites_pal(unsigned char *moby)
{
    GlowState_L03_00425108 *glow = *(GlowState_L03_00425108 **)(moby + 0x68);
    float point[4];
    float randoms[4];
    float src[4];
    int i;

    *(V4_L03_00425108 *)src = *(V4_L03_00425108 *)(moby + 0x10);
    FastVecSub(point, ref_L03_00425108_00, src);
    vec_scale_to_length(point, point, -0.3f);
    vec_scale_to_length(randoms, point, 0.1f);
    FastVecAdd(point, point, src);

    for (i = 0; i < 4; i++) {
        float value = glow->phase[i] + glow->rate[i];
        void *color;
        Sprite_L03_00425108 *sprite;
        glow->phase[i] = value;
        if (value >= 255.0f)
            glow->phase[i] = value - 255.0f;
        else if (value <= 0.0f)
            glow->phase[i] = value + 255.0f;
        if (math_fast_float_d(&glow->alpha[i]))
            glow->alpha[i] = 0xD4;
        value = math_fabs(0.5f - IntToFloat(0xD4 - glow->alpha[i]) * 0.004716981f);
        color = FastTweenColor(0x50C04020, 0x10804020, value);
        sprite = part_spawn_fading(point, color, FloatToInt(glow->phase[i]) & 0xFF, 0x35, 1, 2, 0, glow->size[i]);
        if (sprite)
            sprite->fade = FloatToInt(1.0f) + 0x60;
        FastVecAdd(point, point, randoms);
    }
}

