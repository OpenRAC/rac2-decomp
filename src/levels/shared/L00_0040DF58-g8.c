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
extern u8 *part_spawn_gravity_fade(void *, void *, int, int, int, int, int, float, float, float, int);
extern float mat_fast_helper_a(float, float);
extern float math_random_signed_float_range(float, float);
extern int FloatToInt(float);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern u8 *part_spawn_fading_drift(void *, void *, int, int, int, int, int, float, float, float, int);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void part_spawn_shockwave_ring(void *, void *, void *, int, int, int, int, int, float);
extern void vec_build_spherical_offset(float *, float, float, float);
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
extern u8 *SpawnSpinningSparkParticle(void *, float, float, int, void *, int, int, float, float);
extern float IntToFloat(int);
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
void SpawnBurstEffects(BurstObject *object, void *up)
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
            effect = part_spawn_gravity_fade(velocity, D_L00_001A8F20, D_L00_001B1038, 0x388EF7, 0, 100, 0, inner,
                outer, 0.0f, 0);
            if (effect) effect[2] = D_L00_001FE940.fireColors[0];
            effect = part_spawn_gravity_fade(velocity, D_L00_001A8F20, D_L00_001B1038, 0xF7, 0, 100, 0, inner,
                outer, 0.0f, 0);
            if (effect) effect[2] = D_L00_001FE940.fireColors[0];
            for (i = 0; i < 2; i++) {
                effect = part_spawn_gravity_fade(velocity, D_L00_001A8F20, D_L00_001B1038, 0x388EF7, 0, 127, 0,
                    inner, outer, 0.0f, 0);
                if (effect) effect[2] = D_L00_001FE940.fireColors[5];
            }
            for (i = 0; i < 2; i++) {
                effect = part_spawn_gravity_fade(velocity, D_L00_001A8F20, D_L00_001B1038, 0x388EF7, 0, 127, 0,
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
            heading = mat_fast_helper_a(D_L00_001B8C80.target[0] - object->position[0],
                D_L00_001B8C80.target[1] - object->position[1]);
            phase = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
            lifetime = math_random_int_range(30, 50);
            position[0] = object->position[0] + math_random_signed_float_range(0.0f, 0.1f) * settings->scale;
            position[1] = object->position[1] + math_random_signed_float_range(0.0f, 0.1f) * settings->scale;
            position[2] = object->position[2] + math_random_signed_float_range(0.0f, 0.1f) * settings->scale;
            size = math_random_float_range(0.6f, 1.0f) * settings->scale;
            speed = math_random_float_range(9.0f, 12.0f) * settings->scale * 2.0f;
            angle = FastAddRotations(heading, math_random_signed_float_range(0.0f, 1.3962636f));
            velocity[0] = math_fast_sin_or_cos_a(angle) * 0.016666668f * speed;
            velocity[1] = math_fast_sin_or_cos_b(angle) * 0.016666668f * speed;
            velocity[2] = 0.0f;
            speed = math_random_float_range(3.0f, 12.0f) * settings->scale * 2.0f;
            velocity[2] = speed * 0.016666668f;
            part_spawn_fading_drift(position, velocity, lifetime, 0x148EF7, phase, 127, 127, size * 210000.0f,
                settings->scale * 2100.0f, 0.00405555591f, 1);
            phase *= 2;
            effect = part_spawn_fading_drift(position, velocity, lifetime, 0x1E1EF7, -phase, 48, 48, size * 1260000.0f,
                settings->scale * 4200.0f, 0.00405555591f, 0);
            if (effect) effect[2] = D_L00_001FE940.sparkColors[0];
        }
    }
    {
        int i;
        for (i = 0; i < settings->count24; i++) {
            float heading, angle, size, speed;
            int phase, lifetime;
            heading = mat_fast_helper_a(D_L00_001B8C80.target[0] - object->position[0],
                D_L00_001B8C80.target[1] - object->position[1]);
            phase = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
            lifetime = math_random_int_range(30, 50);
            position[0] = object->position[0] + math_random_signed_float_range(0.0f, 0.1f) * settings->scale;
            position[1] = object->position[1] + math_random_signed_float_range(0.0f, 0.1f) * settings->scale;
            position[2] = object->position[2] + math_random_signed_float_range(0.0f, 0.1f) * settings->scale;
            size = math_random_float_range(0.75f, 1.5f) * settings->scale;
            speed = math_random_float_range(9.0f, 12.0f) * settings->scale * 2.0f;
            angle = FastAddRotations(heading, math_random_signed_float_range(0.0f, 1.3962636f));
            velocity[0] = math_fast_sin_or_cos_a(angle) * 0.016666668f * speed;
            velocity[1] = math_fast_sin_or_cos_b(angle) * 0.016666668f * speed;
            velocity[2] = 0.0f;
            speed = math_random_float_range(3.0f, 12.0f) * settings->scale * 2.0f;
            velocity[2] = speed * 0.016666668f;
            part_spawn_fading_drift(position, velocity, lifetime, 0x328EF7, phase, 127, 127, size * 210000.0f,
                settings->scale * 2100.0f, 0.00405555591f, 5);
        }
    }
    {
        int i;
        for (i = 0; i < settings->count28; i++) {
            float heading, angle, size, speed;
            int phase, lifetime;
            heading = mat_fast_helper_a(D_L00_001B8C80.target[0] - object->position[0],
                D_L00_001B8C80.target[1] - object->position[1]);
            phase = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
            lifetime = math_random_int_range(30, 50);
            position[0] = object->position[0] + math_random_signed_float_range(0.0f, 0.1f) * settings->scale;
            position[1] = object->position[1] + math_random_signed_float_range(0.0f, 0.1f) * settings->scale;
            position[2] = object->position[2] + math_random_signed_float_range(0.0f, 0.1f) * settings->scale;
            size = math_random_float_range(0.6f, 1.0f) * settings->scale;
            speed = math_random_float_range(9.0f, 12.0f) * settings->scale;
            angle = FastAddRotations(heading, math_random_signed_float_range(0.0f, 1.3962636f));
            velocity[0] = math_fast_sin_or_cos_a(angle) * 0.016666668f * speed;
            velocity[1] = math_fast_sin_or_cos_b(angle) * 0.016666668f * speed;
            velocity[2] = 0.0f;
            speed = math_random_float_range(0.0f, 12.0f) * settings->scale;
            velocity[2] = speed * 0.016666668f;
            part_spawn_fading_drift(position, velocity, lifetime, 0x1EF7, phase, 127, 127, size * 210000.0f,
                settings->scale * 2100.0f, 0.00405555591f, 3);
        }
    }
    if (settings->enabled34) {
        *(Quad *)velocity = 0;
        velocity[2] = settings->scale * 0.13333334f;
        *(Quad *)position = *(Quad *)velocity;
        part_spawn_shockwave_ring(object, object->position, position, 16, 0, 0, 255, 40, settings->scale * 3.5f);
    }
    {
        int sign = 1, i;
        float angle;
        angle = mat_fast_helper_a(D_L00_001B8C80.target[0] - object->position[0],
            D_L00_001B8C80.target[1] - object->position[1]);
        for (i = 0; i < settings->count2C; i++) {
            float radius, roll, turn;
            u8 *effect;
            position[0] = object->position[0] + math_random_signed_float_range(0.0f, 1.0f) * settings->scale;
            sign = -sign;
            position[1] = object->position[1] + math_random_signed_float_range(0.0f, 1.0f) * settings->scale;
            position[2] = object->position[2] + math_random_signed_float_range(0.0f, 1.0f) * settings->scale;
            radius = math_random_float_range(0.016666668f, 0.033333335f) * settings->scale;
            roll = math_random_signed_float_range(0.0f, 1.3962636f);
            turn = FastAddRotations(angle, math_random_signed_float_range(0.0f, 1.5707965f));
            vec_build_spherical_offset(velocity, radius, turn, roll);
            effect = SpawnSpinningSparkParticle(position, 0.0f, 1.0f, sign, velocity, 0x323232, 0, 1.01f,
                settings->scale * 315000.0f);
            if (effect) {
                BurstParticle *particle = (BurstParticle *)effect;
                BurstPayload *payload = &particle->payload;
                effect[3] = 0x44;
                particle->lifetime = math_random_int_range(40, 70);
                particle->rate = FloatToInt(4.0f) + 64;
                payload->size = IntToFloat(math_random_int_range(1, 10));
                payload->kind = 3;
                payload->alpha = 127;
                payload->fade = particle->lifetime;
            }
        }
    }
}
