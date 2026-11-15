#include "common.h"

extern int func_00283CF0_2(float f);
extern int func_00283D38_1(int a, int b, float f);
extern float func_002A7878_3(float a, float b);

extern char *func_002B9030(int kind);
extern int func_002A77E0(int a);
extern int func_002A7820(int a, int b);
extern char *D_L00_001FEAF4;

/* Create a type-0x6D object with two vector records and a packed identifier. */
/* Spawns a short-lived particle with a random lifetime and a fading tint. */
char *func_L00_003411A0(char *position, char *velocity, int flags, float scale)
{
    char *particle = AllocParticle(0x6D);
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
        *(unsigned char *)(particle + 8) = RandomIntBelow(0xFF);
        *(unsigned char *)(particle + 2) = *(unsigned char *)D_L00_001FEAF4;
        *(unsigned short *)(particle + 0xA) = RandomIntRange(5, 0x32);
        qcopy(motion, velocity);
        *(float *)(particle + 0xC) = scale * 525000.0f;
        *(unsigned int *)(motion + 0x10) = RandomIntRange(0x40, 0x80);
        tint = func_002A7878_3(0.0f, 0.5f);
        *(unsigned int *)(particle + 4) = func_00283D38_1(0x103080, 0, tint) |
                                    (*(unsigned int *)(motion + 0x10) << 24);
    }
    return particle;
}
