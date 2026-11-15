#include "include_asm.h"
#include "names.h"

/* func_L23_00418BC8 is a unit of its own: it reads $gp data and needs the opt-in quadword-copy
   profile and its scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt).
   The stack vectors stay plain addresses: retail's second names for them are gcse's reaching
   registers, so a pointer local here only moves them away from retail's. */

typedef int TI128 __attribute__((mode(TI)));

extern float D_L23_001B16B8 __attribute__((sda));

extern float fast_vec_dist(float *, float *);
extern void FastVecAdd(float *, float *, float *);
extern void FastVecSub(float *, float *, float *);
extern void vec_scale_to_length(float *, float *, float);
extern void mothership_project_point_onto_surface(char *, float);
extern int CollLine(char *, char *, int, int, int);

/* Walks from one point to another over the planet surface in small steps and says whether nothing blocks the way. */
int mothership_check_clear_path(char *obj, TI128 *startPos, TI128 *endPos) {
    char *state = *(char **)(obj + 0x68);
    TI128 points[6];
    int found;

    if (fast_vec_dist((float *)startPos, (float *)endPos) > 70.0f)
        return 0;
    points[0] = *endPos;
    mothership_project_point_onto_surface((char *)&points[0], *(float *)(state + 0x54) + *(float *)(state + 0x50));
    FastVecSub((float *)&points[1], (float *)&points[0], (float *)startPos);
    vec_scale_to_length((float *)&points[1], (float *)&points[1], D_L23_001B16B8);
    points[4] = *startPos;
    points[2] = *startPos;
    mothership_project_point_onto_surface((char *)&points[2], *(float *)(state + 0x54) + *(float *)(state + 0x50));
    found = 0;
    do {
        float d = fast_vec_dist((float *)&points[4], (float *)&points[0]);

        if (d < D_L23_001B16B8) {
            if (d < 0.0f)
                return 1;
            vec_scale_to_length((float *)&points[5], (float *)&points[1], d);
            found = 1;
            FastVecAdd((float *)&points[3], (float *)&points[4], (float *)&points[5]);
            mothership_project_point_onto_surface((char *)&points[3], *(float *)(state + 0x54) + *(float *)(state + 0x50));
        } else {
            FastVecAdd((float *)&points[3], (float *)&points[4], (float *)&points[1]);
            mothership_project_point_onto_surface((char *)&points[3], *(float *)(state + 0x54) + *(float *)(state + 0x50));
        }
        if (CollLine((char *)&points[2], (char *)&points[3], 0x12, 0, 0) != 0)
            return 0;
        points[2] = points[3];
        FastVecAdd((float *)&points[4], (float *)&points[4], (float *)&points[1]);
    } while (found == 0);
    return 1;
}
