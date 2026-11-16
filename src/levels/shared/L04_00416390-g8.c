#include "common.h"

typedef int TrailVector128 __attribute__((mode(TI)));
typedef struct { int values[5]; } TrailParticleTypes;
typedef struct { float values[10]; } TrailParticleSizes;

extern TrailParticleTypes g_trail_particle_types;
extern TrailParticleSizes g_trail_particle_sizes;
extern int g_trail_size_index __attribute__((sda));
extern float math_random_float_range(float, float);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecScale(void *, void *, float);
extern float FastVecDot(void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern char *part_l04_spawn_spinning(void *, void *, void *, int, int, float, float, float);
extern void racer_start_trail(void *, void *, void *, void *);

/* Spawns a line of trail particles from a position along a direction, with a few special coloured ones. */
void EmitTrailEffects(char *owner, void *pos, void *dir, float length)
{
    struct {
        struct { float v[4]; } __attribute__((aligned(16))) origin;
        TrailParticleTypes types;
        TrailParticleSizes sizes __attribute__((aligned(16)));
        float step[4] __attribute__((aligned(16)));
        float point[4] __attribute__((aligned(16)));
        float offset[4] __attribute__((aligned(16)));
        float bias[4] __attribute__((aligned(16)));
    } frame;
    void *origin = &frame.origin;
    float chance, angle, inc, magnitude;
    int count, type, i;

    *(TrailVector128 *)origin = *(TrailVector128 *)pos;
    frame.types = g_trail_particle_types;
    frame.sizes = g_trail_particle_sizes;
    chance = math_random_float_range(0.0f, 1.0f);
    FastVecScale(frame.bias, owner + 0xC0, 0.05f);
    FastVecScale(frame.step, dir, 1.0f / length);
    FastVecDot(frame.step, owner + 0xC0);
    if (*(short *)(owner + 0xAA) == MOBY_CLASS_ENEMY_HOVERBIKE)
        count = (int)(length + length) + 1;
    else
        count = (int)(length * 5.0f) + 2;
    type = -1;
    inc = math_random_float_range(0.0f, 1.5707964f) + 0.1f;
    angle = math_random_float_range(0.0f, 3.926991f);
    if (chance < 0.05f)
        type = 0;
    else if (chance < 0.1f)
        type = 1;
    else if (chance < 0.15f)
        type = 2;
    for (i = 0; i < count; i++) {
        angle = FastAddRotations(angle, inc);
        frame.offset[0] = math_fast_sin_or_cos_a(angle);
        frame.offset[1] = math_fast_sin_or_cos_b(angle);
        frame.offset[2] = 0.3f;
        magnitude = FastVecDot(frame.offset, frame.step);
        FastVecScale(frame.point, frame.offset,
            (length * 0.1f + frame.sizes.values[g_trail_size_index] * 1.05f) * 0.016666668f);
        FastVecScale(frame.offset, frame.offset, 0.15f);
        FastVecAdd(frame.offset, frame.offset, origin);
        FastVecAdd(frame.offset, frame.offset, frame.bias);
        frame.offset[2] -= 0.2f;
        if (i == 1 && type >= 0) {
            FastVecAdd(frame.point, frame.point, dir);
            part_l04_spawn_spinning(frame.offset, frame.point, dir, frame.types.values[type], type,
                magnitude * 0.01f + 0.05f, frame.offset[2] - 0.25f, 0.0027777778f);
        } else {
            racer_start_trail(owner, frame.point, dir, owner + 0x10);
        }
        if (++g_trail_size_index >= 10)
            g_trail_size_index = 0;
    }
}
