#include "common.h"

extern char *g_path_table[];
extern void FastVecSub(float *, float *, float *);
extern void FastVecAdd(float *, float *, float *);
extern void vec_scale_to_length(float *, float *, float);
extern void FastVecCross(float *, float *, float *);
extern float math_fabs(float);
extern float FastVecLength(float *);
extern float FastVecDot(float *, float *);
typedef struct {
    float x, y, z, active;
} PathPoint_2C9218;
typedef struct {
    int count;
    char pad04[12];
    PathPoint_2C9218 points[1];
} Path_2C9218;

/* Pushes a point away from the walls of a path so it stays at least radius away. Returns 1 if the point was moved. */
int path_push_point_away(int index, float *point, float *out, float radius)
{
    float delta[4], adjustment[4], position[4], edge[4], unit[4], cross[4], projection[4];
    int found = 0, i, offset, next;
    float length, dot;
    qcopy_nc(position, point);
    for (i = 0; i < *(int *)g_path_table[index] - 1; i++) {
        offset = i * 16 + 16;
        next = i * 16 + 32;
        if (((Path_2C9218 *)g_path_table[index])->points[i].active == 0) continue;
        FastVecSub(delta, position, (float *)(g_path_table[index] + offset));
        delta[2] = 0;
        FastVecSub(edge, (float *)(g_path_table[index] + next), (float *)(g_path_table[index] + offset));
        edge[2] = 0;
        vec_scale_to_length(unit, edge, 1.0f);
        FastVecCross(cross, delta, unit);
        if (radius < math_fabs(cross[2])) continue;
        length = FastVecLength(edge);
        dot = FastVecDot(delta, unit);
        if (length < dot || dot < 0) {
            if (FastVecLength(delta) < radius) {
                vec_scale_to_length(adjustment, delta, radius);
                found = 1;
                FastVecAdd(position, adjustment, (float *)(g_path_table[index] + offset));
                position[2] = point[2];
            }
        } else {
            vec_scale_to_length(projection, unit, dot);
            found = 1;
            FastVecSub(adjustment, delta, projection);
            vec_scale_to_length(adjustment, adjustment, radius);
            FastVecAdd(adjustment, adjustment, projection);
            FastVecAdd(position, adjustment, (float *)(g_path_table[index] + offset));
            position[2] = point[2];
        }
    }
    if (found) qcopy(out, position);
    return found;
}
