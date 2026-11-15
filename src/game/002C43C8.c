#include "include_asm.h"
#include "common.h"

typedef struct {
    u8 pad00[0x20];
    u8 state;
    u8 pad21[0xAA - 0x21];
    s16 uid;
} Moby2C43C8;

typedef struct {
    Moby2C43C8 *moby;
    u8 joint;
    u8 spread;
    s16 uid;
    f32 scale;
    f32 dist;
} Attach2C43C8;

typedef struct {
    u8 pad00[0x10];
    f32 pos[4];
    f32 dir[4];
    Attach2C43C8 at;
} Effect2C43C8;

extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00283CE0(int);
extern void func_0029FC20(void *, int, void *);
extern void func_0029FCC0(void *, int, void *);
extern float func_002A7878(float, float);
extern void func_002B9180(void *);

void func_002C43C8(Effect2C43C8 *e) {
    float mtx[16] __attribute__((aligned(16)));
    float off[4] __attribute__((aligned(16)));
    Attach2C43C8 *at = &e->at;
    Moby2C43C8 *m = at->moby;
    float size;
    float keep;
    float k;
    float r;

    if (m == 0 || m->uid != at->uid || m->state == 0xFE || m->state == 0xFD) {
        func_002B9180(e);
        return;
    }
    size = at->scale * func_002A7878(0.05f, 1.0f);
    keep = e->dir[3];
    func_0029FCC0(e->at.moby, at->joint, e->pos);
    func_0029FC20(e->at.moby, at->joint, mtx);
    k = IntToFloat(at->spread);
    r = func_002A7878(-k, k);
    vec_scale_to_length(off, mtx, (r * 0.01f - 1.0f) * at->dist);
    FastVecAdd(e->dir, e->pos, off);
    e->pos[3] = size;
    e->dir[3] = keep;
}
