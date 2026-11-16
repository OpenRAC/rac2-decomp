#include "include_asm.h"
#include "names.h"

typedef int Quadword __attribute__((mode(TI)));
extern unsigned char *part_alloc(int);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern unsigned char *g_dark_puff_effect_byte;

/* Spawns a dark puff particle with the given velocity and lifetime (PAL). */
unsigned char *part_spawn_dark_puff_pal(Quadword *position, float *velocity, int flags, int lifetime, float scale) {
    unsigned char *particle = part_alloc(0x6B);
    unsigned char *motion;
    int shade;
    if (particle) {
        *(Quadword *)(particle + 0x10) = *position;
        motion = particle + 0x20;
        particle[9] = FloatToInt(4.0f) + 0x40;
        particle[3] = flags;
        particle[1] = 0;
        particle[8] = math_random_int_below(255);
        particle[2] = *g_dark_puff_effect_byte;
        *(short *)(particle + 0xA) = lifetime;
        *(float *)motion = velocity[0];
        *(float *)(motion + 4) = velocity[1];
        *(float *)(motion + 8) = velocity[2];
        shade = math_random_int_range(15, 11);
        *(int *)(motion + 0xC) = (shade << 16) + (shade << 8) + shade;
        motion[0x10] = math_random_int_range(1, 4);
        motion[0x11] = lifetime;
        motion[0x13] = 0;
        motion[0x12] = math_random_int_range(95, 127);
        *(float *)(motion + 0x18) = math_random_float_range(0.125f, 0.15f) * 105000.0f;
        *(float *)(motion + 0x1C) = math_random_float_range(0.25f, 0.5f) * 210000.0f;
        motion[0x14] = FloatToInt(scale * 128.0f);
        motion[0x15] = FloatToInt(math_random_float_range(0.9f, 1.1f) * 12.800001f);
        motion[0x16] = FloatToInt(math_random_float_range(0.0f, 0.0125f) * 128.0f);
        motion[0x17] = 0;
        *(int *)(particle + 4) = ((unsigned)motion[0x12] << 24) | 0x103080;
    }
    return particle;
}

extern unsigned char *g_accelerated_puff_byte;

/* Spawns a puff particle that is also pushed by an acceleration (PAL). */
unsigned char *part_spawn_accelerated_puff_pal(Quadword *position, float *velocity, float *acceleration,
                              int flags, int lifetime, float scale) {
    unsigned char *particle = part_alloc(0x6C);
    unsigned char *motion;
    int frame, shade;
    float *force;
    if (particle) {
        *(Quadword *)(particle + 0x10) = *position;
        motion = particle + 0x20;
        particle[9] = FloatToInt(4.0f) + 0x40;
        particle[3] = flags;
        particle[1] = 0;
        particle[8] = math_random_int_below(255);
        particle[2] = *g_accelerated_puff_byte;
        *(short *)(particle + 0xA) = lifetime;
        *(float *)motion = velocity[0];
        *(float *)(motion + 4) = velocity[1];
        *(float *)(motion + 8) = velocity[2];
        force = (float *)(particle + 0x30);
        force[0] = acceleration[0];
        force[1] = acceleration[1];
        force[2] = acceleration[2];
        frame = math_random_int_range(0, 11);
        shade = math_random_int_range(0, 15);
        motion[0xC] = frame | (shade << 4);
        motion[0xD] = math_random_int_range(1, 4) << 4;
        motion[0xE] = lifetime;
        motion[0x1E] = FloatToInt(math_random_float_range(0.15f, 0.25f) * 128.0f);
        motion[0x1F] = FloatToInt(math_random_float_range(0.5f, 1.0f) * 128.0f);
        motion[0x1C] = FloatToInt(math_random_float_range(0.9f, 1.1f) * 12.800001f);
        motion[0x1D] = FloatToInt(math_random_float_range(0.0f, 0.0125f) * 128.0f);
        motion[0xF] = FloatToInt(scale * 128.0f);
        *(unsigned int *)(particle + 4) = ((unsigned)(shade + 0x70) << 24) | 0x103080;
    }
    return particle;
}
