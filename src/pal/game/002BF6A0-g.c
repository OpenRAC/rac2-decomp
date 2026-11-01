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
extern Vector D_001BAFB0, D_001BAFC0;
extern struct { float matrix[4][4]; char unknown40[0x40]; Vector origin; } D_001B52C0;
extern void func_00282C88(Quad *), func_00282CF0(void *, void *, void *), func_00282F20(void *, void *, float), func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float), func_00283028(void *, void *, void *), func_002830C0(void *, void *, void *), func_002B9180(void *);
extern float func_00282DF0(void *), func_00282C48(float), func_00283248(float, float);
extern int func_00277258(void *, int, void *, float), func_00283CF0(float);

/* Integrates a linked particle chain with collision response and projected facing. */
void func_PAL_002BFB58(ChainParticle *particle) {
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
            func_00282C88(&force.quad);
            if (!dynamics->collided && node && !link->collided && !(link->flags & 1)) {
                do {
                    float strength = 0.2f;
                    step = distance * distance;
                    func_00282CF0(&point, &node->position, &particle->position);
                    distance += 1; damping *= 0.999f;
                    func_00282F20(&point, &point, strength / step);
                    func_00282CC0(&force, &force, &point);
                    node = link->next;
                    link = node ? &node->dynamics : link;
                    if (!node) break;
                } while (!link->collided && !(link->flags & 1));
            }
            damping = (0.15f - damping) + 1.07f;
            if (!link || !link->collided) func_00282CC0(velocity, velocity, &force);
            else func_00282D30(velocity, velocity, 0.5f);
            if (dynamics->next) func_00282D30(velocity, velocity, damping);
            else func_00282D30(velocity, velocity, 0.97f);
            velocity->f[2] -= 0.028800001f;
            func_00282CC0(&point, &particle->position, velocity);
        }
        else qcopy(&point,&particle->position);
        if (dynamics->previous) {
            func_00282CF0(&force, &point, &dynamics->previous->position);
            if (func_00282C48(func_00282DF0(&force) - 0.15f) > 0.1f) {
                func_00282F20(&force, &force, 0.15f);
                func_00282CC0(&point, &force, &dynamics->previous->position);
            }
            if (func_00277258(&point, 0, 0, 0.15f)) {
                if (!dynamics->collided) qcopy(&point,&D_001BAFB0);
                else qcopy(&point,&particle->position);
                dynamics->collided = 1;
            } else dynamics->collided = 0;
            if (dynamics->collided) {
                func_00283028(velocity, velocity, &D_001BAFC0);
                func_00282D30(velocity, velocity, 0.95f);
            } else {
                func_00282CF0(&delta, &point, &particle->position);
                func_00282CC0(velocity, velocity, &delta);
                func_00282D30(velocity, velocity, 0.5f);
            }
            func_00282CF0(&delta, &point, &particle->position);
            func_00282CC0(velocity, velocity, &delta);
            func_00282D30(velocity, velocity, 0.5f);
        }
        qcopy(&particle->position,&point);
        if (dynamics->flags & 2) {
            alpha = (particle->color >> 24) - 2;
            if (alpha > 0) particle->color = (particle->color & 0xFFFFFF) | (alpha << 24);
            else if (!dynamics->next) {
                if (dynamics->previous) dynamics->previous->dynamics.next = 0;
                func_002B9180(particle); return;
            }
        }
    }
    attachment = dynamics->previous;
    if (attachment) {
        func_00282CF0(&point, &attachment->position, &D_001B52C0.origin);
        func_002830C0(&point, &point, D_001B52C0.matrix);
        step = 1.0f / point.f[3];
        func_00282D30(&point, &point, step);
        func_00282CF0(&delta, &particle->position, &D_001B52C0.origin);
        func_002830C0(&delta, &delta, D_001B52C0.matrix);
        step = 1.0f / delta.f[3];
        func_00282D30(&delta, &delta, step);
        func_00282CF0(&point, &point, &delta);
        particle->rotation = func_00283CF0(func_00283248(point.f[0], point.f[1]) * 40.743664f) - 32;
    }
}
