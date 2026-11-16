#include "names.h"
typedef int Quadword __attribute__((mode(TI)));
extern unsigned char *part_alloc(int);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float math_random_angle(void);
extern unsigned char *g_puff_effect_byte;

/* Spawns a puff particle with a grey shade, drifting along the given velocity. */
unsigned char *part_l00_spawn_puff(Quadword *position, float *velocity, int flags, int lifetime, float scale) {
    unsigned char *particle = part_alloc(0x6A);
    unsigned char *motion;
    int shade;
    if (particle) {
        *(Quadword *)(particle + 0x10) = *position;
        motion = particle + 0x20;
        particle[9] = FloatToInt(4.0f) + 0x40;
        particle[3] = flags;
        particle[1] = 0;
        particle[8] = math_random_int_below(255);
        particle[2] = *g_puff_effect_byte;
        *(short *)(particle + 0xA) = lifetime;
        *(float *)motion = velocity[0];
        *(float *)(motion + 4) = velocity[1];
        *(float *)(motion + 8) = velocity[2];
        shade = math_random_int_range(15, 31);
        *(int *)(motion + 0xC) = (shade << 16) + (shade << 8) + shade;
        motion[0x10] = math_random_int_range(1, 4);
        motion[0x11] = lifetime;
        motion[0x13] = 0;
        motion[0x12] = math_random_int_range(95, 127);
        *(float *)(motion + 0x14) = math_random_float_range(0.0625f, 0.125f) * 210000.0f;
        *(float *)(motion + 0x18) = math_random_float_range(0.5f, 0.6f) * 210000.0f;
        *(float *)(motion + 0x1C) = scale;
        *(int *)(particle + 4) = ((unsigned)motion[0x12] << 24) | 0x103080;
    }
    return particle;
}
