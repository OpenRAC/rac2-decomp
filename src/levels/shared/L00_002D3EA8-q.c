#include "include_asm.h"
#include "common.h"

extern char D_00189E20[];
extern float func_00282E20(char *);
extern float func_00283248(float, float);
extern void func_002830C0(void *, void *, char *);

/* Returns the angle of a vector in the current view mode space, turning it first when needed. */
float func_L00_002D3EA8(char *vec)
{
    char *heroBase = gHeroState;
    int viewMode = *(unsigned char *)(heroBase + 8899);
    float rotated[4] __attribute__((aligned(16)));

    if (viewMode == 0)
        return FastMatrixHelperA(*(float *)(vec + 8), vec_length_xy(vec));
    if (viewMode < 0)
        return 0.0f;
    if (viewMode >= 3)
        return 0.0f;
    qcopy(rotated, vec);
    transform_vector(rotated, rotated, heroBase + 64);
    return FastMatrixHelperA(rotated[2], vec_length_xy((char *)rotated));
}
