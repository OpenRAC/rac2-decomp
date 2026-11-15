#include "common.h"

extern float func_00283CE0(int);
extern float func_002A7940(void);
extern void func_002ACB48(void *, float);
extern void func_00281EB8(void *, int, int, int, float, float, float);
extern int D_L05_001B0FBC __attribute__((sda));
extern void func_00282CC0(void *, void *, void *);

typedef int TI128 __attribute__((mode(TI)));

/* Places a row of sprites along a direction, changing size from the first one to the last. */
void func_L05_00418D68(void *position, void *direction, int count, int color, float sizeStart, float sizeEnd, float pushOut)
{
    TI128 points[2];
    float step;
    float progress;
    float spin;
    float scale;
    float lastSize;
    float firstSize;
    float pushDistance;
    int i;

    firstSize = sizeStart;
    lastSize = sizeEnd;
    pushDistance = pushOut;
    qcopy(&points[0], position);
    step = 1.0f / IntToFloat(count);
    for (i = 0; i < count; i++) {
        progress = IntToFloat(i) * step;
        scale = firstSize + (lastSize - firstSize) * progress;
        spin = RandomAngle();
        qcopy(&points[1], &points[0]);
        AddRandomOffsetToVector(&points[1], pushDistance);
        DrawBillboardQuad_00281EB8(&points[1], D_L05_001B0FBC, color, 1, scale, 0.0f, spin);
        FastVecAdd(&points[0], &points[0], direction);
    }
}
