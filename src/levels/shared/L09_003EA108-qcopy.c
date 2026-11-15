#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float fast_vec_dist(void *, void *);
extern void find_nearest_path_point(int, TI128 *, TI128 *, float, float, float, int *, float *, int);
extern short path_step_along_entry(char *, int, TI128 *, int, int, float);
extern int path_move_moby_turn_speed(char *, TI128 *, float);
extern int D_L09_001FE6C0[];

/* Finds the closest point on a level table path and steps the object toward the nearer neighbor along it. */
int path_steer_moby_to_nearest(char *moby, int index)
{
    char *vars = *(char **)(moby + 0x68);
    struct { TI128 v0, v1, v2, v3; int e; float f; } local;
    TI128 *pos = (TI128 *)(vars + 0x140);

    local.e = -1;
    find_nearest_path_point(D_L09_001FE6C0[index], pos, &local.v0, 100000.0f, 1.0f, local.f = 0.0f, &local.e, &local.f, 0);
    if (fast_vec_dist(&local.v0, (TI128 *)(moby + 0x10)) > 2.0f) {
        TI128 *q2 = &local.v2;
        short forward_idx = path_step_along_entry(moby, index, q2, *(short *)(vars + 0x118), 1, *(float *)(vars + 0x78) * 10.0f);
        TI128 *q3 = &local.v3;
        short back_idx = path_step_along_entry(moby, index, q3, *(short *)(vars + 0x118), -1, *(float *)(vars + 0x78) * 10.0f);
        float d;

        fast_vec_dist(pos, q2);
        fast_vec_dist(pos, q3);
        d = fast_vec_dist(&local.v0, q2);
        if (d < fast_vec_dist(&local.v0, q3)) {
            local.v1 = *q2;
            *(short *)(vars + 0x118) = forward_idx;
        } else {
            local.v1 = *q3;
            *(short *)(vars + 0x118) = back_idx;
        }
    } else {
        local.v1 = local.v0;
    }
    {
        float distance = fast_vec_dist(moby + 0x10, &local.v0);
        return path_move_moby_turn_speed(moby, &local.v1, distance);
    }
}
