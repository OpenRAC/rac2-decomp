#include "common.h"

/* Built with -fno-gcse and -g: PRE would hoist object+0xC0 out of the loop, and -g gives the
 * nops before the div.s pairs. The acceleration clear is qzero_nc: cse forgets the frame
 * addresses there, so the constructor call builds them again, as retail does. */

typedef int ParticleQuad __attribute__((mode(TI)));
typedef union { ParticleQuad q; float f[4]; } ParticleVector;
extern int D_L08_001AFB30 __attribute__((sda)), D_L08_001AFB34 __attribute__((sda));
extern int D_L08_001AFBC8 __attribute__((sda)), D_L08_001AFBCC __attribute__((sda));
extern float D_L08_001AFB38 __attribute__((sda)), D_L08_001AFB3C __attribute__((sda));
extern float D_L08_001AFB40 __attribute__((sda)), D_L08_001AFB44 __attribute__((sda));
extern float D_L08_001AFB48 __attribute__((sda)), D_L08_001AFB4C __attribute__((sda));
extern float D_L08_001AFB68 __attribute__((sda)), D_L08_001AFB6C __attribute__((sda));
extern float D_L08_001AFBBC __attribute__((sda)), D_L08_001AFBC0 __attribute__((sda));
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
    int startColor = D_L08_001AFB30;
    int endColor = D_L08_001AFB34;
    int n;
    float component, length, magnitude;
    int kind, duration, size;
    unsigned char *particle;

    if (!GetCollHitMaterial()) {
        startColor = D_L08_001AFBC8;
        endColor = D_L08_001AFBCC;
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
                     math_random_float_range(magnitude / D_L08_001AFB68, magnitude));
        frame.inherited.q = *(ParticleQuad *)state;
        frame.inherited.f[2] *= D_L08_001AFBBC;
        FastVecAdd(&frame.velocity, &frame.velocity, &frame.inherited);
        frame.velocity.f[2] += math_random_float_range(rise / D_L08_001AFB6C, rise) * 0.01666666753590107f;
        qzero_nc(&frame.acceleration);
        FastVecAdd(&frame.offset, &frame.offset, position);
        frame.offset.f[2] += D_L08_001AFBC0;
        frame.velocity.f[3] = startScale;
        frame.acceleration.f[3] = endScale;
        kind = FloatToInt(math_random_float_range(D_L08_001AFB38, D_L08_001AFB3C));
        duration = FloatToInt(math_random_float_range(D_L08_001AFB40, D_L08_001AFB44));
        size = FloatToInt(math_random_float_range(D_L08_001AFB48, D_L08_001AFB4C));
        particle = part_spawn_trail(&frame.offset, &frame.velocity, &frame.acceleration, startColor, endColor,
                               kind, duration, size, -1);
        if (particle && (func_001163B0() & 1))
            particle[3] = 0x48;
        } while (--n != 0);
    }
}
