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

int SegmentCrossPolyline(int path_index, float *start, float *end, float *hit_point)
{
    float direction[4], sideways[4], up_axis[4], start_local[4], end_local[4];
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
    vec_clear_128(up_axis);
    up_axis[2] = 1.0f;
    best = 1.0f;
    FastVecSub(start_local, (float *)((char *)g_path_table[path_index] + 0x10), start);
    matrix_mul_vec3(start_local, start_local, direction);
    older = start_local;
    newer = end_local;
    if (i < g_path_table[path_index]->count) {
        offset = 0x20;
        zero = 0.0f;
        do {
            FastVecSub(newer, (float *)((char *)g_path_table[path_index] + offset), start);
            matrix_mul_vec3(newer, newer, direction);
            if (start_local[3] != zero || end_local[3] != zero) {
                if (end_local[1] * start_local[1] < 0.0f) {
                    float ratio = (start_local[0] - end_local[0]) / (start_local[1] - end_local[1]);
                    float along = ratio * -end_local[1] + end_local[0];
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
        } while (i < g_path_table[path_index]->count);
    }
    lerp_vector(hit_point, start, end, best);
    return found;
}
