#include "include_asm.h"

#include "common.h"
extern char *func_002B9030(int);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern unsigned char *D_L04_001FF390;

char *func_PAL_L04_00365B68(void *position, void *velocity, int word, int color,
                           int index, float lifetime, float scale, float size)
{
    char *particle = func_002B9030(0x32);
    char *data;
    if (particle) {
        data = particle + 0x20;
        qcopy(particle + 0x10, position);
        particle[9] = func_00283CF0(1.0f) + 0x40;
        particle[3] = 0x44;
        particle[1] = 0;
        particle[2] = D_L04_001FF390[index];
        *(int *)(particle + 4) = color;
        *(float *)(particle + 0xC) = lifetime * 210000.0f;
        particle[8] = (int)func_002A7878(0.0f, 255.0f);
        *(short *)(particle + 0xA) = 12;
        qcopy(data, velocity);
        *(int *)(data + 0x1C) = word;
        *(float *)(data + 0x10) = scale;
        *(int *)(data + 0x14) = func_00283CF0(func_002A7878(-3.0f, 3.0f));
        *(float *)(data + 0x18) = size;
    }
    return particle;
}
