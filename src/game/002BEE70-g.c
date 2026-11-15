#include "common.h"

/* Needs -g (config/cflags.txt): its line notes give the pre-division nops. The active test reads the word holding
   collided and flags: CSE cannot share that with the signed halfword load before it, and combine narrows it to `lhu`. */
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
extern Vector D_001BAFB0, D_001BAFC0;
extern struct { float matrix[4][4]; char unknown40[0x40]; Vector origin; } D_001B52C0;
extern void func_00282C88(Quad *), func_00282CF0(void *, void *, void *), func_00282F20(void *, void *, float), func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float), func_00283028(void *, void *, void *), func_002830C0(void *, void *, void *), func_002B9180(void *);
extern float func_00282DF0(void *), func_00282C48(float), func_00283248(float, float);
extern int func_00277258(void *, int, void *, float), func_00283CF0(float);
/* Integrates a linked particle chain with collision response and projected facing. */
void func_002BEE70(ChainParticle *particle) {
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
            ClearVector128(&force.quad);
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
            velocity->f[2] -= 0.02f;
            FastVecAdd(&point, &particle->position, velocity);
        }
        else qcopy(&point,&particle->position);
        if (dynamics->previous) {
            FastVecSub(&force, &point, &dynamics->previous->position);
            if (FloatAbs(FastVecLength(&force) - 0.15f) > 0.1f) {
                vec_scale_to_length(&force, &force, 0.15f);
                FastVecAdd(&point, &force, &dynamics->previous->position);
            }
            if (TestPointAgainstCollision(&point, 0, 0, 0.15f)) {
                if (!dynamics->collided) qcopy(&point,&D_001BAFB0);
                else qcopy(&point,&particle->position);
                dynamics->collided = 1;
            } else dynamics->collided = 0;
            if (dynamics->collided) {
                FastVectorNormalize(velocity, velocity, &D_001BAFC0);
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
                KillParticle(particle); return;
            }
        }
    }
    attachment = dynamics->previous;
    if (attachment) {
        FastVecSub(&point, &attachment->position, &D_001B52C0.origin);
        transform_vector(&point, &point, D_001B52C0.matrix);
        step = 1.0f / point.f[3];
        FastVecScale(&point, &point, step);
        FastVecSub(&delta, &particle->position, &D_001B52C0.origin);
        transform_vector(&delta, &delta, D_001B52C0.matrix);
        step = 1.0f / delta.f[3];
        FastVecScale(&delta, &delta, step);
        FastVecSub(&point, &point, &delta);
        particle->rotation = FloatToInt(FastMatrixHelperA(point.f[0], point.f[1]) * 40.743664f) - 32;
    }
}
