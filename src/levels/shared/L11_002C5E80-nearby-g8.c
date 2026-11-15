#include "common.h"

/* Retail records have a measured 0x20 stride, with a point/radius prefix.
 * The last eight bytes exist but their fields are not used by this routine. */
typedef struct {
    float position[3];
    float radius;
    int *owner;
    int kind;
    unsigned char unknown18[8];
} Nearby_L11;

typedef int Vec128_L11 __attribute__((mode(TI)));
extern Nearby_L11 *D_L11_001B2DC0;
extern int D_L11_001B2DC4;
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern float func_00282C48(float);
extern int func_L00_00341FA8(void *, void *, void *, int *, float *, int, float, float, float);

/* Finds the first record, optionally excluding or requiring one owner, whose radius holds the
 * point and whose contact probe lands close to it; reports that contact. */
int func_L11_002C5E80(void *position, int **owner, float *target, int *contact, float *height, int *kind, int *excluded, int *required)
{
    float local[4] __attribute__((aligned(16)));
    float *here;
    int hit;
    float distance;
    int i;

    *(Vec128_L11 *)local = *(Vec128_L11 *)position;
    here = local;
    for (i = 0; i < D_L11_001B2DC4; i++) {
        if (excluded && D_L11_001B2DC0[i].owner == excluded) continue;
        if (required && D_L11_001B2DC0[i].owner != required) continue;
        if (!*D_L11_001B2DC0[i].owner) continue;
        if (fast_vec_dist(&D_L11_001B2DC0[i], here) > D_L11_001B2DC0[i].radius) continue;
        if (find_nearest_path_point(D_L11_001B2DC0[i].owner, here, target, &hit, &distance, D_L11_001B2DC0[i].kind, 12.0f, 10.0f, 0.0f)) {
            if (vec_distance_xy(here, target) < 1.7f && func_00282C48(here[2] - target[2]) < 1.5f) {
                *owner = D_L11_001B2DC0[i].owner;
                *contact = hit;
                *height = distance;
                *kind = D_L11_001B2DC0[i].kind;
                return 1;
            }
        }
    }
    return 0;
}
