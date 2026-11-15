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

extern SegmentPath_2C94C8 *D_001F1700[];
extern void func_00282CF0(float *, float *, float *);
extern float func_00282DF0(float *);
extern void func_00282F20(float *, float *, float);
extern void func_00282C88(float *);
extern void func_00283098(float *, float *, float *);
extern void func_00282D08(float *, float *, float *, float);

int func_002C94C8(int idx, float *a, float *b, float *c)
{
    float v[4], w[4], z[4], t[4], u[4];
    float best;
    float zero;
    int found = 0;
    int i = 1;
    int offset;
    float *prev;
    float *cur;

    FastVecSub(v, b, a);
    v[2] = 0;
    vec_scale_to_length(v, v, 1.0f / FastVecLength(v));
    func_00282C88(w);
    w[0] = v[1];
    w[1] = -v[0];
    func_00282C88(z);
    z[2] = 1.0f;
    best = 1.0f;
    FastVecSub(t, (float *)((char *)D_001F1700[idx] + 0x10), a);
    matrix_mul_vec3(t, t, v);
    prev = t;
    cur = u;
    if (i < D_001F1700[idx]->count) {
        offset = 0x20;
        zero = 0.0f;
        do {
            FastVecSub(cur, (float *)((char *)D_001F1700[idx] + offset), a);
            matrix_mul_vec3(cur, cur, v);
            if (t[3] != zero || u[3] != zero) {
                if (u[1] * t[1] < 0.0f) {
                    float q = (t[0] - u[0]) / (t[1] - u[1]);
                    float x = q * -u[1] + u[0];
                    if (x > 0.0f && x < best) {
                        best = x;
                        found = 1;
                        qcopy(prev, cur);
                        goto next;
                    }
                }
            }
            qcopy(prev, cur);
        next:
            i++;
            offset += 0x10;
        } while (i < D_001F1700[idx]->count);
    }
    lerp_vector(c, a, b, best);
    return found;
}
