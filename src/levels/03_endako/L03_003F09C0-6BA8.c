/* func_L03_003F6BA8: needs -g (nop pairs before div.s) and -fmove-all-movables (loop.c must hoist the edge constant 2, or combine folds the movz into a shift). */
#include "common.h"

typedef int BeamQuad __attribute__((mode(TI)));
struct QuadPacket { BeamQuad vertices[4]; int colors[4]; float uv[4][2]; long state70, state78, state80, state88; };
extern void moby_transform_joint_point(char *, int, char *);
extern void FillQuadPacket(struct QuadPacket *, int, int, float (*)[2], BeamQuad *, int);
extern void vec_clear_128(BeamQuad *);
extern void euler_rotation_basis(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern int FastTweenColor(int, int, float);
extern void draw_world_quad(void *, void *, int);
extern int g_beam_l03_quad_texture_a SDATA(D_L03_001B1108);
extern int g_beam_l03_quad_texture_b __attribute__((sda));
extern int g_beam_quad_mode_a SDATA(D_L03_001B1138);
extern int g_beam_quad_mode_b __attribute__((sda));
extern int g_beam_quad_color_a __attribute__((sda)), g_beam_quad_color_b __attribute__((sda));
extern float g_beam_l03_quad_uvs[][2] SDATA(D_L03_001B1118);
extern BeamQuad g_beam_quad_shape_a[] SDATA(D_L03_001B1150);
extern BeamQuad g_beam_quad_shape_b[] SDATA(D_L03_001B1190);
extern float g_beam_quad_alpha_divisor SDATA(D_L03_001B11D0);

/* Four complete144-byte draw packets, two48-byte rotation bases, the actual
 *64-byte object basis and one initialized16-byte Euler vector. Both template
 * reads cover64 bytes; UV reads cover32. No adjacent-vector pseudo-matrix. */
void gfx_draw_beam_quad_packets(char *object)
{
    float euler[4], rotation[3][4], squared[3][4], matrix[4][4];
    struct QuadPacket packets[4];
    int i, j;
    float alpha;
    moby_transform_joint_point(object, 7, (char *)matrix);
    FillQuadPacket(&packets[0], g_beam_l03_quad_texture_a, g_beam_quad_mode_a, g_beam_l03_quad_uvs, g_beam_quad_shape_a, 1);
    FillQuadPacket(&packets[1], g_beam_l03_quad_texture_a, g_beam_quad_mode_a, g_beam_l03_quad_uvs, g_beam_quad_shape_a, 1);
    FillQuadPacket(&packets[2], g_beam_l03_quad_texture_b, g_beam_quad_mode_b, g_beam_l03_quad_uvs, g_beam_quad_shape_b, 1);
    FillQuadPacket(&packets[3], g_beam_l03_quad_texture_b, g_beam_quad_mode_b, g_beam_l03_quad_uvs, g_beam_quad_shape_b, 1);
    {
        int k;
        for (k = 0; k < 4; ++k) {
            /* x and y of vertex k in packets 1 and 3 (36 floats a packet) */
            float *a = (float *)packets + k * 4;
            a[36] = -a[36];
            a[37] = -a[37];
            a[108] = -a[108];
            a[109] = -a[109];
        }
    }
    packets[0].colors[3] = g_beam_quad_color_a;
    packets[0].colors[1] = g_beam_quad_color_a;
    packets[1].colors[3] = g_beam_quad_color_a;
    packets[1].colors[1] = g_beam_quad_color_a;
    packets[2].colors[3] = g_beam_quad_color_b;
    packets[2].colors[1] = g_beam_quad_color_b;
    packets[3].colors[3] = g_beam_quad_color_b;
    packets[3].colors[1] = g_beam_quad_color_b;
    vec_clear_128((BeamQuad *)euler);
    euler[2] = 0.09817477f;
    euler_rotation_basis(rotation, euler);
    {
        int k;
        for (k = 0; k < 2; ++k) {
            matrix_mul_vec3(&packets[k].vertices[2], &packets[k].vertices[2], rotation);
            matrix_mul_vec3(&packets[k].vertices[3], &packets[k].vertices[3], rotation);
        }
    }
    multiply_matrix3x3(squared, rotation, rotation);
    alpha = 1.0f / g_beam_quad_alpha_divisor;
    for (i = 0; i < 32; ++i) {
        int edge = (i & 1) ? 2 : 0;
        for (j = 0; j < 4; ++j) {
            int color;
            matrix_mul_vec3(&packets[j].vertices[edge], &packets[j].vertices[edge], squared);
            matrix_mul_vec3(&packets[j].vertices[edge+1], &packets[j].vertices[edge+1], squared);
            color = packets[j].colors[edge];
            packets[j].colors[edge] = FastTweenColor(color, color & 0xffffff, alpha);
            color = packets[j].colors[edge+1];
            packets[j].colors[edge+1] = FastTweenColor(color, color & 0xffffff, alpha);
            draw_world_quad(&packets[j], matrix, 1);
        }
    }
}
