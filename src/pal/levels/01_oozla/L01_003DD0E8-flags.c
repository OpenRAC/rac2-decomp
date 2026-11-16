#include "include_asm.h"

#include "common.h"
typedef int OozlaQuad __attribute__((mode(TI)));
extern int g_oozla_intro_stage;
extern float level_get_water_height_pal(void);
extern void *moby_spawn_scaled_effect(float *, float);
extern void set_moby_color(void *, int, int, int);
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern void *part_spawn_drifting(void *, void *, int, float, float);
extern void *part_spawn_spark_2_pal(void *, void *, int, int);
extern float g_water_l01_height[];

/* Spawns a water splash at the moby: an optional ring effect, drifting bubbles and flying drops (PAL). */
void part_spawn_water_splash_pal(char *moby, int bubbles, int drops, int splash)
{
    float velocity[4], position[4];
    float height, angle, radius, size;
    char *vars = *(char **)(moby + 0x68);
    void *effect;
    int i, j, type, lifetime;
    if (g_oozla_intro_stage - *(int *)(vars + 0x6C) < 11)
        return;
    height = level_get_water_height_pal();
    if (splash) {
        *(OozlaQuad *)velocity = *(OozlaQuad *)(moby + 0x10);
        velocity[2] = height;
        effect = moby_spawn_scaled_effect(velocity, 2.25f);
        if (effect)
            set_moby_color(effect, 0x60, 0x50, 0);
    }
    if (bubbles > 0) {
      i = bubbles;
      do {
        --i;
        velocity[0] = *(float *)(moby + 0x10) + math_random_float_range(-0.3f, 0.3f);
        velocity[1] = *(float *)(moby + 0x14) + math_random_float_range(-0.3f, 0.3f);
        velocity[2] = height;
        size = math_random_float_range(0.3f, 0.6f);
        type = ((math_random_int_below(6) + 20) << 24) | 0x5060;
        part_spawn_drifting(velocity, g_water_l01_height, type, size, 5250.0f);
      } while (i != 0);
    }
    if (drops > 0) {
      j = drops;
      do {
        --j;
        angle = math_random_angle();
        radius = math_random_float_range(0.0f, 0.060000002f);
        velocity[0] = math_fast_sin_or_cos_a(angle) * radius;
        velocity[1] = math_fast_sin_or_cos_b(angle) * radius;
        velocity[2] = math_random_float_range(0.060000002f, 0.16000001f);
        position[0] = *(float *)(moby + 0x10) + velocity[0] * 8.0f;
        position[1] = *(float *)(moby + 0x14) + velocity[0] * 8.0f;
        position[2] = height - math_random_float_range(0.0f, 0.2f);
        type = math_random_int_below(2);
        lifetime = math_random_int_range(90, 120);
        part_spawn_spark_2_pal(position, velocity, type, lifetime);
      } while (j != 0);
    }
    *(int *)(vars + 0x6C) = g_oozla_intro_stage;
}
