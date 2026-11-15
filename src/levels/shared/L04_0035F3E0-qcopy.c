#include "common.h"
extern char *part_alloc(int);
extern int FloatToInt(float);
extern int math_random_int_below(int);
extern float math_random_float_range(float, float);
extern unsigned char *D_L04_001FF320;

/* Allocates and initializes one effect record, preserving the two independent
 * random trials that select its secondary control word. */
char *part_spawn_random_effect_record(void *position, void *velocity, int mode, float size)
{
    char *particle = part_alloc(0x48);
    char *data;
    if (particle) {
        qcopy(particle + 0x10, position);
        *(int *)(particle + 4) = 0x7FFFFFFF;
        particle[9] = FloatToInt(4.0f) + 0x40;
        particle[3] = 0x48;
        particle[1] = 0;
        if (mode >= 0)
            *(float *)(particle + 0xC) = math_random_float_range(20000.0f, 40000.0f);
        else
            *(float *)(particle + 0xC) = math_random_float_range(40000.0f, 80000.0f);
        data = particle + 0x20;
        particle[8] = math_random_int_below(8) + 0x1C;
        particle[2] = D_L04_001FF320[0];
        *(int *)(data + 0x10) = mode;
        qcopy(data, velocity);
        *(int *)(data + 0x14) = 0;
        *(int *)(data + 0x18) = math_random_int_below(12) - 6;
        *(float *)(data + 0xC) = size;
        *(float *)(data + 0x1C) = *(float *)(particle + 0xC) * 0.1f;
        if (mode >= 0) {
            *(float *)(data + 0x1C) = *(float *)(particle + 0xC) * 0.05f;
            if (math_random_int_below(30) == 0)
                *(int *)(data + 0x14) = -40;
            else if (math_random_int_below(30) == 0)
                *(int *)(data + 0x14) = -1;
        }
    }
    return particle;
}
