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
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern int func_00282978(void *);
extern void func_002B9180(void *);
extern int func_00283CF0(float);

/* Particle tick: age, fade the alpha by 0.01 a frame and drift; dead at zero. */
void func_PAL_002C0DF0(Particle *p)
{
    float *pl = p->payload;
    float a;
    if (func_00282978(&p->size) != 0) goto kill;
    p->life += pl[4];
    p->seed++;
    a = pl[5] - 0.012f;
    pl[5] = a > 0.0f ? a : 0.0f;
    p->color &= 0xFFFFFF;
    p->color |= func_00283CF0(pl[5] * 255.0f) << 24;
    if (pl[5] <= 0.0f) {
kill:
        func_002B9180(p);
    } else {
        func_00282CC0(p->position, p->position, pl);
        func_00282D30(pl, pl, 0.976f);
    }
}
