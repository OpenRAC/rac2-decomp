#include "common.h"

typedef int Quad __attribute__((mode(TI)));
extern int func_00283CF0(float);
extern void func_0026FEB8(const char *,...);
extern void func_00282CF0(float *,float *,float *);
extern float func_00282E20(float *);
extern int func_L00_002DB4B8(float *,float *,float);
extern char D_L00_001A8988[];
typedef struct CollisionPrimitive {
    float position[3], radius;
    char rest[32];
} CollisionPrimitive;

typedef struct CollisionCell {
    int count;
    int pad[3];
    CollisionPrimitive primitives[0];
} CollisionCell;

/* The grid base pointer uses the measured absolute macro-address form. */
extern char *D_L00_001B1880[] __attribute__((sda));

/* Returns the first cell primitive intersecting the position and radius. */
/* Looks up the collision grid cell at a position and returns the first shape that touches it. */
float *func_L00_002DB350(float radius, Quad *position)
{
    union { Quad q; float f[4]; } origin;
    float delta[4];
    int x, y;
    float *point = origin.f;
    origin.q = *position;
    x = FloatToInt(point[0] * 0.0625f);
    y = FloatToInt(point[1] * 0.0625f);
    if (x < 0 || y < 0 || x > 64 || y > 64) {
        STUB_printf(D_L00_001A8988);
    } else {
        int cell = ((int *)D_L00_001B1880[0])[y * 64 + x];
        int i;
        if (!cell)
            return 0;
        cell += (int)D_L00_001B1880[0];
        for (i = 0; i < ((CollisionCell *)cell)->count; i++) {
            CollisionPrimitive *primitive = &((CollisionCell *)cell)->primitives[i];
            float limit;
            FastVecSub(delta, primitive->position, point);
            limit = primitive->radius;
            delta[3] = 1.0f;
            if (vec_length_xy(delta) < limit + radius &&
                IsPointInCollisionPrimitive(point, primitive->position, radius))
                return primitive->position;
        }
    }
    return 0;
}
