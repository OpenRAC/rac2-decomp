#include "common.h"

typedef struct {
    char pad_000[0x140];
    float pos[3];
} State_001b5200;

extern State_001b5200 g_active_camera;
extern void gfx_init_large_quad_packet(char *p);
extern long long func_0027C878_1(int id);
extern float mat_fast_helper_a(float x, float y);
extern float vec_distance_xy(void *a, void *b);
extern float math_random_angle(void);
extern void euler_to_matrix(void *dst, void *src);
extern void FastVecSub(void *dst, void *a, void *b);
extern void vec_scale_to_length(void *dst, void *src, float scale);
extern void FastVecScale(void *dst, void *src, float scale);
extern void draw_world_quad(void *dst, void *src, int flag);

/* Draws a two-layer glowing flare at a position, turned to face the camera. The second layer is half the size of the first. */
void gfx_draw_facing_glow_flare(char *unused, char *pos, int color, int first, int second, float scale)
{
    char pkt[144];
    float m[16];
    float quat[4];
    float off[4];
    long long r;
    float dx, dy;

    gfx_init_large_quad_packet(pkt);
    *(int *)(pkt + 80) = 0;
    *(float *)(pkt + 92) = 1.0f;
    *(float *)(pkt + 96) = 1.0f;
    *(float *)(pkt + 104) = 1.0f;
    *(float *)(pkt + 108) = 1.0f;
    *(int *)(pkt + 84) = 0;
    *(int *)(pkt + 88) = 0;
    *(int *)(pkt + 100) = 0;
    r = func_0027C878_1(11);
    *(long long *)(pkt + 112) = 0;
    *(long long *)(pkt + 120) = r;
    *(long long *)(pkt + 128) = 0xFF9000000260LL;
    *(long long *)(pkt + 136) = 0x8000000048LL;
    dx = g_active_camera.pos[0] - *(float *)pos;
    dy = g_active_camera.pos[1] - *(float *)(pos + 4);
    *(int *)(pkt + 76) = color + first;
    *(int *)(pkt + 72) = color + first;
    *(int *)(pkt + 68) = color + first;
    *(int *)(pkt + 64) = color + first;
    quat[3] = 0;
    quat[2] = mat_fast_helper_a(dx, dy);
    quat[1] = -mat_fast_helper_a(vec_distance_xy(pos, &g_active_camera.pos[0]),
                              g_active_camera.pos[2] - *(float *)(pos + 8));
    quat[0] = math_random_angle();
    euler_to_matrix(m, quat);
    FastVecSub(off, &g_active_camera.pos[0], pos);
    vec_scale_to_length(off, off, 0.5f);
    m[12] = *(float *)(pos) + off[0];
    m[13] = *(float *)(pos + 4) + off[1];
    m[14] = *(float *)(pos + 8) + off[2];
    m[15] = 1.0f;
    FastVecScale(pkt, pkt, scale);
    FastVecScale(pkt + 16, pkt + 16, scale);
    FastVecScale(pkt + 32, pkt + 32, scale);
    FastVecScale(pkt + 48, pkt + 48, scale);
    draw_world_quad(pkt, m, 0);
    *(int *)(pkt + 76) = color + second;
    *(int *)(pkt + 72) = color + second;
    *(int *)(pkt + 68) = color + second;
    *(int *)(pkt + 64) = color + second;
    FastVecScale(pkt, pkt, 0.5f);
    FastVecScale(pkt + 16, pkt + 16, 0.5f);
    FastVecScale(pkt + 32, pkt + 32, 0.5f);
    FastVecScale(pkt + 48, pkt + 48, 0.5f);
    draw_world_quad(pkt, m, 0);
}
