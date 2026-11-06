/* func_PAL_0032A898, the PAL copy of func_003290D0: the same C, where wrap *(int *)(state + 0x50) (((int)({e}) * 5 + 2) / 6); rewrap func_002A7820(50, 60). */
#include "common.h"

/* One of the 300 0x50-byte particles at D_0022C9A0 (see func_00329328). */
typedef struct {
    float pos[4];
    float velocity[4];
    float spin;
    float angle;
    float size;
    int color;
    int color2;
    int timer;
    int timer2;
    int kind;
    int life;
    int duration;
    char *owner;
    int tail;
} Particle290;

extern Particle290 D_0022C9A0[300];
extern int func_002A7820(int, int);
extern float func_002A78D8(float, float), func_002A7940(void), func_002A7878(float, float);
extern void func_00282C88(void *), func_00283098(void *, void *, void *), func_00282CC0(void *, void *, void *);

/* Claims a free particle for self: random life, grey colour, spin and size, at pos or, when
   pos[3] is -1, at a point on self's basis; counts it in self's state (+0x4C, +0x50).
   The EE ABI passes size in $f12 and pos in $a1 in either declaration order (callers
   declare (void *, void *, float)); this order copies pos last, as retail's $s3 shows. */
void func_PAL_0032A898(char *self, float size, float *pos)
{
    float v[4];
    Particle290 *base = D_0022C9A0;
    char *state = *(char **)(self + 0x68);
    Particle290 *p;
    Particle290 *record;
    int i, c;

    for (i = 0; i < 300; i++) {
        p = &base[i];
        if (p->owner)
            continue;
        p->timer2 = p->timer = func_002A7820(80, 200);
        record = p;
        c = func_002A7820(96, 128);
        p->color2 = p->color = c + ((c << 7) & 0xFF00) + ((c << 14) & 0xFF0000);
        p->kind = *(int *)(state + 0x50) % 2 + 1;
        p->life = p->duration = (((int)(func_002A7820(50, 60)) * 5 + 2) / 6);
        p->size = size;
        p->spin = func_002A78D8(180.0f, 720.0f) * 0.0003490659f;
        p->angle = func_002A7940();
        p->owner = self;
        ++*(int *)(state + 0x4C);
        if (pos[3] == -1.0f) {
            func_00282C88(v);
            v[3] = 1.0f;
            v[0] = -0.3f;
            func_00283098(v, v, self + 0xC0);
            func_00282CC0(p, v, self + 0x10);
        } else {
            qcopy(record->pos, pos);
        }
        p->pos[0] += func_002A7878(-0.015f, 0.015f);
        p->pos[1] += func_002A7878(-0.015f, 0.015f);
        p->pos[2] += func_002A7878(-0.015f, 0.015f);
        func_00282C88(p->velocity);
        p->velocity[2] = func_002A7878(0.01f, 0.015f);
        ++*(int *)(state + 0x50);
        break;
    }
}
