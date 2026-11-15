#include "names.h"
extern float IntToFloat(int);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int CollLine(void *, void *, void *, void *, void *);

typedef struct {
    float x, y, z, w;
} V4;

/* Moves two points along two paths in small steps and checks each pair of positions for a hit. Returns 1 as soon as one is found. */
int coll_sweep_segment_for_hit(char *startA, char *startB, char *endA, char *endB, void *hitInfoA, void *hitInfoB, int stepCount)
{
    V4 deltaA, deltaB, pointA, pointB;
    float ratio;
    float ratioStep;
    int i = 0;

    ratioStep = 1.0f / IntToFloat(stepCount);
    FastVecSub(&deltaA, startA, endA);
    FastVecSub(&deltaB, startB, endB);
    ratio = ratioStep;
    while (i < stepCount) {
        FastVecScale(&pointA, &deltaA, ratio);
        FastVecScale(&pointB, &deltaB, ratio);
        FastVecAdd(&pointA, &pointA, endA);
        FastVecAdd(&pointB, &pointB, endB);
        if (CollLine(&pointA, &pointB, 0, hitInfoA, hitInfoB) != 0)
            return 1;
        i++;
        ratio += ratioStep;
    }
    return 0;
}
