#include "common.h"
extern int g_current_map_index[3] __attribute__((sda));
typedef struct { char pad[0x34]; int frame; } DrawState;
extern DrawState g_glow_context;
extern float g_glow_rotation __attribute__((sda));
extern float g_glow_quad_matrix[4][4] MACRO_ADDR;
extern void euler_rotation_basis(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float IntToFloat(int);
extern float math_fast_sin_or_cos_b(float);
extern int FloatToInt(float);
extern void DrawQuadWithRotatedUVs(void *, int, int, int, int);

/* Draws the pulsing quad that marks the object while the level is src state 9: its corners are
   rotated about Z, moved to the object and queued with a sine-modulated alpha. */
void gfx_draw_state_nine_pulsing_quad(char *moby)
{
    float mat[3][4];
    float rot[4];
    float corners[4][4];
    float offset[4];
    float *dest, *src, *first;
    int i, id, phase;
    unsigned int color;

    if (g_current_map_index[0] != 9)
        return;

    id = -1;
    if ((unsigned int)(g_glow_context.frame - 2) <= 998)
        id = 0x47;
    if (id == -1)
        return;

    qzero_nc(rot);
    rot[2] = g_glow_rotation;
    euler_rotation_basis(mat, rot);
    vec_scale_to_length(offset, mat, 0.05f);
    first = corners[0];
    dest = first;
    src = g_glow_quad_matrix[0];
    for (i = 3; i >= 0; --i) {
        matrix_mul_vec3(dest, src, mat);
        src -= 4;
        FastVecAdd(dest, dest, moby + 0x10);
        FastVecAdd(dest, dest, offset);
        dest += 4;
    }

    phase = g_glow_context.frame % 120;
    {
        float denom = IntToFloat(120);
        float angle = (float)phase * 6.283186f;
        angle /= denom;
        color = FloatToInt((math_fast_sin_or_cos_b(angle) * 0.5f + 0.5f) * 48.0f);
    }
    color = ((color + 80) << 24) | 0x808080;
    DrawQuadWithRotatedUVs(first, id, 0, color, 0);
}
