#include "include_asm.h"
#include "common.h"

extern char *part_alloc(int);
extern int FloatToInt(float);
extern int func_001163B0(void);
extern unsigned char **D_001F2550[];

/* Creates a moving particle with its own colour and life, starting at a point with a velocity. */
char *part_spawn_scaling(void *position, void *velocity, unsigned int color, int endColor, int life, int scale, int type, int additive)
{
    char *particle = part_alloc(4);
    char *p;
    char *motion;

    if (particle != 0) {
        qcopy(particle + 0x10, position);
        *(unsigned int *)(particle + 4) = color;
        *(char *)(particle + 9) = FloatToInt(4.0f) - 0x60;
        *(char *)(particle + 3) = additive ? 0x48 : 0x44;
        *(char *)(particle + 1) = 0;
        *(char *)(particle + 2) = **(unsigned char **)D_001F2550;
        *(char *)(particle + 8) = func_001163B0();
        *(int *)(particle + 0xC) = 0;
        motion = particle + 0x20;
        qcopy(particle + 0x10, position);
        qcopy(motion, velocity);
        *(short *)(particle + 0xA) = life;
        *(int *)(motion + 0x1C) = life;
        *(int *)(motion + 0x10) = color;
        *(int *)(motion + 0x14) = endColor;
        *(short *)(motion + 0x18) = type;
        *(short *)(motion + 0x1A) = scale;
    }
    return particle;
}
