#include "common.h"

extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float mat_fast_helper_a(float, float);
extern int coll_process_hit(void *, int, void *, int, float);
extern int moby_is_in_special_class_range(void *);
extern float FastDiffRots(float, float);
extern float vec_length_xy(void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern char *D_001BF000[];

/* Bends a direction away from or toward nearby objects in front, using the middle heading of those found; returns 1 if any were found. */
int moby_steer_toward_nearby(char *object, float *direction, void *inDirection, float radius, float tolerance)
{
    float forward[4] __attribute__((aligned(16)));
    float probePos[4] __attribute__((aligned(16)));
    float headings[16];
    float medianHeading, wantedHeading, length;
    int found, kept, i, k2;

    qcopy(direction, inDirection);
    qcopy(forward, inDirection);
    forward[2] = 0;
    vec_scale_to_length(forward, forward, radius);
    FastVecAdd(probePos, object + 0x10, forward);
    wantedHeading = mat_fast_helper_a(forward[0], forward[1]);
    found = coll_process_hit(probePos, 0, object, 0, radius);
    if (found) {
        kept = 0;
        for (i = 0; i < found && i < 16; i++) {
            if (moby_is_in_special_class_range(D_001BF000[i]) ||
                (*(char **)(D_001BF000[i] + 0x24) &&
                 *(short *)(*(char **)(D_001BF000[i] + 0x24) + 0x46) == 22)) {
                radius = mat_fast_helper_a(
                    *(float *)(D_001BF000[i] + 0x10) - *(float *)(object + 0x10),
                    *(float *)(D_001BF000[i] + 0x14) - *(float *)(object + 0x14));
                if (FastDiffRots(wantedHeading, radius) < tolerance)
                    headings[kept++] = radius;
            }
        }
        if (kept) {
            int k;
            for (k = 0; k < kept - 1; k++) {
                int next = k;
                next++;
                for (k2 = 0; k2 < kept - next; k2++) {
                    if (headings[k2 + 1] < headings[k2]) {
                        float swap = headings[k2];
                        headings[k2] = headings[k2 + 1];
                        headings[k2 + 1] = swap;
                    }
                }
            }
            medianHeading = headings[kept >> 1];
            length = vec_length_xy(direction);
            direction[0] = math_fast_sin_or_cos_a(medianHeading) * length;
            direction[1] = math_fast_sin_or_cos_b(medianHeading) * length;
        }
        return 1;
    }
    return 0;
}
