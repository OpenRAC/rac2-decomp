#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));

extern char D_00189F70[];
extern char D_001B5340[];

extern void func_00282CC0(void *, void *, void *);
extern void func_00283810(void *, void *, void *, float);
extern void func_002839D0(void *, void *);
extern void func_00283678(void *, void *);
extern void func_002AB600(void *, void *);
extern float func_002A7C00(float, float, float);

/* Advances the two blend weights of a transition and refreshes its eased
   position; returns 1 when both are already complete. */
int func_00271130(char *target, char *blend)
{
    float *weights = (float *)blend;
    float posEase, rotEase;
    float x, y, z;
    struct { TI128 vec; TI128 mat[4]; } scratch;

    if (weights[3] == 1.0f && weights[0] == 1.0f)
        return 1;
    posEase = CosineBlend(0.0f, 1.0f, weights[3]);
    FastVecAdd(blend + 0x30, D_00189F70, blend + 0x30);
    x = *(float *)(blend + 0x30);
    y = *(float *)(blend + 0x34);
    z = *(float *)(blend + 0x38);
    *(float *)(blend + 0x40) = x + (*(float *)(target + 0x30) - x) * posEase;
    *(float *)(blend + 0x44) = y + (*(float *)(target + 0x34) - y) * posEase;
    *(float *)(blend + 0x48) = z + (*(float *)(target + 0x38) - z) * posEase;
    *(TI128 *)gCameraState_001B5340 = *(TI128 *)(blend + 0x40);
    TransformMatrixViaCopy(&scratch.vec, target);
    rotEase = CosineBlend(0.0f, 1.0f, weights[0]);
    FastVectorNormalize3(blend + 0x50, blend + 0x20, &scratch.vec, rotEase);
    RotationToMatrix(blend + 0x50, scratch.mat);
    copy_matrix3x4(gCameraState_001B5340 + 0x230, scratch.mat);
    weights[3] = weights[3] + weights[4];
    if (weights[3] > 1.0f)
        weights[3] = 1.0f;
    weights[0] = weights[0] + weights[1];
    if (weights[0] > 1.0f)
        weights[0] = 1.0f;
    return 0;
}
