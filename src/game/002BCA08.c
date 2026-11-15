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
extern char g_camera_eye_state[];
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int FastDecTimer(void *);
extern void part_kill(void *);
extern int FloatToInt(float);

/* Particle tick: drift the position along its anchor, or fade out. */
void part_update_anchored_fade(Particle *p)
{
    float *motion = p->payload;
    p->seed += *(unsigned char *)motion;
    if (((int *)motion)[1] == 0) {
        float v[4] __attribute__((aligned(16)));
        qcopy(p->position, ((Particle *)((void **)motion)[2])->position);
        FastVecSub(v, g_camera_eye_state, p->position);
        vec_scale_to_length(v, v, 0.01f);
        FastVecAdd(p->position, p->position, v);
    } else if (FastDecTimer(&p->size)) {
        part_kill(p);
    } else {
        p->color = (FloatToInt(p->size * 21.166668f) << 24) | 0xFFFFFF;
    }
}
