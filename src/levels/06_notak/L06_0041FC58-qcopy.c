#include "names.h"
typedef int TI128 __attribute__((mode(TI)));

extern char *D_L06_001FE500[];
extern int func_002A8AF0(float *, float *, int);
extern void func_L02_0031E9E8(void *, float);
extern void func_00282CC0(void *, void *, void *);

/* Finds a spot near the actor that lies inside its current path area; returns 1 if it found one. */
int func_L06_0041FC58(char *moby, char *stateArg)
{
    char *position = moby + 0x10;
    char *vars = stateArg;
    int found = 0;

    if (point_in_path_xy((float *)position,
                      (float *)((char *)gPathList[*(int *)(vars + 0x230)] + 0x10),
                      *(int *)gPathList[*(int *)(vars + 0x230)]) == 0) {
        *(TI128 *)(vars + 0x5B0) = *(TI128 *)(vars + 0x460);
        *(float *)(vars + 0x5BC) = 1.0f;
        return 1;
    }
    {
        char *probePoint = vars + 0x5B0;

        RandomPlanarOffset(probePoint, 7.0f);
        FastVecAdd(probePoint, probePoint, position);
        *(int *)(vars + 0x5BC) = 0;
        if (point_in_path_xy((float *)probePoint,
                          (float *)((char *)gPathList[*(int *)(vars + 0x230)] + 0x10),
                          *(int *)gPathList[*(int *)(vars + 0x230)]) != 0) {
            *(float *)(vars + 0x5BC) = 1.0f;
            found = 1;
        } else {
            *(TI128 *)probePoint = *(TI128 *)position;
        }
    }
    return found;
}
