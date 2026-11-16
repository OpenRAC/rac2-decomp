#include "common.h"
extern char *part_alloc(int);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);
extern unsigned char *g_spinning_particle_colors;

/* Creates a spinning particle at a position, moving with the given velocity. */
char *part_l04_spawn_spinning(void *position, void *velocity, int word, int color,
                           int index, float lifetime, float scale, float size)
{
    char *particle = part_alloc(0x32);
    char *data;
    if (particle) {
        data = particle + 0x20;
        qcopy(particle + 0x10, position);
        particle[9] = FloatToInt(1.0f) + 0x40;
        particle[3] = 0x44;
        particle[1] = 0;
        particle[2] = g_spinning_particle_colors[index];
        *(int *)(particle + 4) = color;
        *(float *)(particle + 0xC) = lifetime * 210000.0f;
        particle[8] = (int)math_random_float_range(0.0f, 255.0f);
        *(short *)(particle + 0xA) = 15;
        qcopy(data, velocity);
        *(int *)(data + 0x1C) = word;
        *(float *)(data + 0x10) = scale;
        *(int *)(data + 0x14) = FloatToInt(math_random_float_range(-3.0f, 3.0f));
        *(float *)(data + 0x18) = size;
    }
    return particle;
}
