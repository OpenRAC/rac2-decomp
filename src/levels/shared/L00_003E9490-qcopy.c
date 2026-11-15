#include "names.h"
typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;

extern void func_00282CF0(char *local, char *first, char *second);
extern void func_00282D30(char *a, char *b, float value);
extern void func_00282CC0(char *target, char *first, char *local);

/* Finds the point part-way between two points, at the given amount from 0 to 1. */
void func_L00_003E9490(float t, Vec16_Fc936841d *result, Vec16_Fc936841d *from, Vec16_Fc936841d *to)
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
