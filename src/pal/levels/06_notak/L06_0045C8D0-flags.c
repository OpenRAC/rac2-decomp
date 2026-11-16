#include "include_asm.h"

#include "common.h"
extern void FastVecAdd(void *, void *, void *);
extern float math_fabs(float);
extern float math_random_float_range(float, float);
extern float g_spark_burst_threshold __attribute__((sda));
extern float g_level_float_param __attribute__((sda));
extern int PlayMobySound(int, int, char *);
extern void moby_mark_spawned(char *);
extern void matrix_mul_vec3(void *, void *, void *);
extern double __extendsfdf2(float);
extern void STUB_printf(char *, ...);
extern char g_str_spark_burst_debug[];
extern void part_spawn_glow_fade_effects_pal(char *, void *, int, float, int, void *, float, unsigned int, float, float, int);

/* Sprays sparks from the object's front side, then removes it. */
void part_emit_spark_burst_remove_pal(char *moby) {
    float pos[4], vel[4];
    int count = 13, i;
    if (g_spark_burst_threshold < 0.9f && g_level_float_param < 0.9f) count = 40;
    for (i = 0; i < count; i++) {
        pos[0] = math_random_float_range(-8.045f, 8.045f);
        pos[1] = math_fabs(pos[0] * 0.1243008077f) * 1.745f;
        pos[2] = math_random_float_range(0.0f, 3.99f);
        vel[0] = pos[0] * 0.0049720327f;
        vel[1] = -0.16000001f;
        vel[2] = math_random_float_range(3.0f, 7.0f) * 0.020000001f;
        matrix_mul_vec3(pos, pos, moby + 0xC0);
        FastVecAdd(pos, pos, moby + 0x10);
        matrix_mul_vec3(vel, vel, moby + 0xC0);
        STUB_printf(g_str_spark_burst_debug, __extendsfdf2(pos[0]), __extendsfdf2(pos[1]), __extendsfdf2(pos[2]), __extendsfdf2(vel[0]), __extendsfdf2(vel[1]), __extendsfdf2(vel[2]));
        part_spawn_glow_fade_effects_pal(moby, pos, 1, 0.0f, 1, vel, 3.0f, 0x50808040, 1.0f, 5.5f, 0);
        PlayMobySound(0, 0, moby);
    }
    moby_mark_spawned(moby);
}

extern void part_spawn_debris_mask(char *, int, void *, int, float, float, float, float);
extern float math_random_angle(void);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern char *cam_moby_create_pal(char *, int, int, int, char *, char *,
                           float *, int, float, float);

/* Spawns a drifting debris particle for each bit set in the mask, with random speed and life. */
void part_spawn_debris_mask_pal(char *object, int mask, void *offset, int color,
                      float speed_min, float speed_max,
                      float vertical_min, float vertical_max)
{
    float velocity[3];
    float angle, speed, life, size;
    char *particle;
    unsigned char shade = color;
    int i;

    for (i = 0; i < 15; i++) {
        if (((mask >> i) ^ 1) & 1)
            continue;
        angle = math_random_angle();
        speed = math_random_float_range(speed_min, speed_max) * (0.020000001f);
        velocity[0] = math_fast_sin_or_cos_a(angle) * speed;
        velocity[1] = math_fast_sin_or_cos_b(angle) * speed;
        velocity[2] = 0.0f;
        velocity[2] = math_random_float_range(vertical_min, vertical_max) * (0.020000001f);
        FastVecAdd(velocity, velocity, offset);
        life = math_random_float_range(90.0f, 270.0f);
        size = math_random_float_range(10.0f, 20.0f);
        particle = cam_moby_create_pal(object, 2, *(short *)(object + 0xAA), i,
                                object + 0x10, object + 0xF0, velocity, shade,
                                life, size);
        if (particle)
            *(unsigned short *)(particle + 0x34) |= 0x10;
    }
}
