#include "common.h"

typedef int L01_EF38Quad __attribute__((mode(TI)));
typedef struct {
    float scale;
    float second;
    int color;
    int kind;
    float rate;
} L01_EF38Payload;
typedef struct {
    unsigned char b0;
    unsigned char b1;
    unsigned char b2;
    unsigned char b3;
    int color;
    unsigned char seed;
    unsigned char alpha;
    unsigned short size;
    float life;
    union {
        L01_EF38Quad q;
        float f[4];
    } position;
    L01_EF38Payload payload;
} L01_EF38Particle;

extern L01_EF38Particle *part_alloc(int);
extern int FloatToInt(float);
extern int math_random_int_below(int);
extern float IntToFloat(int);
extern unsigned char *D_L01_001FF110;

/* Creates a short-lived glowing particle at a position with a color, size and lifetime, and returns it. */
L01_EF38Particle *part_l01_spawn_glow(L01_EF38Quad *position, int color, int kind, float scale, float second, int life)
{
    L01_EF38Particle *particle;
    L01_EF38Payload *out_payload;

    particle = part_alloc(0x34);
    if (particle) {
        out_payload = &particle->payload;
        qcopy(&particle->position, position);
        particle->color = color;
        particle->b3 = 0x44;
        particle->position.f[2] = particle->position.f[2] + 0.05f;
        particle->alpha = FloatToInt(2.0f) + 32;
        particle->b1 = 1;
        particle->b2 = *D_L01_001FF110;
        particle->size = life;
        particle->life = scale * 210000.0f;
        particle->seed = math_random_int_below(255);
        out_payload->color = color;
        out_payload->kind = kind;
        particle->payload.scale = scale;
        out_payload->second = second;
        out_payload->rate = 1.0f / IntToFloat(life);
    }
    return particle;
}
