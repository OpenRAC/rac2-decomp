#include "common.h"
typedef unsigned int TI128 __attribute__((mode(TI)));
/* Each vector occupies a complete 16-byte payload. The fourth motion lane
 * stores the floor threshold; it is not a separate adjacent object. */
typedef union { float lane[4]; TI128 quad; } ParticlePayload_C4B50;
typedef struct { unsigned char header[16]; ParticlePayload_C4B50 position, velocity_floor; } FallingParticle_C4B50;
extern void func_00282CC0(void *, void *, void *);
extern void func_002B9180(void *);
extern float func_002B0520(float *);
extern float D_001B1DC0[];
extern float D_001B1DC8;
extern float D_001B1DD0;
void func_002C4B50(FallingParticle_C4B50 *self) {
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
    FastVecAdd(self->position.lane, self->position.lane, motion.lane);
    FastVecAdd(self->position.lane, self->position.lane, D_001B1DC0);
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
    motion.lane[2] = -0.00013888889f;
    motion.lane[3] = 0.0f;
    FastVecAdd(velocity, motion.lane, velocity);
    velocity[3] = floor + D_001B1DC8;
    return;
}

/* func_002C4D18 shares this unit's -mno-split-addresses: retail reads the
   scalar flag D_001A8BB0 with one lui/lw macro. Its scalar MEM and the
   struct-field stores of the velocity let the flag load go between them. */
extern int D_001A8BB0;
/* The motion block of an attached spark, at 0x20 in the particle. */
typedef struct {
    float vx, vy, vz;   /* velocity */
    char *owner;        /* the object it follows */
    float ox, oy, oz;   /* offset from the owner, in the owner's frame */
    int *rec;           /* colour ramp and lifetime */
} SparkMotion_C4D18;
extern float func_00283CE0(int);
extern void func_00282D30(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern int func_002A9568(int, int, float);
extern int func_00282978(short *);

/* The velocity decays by 0.98 per frame. While D_001A8BB0 is clear the spark
   follows its owner (its offset moved by the velocity, then rotated by the
   owner's matrix at 0xC0) and dies with it; otherwise it drifts. */
void func_002C4D18(char *self)
{
    float v[4], w[4], m[4];
    SparkMotion_C4D18 *p = (SparkMotion_C4D18 *)(self + 0x20);
    int *rec = p->rec;
    char *owner;

    *(float *)(self + 0xC) =
        IntToFloat(*(short *)((char *)rec + 8) * (rec[3] - *(short *)(self + 0xA)) / rec[3]
                      + *(short *)((char *)rec + 0xA)) * 1000.0f;
    v[0] = p->vx;
    v[1] = p->vy;
    v[2] = p->vz;
    FastVecScale(v, v, 0.98f);
    p->vx = v[0];
    p->vy = v[1];
    p->vz = v[2];
    if (D_001A8BB0 == 0) {
        owner = p->owner;
        if (owner != 0 && *(unsigned char *)(owner + 0x20) != 0xFE && *(unsigned char *)(owner + 0x20) != 0xFD) {
            w[0] = p->ox;
            w[1] = p->oy;
            w[2] = p->oz;
            FastVecAdd(w, w, v);
            p->ox = w[0];
            p->oy = w[1];
            p->oz = w[2];
            matrix_mul_vec3(m, w, p->owner + 0xC0);
            FastVecAdd(self + 0x10, p->owner + 0x10, m);
        } else {
            func_002B9180(self);
            return;
        }
    } else {
        FastVecAdd(self + 0x10, self + 0x10, v);
    }
    *(unsigned char *)(self + 8) = *(unsigned char *)(self + 8) + 1;
    *(int *)(self + 4) = func_002A9568(rec[1], rec[0], (float)*(short *)(self + 0xA) / IntToFloat(rec[3]));
    if (FastDecTimer((short *)(self + 0xA)) != 0)
        func_002B9180(self);
}
