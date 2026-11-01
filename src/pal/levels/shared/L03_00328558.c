#include "include_asm.h"

#include "common.h"
typedef struct {
    unsigned char pad_0[0x68];
    unsigned char *state;
    unsigned char pad_6C[0x3e];
    short type;
} Moby;
typedef struct {
    unsigned char pad_0[4];
    int mode;
    unsigned char pad_8[2];
    unsigned char alpha;
    unsigned char alpha_copy;
} ParticlePayload;
typedef struct {
    unsigned char pad_0[8];
    unsigned char variation;
    unsigned char pad_9;
    union {
        short duration;
        unsigned char duration_lo;
    } life;
    unsigned char pad_C[0x14];
    ParticlePayload payload;
} Particle;
extern float D_L03_001A8F20[] __attribute__((sda));
extern void func_00282CC0(void *, void *, void *);
extern int func_002A77E0(int);
extern void func_0029FC20(void *, int, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern Particle *func_PAL_002BE9A8(void *, float, float, float, int, void *, float, unsigned int, int);
extern void func_00282CC0(void *, void *, void *);
extern int func_002A77E0(int);

/* Emits two particle groups scaled by the object's transformed basis length. */
void func_PAL_L03_00328558(Moby *object)
{
    float matrix[16], point[4], velocity[4];
    float weight, radius, energy;
    short type = object->type;

    if ((type != 0x2EE && type != 0xCE0) || object == 0)
        return;

    func_0029FC20(object, 0, matrix);
    weight = func_00282DF0(matrix) * 0.9746588468551636f;
    if (weight > 1.0f)
        weight = 1.0f;
    energy = weight * 44000.0f + 6000.0f;
    radius = weight * 0.02f + 0.01f;
    func_00282F20(velocity, matrix + 8, weight * -0.025f + -0.025f);

    /* Larger smoke puffs with random spin. */
    {
        int i;
        short duration;
        int mode;
        unsigned char alpha;

        duration = 5;
        mode = 2;
        alpha = 0x50;
        func_00282CC0(point, matrix + 12, velocity);
        i = 1;
        do {
            Particle *particle;
            int spin;

            spin = func_002A77E0(16);
            if (func_002A77E0(2))
                spin = -spin;
            particle = func_PAL_002BE9A8(point, radius, 1.0f, 0.75f, spin, D_L03_001A8F20, energy, 0x503030FF, 0);
            if (particle != 0) {
                ParticlePayload *payload = &particle->payload;

                particle->life.duration = duration;
                payload->mode = mode;
                payload->alpha = alpha;
                payload->alpha_copy = particle->life.duration_lo;
            }
            i--;
        } while (i >= 0);
    }

    energy = weight * 25000.0f + 5000.0f;
    radius = weight * 0.015000000596046448f + 0.01f;
    func_00282F20(velocity, matrix + 8, weight * -0.015000000596046448f + -0.01f);

    /* Smaller, short-lived sparks. */
    {
        short duration;
        int mode;
        unsigned char alpha;

        duration = 2;
        mode = 2;
        alpha = 0x7F;
        func_00282CC0(point, matrix + 12, velocity);
        {
            int j;

            j = 4;
            do {
                Particle *particle;

                particle = func_PAL_002BE9A8(point, radius, 1.0f, 1.0f, 16, D_L03_001A8F20, energy, 0x7FFFFFFF, 0);
                if (particle != 0) {
                    ParticlePayload *payload = &particle->payload;

                    particle->life.duration = duration;
                    particle->variation = func_002A77E0(255);
                    payload->mode = mode;
                    payload->alpha = alpha;
                    payload->alpha_copy = particle->life.duration_lo;
                }
                j--;
            } while (j >= 0);
        }
    }
}

