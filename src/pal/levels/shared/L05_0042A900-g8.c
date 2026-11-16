#include "common.h"

/* func_PAL_L05_0042A900, the PAL copy of func_L05_00425058: the same C, where emitter
 * counts and lifetimes take the 50 Hz scale, per-frame rates become 6/5 (0.00405556 becomes
 * 0.00584, 1/60 becomes 0.02), 16 becomes 13, and the two-pass loops count up. */

typedef int Quad __attribute__((mode(TI)));
extern float g_large_explosion_inner_scale __attribute__((sda)), g_large_explosion_outer_scale __attribute__((sda));
extern int g_large_explosion_fade_param __attribute__((sda));
/* Keep the full vector size: sda selects symbolic address formation in cc1,
 * while the assembler keeps this 16 - byte object absolute under -G8. */
extern float g_effect_direction_vec[4] __attribute__((sda));
typedef struct Cam_00435CE8 Cam_00435CE8;
typedef struct CamMgr_00435CE8 {
    u8 pad000[0x140];
    f32 f140[4];
    u8 pad150[0x40];
    Cam_00435CE8 *cam;
} CamMgr_00435CE8;
extern CamMgr_00435CE8 g_hero_l05_state;
extern u8 *g_particle_params_table[] NOT_SDA;
/* Integer and FP arguments retain their respective EE ABI bank order. */
extern u8 *part_spawn_gravity_fade(void *, void *, int, int, int, int, int, float, float, float, int);
extern float mat_fast_helper_a(float, float);
extern float math_random_signed_float_range(float, float);
extern int FloatToInt(float);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern void part_spawn_random_direction_effect(void *, float, float);
extern float FastAddRotations(float, float);
extern u8 *part_spawn_fading_drift(void *, void *, int, int, int, int, int, float, float, float, int);
extern void FastVecScale(void *, void *, float);
extern void math_build_axis_angle_quat(void *, int, float);
extern void vec_rotate_by_quaternion(void *, void *, void *);
extern u8 *part_spawn_trail_2(void *, void *, int, float);
extern char *part_spawn_shockwave_ring(void *, void *, void *, int, int, int, int, int, float);
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
void func_PAL_L05_0042A900(BurstObject *object)
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
        inner = g_large_explosion_inner_scale * state->scale * 210000.0f;
        outer = g_large_explosion_outer_scale * state->scale * 210000.0f;
        effect = part_spawn_gravity_fade(object->position, g_effect_direction_vec, (g_large_explosion_fade_param * 5 + 2) / 6, 0x388EF7,
            0, 100, 0, inner, outer, 0.0f, 0);
        if (effect) effect[2] = g_particle_params_table[92][0];
        effect = part_spawn_gravity_fade(object->position, g_effect_direction_vec, (g_large_explosion_fade_param * 5 + 2) / 6, 0x63F7,
            0, 100, 0, inner, outer, 0.0f, 0);
        if (effect) effect[2] = g_particle_params_table[92][0];
        for (i = 0; i < 2; i++) {
            effect = part_spawn_gravity_fade(object->position, g_effect_direction_vec, (g_large_explosion_fade_param * 5 + 2) / 6,
                0x388EF7, 0, 127, 0, inner, outer, 0.0f, 0);
            if (effect) effect[2] = g_particle_params_table[92][5];
        }
        for (i = 0; i < 2; i++) {
            effect = part_spawn_gravity_fade(object->position, g_effect_direction_vec, (g_large_explosion_fade_param * 5 + 2) / 6,
                0x388EF7, 0, 127, 0, inner, outer, 0.0f, 0);
            if (effect) effect[2] = g_particle_params_table[92][6];
        }
    }
    {
        int i;
        for (i = 0; i < state->count20; i++) {
            /* Heading and perturbed angle have separate lifetimes. Speed is reused
             * for the later vertical component. */
            float size;
            int phase, lifetime;
            u8 *effect;
            phase = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
            lifetime = math_random_int_range(30, 50);
            position[0] = object->position[0] + math_random_signed_float_range(0.0f, 0.1f) * state->scale;
            position[1] = object->position[1] + math_random_signed_float_range(0.0f, 0.1f) * state->scale;
            position[2] = object->position[2] + math_random_signed_float_range(0.0f, 0.1f) * state->scale;
            size = math_random_float_range(0.6f, 1.0f) * state->scale;
            part_spawn_random_direction_effect(velocity, 0.5f, 0.8f);
            part_spawn_fading_drift(position, velocity, (lifetime * 5 + 2) / 6, 0x407FFF, phase, 127, 127,
                size * 210000.0f, state->scale * 2100.0f, 0.00584f, 1);
            phase *= 2;
            effect = part_spawn_fading_drift(position, velocity, (lifetime * 5 + 2) / 6, 0x20FF, -phase, 48, 48,
                size * 1260000.0f, state->scale * 4200.0f, 0.00584f, 0);
            if (effect) effect[2] = g_particle_params_table[53][0];
        }
    }
    {
        int i;
        for (i = 0; i < state->count24; i++) {
            float size;
            int phase, lifetime;
            phase = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
            lifetime = math_random_int_range(30, 50);
            position[0] = object->position[0] + math_random_signed_float_range(0.0f, 0.1f) * state->scale;
            position[1] = object->position[1] + math_random_signed_float_range(0.0f, 0.1f) * state->scale;
            position[2] = object->position[2] + math_random_signed_float_range(0.0f, 0.1f) * state->scale;
            size = math_random_float_range(0.75f, 1.5f) * state->scale;
            part_spawn_random_direction_effect(velocity, 0.5f, 0.8f);
            part_spawn_fading_drift(position, velocity, (lifetime * 5 + 2) / 6, 0x8FFF, phase, 127, 127,
                size * 210000.0f, state->scale * 2100.0f, 0.00584f, 5);
        }
    }
    {
        int i;
        for (i = 0; i < state->count28; i++) {
            float size;
            int phase, lifetime;
            phase = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
            lifetime = math_random_int_range(30, 50);
            position[0] = object->position[0] + math_random_signed_float_range(0.0f, 0.1f) * state->scale;
            position[1] = object->position[1] + math_random_signed_float_range(0.0f, 0.1f) * state->scale;
            position[2] = object->position[2] + math_random_signed_float_range(0.0f, 0.1f) * state->scale;
            size = math_random_float_range(0.6f, 1.0f) * state->scale;
            part_spawn_random_direction_effect(velocity, 0.5f, 0.8f);
            part_spawn_fading_drift(position, velocity, (lifetime * 5 + 2) / 6, 0x3064FF, phase, 127, 127,
                size * 210000.0f, state->scale * 2100.0f, 0.00584f, 3);
        }
    }
    {
        int i;
        for (i = 0; i < state->count30; i++) {
            float speed, roll, turn;
            int lifetime;
            speed = math_random_float_range(15.0f, 20.0f) * state->scale * 0.020000001f;
            FastVecScale(position, object->forward, speed);
            roll = math_random_signed_float_range(0.26179942f, 1.3962636f);
            turn = math_random_signed_float_range(0.26179942f, 1.3962636f);
            math_build_axis_angle_quat(rotation, (int)(object->right), roll);
            vec_rotate_by_quaternion(velocity, position, rotation);
            math_build_axis_angle_quat(rotation, (int)(object->forward), turn);
            vec_rotate_by_quaternion(velocity, velocity, rotation);
            lifetime = math_random_int_range(20, 35);
            part_spawn_trail_2(object->position, velocity, (lifetime * 5 + 2) / 6, 0.00584f);
        }
    }
    if (state->enabled34) {
        *(Quad *)velocity = 0;
        velocity[2] = state->scale * 0.16000001f;
        *(Quad *)position = *(Quad *)velocity;
        part_spawn_shockwave_ring(object, object->position, position, 13, 255, 0, 0, 40, state->scale * 3.5f);
    }
    SpawnExplosionEffects(object, g_effect_direction_vec, object->position, 0.0f, 0.0f, 0, 0, 0, 0.0f, 0.0f, 9.0f, 0.0f, -1,
        state->scale * 20.0f, 0, 0, -1, 0, 0x810001);
    {
        int sign = 1, i;
        float angle;
        angle = mat_fast_helper_a(g_hero_l05_state.f140[0] - object->position[0],
            g_hero_l05_state.f140[1] - object->position[1]);
        for (i = 0; i < state->count2C; i++) {
            float radius, roll, turn;
            u8 *effect;
            position[0] = object->position[0] + math_random_signed_float_range(0.0f, 1.0f) * state->scale;
            sign = -sign;
            position[1] = object->position[1] + math_random_signed_float_range(0.0f, 1.0f) * state->scale;
            position[2] = object->position[2] + math_random_signed_float_range(0.0f, 1.0f) * state->scale;
            radius = math_random_float_range(0.020000001f, 0.040000003f) * state->scale;
            roll = math_random_signed_float_range(0.0f, 1.3962636f);
            turn = FastAddRotations(angle, math_random_signed_float_range(0.0f, 1.5707965f));
            vec_build_spherical_offset(velocity, radius, turn, roll);
            effect = SpawnSpinningSparkParticle(position, 0.0f, 1.0f, sign, velocity, 0x7F60A0FF, 1.01f,
                state->scale * 315000.0f, 0);
            if (effect) {
                BurstParticle *particle = (BurstParticle *)effect;
                BurstPayload *payload = &particle->payload;
                particle->lifetime = (math_random_int_range(40, 70) * 5 + 2) / 6;
                particle->rate = FloatToInt(4.0f) + 64;
                payload->kind = 3;
                payload->size = IntToFloat((math_random_int_range(1, 10) * 5 + 2) / 6);
                payload->alpha = 64;
                payload->fade = particle->lifetime;
            }
        }
    }
}
