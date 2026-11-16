#include "include_asm.h"

#include "common.h"
typedef unsigned int TI128 __attribute__((mode(TI)));
typedef union { float lane[4]; TI128 quad; } ParticlePayload_C4B50;
typedef struct { unsigned char header[16]; ParticlePayload_C4B50 position, velocity_floor; } FallingParticle_C4B50;
extern void FastVecAdd(void *, void *, void *);
extern void part_kill(void *);
extern float coll_get_heightmap_height(float *);
extern float g_particle_ground_vector[];
extern float g_particle_floor_offset;
extern float g_particle_min_floor_height;

void func_PAL_002C585C(FallingParticle_C4B50 *self) {
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
    FastVecAdd(self->position.lane, self->position.lane, g_particle_ground_vector);
    if (old_x != (int)self->position.lane[0] || old_y != (int)self->position.lane[1]) {
        sample.quad = self->position.quad;
        if (coll_get_heightmap_height(sample.lane) >= g_particle_min_floor_height) {
            sample_again.quad = self->position.quad;
            floor = coll_get_heightmap_height(sample_again.lane);
        } else floor = g_particle_min_floor_height;
        if (self->position.lane[2] < floor) goto expired;
    }
    goto update;
expired:
    part_kill(self);
    return;
update:
    motion.lane[0] = 0.0f;
    motion.lane[1] = 0.0f;
    motion.lane[2] = -0.00020000001f;
    motion.lane[3] = 0.0f;
    FastVecAdd(velocity, motion.lane, velocity);
    velocity[3] = floor + g_particle_floor_offset;
    return;
}

extern int g_current_game_mode;
typedef struct {
    float vx, vy, vz;    
    char *owner;         
    float ox, oy, oz;    
    int *rec;            
} SparkMotion_C4D18;
extern float IntToFloat(int);
extern void FastVecScale(void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern int moby_forward_two_values_and_amount(int, int, float);
extern int FastDecTimer(short *);

/* The velocity decays by 0.98 per frame. While D_001A8BB0 is clear the spark
   follows its owner (its offset moved by the velocity, then rotated by the
   owner's matrix at 0xC0) and dies with it; otherwise it drifts. */
void func_PAL_002C5A28(char *self)
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
    FastVecScale(v, v, 0.976f);
    p->vx = v[0];
    p->vy = v[1];
    p->vz = v[2];
    if (g_current_game_mode == 0) {
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
            part_kill(self);
            return;
        }
    } else {
        FastVecAdd(self + 0x10, self + 0x10, v);
    }
    *(unsigned char *)(self + 8) = *(unsigned char *)(self + 8) + 1;
    *(int *)(self + 4) = moby_forward_two_values_and_amount(rec[1], rec[0], (float)*(short *)(self + 0xA) / IntToFloat(rec[3]));
    if (FastDecTimer((short *)(self + 0xA)) != 0)
        part_kill(self);
}
