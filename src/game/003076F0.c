/* func_003076F0: the motion pointer is a byte pointer (its scale is at +0x10), the child's
 * entity is read once for the copy and the +0xE0 argument, and the copy is
 * qcopy(), so the buffer address is set up before the motion is saved. */
#include "common.h"


extern char *func_002AB1F0(char *);
extern void func_002FE8D8(void *object, float *out);
extern void func_00282D30(char *local, void *value, float scale);
extern void func_00282CC0(void *out, void *a, void *b);
extern void func_0029FCC0(void *entity, int a, void *out);
extern void func_00282CF0(void *out, void *a, void *b);
extern void func_002836E8(float *out, float *in);
extern void func_00283098(void *out, void *a, void *b);

/* Aims the Megaturret at its locked target. Drops the target and goes idle when the target is gone. */
void func_003076F0(char *object)
{
    float vec[28];
    char *vars = *(char **)(object + 0x68);
    char *targetInfo = GetMobyPrivateValue0(*(char **)(vars + 0x64));
    char *target;

    GetObjectFacingDirection(object + 0x10, &vec[4]);
    target = *(char **)(vars + 0x64);
    qcopy(&vec[0], target + 0x10);
    if (targetInfo != 0) {
        FastVecScale((char *)&vec[12], target + 0xE0, *(float *)(targetInfo + 0x10));
        FastVecAdd(&vec[0], &vec[0], &vec[12]);
    }
    if (*(char **)(vars + 0x64) == 0
            || *(unsigned char *)(*(char **)(vars + 0x64) + 0x20) == 0xFE
            || *(unsigned char *)(*(char **)(vars + 0x64) + 0x20) == 0xFD
            || !(*(unsigned short *)(*(char **)(vars + 0x64) + 0x34) & 0x1000)) {
        *(unsigned char *)(object + 0x20) = 3;
        *(char **)(vars + 0x64) = 0;
        return;
    }
    TransformMobyJointToWorld(object, 0, &vec[8]);
    FastVecSub(&vec[12], &vec[0], &vec[8]);
    FastMatrixHelperC(&vec[16], (float *)(object + 0xC0));
    matrix_mul_vec3(vars + 0x20, &vec[12], &vec[16]);
}
