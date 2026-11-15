#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vec4;
extern void matrix_mul_vec3(float *, const float *, const float *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(float *, const float *, const float *);
extern int coll_test_point(void *position, int flags, char *self, float radius);
typedef struct {
    char pad[0x18];
    char *hit;
    int count;
    Vec4 point;
    char gap[0x10];
    Vec4 normal;
} Collision;
extern Collision D_L02_001C0940;

/* Tests a sphere around an object against the level. On a hit it records what was hit, the hit point and pushes the object out. Returns 1 for a hit, 0 for none. */
int coll_check_sphere_hit(char *object, char *record) {
    int result;
    Vec4 position;
    Vec4 offset;
    Vec4 initial;
    char *origin = object + 0x10;
    initial.q = 0;
    initial.f[2] = *(float *)(record + 4) + *(float *)record;
    offset.q = initial.q;
    matrix_mul_vec3((float *)&offset, (float *)&offset, (float *)(object + 0xC0));
    FastVecAdd(&position, origin, &offset);
    if (!coll_test_point(&position, *(int *)(record + 0x38) & 2, object, *(float *)record)) {
        result = 0;
        goto done;
    }
    *(char **)(record + 0x84) = D_L02_001C0940.hit;
    qcopy(record + 0x60, &D_L02_001C0940.point);
    qcopy(&position, D_L02_001C0940.gap);
    FastVecSub((float *)origin, (float *)&position, (float *)&offset);
    result = 1;
done:
    return result;
}
