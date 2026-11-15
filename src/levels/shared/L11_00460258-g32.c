#include "names.h"
typedef unsigned int u32;
struct ParticleSettings {
    int *colors;
    short *sizes;
    short *range;
    int unknown0C;
    int lifetime;
    float jitter;
};
extern float D_L11_001B22D0 __attribute__((sda));
extern float D_L11_001B22D4 __attribute__((sda));
extern float D_L11_001B22D8 __attribute__((sda));
extern float D_L11_001B22DC __attribute__((sda));
extern u32 D_L11_001B22C0 __attribute__((sda));
extern struct ParticleSettings D_L11_001B2300 __attribute__((sda));
extern float func_00283CE0(int);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern void *func_L02_003449D8(void *, void *, void *, void *, int);
extern void *func_002C65A0(void *, void *, int, u32, int, int, int, float, float, float, int);
extern float func_00283B98(float, float);

/* Spawns a ring of sparks and puffs around a position, spread evenly in angle with random speeds. */
void func_L11_00460258(void *position, int count) {
    float velocity[4];
    float step = 6.2831854820251465f / IntToFloat(count);
    float angle = RandomFloatRange(-3.1415927410125732f, 3.1415927410125732f);
    float speed;
    int sparksLeft, sparkKind, sparkOffset;
    if (count > 0) {
        sparksLeft = count;
        do {
            sparksLeft--;
            speed = RandomFloatRange(D_L11_001B22D0, D_L11_001B22D4) * 0.01666666753590107f;
            velocity[0] = speed * FastSinOrCosA(angle);
            velocity[1] = speed * FastSinOrCosB(angle);
            velocity[2] = RandomFloatRange(D_L11_001B22D8, D_L11_001B22DC) * 0.01666666753590107f;
            sparkKind = RandomIntBelow(2);
            sparkOffset = RandomIntRange(-2, 2);
            SpawnEnemyRecord(position, velocity, &D_L11_001B2300, (void *)sparkKind, sparkOffset);
            velocity[2] = 0.0f;
            SpawnGravityFadeParticle(position, velocity, 60, D_L11_001B22C0, 3, 48, 0, RandomFloatRange(5.0f, 6.0f) * 210000.0f, 0.0f, 0.0f, 0);
            angle = FastAddRotations(angle, step);
        } while (sparksLeft);
    }
}
