#include "common.h"
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_002A7820(int, int);
extern int func_002A77E0(int);
extern void *func_002BFB38(void *, void *, int, int);
extern void func_002A7A00(float *, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void *func_L00_00338AE0(char *, char *, int, float, float);
extern int func_00283CF0(float);
extern float D_L06_001B2FC8 MACRO_ADDR;
extern char D_L06_001A8F20[] MACRO_ADDR;

/* Spawns a splash of small particles and ring effects at a position. */
void func_L06_00403DA8(void *unused, void *position)
{
    float vector[4];
    float angle, radius;
    int life, kind;
    char *effect;
    int i;
    float *data = &D_L06_001B2FC8;
    for (i = 15; i >= 0; --i) {
        angle = RandomAngle();
        radius = RandomFloatRange(0.0f, 0.050000004f);
        vector[0] = FastSinOrCosA(angle) * radius;
        vector[1] = FastSinOrCosB(angle) * radius;
        vector[2] = RandomFloatRange(0.050000004f, 0.10833334f);
        life = RandomIntRange(90, 120);
        kind = RandomIntBelow(2);
        SpawnSparkParticle_002BFB38(position, vector, kind, life);
    }
    for (i = 0; i < 16; ++i) {
        RandomDirectionVector(vector, 1.0f, 1.0f);
        FastVecAdd(vector, vector, position);
        vector[2] = D_L06_001B2FC8 + 0.05f;
        effect = SpawnRandomTintedEffect((char *)vector, D_L06_001A8F20, (int)data, RandomFloatRange(0.7f, 1.0f), i == 0 ? 2.0f : -2.0f);
        if (effect != 0)
            *(short *)(effect + 10) = FloatToInt(RandomFloatRange(30.0f, 60.0f));
    }
}
