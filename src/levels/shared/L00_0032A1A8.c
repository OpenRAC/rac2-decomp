#include "include_asm.h"
#include "names.h"

typedef int s32;
typedef float f32;
typedef unsigned char u8;

/* The 128-bit unit the group copy needs. */
typedef int V4TI __attribute__((mode(TI)));

extern float *moby_get_private_value_0(char *);

extern void FastVecScale(void *, void *, f32);

extern void FastVecAdd(void *, void *, void *);

extern void FastVecSub(void *, void *, void *);

extern void vec_scale_to_length(void *, void *, f32);

/* Fetches the record the caller names, then either builds a vector from the
   object's own fields or copies the object's second vector, and hands the
   result to the transform and the closing helper. */
/* Works out the vector from a point on the object to a target, scaled by a factor. */
void vec_compute_object_to_target(char *object, char *target, char *result, f32 scale)
{
    char buf[32];
    float *record;

    record = moby_get_private_value_0(object);
    if (record != 0) {
        FastVecScale(buf + 0x10, object + 0xE0, *(f32 *)((char *)record + 0x10));
        FastVecAdd(buf, object + 0x10, buf + 0x10);
    } else {
        *(V4TI *)buf = *(V4TI *)(object + 0x10);
    }
    FastVecSub(result, buf, target);
    vec_scale_to_length(result, result, scale);
}
