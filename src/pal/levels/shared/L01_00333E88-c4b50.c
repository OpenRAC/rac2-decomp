#include "include_asm.h"

#include "common.h"
typedef unsigned int TI128 __attribute__((mode(TI)));
typedef union { float lane[4]; TI128 quad; } ParticlePayload_C4B50;
typedef struct { unsigned char header[16]; ParticlePayload_C4B50 position, velocity_floor; } FallingParticle_C4B50;
extern void func_00282CC0(void *, void *, void *);
extern void func_002B9180(void *);
extern float func_002B0520(float *);
extern float D_001B1DC0[];
extern float D_001B1DC8;
extern float D_001B1DD0;

void func_PAL_L01_00333FF0(FallingParticle_C4B50 *self) {
    ParticlePayload_C4B50 motion, sample, sample_again;
    float *velocity = self->velocity_floor.lane;
    float floor = velocity[3];
    int old_x, old_y;
    if (self->position.lane[0] < 0.0f || self->position.lane[1] < 0.0f ||
        self->position.lane[0] > 512.0f || self->position.lane[1] > 512.0f || self->position.lane[2] < floor)
        goto expired;
    motion.quad = self->velocity_floor.quad;
    motion.lane[3] = 0.0f;
    old_x = (int)self->position.lane[0];
    old_y = (int)self->position.lane[1];
    func_00282CC0(self->position.lane, self->position.lane, motion.lane);
    func_00282CC0(self->position.lane, self->position.lane, D_001B1DC0);
    if (old_x != (int)self->position.lane[0] || old_y != (int)self->position.lane[1]) {
        sample.quad = self->position.quad;
        if (func_002B0520(sample.lane) >= D_001B1DD0) {
            sample_again.quad = self->position.quad;
            floor = func_002B0520(sample_again.lane);
        } else floor = D_001B1DD0;
        if (self->position.lane[2] < floor) goto expired;
    }
    goto update;
expired:
    func_002B9180(self);
    return;
update:
    motion.lane[0] = 0.0f;
    motion.lane[1] = 0.0f;
    motion.lane[2] = -0.00020000001f;
    motion.lane[3] = 0.0f;
    func_00282CC0(velocity, motion.lane, velocity);
    velocity[3] = floor + D_001B1DC8;
    return;
}
