#include "common.h"

/* func_002C94C8: whether segment a-b crosses polyline D_001F1700[idx]; the
 * nearest crossing is interpolated into c. RAC1's SegmentCrossPolyline
 * (moby_path_and_manipulators.c) is the same body. -g gives the line labels
 * after which the assembler pads both divisions; the quotient's own statement
 * places the second label and keeps the product in $f0. */

typedef struct {
    int count;
    int pad[3];
    float points[1][4];
} SegmentPath_2C94C8;

extern SegmentPath_2C94C8 *g_path_table[];
extern void FastVecSub(float *, float *, float *);
extern float FastVecLength(float *);
extern void vec_scale_to_length(float *, float *, float);
extern void vec_clear_128(float *);
extern void matrix_mul_vec3(float *, float *, float *);
extern void lerp_vector(float *, float *, float *, float);

int SegmentCrossPolyline(int pathIndex, float *start, float *end, float *hitPoint)
{
    float direction[4], sideways[4], upAxis[4], startLocal[4], endLocal[4];
    float best;
    float zero;
    int found = 0;
    int i = 1;
    int offset;
    float *older;
    float *newer;

    FastVecSub(direction, end, start);
    direction[2] = 0;
    vec_scale_to_length(direction, direction, 1.0f / FastVecLength(direction));
    vec_clear_128(sideways);
    sideways[0] = direction[1];
    sideways[1] = -direction[0];
    vec_clear_128(upAxis);
    upAxis[2] = 1.0f;
    best = 1.0f;
    FastVecSub(startLocal, (float *)((char *)g_path_table[pathIndex] + 0x10), start);
    matrix_mul_vec3(startLocal, startLocal, direction);
    older = startLocal;
    newer = endLocal;
    if (i < g_path_table[pathIndex]->count) {
        offset = 0x20;
        zero = 0.0f;
        do {
            FastVecSub(newer, (float *)((char *)g_path_table[pathIndex] + offset), start);
            matrix_mul_vec3(newer, newer, direction);
            if (startLocal[3] != zero || endLocal[3] != zero) {
                if (endLocal[1] * startLocal[1] < 0.0f) {
                    float ratio = (startLocal[0] - endLocal[0]) / (startLocal[1] - endLocal[1]);
                    float along = ratio * -endLocal[1] + endLocal[0];
                    if (along > 0.0f && along < best) {
                        best = along;
                        found = 1;
                        qcopy(older, newer);
                        goto next;
                    }
                }
            }
            qcopy(older, newer);
        next:
            i++;
            offset += 0x10;
        } while (i < g_path_table[pathIndex]->count);
    }
    lerp_vector(hitPoint, start, end, best);
    return found;
}
