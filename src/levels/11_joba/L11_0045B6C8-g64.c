#include "common.h"

typedef int L11RenderQuad __attribute__((mode(TI)));
typedef struct {
    float vertex[4][4];
    int color[4];
    float uv[4][2];
    u64 reserved, texture, setup, state;
} L11Packet;

/* The UV table and corner arrays occupy 32 and 64 bytes of small data. */
extern int D_L11_001B30C8[] __attribute__((sda));
extern int D_L11_001B2060 __attribute__((sda));
extern int D_L11_001B2090 __attribute__((sda));
extern int D_L11_001B2064[] __attribute__((sda));
extern int D_L11_001B2098[] __attribute__((sda));
extern float D_L11_001B2070[4][2] __attribute__((sda));
extern L11RenderQuad D_L11_001B20A0[4] __attribute__((sda));
extern L11RenderQuad D_L11_001B20E0[4] __attribute__((sda));
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
/* Draws a spinning star-shaped glow made of two layered sprites. */
void gfx_draw_spinning_glow_sprites(char *moby)
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
    temp[0] = IntToFloat(D_L11_001B30C8[0] % 600) *
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
    FillQuadPacket(&packets[0], D_L11_001B2060, D_L11_001B2090,
                      D_L11_001B2070, D_L11_001B20A0, 1);
    FillQuadPacket(&packets[1], D_L11_001B2064[0], D_L11_001B2098[0],
                      D_L11_001B2070, D_L11_001B20E0, 1);
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
