#include "names.h"
typedef int Quadword __attribute__((mode(TI)));
extern unsigned char *part_alloc(int);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float math_random_angle(void);
extern unsigned char *g_spinning_effect_byte;

/* Spawns a small spinning particle at a position, moving with the given velocity. */
unsigned char *part_l00_spawn_spinning(Quadword *position, Quadword *velocity, int lifetime) {
    unsigned char *particle = part_alloc(0x66);
    unsigned char *motion;
    if (particle) {
        motion = particle + 0x20;
        particle[9] = FloatToInt(2.0f) + 0x40;
        particle[3] = 0x44;
        particle[1] = 0;
        particle[2] = *g_spinning_effect_byte;
        *(float *)(particle + 0xC) = math_random_float_range(0.03f, 0.175f) * 210000.0f;
        particle[8] = math_random_int_below(255);
        *(short *)(particle + 0xA) = lifetime;
        *(Quadword *)(particle + 0x10) = *position;
        *(Quadword *)motion = *velocity;
        *(float *)(motion + 0xC) = math_random_float_range(4.6f, 8.6f) * 0.00027777778f;
        *(float *)(motion + 0x18) = *(float *)(particle + 0xC) * 2.0f;
        *(short *)(motion + 0x16) = math_random_int_range(0, 3);
        *(short *)(motion + 0x14) = lifetime / 2;
        *(float *)(motion + 0x1C) = math_random_angle();
    }
    return particle;
}
