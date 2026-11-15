#include "common.h"

typedef int L03_2518Quad __attribute__((mode(TI)));

extern char g_hero_position[];
/* The camera's 128-byte matrices, reloaded through an absolute macro access each time. */
extern char *D_L03_001B2B0C[] __attribute__((sda));
extern char D_L03_001B9980[];

extern void FastVecSub(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern float vec_distance_xy(void *, void *);
extern void transform_vector(void *, void *, void *);
extern void vec_clear_128(void *);
extern f32 vec_length_xy(void *);
extern float mat_fast_helper_a(float, float);

/* Works out where the moby should aim and which angles it needs to face a target seen through the camera. */
void cam_compute_aim_and_angles(u8 *self, f32 *aim, f32 *angles)
{
    f32 rel[4] __attribute__((aligned(16)));
    f32 tilt[4] __attribute__((aligned(16)));
    f32 dir[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(self + 0x68);
    f32 near;
    f32 x;

    FastVecSub(rel, g_hero_position, D_L03_001B2B0C[0] + *(s32 *)(state + 4) * 128 + 0x30);
    matrix_mul_vec3(rel, rel, D_L03_001B2B0C[0] + *(s32 *)(state + 4) * 128 + 0x40);
    near = 0.5f - vec_distance_xy(g_hero_position, D_L03_001B9980) * 0.0625f;
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
    vec_clear_128(angles);
    qcopy(rel, g_hero_position);
    rel[2] = *(f32 *)(self + 0x18);
    FastVecSub(dir, rel, aim);
    dir[2] += 2.0f;
    angles[1] = -mat_fast_helper_a(vec_length_xy(dir), dir[2]);
    angles[2] = mat_fast_helper_a(dir[0], dir[1]);
}
