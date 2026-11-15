/* func_L00_00415DE8: explosion burst (family F6, func_L16_00406550 with level 0's colours).
 * The emitters take their float parameters interleaved with the ints; one effect pointer serves
 * the four leading fire emitters.
 */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef float Vec4[4] __attribute__((aligned(16)));
#define F(p, o) (*(float *)((u8 *)(p) + (o)))
#define I(p, o) (*(int *)((u8 *)(p) + (o)))

typedef struct { u8 pad[0x140]; float target[4]; } CameraView;
typedef struct { u8 pad[0xD4]; u8 *sparkColors; u8 pad2[0x98]; u8 *fireColors; } EffectTables;

extern float D_L00_001B13EC __attribute__((sda));
extern float D_L00_001B13F0 __attribute__((sda));
extern int D_L00_001B13F4 __attribute__((sda));
extern float D_L00_001A8F20[4] MACRO_ADDR;
extern CameraView D_L00_001B8C80;
extern EffectTables D_L00_001FE940;

extern u8 *func_002C65A0(void *, void *, int, int, int, int, int, float, float, float, int);
extern float func_00283248(float, float);
extern float func_002A78D8(float, float);
extern int func_00283CF0(float);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *, void *, void *);
extern u8 *func_002C7970(void *, void *, int, int, int, int, int, float, float, float, int);
extern void func_00282D30(void *, void *, float);
extern void func_002AB668(void *, void *, float);
extern void func_002ACDE8(void *, void *, void *);
extern u8 *func_002C6DD8(void *, void *, int, float);
extern void func_00308408(void *, void *, void *, int, int, int, int, int, float);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, int, int, int, int, int, float);
extern void func_002AF000(float *, float, float, float);
extern u8 *func_002BDCE8(void *, float, float, int, void *, int, int, float, float);
extern float func_00283CE0(int);

/* Sets off an explosion with fire, sparks, smoke and a shockwave. */
void func_L00_00415DE8(u8 *object, void *unused)
{
    Vec4 position;
    Vec4 velocity;
    Vec4 rotation;
    u8 *state = *(u8 **)(object + 0x68);
    float inner, outer, angle, speed;
    u8 *effect;
    int coreIdx, glowIdx, brightIdx, largeIdx, smallIdx, debrisIdx, smokeIdx, sign;

    inner = D_L00_001B13EC * F(state, 0x14) * 210000.0f;
    outer = D_L00_001B13F0 * F(state, 0x14) * 210000.0f;
    effect = SpawnGravityFadeParticle(object + 0x10, D_L00_001A8F20, D_L00_001B13F4, 0x388EF7, 0, 100, 0, inner, outer, 0.0f, 0);
    if (effect)
        effect[2] = D_L00_001FE940.fireColors[0];
    effect = SpawnGravityFadeParticle(object + 0x10, D_L00_001A8F20, D_L00_001B13F4, 0x63F7, 0, 100, 0, inner, outer, 0.0f, 0);
    if (effect)
        effect[2] = D_L00_001FE940.fireColors[0];
    for (coreIdx = 1; coreIdx >= 0; coreIdx--) {
        effect = SpawnGravityFadeParticle(object + 0x10, D_L00_001A8F20, D_L00_001B13F4, 0x388EF7, 0, 127, 0, inner, outer, 0.0f, 0);
        if (effect)
            effect[2] = D_L00_001FE940.fireColors[5];
    }
    for (glowIdx = 1; glowIdx >= 0; glowIdx--) {
        effect = SpawnGravityFadeParticle(object + 0x10, D_L00_001A8F20, D_L00_001B13F4, 0x388EF7, 0, 127, 0, inner, outer, 0.0f, 0);
        if (effect)
            effect[2] = D_L00_001FE940.fireColors[6];
    }
    for (brightIdx = 0; brightIdx < I(state, 0x20); brightIdx++) {
        float heading, angle, size, speed;
        int lifetime, phase;
        heading = FastMatrixHelperA(D_L00_001B8C80.target[0] - F(object, 0x10), D_L00_001B8C80.target[1] - F(object, 0x14));
        phase = FloatToInt(RandomSignedFloatRange(2.0f, 5.0f));
        lifetime = RandomIntRange(30, 50);
        position[0] = F(object, 0x10) + RandomSignedFloatRange(0.0f, 0.1f) * F(state, 0x14);
        position[1] = F(object, 0x14) + RandomSignedFloatRange(0.0f, 0.1f) * F(state, 0x14);
        position[2] = F(object, 0x18) + RandomSignedFloatRange(0.0f, 0.1f) * F(state, 0x14);
        size = RandomFloatRange(0.6f, 1.0f) * F(state, 0x14);
        speed = RandomFloatRange(9.0f, 12.0f) * F(state, 0x14);
        angle = FastAddRotations(heading, RandomSignedFloatRange(0.0f, 1.3962636f));
        velocity[0] = FastSinOrCosA(angle) * 0.016666668f * speed;
        velocity[1] = FastSinOrCosB(angle) * 0.016666668f * speed;
        velocity[2] = 0.0f;
        speed = RandomFloatRange(0.0f, 12.0f) * F(state, 0x14);
        velocity[2] = speed * 0.016666668f;
        SpawnFadingDriftParticle(position, velocity, lifetime, 0x407FFF, phase, 127, 127, size * 210000.0f, F(state, 0x14) * 2100.0f, 0.00405555591f, 1);
        {
            u8 *effect = SpawnFadingDriftParticle(position, velocity, lifetime, 0x20FF, -(phase * 2), 48, 48, size * 1260000.0f, F(state, 0x14) * 4200.0f, 0.00405555591f, 0);
            if (effect)
                effect[2] = D_L00_001FE940.sparkColors[0];
        }
    }
    for (largeIdx = 0; largeIdx < I(state, 0x24); largeIdx++) {
        float heading, angle, size, speed;
        int lifetime, phase;
        heading = FastMatrixHelperA(D_L00_001B8C80.target[0] - F(object, 0x10), D_L00_001B8C80.target[1] - F(object, 0x14));
        phase = FloatToInt(RandomSignedFloatRange(2.0f, 5.0f));
        lifetime = RandomIntRange(30, 50);
        position[0] = F(object, 0x10) + RandomSignedFloatRange(0.0f, 0.1f) * F(state, 0x14);
        position[1] = F(object, 0x14) + RandomSignedFloatRange(0.0f, 0.1f) * F(state, 0x14);
        position[2] = F(object, 0x18) + RandomSignedFloatRange(0.0f, 0.1f) * F(state, 0x14);
        size = RandomFloatRange(0.75f, 1.5f) * F(state, 0x14);
        speed = RandomFloatRange(9.0f, 12.0f) * F(state, 0x14);
        angle = FastAddRotations(heading, RandomSignedFloatRange(0.0f, 1.3962636f));
        velocity[0] = FastSinOrCosA(angle) * 0.016666668f * speed;
        velocity[1] = FastSinOrCosB(angle) * 0.016666668f * speed;
        velocity[2] = 0.0f;
        speed = RandomFloatRange(0.0f, 12.0f) * F(state, 0x14);
        velocity[2] = speed * 0.016666668f;
        SpawnFadingDriftParticle(position, velocity, lifetime, 0x8FFF, phase, 127, 127, size * 210000.0f, F(state, 0x14) * 2100.0f, 0.00405555591f, 5);
    }
    for (smallIdx = 0; smallIdx < I(state, 0x28); smallIdx++) {
        float heading, angle, size, speed;
        int lifetime, phase;
        heading = FastMatrixHelperA(D_L00_001B8C80.target[0] - F(object, 0x10), D_L00_001B8C80.target[1] - F(object, 0x14));
        phase = FloatToInt(RandomSignedFloatRange(2.0f, 5.0f));
        lifetime = RandomIntRange(30, 50);
        position[0] = F(object, 0x10) + RandomSignedFloatRange(0.0f, 0.1f) * F(state, 0x14);
        position[1] = F(object, 0x14) + RandomSignedFloatRange(0.0f, 0.1f) * F(state, 0x14);
        position[2] = F(object, 0x18) + RandomSignedFloatRange(0.0f, 0.1f) * F(state, 0x14);
        size = RandomFloatRange(0.6f, 1.0f) * F(state, 0x14);
        speed = RandomFloatRange(9.0f, 12.0f) * F(state, 0x14);
        angle = FastAddRotations(heading, RandomSignedFloatRange(0.0f, 1.3962636f));
        velocity[0] = FastSinOrCosA(angle) * 0.016666668f * speed;
        velocity[1] = FastSinOrCosB(angle) * 0.016666668f * speed;
        velocity[2] = 0.0f;
        speed = RandomFloatRange(0.0f, 12.0f) * F(state, 0x14);
        velocity[2] = speed * 0.016666668f;
        SpawnFadingDriftParticle(position, velocity, lifetime, 0x3064FF, phase, 127, 127, size * 210000.0f, F(state, 0x14) * 2100.0f, 0.00405555591f, 3);
    }
    for (debrisIdx = 0; debrisIdx < I(state, 0x30); debrisIdx++) {
        float roll, turn;
        speed = RandomFloatRange(15.0f, 20.0f) * F(state, 0x14) * 0.016666668f;
        FastVecScale(position, object + 0xC0, speed);
        roll = RandomSignedFloatRange(0.261799425f, 1.3962636f);
        turn = RandomSignedFloatRange(0.261799425f, 1.3962636f);
        BuildAxisAngleQuaternion(rotation, object + 0xD0, roll);
        RotateVectorByQuaternion(velocity, position, rotation);
        BuildAxisAngleQuaternion(rotation, object + 0xC0, turn);
        RotateVectorByQuaternion(velocity, velocity, rotation);
        SpawnTrailParticle_002C6DD8(object + 0x10, velocity, RandomIntRange(20, 35), 0.00405555591f);
    }
    if (I(state, 0x34)) {
        *(Quad *)velocity = 0;
        velocity[2] = F(state, 0x14) * 0.13333334f;
        *(Quad *)position = *(Quad *)velocity;
        SpawnShockwaveRing(object, object + 0x10, position, 16, 255, 0, 0, 40, F(state, 0x14) * 3.5f);
    }
    SpawnExplosionEffects(object, D_L00_001A8F20, object + 0x10, 0.0f, 0.0f, 0, 0, 0, 0.0f, 0.0f, 9.0f, 0.0f, -1, 0, 0, -1, 0, 0x810001, F(state, 0x14) * 20.0f);
    sign = 1;
    angle = FastMatrixHelperA(D_L00_001B8C80.target[0] - F(object, 0x10), D_L00_001B8C80.target[1] - F(object, 0x14));
    for (smokeIdx = 0; smokeIdx < I(state, 0x2C); smokeIdx++) {
        float radius, roll, turn;
        position[0] = F(object, 0x10) + RandomSignedFloatRange(0.0f, 1.0f) * F(state, 0x14);
        sign = -sign;
        position[1] = F(object, 0x14) + RandomSignedFloatRange(0.0f, 1.0f) * F(state, 0x14);
        position[2] = F(object, 0x18) + RandomSignedFloatRange(0.0f, 1.0f) * F(state, 0x14);
        radius = RandomFloatRange(0.016666668f, 0.033333335f) * F(state, 0x14);
        roll = RandomSignedFloatRange(0.0f, 1.3962636f);
        turn = FastAddRotations(angle, RandomSignedFloatRange(0.0f, 1.5707965f));
        BuildSphericalOffset(velocity, radius, turn, roll);
        {
            u8 *effect = SpawnSpinningSparkParticle(position, 0.0f, 1.0f, sign, velocity, 0x7F60A0FF, 0, 1.01f, F(state, 0x14) * 315000.0f);
            if (effect) {
                u8 *extra = effect + 0x20;
                *(u16 *)(effect + 0xA) = RandomIntRange(40, 70);
                effect[9] = FloatToInt(4.0f) + 64;
                I(extra, 0x4) = 3;
                F(extra, 0x1C) = IntToFloat(RandomIntRange(1, 10));
                extra[0xA] = 64;
                extra[0xB] = effect[0xA];
            }
        }
    }
}
