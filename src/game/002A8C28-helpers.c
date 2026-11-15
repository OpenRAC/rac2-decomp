#include "include_asm.h"
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
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282D30(void *, void *, float);
extern void func_002A8C00(char *, int, int, float, Quad16 *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
/* The radius is loaded after the first pointer: it sits second in the parameter list. */
extern int func_00277F48(void *, float, int, char *, void *);

/* The func_L01_003120A8 query with the facing taken from the object's frame (its +0xE0 row
   at a quarter, from its position) and a sweep through func_00277F48. */
int func_002A8C28(void *owner, void *start, s32 queryMode, s32 first, s32 second, s32 mode,
                  f32 radius, f32 distance, f32 scale) {
    char *object = owner;
    Vector direction;
    CollisionQuery query;
    if (*(u16 *)(object + 0x34) & 0x100) {
        vec_scale_to_length(&direction, object + 0xE0, 0.25f);
        FastVecAdd(&direction, &direction, object + 0xC0);
    } else {
        direction.f[0] = FastSinOrCosA(*(float *)(object + 0xF8));
        direction.f[1] = FastSinOrCosB(*(float *)(object + 0xF8));
        direction.f[2] = 1.0f;
    }
    FastVecScale(&direction, &direction, scale);
    direction.f[3] = 5627.9248046875f;
    make_hit_descriptor((char *)&query, (int)object, queryMode, distance, (Quad16 *)&direction);
    query.first = first;
    query.second = second;
    query.objectId = *(u16 *)(object + 0xAA);
    return ProcessCollisionHit(start, radius, mode, object, &query);
}
