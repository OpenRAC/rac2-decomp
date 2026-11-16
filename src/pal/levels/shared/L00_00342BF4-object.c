#include "include_asm.h"

#include "common.h"
extern int FloatToInt(float f);
extern int FastTweenColor(int a, int b, float f);
extern float math_random_float_range(float a, float b);
extern char *part_alloc(int kind);
extern int math_random_int_below(int a);
extern int math_random_int_range(int a, int b);
extern char *g_object_particle_byte;

/* Create a type-0x6D object with two vector records and a packed identifier. */
/* PAL version of CreateType6DObject. */
char *part_spawn_type_6d_object_pal(char *position, char *velocity, int flags, float scale)
{
    char *particle = part_alloc(0x6D);
    char *motion;
    float blend;

    if (particle) {
        qcopy(particle + 0x10, position);
        motion = particle + 0x20;
        {
            int value = FloatToInt(4.0f) + 0x40;
            *(unsigned char *)(particle + 3) = flags;
            *(unsigned char *)(particle + 1) = 0;
            *(unsigned char *)(particle + 9) = value;
        }
        *(unsigned char *)(particle + 8) = math_random_int_below(0xFF);
        *(unsigned char *)(particle + 2) = *(unsigned char *)g_object_particle_byte;
        *(unsigned short *)(particle + 0xA) = ((s32)(math_random_int_range(5, 0x32)) * 5 + 2) / 6;
        qcopy(motion, velocity);
        *(float *)(particle + 0xC) = scale * 525000.0f;
        *(unsigned int *)(motion + 0x10) = math_random_int_range(0x40, 0x80);
        blend = math_random_float_range(0.0f, 0.5f);
        *(unsigned int *)(particle + 4) = FastTweenColor(0x103080, 0, blend) |
                                    (*(unsigned int *)(motion + 0x10) << 24);
    }
    return particle;
}
