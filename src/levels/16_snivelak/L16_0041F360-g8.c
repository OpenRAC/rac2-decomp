#include "common.h"
typedef int quad __attribute__((mode(TI)));
typedef union { quad q; struct { f32 x, y, z, w; } v; } RingPoint;
extern f32 g_ribbon_inner_uv_start __attribute__((sda));
extern u32 g_ribbon_l16_inner_color __attribute__((sda));
extern s32 g_ribbon_l16_param_a __attribute__((sda));
extern u32 g_ribbon_l16_outer_color[] MACRO_ADDR;
extern s32 g_ribbon_l16_param_b[] MACRO_ADDR;
extern f32 g_ribbon_inner_uv_end[] MACRO_ADDR;
extern f32 g_ribbon_outer_uv_start[] MACRO_ADDR;
extern f32 g_ribbon_outer_uv_end[] MACRO_ADDR;
extern RingPoint g_particle_template MACRO_ADDR;
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern void FastVecAdd(char *, char *, char *);
/* Integer-bank order: request, owner, flags, vector; independent f12: distance. */
extern void make_hit_descriptor(char *, char *, s32, char *, f32);
extern s32 CollLine(char *, char *, s32, char *, char *);
extern u32 FastTweenColor(u32, u32, f32);
extern void DrawTwoLayerPolylineRibbon(char *, s32, s32, s32, u32, u32, f32, f32, f32);

/* Constructs and clips the expanding ring, then draws its two surfaces. */
void SweepAndDrawRibbonRing(char *self) {
    RingPoint points[33];
    RingPoint *point;
    /* The query copies 40 bytes. Retail initializes through +0x23 here;
     * +0x24..+0x27 is transported opaquely to the queue, not assumed padding. */
    char collision[48];
    char *st = *(char **)(self + 0x68);
    f32 angle;
    u32 inner, outer;
    s32 i, j, k;
    for (i = 0, point = points; i < 32; i++, point++) {
        angle = (f32)(i << 1) * 0.09817477315664291f - 3.141592741012573f;
        point->v.x = math_fast_sin_or_cos_a(angle) * *(f32 *)(st + 0x2C);
        point->v.y = math_fast_sin_or_cos_b(angle) * *(f32 *)(st + 0x2C);
        point->v.z = 0;
        FastVecAdd((char *)point, (char *)point, self + 0x10);
        point->v.w = g_ribbon_inner_uv_start;
    }
    qcopy(&points[32], &points[0]);
    for (j = 0; j < 32; j++) {
        make_hit_descriptor(collision, self, 1, (char *)&g_particle_template, *(f32 *)(st + 0x28));
        collision[24] = 0;
        collision[25] = 1;
        *(u16 *)(collision + 26) = *(u16 *)(self + 0xAA);
        CollLine((char *)&points[j], (char *)&points[j + 1], 9, self, collision);
    }
    inner = FastTweenColor(g_ribbon_l16_inner_color & 0xFFFFFF, g_ribbon_l16_inner_color, *(f32 *)(st + 0x30));
    outer = FastTweenColor(g_ribbon_l16_outer_color[0] & 0xFFFFFF, g_ribbon_l16_outer_color[0], *(f32 *)(st + 0x30));
    DrawTwoLayerPolylineRibbon((char *)points, g_ribbon_l16_param_a, g_ribbon_l16_param_b[0], 33, inner, outer,
                      g_ribbon_inner_uv_start, g_ribbon_inner_uv_end[0], *(f32 *)(st + 0x34));
    for (k = 31; k >= 0; k--) points[k].v.w = g_ribbon_outer_uv_start[0];
    DrawTwoLayerPolylineRibbon((char *)points, g_ribbon_l16_param_a, g_ribbon_l16_param_b[0], 33, inner, outer,
                      g_ribbon_outer_uv_start[0], g_ribbon_outer_uv_end[0], -*(f32 *)(st + 0x34));
}
