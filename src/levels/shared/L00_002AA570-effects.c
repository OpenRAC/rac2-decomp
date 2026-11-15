#include "common.h"

/* Resident fields accessed by the paired particle emitter. */
typedef struct {
    char pad0[128];
    float x;
    float y;
    char pad88[16];
    float angle;
    char pad9c[660];
    float z;
    char pad334[1812];
    unsigned short counter;
} ParticleResidentFields;
extern ParticleResidentFields D_00189E20_20;
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void *func_L00_00338AE0(float, float, float *, float *, float *);

/* Every so often, puffs out two small particles to the sides of the hero. */
void func_L00_002AA570(char *emitInterval, int threshold)
{
    float velocity[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float turn;
    float size;
    int count;
    int i;


    count = D_00189E20_20.counter + 1;
    D_00189E20_20.counter = count;
    if (threshold < (short)count) {
        for (i = 0; i < 2; i++) {
            if (i == 0)
                turn = FastAddRotations(D_00189E20_20.angle, 0.785398006f);
            else
                turn = fast_subtract_rotations(D_00189E20_20.angle, 0.785398006f);
            velocity[0] = FastSinOrCosA(turn) * 0.0100000007f;
            velocity[1] = FastSinOrCosB(turn) * 0.0100000007f;
            position[0] = D_00189E20_20.x + velocity[0] * 18.0f;
            position[1] = D_00189E20_20.y + velocity[1] * 18.0f;
            position[2] = D_00189E20_20.z;
            velocity[2] = 0.0f;
            velocity[0] = velocity[0] - FastSinOrCosA(D_00189E20_20.angle) * 0.0250000022f;
            velocity[1] = velocity[1] - FastSinOrCosB(D_00189E20_20.angle) * 0.0250000022f;
            size = RandomFloatRange(0.4f, 0.5f);
            SpawnRandomTintedEffect(size, i == 0 ? 2.0f : -2.0f, position, velocity, &D_00189E20_20.z);
            D_00189E20_20.counter = emitInterval == 0 ? 0 : RandomIntBelow((int)emitInterval);
        }
    }
}
