#include "common.h"

/* Built with -fno-gcse and -g: PRE would hoist object+0xC0 out of the loop, and -g gives the
 * nops before the div.s pairs. The acceleration clear is qzero_nc: cse forgets the frame
 * addresses there, so the constructor call builds them again, as retail does. */

typedef int ParticleQuad __attribute__((mode(TI)));
typedef union { ParticleQuad q; float f[4]; } ParticleVector;
extern int g_disk_particle_start_color __attribute__((sda)), g_disk_particle_end_color __attribute__((sda));
extern int g_disk_particle_alt_start_color __attribute__((sda)), g_disk_particle_alt_end_color __attribute__((sda));
extern float g_disk_particle_kind_min __attribute__((sda)), g_disk_particle_kind_max __attribute__((sda));
extern float g_disk_particle_duration_min __attribute__((sda)), g_disk_particle_duration_max __attribute__((sda));
extern float g_disk_particle_size_min __attribute__((sda)), g_disk_particle_size_max __attribute__((sda));
extern float g_disk_particle_speed_divisor __attribute__((sda)), g_disk_particle_rise_divisor __attribute__((sda));
extern float g_disk_particle_inherit_scale __attribute__((sda)), g_disk_particle_offset_z __attribute__((sda));
extern int GetCollHitMaterial(void), func_001163B0(void);
extern float math_random_float_range(float, float), math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern float FastVecLength(void *);
extern void matrix_mul_vec3(void *, void *, void *), vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int FloatToInt(float);
extern unsigned char *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);

/* Emit two-ended particles from a transformed disk around the object. */
void part_emit_disk_particles(char *object, void *position, int count,
                      float speed, float rise, float outerRadius, float innerRadius,
                      float startScale, float endScale)
{
    struct { ParticleVector offset, velocity, acceleration, inherited; } frame;
    char *state = *(char **)(object + 0x68);
    int startColor = g_disk_particle_start_color;
    int endColor = g_disk_particle_end_color;
    int n;
    float component, length, magnitude;
    int kind, duration, size;
    unsigned char *particle;

    if (!GetCollHitMaterial()) {
        startColor = g_disk_particle_alt_start_color;
        endColor = g_disk_particle_alt_end_color;
    }
    if (count > 0) {
        n = count;
        do {
        frame.offset.f[0] = math_fast_sin_or_cos_a(math_random_float_range(-3.1415927410125732f, 3.1415927410125732f))
            * math_random_float_range(innerRadius, outerRadius);
        component = math_fast_sin_or_cos_b(math_random_float_range(-3.1415927410125732f, 3.1415927410125732f));
        component *= math_random_float_range(innerRadius, outerRadius);
        frame.offset.f[1] = component;
        frame.offset.f[2] = 0.0f;
        matrix_mul_vec3(&frame.offset, &frame.offset, object + 0xC0);
        length = FastVecLength(&frame.offset);
        magnitude = speed * ((outerRadius - length) * 0.01666666753590107f) / outerRadius;
        vec_scale_to_length(&frame.velocity, &frame.offset,
                     math_random_float_range(magnitude / g_disk_particle_speed_divisor, magnitude));
        frame.inherited.q = *(ParticleQuad *)state;
        frame.inherited.f[2] *= g_disk_particle_inherit_scale;
        FastVecAdd(&frame.velocity, &frame.velocity, &frame.inherited);
        frame.velocity.f[2] += math_random_float_range(rise / g_disk_particle_rise_divisor, rise) * 0.01666666753590107f;
        qzero_nc(&frame.acceleration);
        FastVecAdd(&frame.offset, &frame.offset, position);
        frame.offset.f[2] += g_disk_particle_offset_z;
        frame.velocity.f[3] = startScale;
        frame.acceleration.f[3] = endScale;
        kind = FloatToInt(math_random_float_range(g_disk_particle_kind_min, g_disk_particle_kind_max));
        duration = FloatToInt(math_random_float_range(g_disk_particle_duration_min, g_disk_particle_duration_max));
        size = FloatToInt(math_random_float_range(g_disk_particle_size_min, g_disk_particle_size_max));
        particle = part_spawn_trail(&frame.offset, &frame.velocity, &frame.acceleration, startColor, endColor,
                               kind, duration, size, -1);
        if (particle && (func_001163B0() & 1))
            particle[3] = 0x48;
        } while (--n != 0);
    }
}
