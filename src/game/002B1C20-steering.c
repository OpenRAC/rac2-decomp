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

int func_002B1CC8(char *obj, float *out, void *in, float radius, float tolerance)
{
    float v[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    float angles[16];
    float angle, heading, length;
    int count, n, i, j;

    qcopy(out, in);
    qcopy(v, in);
    v[2] = 0;
    vec_scale_to_length(v, v, radius);
    FastVecAdd(pos, obj + 0x10, v);
    heading = func_00283248(v[0], v[1]);
    count = func_00277F48(pos, 0, obj, 0, radius);
    if (count) {
        n = 0;
        for (i = 0; i < count && i < 16; i++) {
            if (func_002ABB78(D_001BF000[i]) ||
                (*(char **)(D_001BF000[i] + 0x24) &&
                 *(short *)(*(char **)(D_001BF000[i] + 0x24) + 0x46) == 22)) {
                radius = func_00283248(
                    *(float *)(D_001BF000[i] + 0x10) - *(float *)(obj + 0x10),
                    *(float *)(D_001BF000[i] + 0x14) - *(float *)(obj + 0x14));
                if (FastDiffRots(heading, radius) < tolerance)
                    angles[n++] = radius;
            }
        }
        if (n) {
            int k;
            for (k = 0; k < n - 1; k++) {
                int next = k;
                next++;
                for (j = 0; j < n - next; j++) {
                    if (angles[j + 1] < angles[j]) {
                        float t = angles[j];
                        angles[j] = angles[j + 1];
                        angles[j + 1] = t;
                    }
                }
            }
            angle = angles[n >> 1];
            length = vec_length_xy(out);
            out[0] = func_00283180(angle) * length;
            out[1] = func_00283198(angle) * length;
        }
        return 1;
    }
    return 0;
}
