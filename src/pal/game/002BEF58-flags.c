#include "include_asm.h"

#include "common.h"
typedef int TI128_BE400 __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } Vec4_BE400 __attribute__((aligned(16)));
typedef struct { Vec4_BE400 motion; float r, g, b, alpha; } State_BE400;
typedef struct {
    unsigned char pad0[4]; int colour; unsigned char ticks, pad9; short timer;
    float size; TI128_BE400 position; State_BE400 state;
} Particle_BE400;
extern void vec_transform_or_copy(void *, void *);
extern void FastVecAdd(Vec4_BE400 *, Vec4_BE400 *, Vec4_BE400 *);
extern int CollLine(Vec4_BE400 *, Vec4_BE400 *, int, int, int);
extern void vec_clear_128(Vec4_BE400 *);
extern void cam_compute_view_direction(char *, char *, int);
extern void FastVecScale(Vec4_BE400 *, Vec4_BE400 *, float);
extern int FastDecTimer(short *);
extern void part_kill(void *);
extern int gfx_pack_color_floats(float, float, float, float);
extern int g_hero_moby;
extern Vec4_BE400 g_coll_hit_position;
extern int g_ground_check_inhibit __attribute__((sda));

/* Updates a hot colliding particle: it moves, stops on hitting a wall, cools its colour toward black and dies when faded out (PAL: 50 Hz timings). */
void part_update_colliding_pal(Particle_BE400 *particle)
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
    vec_transform_or_copy(position, position);
    particle->size += -120.00001f;
    FastVecAdd(&next, position, &state->motion);
    collisionPosition = position;
    if (state->motion.x != 0.0f || state->motion.y != 0.0f || state->motion.z != 0.0f) {
        if (CollLine(collisionPosition, &next, 2, g_hero_moby, 0)) {
            particle->position = *(TI128_BE400 *)&g_coll_hit_position;
            vec_clear_128(&state->motion);
            particle->size += particle->size;
        } else {
            particle->position = *(TI128_BE400 *)&next;
            if (g_ground_check_inhibit) {
                float scale;
                direction = &correction;
                cam_compute_view_direction((char *)collisionPosition, (char *)direction, 0);
                scale = state->motion.w;
                if (scale != 0.0f) scale = -scale;
                else scale = 0.009072f;
                FastVecScale(direction, direction, scale);
                FastVecAdd(&state->motion, &state->motion, direction);
            } else {
                float acceleration = state->motion.w;
                if (acceleration != 0.0f) state->motion.z += acceleration;
                else state->motion.z += -0.009072f;
            }
        }
    }
    if (state->alpha <= 0.0f ||
        FastDecTimer(&particle->timer) ||
        particle->size < 0.0f ||
        next.x < 0.01f || next.y < 0.01f || next.z < 0.01f) {
        part_kill(particle);
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
    particle->colour = gfx_pack_color_floats(r, g, b, state->alpha);
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
