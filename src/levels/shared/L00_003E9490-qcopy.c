#include "names.h"
typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;

extern void FastVecSub(char *local, char *first, char *second);
extern void FastVecScale(char *a, char *b, float value);
extern void FastVecAdd(char *target, char *first, char *local);

/* Finds the point part-way between two points, at the given amount from 0 to 1. */
void vec_interpolate(float t, Vec16_Fc936841d *result, Vec16_Fc936841d *from, Vec16_Fc936841d *to)
{
    Vec16_Fc936841d offset;

    if (t == 0.0f) {
        *(TI128 *)result = *(TI128 *)from;
    } else if (t == 1.0f) {
        *(TI128 *)result = *(TI128 *)to;
    } else {
        FastVecSub((char *)&offset, (char *)to, (char *)from);
        FastVecScale((char *)&offset, (char *)&offset, t);
        FastVecAdd((char *)result, (char *)from, (char *)&offset);
    }
}
