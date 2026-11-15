#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vec4;
extern void func_00283098(float *, const float *, const float *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(float *, const float *, const float *);
extern int func_00277258(void *position, int flags, char *self, float radius);
typedef struct {
    char pad[0x18];
    char *hit;
    int count;
    Vec4 point;
    char gap[0x10];
    Vec4 normal;
} Collision;
extern Collision D_L13_001BFD00;

/* Tests whether a creature would hit something and, if so, moves it to the contact point. */
int func_L13_0040A2C8(char *object, char *record) {
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
    if (!TestPointAgainstCollision(&position, *(int *)(record + 0x38) & 2, object, *(float *)record)) {
        result = 0;
        goto done;
    }
    *(char **)(record + 0x84) = D_L13_001BFD00.hit;
    qcopy(record + 0x60, &D_L13_001BFD00.point);
    qcopy(&position, D_L13_001BFD00.gap);
    FastVecSub((float *)origin, (float *)&position, (float *)&offset);
    result = 1;
done:
    return result;
}
