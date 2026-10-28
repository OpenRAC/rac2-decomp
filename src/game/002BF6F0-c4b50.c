#include "common.h"
typedef unsigned int TI128 __attribute__((mode(TI)));
typedef struct { unsigned char header[16]; float position[4]; float velocity[3]; float floor; } FallingParticle_C4B50;
extern void func_00282CC0(void *, void *, void *);
extern void func_002B9180(void *);
extern float func_002B0520(float *);
extern float D_001B1DC0[];
extern float D_001B1DC8;
extern float D_001B1DD0;
void func_002C4B50(FallingParticle_C4B50 *self) {
    float motion[4], sample[4], sample_again[4];
    float *velocity = self->velocity;
    float floor = velocity[3];
    int old_x, old_y;
    if (self->position[0] < 0.0f || self->position[1] < 0.0f ||
        self->position[0] > 512.0f || self->position[1] > 512.0f || self->position[2] < floor)
        goto expired;
    *(TI128 *)motion = *(TI128 *)velocity;
    motion[3] = 0.0f;
    old_x = (int)self->position[0];
    old_y = (int)self->position[1];
    func_00282CC0(self->position, self->position, motion);
    func_00282CC0(self->position, self->position, D_001B1DC0);
    if (old_x != (int)self->position[0] || old_y != (int)self->position[1]) {
        *(TI128 *)sample = *(TI128 *)self->position;
        if (func_002B0520(sample) >= D_001B1DD0) {
            *(TI128 *)sample_again = *(TI128 *)self->position;
            floor = func_002B0520(sample_again);
        } else floor = D_001B1DD0;
        if (self->position[2] < floor) goto expired;
    }
    goto update;
expired:
    func_002B9180(self);
    return;
update:
    motion[0] = 0.0f;
    motion[1] = 0.0f;
    motion[2] = -0.00013888889f;
    motion[3] = 0.0f;
    func_00282CC0(velocity, motion, velocity);
    velocity[3] = floor + D_001B1DC8;
    return;
}
