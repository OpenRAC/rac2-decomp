#include "common.h"

typedef struct {
    int color;          /* 0x00 */
    int color2;         /* 0x04 */
    int altColor;       /* 0x08 */
    int altColor2;      /* 0x0C */
    float x[2];         /* 0x10 */
    float y[2];         /* 0x18 */
    float z[2];         /* 0x20 */
    float radialDiv;    /* 0x28 */
    float verticalDiv;  /* 0x2C */
    int count;          /* 0x30 */
    float height;       /* 0x34 */
    float radialSpeed;  /* 0x38 */
    float verticalSpeed;/* 0x3C */
    float outer;        /* 0x40 */
    float inner;        /* 0x44 */
    float velW;         /* 0x48 */
    float accW;         /* 0x4C */
} ParticleConfig;

extern const ParticleConfig g_burst_particle_config;
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void matrix_mul_vec3(void *, void *, void *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int func_001163B0(void);
extern int FloatToInt(float);
extern u8 *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);

typedef struct {
    u8 pad[0x10];
    float position[4];  /* 0x10 */
    u8 pad20[0xA0];
    float rotation[16]; /* 0xC0 */
} ParticleOwner;

/* func_PAL_L01_003DCCC8, the PAL copy of func_L01_003D8830: the same C, where 0.016666668f becomes 0.020000001f and x, y and z take the 50 Hz scale. */
void part_l01_spawn_burst_pal(ParticleOwner *moby)
{
    float pos[4] __attribute__((aligned(16)));
    float vel[4] __attribute__((aligned(16)));
    float acc[4] __attribute__((aligned(16)));
    u8 *particle;
    ParticleOwner *owner = moby;
    int color = g_burst_particle_config.color, color2 = g_burst_particle_config.color2, use_alt, life_a, life_b, life_c;
    int i, count;
    float trig, radial_speed, vertical_speed, outer_radius;

    count = g_burst_particle_config.count;
    for (i = 0; i < count; i++) {
        trig = math_fast_sin_or_cos_a(math_random_float_range(-3.1415927f, 3.1415927f));
        trig *= math_random_float_range(g_burst_particle_config.inner, g_burst_particle_config.outer);
        pos[0] = trig;
        trig = math_fast_sin_or_cos_b(math_random_float_range(-3.1415927f, 3.1415927f));
        trig *= math_random_float_range(g_burst_particle_config.inner, g_burst_particle_config.outer);
        pos[1] = trig;
        pos[2] = 0;
        matrix_mul_vec3(pos, pos, owner->rotation);
        radial_speed = FastVecLength(pos);
        outer_radius = g_burst_particle_config.outer;
        radial_speed = g_burst_particle_config.radialSpeed * ((outer_radius - radial_speed) * 0.020000001f) / outer_radius;
        vec_scale_to_length(vel, pos, math_random_float_range(radial_speed / g_burst_particle_config.radialDiv, radial_speed));
        vertical_speed = g_burst_particle_config.verticalSpeed;
        vel[2] += math_random_float_range(vertical_speed / g_burst_particle_config.verticalDiv, vertical_speed) * 0.020000001f;
        qzero(acc);
        FastVecAdd(pos, pos, owner->position);
        pos[2] += g_burst_particle_config.height;
        vel[3] = g_burst_particle_config.velW;
        acc[3] = g_burst_particle_config.accW;
        use_alt = func_001163B0() & 1;
        if (!use_alt && (func_001163B0() & 1)) {
            color = g_burst_particle_config.altColor;
            color2 = g_burst_particle_config.altColor2;
        }
        life_a = FloatToInt((math_random_float_range(g_burst_particle_config.x[0], g_burst_particle_config.x[1]) * 5.0f + 2.0f) * 0.16666667f);
        life_b = FloatToInt((math_random_float_range(g_burst_particle_config.y[0], g_burst_particle_config.y[1]) * 5.0f + 2.0f) * 0.16666667f);
        life_c = FloatToInt((math_random_float_range(g_burst_particle_config.z[0], g_burst_particle_config.z[1]) * 5.0f + 2.0f) * 0.16666667f);
        particle = part_spawn_trail(pos, vel, acc, color, color2, life_a, life_b, life_c, -1);
        if (particle && use_alt)
            particle[3] = 0x48;
    }
}
