#include "common.h"

extern char *D_001F1700[];
extern void func_00282CF0(float *, float *, float *);
extern void func_00282CC0(float *, float *, float *);
extern void func_00282F20(float *, float *, float);
extern void func_00282DD8(float *, float *, float *);
extern float func_00282C48(float);
extern float func_00282DF0(float *);
extern float func_00282DB0(float *, float *);
typedef struct {
    float x, y, z, active;
} PathPoint_2C9218;
typedef struct {
    int count;
    char pad04[12];
    PathPoint_2C9218 points[1];
} Path_2C9218;

int func_002C9218(int index, float *point, float *out, float radius)
{
    float delta[4], adjustment[4], position[4], edge[4], unit[4], cross[4], projection[4];
    int found = 0, i, offset, next;
    float length, dot;
    qcopy_nc(position, point);
    for (i = 0; i < *(int *)D_001F1700[index] - 1; i++) {
        offset = i * 16 + 16;
        next = i * 16 + 32;
        if (((Path_2C9218 *)D_001F1700[index])->points[i].active == 0) continue;
        FastVecSub(delta, position, (float *)(D_001F1700[index] + offset));
        delta[2] = 0;
        FastVecSub(edge, (float *)(D_001F1700[index] + next), (float *)(D_001F1700[index] + offset));
        edge[2] = 0;
        vec_scale_to_length(unit, edge, 1.0f);
        FastVecCross(cross, delta, unit);
        if (radius < func_00282C48(cross[2])) continue;
        length = FastVecLength(edge);
        dot = FastVecDot(delta, unit);
        if (length < dot || dot < 0) {
            if (FastVecLength(delta) < radius) {
                vec_scale_to_length(adjustment, delta, radius);
                found = 1;
                FastVecAdd(position, adjustment, (float *)(D_001F1700[index] + offset));
                position[2] = point[2];
            }
        } else {
            vec_scale_to_length(projection, unit, dot);
            found = 1;
            FastVecSub(adjustment, delta, projection);
            vec_scale_to_length(adjustment, adjustment, radius);
            FastVecAdd(adjustment, adjustment, projection);
            FastVecAdd(position, adjustment, (float *)(D_001F1700[index] + offset));
            position[2] = point[2];
        }
    }
    if (found) qcopy(out, position);
    return found;
}
