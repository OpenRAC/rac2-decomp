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
int func_PAL_00270FC0(char *a0, char *a1)
{
    float *w = (float *)a1;
    float t, e;
    float x, y, z;
    struct { TI128 vec; TI128 mat[4]; } f;

    if (w[3] == 1.0f && w[0] == 1.0f)
        return 1;
    t = math_cosine_blend(0.0f, 1.0f, w[3]);
    FastVecAdd(a1 + 0x30, g_hero_velocity, a1 + 0x30);
    x = *(float *)(a1 + 0x30);
    y = *(float *)(a1 + 0x34);
    z = *(float *)(a1 + 0x38);
    *(float *)(a1 + 0x40) = x + (*(float *)(a0 + 0x30) - x) * t;
    *(float *)(a1 + 0x44) = y + (*(float *)(a0 + 0x34) - y) * t;
    *(float *)(a1 + 0x48) = z + (*(float *)(a0 + 0x38) - z) * t;
    *(TI128 *)g_camera_eye_state = *(TI128 *)(a1 + 0x40);
    mat_transform_via_copy(&f.vec, a0);
    e = math_cosine_blend(0.0f, 1.0f, w[0]);
    vec_fast_normalize3(a1 + 0x50, a1 + 0x20, &f.vec, e);
    mat_from_rotation(a1 + 0x50, f.mat);
    copy_matrix3x4(g_camera_eye_state + 0x230, f.mat);
    w[3] = w[3] + w[4] * 1.2f;
    if (w[3] > 1.0f)
        w[3] = 1.0f;
    w[0] = w[0] + w[1] * 1.2f;
    if (w[0] > 1.0f)
        w[0] = 1.0f;
    return 0;
}
