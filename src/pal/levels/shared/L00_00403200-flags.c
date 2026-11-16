#include "include_asm.h"
#include "names.h"

extern unsigned char ref_L00_003FF890_00[];
extern void FastVecSub(float *, void *, float *);
extern void vec_scale_to_length(float *, float *, float);
extern void FastVecAdd(float *, float *, float *);
extern int math_fast_float_d(void *);
extern float IntToFloat(int);
extern float math_fabs(float);
extern int FastTweenColor(unsigned int, unsigned int, float);
extern int FloatToInt(float);
extern void *part_spawn_fading(void *, void *, int, int, int, int, int, float);
typedef struct { float phase[4]; float rate[4]; int alpha[4]; float size[4]; } GlowState;

/* Each frame, spawns four fading glow particles in a row beside the object, with colours that pulse and phases that cycle (PAL: this release's copy of the glow ring update). */
void glow_ring_effect_update_pal(unsigned char *moby)
{
    GlowState *vars = *(GlowState **)(moby + 0x68);
    float point[4];
    float step[4];
    int i;

    FastVecSub(point, ref_L00_003FF890_00, (float *)(moby + 0x10));
    vec_scale_to_length(point, point, -0.3f);
    vec_scale_to_length(step, point, 0.1f);
    FastVecAdd(point, point, (float *)(moby + 0x10));

    for (i = 0; i < 4; i++) {
        float value = vars->phase[i] + vars->rate[i];
        void *color;
        vars->phase[i] = value;
        if (value >= 255.0f)
            vars->phase[i] = value - 255.0f;
        else if (value <= 0.0f)
            vars->phase[i] = value + 255.0f;
        if (math_fast_float_d(&vars->alpha[i]))
            vars->alpha[i] = 0xD4;
        value = math_fabs(0.5f - IntToFloat(0xD4 - vars->alpha[i]) * 0.004716981f);
        color = FastTweenColor(0x4040FFFF, 0x1040FFFF, value);
        part_spawn_fading(point, color, FloatToInt(vars->phase[i]) & 0xFF, 0x35, 1, 2, 0, vars->size[i]);
        FastVecAdd(point, point, step);
    }
}
