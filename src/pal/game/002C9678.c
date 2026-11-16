#include "include_asm.h"


#include "common.h"
struct DriftParameters {
    float velocity[3];
    unsigned int color;
    unsigned char frame_step, lifetime, alpha, flags;
    unsigned char distance_limit, speed_start, speed_end, distance;
    float size_start, size_end;
};
struct DriftParticle {
    unsigned char unknown0[4];
    unsigned int color;
    unsigned char frame, unknown9;
    short remaining;
    float size;
    float position[4];
    struct DriftParameters parameters;
};
extern float IntToFloat(int);
extern int FloatToInt(float);
extern int FastTweenColor(int, int, float);
extern void vec_transform_or_copy(char *, char *);
extern float math_square(float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int FastDecTimer(char *);
extern void part_kill(char *);

/* Default game profile matches US and US2 in all 28 placements (612 bytes).
 * This particle view covers the complete 0x40-byte direct-access prefix.
 * The three velocity floats are copied to a complete local vector with w=0;
 * the adjacent packed color word is not misrepresented as a velocity w. */
void part_update_drift_pal(struct DriftParticle *particle)
{
    float velocity[4], change[4];
    struct DriftParameters *parameters = &particle->parameters;
    float speed, end_speed, distance_limit, distance, life, progress;
    velocity[0] = parameters->velocity[0];
    velocity[1] = parameters->velocity[1];
    velocity[2] = parameters->velocity[2];
    velocity[3] = 0.0f;
    speed = IntToFloat(parameters->speed_start) * 0.0078125f;
    end_speed = IntToFloat(parameters->speed_end) * 0.0078125f;
    distance_limit = IntToFloat(parameters->distance_limit) * 0.0078125f;
    distance = IntToFloat(parameters->distance) * 0.0078125f;
    vec_transform_or_copy((char *)particle->position, (char *)particle->position);
    life = IntToFloat(particle->remaining);
    life /= IntToFloat(parameters->lifetime);
    progress = 1.0f - life;
    if (!(parameters->flags & 1)) {
        particle->color = FastTweenColor(0x103080, (int)parameters->color, progress) | ((u32)parameters->alpha << 24);
        speed += (end_speed - speed) * progress;
        particle->size = parameters->size_start + (parameters->size_end - parameters->size_start) * progress;
    } else {
        float initial_alpha, fade;
        int alpha;
        speed = end_speed;
        initial_alpha = IntToFloat(parameters->alpha);
        fade = IntToFloat(parameters->alpha);
        fade *= math_square(progress);
        alpha = FloatToInt(initial_alpha - fade);
        particle->color = parameters->color | ((unsigned int)alpha << 24);
    }
    if (!(parameters->flags & 2)) {
        FastVecScale(change, velocity, speed);
        distance += speed;
        FastVecAdd(particle->position, particle->position, change);
        if (distance <= distance_limit) parameters->distance = FloatToInt(distance * 128.0f);
        else {
            parameters->flags |= 2;
            FastVecScale(change, velocity, distance_limit - distance);
            FastVecAdd(particle->position, change, particle->position);
        }
    }
    particle->frame += parameters->frame_step;
    if (FastDecTimer((char *)&particle->remaining)) {
        if (!(parameters->flags & 1)) {
            parameters->flags |= 1;
            parameters->lifetime = 17;
            particle->remaining = 17;
        } else part_kill((char *)particle);
    }
}


