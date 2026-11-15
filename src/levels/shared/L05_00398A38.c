#include "common.h"

typedef int Quad98A __attribute__((mode(TI)));
typedef union {
    Quad98A q;
    float f[4];
} Vec98A;

typedef struct {
    Vec98A p[4];
    int color[4];
    float uv[8];
    u64 zero, texture, mode, primitive;
} Ribbon98A;

extern u64 GetEffectTextureDescriptor(int);
extern void beam_extend_trail_point(void *, int);
extern void transform_reset_record(void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern void transform_vector(void *, void *, void *);
extern void draw_world_quad(void *, int, int);
extern float IntToFloat(int);
extern char D_L05_001B96C0[];

/* Draw two textured strips along the points, scrolling the wider strip's U coordinate. */
/* Draws a two-layer scrolling ribbon through a list of points, one band at a time. */
void DrawScrollingTwoLayerRibbon(char *obj, int count, Vec98A *points, int n)
{
    Ribbon98A inner, outer;
    Vec98A tangent, view, right, pos, thin, wide;
    int color = 0x80ff4000;
    char *data = *(char **)(obj + 0x68);
    float u, v;

    if (*(int *)(data + 0x24))
        color = 0x800040ff;
    inner.texture = GetEffectTextureDescriptor(43);
    inner.mode = 0xff9000000260ULL;
    inner.primitive = ((u64)count << 32) | 0x68;
    inner.color[1] = 0x7fffffff;
    inner.color[0] = 0x7fffffff;
    inner.zero = 0;
    outer.texture = GetEffectTextureDescriptor(43);
    outer.mode = 0xff9000000260ULL;
    outer.zero = 0;
    outer.primitive = ((u64)(count / 3) << 32) | 0x68;
    thin.q = 0;
    wide.q = 0;
    thin.f[2] = 0.04f;
    wide.f[2] = 0.16f;
    inner.color[1] = color;
    outer.color[0] = color;
    thin.f[3] = 1.0f;
    wide.f[3] = 1.0f;
    beam_extend_trail_point(points, n);
    transform_reset_record(&inner);
    transform_reset_record(&outer);
    inner.uv[0] = 0;
    inner.uv[1] = 0;
    inner.uv[2] = 0;
    inner.uv[3] = 1;
    inner.uv[4] = 1;
    inner.uv[5] = 0;
    inner.uv[6] = 1;
    inner.uv[7] = 1;
    outer.uv[0] = 0;
    outer.uv[1] = 0;
    outer.uv[2] = 0;
    outer.uv[3] = 1;
    outer.uv[4] = 0.33f;
    outer.uv[5] = 0;
    outer.uv[6] = 0.33f;
    outer.uv[7] = 1;
    FastVecSub(&tangent, points + 1, points);
    vec_scale_to_length(&tangent, &tangent, 1.0f);
    FastVecSub(&view, D_L05_001B96C0, points);
    FastVecCross(&right, &view, &tangent);
    vec_scale_to_length(&right, &right, 1.0f);
    FastVecCross(&view, &tangent, &right);
    qcopy(&pos, points);
    qcopy(&inner.p[0], &thin);
    FastVecScale(&inner.p[1], &inner.p[0], -1.0f);
    transform_vector(&inner.p[0], &inner.p[0], &tangent);
    transform_vector(&inner.p[1], &inner.p[1], &tangent);
    qcopy(&outer.p[0], &wide);
    FastVecScale(&outer.p[1], &outer.p[0], -1.0f);
    transform_vector(&outer.p[0], &outer.p[0], &tangent);
    transform_vector(&outer.p[1], &outer.p[1], &tangent);
    {
        int i;

        for (i = 1; i < n - 1; i++) {
            Vec98A *following = points + (i + 1);
            Vec98A *current = points + i;

            qcopy(&inner.p[2], &thin);
            FastVecScale(&inner.p[3], &inner.p[2], -1.0f);
            qcopy(&outer.p[2], &wide);
            FastVecScale(&outer.p[3], &outer.p[2], -1.0f);
            FastVecSub(&tangent, following, current);
            vec_scale_to_length(&tangent, &tangent, 1.0f);
            FastVecSub(&view, D_L05_001B96C0, current);
            FastVecCross(&right, &view, &tangent);
            vec_scale_to_length(&right, &right, 1.0f);
            FastVecCross(&view, &tangent, &right);
            qcopy(&pos, current);
            transform_vector(&inner.p[2], &inner.p[2], &tangent);
            transform_vector(&inner.p[3], &inner.p[3], &tangent);
            transform_vector(&outer.p[2], &outer.p[2], &tangent);
            transform_vector(&outer.p[3], &outer.p[3], &tangent);
            inner.color[3] = 0x7f7f7f7f;
            inner.color[2] = 0x7f7f7f7f;
            outer.color[3] = color;
            outer.color[2] = color;
            draw_world_quad(&inner, 0, 0);
            draw_world_quad(&outer, 0, 0);
            u = IntToFloat(i) * 0.33f;
            v = u + 0.33f;
            if (u >= 1.0f) {
                u -= 1.0f;
                v -= 1.0f;
            }
            outer.uv[0] = u;
            outer.uv[4] = v;
            outer.uv[2] = u;
            outer.uv[6] = v;
            qcopy(&inner.p[0], &inner.p[2]);
            qcopy(&inner.p[1], &inner.p[3]);
            qcopy(&outer.p[0], &outer.p[2]);
            qcopy(&outer.p[1], &outer.p[3]);
        }
    }
}
