#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));

extern char g_hero_velocity[];
extern char g_camera_eye_state[];

extern void FastVecAdd(void *, void *, void *);
extern void vec_fast_normalize3(void *, void *, void *, float);
extern void mat_from_rotation(void *, void *);
extern void copy_matrix3x4(void *, void *);
extern void mat_transform_via_copy(void *, void *);
extern float math_cosine_blend(float, float, float);

/* Advances the two blend weights of a transition and refreshes its eased
   position; returns 1 when both are already complete. */
int cam_advance_blend(char *target, char *blend)
{
    float *weights = (float *)blend;
    float posEase, rotEase;
    float x, y, z;
    struct { TI128 vec; TI128 mat[4]; } scratch;

    if (weights[3] == 1.0f && weights[0] == 1.0f)
        return 1;
    posEase = math_cosine_blend(0.0f, 1.0f, weights[3]);
    FastVecAdd(blend + 0x30, g_hero_velocity, blend + 0x30);
    x = *(float *)(blend + 0x30);
    y = *(float *)(blend + 0x34);
    z = *(float *)(blend + 0x38);
    *(float *)(blend + 0x40) = x + (*(float *)(target + 0x30) - x) * posEase;
    *(float *)(blend + 0x44) = y + (*(float *)(target + 0x34) - y) * posEase;
    *(float *)(blend + 0x48) = z + (*(float *)(target + 0x38) - z) * posEase;
    *(TI128 *)g_camera_eye_state = *(TI128 *)(blend + 0x40);
    mat_transform_via_copy(&scratch.vec, target);
    rotEase = math_cosine_blend(0.0f, 1.0f, weights[0]);
    vec_fast_normalize3(blend + 0x50, blend + 0x20, &scratch.vec, rotEase);
    mat_from_rotation(blend + 0x50, scratch.mat);
    copy_matrix3x4(g_camera_eye_state + 0x230, scratch.mat);
    weights[3] = weights[3] + weights[4];
    if (weights[3] > 1.0f)
        weights[3] = 1.0f;
    weights[0] = weights[0] + weights[1];
    if (weights[0] > 1.0f)
        weights[0] = 1.0f;
    return 0;
}
