#include "common.h"

/* Spawn a two-ended trail particle (kind 2) between two points. */
typedef int Quad __attribute__((mode(TI)));
typedef struct {
    u8 used;
    u8 flag1;
    u8 texture;
    u8 mode;
    s32 color;
    u8 alpha;
    u8 fade;
    s16 kind;
    f32 phase;
    Quad position;
    struct ParticleTrail {
        s32 packedA;
        s32 packedB;
        s32 startColor;
        s32 endColor;
        s16 kind;
        s16 duration;
        s16 size;
        s16 scaleA;
        s16 scaleB;
    } trail;
} Particle;
extern Particle *func_002B9030(int);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern void func_002AE730(float *, int *);
extern void func_002AE838(void *, void *);
extern u8 *D_001F2540[];
extern u8 *D_001F259C;

Particle *func_002BAA28(void *position, float *from, float *to, int startColor, int endColor, int kind, int duration, int size, int flags)
{
    Particle *p = func_002B9030(2);
    float a[4], b[4];
    struct ParticleTrail *t;
    if (p != 0) {
        qcopy(&p->position, position);
        p->color = startColor;
        p->fade = func_00283CF0(4.0f) + 0x40;
        p->phase = 0.0f;
        p->flag1 = 0;
        p->mode = 0x44;
        p->alpha = func_00283CF0(func_002A7878(p->phase, 255.0f));
        if (flags == -1) {
            p->texture = *D_001F259C;
        } else {
            p->texture = *D_001F2540[flags & 0xFFFF];
            if (flags & 0x10000)
                p->mode = 0x48;
        }
        p->kind = kind;
        t = &p->trail;
        t->scaleA = func_00283CF0(from[3] * 210.00002f);
        t->scaleB = func_00283CF0(to[3] * 210.00002f);
        func_002AE730(from, &t->packedA);
        func_002AE730(to, &t->packedB);
        func_002AE838(a, &t->packedA);
        func_002AE838(b, &t->packedB);
        t->startColor = startColor;
        t->endColor = endColor;
        t->kind = kind;
        t->duration = duration;
        t->size = size;
    }
    return p;
}
