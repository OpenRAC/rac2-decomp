#include "common.h"
#include "common.h"


#include "common.h"


#include "common.h"

typedef int OozlaQuad __attribute__((mode(TI)));
extern int D_L01_001B2088;
extern float func_L01_003BAFB0(void);
extern void *func_00312D58(float *, float);
extern void func_002A0488(void *, int, int, int);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern void func_002C19D8(void *, void *, int, float, float);
extern void func_002BFB38(void *, void *, int, int);
extern float D_L01_001AFE18[];

/* Same body as func_L01_003B4200, with this function's own callees. */
/* Same body as func_L01_003D8C00, with this function's own callees. */
/* Spawns a water splash, bubbles and drops at the object, at most once every few frames. */
void func_L01_003DBCB8(char *object, int bubbles, int drops, int splash)
{
    float velocity[4], position[4];
    float height, angle, radius, size;
    char *state = *(char **)(object + 0x68);
    void *effect;
    int i, j, type, lifetime;
    if (D_L01_001B2088 - *(int *)(state + 0x40C) < 11)
        return;
    height = GetWaterHeight();
    if (splash) {
        *(OozlaQuad *)velocity = *(OozlaQuad *)(object + 0x10);
        velocity[2] = height;
        effect = SpawnScaledEffectMoby(velocity, 2.25f);
        if (effect)
            set_moby_color(effect, 0x60, 0x50, 0);
    }
    if (bubbles > 0) {
      i = bubbles;
      do {
        --i;
        velocity[0] = *(float *)(object + 0x10) + RandomFloatRange(-0.3f, 0.3f);
        velocity[1] = *(float *)(object + 0x14) + RandomFloatRange(-0.3f, 0.3f);
        velocity[2] = height;
        size = RandomFloatRange(0.3f, 0.6f);
        type = ((RandomIntBelow(6) + 20) << 24) | 0x5060;
        SpawnDriftingParticle_002C19D8(velocity, D_L01_001AFE18, type, size, 5250.0f);
      } while (i != 0);
    }
    if (drops > 0) {
      j = drops;
      do {
        --j;
        angle = RandomAngle();
        radius = RandomFloatRange(0.0f, 0.0500000045f);
        velocity[0] = FastSinOrCosA(angle) * radius;
        velocity[1] = FastSinOrCosB(angle) * radius;
        velocity[2] = RandomFloatRange(0.0500000045f, 0.13333334f);
        position[0] = *(float *)(object + 0x10) + velocity[0] * 8.0f;
        position[1] = *(float *)(object + 0x14) + velocity[0] * 8.0f;
        position[2] = height - RandomFloatRange(0.0f, 0.2f);
        type = RandomIntBelow(2);
        lifetime = RandomIntRange(90, 120);
        SpawnSparkParticle_002BFB38(position, velocity, type, lifetime);
      } while (j != 0);
    }
    *(int *)(state + 0x40C) = D_L01_001B2088;
}
