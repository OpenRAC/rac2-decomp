#include "include_asm.h"

#include "common.h"
typedef int L11RenderQuad __attribute__((mode(TI)));
typedef struct {
    float vertex[4][4];
    int color[4];
    float uv[4][2];
    u64 reserved, texture, setup, state;
} L11Packet;
extern int g_arena_progress_level[] __attribute__((sda));
extern int g_glow_quad_param_a __attribute__((sda));
extern int g_glow_quad_param_c __attribute__((sda));
extern int g_glow_quad_params_b[] __attribute__((sda));
extern int g_glow_quad_params_d[] __attribute__((sda));
extern float g_glow_l11_quad_uvs[4][2] __attribute__((sda));
extern L11RenderQuad g_glow_render_quads_a[4] __attribute__((sda));
extern L11RenderQuad g_glow_render_quads_b[4] __attribute__((sda));
extern float IntToFloat(int);
extern void euler_to_matrix(void *, void *);
extern void transform_vector(void *, void *, void *);
extern int math_fast_helper_a(void *, float);
extern void multiply_matrix(void *, void *, void *);
extern void FillQuadPacket(void *, int, int, void *, void *, int);
extern void vec_clear_128(void *);
extern void euler_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void draw_world_quad(void *, void *, int);

/* Rotate alternating packet edges and submit the pair sixteen times. */
void gfx_draw_spinning_glow_sprites_pal(char *moby)
{
    float matrix[16], rotation[16], spin[12];
    float vector[4];
    L11Packet packets[2];
    float angles[4], temp[4], transform[12];
    char *vars = *(char **)(moby + 0x68);
    int i, j, k, side;

    *(L11RenderQuad *)vector = 0;
    vector[0] = 30.0f;
    vector[3] = 1.0f;
    *(L11RenderQuad *)temp = 0;
    temp[0] = IntToFloat(g_arena_progress_level[0] % 500) *
        (1.0f / 600.0f) * 2.0f * 3.14159274f - 3.14159274f;
    *(L11RenderQuad *)angles = *(L11RenderQuad *)temp;
    euler_to_matrix(rotation, angles);
    euler_to_matrix(matrix, moby + 0xF0);
    qcopy(matrix + 12, moby + 0x10);
    matrix[15] = 1.0f;
    transform_vector(temp, vector, matrix);
    temp[3] = 30.0f;
    if (math_fast_helper_a(temp, 512.0f) != -1)
        multiply_matrix(matrix, matrix, rotation);
    FillQuadPacket(&packets[0], g_glow_quad_param_a, g_glow_quad_param_c,
                      g_glow_l11_quad_uvs, g_glow_render_quads_a, 1);
    FillQuadPacket(&packets[1], g_glow_quad_params_b[0], g_glow_quad_params_d[0],
                      g_glow_l11_quad_uvs, g_glow_render_quads_b, 1);
    for (i = 0; i < 4; i++) {
        packets[0].color[i] += *(int *)vars;
        packets[1].color[i] += *(int *)vars;
    }
    vec_clear_128(angles);
    angles[0] = 0.52359879f;
    euler_rotation_basis(spin, angles);
    multiply_matrix3x3(transform, spin, spin);
    for (k = 0; k < 16; k++) {
        side = (k & 1) ? 2 : 0;
        for (j = 0; j < 2; j++) {
            matrix_mul_vec3(packets[j].vertex[side], packets[j].vertex[side], transform);
            matrix_mul_vec3(packets[j].vertex[side + 1], packets[j].vertex[side + 1], transform);
            draw_world_quad(&packets[j], matrix, 1);
        }
    }
}
