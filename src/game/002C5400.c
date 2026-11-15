#include "names.h"
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
extern int FastDecTimer(void *);
extern void part_kill(void *);
extern float IntToFloat(int);
extern int FastTweenColor(int, int, float);

/* Particle tick: drift (around an anchor when it has one) and fade with the remaining life. */
/* Updates a drifting particle (it can follow an anchor object) and fades it as time runs out. */
void part_update_anchored_fading(Particle *p)
{
    float *payload = p->payload;
    if (((char **)payload)[7] != 0) {
        payload[0] += payload[4];
        payload[1] += payload[5];
        payload[2] += payload[6];
        FastVecAdd(p->position, ((char **)payload)[7] + 0x10, payload);
    } else {
        p->position[0] += payload[4];
        p->position[1] += payload[5];
        p->position[2] += payload[6];
    }
    if (FastDecTimer(&p->size)) {
        part_kill(p);
    } else if (((char **)payload)[7] != 0) {
        p->color = FastTweenColor(p->color & 0xFFFFFF, p->color, IntToFloat(p->size - 1) / IntToFloat(p->size));
    } else {
        p->color = FastTweenColor(0, p->color, IntToFloat(p->size - 1) / IntToFloat(p->size));
    }
}
