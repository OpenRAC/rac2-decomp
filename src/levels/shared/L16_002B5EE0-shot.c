#include "common.h"
typedef struct { float v[4]; void *owner; int flags; unsigned char mode, enabled; unsigned short kind; float radius; int active; } ShotProbe;
typedef struct {
    char pad00[0x30];
    float velocity[4];
    void *owner;
    int pad44;
    int timer;
    int pad4C;
    float size;
    float radius;
    char pad58[8];
    float speed;
    int mode;
    int enabled;
} ShotState;
typedef struct {
    char pad00[0x10];
    float position[4];
    unsigned char state;
    char pad21[0x47];
    ShotState *vars;
    char pad6C[0x3E];
    unsigned short kind;
} ShotMoby;
extern void func_002AFFD8(void *, void *, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00277258(void *, int, float, void *);
extern int func_002E5CF8(void *, int, void *);
extern int func_00283CF0(float);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern int func_00277F48(void *, int, void *, void *, float);
extern int func_00282948(void *);
extern void func_0029F338(void *);
extern void func_L09_003AEE80(void *);

/* Moves a shot, tests it against the level and its targets, and explodes it on contact or timeout. */
void func_L16_003A8D58(ShotMoby *m)
{
    float start[4], scratch[4], old[4];
    ShotProbe probe;
    ShotState *v = m->vars;
    qcopy(start, m->position);
    func_002AFFD8(m->position, scratch, 1);
    qcopy(old, m->position);
    if (m->state == 0) {
        func_00282CC0(m->position, m->position, v->velocity);
        probe.owner = m;
        probe.flags = 0x10001;
        probe.radius = v->radius;
        probe.active = 1;
        qcopy(probe.v, v->velocity);
        func_00282F20(&probe, &probe, v->speed);
        probe.v[3] = 5627.9248046875f;
        probe.mode = v->mode;
        probe.enabled = v->enabled;
        probe.kind = m->kind;
        if (func_002761F8(old, m->position, 0, v->owner, &probe) ||
            func_00277258(m->position, 0, 0.2f, v->owner)) {
            func_002E5CF8(0, 0, m);
            func_002ABBB8(m, v->velocity, 0, 0.0f, 0.0f, func_00283CF0(v->size * 5.0f),
                         func_00283CF0(v->size * 4.0f), func_00283CF0(v->size * 10.0f),
                         0.0f, 0.0f, 9.0f, v->size, -1, 0.0f, 0, 1, -1, 0, 0x810001);
            func_00277F48(m->position, 0x10, v->owner, &probe, 1.0f);
            func_0029F338(m);
            return;
        }
    }
    if (func_00282948(&v->timer)) {
        func_002ABBB8(m, v->velocity, 0, 2.0f, v->radius, func_00283CF0(v->size * 5.0f),
                     func_00283CF0(v->size * 4.0f), func_00283CF0(v->size * 10.0f),
                     0.0f, 0.0f, 9.0f, v->size, -1, 0.0f, 0, 1, -1, 0, 0x810001);
        func_0029F338(m);
        return;
    }
    if (m->position[0] < 2.0f || m->position[0] > 1021.0f ||
        m->position[1] < 2.0f || m->position[1] > 1021.0f ||
        m->position[2] < 2.0f || m->position[2] > 1021.0f) {
        func_0029F338(m);
        return;
    }
    func_L09_003AEE80(m);
}
