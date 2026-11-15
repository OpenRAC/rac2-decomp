#include "common.h"

typedef int Quad128 __attribute__((mode(TI)));

typedef struct {
    u8 pad[0x70];
    long f70, f78, f80, f88;
} QuadPacket;

typedef struct {
    Quad128 vertices[4];
    unsigned int colors[4];
    float uv[4][2];
    long header[4];
} RibbonPayload;

typedef union {
    QuadPacket raw;
    RibbonPayload view;
} RibbonPacket;

extern void func_00281DE8(QuadPacket *, int, int, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern void func_00280B90(void *, void *, int);
extern char D_L00_001B8DC0[];

/* Draws two fading textured ribbons along a list of weighted points. */
void func_L00_0041F820(Quad128 *points, int firstTexture, int secondTexture, int count,
                       unsigned int firstColor, unsigned int secondColor, float unused,
                       float width, float uv)
{
    struct {
        RibbonPacket first, second;
        Quad128 side, offset, eye, tangent;
    } frame;

    int index, alpha;
    float fade, zero;
    unsigned int firstAlpha = firstColor >> 24, secondAlpha = secondColor >> 24;

    func_00281DE8(&frame.first.raw, firstTexture, 1, 128);
    /* Clear the template U word before capturing its float zero. */
    *(u32 *)&frame.first.view.uv[0][0] = 0;
    zero = frame.first.view.uv[0][0];
    frame.first.view.colors[3] = firstColor;
    frame.first.view.colors[2] = firstColor;
    frame.first.view.colors[1] = firstColor;
    frame.first.view.colors[0] = firstColor;
    frame.first.view.uv[0][1] = 0;
    frame.first.view.uv[1][1] = 1;
    frame.first.view.uv[2][1] = 0;
    frame.first.view.uv[3][1] = 1;
    frame.first.view.uv[1][0] = uv;
    frame.first.view.uv[0][0] = uv;
    frame.first.view.uv[3][0] = uv + 1;
    frame.first.view.uv[2][0] = uv + 1;

    func_00281DE8(&frame.second.raw, secondTexture, 1, 128);
    frame.second.view.colors[3] = secondColor;
    frame.second.view.colors[2] = secondColor;
    frame.second.view.colors[1] = secondColor;
    frame.second.view.colors[0] = secondColor;
    frame.second.view.uv[0][1] = zero;
    frame.second.view.uv[1][1] = 1;
    frame.second.view.uv[1][0] = uv;
    frame.second.view.uv[3][0] = uv + 1;
    frame.second.view.uv[2][1] = zero;
    frame.second.view.uv[3][1] = 1;
    frame.second.view.uv[0][0] = uv;
    frame.second.view.uv[2][0] = uv + 1;

    FastVecSub(&frame.eye, points, D_L00_001B8DC0);
    FastVecSub(&frame.tangent, points + 1, points);
    FastVecCross(&frame.side, &frame.tangent, &frame.eye);
    vec_scale_to_length(&frame.offset, &frame.side, ((float *)points)[3]);
    FastVecAdd(&frame.first.view.vertices[0], points, &frame.offset);
    FastVecSub(&frame.first.view.vertices[1], points, &frame.offset);
    FastVecScale(&frame.offset, &frame.offset, width);
    FastVecAdd(&frame.second.view.vertices[0], points, &frame.offset);
    FastVecSub(&frame.second.view.vertices[1], points, &frame.offset);

    for (index = 1; index < count; index++) {
        FastVecSub(&frame.eye, &points[index], D_L00_001B8DC0);
        FastVecSub(&frame.tangent, &points[index], &points[index - 1]);
        FastVecCross(&frame.side, &frame.tangent, &frame.eye);
        vec_scale_to_length(&frame.offset, &frame.side, ((float *)&points[index])[3]);
        FastVecAdd(&frame.first.view.vertices[2], &points[index], &frame.offset);
        FastVecSub(&frame.first.view.vertices[3], &points[index], &frame.offset);
        FastVecScale(&frame.offset, &frame.offset, width);
        FastVecAdd(&frame.second.view.vertices[2], &points[index], &frame.offset);
        FastVecSub(&frame.second.view.vertices[3], &points[index], &frame.offset);

        fade = 1.0f - IntToFloat(index) / IntToFloat(count);
        alpha = FloatToInt(IntToFloat(firstAlpha) * fade);
        frame.first.view.colors[3] = FastTweenColor(0x1010ff, firstColor & 0xffffff, fade) |
                                     ((unsigned int)alpha << 24);
        frame.first.view.colors[2] = frame.first.view.colors[3];
        alpha = FloatToInt(IntToFloat(secondAlpha) * fade);
        frame.second.view.colors[3] = FastTweenColor(0x1010ff, secondColor & 0xffffff, fade) |
                                      ((unsigned int)alpha << 24);
        frame.second.view.colors[2] = frame.second.view.colors[3];

        draw_world_quad(&frame.first, 0, 0);
        draw_world_quad(&frame.second, 0, 0);

        qcopy(&frame.first.view.vertices[0], &frame.first.view.vertices[2]);
        qcopy(&frame.first.view.vertices[1], &frame.first.view.vertices[3]);
        qcopy(&frame.second.view.vertices[0], &frame.second.view.vertices[2]);
        qcopy(&frame.second.view.vertices[1], &frame.second.view.vertices[3]);
        frame.first.view.colors[0] = frame.first.view.colors[2];
        frame.first.view.colors[1] = frame.first.view.colors[3];
        frame.second.view.colors[0] = frame.second.view.colors[2];
        frame.second.view.colors[1] = frame.second.view.colors[3];
    }
}
