#include "common.h"

typedef struct { float x, y, z, w; } MmiPoint;
typedef float TrailVector[4] __attribute__((aligned(16)));
typedef char PointExtent[sizeof(MmiPoint) == 16 ? 1 : -1];
extern char *moby_get_private_value_4(u8 *);
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
extern float g_trail_size_max __attribute__((sda));
extern float g_trail_l00_speed_max __attribute__((sda));
extern float g_trail_speed_alt_min NOT_SDA;
extern float g_trail_speed_alt_max __attribute__((sda));
extern float g_trail_from_height_max __attribute__((sda));
extern float g_trail_to_height_min __attribute__((sda));
extern float g_trail_to_height_max __attribute__((sda));
extern int g_trail_duration_max __attribute__((sda));

/* The sampler clamps n to its limit and writes only output[0..n-1]. The
 * constructor consumes all four floats from each endpoint, including size w.
 * Sampled position w is not guaranteed initialized: the constructor transfers
 * it, but the family-2 update adds XYZ only and the normal renderer replaces
 * the output w with zero before consumption. No extra initialization is added.
 * Retail performs the initial zero-z and randomized-w stores before later
 * overwrites; its RNG calls and actual writes are retained without qualifiers.
 * The second radial lower bound is absolute, including at the RNG call site:
 * NOT_SDA plus the standard no-split-addresses profile retains that access. */
/* Spawns a spray of short trails along the points of an object's model. */
void part_spawn_model_trails(unsigned char *object, const unsigned char *info, float opacity)
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
        speed = math_random_float_range(D_L00_001B0670_gp, g_trail_l00_speed_max) * 0.01666666753590107f;
        from[0] = math_fast_sin_or_cos_a(angle) * speed;
        from[1] = math_fast_sin_or_cos_b(angle) * speed;
        from[2] = 0.0f;
        from[2] = math_random_float_range(D_L00_001B0680_gp, g_trail_from_height_max) * 0.01666666753590107f;
        from[3] = math_random_float_range(0.1f, 0.2f);
        angle = FastAddRotations(angle, math_random_float_range(120.0f, 240.0f) * 0.01745329424738884f);
        speed = math_random_float_range(g_trail_speed_alt_min, g_trail_speed_alt_max) * 0.01666666753590107f;
        to[0] = math_fast_sin_or_cos_a(angle) * speed;
        to[1] = math_fast_sin_or_cos_b(angle) * speed;
        to[2] = 0.0f;
        to[2] = math_random_float_range(g_trail_to_height_min, g_trail_to_height_max) * 0.01666666753590107f;
        to[3] = math_random_float_range(0.1f, 0.2f);
        size = math_random_float_range(D_L00_001B0668_gp, g_trail_size_max);
        to[3] = from[3] = size;
        original = *(const u32 *)info;
        color = (int)FastTweenColor((original & 0xFFFFFF) | 0x10000000, original, opacity);
        end_color = *(const int *)(info + 8);
        duration = math_random_int_range(D_L00_001B0690_gp, g_trail_duration_max);
        part_spawn_trail(&points[i], from, to, color, end_color, 5, duration, 10, D_L00_001B0664_gp);
    }
}
