#include "include_asm.h"

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
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern int FastDecTimer(void *);
extern void part_kill(void *);
extern int FloatToInt(float);

/* Particle tick: age, fade the alpha by 0.01 a frame and drift; dead at zero. */
void part_update_smoothed_drift_pal(Particle *p)
{
    float *pl = p->payload;
    float a;
    if (FastDecTimer(&p->size) != 0) goto kill;
    p->life += pl[4];
    p->seed++;
    a = pl[5] - 0.012f;
    pl[5] = a > 0.0f ? a : 0.0f;
    p->color &= 0xFFFFFF;
    p->color |= FloatToInt(pl[5] * 255.0f) << 24;
    if (pl[5] <= 0.0f) {
kill:
        part_kill(p);
    } else {
        FastVecAdd(p->position, p->position, pl);
        FastVecScale(pl, pl, 0.976f);
    }
}
