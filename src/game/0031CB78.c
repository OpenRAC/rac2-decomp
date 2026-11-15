#include "common.h"

typedef struct {
    char pad_000[0x140];
    float pos[3];
} State_001b5200;

extern State_001b5200 D_001B5200;
extern void func_0031C8E0(char *p);
extern long long func_0027C878_1(int id);
extern float func_00283248(float x, float y);
extern float func_00282E80(void *a, void *b);
extern float func_002A7940(void);
extern void func_00283410(void *dst, void *src);
extern void func_00282CF0(void *dst, void *a, void *b);
extern void func_00282F20(void *dst, void *src, float scale);
extern void func_00282D30(void *dst, void *src, float scale);
extern void func_00280B90(void *dst, void *src, int flag);

void func_0031CB78(char *unused, char *pos, int color, int first, int second, float scale)
{
    char pkt[144];
    float m[16];
    float quat[4];
    float off[4];
    long long r;
    float dx, dy;

    func_0031C8E0(pkt);
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
    dx = D_001B5200.pos[0] - *(float *)pos;
    dy = D_001B5200.pos[1] - *(float *)(pos + 4);
    *(int *)(pkt + 76) = color + first;
    *(int *)(pkt + 72) = color + first;
    *(int *)(pkt + 68) = color + first;
    *(int *)(pkt + 64) = color + first;
    quat[3] = 0;
    quat[2] = func_00283248(dx, dy);
    quat[1] = -func_00283248(vec_distance_xy(pos, &D_001B5200.pos[0]),
                              D_001B5200.pos[2] - *(float *)(pos + 8));
    quat[0] = func_002A7940();
    euler_to_matrix(m, quat);
    FastVecSub(off, &D_001B5200.pos[0], pos);
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
