#include "common.h"
extern char *func_002B9030(int);
extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern float func_002A7878(float, float);
extern unsigned char *D_L04_001FF320;

/* Allocates and initializes one effect record, preserving the two independent
 * random trials that select its secondary control word. */
char *func_L04_0035F3E0(void *position, void *velocity, int mode, float size)
{
    char *particle = func_002B9030(0x48);
    char *data;
    if (particle) {
        qcopy(particle + 0x10, position);
        *(int *)(particle + 4) = 0x7FFFFFFF;
        particle[9] = func_00283CF0(4.0f) + 0x40;
        particle[3] = 0x48;
        particle[1] = 0;
        if (mode >= 0)
            *(float *)(particle + 0xC) = func_002A7878(20000.0f, 40000.0f);
        else
            *(float *)(particle + 0xC) = func_002A7878(40000.0f, 80000.0f);
        data = particle + 0x20;
        particle[8] = func_002A77E0(8) + 0x1C;
        particle[2] = D_L04_001FF320[0];
        *(int *)(data + 0x10) = mode;
        qcopy(data, velocity);
        *(int *)(data + 0x14) = 0;
        *(int *)(data + 0x18) = func_002A77E0(12) - 6;
        *(float *)(data + 0xC) = size;
        *(float *)(data + 0x1C) = *(float *)(particle + 0xC) * 0.1f;
        if (mode >= 0) {
            *(float *)(data + 0x1C) = *(float *)(particle + 0xC) * 0.05f;
            if (func_002A77E0(30) == 0)
                *(int *)(data + 0x14) = -40;
            else if (func_002A77E0(30) == 0)
                *(int *)(data + 0x14) = -1;
        }
    }
    return particle;
}
