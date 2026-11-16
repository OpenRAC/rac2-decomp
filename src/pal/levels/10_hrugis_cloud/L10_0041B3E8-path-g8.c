#include "include_asm.h"

#include "common.h"
typedef struct {
    u8 pad[0x2C8];
    u8 *child;
} HrugisPathState;
typedef int TI128 __attribute__((mode(TI)));
extern u8 *SpawnFreeLevelObjectById_pal(s32, s32);
extern f32 fast_vec_dist(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void FastVecCross(void *, void *, void *);
extern void FastVecScale(void *, void *, f32);
extern f32 math_ease_out_quad(f32);
extern f32 math_closest_point_on_segment(void *, void *, void *, void *);
extern u8 *g_curve_point_records MACRO_ADDR;
extern u8 g_mission_state[];
extern f32 g_child_curve_distance NOT_SDA;
extern s32 g_boss_flag_a __attribute__((sda));

void hrugis_launch_child_on_curve_pal(u8 *obj) {
    f32 up[4] __attribute__((aligned(16)));
    f32 delta[4] __attribute__((aligned(16)));
    f32 scaled[4] __attribute__((aligned(16)));
    f32 closest[4] __attribute__((aligned(16)));
    f32 correction[4] __attribute__((aligned(16)));
    u8 *s = *(u8 **)(obj + 0x68);
    u8 *best, *p, *target, *childpos;
    s32 *index;
    f32 distance, d, scale;
    s32 i;
    *(TI128 *)up = 0;
    up[2] = 1.0f;
    if (((HrugisPathState *)s)->child) return;
    p = SpawnFreeLevelObjectById_pal(0xF8D, 1);
    ((HrugisPathState *)s)->child = p;
    distance = g_child_curve_distance;
    best = 0;
    for (index = (s32 *)(s + 0x2A0), i = 3; i >= 0; i--, index++) {
        p = g_curve_point_records + *index * 128;
        d = fast_vec_dist(p + 0x30, obj + 0x10);
        if (d < distance) {
            distance = d;
            best = p;
        }
    }
    if (!best) return;
    target = g_curve_point_records + *(s32 *)g_mission_state * 128;
    childpos = ((HrugisPathState *)s)->child + 0x10;
    qcopy(childpos, best + 0x30);
    FastVecSub(delta, target + 0x30, childpos);
    delta[3] = 0;
    vec_scale_to_length(((HrugisPathState *)s)->child + 0xC0, delta, 1.0f);
    FastVecCross(((HrugisPathState *)s)->child + 0xD0, ((HrugisPathState *)s)->child + 0xC0, up);
    *(s32 *)(((HrugisPathState *)s)->child + 0xDC) = 0;
    vec_scale_to_length(((HrugisPathState *)s)->child + 0xD0, ((HrugisPathState *)s)->child + 0xD0, 1.0f);
    FastVecCross(((HrugisPathState *)s)->child + 0xE0, ((HrugisPathState *)s)->child + 0xD0, ((HrugisPathState *)s)->child + 0xC0);
    *(s32 *)(((HrugisPathState *)s)->child + 0xEC) = 0;
    /* Retail keeps the saved position pointer live across these copies. */
    qcopy_nc(s + 0x260, ((HrugisPathState *)s)->child + 0x10);
    qcopy_nc(s + 0x270, obj + 0x10);
    d = fast_vec_dist(s + 0x260, s + 0x270);
    scale = math_ease_out_quad(d * 0.001953129889f) * 160.0f;
    vec_scale_to_length(scaled, delta, scale);
    FastVecAdd(s + 0x280, scaled, s + 0x260);
    math_closest_point_on_segment(closest, s + 0x260, s + 0x270, s + 0x280);
    FastVecSub(correction, s + 0x280, closest);
    FastVecScale(correction, correction, -1.0f);
    FastVecAdd(s + 0x280, closest, correction);
    FastVecSub(delta, target + 0x30, s + 0x270);
    vec_scale_to_length(scaled, delta, scale);
    FastVecAdd(s + 0x290, scaled, s + 0x270);
    math_closest_point_on_segment(closest, s + 0x260, s + 0x270, s + 0x290);
    FastVecSub(correction, s + 0x290, closest);
    FastVecScale(correction, correction, -1.0f);
    FastVecAdd(s + 0x290, closest, correction);
    FastVecSub(delta, s + 0x260, s + 0x270);
    vec_scale_to_length(scaled, delta, 8.0f);
    FastVecAdd(s + 0x270, scaled, s + 0x270);
    *(s32 *)(s + 0x2D4) = 0;
    *(f32 *)(s + 0x2D8) = 0.013962637f;
    g_boss_flag_a = 1;
}
