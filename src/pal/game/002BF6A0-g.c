#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
typedef struct ChainParticle ChainParticle;
typedef struct {
    Vector velocity;
    ChainParticle *previous, *next;
    u32 unknown38;
    short collided;
    short flags;
} ChainParticleDynamics;
struct ChainParticle {
    u32 unknown00, color;
    s8 rotation;
    u8 unknown09[7];
    Vector position;
    ChainParticleDynamics dynamics;
};
extern Vector g_coll_hit_point, g_coll_hit_normal;
extern struct { float matrix[4][4]; char unknown40[0x40]; Vector origin; } g_particle_view_transform;
extern void vec_clear_128(Quad *), FastVecSub(void *, void *, void *), vec_scale_to_length(void *, void *, float), FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float), vec_fast_normalize(void *, void *, void *), transform_vector(void *, void *, void *), part_kill(void *);
extern float FastVecLength(void *), math_fabs(float), mat_fast_helper_a(float, float);
extern int coll_test_point(void *, int, void *, float), FloatToInt(float);

/* Integrates a linked particle chain with collision response and projected facing. */
void part_update_linked_effect_pal(ChainParticle *particle) {
    Vector point, delta, force;
    ChainParticle *node, *attachment;
    ChainParticleDynamics *link;
    float distance, damping, step;
    int alpha;
    ChainParticleDynamics *dynamics=&particle->dynamics;
    Vector *velocity=&dynamics->velocity;
    if (dynamics->flags != 0xFF) {
        if (((*(u32 *)&dynamics->collided >> 16) ^ 1) & 1) {
            node = dynamics->next;
            link = node ? &node->dynamics : 0;
            distance = 2; damping = 0.15f;
            vec_clear_128(&force.quad);
            if (!dynamics->collided && node && !link->collided && !(link->flags & 1)) {
                do {
                    float strength = 0.2f;
                    step = distance * distance;
                    FastVecSub(&point, &node->position, &particle->position);
                    distance += 1; damping *= 0.999f;
                    vec_scale_to_length(&point, &point, strength / step);
                    FastVecAdd(&force, &force, &point);
                    node = link->next;
                    link = node ? &node->dynamics : link;
                    if (!node) break;
                } while (!link->collided && !(link->flags & 1));
            }
            damping = (0.15f - damping) + 1.07f;
            if (!link || !link->collided) FastVecAdd(velocity, velocity, &force);
            else FastVecScale(velocity, velocity, 0.5f);
            if (dynamics->next) FastVecScale(velocity, velocity, damping);
            else FastVecScale(velocity, velocity, 0.97f);
            velocity->f[2] -= 0.028800001f;
            FastVecAdd(&point, &particle->position, velocity);
        }
        else qcopy(&point,&particle->position);
        if (dynamics->previous) {
            FastVecSub(&force, &point, &dynamics->previous->position);
            if (math_fabs(FastVecLength(&force) - 0.15f) > 0.1f) {
                vec_scale_to_length(&force, &force, 0.15f);
                FastVecAdd(&point, &force, &dynamics->previous->position);
            }
            if (coll_test_point(&point, 0, 0, 0.15f)) {
                if (!dynamics->collided) qcopy(&point,&g_coll_hit_point);
                else qcopy(&point,&particle->position);
                dynamics->collided = 1;
            } else dynamics->collided = 0;
            if (dynamics->collided) {
                vec_fast_normalize(velocity, velocity, &g_coll_hit_normal);
                FastVecScale(velocity, velocity, 0.95f);
            } else {
                FastVecSub(&delta, &point, &particle->position);
                FastVecAdd(velocity, velocity, &delta);
                FastVecScale(velocity, velocity, 0.5f);
            }
            FastVecSub(&delta, &point, &particle->position);
            FastVecAdd(velocity, velocity, &delta);
            FastVecScale(velocity, velocity, 0.5f);
        }
        qcopy(&particle->position,&point);
        if (dynamics->flags & 2) {
            alpha = (particle->color >> 24) - 2;
            if (alpha > 0) particle->color = (particle->color & 0xFFFFFF) | (alpha << 24);
            else if (!dynamics->next) {
                if (dynamics->previous) dynamics->previous->dynamics.next = 0;
                part_kill(particle); return;
            }
        }
    }
    attachment = dynamics->previous;
    if (attachment) {
        FastVecSub(&point, &attachment->position, &g_particle_view_transform.origin);
        transform_vector(&point, &point, g_particle_view_transform.matrix);
        step = 1.0f / point.f[3];
        FastVecScale(&point, &point, step);
        FastVecSub(&delta, &particle->position, &g_particle_view_transform.origin);
        transform_vector(&delta, &delta, g_particle_view_transform.matrix);
        step = 1.0f / delta.f[3];
        FastVecScale(&delta, &delta, step);
        FastVecSub(&point, &point, &delta);
        particle->rotation = FloatToInt(mat_fast_helper_a(point.f[0], point.f[1]) * 40.743664f) - 32;
    }
}
