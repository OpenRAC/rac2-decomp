#include "include_asm.h"

#include "common.h"
typedef int TI128_BE400 __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } Vec4_BE400 __attribute__((aligned(16)));
typedef struct { Vec4_BE400 motion; float r, g, b, alpha; } State_BE400;
typedef struct {
    unsigned char pad0[4]; int colour; unsigned char ticks, pad9; short timer;
    float size; TI128_BE400 position; State_BE400 state;
} Particle_BE400;
extern void func_00300190(void *, void *);
extern void func_00282CC0(Vec4_BE400 *, Vec4_BE400 *, Vec4_BE400 *);
extern int func_002761F8(Vec4_BE400 *, Vec4_BE400 *, int, int, int);
extern void func_00282C88(Vec4_BE400 *);
extern void func_002AFFD8(char *, char *, int);
extern void func_00282D30(Vec4_BE400 *, Vec4_BE400 *, float);
extern int func_00282978(short *);
extern void func_002B9180(void *);
extern int func_002AAE98(float, float, float, float);
extern int D_0018C0B0;
extern Vec4_BE400 D_001BAFA0;
extern int D_001A8CA0 __attribute__((sda));

void func_PAL_002BF0E0(Particle_BE400 *particle)
{
    Vec4_BE400 next, correction;
    Vec4_BE400 *position, *collisionPosition, *direction;
    State_BE400 *state;
    float r, g, b;
    int negative;
    if (!particle) return;
    state = &particle->state;
    r = state->r;
    negative = 0;
    g = state->g;
    b = state->b;
    if (r < 0.0f || g < 0.0f || b < 0.0f) {
        r = -r;
        negative = 1;
        g = -g;
        b = -b;
    }
    position = (Vec4_BE400 *)&particle->position;
    func_00300190(position, position);
    particle->size += -120.00001f;
    func_00282CC0(&next, position, &state->motion);
    collisionPosition = position;
    if (state->motion.x != 0.0f || state->motion.y != 0.0f || state->motion.z != 0.0f) {
        if (func_002761F8(collisionPosition, &next, 2, D_0018C0B0, 0)) {
            particle->position = *(TI128_BE400 *)&D_001BAFA0;
            func_00282C88(&state->motion);
            particle->size += particle->size;
        } else {
            particle->position = *(TI128_BE400 *)&next;
            if (D_001A8CA0) {
                float scale;
                direction = &correction;
                func_002AFFD8((char *)collisionPosition, (char *)direction, 0);
                scale = state->motion.w;
                if (scale != 0.0f) scale = -scale;
                else scale = 0.009072f;
                func_00282D30(direction, direction, scale);
                func_00282CC0(&state->motion, &state->motion, direction);
            } else {
                float acceleration = state->motion.w;
                if (acceleration != 0.0f) state->motion.z += acceleration;
                else state->motion.z += -0.009072f;
            }
        }
    }
    if (state->alpha <= 0.0f ||
        func_00282978(&particle->timer) ||
        particle->size < 0.0f ||
        next.x < 0.01f || next.y < 0.01f || next.z < 0.01f) {
        func_002B9180(particle);
        return;
    }
    if (!negative) {
        r += -0.012f;
        if (r < 0.0f) r = 0.0f;
        g += -0.036012f;
        if (g < 0.0f) g = 0.0f;
    } else {
        g += -0.012f;
        if (g < 0.0f) g = 0.0f;
        r += -0.036012f;
        if (r < 0.0f) r = 0.0f;
    }
    b += -0.060000002f;
    if (b < 0.0f) b = 0.0f;
    if (state->alpha < 0.0f) state->alpha = 0.0f;
    particle->colour = func_002AAE98(r, g, b, state->alpha);
    if (negative > 0) {
        state->r = -r;
        state->g = -g;
        state->b = -b;
    } else {
        state->r = r;
        state->g = g;
        state->b = b;
    }
    --particle->ticks;
}
