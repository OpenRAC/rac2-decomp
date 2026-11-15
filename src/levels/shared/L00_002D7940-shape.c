#include "common.h"

typedef int Quad __attribute__((mode(TI)));

typedef union {
    Quad q;
    float f[4];
} Vec;

/* The grid's primitive (func_L00_002DB350): its centre, then which shape it is. */
typedef struct {
    float position[3], radius;
    int type, index;
    char rest[24];
} CollisionPrimitive;

/* A placed cuboid, sphere or cylinder: a transform, its position and its inverse. */
typedef struct {
    float matrix[12];
    float position[4];
    float inverse[16];
} CollisionShape;

typedef struct {
    float matrix[12];
    float position[4];
    float inverse[16];
    float radius;
    char pad[12];
} CollisionPill;

extern CollisionShape *D_L00_001B1F8C __attribute__((sda));
extern CollisionShape *D_L00_001B1F94 __attribute__((sda));
extern CollisionShape *D_L00_001B1F9C __attribute__((sda));
extern CollisionPill *D_L00_001B1F84 __attribute__((sda));

extern void func_00282CC0(float *, float *, float *);
extern void func_00282CF0(float *, float *, float *);
extern void func_00283098(float *, float *, float *);
extern float func_00282DF0(float *);
extern float func_00282E20(float *);
extern float func_00282E48(float *, float *);

/* Is the position inside the primitive's shape, the radius widening a sphere? Each shape is
   tested in its own space: a cuboid against the unit cube, a cylinder against the unit
   cylinder, and a pill against its cylinder and then the sphere at either end. */
/* Tells whether a point is inside a collision shape. */
int func_L00_002DB4B8(Quad *position, CollisionPrimitive *primitive, float radius)
{
    Vec origin, axis, local, transformed;
    float *point = origin.f;

    origin.q = *position;
    switch (primitive->type) {
    case 3: {
        CollisionShape *cuboid = D_L00_001B1F8C + primitive->index;

        FastVecSub(local.f, point, cuboid->position);
        local.f[3] = 0.0f;
        matrix_mul_vec3(transformed.f, local.f, cuboid->inverse);
        return -1.0f <= transformed.f[0] && transformed.f[0] <= 1.0f
            && -1.0f <= transformed.f[1] && transformed.f[1] <= 1.0f
            && -1.0f <= transformed.f[2] && transformed.f[2] <= 1.0f;
    }
    case 6: {
        CollisionShape *cylinder = D_L00_001B1F9C + primitive->index;
        int inside = 0;

        FastVecSub(local.f, point, cylinder->position);
        local.f[3] = 0.0f;
        matrix_mul_vec3(transformed.f, local.f, cylinder->inverse);
        if (vec_length_xy(transformed.f) < 1.0f && -1.0f <= transformed.f[2] && transformed.f[2] <= 1.0f)
            inside = 1;
        return inside;
    }
    case 5: {
        CollisionShape *sphere = D_L00_001B1F94 + primitive->index;
        float limit = FastVecLength(sphere->matrix) + radius;

        return fast_vec_dist(point, sphere->position) < limit;
    }
    case 7: {
        CollisionPill *pill = D_L00_001B1F84 + primitive->index;

        FastVecSub(local.f, point, pill->position);
        local.f[3] = 0.0f;
        matrix_mul_vec3(transformed.f, local.f, pill->inverse);
        if (vec_length_xy(transformed.f) < 1.0f && -1.0f <= transformed.f[2] && transformed.f[2] <= 1.0f)
            return 1;
        axis.f[0] = 0.0f;
        axis.f[1] = 0.0f;
        axis.f[2] = 1.0f;
        axis.f[3] = 1.0f;
        matrix_mul_vec3(transformed.f, axis.f, pill->matrix);
        FastVecAdd(transformed.f, transformed.f, pill->position);
        FastVecSub(axis.f, point, transformed.f);
        if (FastVecLength(axis.f) < pill->radius)
            return 1;
        axis.f[0] = 0.0f;
        axis.f[1] = 0.0f;
        axis.f[2] = -1.0f;
        axis.f[3] = 1.0f;
        matrix_mul_vec3(transformed.f, axis.f, pill->matrix);
        FastVecAdd(transformed.f, transformed.f, pill->position);
        FastVecSub(axis.f, point, transformed.f);
        if (FastVecLength(axis.f) < pill->radius)
            return 1;
        return 0;
    }
    }
    return 0;
}
