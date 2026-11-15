#include "common.h"

extern int func_00283CF0_2(float f);
extern int func_00283D38_1(int a, int b, float f);
extern float func_002A7878_3(float a, float b);

extern char *part_alloc(int kind);
extern int math_random_int_below(int a);
extern int math_random_int_range(int a, int b);
extern char *D_L00_001FEAF4;

/* Create a type-0x6D object with two vector records and a packed identifier. */
/* Spawns a short-lived particle with a random lifetime and a fading tint. */
char *CreateType6DObject(char *position, char *velocity, int flags, float scale)
{
    char *particle = part_alloc(0x6D);
    char *motion;
    float tint;

    if (particle) {
        qcopy(particle + 0x10, position);
        motion = particle + 0x20;
        {
            int value = func_00283CF0_2(4.0f) + 0x40;
            *(unsigned char *)(particle + 3) = flags;
            *(unsigned char *)(particle + 1) = 0;
            *(unsigned char *)(particle + 9) = value;
        }
        *(unsigned char *)(particle + 8) = math_random_int_below(0xFF);
        *(unsigned char *)(particle + 2) = *(unsigned char *)D_L00_001FEAF4;
        *(unsigned short *)(particle + 0xA) = math_random_int_range(5, 0x32);
        qcopy(motion, velocity);
        *(float *)(particle + 0xC) = scale * 525000.0f;
        *(unsigned int *)(motion + 0x10) = math_random_int_range(0x40, 0x80);
        tint = func_002A7878_3(0.0f, 0.5f);
        *(unsigned int *)(particle + 4) = func_00283D38_1(0x103080, 0, tint) |
                                    (*(unsigned int *)(motion + 0x10) << 24);
    }
    return particle;
}
