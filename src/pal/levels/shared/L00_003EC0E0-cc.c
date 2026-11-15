#include "names.h"
/* func_PAL_L00_003EC0E0, the PAL copy of func_L00_003E7E40: the same C, where wrap *(const int *)(info + 8) (((int)({e}) * 5 + 2) / 6); lit 10 becomes 8; rewrap func_002A7820(D_L00_001B0690_gp, D_L00_001B0694). */
#include "common.h"

typedef struct { float x, y, z, w; } MmiPoint;
typedef float TrailVector[4] __attribute__((aligned(16)));
extern s32 moby_get_private_value_4(u8 *);
extern int coll_scatter_points_in_shapes(float, char *, int, MmiPoint *, int);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float FastAddRotations(float, float);
extern u32 FastTweenColor(u32, u32, float);
extern int math_random_int_range(int, int);
extern void *part_spawn_trail(void *, float *, float *, int, int, int, int, int, int);
extern float D_L00_001B0660_gp SDATA(D_L00_001B0660);
extern int D_L00_001B0664_gp SDATA(D_L00_001B0664);
extern float D_L00_001B0668_gp SDATA(D_L00_001B0668);
extern float D_L00_001B0670_gp SDATA(D_L00_001B0670);
extern float D_L00_001B0680_gp SDATA(D_L00_001B0680);
extern int D_L00_001B0690_gp SDATA(D_L00_001B0690);
extern float D_L00_001B066C __attribute__((sda));
extern float D_L00_001B0674 __attribute__((sda));
extern float D_L00_001B0678 NOT_SDA;
extern float D_L00_001B067C __attribute__((sda));
extern float D_L00_001B0684 __attribute__((sda));
extern float D_L00_001B0688 __attribute__((sda));
extern float D_L00_001B068C __attribute__((sda));
extern int D_L00_001B0694 __attribute__((sda));

/* The sampler clamps n to its limit and writes only output[0..n-1]. The
 * constructor consumes all four floats from each endpoint, including size w.
 * Sampled position w is not guaranteed initialized: the constructor transfers
 * it, but the family-2 update adds XYZ only and the normal renderer replaces
 * the output w with zero before consumption. No extra initialization is added.
 * Retail performs the initial zero-z and randomized-w stores before later
 * overwrites; its RNG calls and actual writes are retained without qualifiers.
 * The second radial lower bound is absolute, including at the RNG call site:
 * NOT_SDA plus the standard no-split-addresses profile retains that access. */
void func_PAL_L00_003EC0E0(unsigned char *object, const unsigned char *info, float opacity)
{
    MmiPoint points[32] __attribute__((aligned(16)));
    TrailVector from, to;
    const unsigned char *model;
    float angle, speed, size;
    u32 original;
    int count, i, color, end_color, duration;
    model = (const unsigned char *)moby_get_private_value_4(object);
    if (model == 0)
        return;
    count = coll_scatter_points_in_shapes(D_L00_001B0660_gp, (char *)object, 32, points, model[0x19]);
    for (i = 0; i < count; i++) {
        angle = math_random_angle();
        speed = math_random_float_range(D_L00_001B0670_gp, D_L00_001B0674) * 0.020000001f;
        from[0] = math_fast_sin_or_cos_a(angle) * speed;
        from[1] = math_fast_sin_or_cos_b(angle) * speed;
        from[2] = 0.0f;
        from[2] = math_random_float_range(D_L00_001B0680_gp, D_L00_001B0684) * 0.020000001f;
        from[3] = math_random_float_range(0.1f, 0.2f);
        angle = FastAddRotations(angle, math_random_float_range(120.0f, 240.0f) * 0.01745329424738884f);
        speed = math_random_float_range(D_L00_001B0678, D_L00_001B067C) * 0.020000001f;
        to[0] = math_fast_sin_or_cos_a(angle) * speed;
        to[1] = math_fast_sin_or_cos_b(angle) * speed;
        to[2] = 0.0f;
        to[2] = math_random_float_range(D_L00_001B0688, D_L00_001B068C) * 0.020000001f;
        to[3] = math_random_float_range(0.1f, 0.2f);
        size = math_random_float_range(D_L00_001B0668_gp, D_L00_001B066C);
        to[3] = from[3] = size;
        original = *(const u32 *)info;
        color = (int)FastTweenColor((original & 0xFFFFFF) | 0x10000000, original, opacity);
        end_color = *(const int *)(info + 8);
        duration = (((int)(math_random_int_range(D_L00_001B0690_gp, D_L00_001B0694)) * 5 + 2) / 6);
        part_spawn_trail(&points[i], from, to, color, end_color, 4, duration, 8, D_L00_001B0664_gp);
    }
}
