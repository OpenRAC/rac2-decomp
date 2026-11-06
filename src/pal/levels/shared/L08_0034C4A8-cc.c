/* func_PAL_L08_0034C4A8, the PAL copy of func_L08_0034A078: the same C, where scale func_002A7820(10, 30). */
#include "common.h"
extern unsigned char *func_002B9030(int);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_00283CE0(int);
extern unsigned char *D_L08_001FF794;
unsigned char *func_PAL_L08_0034C4A8(void *position, void *velocity, int kind, void *owner)
{
    unsigned char *particle = func_002B9030(0x45);
    if (particle) {
        unsigned char *data;
        int lifetime;
        qcopy(particle + 0x10, position);
        {
            int display = func_00283CF0(4.0f);
            data = particle + 0x20;
            particle[9] = display + 0x70;
        }
        particle[1] = 0;
        particle[3] = 0x48;
        *(float *)(particle + 0xc) = func_002A7878(8000.0f, 50000.0f);
        particle[8] = func_002A77E0(256);
        particle[2] = *D_L08_001FF794;
        lifetime = (((int)(func_002A7820(10, 30)) * 5 + 2) / 6);
        *(short *)(particle + 0xa) = lifetime;
        {
            float age = func_00283CE0((short)lifetime);
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
