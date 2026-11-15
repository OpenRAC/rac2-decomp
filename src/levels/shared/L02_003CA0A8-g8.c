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
extern struct Tuning D_L02_001AFFB8[] __attribute__((sda));
extern float D_L02_001AFFC0 __attribute__((sda));
extern int D_L02_001AFFC8 __attribute__((sda));
extern int D_L02_001AFFD0 __attribute__((sda));
extern float D_L02_001AFFD8 __attribute__((sda));
extern struct Pair D_L02_001AFFE0 NOT_SDA;
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern int func_00283D38(int, int, float);
extern float func_00283180(float), func_00283198(float), func_00283B98(float, float);
extern void func_002C3150(void *, void *, int, int, int, int, float);
extern void func_00282D30(void *, void *, float);

/* Spawns the effect's burst: 32 pairs of particles in a ring around the object. */
void func_L02_003CA0A8(char *obj)
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
    range.a = D_L02_001AFFC0 * (1.0f / 60.0f);
    t = D_L02_001AFFB8[0].speed[1] * (1.0f / 60.0f);
    range.b = t;
    speed = range;
    range = D_L02_001AFFE0;
    for (i = 0; i < 32; i++) {
        alpha = RandomIntRange(D_L02_001AFFC8, D_L02_001AFFB8[0].alpha[1]);
        r = RandomFloatRange(zero, 1.0f);
        color = FastTweenColor(D_L02_001AFFD0, D_L02_001AFFB8[0].colors[1], r);
        r = RandomFloatRange(speed.a, speed.b);
        vel[0] = FastSinOrCosA(angle) * r;
        vel[1] = FastSinOrCosB(angle) * r;
        vel[2] = zero;
        angle = FastAddRotations(angle, RandomFloatRange(range.a, range.b));
        SpawnHeroRelativeParticle(pos, vel, color, alpha & 255, RandomIntBelow(255) & 255, 0, D_L02_001AFFD8);
        FastVecScale(vel, vel, 0.8f);
        SpawnHeroRelativeParticle(pos, vel, color, alpha & 255, RandomIntBelow(255) & 255, 0, D_L02_001AFFB8[0].sizes[1]);
    }
}
