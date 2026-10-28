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

extern void *func_002B9030(int);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern int func_00282C30(int);
extern void func_002C6748(char *);
extern unsigned char *ref_L00_0033DC48_00[];

Particle_C65A0 *func_002C65A0(const float *position, const float *velocity,
                            float start_size, float end_size, float gravity,
                            int steps, unsigned int color, int phase_step,
                            int alpha_start, int alpha_end, int transform_mode) {
    Particle_C65A0 *self = func_002B9030(0x55);
    if (self != 0) {
        ParticleContext_C65A0 *context;
        int variation;
        int difference, delta;
        float duration;
        qcopy(self->position, position);
        context = &self->context;
        self->position[3] = func_00283CE0(transform_mode);
        self->color = ((unsigned int)alpha_start << 24) | color;
        variation = func_00283CF0(4.0f) + 0x40;
        self->byte1 = 0;
        self->size = start_size;
        self->kind = 0x48;
        self->variation = variation;
        self->phase = func_002A77E0(0xFF);
        difference = alpha_end - alpha_start;
        self->shade = ref_L00_0033DC48_00[0][0];
        context->velocity[0] = velocity[0];
        context->velocity[1] = velocity[1];
        context->velocity[2] = velocity[2];
        context->gravity = gravity;
        context->phase_delta = phase_step;
        delta = difference / steps;
        if (delta != 0) steps = difference / delta;
        context->alpha_delta = delta;
        duration = func_00283CE0(steps);
        context->size_delta = (end_size - start_size) / duration;
        self->timer = func_00282C30(steps);
        context->update = func_002C6748;
    }
    return self;
}
