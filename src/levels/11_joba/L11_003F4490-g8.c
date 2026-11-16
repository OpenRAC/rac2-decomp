#include "common.h"
typedef int StripQuadVector __attribute__((mode(TI)));
typedef struct {
    float pos[4][4];
    int color[4];
    float uv[4][2];
    long state, texture, flags, blend;
} StripQuad;

extern long GetEffectTextureDescriptor(int);
extern void gfx_init_small_sprite_packet_c(void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void transform_vector(void *, void *, void *);
extern void draw_world_quad(void *, int, int);
extern float IntToFloat(int);
extern float g_joba_beam_uv_step __attribute__((sda));
extern float g_hero_l11_position[];

/* Draws a glowing beam as two overlapping textured strips that follow a list of points. */
void DrawDualQuadStrip(float (*points)[4], int count, int blend, int color1, int color2, float width, float scale) {
    float direction[4] __attribute__((aligned(16)));
    float facing[4] __attribute__((aligned(16)));
    float side[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    StripQuad first, second;
    float horizontal[4] __attribute__((aligned(16)));
    float vertical[4] __attribute__((aligned(16)));
    float (*initialNext)[4] = points + 1;

    int i;
    float u, next;
    first.texture = GetEffectTextureDescriptor(43);
    first.flags = 0xFF9000000260L;
    first.blend = ((long)blend << 32) | 0x68;
    first.state = 0;
    first.color[3] = color1;
    first.color[2] = color1;
    first.color[1] = color1;
    first.color[0] = color1;
    gfx_init_small_sprite_packet_c(&first);
    first.uv[0][0] = 0;
    first.uv[0][1] = 0;
    first.uv[1][0] = 0;
    first.uv[1][1] = 1;
    first.uv[2][0] = 1;
    first.uv[2][1] = 0;
    first.uv[3][0] = 1;
    first.uv[3][1] = 1;
    second.texture = GetEffectTextureDescriptor(43);
    second.flags = 0xFF9000000260L;
    second.state = 0;
    second.blend = ((long)(blend/3)<<32)|0x68;
    second.color[3] = color2;
    second.color[2] = color2;
    second.color[1] = color2;
    second.color[0] = color2;
    gfx_init_small_sprite_packet_c(&second);
    *(StripQuadVector *)horizontal = 0;
    *(StripQuadVector *)vertical = 0;
    second.uv[0][0] = 0;
    second.uv[0][1] = 0;
    second.uv[1][0] = 0;
    second.uv[1][1] = 1;
    second.uv[2][0] = g_joba_beam_uv_step;
    second.uv[2][1] = 0;
    second.uv[3][0] = g_joba_beam_uv_step;
    second.uv[3][1] = 1;
    horizontal[3] = 1;
    vertical[3] = 1;
    horizontal[2] = width;
    vertical[2] = horizontal[2]*scale;
    FastVecSub(direction, initialNext, points);
    vec_scale_to_length(direction, direction, 1.0f);
    FastVecSub(facing, g_hero_l11_position, points);
    FastVecCross(side, facing, direction);
    vec_scale_to_length(side, side, 1.0f);
    FastVecCross(facing, direction, side);
    qcopy_nc(position, points);
    qcopy_nc(first.pos[0], horizontal);
    FastVecScale(first.pos[1], first.pos[0], -1.0f);
    transform_vector(first.pos[0], first.pos[0], direction);
    transform_vector(first.pos[1], first.pos[1], direction);
    qcopy_nc(second.pos[0], vertical);
    FastVecScale(second.pos[1], second.pos[0], -1.0f);
    transform_vector(second.pos[0], second.pos[0], direction);
    transform_vector(second.pos[1], second.pos[1], direction);
    for (i = 1; i < count - 1; i++) {
        qcopy_nc(first.pos[2], horizontal);
        FastVecScale(first.pos[3], first.pos[2], -1.0f);
        qcopy_nc(second.pos[2], vertical);
        FastVecScale(second.pos[3], second.pos[2], -1.0f);
        FastVecSub(direction, points[i+1], points[i]);
        vec_scale_to_length(direction, direction, 1.0f);
        FastVecSub(facing, g_hero_l11_position, points[i]);
        FastVecCross(side, facing, direction);
        vec_scale_to_length(side, side, 1.0f);
        FastVecCross(facing, direction, side);
        qcopy_nc(position, points[i]);
        transform_vector(first.pos[2], first.pos[2], direction);
        transform_vector(first.pos[3], first.pos[3], direction);
        transform_vector(second.pos[2], second.pos[2], direction);
        transform_vector(second.pos[3], second.pos[3], direction);
        first.color[3] = color1;
        first.color[2] = color1;
        first.color[1] = color1;
        first.color[0] = color1;
        second.color[3] = color2;
        second.color[2] = color2;
        second.color[1] = color2;
        second.color[0] = color2;
        if (i == 1) {
            first.color[0] = 0;
            first.color[1] = 0;
            second.color[0] = 0;
            second.color[1] = 0;
        } else if (i == count - 2) {
            first.color[2] = 0;
            first.color[3] = 0;
            second.color[2] = 0;
            second.color[3] = 0;
        }
        draw_world_quad(&first, 0, 0);
        draw_world_quad(&second, 0, 0);
        u = g_joba_beam_uv_step*IntToFloat(i);
        next = u+g_joba_beam_uv_step;
        if (u >= 1.0f) {
            u -= 1.0f;
            next -= 1.0f;
        }
        second.uv[0][0] = u;
        second.uv[2][0] = next;
        second.uv[1][0] = u;
        second.uv[3][0] = next;
        qcopy_nc(first.pos[0], first.pos[2]);
        qcopy_nc(first.pos[1], first.pos[3]);
        qcopy_nc(second.pos[0], second.pos[2]);
        qcopy_nc(second.pos[1], second.pos[3]);
    }
}
