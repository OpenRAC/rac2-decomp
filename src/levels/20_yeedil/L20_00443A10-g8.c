#include "common.h"

typedef struct { char reserved00[0x30]; float point[4]; char reserved40[0x40]; } HeadingReference;
extern HeadingReference *D_L20_001B308C;
extern struct { char reserved00[0x80]; float position[4]; } D_00189E20;
extern float D_L20_001B2098 __attribute__((sda));
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *, void *, void *);

void func_L20_00443A10(char *object, float *output)
{
    char *state = *(char **)(object + 0x68);
    float towardHero, heading;
    unsigned int index;
    float y;
    HeadingReference *reference;
    towardHero = func_00283248(D_00189E20.position[0] - *(float *)(object + 0x10),
        D_00189E20.position[1] - *(float *)(object + 0x14));
    index = *(unsigned int *)(state + 0x230);
    heading = func_00283248(D_L20_001B308C[index].point[0] - *(float *)(object + 0x10),
        D_L20_001B308C[index].point[1] - *(float *)(object + 0x14));
    if (0.0f < fast_subtract_rotations(towardHero, heading))
        heading = fast_subtract_rotations(heading, 1.5707964f);
    else
        heading = FastAddRotations(heading, 1.5707964f);
    output[0] = func_00283180(heading) * D_L20_001B2098;
    y = func_00283198(heading) * D_L20_001B2098;
    reference = D_L20_001B308C;
    *(int *)&output[2] = 0;
    output[1] = y;
    FastVecAdd(output, output, reference[*(unsigned int *)(state + 0x230)].point);
}
