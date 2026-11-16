#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
extern void vec_random_direction(void *, float, float);
extern void FastVecAdd(void *, void *, void *);
extern float math_random_float_range(float, float);
extern s32 math_random_int_range(s32, s32);
extern s32 FloatToInt(float);
extern float g_smoke_spark_dir_min __attribute__((sda));
extern float g_smoke_spark_dir_max[] __attribute__((nosda));
extern float g_smoke_spark_speed_min[] __attribute__((nosda));
extern float g_smoke_spark_speed_max[] __attribute__((nosda));
extern float g_smoke_particle_scale_a __attribute__((sda));
extern float g_smoke_particle_scale_b[] __attribute__((nosda));
extern s32 g_smoke_particle_texture_a __attribute__((sda));
extern s32 g_smoke_particle_texture_b[] __attribute__((nosda));
extern s32 g_smoke_color_a_min __attribute__((sda));
extern s32 g_smoke_color_a_max[] __attribute__((nosda));
extern s32 g_smoke_color_b_min[] __attribute__((nosda));
extern s32 g_smoke_color_b_max[] __attribute__((nosda));
extern s32 g_smoke_spark_count __attribute__((sda));
extern u32 math_random_int_below(s32);
extern u8 *part_spawn_hero_relative(void *, void *, s32, u32, u32, s32, float);
extern void vec_clear_128(void *);
/* Emits a puff of smoke and a few sparks from the object each frame. */
void snivelak_emit_smoke_sparks(u8 *moby) {
  float velocity[4];
  float pos[4];
  float tick = 0.016666668f;
  s32 i;
  u32 color;
  u32 random;
  u8 *particle;
  u8 *origin;
  u32 nv;
  origin = moby + 0x10;
  vec_random_direction(velocity, g_smoke_spark_dir_min * tick, g_smoke_spark_dir_max[0] * tick);
  color = math_random_int_range(g_smoke_color_a_min, g_smoke_color_a_max[0]) & 255;
  random = math_random_int_below(255) & 255;
  particle = part_spawn_hero_relative(origin, velocity, g_smoke_particle_texture_a, color, random, 0, g_smoke_particle_scale_a);
  if (particle)
    particle[9] = FloatToInt(4.0f) - 16;
  vec_clear_128(velocity);
  for (i = 0; i < g_smoke_spark_count; i++) {
    origin = pos;
    vec_random_direction(origin, 0.0f, 0.25f);
    FastVecAdd(origin, origin, moby + 0x10);
    velocity[2] = -(math_random_float_range(g_smoke_spark_speed_min[0], g_smoke_spark_speed_max[0]) * tick);
    color = math_random_int_range(g_smoke_color_b_min[0], g_smoke_color_b_max[0]) & 255;
    random = math_random_int_below(255) & 255;
    particle = part_spawn_hero_relative(origin, velocity, g_smoke_particle_texture_b[0], color, random, 0, g_smoke_particle_scale_b[0]);
    if (particle)
      particle[9] = FloatToInt(4.0f) - 16;
  }

}

