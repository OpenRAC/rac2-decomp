#include "common.h"

typedef struct {
    float matrix[16];
    u32 color[4];
    float uv[8];
    u64 state[4];
} __attribute__((aligned(16))) WorldQuad;

typedef struct {
    u8 prefix00[0x140];
    float position[4];
} CameraPrefix;
extern CameraPrefix g_active_camera;
extern void gfx_init_large_quad_packet(char *);
extern u64 GetEffectTextureDescriptor(int);
extern float mat_fast_helper_a(float, float);
extern float vec_distance_xy(const void *, const void *);
extern float math_random_angle(void);
extern void euler_to_matrix(void *, const void *);
extern void FastVecSub(void *, const void *, const void *);
extern void vec_scale_to_length(void *, const void *, float);
extern void FastVecScale(void *, const void *, float);
extern void draw_world_quad(const void *, const void *, int);

typedef char WorldQuadExtent[(sizeof(WorldQuad) == 0x90) ? 1 : -1];

/* The qualified 0031CB78 sibling uses the same packet and camera-facing
 * construction. This variant draws textures 5/42 with its own two colors. */
/* Draws a two-layer glow at a position, turned to face the camera, using two different textures and colors. */
void gfx_draw_facing_glow_two_textures(char *unused, char *pos, float scale, int first, int second)
{
    WorldQuad packet;
    float matrix[16] __attribute__((aligned(16)));
    float euler[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    u64 texture;
    float dx, dy;

    gfx_init_large_quad_packet((char *)&packet);
    packet.uv[0] = 0.0f;
    packet.uv[3] = 1.0f;
    packet.uv[4] = 1.0f;
    packet.uv[6] = 1.0f;
    packet.uv[7] = 1.0f;
    packet.uv[1] = 0.0f;
    packet.uv[2] = 0.0f;
    packet.uv[5] = 0.0f;
    texture = GetEffectTextureDescriptor(5);
    packet.state[0] = 0;
    packet.state[1] = texture;
    packet.state[2] = 0xFF9000000260ULL;
    packet.state[3] = 0x8000000048ULL;
    dx = g_active_camera.position[0] - *(float *)pos;
    dy = g_active_camera.position[1] - *(float *)(pos + 4);
    packet.color[3] = (u32)first + 0x30000000u;
    packet.color[2] = (u32)first + 0x30000000u;
    packet.color[1] = (u32)first + 0x30000000u;
    packet.color[0] = (u32)first + 0x30000000u;
    euler[3] = 0.0f;
    euler[2] = mat_fast_helper_a(dx, dy);
    euler[1] = -mat_fast_helper_a(vec_distance_xy(pos, g_active_camera.position),
                              g_active_camera.position[2] - *(float *)(pos + 8));
    euler[0] = math_random_angle();
    euler_to_matrix(matrix, euler);
    FastVecSub(offset, g_active_camera.position, pos);
    vec_scale_to_length(offset, offset, 0.5f);
    matrix[12] = *(float *)pos + offset[0];
    matrix[13] = *(float *)(pos + 4) + offset[1];
    matrix[14] = *(float *)(pos + 8) + offset[2];
    matrix[15] = 1.0f;
    FastVecScale(packet.matrix, packet.matrix, scale);
    FastVecScale(packet.matrix + 4, packet.matrix + 4, scale);
    FastVecScale(packet.matrix + 8, packet.matrix + 8, scale);
    FastVecScale(packet.matrix + 12, packet.matrix + 12, scale);
    draw_world_quad(&packet, matrix, 0);
    packet.state[1] = GetEffectTextureDescriptor(42);
    packet.color[3] = (u32)second + 0x20000000u;
    packet.color[2] = (u32)second + 0x20000000u;
    packet.color[1] = (u32)second + 0x20000000u;
    packet.color[0] = (u32)second + 0x20000000u;
    FastVecScale(packet.matrix, packet.matrix, 1.0f);
    FastVecScale(packet.matrix + 4, packet.matrix + 4, 1.0f);
    FastVecScale(packet.matrix + 8, packet.matrix + 8, 1.0f);
    FastVecScale(packet.matrix + 12, packet.matrix + 12, 1.0f);
    draw_world_quad(&packet, matrix, 0);
}
