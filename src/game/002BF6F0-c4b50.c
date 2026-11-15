#include "common.h"
typedef unsigned int TI128 __attribute__((mode(TI)));
/* Each vector occupies a complete 16-byte payload. The fourth motion lane
 * stores the floor threshold; it is not a separate adjacent object. */
typedef union { float lane[4]; TI128 quad; } ParticlePayload_C4B50;
typedef struct { unsigned char header[16]; ParticlePayload_C4B50 position, velocity_floor; } FallingParticle_C4B50;
extern void FastVecAdd(void *, void *, void *);
extern void part_kill(void *);
extern float coll_get_heightmap_height(float *);
extern float D_001B1DC0[];
extern float D_001B1DC8;
extern float D_001B1DD0;
/* Moves a falling particle over the ground grid and removes it when it leaves the area or sinks below the ground. */
void part_update_falling_ground(FallingParticle_C4B50 *self) {
    ParticlePayload_C4B50 motion, sample, sampleAgain;
    float *velocity = self->velocity_floor.lane;
    float floor = velocity[3];
    int oldX, oldY;
    if (self->position.lane[0] < 0.0f || self->position.lane[1] < 0.0f ||
        self->position.lane[0] > 512.0f || self->position.lane[1] > 512.0f || self->position.lane[2] < floor)
        goto expired;
    motion.quad = self->velocity_floor.quad;
    motion.lane[3] = 0.0f;
    oldX = (int)self->position.lane[0];
    oldY = (int)self->position.lane[1];
    FastVecAdd(self->position.lane, self->position.lane, motion.lane);
    FastVecAdd(self->position.lane, self->position.lane, D_001B1DC0);
    if (oldX != (int)self->position.lane[0] || oldY != (int)self->position.lane[1]) {
        sample.quad = self->position.quad;
        if (coll_get_heightmap_height(sample.lane) >= D_001B1DD0) {
            sampleAgain.quad = self->position.quad;
            floor = coll_get_heightmap_height(sampleAgain.lane);
        } else floor = D_001B1DD0;
        if (self->position.lane[2] < floor) goto expired;
    }
    goto update;
expired:
    part_kill(self);
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
extern int g_current_game_mode;
/* The motion block of an attached spark, at 0x20 in the particle. */
typedef struct {
    float vx, vy, vz;   /* velocity */
    char *owner;        /* the object it follows */
    float ox, oy, oz;   /* offset from the owner, in the owner's frame */
    int *rec;           /* colour ramp and lifetime */
} SparkMotion_C4D18;
extern float IntToFloat(int);
extern void FastVecScale(void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern int moby_forward_two_values_and_amount(int, int, float);
extern int FastDecTimer(short *);

/* The velocity decays by 0.98 per frame. While D_001A8BB0 is clear the spark
   follows its owner (its offset moved by the velocity, then rotated by the
   owner's matrix at 0xC0) and dies with it; otherwise it drifts. */
void UpdateOwnerFollowingSpark(char *self)
{
    float velocity[4], offset[4], rotated[4];
    SparkMotion_C4D18 *spark = (SparkMotion_C4D18 *)(self + 0x20);
    int *rec = spark->rec;
    char *owner;

    *(float *)(self + 0xC) =
        IntToFloat(*(short *)((char *)rec + 8) * (rec[3] - *(short *)(self + 0xA)) / rec[3]
                      + *(short *)((char *)rec + 0xA)) * 1000.0f;
    velocity[0] = spark->vx;
    velocity[1] = spark->vy;
    velocity[2] = spark->vz;
    FastVecScale(velocity, velocity, 0.98f);
    spark->vx = velocity[0];
    spark->vy = velocity[1];
    spark->vz = velocity[2];
    if (g_current_game_mode == 0) {
        owner = spark->owner;
        if (owner != 0 && *(unsigned char *)(owner + 0x20) != 0xFE && *(unsigned char *)(owner + 0x20) != 0xFD) {
            offset[0] = spark->ox;
            offset[1] = spark->oy;
            offset[2] = spark->oz;
            FastVecAdd(offset, offset, velocity);
            spark->ox = offset[0];
            spark->oy = offset[1];
            spark->oz = offset[2];
            matrix_mul_vec3(rotated, offset, spark->owner + 0xC0);
            FastVecAdd(self + 0x10, spark->owner + 0x10, rotated);
        } else {
            part_kill(self);
            return;
        }
    } else {
        FastVecAdd(self + 0x10, self + 0x10, velocity);
    }
    *(unsigned char *)(self + 8) = *(unsigned char *)(self + 8) + 1;
    *(int *)(self + 4) = moby_forward_two_values_and_amount(rec[1], rec[0], (float)*(short *)(self + 0xA) / IntToFloat(rec[3]));
    if (FastDecTimer((short *)(self + 0xA)) != 0)
        part_kill(self);
}
