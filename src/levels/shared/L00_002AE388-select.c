#include "common.h"

extern unsigned char D_00189E20_26[];
extern char *D_L00_001FACE0[];
extern unsigned char D_L00_001B8FF0[];

extern float func_L00_002AE388(char *, float, float, float, float, int *);
extern float func_L00_002AE5F0(char *, void *, float, float, float, int *, void *);
extern void func_00283698(void *, void *);
extern void *func_002AB1F0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, int, int);

/* Select the best eligible hero target, optionally testing line of sight. */
char *func_L00_002AE888(void *axis, int type, int occlusion, float range,
                      float heading, float hlimit, float vlimit)
{
    float matrix[16] __attribute__((aligned(16)));
    float start[4] __attribute__((aligned(16)));
    float end[4] __attribute__((aligned(16)));
    int blocked;
    char *best = 0, *object;
    int index;
    float score, bestScore = 100000000.0f;

    if (D_00189E20_26[0x22c3])
        matrix_from_basis_rows(matrix, D_L00_001B8FF0);

    for (index = 0; (object = D_L00_001FACE0[index]) != 0; index++) {
        if (type != -1 && *(short *)(*(char **)(object + 0x24) + 0x46) != type)
            continue;
        if (type == 5) {
            float *data = GetMobyPrivateValue0(object);
            if (!data || data[0] == 0.0f)
                continue;
        }
        if (!(*(unsigned short *)(object + 0x34) & 0x1000))
            continue;

        if (D_00189E20_26[0x22c3])
            score = ScoreTargetByAimAxis(object, axis, range, hlimit, vlimit, &blocked, matrix);
        else
            score = ScoreTargetByHeading(object, heading, range, hlimit, vlimit, &blocked);
        if (blocked || !(score < bestScore))
            continue;

        if (occlusion) {
            qcopy_nc(start, D_00189E20_26 + 0xe0);
            vec_scale_to_length(end, object + 0xe0, 1.0f);
            FastVecAdd(end, end, object + 0x10);
            if (CollLine(start, end, 2, 0, 0))
                continue;
        }
        bestScore = score;
        best = object;
    }
    return best;
}
