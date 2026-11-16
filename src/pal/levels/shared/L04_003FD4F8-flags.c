#include "include_asm.h"

#include "common.h"
extern void FastVecScale(void *, const void *, float);
extern void FastVecAdd(void *, const void *, const void *);
extern void FastVecSub(void *, const void *, const void *);
extern void FastVecCross(void *, const void *, const void *);
extern float FastVecLength(const void *);
extern int CollLine(const void *, const void *, int, void *, const void *);
extern float FastAddRotations(float, float), fast_subtract_rotations(float, float);
extern unsigned char g_spark_origin_quad[];
typedef struct {
    float point[4];
    char gap[0x10];
    float normal[4];
} CollisionSteeringHit;

void func_PAL_L04_003FE558(char *object, float *heading, float *pitch)
{
    float probe[4] __attribute__((aligned(16)));
    float vector[4] __attribute__((aligned(16)));
    CollisionSteeringHit *hit;
    float distance, weight;
    qcopy(vector, object + 0xc0);
    FastVecScale(probe, vector, 17.0f);
    FastVecAdd(probe, probe, object + 0x10);
    if (CollLine(object + 0x10, probe, 0, object, 0)) {
        hit = (CollisionSteeringHit *)g_spark_origin_quad;
        FastVecSub(vector, object + 0x10, hit->point);
        distance = FastVecLength(vector);
        FastVecCross(probe, vector, hit->normal);
        weight = (distance - 2.0f) * 0.06666667014360428f;
        if (weight < 0.0f) weight = 0.0f;
        if (probe[2] > 0.0f) *heading = FastAddRotations(*heading, (1.0f - weight) * 0.04537857f);
        else *heading = fast_subtract_rotations(*heading, (1.0f - weight) * 0.04537857f);
    }
    FastVecScale(vector, object + 0xe0, -3.0f);
    FastVecAdd(probe, vector, object + 0x10);
    if (CollLine(object + 0x10, probe, 0, object, 0)) {
        FastVecSub(vector, object + 0x10, g_spark_origin_quad);
        distance = FastVecLength(vector);
        if (distance <= 1.0f) {
            if (*pitch > 0.0f) *pitch = 0.0f;
            *pitch = (1.0f - distance) * -1.5707963705062866f;
        } else {
            weight = distance - 1.0f;
            weight *= 0.5f;
            *pitch = weight * 0.3f;
        }
    } else *pitch = 0.3f;
}
