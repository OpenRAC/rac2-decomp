#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword bits; float f[4]; } Vector4;
typedef struct {
    Vector4 point[4];
    unsigned int color[4];
    float uv[8];
    unsigned long tag, tex, alpha, test;
} Beam;

extern void func_00281DE8(void *, int, int, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00280B90(void *, void *, int);
extern Vector4 D_L00_001B8DC0;

/* Draw two camera-facing ribbon strips over the supplied polyline. */
void func_L00_002EBE88(Vector4 *points, int texture0, int texture1, int count, unsigned int color0, unsigned int color1, float unused, float scale, float u)
{
    Beam first, second;
    Vector4 cross, offset, cameraDelta, segment;
    int i;
    float zero;
    func_00281DE8(&first, texture0, 1, 0x80);
    first.color[0] = first.color[1] = first.color[2] = first.color[3] = color0;
    /* Initialize the UV word as bits, then reuse its floating value. */
    *(int *)&first.uv[0] = 0;
    zero = first.uv[0];
    first.uv[1] = 0; first.uv[3] = 1; first.uv[5] = 0; first.uv[7] = 1;
    first.uv[2] = u; first.uv[0] = u; first.uv[6] = u + 1; first.uv[4] = u + 1;
    func_00281DE8(&second, texture1, 1, 0x80);
    second.color[0] = second.color[1] = second.color[2] = second.color[3] = color1;
    second.uv[5] = second.uv[1] = zero; second.uv[7] = second.uv[3] = 1;
    second.uv[0] = second.uv[2] = u; second.uv[4] = second.uv[6] = u + 1;
    FastVecSub(&cameraDelta, points, &D_L00_001B8DC0);
    FastVecSub(&segment, points + 1, points);
    FastVecCross(&cross, &segment, &cameraDelta);
    vec_scale_to_length(&offset, &cross, points[0].f[3]);
    FastVecAdd(&first.point[0], points, &offset);
    FastVecSub(&first.point[1], points, &offset);
    FastVecScale(&offset, &offset, scale);
    FastVecAdd(&second.point[0], points, &offset);
    FastVecSub(&second.point[1], points, &offset);
    for (i = 1; i < count; i++) {
        FastVecSub(&cameraDelta, points + i, &D_L00_001B8DC0);
        FastVecSub(&segment, points + i, points + i - 1);
        FastVecCross(&cross, &segment, &cameraDelta);
        vec_scale_to_length(&offset, &cross, points[i].f[3]);
        FastVecAdd(&first.point[2], points + i, &offset);
        FastVecSub(&first.point[3], points + i, &offset);
        FastVecScale(&offset, &offset, scale);
        FastVecAdd(&second.point[2], points + i, &offset);
        FastVecSub(&second.point[3], points + i, &offset);
        draw_world_quad(&first, 0, 0); draw_world_quad(&second, 0, 0);
        qcopy(&first.point[0], &first.point[2]); qcopy(&first.point[1], &first.point[3]);
        qcopy(&second.point[0], &second.point[2]); qcopy(&second.point[1], &second.point[3]);
    }
}
