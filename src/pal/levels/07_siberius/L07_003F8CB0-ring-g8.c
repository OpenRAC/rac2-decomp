#include "include_asm.h"

#include "common.h"

/* func_PAL_L07_003F8CB0, the PAL copy of func_L07_003F4578: the same C, where the step scale
   0.0166667f becomes 0.020000001f, `size` takes the 50 Hz scale and the particle call is
   func_PAL_002C23B8. The extra divisor register leaves two pointers spilled instead of one;
   `step_out` holds the address of `step` in a named local declared before `position`, which
   gives it the lower pseudo number and so the first of the two stack slots, as in retail.

   It reads its parameters through $gp, so it has a -G8 unit of its own.
   D_L07_001B0E78_4 is the absolute (macro) form of D_L07_001B0E78's address; retail
   reads E78 through $gp and E7C through lui. `next` takes both the quotient and the
   remainder of `% 32` (expand_divmod's target), which leaves that chain to global-alloc
   as in retail. */

typedef union { s32 q __attribute__((mode(TI))); f32 f[4]; } Vector;
typedef struct {
    Vector direction;
    u8 *owner;
    s32 flags;
    u8 type, count;
    u16 classId;
    f32 amount;
    s32 mode;
    f32 extra;
} Query;
typedef struct {
    Vector points[33];
    union { Query query; struct { Vector point, direction; } particle; } work;
} Frame;
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void make_hit_descriptor(void *, void *, s32, void *, f32);
extern s32 CollLine(void *, void *, s32, void *, void *);
extern u32 FastTweenColor(u32, u32, f32);
extern void DrawTwoLayerPolylineRibbon(void *, s32, s32, s32, u32, u32, f32, f32, f32);
extern s32 level_is_resident_flag_clear(void);
extern s32 math_random_int_range(s32, s32);
extern f32 math_random_signed_float_range(f32, f32);
extern s32 FloatToInt(f32);
extern f32 math_random_float_range(f32, f32);
extern f32 ApproachValue(f32 *, f32, f32);
extern s32 math_random_int_below(s32);
extern void lerp_vector(void *, void *, void *, f32);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void *part_spawn_burst_pal(void *, void *, s32, s32, s32, s32, f32, f32, f32, f32, f32);
extern u8 g_default_hit_direction[] MACRO_ADDR;
extern s32 g_ring_particle_density __attribute__((sda));
extern u32 g_trail_particle_color __attribute__((sda));
extern s32 g_trail_size_range[] __attribute__((sda));
extern f32 g_trail_growth_rate __attribute__((sda));
extern f32 g_trail_life_range __attribute__((sda));
extern f32 D_L07_001B0E78_4[] MACRO_ADDR;
extern u32 g_ring_color_a __attribute__((sda));
extern u32 g_ring_color_b;
extern s32 g_ring_ribbon_layer_a __attribute__((sda));
extern s32 g_ring_ribbon_layer_b;
extern f32 g_ring_edge_param_a __attribute__((sda));
extern f32 g_ring_edge_param_b;

/* Sample a closed ring, perform its collision passes, then emit its particles. */
void UpdateCollisionRing_pal(u8 *moby)
{
    Frame frame;
    u8 *vars = *(u8 **)(moby + 0x68);
    f32 *step_out;
    u8 *position = moby + 0x10;
    s32 i, j, k, segment, next, size, count;
    u32 color0, color1, color;
    f32 angle, life, step;

    for (i = 0; i < 32; i++) {
        angle = (f32)(i * 2) * 0.09817477f - 3.1415927f;
        frame.points[i].f[0] = math_fast_sin_or_cos_a(angle) * *(f32 *)(vars + 0x24);
        frame.points[i].f[1] = math_fast_sin_or_cos_b(angle) * *(f32 *)(vars + 0x24);
        frame.points[i].f[2] = 0.0f;
        if (*(u8 **)(vars + 0x20) != 0)
            matrix_mul_vec3(&frame.points[i], &frame.points[i], *(u8 **)(vars + 0x20) + 0xC0);
        FastVecAdd(&frame.points[i], &frame.points[i], moby + 0x10);
        frame.points[i].f[3] = g_ring_edge_param_a;
    }
    qcopy(&frame.points[32], &frame.points[0]);
    for (j = 0; j < 32; j++) {
        make_hit_descriptor(&frame.work.query, moby, 1, g_default_hit_direction, *(f32 *)(vars + 0x34));
        frame.work.query.type = 0;
        frame.work.query.count = 1;
        frame.work.query.classId = *(u16 *)(moby + 0xAA);
        CollLine(&frame.points[j], &frame.points[j + 1], 9, moby, &frame.work.query);
    }
    color0 = FastTweenColor(g_ring_color_a & 0xFFFFFF, g_ring_color_a, *(f32 *)(vars + 0x28));
    color1 = FastTweenColor(g_ring_color_b & 0xFFFFFF, g_ring_color_b, *(f32 *)(vars + 0x28));
    DrawTwoLayerPolylineRibbon(frame.points, g_ring_ribbon_layer_a, g_ring_ribbon_layer_b, 33,
                     color0, color1, g_ring_edge_param_a, g_ring_edge_param_b, *(f32 *)(vars + 0x2C));
    if (!level_is_resident_flag_clear())
        return;
    for (k = 0; (f32)k < (f32)g_ring_particle_density * *(f32 *)(vars + 0x24); k++) {
        size = ((s32)math_random_int_range(g_trail_size_range[0], g_trail_size_range[1]) * 5 + 2) / 6;
        count = FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
        life = math_random_float_range(g_trail_life_range, D_L07_001B0E78_4[1]) * 210000.0f;
        step = g_trail_growth_rate * 0.020000001f;
        step_out = &step;
        ApproachValue(step_out, 0.0f, math_random_float_range(0.0f, 2.0f) * 0.020000001f);
        segment = math_random_int_below(32);
        next = (segment + 1) % 32;
        lerp_vector(&frame.work.particle.point, &frame.points[segment],
                     &frame.points[next], math_random_float_range(0.0f, 1.0f));
        FastVecSub(&frame.work.particle.direction, &frame.work.particle.point, position);
        frame.work.particle.direction.f[2] = 0.0f;
        vec_scale_to_length(&frame.work.particle.direction, &frame.work.particle.direction, step);
        frame.work.particle.point.f[3] = 2.0f;
        color = g_trail_particle_color;
        FastTweenColor(color & 0xFFFFFF, color, *(f32 *)(vars + 0x28));
        part_spawn_burst_pal(&frame.work.particle.point, &frame.work.particle.direction,
                     size, (s32)color >> 24, color & 0xFFFFFF,
                     count, life, 500.0f, 1.0f, 0.0f, 1.0f);
    }
}
