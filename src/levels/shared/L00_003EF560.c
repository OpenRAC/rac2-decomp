#include "common.h"

typedef int BurstWord128 __attribute__((mode(TI)));
typedef union { BurstWord128 word; float f[4]; } BurstVector;
typedef struct { unsigned int values[6]; } BurstColors;
extern BurstVector D_L00_001B8DC0 __attribute__((nosda));
extern BurstColors D_L00_001B0840 __attribute__((nosda));
extern BurstColors D_L00_001B0858 __attribute__((nosda));
typedef struct { char pad[0x20]; float x, y, z; } BurstLight;
extern BurstLight D_L00_0029AEF0 __attribute__((nosda));
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern float func_002A7878(float, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282FB8(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern int func_002A7820(int, int);
extern char *func_00308600(void *, void *, int, int, int);
extern float func_002A7940(void);
extern void func_002AF000(float *, float, float, float);
extern void func_00282C88(BurstWord128 *);
extern int func_002A77E0(int);
extern char *func_002BBCB0(void *, void *, unsigned int, unsigned int, int, int, int, int, float, float);
extern char *func_00312B70(void *, void *, int, int);
extern int func_002AAFA0(unsigned int, int);
extern char *func_002BCB00(void *, void *, int, int, int, int, int, int, int, float);

/* Starts a big burst at the position: it throws out sparks, trails and smoke with random
   speeds and colours, and adds a bright flash of light. */
void func_L00_003EF560(char *object, BurstVector *position) {
    BurstVector delta, velocity, random;
    /* Both 24-byte local copies begin on observed 16-byte stack boundaries. */
    BurstColors colorsA __attribute__((aligned(16)));
    BurstColors colorsB __attribute__((aligned(16)));
    char *base;
    char *base2;
    BurstVector *vp;
    float distance, pitch, yaw, speed, rate;
    int i, j, k, a, b, lifetimeA, lifetimeB;
    int colorA, colorB;
    unsigned int *pa, *pb;
    rate = 0.016666668f;
    base = object + 0xC0;
    FastVecSub(&delta, &gCameraPosition_L00, position);
    distance = FastVecLength(&delta);
    random.word = 0;
    random.f[0] = RandomFloatRange(-1.0f, 1.0f);
    random.f[1] = RandomFloatRange(-1.0f, 1.0f);
    random.f[2] = RandomFloatRange(-1.0f, 1.0f);
    delta.f[2] += distance * 0.5f;
    velocity.word = random.word;
    vec_scale_to_length(&velocity, &velocity, distance * 0.0033333336468786f);
    vec_scale_to_length(&delta, &delta, (distance + distance) * rate);
    FastVecAdd(&velocity, &velocity, &delta);
    FastVectorDivideHelper(&velocity, &velocity, 0.1666666716337204f);
    matrix_mul_vec3(&velocity, &velocity, base);
    lifetimeA = RandomIntRange(60, 90);
    SpawnSpinningDebrisMoby(position, &velocity, lifetimeA, 0, 0);
    i = 8;
    do {
        i--;
        pitch = RandomFloatRange(0.4363323450088501f, 0.7853982448577881f);
        yaw = RandomAngle();
        speed = RandomFloatRange(13.0f, 20.0f);
        BuildSphericalOffset(random.f, speed * 0.016666668f, yaw, pitch);
        matrix_mul_vec3(&random, &random, object + 0xC0);
        lifetimeA = RandomIntRange(60, 90);
        SpawnSpinningDebrisMoby(position, &random, lifetimeA, 1, 0);
    } while (i >= 0);
    vp = &velocity;
    ClearVector128(&vp->word);
    j = 9;
    do {
        j--;
        speed = RandomFloatRange(8.0f, 10.0f) * 0.016666668f;
        colorsA = D_L00_001B0840;
        colorsB = D_L00_001B0858;
        pa = &colorsA.values[RandomIntBelow(6)];
        pb = &colorsB.values[RandomIntBelow(6)];
        lifetimeA = RandomIntRange(20, 40);
        lifetimeB = RandomIntRange(50, 70);
        SpawnFireworkSparkParticle(position, vp, *pa, *pb, lifetimeA, lifetimeB, 0, 0,
                     600000.0f, speed * 1.5f);
    } while (j >= 0);
    D_L00_0029AEF0.x = D_L00_0029AEF0.z = D_L00_0029AEF0.y = 40.0f;
    SpawnTemplateEffectMoby(&D_L00_0029AEF0, position, 0, 0);
    base2 = object + 0xC0;
    k = 49;
    do {
        k--;
        pitch = RandomFloatRange(0.13962635397911072f, 0.6108652949333191f);
        yaw = RandomAngle();
        speed = RandomFloatRange(16.0f, 30.0f);
        BuildSphericalOffset(random.f, speed * 0.016666668f, yaw, pitch);
        colorA = SwapPackedColorChannels(0x4F007FFF, 0);
        colorB = SwapPackedColorChannels(0x1F00007F, 0);
        matrix_mul_vec3(&random, &random, base2);
        lifetimeA = RandomIntRange(60, 120);
        SpawnSparkParticle_002BCB00(position, &random, colorA, colorB, lifetimeA - 10, 1, -1, -1, 0, 40000.0f);
    } while (k >= 0);
}
