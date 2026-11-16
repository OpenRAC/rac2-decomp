#include "names.h"
typedef int Quadword __attribute__((mode(TI)));
extern unsigned char *part_alloc(int);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float math_random_angle(void);
extern unsigned char *g_accelerated_puff_byte;

/* Spawns a puff particle that is pushed by an extra acceleration as well as its velocity. */
unsigned char *part_spawn_accelerated_puff(Quadword *position, float *velocity, float *acceleration,
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
        motion[0x1C] = FloatToInt(math_random_float_range(0.9f, 1.1f) * 10.666667f);
        motion[0x1D] = FloatToInt(math_random_float_range(0.0f, 0.0125f) * 128.0f);
        motion[0xF] = FloatToInt(scale * 128.0f);
        *(unsigned int *)(particle + 4) = ((unsigned)(shade + 0x70) << 24) | 0x103080;
    }
    return particle;
}
