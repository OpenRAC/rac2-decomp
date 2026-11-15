#include "names.h"
typedef int TI128 __attribute__((mode(TI)));

extern char *g_path_list[];
extern int point_in_path_xy(float *, float *, int);
extern void math_random_planar_offset(void *, float);
extern void FastVecAdd(void *, void *, void *);

/* Finds a spot near the actor that lies inside its current path area; returns 1 if it found one. */
int actor_find_path_area_point(char *moby, char *stateArg)
{
    char *position = moby + 0x10;
    char *vars = stateArg;
    int found = 0;

    if (point_in_path_xy((float *)position,
                      (float *)((char *)g_path_list[*(int *)(vars + 0x230)] + 0x10),
                      *(int *)g_path_list[*(int *)(vars + 0x230)]) == 0) {
        *(TI128 *)(vars + 0x5B0) = *(TI128 *)(vars + 0x460);
        *(float *)(vars + 0x5BC) = 1.0f;
        return 1;
    }
    {
        char *probePoint = vars + 0x5B0;

        math_random_planar_offset(probePoint, 7.0f);
        FastVecAdd(probePoint, probePoint, position);
        *(int *)(vars + 0x5BC) = 0;
        if (point_in_path_xy((float *)probePoint,
                          (float *)((char *)g_path_list[*(int *)(vars + 0x230)] + 0x10),
                          *(int *)g_path_list[*(int *)(vars + 0x230)]) != 0) {
            *(float *)(vars + 0x5BC) = 1.0f;
            found = 1;
        } else {
            *(TI128 *)probePoint = *(TI128 *)position;
        }
    }
    return found;
}
