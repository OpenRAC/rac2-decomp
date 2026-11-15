#include "include_asm.h"
#include "names.h"

typedef int s32;
typedef float f32;
typedef unsigned char u8;

/* The 128-bit unit the group copy needs. */
typedef int V4TI __attribute__((mode(TI)));

extern float *func_002AB1F0(char *);

extern void func_00282D30(void *, void *, f32);

extern void func_00282CC0(void *, void *, void *);

extern void func_00282CF0(void *, void *, void *);

extern void func_00282F20(void *, void *, f32);

/* Fetches the record the caller names, then either builds a vector from the
   object's own fields or copies the object's second vector, and hands the
   result to the transform and the closing helper. */
/* Works out the vector from a point on the object to a target, scaled by a factor. */
void func_L00_0032A1A8(char *object, char *target, char *result, f32 scale)
{
    char buf[32];
    float *record;

    record = GetMobyPrivateValue0(object);
    if (record != 0) {
        FastVecScale(buf + 0x10, object + 0xE0, *(f32 *)((char *)record + 0x10));
        FastVecAdd(buf, object + 0x10, buf + 0x10);
    } else {
        *(V4TI *)buf = *(V4TI *)(object + 0x10);
    }
    FastVecSub(result, buf, target);
    vec_scale_to_length(result, result, scale);
}
