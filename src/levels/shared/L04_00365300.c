#include "common.h"

extern float func_00282E80(char *, char *);
extern float func_00282C10(float);

float func_L04_00365300(char *object, char *a1, char *a2) {
    float span = vec_distance_xy(object, a1);
    float area;

    if (span == 0.0f)
        return vec_distance_xy(object, a2);
    area = (*(float *)(a2 + 4) - *(float *)(object + 4)) * (*(float *)(a1 + 0) - *(float *)(object + 0)) -
           (*(float *)(a2 + 0) - *(float *)(object + 0)) * (*(float *)(a1 + 4) - *(float *)(object + 4));
    area *= area;
    area /= span * span;
    return square_root(area);
}
