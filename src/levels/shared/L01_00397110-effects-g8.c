#include "common.h"

extern void vec_random_direction(void *, float, float);
extern int math_random_int_below(int);
extern void *part_spawn_hero_relative(void *, void *, int, unsigned char, unsigned char, int, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float IntToFloat(int);
extern float math_fabs(float);
extern int FastTweenColor(int, int, float);
extern unsigned char *part_spawn_fading(void *, int, int, int, int, int, int, float);
typedef unsigned int Quadword __attribute__((mode(TI)));
typedef union { Quadword whole; float f[4]; } Vector;
extern Vector g_level_origin_vec;
extern int g_oozla_intro_stage;
extern int ref_L01_003CEB00_0;
extern float g_sparkle_l01_speed_min __attribute__((sda));
extern float g_sparkle_l01_speed_max __attribute__((sda));
extern float g_glow_ring_jitter_min __attribute__((sda));
extern float g_sparkle_jitter_speed_max __attribute__((sda));
extern unsigned char g_sparkle_l01_alpha __attribute__((sda));
extern int g_sparkle_particle_sprite __attribute__((sda));
extern int g_sparkle_trail_particle_sprite __attribute__((sda));
extern float g_sparkle_particle_size __attribute__((sda));
extern float g_sparkle_trail_particle_size __attribute__((sda));
extern int g_sparkle_ring_color_start __attribute__((sda));
extern int g_sparkle_ring_color_end __attribute__((sda));
extern float g_sparkle_scale_base __attribute__((sda));
extern float g_sparkle_scale_growth __attribute__((sda));
extern int g_sparkle_fade_param __attribute__((sda));
extern int g_sparkle_fade_sprite __attribute__((sda));

/* Spawns sparkles and four pulsing rings between the moby and camera. */
void part_spawn_sparkles_and_glow_rings(char *moby)
{
    float pos[4], v[4], jitter[4], dir[4], step[4];
    int i, c, n;
    int alpha;
    float colorScale;
    float midpoint;
    qcopy(pos, moby + 0x10);
    if (math_random_int_below(4) == 0) {
        vec_random_direction(v, g_sparkle_l01_speed_min * (1.0f / 60.0f), g_sparkle_l01_speed_max * (1.0f / 60.0f));
        alpha = g_sparkle_l01_alpha;
        n = math_random_int_below(255);
        part_spawn_hero_relative(pos, v, g_sparkle_particle_sprite, alpha, n & 255, 0, g_sparkle_particle_size);
        for (i = 2; i >= 0; i--) {
            int trailAlpha;
            vec_random_direction(jitter, g_glow_ring_jitter_min * (1.0f / 60.0f), g_sparkle_jitter_speed_max * (1.0f / 60.0f));
            FastVecAdd(v, v, jitter);
            trailAlpha = g_sparkle_l01_alpha;
            n = math_random_int_below(255);
            part_spawn_hero_relative(pos, v, g_sparkle_trail_particle_sprite, trailAlpha, n & 255, 0, g_sparkle_trail_particle_size);
        }
    }
    colorScale = 1.0f / 255.0f;
    FastVecSub(dir, &g_level_origin_vec, pos);
    midpoint = 0.5f;
    vec_scale_to_length(dir, dir, -0.3f);
    vec_scale_to_length(step, dir, 0.1f);
    FastVecAdd(dir, dir, pos);
    for (i = 0; i < 4; i++) {
        int ringAlpha;
        unsigned char finalAlpha;
        float t = IntToFloat(255 - ((ref_L01_003CEB00_0 + i * 20) & 255));
        c = FastTweenColor(g_sparkle_ring_color_start, g_sparkle_ring_color_end, math_fabs(midpoint - t * colorScale));
        ringAlpha = *(unsigned char *)&g_oozla_intro_stage;
        if (i & 2)
            ringAlpha = ringAlpha * 2;
        if (i & 1)
            ringAlpha = 255 - ringAlpha;
        finalAlpha = ringAlpha;
        t = IntToFloat(i);
        part_spawn_fading(dir, c, finalAlpha, g_sparkle_fade_sprite, g_sparkle_fade_param, 2, 0,
          (g_sparkle_scale_base + t * g_sparkle_scale_growth) * (*(float *)(moby + 0x2C) / *(float *)(*(char **)(moby + 0x24) + 0x24)));
        FastVecAdd(dir, dir, step);
    }
}
