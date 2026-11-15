#include "include_asm.h"
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern int math_random_int_range(int, int);
extern int gfx_swap_packed_color_channels(unsigned int, int);
extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern int FloatToInt(float);
extern int math_random_int_below(int);
extern char *part_spawn_firework_spark(void *, void *, int, int, float, int, int, float, int, int);
extern char *part_spawn_shockwave_ring(void *, void *, void *, float, int, int, int, int, int);
extern int PlayMobySound(int, int, void *);
extern char *moby_spawn_template_effect(void *, void *, int, int);

typedef struct { int colors[6]; } __attribute__((packed)) BurstColors;
typedef struct {
    float origin[4];
    void *owner;
    int flags;
    unsigned char kind, enabled;
    unsigned short uid;
    float damage;
    int reserved;
} ExplosionDamage;
typedef struct { float vector[4], random[4]; } ExplosionVectors;
extern BurstColors D_001A9F20, D_001A9F38;
extern float D_001B168C[] __attribute__((sda)), D_001B1690[] __attribute__((sda));
extern char g_camera_eye_state[];
typedef struct {
    char unknown[0x160];
    float shake;
    int unknown164;
    int timer;
    int phase;
} ExplosionCamera;
extern ExplosionCamera g_active_camera;
typedef struct { char unknown[32]; float scale[3]; } BlastEffect;
extern BlastEffect D_00258C80, D_00258CD0;
extern void part_init_effect_record(void *, void *, int, float);
extern int coll_process_hit(float, void *, int, void *, void *);
extern void *part_spawn_spark(void *, void *, int, int, float, int, int, int, int, int);
extern void *part_spawn_spinning_debris(void *, void *, int, int, int);
extern void FastVecAdd(void *, void *, void *);
extern void vec_fast_divide_helper(void *, void *, float);
extern void part_spawn_color_blend(void *, void *, int, int, int, float);
extern int math_fast_helper_a(void *, float);
extern float IntToFloat(int);
extern void vec_build_spherical_offset(void *, float, float, float);

/* Creates an explosion at a position with sparks, flashes, smoke, debris, damage, camera shake and sound. */
void SpawnExplosionEffects(char *owner, void *direction, float *position,
    float radius, float damage, int sparks, int flashes, int smoke,
    float glow, float white, float cutoff, float scale, int sound, float blast,
    int shake, int debris, int quality, unsigned char channels, int flags)
{
    float drift[4];
    float delta[4];
    float distance;
    float load = D_001B1690[0] + D_001B168C[0];
    *(Quad *)drift = 0;
    drift[2] = scale * 0.13333334028720856f;
    if (quality == -1 && load > 1.7000000476837158f) quality = 1;
    if (!position) {
        if (!owner) return;
        position = (float *)(owner + 0x10);
    }
    if (radius > 0.0f) {
        {
            ExplosionDamage message;
            part_init_effect_record(&message, owner, flags, damage);
            message.kind = 2;
            message.enabled = 1;
            message.uid = *(unsigned short *)(owner + 0xAA);
            coll_process_hit(radius, position, 16, owner, &message);
        }
    }
    {
        int i;
        for (i = 0; i < sparks; i++) {
            {
                float vector[4];
                float angle, azimuth, speed;
                int c1, c2, life;
                angle = math_random_float_range(0.2617994248867035f, 1.396263599395752f);
                azimuth = math_random_angle();
                speed = math_random_float_range(7.0f, 10.5f);
                vec_build_spherical_offset(vector, scale * 0.01666666753590107f * speed, azimuth, angle);
                vector[2] += 0.05000000447034836f;
                c1 = gfx_swap_packed_color_channels(0x4F007FFF, channels);
                c2 = gfx_swap_packed_color_channels(0x1F00007F, channels);
                life = math_random_int_range(60, 120);
                part_spawn_spark(position, vector, c1, c2, scale * 40000.0f, life - quality * 10, 1, -1, -1, 0);
            }
        }
    }
    FastVecSub(delta, g_camera_eye_state, position);
    distance = FastVecLength(delta);
    if (debris) {
        {
            ExplosionVectors v;
            int i;
            *(Quad *)v.random = 0;
            v.random[0] = math_random_float_range(-1.0f, 1.0f);
            v.random[1] = math_random_float_range(-1.0f, 1.0f);
            v.random[2] = math_random_float_range(-1.0f, 1.0f);
            *(Quad *)v.vector = *(Quad *)v.random;
            if (distance < 14.0f) {
                delta[2] += distance * 0.5f;
                vec_scale_to_length(v.vector, v.vector, distance * 0.0033333336468786f);
                vec_scale_to_length(delta, delta, (distance + distance) * 0.01666666753590107f);
                FastVecAdd(v.vector, v.vector, delta);
                vec_fast_divide_helper(v.vector, v.vector, 0.1666666716337204f);
                part_spawn_spinning_debris(position, v.vector, math_random_int_range(60, 90), 0, 0);
            }
            debris--;
            for (i = 0; i < debris; i++) {
                int special;
                float angle, azimuth, speed;
                int life;
                angle = math_random_float_range(0.2617994248867035f, 1.3089970350265503f);
                azimuth = math_random_angle();
                speed = math_random_float_range(7.0f, 10.5f);
                vec_build_spherical_offset(v.random, scale * 0.01666666753590107f * speed, azimuth, angle);
                v.random[2] += 0.03333333507180214f;
                {
                    int rem = i % 3;
                    int one = 1;
                    int zero = 0;
                    special = zero;
                    if (rem == 0) special = one;
                }
                life = math_random_int_range(60, 90);
                part_spawn_spinning_debris(position, v.random, life, special, 0);
            }
        }
    }
    {
        int count;
        float under;
        int i;
        if (distance < IntToFloat(flashes) * 2.0f)
        count = FloatToInt(distance) / 2;
        else
        count = flashes;
        under = 0.0f;
        if (distance < 7.0f) under = 7.0f - distance;
        for (i = 0; i < count; i++) {
            {
                BurstColors colors1, colors2;
                float size, big;
                int c1, c2;
                size = math_random_float_range(8.0f, 10.0f) * 0.01666666753590107f;
                colors1 = D_001A9F20;
                colors2 = D_001A9F38;
                size = size - under * 0.01666666753590107f;
                c1 = math_random_int_below(6);
                size *= scale;
                c1 = gfx_swap_packed_color_channels(colors1.colors[c1], channels);
                c2 = gfx_swap_packed_color_channels(colors2.colors[math_random_int_below(6)], channels);
                big = scale * 400000.0f;
                {
                    int life = math_random_int_range(15, 20) - quality * 3;
                    int life2 = math_random_int_range(30, 45) - quality * 5;
                    part_spawn_firework_spark(position, drift, c1, c2, big, life, life2, size, 0, 0);
                }
                {
                    int life = math_random_int_range(5, 10) - quality * 2;
                    int life2 = math_random_int_range(15, 20) - quality * 3;
                    part_spawn_firework_spark(position, drift, 0x7FFFFFFF, 0xFFFFFF, big, life, life2, size * 0.5f, 0, 0);
                }
            }
        }
    }
    {
        int i;
        for (i = 0; i < smoke; i++) {
            {
                BurstColors colors1, colors2;
                ExplosionVectors v;
                float speed, k;
                int c1, c2;
                colors1 = D_001A9F20;
                colors2 = D_001A9F38;
                *(Quad *)v.random = 0;
                v.random[0] = math_random_float_range(-1.0f, 1.0f);
                v.random[1] = math_random_float_range(-1.0f, 1.0f);
                v.random[2] = math_random_float_range(-1.0f, 1.0f);
                *(Quad *)v.vector = *(Quad *)v.random;
                k = 0.01666666753590107f;
                speed = math_random_float_range(0.0f, 3.0f);
                vec_scale_to_length(v.vector, v.vector, scale * k * speed);
                c1 = gfx_swap_packed_color_channels(colors1.colors[math_random_int_below(6)], channels);
                c2 = gfx_swap_packed_color_channels(colors2.colors[math_random_int_below(6)], channels);
                part_spawn_color_blend(position, v.vector, c1, c2, math_random_int_range(30, 45) - quality * 5, 200000.0f);
            }
        }
    }
    if (owner && glow > 0.0f) {
        int r = 150, g = 150, b = 150, r2 = 127, g2 = 127, b2 = 0;
        if (channels) {
            if (!(channels & 4)) { r = 70; b = 70; r2 = 60; }
            else { r = 35; g = 0; b = 250; r2 = 32; g2 = 0; b2 = 100; }
        }
        if (D_001B168C[0] < 0.949999988079071f && cutoff < distance) {
            part_spawn_shockwave_ring(owner, position, drift, glow, 16, r, g, b, 32);
            part_spawn_shockwave_ring(owner, position, drift, glow, 22, r2 & 255, g2 & 255, b2 + 80, 32);
        }
        part_spawn_shockwave_ring(owner, position, drift, glow, 30, r2 & 255, g2 & 255, b2, 48);
    }
    if (owner && white > 0.0f) part_spawn_shockwave_ring(owner, position, drift, white, 27, 255, 255, 255, 32);
    if (shake) {
        {
            float vector[4];
            *(Quad *)vector = *(Quad *)position;
            vector[3] = 2.0f;
            if (math_fast_helper_a(vector, 10.0f) != -1) {
                ExplosionCamera *camera = &g_active_camera;
                if (distance < 20.0f) camera->shake = 0.4f - distance * 0.017500000074505806f;
                else camera->shake = 0.050000011920928955f;
                {
                    ExplosionCamera *state = &g_active_camera;
                    state->timer = 25;
                    state->phase = 0;
                }
            }
        }
    }
    if (owner && sound != -1) PlayMobySound(sound, 0, owner);
    if (blast != 0.0f && quality == 0) {
        {
            float vector[4];
            qcopy(vector, position);
            vector[3] = blast;
            if (math_fast_helper_a(vector, 100.0f) != -1) {
                if (blast > 0.0f) {
                    BlastEffect *effect = &D_00258C80;
                    effect->scale[1] = blast;
                    effect->scale[2] = blast;
                    effect->scale[0] = blast;
                } else {
                    BlastEffect *effect = &D_00258C80;
                    effect->scale[1] = 15.0f;
                    effect->scale[2] = 15.0f;
                    effect->scale[0] = 15.0f;
                }
                if (channels) moby_spawn_template_effect(&D_00258CD0, position, 0, 0);
                else moby_spawn_template_effect(&D_00258C80, position, 0, 0);
            }
        }
    }
}
