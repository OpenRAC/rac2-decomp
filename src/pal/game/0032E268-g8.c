#include "names.h"
/* func_PAL_0032E268, the PAL copy of func_0032CA40: the same C, where the per-frame steps 1/60 become 1/50
 * (0.0166667f, 0.0333333f, 0.0040556f, 0.133333f become 0.02f, 0.04f, 0.00584f, 0.16f) and frame counts
 * pass through the 50 Hz scale ((x) * 5 + 2) / 6.  The two fixed-count loops count up here. */
#include "common.h"

extern float g_explosion_angle_scale __attribute__((sda));
extern float g_explosion_size_scale __attribute__((sda));
extern int g_explosion_particle_kind __attribute__((sda));
extern unsigned char *g_part_tex_flash_puffs_table __attribute__((section(".data")));
typedef struct {
    char pad0[0xD4];
    unsigned char *a;
    char pad1[0x98];
    unsigned char *b;
} EffectTextures;
extern unsigned char *g_particle_texture_table[];
extern char g_default_effect_vector[] __attribute__((sda));
typedef struct {
    char pad[0x140];
    float x, y, z;
} EffectCamera;
extern EffectCamera g_active_camera;
/* These typed interleavings preserve the EE integer and floating-point argument banks. */
extern char *part_spawn_gravity_fade(void *, void *, int, int, int, int, int, float, float, float, int);
extern char *part_spawn_fading_drift(void *, void *, int, int, int, int, int, float, float, float, int);
extern char *part_spawn_trail_2(void *, void *, int, float);
extern float math_random_float_range(float, float), math_random_signed_float_range(float, float);
extern int math_random_int_range(int, int), FloatToInt(float);
extern float IntToFloat(int), mat_fast_helper_a(float, float);
extern float FastAddRotations(float, float), math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *), FastVecScale(void *, void *, float);
extern void math_build_axis_angle_quat(void *, void *, float), vec_rotate_by_quaternion(void *, void *, void *);
extern char *part_spawn_shockwave_ring(void *, void *, void *, int, int, int, int, int, float);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern void vec_build_spherical_offset(void *, float, float, float);
extern char *SpawnSpinningSparkParticle(void *, float, float, float, float, int, void *, int, int);

#define F(p, o) (*(float *)((char *)(p) + (o)))
#define I(p, o) (*(int *)((char *)(p) + (o)))

typedef struct {
    int unused, mode;
    char pad[2];
    unsigned char alpha, life;
    char padC[16];
    float growth;
} EffectParticleData;
typedef unsigned int EffectQuad __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } EffectVec __attribute__((aligned(16)));

/* Emits the explosion layers, debris and spinning sparks configured by the object. */
void func_PAL_0032E268(char *object, void *radial, void *attachment, float distance)
{
    EffectVec pos, velocity, rotated;
    char *state = *(char **)(object + 0x68), *particle;
    int i, sign;
    {
        float angle, size;
        angle = g_explosion_angle_scale * F(state, 0x14) * 210000.0f;
        size = g_explosion_size_scale * F(state, 0x14) * 210000.0f;
        {
            particle = part_spawn_gravity_fade(object + 0x10, attachment, (g_explosion_particle_kind * 5 + 2) / 6, 0x388EF7, 0, 100, 0, angle, size, 0.0f, 0);
            if (particle) particle[2] = g_part_tex_flash_puffs_table[0];
            particle = part_spawn_gravity_fade(object + 0x10, attachment, (g_explosion_particle_kind * 5 + 2) / 6, 0x63F7, 0, 100, 0, angle, size, 0.0f, 0);
            if (particle) particle[2] = g_part_tex_flash_puffs_table[0];
        }
        {
            int i;
            for (i = 0; i < 2; i++) {
                particle = part_spawn_gravity_fade(object + 0x10, attachment, (g_explosion_particle_kind * 5 + 2) / 6, 0x388EF7, 0, 127, 0, angle, size, 0.0f, 0);
                if (particle) particle[2] = ((EffectTextures *)g_particle_texture_table)->b[5];
            }
        }
        {
            int i;
            for (i = 0; i < 2; i++) {
                particle = part_spawn_gravity_fade(object + 0x10, attachment, (g_explosion_particle_kind * 5 + 2) / 6, 0x388EF7, 0, 127, 0, angle, size, 0.0f, 0);
                if (particle) particle[2] = ((EffectTextures *)g_particle_texture_table)->b[6];
            }
        }
    }
    {
        int i;
        for (i = 0; i < I(state, 32); i++) {
            int spin, life;
            char *particle;
            float facing, size, speed, angle;
            facing = mat_fast_helper_a(g_active_camera.x - F(object, 0x10), g_active_camera.y - F(object, 0x14));
            spin = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
            life = math_random_int_range(30, 50);
            pos.x = F(object, 0x10) + math_random_signed_float_range(0.0f, 0.1f) * F(state, 0x14);
            pos.y = F(object, 0x14) + math_random_signed_float_range(0.0f, 0.1f) * F(state, 0x14);
            pos.z = F(object, 0x18) + math_random_signed_float_range(0.0f, 0.1f) * F(state, 0x14);
            size = math_random_float_range(0.6f, 1.0f) * F(state, 0x14);
            speed = math_random_float_range(9.0f, 12.0f) * F(state, 0x14);
            angle = FastAddRotations(facing, math_random_signed_float_range(0.0f, 1.396263599395752f));
            velocity.x = math_fast_sin_or_cos_a(angle) * 0.020000001f * speed;
            velocity.y = math_fast_sin_or_cos_b(angle) * 0.020000001f * speed;
            velocity.z = 0.0f;
            speed = math_random_float_range(0.0f, 12.0f) * F(state, 0x14);
            velocity.z = speed * 0.020000001f;
            FastVecAdd(&velocity, &velocity, attachment);
            particle = part_spawn_fading_drift(&pos, &velocity, (life * 5 + 2) / 6, 0x407FFF, spin, 127, 127, size * 210000.0f, F(state, 0x14) * 2100.0f, 0.00584f, 1);
            particle = part_spawn_fading_drift(&pos, &velocity, (life * 5 + 2) / 6, 0x20FF, -(spin * 2), 48, 48, size * 1260000.0f, F(state, 0x14) * 4200.0f, 0.00584f, 0);
            if (particle) particle[2] = ((EffectTextures *)g_particle_texture_table)->a[0];
        }
    }
    {
        int i;
        for (i = 0; i < I(state, 36); i++) {
            int spin, life;
            char *particle;
            float facing, size, speed, angle;
            facing = mat_fast_helper_a(g_active_camera.x - F(object, 0x10), g_active_camera.y - F(object, 0x14));
            spin = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
            life = math_random_int_range(30, 50);
            pos.x = F(object, 0x10) + math_random_signed_float_range(0.0f, 0.1f) * F(state, 0x14);
            pos.y = F(object, 0x14) + math_random_signed_float_range(0.0f, 0.1f) * F(state, 0x14);
            pos.z = F(object, 0x18) + math_random_signed_float_range(0.0f, 0.1f) * F(state, 0x14);
            size = math_random_float_range(0.75f, 1.5f) * F(state, 0x14);
            speed = math_random_float_range(9.0f, 12.0f) * F(state, 0x14);
            angle = FastAddRotations(facing, math_random_signed_float_range(0.0f, 1.396263599395752f));
            velocity.x = math_fast_sin_or_cos_a(angle) * 0.020000001f * speed;
            velocity.y = math_fast_sin_or_cos_b(angle) * 0.020000001f * speed;
            velocity.z = 0.0f;
            speed = math_random_float_range(0.0f, 12.0f) * F(state, 0x14);
            velocity.z = speed * 0.020000001f;
            FastVecAdd(&velocity, &velocity, attachment);
            particle = part_spawn_fading_drift(&pos, &velocity, (life * 5 + 2) / 6, 0x8FFF, spin, 127, 127, size * 210000.0f, F(state, 0x14) * 2100.0f, 0.00584f, 5);
        }
    }
    {
        int i;
        for (i = 0; i < I(state, 40); i++) {
            int spin, life;
            char *particle;
            float facing, size, speed, angle;
            facing = mat_fast_helper_a(g_active_camera.x - F(object, 0x10), g_active_camera.y - F(object, 0x14));
            spin = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
            life = math_random_int_range(30, 50);
            pos.x = F(object, 0x10) + math_random_signed_float_range(0.0f, 0.1f) * F(state, 0x14);
            pos.y = F(object, 0x14) + math_random_signed_float_range(0.0f, 0.1f) * F(state, 0x14);
            pos.z = F(object, 0x18) + math_random_signed_float_range(0.0f, 0.1f) * F(state, 0x14);
            size = math_random_float_range(0.6f, 1.0f) * F(state, 0x14);
            speed = math_random_float_range(9.0f, 12.0f) * F(state, 0x14);
            angle = FastAddRotations(facing, math_random_signed_float_range(0.0f, 1.396263599395752f));
            velocity.x = math_fast_sin_or_cos_a(angle) * 0.020000001f * speed;
            velocity.y = math_fast_sin_or_cos_b(angle) * 0.020000001f * speed;
            velocity.z = 0.0f;
            speed = math_random_float_range(0.0f, 12.0f) * F(state, 0x14);
            velocity.z = speed * 0.020000001f;
            FastVecAdd(&velocity, &velocity, attachment);
            particle = part_spawn_fading_drift(&pos, &velocity, (life * 5 + 2) / 6, 0x3064FF, spin, 127, 127, size * 210000.0f, F(state, 0x14) * 2100.0f, 0.00584f, 3);
        }
    }
    {
        int i;
        for (i = 0; i < I(state, 0x30); i++) {
            float speed, angle, turn;
            int life;
            speed = math_random_float_range(15.0f, 20.0f) * F(state, 0x14);
            FastVecScale(&pos, object + 0xC0, speed * 0.020000001f);
            angle = math_random_signed_float_range(0.2617994248867035f, 1.396263599395752f);
            turn = math_random_signed_float_range(0.2617994248867035f, 1.396263599395752f);
            math_build_axis_angle_quat(&rotated, object + 0xD0, angle);
            vec_rotate_by_quaternion(&velocity, &pos, &rotated);
            math_build_axis_angle_quat(&rotated, object + 0xC0, turn);
            vec_rotate_by_quaternion(&velocity, &velocity, &rotated);
            FastVecAdd(&velocity, &velocity, attachment);
            life = math_random_int_range(20, 35);
            part_spawn_trail_2(object + 0x10, &velocity, (life * 5 + 2) / 6, 0.00584f);
        }
    }
    if (I(state, 0x34)) {
        *(EffectQuad *)&velocity = 0;
        velocity.z = F(state, 0x14) * 0.16000001f;
        *(EffectQuad *)&pos = *(EffectQuad *)&velocity;
        FastVecAdd(&pos, &pos, attachment);
        part_spawn_shockwave_ring(object, object + 0x10, &pos, (16 * 5 + 2) / 6, 255, 0, 0, 40, F(state, 0x14) * 3.5f);
    }
    SpawnExplosionEffects(object, g_default_effect_vector, object + 0x10, 0.0f, 0.0f, 0, 0, 0, 0.0f, 0.0f, 9.0f, 0.0f, -1, distance * F(state, 0x14), 0, 0, -1, 0, 0x810001);
    {
        float angle;
        sign = 1;
        angle = mat_fast_helper_a(g_active_camera.x - F(object, 0x10), g_active_camera.y - F(object, 0x14));
        for (i = 0; i < I(state, 0x2C); i++) {
            float size, turn, height;
            char *particle;
            sign = -sign;
            pos.x = F(object, 0x10) + math_random_signed_float_range(0.0f, 1.0f) * F(state, 0x14);
            pos.y = F(object, 0x14) + math_random_signed_float_range(0.0f, 1.0f) * F(state, 0x14);
            pos.z = F(object, 0x18) + math_random_signed_float_range(0.0f, 1.0f) * F(state, 0x14);
            size = math_random_float_range(0.020000001f, 0.040000003f) * F(state, 0x14);
            turn = math_random_signed_float_range(0.0f, 1.396263599395752f);
            height = FastAddRotations(angle, math_random_signed_float_range(0.0f, 1.5707964897155762f));
            vec_build_spherical_offset(&velocity, size, height, turn);
            FastVecAdd(&velocity, &velocity, attachment);
            particle = SpawnSpinningSparkParticle(&pos, 0.0f, 1.0f, 1.0099999904632568f, F(state, 0x14) * 315000.0f, sign, &velocity, 0x7F60A0FF, 0);
            if (particle) {
                EffectParticleData *data = (EffectParticleData *)(particle + 0x20);
                *(short *)(particle + 0xA) = (math_random_int_range(40, 70) * 5 + 2) / 6;
                particle[9] = FloatToInt(4.0f) + 64;
                data->mode = 3;
                data->growth = IntToFloat((math_random_int_range(1, 10) * 5 + 2) / 6);
                data->alpha = 64;
                data->life = particle[0xA];
            }
        }
    }
}
