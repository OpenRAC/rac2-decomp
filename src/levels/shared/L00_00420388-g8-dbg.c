/* func_L00_00420388 in its own unit (flags in config/cflags.txt: -O2 -G8 -ffunction-sections -g). */

#include "include_asm.h"
#include "names.h"
typedef int Quad __attribute__((mode(TI)));
extern char *func_L00_002DB350(Quad *, float);
extern char *D_L00_001B1F94;
extern char D_L00_001BF230[];
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
/* Checks whether a point is close to a level collision shape and, if so, records two points on the line from its center. */
int func_L00_00420388(Quad *src, float margin)
{
    struct { Quad local; float delta[4]; } temp;
    char *hit;
    char *record;
    char *center;
    char *outer;
    char *inner;
    float radius;
    float reciprocal;
    temp.local = *src;
    hit = FindIntersectingGridPrimitive(&temp.local, margin);
    if (hit) {
        record = D_L00_001B1F94;
        record += *(int *)(hit + 0x14) * 0x80;
        center = record + 0x30;
        FastVecSub(temp.delta, src, center);
        radius = FastVecLength(record);
        reciprocal = 1.0f / FastVecLength(temp.delta);
        outer = D_L00_001BF230;
        inner = outer - 0x10;
        FastVecScale(outer, temp.delta, (radius + margin) * reciprocal);
        FastVecScale(inner, temp.delta, radius * reciprocal);
        FastVecAdd(outer, outer, center);
        FastVecAdd(inner, inner, center);
        return 1;
    }
    return 0;
}
