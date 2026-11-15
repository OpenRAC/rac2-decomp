#include "names.h"
/* func_PAL_L16_00412C28, the PAL copy of func_L16_0040DC70: the same C, with the tick at 50 Hz and both alphas scaled. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
extern void vec_random_direction(void *, float, float);
extern void FastVecAdd(void *, void *, void *);
extern float math_random_float_range(float, float);
extern s32 math_random_int_range(s32, s32);
extern s32 FloatToInt(float);
extern float D_L16_001B1670 __attribute__((sda));
extern float D_L16_001B1674[] __attribute__((nosda));
extern float D_L16_001B1678[] __attribute__((nosda));
extern float D_L16_001B167C[] __attribute__((nosda));
extern float D_L16_001B1680 __attribute__((sda));
extern float D_L16_001B1684[] __attribute__((nosda));
extern s32 D_L16_001B1688 __attribute__((sda));
extern s32 D_L16_001B168C[] __attribute__((nosda));
extern s32 D_L16_001B1690 __attribute__((sda));
extern s32 D_L16_001B1694[] __attribute__((nosda));
extern s32 D_L16_001B1698[] __attribute__((nosda));
extern s32 D_L16_001B169C[] __attribute__((nosda));
extern s32 D_L16_001B16A0 __attribute__((sda));
extern u32 math_random_int_below(s32);
extern u8 *part_spawn_hero_relative(void *, void *, s32, u32, u32, s32, float);
extern void vec_clear_128(void *);
void func_PAL_L16_00412C28(u8 *arg) {
  float velocity[4];
  float pos[4];
  float tick = 0.020000001f;
  s32 i;
  u32 color;
  u32 alpha;
  u32 random;
  u8 *particle;
  u8 *origin;
  origin = arg + 0x10;
  vec_random_direction(velocity, D_L16_001B1670 * tick, D_L16_001B1674[0] * tick);
  color = (((s32)(math_random_int_range(D_L16_001B1690, D_L16_001B1694[0])) * 5 + 2) / 6) & 255;
  random = math_random_int_below(255) & 255;
  particle = part_spawn_hero_relative(origin, velocity, D_L16_001B1688, color, random, 0, D_L16_001B1680);
  if (particle)
    particle[9] = FloatToInt(4.0f) - 16;
  vec_clear_128(velocity);
  for (i = 0; i < D_L16_001B16A0; i++) {
    origin = pos;
    vec_random_direction(origin, 0.0f, 0.25f);
    FastVecAdd(origin, origin, arg + 0x10);
    velocity[2] = -(math_random_float_range(D_L16_001B1678[0], D_L16_001B167C[0]) * tick);
    alpha = (((s32)(math_random_int_range(D_L16_001B1698[0], D_L16_001B169C[0])) * 5 + 2) / 6) & 255;
    random = math_random_int_below(255) & 255;
    particle = part_spawn_hero_relative(origin, velocity, D_L16_001B168C[0], alpha, random, 0, D_L16_001B1684[0]);
    if (particle)
      particle[9] = FloatToInt(4.0f) - 16;
  }

}

