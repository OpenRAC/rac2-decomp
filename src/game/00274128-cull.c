#include "common.h"

/* Partial layouts shared with the point-index append operation. */
typedef struct {
    char pad000[0x10];
    float plane[4];
    char pad020[0x10];
    float (*points)[4];
    char pad034[0x25];
    unsigned char indices[3];
    unsigned char count;
} OozlaAppendDescriptor164;

typedef struct {
    char pad000[0x68];
    OozlaAppendDescriptor164 *descriptor;
    char pad06C[0x54];
    float transform[3][4];
} OozlaAppendObject164;

extern void func_00283098(float *, const float *, const float *);
extern void func_00282F20_16(void *, void *, float);
extern float func_00282DB0_3(void *, void *);
extern void func_00282CF0(float *, const float *, const float *);
extern void func_00282DD8(void *, void *, void *);

/* Project point differences perpendicular to direction, then prune the index set. */
void func_00274810(OozlaAppendObject164 *object, int index, const float *direction)
{
    float point[4], vectors[3][4], projection[4];
    float c0[4], c1[4], c2[4], c3[4];
    int i = 0;
    OozlaAppendDescriptor164 *p = object->descriptor;

    matrix_mul_vec3(point, p->points[p->indices[index]], object->transform[0]);
    func_00282F20_16(projection, (void *)direction,
                     func_00282DB0_3((void *)direction, point));
    FastVecSub(point, point, projection);
    for (; i < p->count; i++) {
        if (p->indices[i] == index) {
            qcopy(vectors[i], point);
        } else {
            FastVecSub(vectors[i], p->points[p->indices[i]],
                         p->points[p->indices[index]]);
            matrix_mul_vec3(vectors[i], vectors[i], object->transform[0]);
            func_00282F20_16(projection, (void *)direction,
                             func_00282DB0_3((void *)direction, vectors[i]));
            FastVecSub(vectors[i], vectors[i], projection);
            if (func_00282DB0_3(vectors[i], point) > 0.0f) {
                p->indices[i] = p->indices[p->count - 1];
                --p->count;
            }
        }
    }
    if (p->count == 3) {
        FastVecCross(c0, vectors[0], vectors[2]);
        FastVecCross(c1, vectors[1], vectors[2]);
        FastVecCross(c2, vectors[0], vectors[1]);
        FastVecCross(c3, vectors[1], vectors[0]);
        if (func_00282DB0_3(c0, c2) < 0.0f) {
            p->indices[1] = p->indices[2];
            --p->count;
        } else if (func_00282DB0_3(c1, c3) < 0.0f) {
            p->indices[0] = p->indices[2];
            --p->count;
        }
    }
}
