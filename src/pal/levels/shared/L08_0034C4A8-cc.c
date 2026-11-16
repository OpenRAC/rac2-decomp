#include "names.h"
/* func_PAL_L08_0034C4A8, the PAL copy of func_L08_0034A078: the same C, where scale func_002A7820(10, 30). */
#include "common.h"
extern unsigned char *part_alloc(int);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float IntToFloat(int);
extern unsigned char *g_particle_color_ptr;
/* Spawns a short-lived particle at a position with a velocity, a random size and color, linked to an owner (PAL: 50 Hz lifetime). */
unsigned char *part_spawn_short_lived_pal(void *position, void *velocity, int kind, void *owner)
{
    unsigned char *particle = part_alloc(0x45);
    if (particle) {
        unsigned char *data;
        int lifetime;
        qcopy(particle + 0x10, position);
        {
            int display = FloatToInt(4.0f);
            data = particle + 0x20;
            particle[9] = display + 0x70;
        }
        particle[1] = 0;
        particle[3] = 0x48;
        *(float *)(particle + 0xc) = math_random_float_range(8000.0f, 50000.0f);
        particle[8] = math_random_int_below(256);
        particle[2] = *g_particle_color_ptr;
        lifetime = (((int)(math_random_int_range(10, 30)) * 5 + 2) / 6);
        *(short *)(particle + 0xa) = lifetime;
        {
            float age = IntToFloat((short)lifetime);
            *(void **)(data + 0x1c) = owner;
            *(float *)(data + 0x10) = 1.0f / age;
        }
        *(short *)(data + 0x14) = kind;
        *(int *)(data + 0x18) = 0x7f7f7f;
        *(short *)(data + 0x16) = 0;
        qcopy(data, velocity);
        *(unsigned int *)(particle + 4) = (kind << 24) | 0x7f7f7f;
    }
    return particle;
}
