#include "common.h"

extern float func_00282E80(char *, char *);
extern float func_00282C10(float);

/* Works out how far a point is from a line between two other points. */
float func_L04_00365300(char *object, char *a1, char *a2) {
    float baseLen = vec_distance_xy(object, a1);
    float cross;

    if (baseLen == 0.0f)
        return vec_distance_xy(object, a2);
    cross = (*(float *)(a2 + 4) - *(float *)(object + 4)) * (*(float *)(a1 + 0) - *(float *)(object + 0)) -
           (*(float *)(a2 + 0) - *(float *)(object + 0)) * (*(float *)(a1 + 4) - *(float *)(object + 4));
    cross *= cross;
    cross /= baseLen * baseLen;
    return square_root(cross);
}
