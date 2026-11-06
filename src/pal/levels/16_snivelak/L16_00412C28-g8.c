/* func_PAL_L16_00412C28, the PAL copy of func_L16_0040DC70: the same C, with the tick at 50 Hz and both alphas scaled. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
extern void func_002A7A00(void *, float, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A7878(float, float);
extern s32 func_002A7820(s32, s32);
extern s32 func_00283CF0(float);
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
extern u32 func_002A77E0(s32);
extern u8 *func_002C3150(void *, void *, s32, u32, u32, s32, float);
extern void func_00282C88(void *);
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
  func_002A7A00(velocity, D_L16_001B1670 * tick, D_L16_001B1674[0] * tick);
  color = (((s32)(func_002A7820(D_L16_001B1690, D_L16_001B1694[0])) * 5 + 2) / 6) & 255;
  random = func_002A77E0(255) & 255;
  particle = func_002C3150(origin, velocity, D_L16_001B1688, color, random, 0, D_L16_001B1680);
  if (particle)
    particle[9] = func_00283CF0(4.0f) - 16;
  func_00282C88(velocity);
  for (i = 0; i < D_L16_001B16A0; i++) {
    origin = pos;
    func_002A7A00(origin, 0.0f, 0.25f);
    func_00282CC0(origin, origin, arg + 0x10);
    velocity[2] = -(func_002A7878(D_L16_001B1678[0], D_L16_001B167C[0]) * tick);
    alpha = (((s32)(func_002A7820(D_L16_001B1698[0], D_L16_001B169C[0])) * 5 + 2) / 6) & 255;
    random = func_002A77E0(255) & 255;
    particle = func_002C3150(origin, velocity, D_L16_001B168C[0], alpha, random, 0, D_L16_001B1684[0]);
    if (particle)
      particle[9] = func_00283CF0(4.0f) - 16;
  }

}

