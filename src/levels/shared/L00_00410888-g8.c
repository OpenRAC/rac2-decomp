#include "common.h"

typedef int EffectVector __attribute__((mode(TI)));

extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002ACEC0(void *, void *, void *, float);
extern float func_002A7878(float, float);
extern float func_00283B98(float, float);
extern void func_00282D30(void *, void *, float);
extern int func_002A7820(int, int);
extern float func_002A78D8(float, float);
extern void func_002C6DD8(void *, void *, int, float);
extern float func_00282C48(float);
extern void func_002AB668(void *, void *, float);
extern void func_002ACDE8(void *, void *, void *);
extern int func_00283CF0(float);
extern void func_00282CF0(void *, void *, void *);
extern void *func_002C16C0(void *, void *, int, int, int, int, float, float, float, float, float);
extern char D_0018A550[];

typedef struct {
    char pad[0x110];
    float velocity[4];
    char pad2[0x220];
    int flag;
} EffectHero;

extern EffectHero D_00189E20;
extern float D_L00_001B1300 __attribute__((sda));
extern float D_L00_001B1304 __attribute__((sda));
extern int D_L00_001B1308 __attribute__((sda));
extern int D_L00_001B130C __attribute__((sda));
extern int D_L00_001B1310 __attribute__((sda));
extern float D_L00_001B1314 __attribute__((sda));
extern float D_L00_001B1318 __attribute__((sda));
extern float D_L00_001B131C __attribute__((sda));
extern float D_L00_001B1320 __attribute__((sda));
extern float D_L00_001B1324 __attribute__((sda));
extern float D_L00_001B1328 __attribute__((sda));

/* Emit two groups of particles around the object, rotating each emission direction. */
void func_L00_00410888(char *object, int mode)
{
    float rotation[4], direction[4], basis[4], position[4], point[4], velocity[4], offset[4];
    float angle, jitter, scale, speed, spread;
    int i, j, life, kind, life2;

    *(EffectVector *)basis = 0;
    basis[0] = 0.3f;
    basis[1] = -1.0f;
    basis[3] = 1.0f;
    matrix_mul_vec3(basis, basis, object + 0xc0);
    angle = 0.0f;
    FastVecAdd(position, object + 0x10, basis);
    ApplyAxisRotationToQuaternion(basis, D_0018A550, D_0018A550 + 0x10, 0.349065899848938f);
    qcopy(direction, basis);
    for (i = 0; i < mode * 20 + 20; i++) {
        angle = FastAddRotations(angle, RandomFloatRange(0.0f, 0.6283186f));
        FastVecScale(offset, direction, RandomFloatRange(7.0f, 60.0f) * 0.016666668f);
        life = RandomIntRange(10, 30);
        point[0] = position[0] + RandomSignedFloatRange(0.0f, 0.2f);
        point[1] = position[1] + RandomSignedFloatRange(0.0f, 0.2f);
        point[2] = position[2] + RandomSignedFloatRange(0.0f, 0.2f);
        SpawnTrailParticle_002C6DD8(point, offset, life, 0.0022222223f);
        if (FloatAbs(angle) > 0.00001f) {
            BuildAxisAngleQuaternion(rotation, D_0018A550, angle);
            RotateVectorByQuaternion(direction, basis, rotation);
        }
    }

    ApplyAxisRotationToQuaternion(basis, D_0018A550, D_0018A550 + 0x10, D_L00_001B1300 * 0.017453294f);
    angle = 0.0f;
    qcopy(direction, basis);
    /* Only external calls read this local vector after its clear. */
    qzero_nc(offset);
    if (gHeroState.flag)
        FastVecScale(offset, gHeroState.velocity, 1.7f);
    scale = D_L00_001B1324;
    speed = D_L00_001B1328;
    spread = D_L00_001B1304;
    if (mode) {
        scale = 2.0f;
        speed = 10000.0f;
        spread = 0.8f;
    }
    for (j = 19; j >= 0; j--) {
        angle = FastAddRotations(angle, RandomFloatRange(0.0f, 0.6283186f));
        FastVecScale(velocity, direction,
                      RandomFloatRange(D_L00_001B1318 * 0.016666668f,
                                    D_L00_001B131C * 0.016666668f));
        FastVecAdd(velocity, velocity, offset);
        kind = D_L00_001B1310;
        life2 = FloatToInt(RandomSignedFloatRange(1.0f, 2.0f));
        point[0] = position[0] + RandomSignedFloatRange(0.0f, spread);
        point[1] = position[1] + RandomSignedFloatRange(0.0f, spread);
        point[2] = position[2] + RandomSignedFloatRange(0.0f, spread);
        jitter = RandomFloatRange(D_L00_001B1320, scale) * 210000.0f;
        FastVecSub(point, point, velocity);
        SpawnBurstParticle_002C16C0(point, velocity, kind, D_L00_001B1308, D_L00_001B130C,
                      life2, jitter, speed, D_L00_001B1314, 0.0f, 0.0f);
        if (FloatAbs(angle) > 0.00001f) {
            BuildAxisAngleQuaternion(rotation, D_0018A550, angle);
            RotateVectorByQuaternion(direction, basis, rotation);
        }
    }
}
