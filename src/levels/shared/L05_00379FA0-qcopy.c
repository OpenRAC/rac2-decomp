#include "common.h"

typedef int Quad __attribute__((mode(TI)));

/* One entry of the space-level projectile pool (see func_L05_0037A218). */
typedef struct {
    float position[4], previous[4], origin[4], target[4], velocity[4];
    u8 *object;
    float distance;
    int flags, color, effect, mode;
    float rate, spin, life;
    u8 pad74[12];
} L05Projectile;

extern L05Projectile D_L05_00221DD0[];
extern u8 *func_L05_00379CA0(u8 *);
extern void func_0029FCC0(u8 *, int, float *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_L05_0037DA58(void *, int, int, int);

/* Takes the first free pool entry for OBJECT: its target is joint JOINT of OTHER (or of
 * OBJECT), or the object's position when JOINT is -1; it starts from the state's bone
 * position pushed SPEED along the bone's axis and moves at twice the start-to-target
 * vector. EMIT, when set, spawns an effect of that kind on the way.
 * The integer and float parameters keep their EE register order (a0..t2, f12..f15). */
void func_L05_00379FA0(u8 *object, int color, int mode, float rate, int effect, float speed,
                       float spin, float life, int emit, int joint, u8 *other)
{
    float direction[4], point[4];
    L05Projectile *base = D_L05_00221DD0;
    u8 *position = object + 0x10;
    L05Projectile *p;
    u8 *state;
    int i;

    for (i = 0; i < 128; i++) {
        if (base[i].object)
            continue;
        p = &base[i];
        p->object = object;
        state = func_L05_00379CA0(object);
        if (joint != -1) {
            if (other)
                TransformMobyJointToWorld(other, joint, p->target);
            else
                TransformMobyJointToWorld(object, joint, p->target);
        } else {
            *(Quad *)p->target = *(Quad *)position;
        }
        *(Quad *)direction = *(Quad *)(*(u8 **)(state + 0x120) + 0xC0);
        vec_scale_to_length(direction, direction, speed);
        FastVecAdd(p->origin, *(u8 **)(state + 0x120) + 0x10, direction);
        *(Quad *)p->previous = *(Quad *)p->target;
        FastVecSub(p->velocity, p->origin, p->target);
        vec_scale_to_length(p->velocity, p->velocity, 2.0f);
        FastVecAdd(p->position, p->velocity, p->previous);
        p->color = color;
        p->mode = mode;
        p->rate = rate;
        p->effect = effect;
        p->spin = spin;
        p->life = life;
        p->flags = 0;
        p->distance = 0.0f;
        if (emit) {
            vec_scale_to_length(point, p->velocity, 0.8f);
            FastVecAdd(point, point, p->target);
            EmitParticlePairBurst(point, emit, p->color, 20);
        }
        return;
    }
}
