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
extern char D_001B5340[];
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_00282978(void *);
extern void func_002B9180(void *);
extern int func_00283CF0(float);

/* Particle tick: drift the position along its anchor, or fade out. */
void func_002BCA08(Particle *p)
{
    float *motion = p->payload;
    p->seed += *(unsigned char *)motion;
    if (((int *)motion)[1] == 0) {
        float v[4] __attribute__((aligned(16)));
        qcopy(p->position, ((Particle *)((void **)motion)[2])->position);
        FastVecSub(v, gCameraState_001B5340, p->position);
        vec_scale_to_length(v, v, 0.01f);
        FastVecAdd(p->position, p->position, v);
    } else if (FastDecTimer(&p->size)) {
        KillParticle(p);
    } else {
        p->color = (FloatToInt(p->size * 21.166668f) << 24) | 0xFFFFFF;
    }
}
