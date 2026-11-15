#include "names.h"
/* Builds the object matrix and its inverse, brings the offset into the object frame and
   applies a step to the second vector whose sign follows the offset's first component. The
   step size is one of two resident floats. Every callee is a ref_ name: the retail keeps
   level-resident copies of the helpers. */
extern float D_L03_001B02D0 __attribute__((sda));
extern float D_L03_001B02D4 __attribute__((sda));
extern void ref_L03_003CA148_01(float *, char *);
extern void ref_L03_003CA148_02(float *, float *);
extern void ref_L03_003CA148_03(float *, float *, char *);
extern void ref_L03_003CA148_00(char *, float *, float *, int);
extern void ref_L03_003CA148_04(float *, float *, float);
extern void ref_L03_003CA148_05(float *, float *, char *);

void mat_compute_side_step_offset(char *moby, float *offset, float *output) {
    float local[4] __attribute__((aligned(16)));
    float matrix[16] __attribute__((aligned(16)));
    float inverse[16] __attribute__((aligned(16)));
    float step;

    ref_L03_003CA148_01(matrix, moby + 0xF0);
    ref_L03_003CA148_02(inverse, matrix);
    ref_L03_003CA148_03(local, offset, moby + 0x10);
    ref_L03_003CA148_00(moby, local, local, 0);
    if (*(short *)(moby + 0xAA) == 0xE87 /* moby class 3719 */) {
        step = D_L03_001B02D0;
    } else {
        step = D_L03_001B02D4;
    }
    if (local[0] < 0.0f) {
        step = -step;
    }
    ref_L03_003CA148_04(output, matrix, step);
    ref_L03_003CA148_05(output, output, moby + 0x10);
}
