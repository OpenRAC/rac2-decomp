/* func_PAL_0032B930, the PAL copy of func_0032A140: the same C, where the 60, 120, 10 and 40 frame
 * counts become 50, 100, 8 and 33 and the 0.0523599 spin step becomes 0.0628319 (x6/5). */
#include "include_asm.h"
#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } Vec4 __attribute__((aligned(16)));
typedef struct { float u, v; } UVPair;

typedef struct {
    char pad[0xE0];
    Vec4 pos;
    char pad2[0x21A0];
    char *object;
} Context;

typedef struct {
    int done;
    int timer;
    char *first;
    char *second;
    int light;
    float radius;
} BlastState;

typedef struct {
    char pad[0x10];
    Vec4 pos;
    unsigned char mode;
    char pad21[0x47];
    BlastState *state;
} Blast;

typedef struct {
    char pad[8];
    float scale;
    int zero;
    Vec4 pos;
} Light;

extern Context D_00189E20;
extern char D_0018A0C0[];
extern UVPair D_00235D00[];
extern char D_001BAFA0[], D_001B5340[];
extern Light D_001C2B40[];
extern int D_001BF000[];
extern int D_001B0590 __attribute__((sda));
extern float func_002A7940(void), func_00283CE0(int), func_002A7790(float);
extern float func_00283180(float), func_00283B98(float,float), func_00283BE0(float,float);
extern int func_00283CF0(float), func_00282948(void *);
extern void func_002AF000(void *,float,float,float), func_00282CC0(void *,void *,void *);
extern void func_00282CF0(void *,void *,void *), func_00282F20(void *,void *,float);
extern int func_002761F8(void *,void *,int,void *,int), func_00277F48(void *,int,void *,int,float);
extern void func_PAL_0032CDB0(void *,void *,int), func_PAL_0032C3B0(void *), func_0032A978(void *);
extern void func_002A8C00(void *,void *,int,void *,float), func_002A8E20(void *,void *);
extern void func_PAL_0032C220(void *), func_0029F338(void *), func_00291450(int);
extern void func_002833F0(void *,void *), func_0032ACF0(void *), func_0032AF50(void *);
extern void func_0032B7D0(void *), func_PAL_0032C9A8(void), func_0027CFD0(void (*)(void),void *);

void func_PAL_0032B930(Blast *self)
{
    float v[4] __attribute__((aligned(16)));
    struct {
        float direction[4];
        char pad10[8];
        unsigned char kind, mode;
        short classid;
        int pad1C;
        int enabled;
        char tail[12];
    } hit;
    BlastState *state = self->state;
    Light *light;
    int count;
    int i;
    int *list;
    void *info;
    float t, ratio, phase;

    qcopy(&self->pos, D_00189E20.object + 0x10);
    switch (self->mode) {
    case 0:
        self->mode = 1;
        state->timer = 50;
        state->radius = 0;
        for (i = 0; i < 137; i++) {
            D_00235D00[i].u = func_002A7940();
            D_00235D00[i].v = func_002A7940();
        }
    case 1:
        self->mode = 2;
    case 2:
        ratio = func_00283CE0(state->timer);
        ratio /= func_00283CE0(50);
        state->radius = func_002A7790(1.0f - ratio) * 15.0f;
        if (state->timer % 3 == 0) {
            float a = func_002A7940();
            float b = func_002A7940();
            func_002AF000(v, state->radius, a, b);
            func_00282CC0(v, v, &D_00189E20.pos);
            if (func_002761F8(&D_00189E20.pos, v, 0, D_00189E20.object, 0))
                qcopy(v, D_001BAFA0);
            func_PAL_0032CDB0(self, v, 8);
        }
        if (state->timer < 8 && !(state->timer & 7))
            func_PAL_0032C3B0(self);
        if (func_00282948(&state->timer)) {
            state->timer = 100;
            self->mode = 3;
            count = func_00277F48(&D_00189E20.pos, 0, self, 0, 15.0f);
            i = 0;
            if (i < count) {
                list = D_001BF000;
                info = &hit;
                for (; i < count; i++) {
                    if ((*(unsigned long long *)((char *)list[i] + 0x30) & 0x500000000000ULL) &&
                        (char *)list[i] != D_00189E20.object &&
                        *(short *)((char *)list[i] + 0xAA) != 3303 && *(short *)((char *)list[i] + 0xAA) != 3000) {
                        func_00282CF0(v, (char *)list[i] + 0x10, &D_00189E20.pos);
                        func_00282F20(v, v, 1.0f);
                        func_00282F20(info, info, 1.0f);
                        func_002A8C00(info, self, 0x830000, v, 30.0f);
                        *(Quad *)hit.direction = *(Quad *)v;
                        hit.enabled = 1;
                        hit.direction[3] = 5627.925f;
                        hit.kind = 5;
                        hit.mode = 3;
                        hit.classid = *(short *)((char *)list[i] + 0xAA);
                        func_002A8E20((char *)list[i], info);
                    }
                }
            }
            func_0032A978(self);
        }
        break;
    case 3:
        if (!(state->timer & 7))
            func_PAL_0032C3B0(self);
        func_00282948(&state->timer);
        func_PAL_0032C220(self);
        if (state->timer == 33)
            self->mode = 4;
        break;
    case 4:
        if (func_00282948(&state->timer) && !state->done) {
            if (state->first)
                func_0029F338(state->first);
            if (state->second)
                func_0029F338(state->second);
            if (state->light != -1)
                func_00291450(state->light);
            D_001B0590 = 0;
            func_0029F338(self);
            return;
        }
        break;
    }
    phase = func_00283CE0(state->timer);
    phase /= func_00283CE0(100);
    phase = 1.0f - phase;
    phase *= 6.2831855f;
    t = (func_00283180(phase - 3.1415927f) + 1.0f) * 0.5f;
    if (state->first) {
        i = func_00283CF0(t * 32.0f);
        **(int **)(state->first + 0x68) = i;
        *(float *)(state->first + 0xF8) = func_00283B98(*(float *)(state->first + 0xF8), 0.062831864f);
        func_002833F0(state->first + 0xC0, state->first + 0xF0);
        *(float *)(state->first + 0xC0) *= 0.5f;
        *(float *)(state->first + 0xD4) *= 0.5f;
        *(float *)(state->first + 0xE8) = t * 1.5f;
        qcopy(state->first + 0x10, D_00189E20.object + 0x10);
    }
    if (state->second) {
        i = func_00283CF0(t * 32.0f);
        **(int **)(state->second + 0x68) = i;
        *(float *)(state->second + 0xF8) = func_00283BE0(*(float *)(state->second + 0xF8), 0.062831864f);
        func_002833F0(state->second + 0xC0, state->second + 0xF0);
        *(float *)(state->second + 0xE8) = t;
        qcopy(state->second + 0x10, D_00189E20.object + 0x10);
    }
    if (state->light != -1) {
        light = &D_001C2B40[state->light];
        func_00282F20(v, D_0018A0C0, 0.5f);
        func_00282CC0(&light->pos, *(char **)(D_0018A0C0 + 0x1FF0) + 16, v);
        func_00282CF0(v, D_001B5340, &light->pos);
        func_00282F20(v, v, 0.15f);
        func_00282CC0(&light->pos, &light->pos, v);
        light->scale = t;
        light->pos.w = 5.0f;
        light->zero = 0;
    }
    func_0032ACF0(self);
    func_0032AF50(self);
    func_0032B7D0(self);
    func_0027CFD0(func_PAL_0032C9A8, self);
}
