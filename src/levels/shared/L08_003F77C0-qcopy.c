#include "include_asm.h"
#include "names.h"
/* func_L08_003F77C0: the level-08 sparkle seeding, the twin of func_L00_00382CE8 with its own
 * table, colour base, life and scale constants and twelve slots. */
#include "common.h"
extern void FastVecSub(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern float FastVecDot(void *,void *);
extern float FastVecLength(void *);
extern float math_fabs(float);
extern float FastDiffRots(float,float);
extern float math_fast_float_g(float);
extern float math_fast_sin_or_cos_a(float);
extern float math_random_float_range(float,float);
extern float math_random_signed_float_range(float,float);
extern float math_random_angle(void);
extern int math_random_int_below(int);
extern void vec_build_spherical_offset(float *,float,float,float);
extern char *part_spawn_ground_effect(void *,int,unsigned int,int,int,void *,int,float,float,float);
typedef struct {
    void *owner;
    int active;
    char pad08[8];
    short size[16];
    short life[16];
    unsigned int color[16];
    float phase[16];
    float scale[16];
} Sparkle;
extern Sparkle g_lens_flare_2;
/* Starts a set of eleven randomly coloured sparkles for the owner (once only), picking each
   one's colour, lifetime and size. */
void part_start_sparkle_burst(void *owner)
{
    int i, intensity, color_mode, red;
    unsigned int base_color;
    int green_part;
    float phase;
    if (g_lens_flare_2.active == 1) return;
    g_lens_flare_2.owner = owner;
    g_lens_flare_2.active = 1;
    i = 1;
    base_color = 0x706080;
    for (; i < 12; ++i) {
        intensity = math_random_int_below(63) + 1;
        color_mode = math_random_int_below(6);
        switch (color_mode) {
        case 0: g_lens_flare_2.color[i] = intensity + base_color - (intensity << 16); break;
        case 1: g_lens_flare_2.color[i] = (intensity << 8) + (intensity + base_color); break;
        case 2: g_lens_flare_2.color[i] = (math_random_int_below(intensity) << 8) + (intensity + base_color); break;
        case 3:
            red = math_random_int_below(intensity);
            green_part = (math_random_int_below(intensity) << 8) + base_color;
            g_lens_flare_2.color[i] = (red << 16) + green_part + intensity; break;
        default: g_lens_flare_2.color[i] = base_color; break;
        }
        g_lens_flare_2.life[i] = math_random_int_below(3) + 1;
        phase = math_random_float_range(-0.95f, 2.5f);
        g_lens_flare_2.phase[i] = phase;
        phase = math_fabs(math_fast_sin_or_cos_a(math_fast_float_g(phase + 1)));
        g_lens_flare_2.scale[i] = phase * phase * phase * 1.7f;
        g_lens_flare_2.size[i] = 23;
    }
    g_lens_flare_2.phase[0] = -1;
    g_lens_flare_2.scale[0] = 2;
    g_lens_flare_2.color[0] = 0x808080;
    g_lens_flare_2.life[0] = 0;
    g_lens_flare_2.size[0] = 127;
}
