#include "include_asm.h"
#include "names.h"
typedef int Position __attribute__((mode(TI)));
extern char D_00189E20[];
extern float D_L00_001BF228;
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_002761F8(void *, void *, int, void *, int);
/* Checks whether there is a ledge or step just in front of the hero that it can step onto. */
int func_L00_002CAD90(void)
{
    char *base = gHeroState;
    float first[4], second[4];
    float t;
    if ((unsigned char)base[0x22C3] == 2) return 0;
    if (*(float *)(base + 0x174) < *(float *)(base + 0x264) * 0.05f) return 0;
    t = FastDiffRots(FastMatrixHelperA(*(float *)(base + 0x110), *(float *)(base + 0x114)), *(float *)(base + 0x98));
    if (0.5235988497734069824f < t) return 0;
    *(Position *)first = *(Position *)(base + 0x80);
    first[0] += FastSinOrCosA(*(float *)(base + 0x98)) * *(float *)(base + 0x264) * 0.75f;
    first[1] += FastSinOrCosB(*(float *)(base + 0x98)) * *(float *)(base + 0x264) * 0.75f;
    *(Position *)second = *(Position *)first;
    first[2] += 0.47f;
    second[2] -= 1.0f;
    if (!CollLine(first, second, 2, *(void **)(base + 0x2290), 0)) return 0;
    t = D_L00_001BF228 - *(float *)(base + 0x88);
    if (t < 0.37f) {
        if (-1.0f < t) return 1;
        else return 0;
    }
    return 0;
}
