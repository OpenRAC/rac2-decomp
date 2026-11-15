#include "common.h"

typedef struct {
    unsigned char b0, b1, b2, b3;
    int color;
    unsigned char seed, alpha;
    short size;
    float life;
    float position[4];
    float payload[8];
} Particle;
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern int func_00282978(void *);
extern void func_002B9180(void *);
extern int func_00283CF0(float);

/* Particle tick: age, fade the alpha by 0.01 a frame and drift; dead at zero. */
/* Updates a particle that drifts, slows down and fades out until it is invisible. */
void func_002C00F0(Particle *p)
{
    float *payload = p->payload;
    float alpha;
    if (FastDecTimer(&p->size) != 0) goto kill;
    p->life += payload[4];
    p->seed++;
    alpha = payload[5] - 0.01f;
    payload[5] = alpha > 0.0f ? alpha : 0.0f;
    p->color &= 0xFFFFFF;
    p->color |= FloatToInt(payload[5] * 255.0f) << 24;
    if (payload[5] <= 0.0f) {
kill:
        KillParticle(p);
    } else {
        FastVecAdd(p->position, p->position, payload);
        FastVecScale(payload, payload, 0.98f);
    }
}
