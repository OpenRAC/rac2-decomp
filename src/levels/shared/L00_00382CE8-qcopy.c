#include "names.h"
/* func_L00_00382CE8: seed the sparkle table (owner, per-slot colour, life, phase and scale).
 * The grey base colour is a local set after the index, so each case adds it in its own register. */
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
extern Sparkle g_flare_state;
/* Sets up the table of sparkles once: each gets a random colour, lifetime, phase and size. */
void sparkle_init_table(void *owner)
{
    int i, intensity, mode, component;
    unsigned int grey;
    int green;
    float value;
    if (g_flare_state.active == 1) return;
    g_flare_state.owner = owner;
    g_flare_state.active = 1;
    i = 1;
    grey = 0x202080;
    for (; i < 14; ++i) {
        intensity = math_random_int_below(63) + 1;
        mode = math_random_int_below(6);
        switch (mode) {
        case 0: g_flare_state.color[i] = intensity + grey - (intensity << 16); break;
        case 1: g_flare_state.color[i] = (intensity << 8) + (intensity + grey); break;
        case 2: g_flare_state.color[i] = (math_random_int_below(intensity) << 8) + (intensity + grey); break;
        case 3:
            component = math_random_int_below(intensity);
            green = (math_random_int_below(intensity) << 8) + grey;
            g_flare_state.color[i] = (component << 16) + green + intensity; break;
        default: g_flare_state.color[i] = grey; break;
        }
        g_flare_state.life[i] = math_random_int_below(30) / 10 + 1;
        value = math_random_float_range(-0.95f, 2.4f);
        g_flare_state.phase[i] = value;
        value = math_fabs(math_fast_sin_or_cos_a(math_fast_float_g(value + 1)));
        g_flare_state.scale[i] = value * value * value * 1.4f;
        g_flare_state.size[i] = 32;
    }
    g_flare_state.phase[0] = -1;
    g_flare_state.scale[0] = 2;
    g_flare_state.color[0] = 0x808080;
    g_flare_state.life[0] = 0;
    g_flare_state.size[0] = 127;
}
