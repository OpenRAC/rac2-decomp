#include "names.h"
typedef int V4_Fc936841d __attribute__((mode(TI)));

extern char *func_0029EFD0(int);
extern float func_002A78D8(float, float);
extern void func_002A0F48(void *);

/* Creates a small flying object (class 3031) at a given place, with a random spin. */
char *func_003285C0(int ownerId, void *position, void *velocity)
{
    char *moby = CreateMoby(0xBD7 /* moby class 3031 */);
    char *vars;
    int fullValue;

    if (moby != 0) {
        vars = *(char **)(moby + 0x68);
        *(int *)(vars + 0x40) = ownerId;
        *(V4_Fc936841d *)(moby + 0x10) = *(V4_Fc936841d *)position;
        *(V4_Fc936841d *)vars = *(V4_Fc936841d *)velocity;
        *(int *)(vars + 0x10) = 0;
        *(float *)(vars + 0x14) = RandomSignedFloatRange(180.0f, 360.0f) * 0.00029088825f;
        *(float *)(vars + 0x18) = RandomSignedFloatRange(180.0f, 360.0f) * 0.00029088825f;
        fullValue = 0xFF;
        *(unsigned short *)(moby + 0x32) = fullValue;
        *(unsigned char *)(moby + 0x30) = fullValue;
        *(float *)(moby + 0x2C) *= 0.5f;
        *(unsigned char *)(moby + 0x20) = 0;
        *(int *)(vars + 0x5C) = 0x1E;
        func_002A0F48(moby);
    }
    return moby;
}
