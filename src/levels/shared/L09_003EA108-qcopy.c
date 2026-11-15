#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float func_00282E48(void *, void *);
extern void func_L00_00341FA8(int, TI128 *, TI128 *, float, float, float, int *, float *, int);
extern short func_L09_0033E8B0(char *, int, TI128 *, int, int, float);
extern int func_L09_003E9E60(char *, TI128 *, float);
extern int D_L09_001FE6C0[];

int func_L09_003EA108(char *arg0, int arg1)
{
    char *st = *(char **)(arg0 + 0x68);
    struct { TI128 v0, v1, v2, v3; int e; float f; } local;
    TI128 *pos = (TI128 *)(st + 0x140);

    local.e = -1;
    find_nearest_path_point(D_L09_001FE6C0[arg1], pos, &local.v0, 100000.0f, 1.0f, local.f = 0.0f, &local.e, &local.f, 0);
    if (fast_vec_dist(&local.v0, (TI128 *)(arg0 + 0x10)) > 2.0f) {
        TI128 *q2 = &local.v2;
        short a = func_L09_0033E8B0(arg0, arg1, q2, *(short *)(st + 0x118), 1, *(float *)(st + 0x78) * 10.0f);
        TI128 *q3 = &local.v3;
        short b = func_L09_0033E8B0(arg0, arg1, q3, *(short *)(st + 0x118), -1, *(float *)(st + 0x78) * 10.0f);
        float d;

        fast_vec_dist(pos, q2);
        fast_vec_dist(pos, q3);
        d = fast_vec_dist(&local.v0, q2);
        if (d < fast_vec_dist(&local.v0, q3)) {
            local.v1 = *q2;
            *(short *)(st + 0x118) = a;
        } else {
            local.v1 = *q3;
            *(short *)(st + 0x118) = b;
        }
    } else {
        local.v1 = local.v0;
    }
    {
        float distance = fast_vec_dist(arg0 + 0x10, &local.v0);
        return func_L09_003E9E60(arg0, &local.v1, distance);
    }
}
