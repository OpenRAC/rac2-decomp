#include "common.h"
extern void func_00282D30(void *, const void *, float);
extern void func_00282CC0(void *, const void *, const void *);
extern void func_00282CF0(void *, const void *, const void *);
extern void func_00282DD8(void *, const void *, const void *);
extern float func_00282DF0(const void *);
/* Optional final argument is a 40-byte hit packet; both probes pass null. */
extern int func_002761F8(const void *, const void *, int, void *, const void *);
extern float func_00283B98(float, float), func_00283BE0(float, float);
extern unsigned char D_L04_001BFAE0[];

typedef struct {
    float point[4];
    char gap[0x10];
    float normal[4];
} CollisionSteeringHit;

void func_L04_003FA350(char *object, float *heading, float *pitch)
{
    float probe[4] __attribute__((aligned(16)));
    float vector[4] __attribute__((aligned(16)));
    CollisionSteeringHit *hit;
    float distance, weight;
    qcopy(vector, object + 0xc0);
    func_00282D30(probe, vector, 17.0f);
    func_00282CC0(probe, probe, object + 0x10);
    if (func_002761F8(object + 0x10, probe, 0, object, 0)) {
        hit = (CollisionSteeringHit *)D_L04_001BFAE0;
        func_00282CF0(vector, object + 0x10, hit->point);
        distance = func_00282DF0(vector);
        func_00282DD8(probe, vector, hit->normal);
        weight = (distance - 2.0f) * 0.06666667014360428f;
        if (weight < 0.0f) weight = 0.0f;
        if (probe[2] > 0.0f) *heading = func_00283B98(*heading, (1.0f - weight) * 0.03781547397375107f);
        else *heading = func_00283BE0(*heading, (1.0f - weight) * 0.03781547397375107f);
    }
    func_00282D30(vector, object + 0xe0, -3.0f);
    func_00282CC0(probe, vector, object + 0x10);
    if (func_002761F8(object + 0x10, probe, 0, object, 0)) {
        func_00282CF0(vector, object + 0x10, D_L04_001BFAE0);
        distance = func_00282DF0(vector);
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
