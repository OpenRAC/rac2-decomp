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

/* func_PAL_00270FC0, the PAL copy of func_00271130: the same C, where both
   weight rates are scaled by 1.2f for 50 Hz. */
/* Advances the two blend weights of a transition and refreshes its eased
   position; returns 1 when both are already complete. */
int cam_advance_blend_pal(char *target, char *state)
{
    float *weights = (float *)state;
    float pos_ease, rot_ease;
    float x, y, z;
    struct { TI128 vec; TI128 mat[4]; } frame;

    if (weights[3] == 1.0f && weights[0] == 1.0f)
        return 1;
    pos_ease = math_cosine_blend(0.0f, 1.0f, weights[3]);
    FastVecAdd(state + 0x30, g_hero_velocity, state + 0x30);
    x = *(float *)(state + 0x30);
    y = *(float *)(state + 0x34);
    z = *(float *)(state + 0x38);
    *(float *)(state + 0x40) = x + (*(float *)(target + 0x30) - x) * pos_ease;
    *(float *)(state + 0x44) = y + (*(float *)(target + 0x34) - y) * pos_ease;
    *(float *)(state + 0x48) = z + (*(float *)(target + 0x38) - z) * pos_ease;
    *(TI128 *)g_camera_eye_state = *(TI128 *)(state + 0x40);
    mat_transform_via_copy(&frame.vec, target);
    rot_ease = math_cosine_blend(0.0f, 1.0f, weights[0]);
    vec_fast_normalize3(state + 0x50, state + 0x20, &frame.vec, rot_ease);
    mat_from_rotation(state + 0x50, frame.mat);
    copy_matrix3x4(g_camera_eye_state + 0x230, frame.mat);
    weights[3] = weights[3] + weights[4] * 1.2f;
    if (weights[3] > 1.0f)
        weights[3] = 1.0f;
    weights[0] = weights[0] + weights[1] * 1.2f;
    if (weights[0] > 1.0f)
        weights[0] = 1.0f;
    return 0;
}
