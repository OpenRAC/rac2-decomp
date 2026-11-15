#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float func_00282E48(void *, void *);
extern void func_L00_00341FA8(int, TI128 *, TI128 *, float, float, float, int *, float *, int);
extern short func_L09_0033E8B0(char *, int, TI128 *, int, int, float);
extern int func_L09_003E9E60(char *, TI128 *, float);
extern int D_L09_001FE6C0[];

/* Finds the closest point on a level table path and steps the object toward the nearer neighbor along it. */
int func_L09_003EA108(char *moby, int index)
{
    char *vars = *(char **)(moby + 0x68);
    struct { TI128 v0, v1, v2, v3; int e; float f; } local;
    TI128 *pos = (TI128 *)(vars + 0x140);

    local.e = -1;
    find_nearest_path_point(D_L09_001FE6C0[index], pos, &local.v0, 100000.0f, 1.0f, local.f = 0.0f, &local.e, &local.f, 0);
    if (fast_vec_dist(&local.v0, (TI128 *)(moby + 0x10)) > 2.0f) {
        TI128 *q2 = &local.v2;
        short forwardIdx = StepAlongPathTableEntry(moby, index, q2, *(short *)(vars + 0x118), 1, *(float *)(vars + 0x78) * 10.0f);
        TI128 *q3 = &local.v3;
        short backIdx = StepAlongPathTableEntry(moby, index, q3, *(short *)(vars + 0x118), -1, *(float *)(vars + 0x78) * 10.0f);
        float d;

        fast_vec_dist(pos, q2);
        fast_vec_dist(pos, q3);
        d = fast_vec_dist(&local.v0, q2);
        if (d < fast_vec_dist(&local.v0, q3)) {
            local.v1 = *q2;
            *(short *)(vars + 0x118) = forwardIdx;
        } else {
            local.v1 = *q3;
            *(short *)(vars + 0x118) = backIdx;
        }
    } else {
        local.v1 = local.v0;
    }
    {
        float distance = fast_vec_dist(moby + 0x10, &local.v0);
        return MoveMobyTowardPathPoint(moby, &local.v1, distance);
    }
}
