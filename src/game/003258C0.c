#include "names.h"
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern float func_002A7940(void);
extern float func_002A78D8(float, float);
extern void func_002AF000(float *, float, float, float);
extern void func_00282CC0(float *, float *, int);
extern void func_002C2210(float *, int, int, int, int, float *, int, float, float, float);

/* Spawns two small puffs that drift away from a point with random speed and size. */
void func_003258C0(float *self, int unused, int basis)
{
    float velocity[4];
    float scale = RandomFloatRange(0.10000000149011612f, 0.25f);
    int coin = RandomIntBelow(2);
    int side;
    float yaw, pitch;

    if (coin == 0)
        coin = coin - 1;
    side = coin;
    yaw = RandomAngle();
    pitch = RandomFloatRange(0.349065899848938f, 1.5358898639678955f);

    BuildSphericalOffset(velocity, RandomFloatRange(0.05000000074505806f, 0.10000000149011612f), yaw, pitch);
    FastVecAdd(velocity, velocity, basis);
    self[0] = self[0] + RandomSignedFloatRange(0.0f, 0.15000000596046448f);
    self[1] = self[1] + RandomSignedFloatRange(0.0f, 0.15000000596046448f);
    SpawnGroundEffectParticle(self, 0x1E, 0x7F207F7F, 0, side, velocity, 0, scale * 0.10000000149011612f, scale,
                  0.006000000052154064f);
    SpawnGroundEffectParticle(self, 0x1E, 0x7F7F7F7F, 1, -side, velocity, 0, scale * 0.07000000029802322f,
                  scale * 0.699999988079071f, 0.006000000052154064f);
}
