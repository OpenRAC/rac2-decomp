#include "include_asm.h"
#include "common.h"

extern char D_00189EA0[];
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);

typedef union {
    int q __attribute__((mode(TI)));
    float f[4];
} Quad __attribute__((aligned(16)));

/* Rebuilds the camera's three axes so it looks from its position toward the player. */
void func_L04_0046D6A8(char *obj) {
    Quad offset;
    Quad upVector;
    char *axisY;
    char *cameraData = *(char **)(obj + 0x70);

    qcopy(&offset, gHeroPosition);
    offset.f[2] = offset.f[2] + *(float *)(cameraData + 0x90);
    upVector.q = 0;
    upVector.f[2] = 1.0f;
    upVector.f[3] = 1.0f;
    FastVecSub(obj, &offset, obj + 0x30);
    vec_scale_to_length(obj, obj, 1.0f);
    axisY = obj + 0x10;
    FastVecCross(axisY, obj, &upVector);
    vec_scale_to_length(axisY, axisY, 1.0f);
    FastVecCross(obj + 0x20, axisY, obj);
}
