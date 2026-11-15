#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;

typedef struct { int a,b,c,d; } __attribute__((aligned(16))) Quad16;
/* Known 36-byte query fields; alignment supplies the measured 48-byte slot. */
typedef struct {
    Vector direction;
    int owner, queryMode;
    u8 first, second;
    u16 objectId;
    float distance;
    int enabled;
} CollisionQuery;
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecScale(void *, void *, float);
extern void make_hit_descriptor(char *, int, int, float, Quad16 *);
extern int CollLine(char *, char *, int, char *, void *);

/* Casts a collision line from start to end for an object, aimed along the way the object faces, and returns what it hit. */
int coll_cast_object_line(void *owner, void *start, void *end, s32 queryMode,
                     f32 distance, f32 scale, s32 first, s32 second, s32 mode) {
    char *object = owner;
    Vector direction;
    CollisionQuery query;
    if (*(u16 *)(object + 0x34) & 0x100) {
        qcopy(&direction, object + 0xC0);
    } else {
        direction.f[0] = math_fast_sin_or_cos_a(*(float *)(object + 0xF8));
        direction.f[1] = math_fast_sin_or_cos_b(*(float *)(object + 0xF8));
        direction.f[2] = 0.0f;
    }
    FastVecScale(&direction, &direction, scale);
    direction.f[2] = 1.0f;
    direction.f[3] = 5627.9248046875f;
    make_hit_descriptor((char *)&query, (int)object, queryMode, distance, (Quad16 *)&direction);
    query.first = first;
    query.second = second;
    query.objectId = *(u16 *)(object + 0xAA);
    return CollLine(start, end, mode | 9, object, &query);
}
