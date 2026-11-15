#include "common.h"

typedef int Quad __attribute__((mode(TI)));
extern float D_L05_001B1584 __attribute__((sda)), D_L05_001B1588 __attribute__((sda));
extern int D_L05_001B158C __attribute__((sda));
/* Keep the full vector size: sda selects symbolic address formation in cc1,
 * while the assembler keeps this 16 - byte object absolute under -G8. */
extern float D_L05_001A8F20[4] __attribute__((sda));
typedef struct BurstCamera BurstCamera;
typedef struct BurstCameraManager {
    u8 pad000[0x140];
    f32 f140[4];
    u8 pad150[0x40];
    BurstCamera *cam;
} BurstCameraManager;
extern BurstCameraManager D_L05_001B9580;
extern u8 *D_L05_001FF240[] NOT_SDA;
/* Integer and FP arguments retain their respective EE ABI bank order. */
extern u8 *part_spawn_gravity_fade(void *, void *, int, int, int, int, int, float, float, float, int);
extern float mat_fast_helper_a(float, float);
extern float math_random_signed_float_range(float, float);
extern int FloatToInt(float);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern float FastAddRotations(float, float);
extern void part_spawn_random_direction_effect(void *, float, float);
extern u8 *part_spawn_fading_drift(void *, void *, int, int, int, int, int, float, float, float, int);
extern void FastVecScale(void *, void *, float);
extern void math_build_axis_angle_quat(void *, int, float);
extern void vec_rotate_by_quaternion(void *, void *, void *);
extern u8 *part_spawn_trail_2(void *, void *, int, float);
extern void part_spawn_shockwave_ring(void *, void *, void *, int, int, int, int, int, float);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
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
extern u8 *SpawnSpinningSparkParticle(void *, float, float, int, void *, int, float, float, int);
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
/* Makes an explosion with fire flares, smoke and sparks, a slightly different look from the one at 00425058. */
void part_spawn_fire_explosion(BurstObject *object)
{
    float position[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float rotation[4];
    BurstSettings *state = object->settings;

    /* The initial emitters share one result variable; later groups own theirs. */
    {
        float inner, outer;
        int i;
        u8 *effect;
        inner = D_L05_001B1584 * state->scale * 210000.0f;
        outer = D_L05_001B1588 * state->scale * 210000.0f;
        effect = part_spawn_gravity_fade(object->position, D_L05_001A8F20, D_L05_001B158C, 0xF78E38, 0, 100, 0, inner,
            outer, 0.0f, 0);
        if (effect) effect[2] = D_L05_001FF240[92][0];
        effect = part_spawn_gravity_fade(object->position, D_L05_001A8F20, D_L05_001B158C, 0xF76300, 0, 100, 0, inner,
            outer, 0.0f, 0);
        if (effect) effect[2] = D_L05_001FF240[92][0];
        for (i = 1; i >= 0; i--) {
            effect = part_spawn_gravity_fade(object->position, D_L05_001A8F20, D_L05_001B158C, 0xF78E38, 0, 127, 0,
                inner, outer, 0.0f, 0);
            if (effect) effect[2] = D_L05_001FF240[92][5];
        }
        for (i = 1; i >= 0; i--) {
            effect = part_spawn_gravity_fade(object->position, D_L05_001A8F20, D_L05_001B158C, 0xF78E38, 0, 127, 0,
                inner, outer, 0.0f, 0);
            if (effect) effect[2] = D_L05_001FF240[92][6];
        }
    }
    {
        int i;
        for (i = 0; i < state->count20; i++) {
            float size;
            int phase, lifetime;
            u8 *effect;
            phase = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
            lifetime = math_random_int_range(40, 50);
            position[0] = object->position[0] + math_random_signed_float_range(0.0f, 0.1f) * state->scale;
            position[1] = object->position[1] + math_random_signed_float_range(0.0f, 0.1f) * state->scale;
            position[2] = object->position[2] + math_random_signed_float_range(0.0f, 0.1f) * state->scale;
            size = math_random_float_range(0.6f, 1.0f) * state->scale;
            part_spawn_random_direction_effect(velocity, 0.3f, 0.6f);
            part_spawn_fading_drift(position, velocity, lifetime, 0x407FFF, phase, 127, 127, size * 210000.0f,
                state->scale * 2100.0f, 0.00405555591f, 1);
            phase *= 2;
            effect = part_spawn_fading_drift(position, velocity, lifetime, 0xFF2000, -phase, 48, 48, size * 1260000.0f,
                state->scale * 4200.0f, 0.00405555591f, 0);
            if (effect) effect[2] = D_L05_001FF240[53][0];
        }
    }
    {
        int i;
        for (i = 0; i < state->count24; i++) {
            float size;
            int phase, lifetime;
            phase = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
            lifetime = math_random_int_range(40, 50);
            position[0] = object->position[0] + math_random_signed_float_range(0.0f, 0.1f) * state->scale;
            position[1] = object->position[1] + math_random_signed_float_range(0.0f, 0.1f) * state->scale;
            position[2] = object->position[2] + math_random_signed_float_range(0.0f, 0.1f) * state->scale;
            size = math_random_float_range(0.75f, 1.5f) * state->scale;
            part_spawn_random_direction_effect(velocity, 0.3f, 0.6f);
            part_spawn_fading_drift(position, velocity, lifetime, 0xFF8F00, phase, 127, 127, size * 210000.0f,
                state->scale * 2100.0f, 0.00405555591f, 5);
        }
    }
    {
        int i;
        for (i = 0; i < state->count28; i++) {
            float size;
            int phase, lifetime;
            phase = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
            lifetime = math_random_int_range(40, 50);
            position[0] = object->position[0] + math_random_signed_float_range(0.0f, 0.1f) * state->scale;
            position[1] = object->position[1] + math_random_signed_float_range(0.0f, 0.1f) * state->scale;
            position[2] = object->position[2] + math_random_signed_float_range(0.0f, 0.1f) * state->scale;
            size = math_random_float_range(0.6f, 1.0f) * state->scale;
            part_spawn_random_direction_effect(velocity, 0.3f, 0.6f);
            part_spawn_fading_drift(position, velocity, lifetime, 0xFF6430, phase, 127, 127, size * 210000.0f,
                state->scale * 2100.0f, 0.00405555591f, 3);
        }
    }
    {
        int i;
        for (i = 0; i < state->count30; i++) {
            float speed, roll, turn;
            int lifetime;
            speed = math_random_float_range(15.0f, 20.0f) * state->scale * 0.016666668f;
            FastVecScale(position, object->forward, speed);
            roll = math_random_signed_float_range(0.26179942f, 1.3962636f);
            turn = math_random_signed_float_range(0.26179942f, 1.3962636f);
            math_build_axis_angle_quat(rotation, (int)(object->right), roll);
            vec_rotate_by_quaternion(velocity, position, rotation);
            math_build_axis_angle_quat(rotation, (int)(object->forward), turn);
            vec_rotate_by_quaternion(velocity, velocity, rotation);
            lifetime = math_random_int_range(20, 35);
            part_spawn_trail_2(object->position, velocity, lifetime, 0.00405555591f);
        }
    }
    if (state->enabled34) {
        *(Quad *)velocity = 0;
        velocity[2] = state->scale * 0.05000000447f;
        *(Quad *)position = *(Quad *)velocity;
        part_spawn_shockwave_ring(object, object->position, position, 16, 255, 0, 0, 40, state->scale * 3.0f);
    }
    SpawnExplosionEffects(object, D_L05_001A8F20, object->position, 0.0f, 0.0f, 0, 0, 0, 0.0f, 0.0f, 9.0f, 0.0f, -1,
        state->scale * 20.0f, 0, 0, -1, 0, 0x810001);
    {
        int sign = 1, i;
        float angle;
        angle = mat_fast_helper_a(D_L05_001B9580.f140[0] - object->position[0],
            D_L05_001B9580.f140[1] - object->position[1]);
        for (i = 0; i < state->count2C; i++) {
            float radius, roll, turn;
            u8 *effect;
            position[0] = object->position[0] + math_random_signed_float_range(0.0f, 1.0f) * state->scale;
            sign = -sign;
            position[1] = object->position[1] + math_random_signed_float_range(0.0f, 1.0f) * state->scale;
            position[2] = object->position[2] + math_random_signed_float_range(0.0f, 1.0f) * state->scale;
            radius = math_random_float_range(0.016666668f, 0.033333335f) * state->scale;
            roll = math_random_signed_float_range(0.0f, 1.3962636f);
            turn = FastAddRotations(angle, math_random_signed_float_range(0.0f, 1.5707965f));
            vec_build_spherical_offset(velocity, radius, turn, roll);
            effect = SpawnSpinningSparkParticle(position, 0.0f, 1.0f, sign, velocity, 0x7F60A0FF, 1.01f,
                state->scale * 315000.0f, 0);
            if (effect) {
                BurstParticle *particle = (BurstParticle *)effect;
                BurstPayload *payload = &particle->payload;
                particle->lifetime = math_random_int_range(40, 70);
                particle->rate = FloatToInt(4.0f) + 64;
                payload->kind = 3;
                payload->size = IntToFloat(math_random_int_range(1, 10));
                payload->alpha = 64;
                payload->fade = particle->lifetime;
            }
        }
    }
}
