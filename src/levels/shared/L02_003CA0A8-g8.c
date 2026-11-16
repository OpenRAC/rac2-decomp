#include "common.h"

struct Pair { float a, b; };
/* The effect's tuning block: a member at its start is read as an absolute macro load, which is
   how retail reads the second value of each pair. */
struct Tuning {
    float rates[2];
    float speed[2];
    int alpha[2];
    int colors[2];
    float sizes[2];
};
extern struct Tuning g_glow_effect_params[] __attribute__((sda));
extern float g_glow_range_scale __attribute__((sda));
extern int g_glow_alpha_min __attribute__((sda));
extern int g_glow_color_start __attribute__((sda));
extern float g_glow_size __attribute__((sda));
extern struct Pair g_glow_range_pair NOT_SDA;
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern int FastTweenColor(int, int, float);
extern float math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float), FastAddRotations(float, float);
extern void *part_spawn_hero_relative(void *, void *, int, int, int, int, float);
extern void FastVecScale(void *, void *, float);

/* Spawns the effect's burst: 32 pairs of particles in a ring around the object. */
void SpawnEffectParticleRing(char *obj)
{
    float pos[4] __attribute__((aligned(16)));
    struct Pair speed, range;
    float vel[4] __attribute__((aligned(16)));
    int i, alpha, color;
    float angle, zero, r, t;

    qcopy(pos, obj + 0x10);
    t = 0.5f;
    pos[2] += t;
    angle = zero = 0.0f;
    range.a = g_glow_range_scale * (1.0f / 60.0f);
    t = g_glow_effect_params[0].speed[1] * (1.0f / 60.0f);
    range.b = t;
    speed = range;
    range = g_glow_range_pair;
    for (i = 0; i < 32; i++) {
        alpha = math_random_int_range(g_glow_alpha_min, g_glow_effect_params[0].alpha[1]);
        r = math_random_float_range(zero, 1.0f);
        color = FastTweenColor(g_glow_color_start, g_glow_effect_params[0].colors[1], r);
        r = math_random_float_range(speed.a, speed.b);
        vel[0] = math_fast_sin_or_cos_a(angle) * r;
        vel[1] = math_fast_sin_or_cos_b(angle) * r;
        vel[2] = zero;
        angle = FastAddRotations(angle, math_random_float_range(range.a, range.b));
        part_spawn_hero_relative(pos, vel, color, alpha & 255, math_random_int_below(255) & 255, 0, g_glow_size);
        FastVecScale(vel, vel, 0.8f);
        part_spawn_hero_relative(pos, vel, color, alpha & 255, math_random_int_below(255) & 255, 0, g_glow_effect_params[0].sizes[1]);
    }
}
