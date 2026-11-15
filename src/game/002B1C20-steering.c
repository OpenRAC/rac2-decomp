#include "common.h"

extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283248(float, float);
extern int func_00277F48(void *, int, void *, int, float);
extern int func_002ABB78(void *);
extern float func_00283C80(float, float);
extern float func_00282E20(void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern char *D_001BF000[];

/* Bends a direction away from or toward nearby objects in front, using the middle heading of those found; returns 1 if any were found. */
int func_002B1CC8(char *object, float *direction, void *inDirection, float radius, float tolerance)
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
    wantedHeading = FastMatrixHelperA(forward[0], forward[1]);
    found = ProcessCollisionHit(probePos, 0, object, 0, radius);
    if (found) {
        kept = 0;
        for (i = 0; i < found && i < 16; i++) {
            if (IsMobyInSpecialClassRange(D_001BF000[i]) ||
                (*(char **)(D_001BF000[i] + 0x24) &&
                 *(short *)(*(char **)(D_001BF000[i] + 0x24) + 0x46) == 22)) {
                radius = FastMatrixHelperA(
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
            direction[0] = FastSinOrCosA(medianHeading) * length;
            direction[1] = FastSinOrCosB(medianHeading) * length;
        }
        return 1;
    }
    return 0;
}
