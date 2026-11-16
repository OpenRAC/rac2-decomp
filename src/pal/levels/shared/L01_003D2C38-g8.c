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

/* func_PAL_L01_003D2C38, the PAL copy of func_L01_003CEB00: the same C, where 1/60 becomes 1/50 and the
   ring phase takes the 50 Hz scale, so its range 255 becomes 212. */
/* Spawns sparkles and four pulsing rings between the moby and camera. */
void part_spawn_sparkles_and_glow_rings_pal(char *moby)
{
    float pos[4], velocity[4], jitter[4], dir[4], step[4];
    int i, color, random_value;
    int alpha;
    qcopy(pos, moby + 0x10);
    if (math_random_int_below(4) == 0) {
        vec_random_direction(velocity, g_sparkle_l01_speed_min * 0.020000001f, g_sparkle_l01_speed_max * 0.020000001f);
        alpha = g_sparkle_l01_alpha;
        random_value = math_random_int_below(255);
        part_spawn_hero_relative(pos, velocity, g_sparkle_particle_sprite, alpha, random_value & 255, 0, g_sparkle_particle_size);
        for (i = 2; i >= 0; i--) {
            int trail_alpha;
            vec_random_direction(jitter, g_glow_ring_jitter_min * 0.020000001f, g_sparkle_jitter_speed_max * 0.020000001f);
            FastVecAdd(velocity, velocity, jitter);
            trail_alpha = g_sparkle_l01_alpha;
            random_value = math_random_int_below(255);
            part_spawn_hero_relative(pos, velocity, g_sparkle_trail_particle_sprite, trail_alpha, random_value & 255, 0, g_sparkle_trail_particle_size);
        }
    }
    FastVecSub(dir, &g_level_origin_vec, pos);
    vec_scale_to_length(dir, dir, -0.3f);
    vec_scale_to_length(step, dir, 0.1f);
    FastVecAdd(dir, dir, pos);
    for (i = 0; i < 4; i++) {
        int ring_alpha;
        unsigned char final_alpha;
        float t = IntToFloat(212 - ((s32)((ref_L01_003CEB00_0 + i * 20) & 255) * 5 + 2) / 6);
        color = FastTweenColor(g_sparkle_ring_color_start, g_sparkle_ring_color_end, math_fabs(0.5f - t * (1.0f / 212.0f)));
        ring_alpha = *(unsigned char *)&g_oozla_intro_stage;
        if (i & 2)
            ring_alpha = ring_alpha * 2;
        if (i & 1)
            ring_alpha = 255 - ring_alpha;
        final_alpha = ring_alpha;
        t = IntToFloat(i);
        part_spawn_fading(dir, color, final_alpha, g_sparkle_fade_sprite, g_sparkle_fade_param, 2, 0,
          (g_sparkle_scale_base + t * g_sparkle_scale_growth) * (*(float *)(moby + 0x2C) / *(float *)(*(char **)(moby + 0x24) + 0x24)));
        FastVecAdd(dir, dir, step);
    }
}
