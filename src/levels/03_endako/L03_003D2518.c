#include "common.h"

typedef int L03_2518Quad __attribute__((mode(TI)));

extern char D_00189EA0[];
/* The camera's 128-byte matrices, reloaded through an absolute macro access each time. */
extern char *D_L03_001B2B0C[] __attribute__((sda));
extern char D_L03_001B9980[];

extern void func_00282CF0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern float func_00282E80(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00282C88(void *);
extern f32 func_00282E20(void *);
extern float func_00283248(float, float);

void func_L03_003D2518(u8 *self, f32 *aim, f32 *angles)
{
    f32 rel[4] __attribute__((aligned(16)));
    f32 tilt[4] __attribute__((aligned(16)));
    f32 dir[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(self + 0x68);
    f32 near;
    f32 x;

    FastVecSub(rel, D_00189EA0, D_L03_001B2B0C[0] + *(s32 *)(state + 4) * 128 + 0x30);
    matrix_mul_vec3(rel, rel, D_L03_001B2B0C[0] + *(s32 *)(state + 4) * 128 + 0x40);
    near = 0.5f - vec_distance_xy(D_00189EA0, D_L03_001B9980) * 0.0625f;
    if (near < 0.0f)
        near = 0.0f;
    x = rel[0] - near;
    if (1.0f < x)
        x = 1.0f;
    else if (x < -1.0f)
        x = -1.0f;
    *(L03_2518Quad *)tilt = 0;
    tilt[0] = x;
    tilt[3] = 1.0f;
    transform_vector(aim, tilt, D_L03_001B2B0C[0] + *(s32 *)(state + 4) * 128);
    func_00282C88(angles);
    qcopy(rel, D_00189EA0);
    rel[2] = *(f32 *)(self + 0x18);
    FastVecSub(dir, rel, aim);
    dir[2] += 2.0f;
    angles[1] = -func_00283248(vec_length_xy(dir), dir[2]);
    angles[2] = func_00283248(dir[0], dir[1]);
}
