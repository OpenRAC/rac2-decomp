#include "common.h"

typedef int Vector __attribute__((mode(TI)));
extern int D_L02_001B0344 __attribute__((sda));
extern float D_L02_001B0338 __attribute__((sda));
extern float D_L02_001B033C __attribute__((sda));
extern float D_L02_001B0340 __attribute__((sda));
extern float D_L02_001B0350 __attribute__((sda));
extern float D_L02_001B0354;
extern float D_L02_001B0358;
extern float D_L02_001B0360 __attribute__((sda));
extern float D_L02_001B0364;
extern float D_L02_001B0368;
extern Vector D_L02_00241290[];
extern Vector D_L02_002415B0[];
extern void func_0029FCC0(char *, int, char *);
extern void func_0029FC20(char *, int, char *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282E48(void *, void *);
extern float func_002AA548(void *, void *, float, float, float, float);
extern float func_00282C48(float);

/* Only table-row stores use the non-clobbering copy: the surrounding scalar
 * accesses and live stack vectors occupy distinct storage. */
/* Records the blade's end and base positions each frame into a trail history of up to 50 samples, smoothing towards the new positions. */
void func_L02_003D6690(char *self, int joint) {
    float origin[4] __attribute__((aligned(16)));
    float endpoint[4] __attribute__((aligned(16)));
    float matrix[16] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float previous_end[4] __attribute__((aligned(16)));
    float previous_origin[4] __attribute__((aligned(16)));
    float error;
    int sample;
    if (gBladeTrailCount >= 50)
        return;
    TransformMobyJointToWorld(self, joint, (char *)origin);
    TransformMobyJointPoint(self, joint, (char *)matrix);
    qcopy(direction, matrix);
    error = 100.0f;
    vec_scale_to_length(direction, direction, 5.3f);
    FastVecAdd(endpoint, origin, direction);
    sample = gBladeTrailCount;
    if (sample > 0) {
        qcopy(previous_end, &gBladeTrailEndPoints[sample]);
        qcopy(previous_origin, &gBladeTrailBasePoints[sample]);
        error = fast_vec_dist(previous_end, endpoint);
        error += fast_vec_dist(previous_origin, origin);
        if (error > 0.01f) {
            do {
                int next;
                error = FloatAbs(StepValueTowardTarget(previous_end, &D_L02_001B0350, endpoint[0],
                    D_L02_001B0338 * 0.00027777778f, D_L02_001B033C * 0.00027777778f, D_L02_001B0340 * 0.016666668f));
                error += FloatAbs(StepValueTowardTarget(previous_end + 1, &D_L02_001B0354, endpoint[1],
                    D_L02_001B0338 * 0.00027777778f, D_L02_001B033C * 0.00027777778f, D_L02_001B0340 * 0.016666668f));
                error += FloatAbs(StepValueTowardTarget(previous_end + 2, &D_L02_001B0358, endpoint[2],
                    D_L02_001B0338 * 0.00027777778f, D_L02_001B033C * 0.00027777778f, D_L02_001B0340 * 0.016666668f));
                qcopy_nc(gBladeTrailEndPoints + 1 + gBladeTrailCount, previous_end);
                error += FloatAbs(StepValueTowardTarget(previous_origin, &D_L02_001B0360, origin[0],
                    D_L02_001B0338 * 0.00027777778f, D_L02_001B033C * 0.00027777778f, D_L02_001B0340 * 0.016666668f));
                error += FloatAbs(StepValueTowardTarget(previous_origin + 1, &D_L02_001B0364, origin[1],
                    D_L02_001B0338 * 0.00027777778f, D_L02_001B033C * 0.00027777778f, D_L02_001B0340 * 0.016666668f));
                error += FloatAbs(StepValueTowardTarget(previous_origin + 2, &D_L02_001B0368, origin[2],
                    D_L02_001B0338 * 0.00027777778f, D_L02_001B033C * 0.00027777778f, D_L02_001B0340 * 0.016666668f));
                qcopy_nc(gBladeTrailBasePoints + 1 + gBladeTrailCount, previous_origin);
                next = gBladeTrailCount;
                if (next >= 50)
                    return;
                gBladeTrailCount = next + 1;
            } while (error > 0.01f);
        }
    }
    if (error > 0.01f) {
        qcopy_nc(gBladeTrailEndPoints + 1 + gBladeTrailCount, endpoint);
        qcopy_nc(gBladeTrailBasePoints + 1 + gBladeTrailCount, origin);
        gBladeTrailCount++;
    }
}
