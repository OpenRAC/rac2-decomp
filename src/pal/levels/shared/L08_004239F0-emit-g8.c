#include "common.h"

/* func_PAL_L08_004239F0, the PAL copy of func_L08_0041E790, written as func_PAL_L08_003CA1C8: 1/60 becomes 1/50, the
 * three func_00283CF0 arguments take the 50 Hz scale, and the acceleration address sits in a local set
 * before the rise term: its longer life keeps loop.c hoisting it past the nine extra scale insns. */

/* Built with -fno-gcse and -g: PRE would hoist object+0xC0 out of the loop, and -g gives the
 * nops before the div.s pairs. The acceleration clear is qzero_nc: cse forgets the frame
 * addresses there, so the constructor call builds them again, as retail does. */

typedef int ParticleQuad __attribute__((mode(TI)));
typedef union { ParticleQuad q; float f[4]; } ParticleVector;
extern int g_ring_l08_color_start __attribute__((sda)), g_ring_l08_color_end __attribute__((sda));
extern int g_ring_l08_color_start_2 __attribute__((sda)), g_ring_l08_color_end_2 __attribute__((sda));
extern float g_ring_red_min __attribute__((sda)), g_ring_red_max __attribute__((sda));
extern float g_ring_green_min __attribute__((sda)), g_ring_green_max __attribute__((sda));
extern float g_ring_blue_min __attribute__((sda)), g_ring_blue_max __attribute__((sda));
extern float g_ring_speed_min_divisor __attribute__((sda)), g_ring_rise_min_divisor __attribute__((sda));
extern float g_ring_boost_scale __attribute__((sda)), g_ring_height_offset __attribute__((sda));
extern int GetCollHitMaterial(void), func_001163B0(void);
extern float math_random_float_range(float, float), math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern float FastVecLength(void *);
extern void matrix_mul_vec3(void *, void *, void *), vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int FloatToInt(float);
extern unsigned char *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);

/* Emit two-ended particles from a transformed disk around the object. */
/* Spawns a burst of small particles that fly outward from a point in a ring, rising and shrinking as they go (PAL: 50 Hz speeds). */
void part_spawn_ring_pal(char *object, void *position, int count,
                      float speed, float rise, float outer_radius, float inner_radius,
                      float start_scale, float end_scale)
{
    struct { ParticleVector offset, velocity, acceleration, inherited; } frame;
    char *state = *(char **)(object + 0x68);
    int start_color = g_ring_l08_color_start;
    int end_color = g_ring_l08_color_end;
    int n;
    float component, length, magnitude;
    int kind, duration, size;
    unsigned char *particle;
    ParticleVector *acceleration;

    if (!GetCollHitMaterial()) {
        start_color = g_ring_l08_color_start_2;
        end_color = g_ring_l08_color_end_2;
    }
    if (count > 0) {
        n = count;
        do {
        frame.offset.f[0] = math_fast_sin_or_cos_a(math_random_float_range(-3.1415927410125732f, 3.1415927410125732f))
            * math_random_float_range(inner_radius, outer_radius);
        component = math_fast_sin_or_cos_b(math_random_float_range(-3.1415927410125732f, 3.1415927410125732f));
        component *= math_random_float_range(inner_radius, outer_radius);
        frame.offset.f[1] = component;
        frame.offset.f[2] = 0.0f;
        matrix_mul_vec3(&frame.offset, &frame.offset, object + 0xC0);
        length = FastVecLength(&frame.offset);
        magnitude = speed * ((outer_radius - length) * 0.020000001f) / outer_radius;
        vec_scale_to_length(&frame.velocity, &frame.offset,
                     math_random_float_range(magnitude / g_ring_speed_min_divisor, magnitude));
        frame.inherited.q = *(ParticleQuad *)state;
        frame.inherited.f[2] *= g_ring_boost_scale;
        FastVecAdd(&frame.velocity, &frame.velocity, &frame.inherited);
        acceleration = &frame.acceleration;
        frame.velocity.f[2] += math_random_float_range(rise / g_ring_rise_min_divisor, rise) * 0.020000001f;
        qzero_nc(acceleration);
        FastVecAdd(&frame.offset, &frame.offset, position);
        frame.offset.f[2] += g_ring_height_offset;
        frame.velocity.f[3] = start_scale;
        frame.acceleration.f[3] = end_scale;
        kind = FloatToInt((math_random_float_range(g_ring_red_min, g_ring_red_max) * 5.0f + 2.0f) * 0.16666667f);
        duration = FloatToInt((math_random_float_range(g_ring_green_min, g_ring_green_max) * 5.0f + 2.0f) * 0.16666667f);
        size = FloatToInt((math_random_float_range(g_ring_blue_min, g_ring_blue_max) * 5.0f + 2.0f) * 0.16666667f);
        particle = part_spawn_trail(&frame.offset, &frame.velocity, &frame.acceleration, start_color, end_color,
                               kind, duration, size, -1);
        if (particle && (func_001163B0() & 1))
            particle[3] = 0x48;
        } while (--n != 0);
    }
}
