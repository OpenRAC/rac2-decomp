#include "common.h"
typedef int StripQuadVector __attribute__((mode(TI)));
typedef struct {
    float pos[4][4];
    int color[4];
    float uv[4][2];
    long state, texture, flags, blend;
} StripQuad;

extern long func_0027C878(int);
extern void func_L00_003E0CE8(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(void *, int, int);
extern float func_00283CE0(int);
extern float D_L11_001B05E0 __attribute__((sda));
extern float D_L11_001BA8C0[];

/* Draws a glowing beam as two overlapping textured strips that follow a list of points. */
void func_L11_003F4490(float (*points)[4], int count, int blend, int color1, int color2, float width, float scale) {
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
    InitSmallSpritePacketC(&first);
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
    InitSmallSpritePacketC(&second);
    *(StripQuadVector *)horizontal = 0;
    *(StripQuadVector *)vertical = 0;
    second.uv[0][0] = 0;
    second.uv[0][1] = 0;
    second.uv[1][0] = 0;
    second.uv[1][1] = 1;
    second.uv[2][0] = D_L11_001B05E0;
    second.uv[2][1] = 0;
    second.uv[3][0] = D_L11_001B05E0;
    second.uv[3][1] = 1;
    horizontal[3] = 1;
    vertical[3] = 1;
    horizontal[2] = width;
    vertical[2] = horizontal[2]*scale;
    FastVecSub(direction, initialNext, points);
    vec_scale_to_length(direction, direction, 1.0f);
    FastVecSub(facing, D_L11_001BA8C0, points);
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
        FastVecSub(facing, D_L11_001BA8C0, points[i]);
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
        u = D_L11_001B05E0*IntToFloat(i);
        next = u+D_L11_001B05E0;
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
