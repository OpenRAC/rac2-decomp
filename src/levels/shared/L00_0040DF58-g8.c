/* func_L00_0040DF58: offset explosion burst (family F6, see func_L16_00406550). One flash group half
 * a forward vector ahead of the object, then the configured particle groups. The two fire loops count
 * up in the source: the loop pass reverses them after hoisting the colour table address, which is what
 * orders the first loop's preheader. The emitters take their float parameters interleaved with the ints.
 */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
extern float D_L00_001B1030 __attribute__((sda)), D_L00_001B1034 __attribute__((sda));
extern int D_L00_001B1038 __attribute__((sda));
extern float D_L00_001A8F20[4] MACRO_ADDR;
typedef struct { u8 pad[0x140]; float target[4]; } CameraView;
typedef struct { u8 pad[0xD4]; u8 *sparkColors; u8 pad2[0x98]; u8 *fireColors; } EffectTables;
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
extern u8 *func_002C7970(void *, void *, int, int, int, int, int, float, float, float, int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00308408(void *, void *, void *, int, int, int, int, int, float);
extern void func_002AF000(float *, float, float, float);
typedef struct BurstPayload {
    u8 pad00[4];
    int kind;
    u8 pad08[2];
    u8 alpha, fade;
    u8 pad0C[0x10];
    float size;
} BurstPayload;
typedef struct BurstParticle {
    u8 pad00[9];
    u8 rate;
    u16 lifetime;
    u8 pad0C[0x14];
    BurstPayload payload;
} BurstParticle;
extern u8 *func_002BDCE8(void *, float, float, int, void *, int, int, float, float);
extern float func_00283CE0(int);
typedef struct BurstSettings {
    u8 pad00[0x14];
    float scale;
    u8 pad18[8];
    int count20, count24, count28, count2C, count30, enabled34;
} BurstSettings;
typedef struct BurstObject {
    u8 pad00[0x10];
    float position[4];
    u8 pad20[0x48];
    BurstSettings *settings;
    u8 pad6C[0x54];
    float forward[4], right[4];
} BurstObject;
/* Makes an explosion burst at the object: a fireball, flying sparks, smoke puffs and a shock ring, all scaled by the object's settings. */
void func_L00_0040DF58(BurstObject *object, void *up)
{
    float position[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    BurstSettings *settings = object->settings;

    {
        float inner, outer;
        int i, j;
        u8 *effect;
        for (j = 0; j < 1; j++) {
            FastVecScale(position, object->forward, 0.5f);
            qcopy(velocity, object->position);
            FastVecAdd(velocity, velocity, position);
            inner = D_L00_001B1030 * settings->scale * 210000.0f;
            outer = D_L00_001B1034 * settings->scale * 210000.0f;
            effect = SpawnGravityFadeParticle(velocity, D_L00_001A8F20, D_L00_001B1038, 0x388EF7, 0, 100, 0, inner,
                outer, 0.0f, 0);
            if (effect) effect[2] = D_L00_001FE940.fireColors[0];
            effect = SpawnGravityFadeParticle(velocity, D_L00_001A8F20, D_L00_001B1038, 0xF7, 0, 100, 0, inner,
                outer, 0.0f, 0);
            if (effect) effect[2] = D_L00_001FE940.fireColors[0];
            for (i = 0; i < 2; i++) {
                effect = SpawnGravityFadeParticle(velocity, D_L00_001A8F20, D_L00_001B1038, 0x388EF7, 0, 127, 0,
                    inner, outer, 0.0f, 0);
                if (effect) effect[2] = D_L00_001FE940.fireColors[5];
            }
            for (i = 0; i < 2; i++) {
                effect = SpawnGravityFadeParticle(velocity, D_L00_001A8F20, D_L00_001B1038, 0x388EF7, 0, 127, 0,
                    inner, outer, 0.0f, 0);
                if (effect) effect[2] = D_L00_001FE940.fireColors[6];
            }
        }
    }
    {
        int i;
        for (i = 0; i < settings->count20; i++) {
            float heading, angle, size, speed;
            int phase, lifetime;
            u8 *effect;
            heading = FastMatrixHelperA(D_L00_001B8C80.target[0] - object->position[0],
                D_L00_001B8C80.target[1] - object->position[1]);
            phase = FloatToInt(RandomSignedFloatRange(2.0f, 5.0f));
            lifetime = RandomIntRange(30, 50);
            position[0] = object->position[0] + RandomSignedFloatRange(0.0f, 0.1f) * settings->scale;
            position[1] = object->position[1] + RandomSignedFloatRange(0.0f, 0.1f) * settings->scale;
            position[2] = object->position[2] + RandomSignedFloatRange(0.0f, 0.1f) * settings->scale;
            size = RandomFloatRange(0.6f, 1.0f) * settings->scale;
            speed = RandomFloatRange(9.0f, 12.0f) * settings->scale * 2.0f;
            angle = FastAddRotations(heading, RandomSignedFloatRange(0.0f, 1.3962636f));
            velocity[0] = FastSinOrCosA(angle) * 0.016666668f * speed;
            velocity[1] = FastSinOrCosB(angle) * 0.016666668f * speed;
            velocity[2] = 0.0f;
            speed = RandomFloatRange(3.0f, 12.0f) * settings->scale * 2.0f;
            velocity[2] = speed * 0.016666668f;
            SpawnFadingDriftParticle(position, velocity, lifetime, 0x148EF7, phase, 127, 127, size * 210000.0f,
                settings->scale * 2100.0f, 0.00405555591f, 1);
            phase *= 2;
            effect = SpawnFadingDriftParticle(position, velocity, lifetime, 0x1E1EF7, -phase, 48, 48, size * 1260000.0f,
                settings->scale * 4200.0f, 0.00405555591f, 0);
            if (effect) effect[2] = D_L00_001FE940.sparkColors[0];
        }
    }
    {
        int i;
        for (i = 0; i < settings->count24; i++) {
            float heading, angle, size, speed;
            int phase, lifetime;
            heading = FastMatrixHelperA(D_L00_001B8C80.target[0] - object->position[0],
                D_L00_001B8C80.target[1] - object->position[1]);
            phase = FloatToInt(RandomSignedFloatRange(2.0f, 5.0f));
            lifetime = RandomIntRange(30, 50);
            position[0] = object->position[0] + RandomSignedFloatRange(0.0f, 0.1f) * settings->scale;
            position[1] = object->position[1] + RandomSignedFloatRange(0.0f, 0.1f) * settings->scale;
            position[2] = object->position[2] + RandomSignedFloatRange(0.0f, 0.1f) * settings->scale;
            size = RandomFloatRange(0.75f, 1.5f) * settings->scale;
            speed = RandomFloatRange(9.0f, 12.0f) * settings->scale * 2.0f;
            angle = FastAddRotations(heading, RandomSignedFloatRange(0.0f, 1.3962636f));
            velocity[0] = FastSinOrCosA(angle) * 0.016666668f * speed;
            velocity[1] = FastSinOrCosB(angle) * 0.016666668f * speed;
            velocity[2] = 0.0f;
            speed = RandomFloatRange(3.0f, 12.0f) * settings->scale * 2.0f;
            velocity[2] = speed * 0.016666668f;
            SpawnFadingDriftParticle(position, velocity, lifetime, 0x328EF7, phase, 127, 127, size * 210000.0f,
                settings->scale * 2100.0f, 0.00405555591f, 5);
        }
    }
    {
        int i;
        for (i = 0; i < settings->count28; i++) {
            float heading, angle, size, speed;
            int phase, lifetime;
            heading = FastMatrixHelperA(D_L00_001B8C80.target[0] - object->position[0],
                D_L00_001B8C80.target[1] - object->position[1]);
            phase = FloatToInt(RandomSignedFloatRange(2.0f, 5.0f));
            lifetime = RandomIntRange(30, 50);
            position[0] = object->position[0] + RandomSignedFloatRange(0.0f, 0.1f) * settings->scale;
            position[1] = object->position[1] + RandomSignedFloatRange(0.0f, 0.1f) * settings->scale;
            position[2] = object->position[2] + RandomSignedFloatRange(0.0f, 0.1f) * settings->scale;
            size = RandomFloatRange(0.6f, 1.0f) * settings->scale;
            speed = RandomFloatRange(9.0f, 12.0f) * settings->scale;
            angle = FastAddRotations(heading, RandomSignedFloatRange(0.0f, 1.3962636f));
            velocity[0] = FastSinOrCosA(angle) * 0.016666668f * speed;
            velocity[1] = FastSinOrCosB(angle) * 0.016666668f * speed;
            velocity[2] = 0.0f;
            speed = RandomFloatRange(0.0f, 12.0f) * settings->scale;
            velocity[2] = speed * 0.016666668f;
            SpawnFadingDriftParticle(position, velocity, lifetime, 0x1EF7, phase, 127, 127, size * 210000.0f,
                settings->scale * 2100.0f, 0.00405555591f, 3);
        }
    }
    if (settings->enabled34) {
        *(Quad *)velocity = 0;
        velocity[2] = settings->scale * 0.13333334f;
        *(Quad *)position = *(Quad *)velocity;
        SpawnShockwaveRing(object, object->position, position, 16, 0, 0, 255, 40, settings->scale * 3.5f);
    }
    {
        int sign = 1, i;
        float angle;
        angle = FastMatrixHelperA(D_L00_001B8C80.target[0] - object->position[0],
            D_L00_001B8C80.target[1] - object->position[1]);
        for (i = 0; i < settings->count2C; i++) {
            float radius, roll, turn;
            u8 *effect;
            position[0] = object->position[0] + RandomSignedFloatRange(0.0f, 1.0f) * settings->scale;
            sign = -sign;
            position[1] = object->position[1] + RandomSignedFloatRange(0.0f, 1.0f) * settings->scale;
            position[2] = object->position[2] + RandomSignedFloatRange(0.0f, 1.0f) * settings->scale;
            radius = RandomFloatRange(0.016666668f, 0.033333335f) * settings->scale;
            roll = RandomSignedFloatRange(0.0f, 1.3962636f);
            turn = FastAddRotations(angle, RandomSignedFloatRange(0.0f, 1.5707965f));
            BuildSphericalOffset(velocity, radius, turn, roll);
            effect = SpawnSpinningSparkParticle(position, 0.0f, 1.0f, sign, velocity, 0x323232, 0, 1.01f,
                settings->scale * 315000.0f);
            if (effect) {
                BurstParticle *particle = (BurstParticle *)effect;
                BurstPayload *payload = &particle->payload;
                effect[3] = 0x44;
                particle->lifetime = RandomIntRange(40, 70);
                particle->rate = FloatToInt(4.0f) + 64;
                payload->size = IntToFloat(RandomIntRange(1, 10));
                payload->kind = 3;
                payload->alpha = 127;
                payload->fade = particle->lifetime;
            }
        }
    }
}
