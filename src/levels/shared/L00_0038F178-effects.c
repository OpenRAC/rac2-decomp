#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern int g_frame_l00_counter MACRO_ADDR;
extern void FastVecScale(void *, void *, float);
extern void vec_random_direction(float *, float, float);
extern void FastVecAdd(void *, void *, void *), vec_clear_128(Quad *);
extern float math_random_float_range(float, float);
extern int FastTweenColor(int, int, float), FloatToInt(float);
extern void gravity_offset_position(void *, float *, float *, float);
extern void *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);
/* Emits a short-lived particle every eighth frame using the actor's local vector. */
void part_emit_sparkle(char *actor) {
    char *state = *(char **)(actor + 0x68);
    float offset[4], velocity[4], jitter[4];
    float *jitterPoint, *velocityPoint;
    int firstColor, lastColor, kind, duration, size, count;
    if (g_frame_l00_counter & 7) return;
    jitterPoint = jitter;
    velocityPoint = velocity;
    count = 0;
    do {
        count--;
        FastVecScale(offset, state, 0.5f);
        vec_random_direction(jitterPoint, 0.0f, 0.016666668f);
        FastVecAdd(offset, jitterPoint, offset);
        vec_clear_128((Quad *)velocityPoint);
        offset[3] = math_random_float_range(0.25f, 0.15f);
        velocity[3] = math_random_float_range(0.15f, 0.05f);
        firstColor = FastTweenColor(0x804080FF, 0x8040FFFF, math_random_float_range(0.0f, 1.0f));
        lastColor = FastTweenColor(0x80104040, 0x80002080, math_random_float_range(0.0f, 1.0f));
        kind = FloatToInt(math_random_float_range(0.0f, 1.0f) + 1.0f);
        duration = FloatToInt((math_random_float_range(-0.5f, 0.5f) + 1.0f) * 30.0f);
        size = FloatToInt((math_random_float_range(-0.5f, 0.5f) + 1.0f) * 10.0f);
        gravity_offset_position(actor + 0x10, velocityPoint, velocityPoint, (float)duration * 0.0011111111f);
        part_spawn_trail(actor + 0x10, offset, velocityPoint, firstColor, lastColor, kind, duration, size, 0x10019);
    } while (count >= 0);
}
