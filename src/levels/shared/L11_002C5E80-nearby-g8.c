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
extern Nearby_L11 *g_nearby_entries;
extern int g_nearby_entry_count;
extern float fast_vec_dist(void *, void *);
extern float vec_distance_xy(void *, void *);
extern float math_fabs(float);
extern int find_nearest_path_point(void *, void *, void *, int *, float *, int, float, float, float);

/* Finds the first record, optionally excluding or requiring one owner, whose radius holds the
 * point and whose contact probe lands close to it; reports that contact. */
int FindNearbyRecordContact(void *position, int **owner, float *target, int *contact, float *height, int *kind, int *excluded, int *required)
{
    float local[4] __attribute__((aligned(16)));
    float *here;
    int hit;
    float distance;
    int i;

    *(Vec128_L11 *)local = *(Vec128_L11 *)position;
    here = local;
    for (i = 0; i < g_nearby_entry_count; i++) {
        if (excluded && g_nearby_entries[i].owner == excluded) continue;
        if (required && g_nearby_entries[i].owner != required) continue;
        if (!*g_nearby_entries[i].owner) continue;
        if (fast_vec_dist(&g_nearby_entries[i], here) > g_nearby_entries[i].radius) continue;
        if (find_nearest_path_point(g_nearby_entries[i].owner, here, target, &hit, &distance, g_nearby_entries[i].kind, 12.0f, 10.0f, 0.0f)) {
            if (vec_distance_xy(here, target) < 1.7f && math_fabs(here[2] - target[2]) < 1.5f) {
                *owner = g_nearby_entries[i].owner;
                *contact = hit;
                *height = distance;
                *kind = g_nearby_entries[i].kind;
                return 1;
            }
        }
    }
    return 0;
}
