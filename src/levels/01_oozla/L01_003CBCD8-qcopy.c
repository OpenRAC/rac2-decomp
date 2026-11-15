#include "include_asm.h"
#include "names.h"

/* Needs the quadword copy (-frac2-qcopy with the barrier) and -fno-gcse. The table base is an `sda` incomplete array so the assembler expands it as one `la` in the loop instead of cc1 hoisting the %hi out of it. */

typedef int OozlaQuad __attribute__((mode(TI)));

extern int D_L01_001B2088 __attribute__((sda));
extern char D_L01_001B03E8[];
extern void func_002A6CF0(char *, int, int);
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
extern float D_L01_001AFE18[] __attribute__((sda));



/* Makes a water splash with bubbles and drops where the swamp monster hits the water. It will not repeat for a few frames. */
void func_L01_003CBCD8(char *object, int bubbles, int drops, int splash)
{
    float velocity[4], position[4];
    float height, angle, radius, size;
    void *effect;
    int i, j, type, lifetime;
    int *timer = 0;
    int dropCount = drops;
    int currentFrame;
    if (*(short *)(object + 0xAA) == 0xA8D /* Swamp Monster I Arm */) {
        timer = (int *)(*(char **)(object + 0x68) + 0xF4);
    } else if (*(short *)(object + 0xAA) == 0xA8E /* Swamp Monster I Eye */) {
        timer = (int *)(*(char **)(object + 0x68) + 0xC8);
    }
    if (timer == 0)
        func_002A6CF0(D_L01_001B03E8, *(short *)(object + 0xAA), *(short *)(object + 0xB2));
    currentFrame = D_L01_001B2088;
    if (currentFrame - *timer < 11)
        return;
    height = GetWaterHeight();
    if (splash) {
        *(OozlaQuad *)velocity = *(OozlaQuad *)(object + 0x10);
        velocity[2] = height;
        effect = SpawnScaledEffectMoby(velocity, 4.0f);
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
        size = RandomFloatRange(0.5f, 0.9f);
        type = ((RandomIntBelow(6) + 20) << 24) | 0x5060;
        SpawnDriftingParticle_002C19D8(velocity, D_L01_001AFE18, type, size, 5250.0f);
      } while (i != 0);
    }
    if (dropCount > 0) {
      j = dropCount;
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
    *timer = D_L01_001B2088;
}
