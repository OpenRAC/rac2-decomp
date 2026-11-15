#include "common.h"

typedef struct {
    float velocity[3];
    float gravity, size_delta;
    unsigned char alpha_delta, phase_delta;
    unsigned short pad16;
    int pad18;
    void (*update)(char *);
} ParticleContext_C65A0;

typedef struct {
    unsigned char byte0, byte1, shade, kind;
    unsigned int color;
    unsigned char phase, variation;
    short timer;
    float size;
    float position[4];
    ParticleContext_C65A0 context;
} Particle_C65A0;

extern void *part_alloc(int);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern int math_random_int_below(int);
extern int subtract_integer_with_clamp(int);
extern void part_update_spin_falling(char *);
extern unsigned char *ref_L00_0033DC48_00[];

/* Creates a particle that flies with a speed and gravity, changing size and fading in see-through amount over its life. */
Particle_C65A0 *part_spawn_gravity_fade(const float *position, const float *velocity,
                            float startSize, float endSize, float gravity,
                            int steps, unsigned int color, int phaseStep,
                            int alphaStart, int alphaEnd, int transformMode) {
    Particle_C65A0 *particle = part_alloc(0x55);
    if (particle != 0) {
        ParticleContext_C65A0 *context;
        int variation;
        int difference, delta;
        float duration;
        qcopy(particle->position, position);
        context = &particle->context;
        particle->position[3] = IntToFloat(transformMode);
        particle->color = ((unsigned int)alphaStart << 24) | color;
        variation = FloatToInt(4.0f) + 0x40;
        particle->byte1 = 0;
        particle->size = startSize;
        particle->kind = 0x48;
        particle->variation = variation;
        particle->phase = math_random_int_below(0xFF);
        difference = alphaEnd - alphaStart;
        particle->shade = ref_L00_0033DC48_00[0][0];
        context->velocity[0] = velocity[0];
        context->velocity[1] = velocity[1];
        context->velocity[2] = velocity[2];
        context->gravity = gravity;
        context->phase_delta = phaseStep;
        delta = difference / steps;
        if (delta != 0) steps = difference / delta;
        context->alpha_delta = delta;
        duration = IntToFloat(steps);
        context->size_delta = (endSize - startSize) / duration;
        particle->timer = subtract_integer_with_clamp(steps);
        context->update = part_update_spin_falling;
    }
    return particle;
}
